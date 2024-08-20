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
    constructor(k42) {
        this.colors = k42;
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
    constructor(c42, d42, e42, f42 = -1, g42 = undefined, h42) {
        super(c42, e42, f42, h42);
        if (typeof g42 === 'function') {
            this.paramsGenerator_ = g42;
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
        this.updateTextAlign = (j42) => {
            if (this.content) {
                this.textAlignment = getTextAlign(j42, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(d42);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b42) {
        if (b42.controller !== undefined) {
            this.controller = b42.controller;
        }
        if (b42.imageRes !== undefined) {
            this.imageRes = b42.imageRes;
        }
        if (b42.imageSize !== undefined) {
            this.imageSize = b42.imageSize;
        }
        if (b42.title !== undefined) {
            this.title = b42.title;
        }
        if (b42.content !== undefined) {
            this.content = b42.content;
        }
        if (b42.checkAction !== undefined) {
            this.checkAction = b42.checkAction;
        }
        if (b42.onCheckedChange !== undefined) {
            this.onCheckedChange = b42.onCheckedChange;
        }
        if (b42.checkTips !== undefined) {
            this.checkTips = b42.checkTips;
        }
        if (b42.isChecked !== undefined) {
            this.isChecked = b42.isChecked;
        }
        if (b42.primaryButton !== undefined) {
            this.primaryButton = b42.primaryButton;
        }
        if (b42.secondaryButton !== undefined) {
            this.secondaryButton = b42.secondaryButton;
        }
        if (b42.buttons !== undefined) {
            this.buttons = b42.buttons;
        }
        if (b42.textAlignment !== undefined) {
            this.textAlignment = b42.textAlignment;
        }
        if (b42.marginOffset !== undefined) {
            this.marginOffset = b42.marginOffset;
        }
        if (b42.contentScroller !== undefined) {
            this.contentScroller = b42.contentScroller;
        }
        if (b42.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b42.fontColorWithTheme;
        }
        if (b42.theme !== undefined) {
            this.theme = b42.theme;
        }
        if (b42.themeColorMode !== undefined) {
            this.themeColorMode = b42.themeColorMode;
        }
        if (b42.fontSizeScale !== undefined) {
            this.fontSizeScale = b42.fontSizeScale;
        }
        if (b42.minContentHeight !== undefined) {
            this.minContentHeight = b42.minContentHeight;
        }
        if (b42.updateTextAlign !== undefined) {
            this.updateTextAlign = b42.updateTextAlign;
        }
        if (b42.imageIndex !== undefined) {
            this.imageIndex = b42.imageIndex;
        }
        if (b42.textIndex !== undefined) {
            this.textIndex = b42.textIndex;
        }
        if (b42.checkBoxIndex !== undefined) {
            this.checkBoxIndex = b42.checkBoxIndex;
        }
    }

    updateStateVars(a42) {
    }

    purgeVariableDependenciesOnElmtId(z41) {
        this.__imageSize.purgeDependencyOnElmtId(z41);
        this.__isChecked.purgeDependencyOnElmtId(z41);
        this.__textAlignment.purgeDependencyOnElmtId(z41);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z41);
        this.__fontSizeScale.purgeDependencyOnElmtId(z41);
        this.__minContentHeight.purgeDependencyOnElmtId(z41);
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

    setController(y41) {
        this.controller = y41;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(x41) {
        this.__imageSize.set(x41);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(w41) {
        this.__isChecked.set(w41);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(v41) {
        this.__textAlignment.set(v41);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(u41) {
        this.__fontColorWithTheme.set(u41);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(t41) {
        this.__fontSizeScale.set(t41);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(s41) {
        this.__minContentHeight.set(s41);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((q41, r41) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((k41, l41) => {
                if (l41) {
                    let m41 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, k41, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 120, col: 5 });
                    ViewPU.create(m41);
                    let b1 = () => {
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
                    m41.paramsGenerator_ = b1;
                } else {
                    this.updateStateVarsOfChildByElmtId(k41, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    contentBuilder(o39 = null) {
        {
            this.observeComponentCreation2((q39, r39) => {
                if (r39) {
                    let s39 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((q40, r40) => {
                                ForEach.create();
                                const a1 = u40 => {
                                    const v40 = u40;
                                    this.observeComponentCreation2((x40, y40) => {
                                        If.create();
                                        if (v40 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (v40 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((f41, g41) => {
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
                                                this.textPart.bind(this)();
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.observeComponentCreation2((b41, c41) => {
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
                                this.forEachUpdateFunction(q40, [this.imageIndex, this.textIndex, this.checkBoxIndex],
                                    a1);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, q39, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 135, col: 5 });
                    ViewPU.create(s39);
                    let y = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((x39, y39) => {
                                    ForEach.create();
                                    const z = b40 => {
                                        const c40 = b40;
                                        this.observeComponentCreation2((e40, f40) => {
                                            If.create();
                                            if (c40 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (c40 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((m40, n40) => {
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
                                                    this.textPart.bind(this)();
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.observeComponentCreation2((i40, j40) => {
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
                                    this.forEachUpdateFunction(x39,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], z);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    s39.paramsGenerator_ = y;
                } else {
                    this.updateStateVarsOfChildByElmtId(q39, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(w38 = null) {
        this.observeComponentCreation2((l39, m39) => {
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
        this.observeComponentCreation2((z38, a39) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h39, i39) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((k39) => {
                            this.isChecked = k39;
                            if (this.checkAction) {
                                this.checkAction(k39);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(k39);
                            }
                        });
                        Checkbox.accessibilityLevel('yes');
                        Checkbox.margin({
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level4'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((f39, g39) => {
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

    imagePart(p38 = null) {
        this.observeComponentCreation2((u38, v38) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((s38, t38) => {
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

    textPart(k37 = null) {
        this.observeComponentCreation2((n38, o38) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((l38, m38) => {
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
        this.observeComponentCreation2((b38, c38) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j38, k38) => {
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
                    this.observeComponentCreation2((h38, i38) => {
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
        this.observeComponentCreation2((p37, q37) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z37, a38) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((v37, w37) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((y37) => {
                            if (y37) {
                                resolveKeyEvent(y37, this.contentScroller);
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
    constructor(c37, d37, e37, f37 = -1, g37 = undefined, h37) {
        super(c37, e37, f37, h37);
        if (typeof g37 === 'function') {
            this.paramsGenerator_ = g37;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (j37) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(d37.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(d37);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b37) {
        if (b37.title !== undefined) {
            this.title = b37.title;
        }
        if (b37.content !== undefined) {
            this.content = b37.content;
        }
        if (b37.checkTips !== undefined) {
            this.checkTips = b37.checkTips;
        }
        if (b37.updateTextAlign !== undefined) {
            this.updateTextAlign = b37.updateTextAlign;
        }
        if (b37.dialogBuilder !== undefined) {
            this.dialogBuilder = b37.dialogBuilder;
        }
        if (b37.imageIndex !== undefined) {
            this.imageIndex = b37.imageIndex;
        }
        if (b37.textIndex !== undefined) {
            this.textIndex = b37.textIndex;
        }
        if (b37.checkBoxIndex !== undefined) {
            this.checkBoxIndex = b37.checkBoxIndex;
        }
        if (b37.childrenSize !== undefined) {
            this.childrenSize = b37.childrenSize;
        }
    }

    updateStateVars(a37) {
    }

    purgeVariableDependenciesOnElmtId(z36) {
        this.__minContentHeight.purgeDependencyOnElmtId(z36);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(y36 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(x36) {
        this.__minContentHeight.set(x36);
    }

    onPlaceChildren(q36, r36, s36) {
        let t36 = 0;
        let u36 = 0;
        for (let v36 = 0; v36 < r36.length; v36++) {
            let w36 = r36[v36];
            w36.layout({ x: t36, y: u36 });
            u36 += w36.measureResult.height;
        }
    }

    onMeasureSize(y35, z35, a36) {
        let b36 = { width: Number(a36.maxWidth), height: 0 };
        if (z35.length < this.childrenSize) {
            return b36;
        }
        let c36 = 0;
        let d36 = 0;
        if (this.checkTips !== null) {
            let n36 = z35[this.checkBoxIndex];
            let o36 = {
                maxWidth: a36.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: a36.maxHeight
            };
            let p36 = n36.measure(o36);
            d36 = p36.height;
            c36 += d36;
        }
        let e36 = z35[this.imageIndex];
        let f36 = 0;
        if (this.title !== null || this.content !== null) {
            f36 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let g36 = Number(a36.maxHeight) - d36 - f36;
        let h36 = {
            maxWidth: a36.maxWidth,
            maxHeight: g36
        };
        let i36 = e36.measure(h36);
        c36 += i36.height;
        if (this.title !== null || this.content !== null) {
            let j36 = z35[this.textIndex];
            this.updateTextAlign(b36.width);
            let k36 = Number(a36.maxHeight) - i36.height - d36;
            let l36 = {
                maxWidth: a36.maxWidth,
                maxHeight: Math.max(k36, TEXT_MIN_HEIGHT)
            };
            let m36 = j36.measure(l36);
            c36 += m36.height;
        }
        b36.height = c36;
        this.minContentHeight = Math.max(d36 + i36.height + f36, MIN_CONTENT_HEIGHT);
        return b36;
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
    constructor(s35, t35, u35, v35 = -1, w35 = undefined, x35) {
        super(s35, u35, v35, x35);
        if (typeof w35 === 'function') {
            this.paramsGenerator_ = w35;
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
        this.setInitiallyProvidedValue(t35);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r35) {
        if (r35.controller !== undefined) {
            this.controller = r35.controller;
        }
        if (r35.title !== undefined) {
            this.title = r35.title;
        }
        if (r35.content !== undefined) {
            this.content = r35.content;
        }
        if (r35.confirm !== undefined) {
            this.confirm = r35.confirm;
        }
        if (r35.radioContent !== undefined) {
            this.radioContent = r35.radioContent;
        }
        if (r35.buttons !== undefined) {
            this.buttons = r35.buttons;
        }
        if (r35.contentPadding !== undefined) {
            this.contentPadding = r35.contentPadding;
        }
        if (r35.isFocus !== undefined) {
            this.isFocus = r35.isFocus;
        }
        if (r35.currentFocusIndex !== undefined) {
            this.currentFocusIndex = r35.currentFocusIndex;
        }
        if (r35.radioHeight !== undefined) {
            this.radioHeight = r35.radioHeight;
        }
        if (r35.itemHeight !== undefined) {
            this.itemHeight = r35.itemHeight;
        }
        if (r35.selectedIndex !== undefined) {
            this.selectedIndex = r35.selectedIndex;
        }
        if (r35.contentBuilder !== undefined) {
            this.contentBuilder = r35.contentBuilder;
        }
        if (r35.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = r35.fontColorWithTheme;
        }
        if (r35.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = r35.dividerColorWithTheme;
        }
        if (r35.theme !== undefined) {
            this.theme = r35.theme;
        }
        if (r35.themeColorMode !== undefined) {
            this.themeColorMode = r35.themeColorMode;
        }
        if (r35.contentScroller !== undefined) {
            this.contentScroller = r35.contentScroller;
        }
        if (r35.fontSizeScale !== undefined) {
            this.fontSizeScale = r35.fontSizeScale;
        }
        if (r35.minContentHeight !== undefined) {
            this.minContentHeight = r35.minContentHeight;
        }
    }

    updateStateVars(q35) {
    }

    purgeVariableDependenciesOnElmtId(p35) {
        this.__selectedIndex.purgeDependencyOnElmtId(p35);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(p35);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(p35);
        this.__fontSizeScale.purgeDependencyOnElmtId(p35);
        this.__minContentHeight.purgeDependencyOnElmtId(p35);
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

    setController(o35) {
        this.controller = o35;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(n35) {
        this.__selectedIndex.set(n35);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m35) {
        this.__fontColorWithTheme.set(m35);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(l35) {
        this.__dividerColorWithTheme.set(l35);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k35) {
        this.__fontSizeScale.set(k35);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(j35) {
        this.__minContentHeight.set(j35);
    }

    buildContent(k32 = null) {
        this.observeComponentCreation2((d35, e35) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((g35, h35) => {
                let i35 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (h35 > 0) {
                            this.contentScroller.scrollBy(0, i35);
                        } else if (h35 < 0) {
                            this.contentScroller.scrollBy(0, 0 - i35);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((b35, c35) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((r34, s34) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z34, a35) => {
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
                    this.observeComponentCreation2((x34, y34) => {
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
        this.observeComponentCreation2((o34, p34) => {
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
        this.observeComponentCreation2((q32, r32) => {
            ForEach.create();
            const u = (u32, v32) => {
                const w32 = u32;
                {
                    const v = (m34, n34) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m34);
                        w(m34, n34);
                        if (!n34) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const w = (h34, i34) => {
                        ListItem.create(x, true);
                        ListItem.onSizeChange((k34, l34) => {
                            this.itemHeight = Number(l34.height);
                        });
                    };
                    const x = (d33, e33) => {
                        v(d33, e33);
                        this.observeComponentCreation2((f34, g34) => {
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
                        this.observeComponentCreation2((c34, d34) => {
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
                                this.selectedIndex = v32;
                                w32.action && w32.action();
                                this.controller?.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((a34, b34) => {
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
                        this.observeComponentCreation2((y33, z33) => {
                            Text.create(w32.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((s33, t33) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === v32);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(v32));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = v32;
                                if (v32 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (v32 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((w33, x33) => {
                                this.radioHeight = Number(x33.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((l33, m33) => {
                            If.create();
                            if (v32 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((q33, r33) => {
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
                    this.observeComponentCreation2(w, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(q32, this.radioContent, u, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((i32, j32) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((c32, d32) => {
                if (d32) {
                    let e32 = new CustomDialogContentComponent(this, {
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
                    }, undefined, c32, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 507, col: 5 });
                    ViewPU.create(e32);
                    let t = () => {
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
                    e32.paramsGenerator_ = t;
                } else {
                    this.updateStateVarsOfChildByElmtId(c32, {});
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
    constructor(s31, t31, u31, v31 = -1, w31 = undefined, x31) {
        super(s31, u31, v31, x31);
        if (typeof w31 === 'function') {
            this.paramsGenerator_ = w31;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(t31.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (z31) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(t31);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r31) {
        if (r31.textIndex !== undefined) {
            this.textIndex = r31.textIndex;
        }
        if (r31.checkboxIndex !== undefined) {
            this.checkboxIndex = r31.checkboxIndex;
        }
        if (r31.updateTextAlign !== undefined) {
            this.updateTextAlign = r31.updateTextAlign;
        }
        if (r31.dialogBuilder !== undefined) {
            this.dialogBuilder = r31.dialogBuilder;
        }
    }

    updateStateVars(q31) {
    }

    purgeVariableDependenciesOnElmtId(p31) {
        this.__minContentHeight.purgeDependencyOnElmtId(p31);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(o31) {
        this.__minContentHeight.set(o31);
    }

    doNothingBuilder(n31 = null) {
    }

    onPlaceChildren(g31, h31, i31) {
        let j31 = 0;
        let k31 = 0;
        for (let l31 = 0; l31 < h31.length; l31++) {
            let m31 = h31[l31];
            m31.layout({ x: j31, y: k31 });
            k31 += m31.measureResult.height;
        }
    }

    onMeasureSize(u30, v30, w30) {
        let x30 = { width: Number(w30.maxWidth), height: 0 };
        let y30 = 2;
        if (v30.length < y30) {
            return x30;
        }
        this.updateTextAlign(x30.width);
        let z30 = 0;
        let a31 = v30[this.checkboxIndex];
        let b31 = {
            maxWidth: w30.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: w30.maxHeight
        };
        let c31 = a31.measure(b31);
        z30 += c31.height;
        let d31 = v30[this.textIndex];
        let e31 = {
            maxWidth: w30.maxWidth,
            maxHeight: Number(w30.maxHeight) - z30
        };
        let f31 = d31.measure(e31);
        z30 += f31.height;
        x30.height = z30;
        this.minContentHeight = Math.max(c31.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return x30;
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
    constructor(m30, n30, o30, p30 = -1, q30 = undefined, r30) {
        super(m30, o30, p30, r30);
        if (typeof q30 === 'function') {
            this.paramsGenerator_ = q30;
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
        this.updateTextAlign = (t30) => {
            if (this.content) {
                this.textAlign = getTextAlign(t30, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(n30);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l30) {
        if (l30.controller !== undefined) {
            this.controller = l30.controller;
        }
        if (l30.title !== undefined) {
            this.title = l30.title;
        }
        if (l30.content !== undefined) {
            this.content = l30.content;
        }
        if (l30.checkTips !== undefined) {
            this.checkTips = l30.checkTips;
        }
        if (l30.isChecked !== undefined) {
            this.isChecked = l30.isChecked;
        }
        if (l30.primaryButton !== undefined) {
            this.primaryButton = l30.primaryButton;
        }
        if (l30.secondaryButton !== undefined) {
            this.secondaryButton = l30.secondaryButton;
        }
        if (l30.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = l30.fontColorWithTheme;
        }
        if (l30.theme !== undefined) {
            this.theme = l30.theme;
        }
        if (l30.themeColorMode !== undefined) {
            this.themeColorMode = l30.themeColorMode;
        }
        if (l30.onCheckedChange !== undefined) {
            this.onCheckedChange = l30.onCheckedChange;
        }
        if (l30.contentScroller !== undefined) {
            this.contentScroller = l30.contentScroller;
        }
        if (l30.buttons !== undefined) {
            this.buttons = l30.buttons;
        }
        if (l30.textAlign !== undefined) {
            this.textAlign = l30.textAlign;
        }
        if (l30.marginOffset !== undefined) {
            this.marginOffset = l30.marginOffset;
        }
        if (l30.fontSizeScale !== undefined) {
            this.fontSizeScale = l30.fontSizeScale;
        }
        if (l30.minContentHeight !== undefined) {
            this.minContentHeight = l30.minContentHeight;
        }
        if (l30.textIndex !== undefined) {
            this.textIndex = l30.textIndex;
        }
        if (l30.checkboxIndex !== undefined) {
            this.checkboxIndex = l30.checkboxIndex;
        }
        if (l30.updateTextAlign !== undefined) {
            this.updateTextAlign = l30.updateTextAlign;
        }
    }

    updateStateVars(k30) {
    }

    purgeVariableDependenciesOnElmtId(j30) {
        this.__isChecked.purgeDependencyOnElmtId(j30);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(j30);
        this.__textAlign.purgeDependencyOnElmtId(j30);
        this.__fontSizeScale.purgeDependencyOnElmtId(j30);
        this.__minContentHeight.purgeDependencyOnElmtId(j30);
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

    setController(i30) {
        this.controller = i30;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(h30) {
        this.__isChecked.set(h30);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(g30) {
        this.__fontColorWithTheme.set(g30);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(f30) {
        this.__textAlign.set(f30);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(e30) {
        this.__fontSizeScale.set(e30);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(d30) {
        this.__minContentHeight.set(d30);
    }

    textBuilder(o29 = null) {
        this.observeComponentCreation2((b30, c30) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((z29, a30) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((x29, y29) => {
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
        this.observeComponentCreation2((t29, u29) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(this.textAlign);
            Text.onKeyEvent((s) => {
                if (s) {
                    resolveKeyEvent(s, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(b29 = null) {
        this.observeComponentCreation2((l29, m29) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((h29, i29) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((k29) => {
                this.isChecked = k29;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.accessibilityLevel('yes');
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((f29, g29) => {
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

    buildContent(n27 = null) {
        {
            this.observeComponentCreation2((p27, q27) => {
                if (q27) {
                    let r27 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((m28, n28) => {
                                ForEach.create();
                                const r = q28 => {
                                    const r28 = q28;
                                    this.observeComponentCreation2((t28, u28) => {
                                        If.create();
                                        if (r28 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.textBuilder.bind(this)();
                                            });
                                        } else if (r28 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((y28, z28) => {
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
                                this.forEachUpdateFunction(m28, [this.textIndex, this.checkboxIndex], r);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, p27, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 710, col: 5 });
                    ViewPU.create(r27);
                    let m = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((w27, x27) => {
                                    ForEach.create();
                                    const n = a28 => {
                                        const b28 = a28;
                                        this.observeComponentCreation2((d28, e28) => {
                                            If.create();
                                            if (b28 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.textBuilder.bind(this)();
                                                });
                                            } else if (b28 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((i28, j28) => {
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
                                    this.forEachUpdateFunction(w27, [this.textIndex, this.checkboxIndex], n);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    r27.paramsGenerator_ = m;
                } else {
                    this.updateStateVarsOfChildByElmtId(p27, {});
                }
            }, { name: "ConfirmDialogContentLayout" });
        }
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((l27, m27) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((f27, g27) => {
                if (g27) {
                    let h27 = new CustomDialogContentComponent(this, {
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
                    }, undefined, f27, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 724, col: 5 });
                    ViewPU.create(h27);
                    let l = () => {
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
                    h27.paramsGenerator_ = l;
                } else {
                    this.updateStateVarsOfChildByElmtId(f27, {});
                }
            }, { name: "CustomDialogContentComponent" });
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
    constructor(x26, y26, z26, a27 = -1, b27 = undefined, c27) {
        super(x26, z26, a27, c27);
        if (typeof b27 === 'function') {
            this.paramsGenerator_ = b27;
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
        this.setInitiallyProvidedValue(y26);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w26) {
        if (w26.controller !== undefined) {
            this.controller = w26.controller;
        }
        if (w26.primaryTitle !== undefined) {
            this.primaryTitle = w26.primaryTitle;
        }
        if (w26.secondaryTitle !== undefined) {
            this.secondaryTitle = w26.secondaryTitle;
        }
        if (w26.content !== undefined) {
            this.content = w26.content;
        }
        if (w26.primaryButton !== undefined) {
            this.primaryButton = w26.primaryButton;
        }
        if (w26.secondaryButton !== undefined) {
            this.secondaryButton = w26.secondaryButton;
        }
        if (w26.buttons !== undefined) {
            this.buttons = w26.buttons;
        }
        if (w26.textAlign !== undefined) {
            this.textAlign = w26.textAlign;
        }
        if (w26.contentScroller !== undefined) {
            this.contentScroller = w26.contentScroller;
        }
        if (w26.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = w26.fontColorWithTheme;
        }
        if (w26.theme !== undefined) {
            this.theme = w26.theme;
        }
        if (w26.themeColorMode !== undefined) {
            this.themeColorMode = w26.themeColorMode;
        }
        if (w26.fontSizeScale !== undefined) {
            this.fontSizeScale = w26.fontSizeScale;
        }
        if (w26.minContentHeight !== undefined) {
            this.minContentHeight = w26.minContentHeight;
        }
    }

    updateStateVars(v26) {
    }

    purgeVariableDependenciesOnElmtId(u26) {
        this.__textAlign.purgeDependencyOnElmtId(u26);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(u26);
        this.__fontSizeScale.purgeDependencyOnElmtId(u26);
        this.__minContentHeight.purgeDependencyOnElmtId(u26);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(t26) {
        this.controller = t26;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(s26) {
        this.__textAlign.set(s26);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(r26) {
        this.__fontColorWithTheme.set(r26);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(q26) {
        this.__fontSizeScale.set(q26);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(p26) {
        this.__minContentHeight.set(p26);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((n26, o26) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((h26, i26) => {
                if (i26) {
                    let j26 = new CustomDialogContentComponent(this, {
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
                    }, undefined, h26, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 782, col: 5 });
                    ViewPU.create(j26);
                    let k = () => {
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
                    j26.paramsGenerator_ = k;
                } else {
                    this.updateStateVarsOfChildByElmtId(h26, {});
                }
            }, { name: "CustomDialogContentComponent" });
        }
        __Common__.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    AlertDialogContentBuilder(q25 = null) {
        this.observeComponentCreation2((d26, e26) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((b26, c26) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((u25, v25) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
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
            Text.onAreaChange((i, j) => {
                this.updateTextAlign(Number(j.width));
            });
            Text.onKeyEvent((g) => {
                if (g) {
                    resolveKeyEvent(g, this.contentScroller);
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

    updateTextAlign(p25) {
        this.textAlign = getTextAlign(p25, this.content, `${BODY_L * this.fontSizeScale}vp`);
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
    constructor(j25, k25, l25, m25 = -1, n25 = undefined, o25) {
        super(j25, l25, m25, o25);
        if (typeof n25 === 'function') {
            this.paramsGenerator_ = n25;
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
        this.setInitiallyProvidedValue(k25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i25) {
        if (i25.controller !== undefined) {
            this.controller = i25.controller;
        }
        if (i25.primaryTitle !== undefined) {
            this.primaryTitle = i25.primaryTitle;
        }
        if (i25.secondaryTitle !== undefined) {
            this.secondaryTitle = i25.secondaryTitle;
        }
        if (i25.contentBuilder !== undefined) {
            this.contentBuilder = i25.contentBuilder;
        }
        if (i25.contentAreaPadding !== undefined) {
            this.contentAreaPadding = i25.contentAreaPadding;
        }
        if (i25.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = i25.localizedContentAreaPadding;
        }
        if (i25.buttons !== undefined) {
            this.buttons = i25.buttons;
        }
        if (i25.theme !== undefined) {
            this.theme = i25.theme;
        }
        if (i25.themeColorMode !== undefined) {
            this.themeColorMode = i25.themeColorMode;
        }
        if (i25.fontSizeScale !== undefined) {
            this.fontSizeScale = i25.fontSizeScale;
        }
        if (i25.minContentHeight !== undefined) {
            this.minContentHeight = i25.minContentHeight;
        }
    }

    updateStateVars(h25) {
    }

    purgeVariableDependenciesOnElmtId(g25) {
        this.__fontSizeScale.purgeDependencyOnElmtId(g25);
        this.__minContentHeight.purgeDependencyOnElmtId(g25);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(f25) {
        this.controller = f25;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(e25) {
        this.__fontSizeScale.set(e25);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(d25) {
        this.__minContentHeight.set(d25);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((b25, c25) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((v24, w24) => {
                if (w24) {
                    let x24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, v24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 875, col: 5 });
                    ViewPU.create(x24);
                    let f = () => {
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
                    x24.paramsGenerator_ = f;
                } else {
                    this.updateStateVarsOfChildByElmtId(v24, {});
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
    constructor(s24) {
        super(s24);
        this.arg_ = s24;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(m24, n24, o24, p24 = -1, q24 = undefined, r24) {
        super(m24, o24, p24, r24);
        if (typeof q24 === 'function') {
            this.paramsGenerator_ = q24;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(n24.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(n24.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(n24.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(n24);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l24) {
        if (l24.dialogBuilder !== undefined) {
            this.dialogBuilder = l24.dialogBuilder;
        }
        if (l24.titleIndex !== undefined) {
            this.titleIndex = l24.titleIndex;
        }
        if (l24.contentIndex !== undefined) {
            this.contentIndex = l24.contentIndex;
        }
        if (l24.buttonIndex !== undefined) {
            this.buttonIndex = l24.buttonIndex;
        }
    }

    updateStateVars(k24) {
    }

    purgeVariableDependenciesOnElmtId(j24) {
        this.__titleHeight.purgeDependencyOnElmtId(j24);
        this.__buttonHeight.purgeDependencyOnElmtId(j24);
        this.__titleMinHeight.purgeDependencyOnElmtId(j24);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(i24 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(h24) {
        this.__titleHeight.set(h24);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(g24) {
        this.__buttonHeight.set(g24);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(f24) {
        this.__titleMinHeight.set(f24);
    }

    onPlaceChildren(y23, z23, a24) {
        let b24 = 0;
        let c24 = 0;
        for (let d24 = 0; d24 < z23.length; d24++) {
            let e24 = z23[d24];
            e24.layout({ x: b24, y: c24 });
            c24 += e24.measureResult.height;
        }
    }

    onMeasureSize(k23, l23, m23) {
        let n23 = { width: Number(m23.maxWidth), height: 0 };
        let o23 = 3;
        if (l23.length < o23) {
            return n23;
        }
        let p23 = 0;
        let q23 = l23[this.titleIndex];
        let r23 = {
            maxWidth: m23.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: m23.maxHeight
        };
        let s23 = q23.measure(r23);
        this.titleHeight = s23.height;
        p23 += this.titleHeight;
        let t23 = l23[this.buttonIndex];
        let u23 = t23.measure(m23);
        this.buttonHeight = u23.height;
        p23 += this.buttonHeight;
        let v23 = l23[this.contentIndex];
        let w23 = {
            maxWidth: m23.maxWidth,
            maxHeight: Number(m23.maxHeight) - p23
        };
        let x23 = v23.measure(w23);
        p23 += x23.height;
        n23.height = p23;
        return n23;
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
    constructor(e23, f23, g23, h23 = -1, i23 = undefined, j23) {
        super(e23, g23, h23, j23);
        if (typeof i23 === 'function') {
            this.paramsGenerator_ = i23;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(f23.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(f23.fontSizeScale, this, 'fontSizeScale');
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
        this.setInitiallyProvidedValue(f23);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d23) {
        if (d23.controller !== undefined) {
            this.controller = d23.controller;
        }
        if (d23.primaryTitle !== undefined) {
            this.primaryTitle = d23.primaryTitle;
        }
        if (d23.secondaryTitle !== undefined) {
            this.secondaryTitle = d23.secondaryTitle;
        }
        if (d23.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = d23.localizedContentAreaPadding;
        }
        if (d23.contentBuilder !== undefined) {
            this.contentBuilder = d23.contentBuilder;
        }
        if (d23.buttons !== undefined) {
            this.buttons = d23.buttons;
        }
        if (d23.contentAreaPadding !== undefined) {
            this.contentAreaPadding = d23.contentAreaPadding;
        }
        if (d23.keyIndex !== undefined) {
            this.keyIndex = d23.keyIndex;
        }
        if (d23.theme !== undefined) {
            this.theme = d23.theme;
        }
        if (d23.themeColorMode !== undefined) {
            this.themeColorMode = d23.themeColorMode;
        }
        if (d23.titleHeight !== undefined) {
            this.titleHeight = d23.titleHeight;
        }
        if (d23.buttonHeight !== undefined) {
            this.buttonHeight = d23.buttonHeight;
        }
        if (d23.contentMaxHeight !== undefined) {
            this.contentMaxHeight = d23.contentMaxHeight;
        }
        if (d23.customStyle !== undefined) {
            this.customStyle = d23.customStyle;
        }
        if (d23.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = d23.buttonMaxFontSize;
        }
        if (d23.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = d23.buttonMinFontSize;
        }
        if (d23.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = d23.primaryTitleMaxFontSize;
        }
        if (d23.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = d23.primaryTitleMinFontSize;
        }
        if (d23.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = d23.secondaryTitleMaxFontSize;
        }
        if (d23.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = d23.secondaryTitleMinFontSize;
        }
        if (d23.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = d23.primaryTitleFontColorWithTheme;
        }
        if (d23.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = d23.secondaryTitleFontColorWithTheme;
        }
        if (d23.titleTextAlign !== undefined) {
            this.titleTextAlign = d23.titleTextAlign;
        }
        if (d23.isButtonVertical !== undefined) {
            this.isButtonVertical = d23.isButtonVertical;
        }
        if (d23.titleMinHeight !== undefined) {
            this.titleMinHeight = d23.titleMinHeight;
        }
        if (d23.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = d23.isFollowingSystemFontScale;
        }
        if (d23.appMaxFontScale !== undefined) {
            this.appMaxFontScale = d23.appMaxFontScale;
        }
        if (d23.titleIndex !== undefined) {
            this.titleIndex = d23.titleIndex;
        }
        if (d23.contentIndex !== undefined) {
            this.contentIndex = d23.contentIndex;
        }
        if (d23.buttonIndex !== undefined) {
            this.buttonIndex = d23.buttonIndex;
        }
    }

    updateStateVars(c23) {
    }

    purgeVariableDependenciesOnElmtId(b23) {
        this.__minContentHeight.purgeDependencyOnElmtId(b23);
        this.__titleHeight.purgeDependencyOnElmtId(b23);
        this.__buttonHeight.purgeDependencyOnElmtId(b23);
        this.__contentMaxHeight.purgeDependencyOnElmtId(b23);
        this.__fontSizeScale.purgeDependencyOnElmtId(b23);
        this.__customStyle.purgeDependencyOnElmtId(b23);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(b23);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(b23);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(b23);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(b23);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(b23);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(b23);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(b23);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(b23);
        this.__titleTextAlign.purgeDependencyOnElmtId(b23);
        this.__isButtonVertical.purgeDependencyOnElmtId(b23);
        this.__titleMinHeight.purgeDependencyOnElmtId(b23);
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

    set minContentHeight(a23) {
        this.__minContentHeight.set(a23);
    }

    defaultContentBuilder(z22 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(y22) {
        this.__titleHeight.set(y22);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(x22) {
        this.__buttonHeight.set(x22);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(w22) {
        this.__contentMaxHeight.set(w22);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(v22) {
        this.__fontSizeScale.set(v22);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(u22) {
        this.__customStyle.set(u22);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(t22) {
        this.__buttonMaxFontSize.set(t22);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(s22) {
        this.__buttonMinFontSize.set(s22);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(r22) {
        this.__primaryTitleMaxFontSize.set(r22);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(q22) {
        this.__primaryTitleMinFontSize.set(q22);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(p22) {
        this.__secondaryTitleMaxFontSize.set(p22);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(o22) {
        this.__secondaryTitleMinFontSize.set(o22);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(n22) {
        this.__primaryTitleFontColorWithTheme.set(n22);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(m22) {
        this.__secondaryTitleFontColorWithTheme.set(m22);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(l22) {
        this.__titleTextAlign.set(l22);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(k22) {
        this.__isButtonVertical.set(k22);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(j22) {
        this.__titleMinHeight.set(j22);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((f22, g22) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((d22, e22) => {
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
        this.observeComponentCreation2((b22, c22) => {
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
            this.observeComponentCreation2((x19, y19) => {
                if (y19) {
                    let z19 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((d21, e21) => {
                                ForEach.create();
                                const e = h21 => {
                                    const i21 = h21;
                                    this.observeComponentCreation2((k21, l21) => {
                                        If.create();
                                        if (i21 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((z21, a22) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (i21 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((v21, w21) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((t21, u21) => {
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
                                                this.observeComponentCreation2((o21, p21) => {
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
                                this.forEachUpdateFunction(d21, [this.titleIndex, this.contentIndex, this.buttonIndex],
                                    e);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, x19, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1013, col: 11 });
                    ViewPU.create(z19);
                    let c = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((e20, f20) => {
                                    ForEach.create();
                                    const d = i20 => {
                                        const j20 = i20;
                                        this.observeComponentCreation2((l20, m20) => {
                                            If.create();
                                            if (j20 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((a21, b21) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (j20 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((w20, x20) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((u20, v20) => {
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
                                                    this.observeComponentCreation2((p20, q20) => {
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
                                    this.forEachUpdateFunction(e20,
                                        [this.titleIndex, this.contentIndex, this.buttonIndex], d);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    z19.paramsGenerator_ = c;
                } else {
                    this.updateStateVarsOfChildByElmtId(x19, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    onMeasureSize(j19, k19, l19) {
        let m19 = { width: j19.width, height: j19.height };
        let n19 = Number(l19.maxWidth);
        let o19 = Number(l19.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(n19 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let p19 = 0;
        k19.forEach((r19) => {
            this.contentMaxHeight = '100%';
            let s19 = r19.measure(l19);
            if (o19 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                s19 = r19.measure(l19);
            }
            p19 += s19.height;
        });
        m19.height = p19;
        m19.width = n19;
        return m19;
    }

    aboutToAppear() {
        let h19 = this.getUIContext();
        this.isFollowingSystemFontScale = h19.isFollowingSystemFontScale();
        this.appMaxFontScale = h19.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let i19 = this.controller;
            if (i19.arg_ && i19.arg_.customStyle && i19.arg_.customStyle === true) {
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
            let f19 = this.getUIContext();
            let g19 = f19.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(g19, this.appMaxFontScale);
        }
        catch (c19) {
            let d19 = c19.code;
            let e19 = c19.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${d19}, message: ${e19}`);
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

    titleBuilder(b18 = null) {
        this.observeComponentCreation2((a19, b19) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((y18, z18) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((w18, x18) => {
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
        this.observeComponentCreation2((m18, n18) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u18, v18) => {
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
        this.observeComponentCreation2((k18, l18) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((i18, j18) => {
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
        let a18 = ALERT_TITLE_ALIGNMENT;
        if (a18 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (a18 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (a18 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (a18 === TextAlign.JUSTIFY) {
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

    ButtonBuilder(m17 = null) {
        this.observeComponentCreation2((y17, z17) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((p17, q17) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u17, v17) => {
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

    buildSingleButton(r16, s16 = null) {
        this.observeComponentCreation2((u16, v16) => {
            If.create();
            if (this.isNewPropertiesHighPriority(r16)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k17, l17) => {
                        Button.createWithLabel(r16.value);
                        __Button__setButtonProperties(r16, this.controller);
                        Button.role(r16.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (r16.background !== undefined && r16.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g17, h17) => {
                        Button.createWithLabel(r16.value);
                        __Button__setButtonProperties(r16, this.controller);
                        Button.backgroundColor(r16.background);
                        Button.fontColor(r16.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (r16.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((c17, d17) => {
                        Button.createWithLabel(r16.value);
                        __Button__setButtonProperties(r16, this.controller);
                        Button.backgroundColor(r16.background);
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
                    this.observeComponentCreation2((y16, z16) => {
                        Button.createWithLabel(r16.value);
                        __Button__setButtonProperties(r16, this.controller);
                        Button.fontColor(r16.fontColor);
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

    buildHorizontalAlignButtons(a16 = null) {
        this.observeComponentCreation2((c16, d16) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p16, q16) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((i16, j16) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n16, o16) => {
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

    buildVerticalAlignButtons(h15 = null) {
        this.observeComponentCreation2((j15, k15) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y15, z15) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((p15, q15) => {
                        ForEach.create();
                        const b = (v15, w15) => {
                            const x15 = v15;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - w15 - 1 : w15);
                        };
                        this.forEachUpdateFunction(p15, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), b, (u15) => u15.value.toString(), true, false);
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

    isNewPropertiesHighPriority(g15) {
        if (g15.role === ButtonRole.ERROR) {
            return true;
        }
        if (g15.buttonStyle !== undefined &&
            g15.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (g15.background === undefined && g15.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(o14, p14 = null) {
        this.observeComponentCreation2((r14, s14) => {
            If.create();
            if (this.buttons && this.buttons[o14]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e15, f15) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[o14]);
                    Row.pop();
                    this.observeComponentCreation2((x14, y14) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - o14 - 1 : o14) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c15, d15) => {
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

    isVerticalAlignButton(i14) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let j14 = false;
            let k14 = vp2px(i14 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((m14) => {
                let n14 = measure.measureTextSize({
                    textContent: m14.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(n14.width) > k14) {
                    j14 = true;
                }
            });
            return j14;
        }
        return false;
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

function __Button__setButtonProperties(f14, g14) {
    Button.onClick(() => {
        if (f14.action) {
            f14.action();
        }
        g14?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(f14.buttonStyle ?? ALERT_BUTTON_STYLE);
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

function getNumberByResourceId(y13, z13, a14) {
    try {
        let e14 = resourceManager.getSystemResourceManager().getNumber(y13);
        if (e14 > 0 || a14) {
            return e14;
        } else {
            return z13;
        }
    } catch (b14) {
        let c14 = b14.code;
        let d14 = b14.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${c14}, message: ${d14}`);
        return z13;
    }
}

function getEnumNumberByResourceId(o11, p11) {
    try {
        let x13 = getContext().resourceManager.getNumber(o11);
        if (x13 > 0) {
            return x13;
        } else {
            return p11;
        }
    } catch (a13) {
        let v13 = a13.code;
        let w13 = a13.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${v13}, message: ${w13}`);
        return p11;
    }
}

function getTextAlign(c11, d11, e11) {
    let f11 = measure.measureTextSize({
        textContent: d11,
        fontSize: e11,
        constraintWidth: c11,
    });
    let g11 = measure.measureTextSize({
        textContent: d11,
        fontSize: e11,
    });
    if (getTextHeight(f11) <= getTextHeight(g11)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}

function getTextHeight(x10) {
    if (x10 && x10.height !== null && x10.height !== undefined) {
        return Number(x10.height);
    }
    return 0;
}

function resolveKeyEvent(n10, o10) {
    if (n10.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (n10.keyCode === KEYCODE_UP) {
        o10.scrollPage({ next: false });
        n10.stopPropagation();
    } else if (n10.keyCode === KEYCODE_DOWN) {
        if (o10.isAtEnd()) {
            return;
        } else {
            o10.scrollPage({ next: true });
            n10.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(q9, r9, s9, t9 = -1, u9 = undefined, y9) {
        super(q9, s9, t9, y9);
        if (typeof u9 === 'function') {
            this.paramsGenerator_ = u9;
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
        this.setInitiallyProvidedValue(r9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p9) {
        if (p9.controller !== undefined) {
            this.controller = p9.controller;
        }
        if (p9.content !== undefined) {
            this.content = p9.content;
        }
        if (p9.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = p9.fontColorWithTheme;
        }
        if (p9.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = p9.loadingProgressIconColorWithTheme;
        }
        if (p9.theme !== undefined) {
            this.theme = p9.theme;
        }
        if (p9.themeColorMode !== undefined) {
            this.themeColorMode = p9.themeColorMode;
        }
        if (p9.fontSizeScale !== undefined) {
            this.fontSizeScale = p9.fontSizeScale;
        }
        if (p9.minContentHeight !== undefined) {
            this.minContentHeight = p9.minContentHeight;
        }
    }

    updateStateVars(o9) {
    }

    purgeVariableDependenciesOnElmtId(n9) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(n9);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(n9);
        this.__fontSizeScale.purgeDependencyOnElmtId(n9);
        this.__minContentHeight.purgeDependencyOnElmtId(n9);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(m9) {
        this.controller = m9;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(k9) {
        this.__fontColorWithTheme.set(k9);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(j9) {
        this.__loadingProgressIconColorWithTheme.set(j9);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(g8) {
        this.__fontSizeScale.set(g8);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(f8) {
        this.__minContentHeight.set(f8);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((q7, w7) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((g7, p7) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((s6, t6) => {
                if (t6) {
                    let u6 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, s6, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1585, col: 7 });
                    ViewPU.create(u6);
                    let a = () => {
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
                    u6.paramsGenerator_ = a;
                } else {
                    this.updateStateVarsOfChildByElmtId(s6, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    contentBuilder(s3 = null) {
        this.observeComponentCreation2((a6, f6) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((q5, z5) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((h4, m5) => {
            Text.create(this.content);
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
            Text.maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES);
            Text.focusable(true);
            Text.defaultFocus(true);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((f4, g4) => {
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

export class PopupDialog extends ViewPU {
    constructor(t2, u2, g3, k3 = -1, q3 = undefined, r3) {
        super(t2, g3, k3, r3);
        if (typeof q3 === 'function') {
            this.paramsGenerator_ = q3;
        }
        this.__show = new SynchedPropertySimpleTwoWayPU(u2.show, this, 'show');
        this.__popup = new SynchedPropertyObjectOneWayPU(u2.popup, this, 'popup');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popup.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(u2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s2) {
        if (s2.targetBuilder !== undefined) {
            this.targetBuilder = s2.targetBuilder;
        }
        if (s2.dialogWidth !== undefined) {
            this.dialogWidth = s2.dialogWidth;
        }
    }

    updateStateVars(r2) {
        this.__popup.reset(r2.popup);
    }

    purgeVariableDependenciesOnElmtId(a2) {
        this.__show.purgeDependencyOnElmtId(a2);
        this.__popup.purgeDependencyOnElmtId(a2);
        this.__dialogWidth.purgeDependencyOnElmtId(a2);
    }

    aboutToBeDeleted() {
        this.__show.aboutToBeDeleted();
        this.__popup.aboutToBeDeleted();
        this.__dialogWidth.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get show() {
        return this.__show.get();
    }

    set show(z1) {
        this.__show.set(z1);
    }

    get popup() {
        return this.__popup.get();
    }

    set popup(y1) {
        this.__popup.set(y1);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(x1) {
        this.__dialogWidth.set(x1);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((o, p) => {
            Column.create();
            Column.onClick(() => {
                let q1 = display.getDefaultDisplaySync();
                let w1 = px2vp(q1.width);
                if (w1 - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
                    this.popup.width = this.popup?.width ?? MAX_DIALOG_WIDTH;
                } else {
                    this.popup.width = this.dialogWidth;
                }
                this.show = !this.show;
            });
            Column.bindPopup(this.show, {
                builder: this.popup?.builder,
                placement: this.popup?.placement ?? Placement.Bottom,
                popupColor: this.popup?.popupColor,
                enableArrow: this.popup?.enableArrow ?? true,
                autoCancel: this.popup?.autoCancel,
                onStateChange: this.popup?.onStateChange ?? ((o1) => {
                    if (!o1.isVisible) {
                        this.show = false;
                    }
                }),
                arrowOffset: this.popup?.arrowOffset,
                showInSubWindow: this.popup?.showInSubWindow,
                mask: this.popup?.mask,
                targetSpace: this.popup?.targetSpace,
                offset: this.popup?.offset,
                width: this.popup?.width,
                arrowPointPosition: this.popup?.arrowPointPosition,
                arrowWidth: this.popup?.arrowWidth,
                arrowHeight: this.popup?.arrowHeight,
                radius: this.popup?.radius ?? {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.corner_radius_level16'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                shadow: this.popup?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
                backgroundBlurStyle: this.popup?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
                focusable: this.popup?.focusable,
                transition: this.popup?.transition,
                onWillDismiss: this.popup?.onWillDismiss
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

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog, PopupDialog };