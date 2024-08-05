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

class CustomThemeImpl {
    constructor(c31) {
        this.colors = c31;
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
const BODY_S = getNumberByResourceId(125830972, 12);
const TITLE_S = getNumberByResourceId(125830966, 20);
const SUBTITLE_S = getNumberByResourceId(125830969, 14);
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
const DIALOG_DIVIDER_SHOW = getNumberByResourceId(125831202, 1);
const ALERT_BUTTON_STYLE = getNumberByResourceId(125831085, 2);
const ALERT_TITLE_ALIGNMENT = getEnumNumberByResourceId(125831126, 1);

export class TipsDialog extends ViewPU {
    constructor(u30, v30, w30, x30 = -1, y30 = undefined, z30) {
        super(u30, w30, x30, z30);
        if (typeof y30 === 'function') {
            this.paramsGenerator_ = y30;
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
        this.updateTextAlign = (b31) => {
            if (this.content) {
                this.textAlignment = getTextAlign(b31, this.content, `${BODY_L}fp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(v30);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t30) {
        if (t30.controller !== undefined) {
            this.controller = t30.controller;
        }
        if (t30.imageRes !== undefined) {
            this.imageRes = t30.imageRes;
        }
        if (t30.imageSize !== undefined) {
            this.imageSize = t30.imageSize;
        }
        if (t30.title !== undefined) {
            this.title = t30.title;
        }
        if (t30.content !== undefined) {
            this.content = t30.content;
        }
        if (t30.checkAction !== undefined) {
            this.checkAction = t30.checkAction;
        }
        if (t30.onCheckedChange !== undefined) {
            this.onCheckedChange = t30.onCheckedChange;
        }
        if (t30.checkTips !== undefined) {
            this.checkTips = t30.checkTips;
        }
        if (t30.isChecked !== undefined) {
            this.isChecked = t30.isChecked;
        }
        if (t30.primaryButton !== undefined) {
            this.primaryButton = t30.primaryButton;
        }
        if (t30.secondaryButton !== undefined) {
            this.secondaryButton = t30.secondaryButton;
        }
        if (t30.buttons !== undefined) {
            this.buttons = t30.buttons;
        }
        if (t30.textAlignment !== undefined) {
            this.textAlignment = t30.textAlignment;
        }
        if (t30.marginOffset !== undefined) {
            this.marginOffset = t30.marginOffset;
        }
        if (t30.contentScroller !== undefined) {
            this.contentScroller = t30.contentScroller;
        }
        if (t30.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = t30.fontColorWithTheme;
        }
        if (t30.theme !== undefined) {
            this.theme = t30.theme;
        }
        if (t30.themeColorMode !== undefined) {
            this.themeColorMode = t30.themeColorMode;
        }
        if (t30.fontSizeScale !== undefined) {
            this.fontSizeScale = t30.fontSizeScale;
        }
        if (t30.minContentHeight !== undefined) {
            this.minContentHeight = t30.minContentHeight;
        }
        if (t30.updateTextAlign !== undefined) {
            this.updateTextAlign = t30.updateTextAlign;
        }
        if (t30.imageIndex !== undefined) {
            this.imageIndex = t30.imageIndex;
        }
        if (t30.textIndex !== undefined) {
            this.textIndex = t30.textIndex;
        }
        if (t30.checkBoxIndex !== undefined) {
            this.checkBoxIndex = t30.checkBoxIndex;
        }
    }

    updateStateVars(s30) {
    }

    purgeVariableDependenciesOnElmtId(r30) {
        this.__imageSize.purgeDependencyOnElmtId(r30);
        this.__isChecked.purgeDependencyOnElmtId(r30);
        this.__textAlignment.purgeDependencyOnElmtId(r30);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(r30);
        this.__fontSizeScale.purgeDependencyOnElmtId(r30);
        this.__minContentHeight.purgeDependencyOnElmtId(r30);
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

    setController(q30) {
        this.controller = q30;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(p30) {
        this.__imageSize.set(p30);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(o30) {
        this.__isChecked.set(o30);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(n30) {
        this.__textAlignment.set(n30);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m30) {
        this.__fontColorWithTheme.set(m30);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(l30) {
        this.__fontSizeScale.set(l30);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(k30) {
        this.__minContentHeight.set(k30);
    }

    initialRender() {
        this.observeComponentCreation2((i30, j30) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((c30, d30) => {
                if (d30) {
                    let e30 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, c30, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 118, col: 5 });
                    ViewPU.create(e30);
                    let f30 = () => {
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
                    e30.paramsGenerator_ = f30;
                } else {
                    this.updateStateVarsOfChildByElmtId(c30, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(g28 = null) {
        {
            this.observeComponentCreation2((i28, j28) => {
                if (j28) {
                    let k28 = new TipsDialogContentLayout(g28 ? g28 : this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((i29, j29) => {
                                ForEach.create();
                                const k29 = m29 => {
                                    const n29 = m29;
                                    this.observeComponentCreation2((p29, q29) => {
                                        If.create();
                                        if (n29 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)(g28 ? g28 : this);
                                            });
                                        } else if (n29 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((x29, y29) => {
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
                                                this.textPart.bind(this)(g28 ? g28 : this);
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.observeComponentCreation2((t29, u29) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.checkBoxPart.bind(this)(g28 ? g28 : this);
                                                WithTheme.pop();
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(i29, [this.imageIndex, this.textIndex, this.checkBoxIndex],
                                    k29);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, i28, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 133, col: 5 });
                    ViewPU.create(k28);
                    let l28 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((p28, q28) => {
                                    ForEach.create();
                                    const r28 = t28 => {
                                        const u28 = t28;
                                        this.observeComponentCreation2((w28, x28) => {
                                            If.create();
                                            if (u28 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)(g28 ? g28 : this);
                                                });
                                            } else if (u28 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((e29, f29) => {
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
                                                    this.textPart.bind(this)(g28 ? g28 : this);
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.observeComponentCreation2((a29, b29) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.checkBoxPart.bind(this)(g28 ? g28 : this);
                                                    WithTheme.pop();
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(p28,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], r28);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    k28.paramsGenerator_ = l28;
                } else {
                    this.updateStateVarsOfChildByElmtId(i28, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(o27 = null) {
        this.observeComponentCreation2((d28, e28) => {
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
        this.observeComponentCreation2((r27, s27) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z27, a28) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((c28) => {
                            this.isChecked = c28;
                            if (this.checkAction) {
                                this.checkAction(c28);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(c28);
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
                    this.observeComponentCreation2((x27, y27) => {
                        Text.create(this.checkTips);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_L'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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

    imagePart(h27 = null) {
        this.observeComponentCreation2((m27, n27) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((k27, l27) => {
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

    textPart(c26 = null) {
        this.observeComponentCreation2((f27, g27) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((d27, e27) => {
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
        this.observeComponentCreation2((t26, u26) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b27, c27) => {
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
                    this.observeComponentCreation2((z26, a27) => {
                        Text.create(this.title);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Title_S'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
        this.observeComponentCreation2((h26, i26) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r26, s26) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((n26, o26) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((q26) => {
                            if (q26) {
                                resolveKeyEvent(q26, this.contentScroller);
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
        this.updateDirtyElements();
    }
}

class TipsDialogContentLayout extends ViewPU {
    constructor(u25, v25, w25, x25 = -1, y25 = undefined, z25) {
        super(u25, w25, x25, z25);
        if (typeof y25 === 'function') {
            this.paramsGenerator_ = y25;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (b26) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(v25.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(v25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t25) {
        if (t25.title !== undefined) {
            this.title = t25.title;
        }
        if (t25.content !== undefined) {
            this.content = t25.content;
        }
        if (t25.checkTips !== undefined) {
            this.checkTips = t25.checkTips;
        }
        if (t25.updateTextAlign !== undefined) {
            this.updateTextAlign = t25.updateTextAlign;
        }
        if (t25.dialogBuilder !== undefined) {
            this.dialogBuilder = t25.dialogBuilder;
        }
        if (t25.imageIndex !== undefined) {
            this.imageIndex = t25.imageIndex;
        }
        if (t25.textIndex !== undefined) {
            this.textIndex = t25.textIndex;
        }
        if (t25.checkBoxIndex !== undefined) {
            this.checkBoxIndex = t25.checkBoxIndex;
        }
        if (t25.childrenSize !== undefined) {
            this.childrenSize = t25.childrenSize;
        }
    }

    updateStateVars(s25) {
    }

    purgeVariableDependenciesOnElmtId(r25) {
        this.__minContentHeight.purgeDependencyOnElmtId(r25);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(q25 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(p25) {
        this.__minContentHeight.set(p25);
    }

    onPlaceChildren(i25, j25, k25) {
        let l25 = 0;
        let m25 = 0;
        for (let n25 = 0; n25 < j25.length; n25++) {
            let o25 = j25[n25];
            o25.layout({ x: l25, y: m25 });
            m25 += o25.measureResult.height;
        }
    }

    onMeasureSize(q24, r24, s24) {
        let t24 = { width: Number(s24.maxWidth), height: 0 };
        if (r24.length < this.childrenSize) {
            return t24;
        }
        let u24 = 0;
        let v24 = 0;
        if (this.checkTips !== null) {
            let f25 = r24[this.checkBoxIndex];
            let g25 = {
                maxWidth: s24.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: s24.maxHeight
            };
            let h25 = f25.measure(g25);
            v24 = h25.height;
            u24 += v24;
        }
        let w24 = r24[this.imageIndex];
        let x24 = 0;
        if (this.title !== null || this.content !== null) {
            x24 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let y24 = Number(s24.maxHeight) - v24 - x24;
        let z24 = {
            maxWidth: s24.maxWidth,
            maxHeight: y24
        };
        let a25 = w24.measure(z24);
        u24 += a25.height;
        if (this.title !== null || this.content !== null) {
            let b25 = r24[this.textIndex];
            this.updateTextAlign(t24.width);
            let c25 = Number(s24.maxHeight) - a25.height - v24;
            let d25 = {
                maxWidth: s24.maxWidth,
                maxHeight: Math.max(c25, TEXT_MIN_HEIGHT)
            };
            let e25 = b25.measure(d25);
            u24 += e25.height;
        }
        t24.height = u24;
        this.minContentHeight = Math.max(v24 + a25.height + x24, MIN_CONTENT_HEIGHT);
        return t24;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(k24, l24, m24, n24 = -1, o24 = undefined, p24) {
        super(k24, m24, n24, p24);
        if (typeof o24 === 'function') {
            this.paramsGenerator_ = o24;
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
        this.setInitiallyProvidedValue(l24);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j24) {
        if (j24.controller !== undefined) {
            this.controller = j24.controller;
        }
        if (j24.title !== undefined) {
            this.title = j24.title;
        }
        if (j24.content !== undefined) {
            this.content = j24.content;
        }
        if (j24.confirm !== undefined) {
            this.confirm = j24.confirm;
        }
        if (j24.radioContent !== undefined) {
            this.radioContent = j24.radioContent;
        }
        if (j24.buttons !== undefined) {
            this.buttons = j24.buttons;
        }
        if (j24.contentPadding !== undefined) {
            this.contentPadding = j24.contentPadding;
        }
        if (j24.isFocus !== undefined) {
            this.isFocus = j24.isFocus;
        }
        if (j24.currentFocusIndex !== undefined) {
            this.currentFocusIndex = j24.currentFocusIndex;
        }
        if (j24.radioHeight !== undefined) {
            this.radioHeight = j24.radioHeight;
        }
        if (j24.itemHeight !== undefined) {
            this.itemHeight = j24.itemHeight;
        }
        if (j24.selectedIndex !== undefined) {
            this.selectedIndex = j24.selectedIndex;
        }
        if (j24.contentBuilder !== undefined) {
            this.contentBuilder = j24.contentBuilder;
        }
        if (j24.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = j24.fontColorWithTheme;
        }
        if (j24.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = j24.dividerColorWithTheme;
        }
        if (j24.theme !== undefined) {
            this.theme = j24.theme;
        }
        if (j24.themeColorMode !== undefined) {
            this.themeColorMode = j24.themeColorMode;
        }
        if (j24.contentScroller !== undefined) {
            this.contentScroller = j24.contentScroller;
        }
        if (j24.fontSizeScale !== undefined) {
            this.fontSizeScale = j24.fontSizeScale;
        }
        if (j24.minContentHeight !== undefined) {
            this.minContentHeight = j24.minContentHeight;
        }
    }

    updateStateVars(i24) {
    }

    purgeVariableDependenciesOnElmtId(h24) {
        this.__selectedIndex.purgeDependencyOnElmtId(h24);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(h24);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(h24);
        this.__fontSizeScale.purgeDependencyOnElmtId(h24);
        this.__minContentHeight.purgeDependencyOnElmtId(h24);
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

    setController(g24) {
        this.controller = g24;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(f24) {
        this.__selectedIndex.set(f24);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(e24) {
        this.__fontColorWithTheme.set(e24);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(d24) {
        this.__dividerColorWithTheme.set(d24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(c24) {
        this.__fontSizeScale.set(c24);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(b24) {
        this.__minContentHeight.set(b24);
    }

    buildContent(c21 = null) {
        this.observeComponentCreation2((v23, w23) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((y23, z23) => {
                let a24 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (z23 > 0) {
                            this.contentScroller.scrollBy(0, a24);
                        } else if (z23 < 0) {
                            this.contentScroller.scrollBy(0, 0 - a24);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((t23, u23) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((j23, k23) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r23, s23) => {
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
                    this.observeComponentCreation2((p23, q23) => {
                        Text.create(this.content);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
        this.observeComponentCreation2((g23, h23) => {
            List.create();
            List.width('100%');
            List.clip(false);
            List.onFocus(() => {
                if (!this.contentScroller.isAtEnd()) {
                    this.contentScroller.scrollEdge(Edge.Top);
                    focusControl.requestFocus(String(FIRST_ITEM_INDEX));
                }
            });
            List.defaultFocus(this.buttons?.length == 0 ? true : false);
        }, List);
        this.observeComponentCreation2((i21, j21) => {
            ForEach.create();
            const k21 = (m21, n21) => {
                const o21 = m21;
                {
                    const p21 = (e23, f23) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e23);
                        q21(e23, f23);
                        if (!f23) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const q21 = (z22, a23) => {
                        ListItem.create(r21, true);
                        ListItem.onSizeChange((c23, d23) => {
                            this.itemHeight = Number(d23.height);
                        });
                    };
                    const r21 = (v21, w21) => {
                        p21(v21, w21);
                        this.observeComponentCreation2((x22, y22) => {
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
                        this.observeComponentCreation2((u22, v22) => {
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
                                this.selectedIndex = n21;
                                o21.action && o21.action();
                                this.controller?.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((s22, t22) => {
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
                        this.observeComponentCreation2((q22, r22) => {
                            Text.create(o21.title);
                            Text.fontSize({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.Body_L'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((k22, l22) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === n21);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(n21));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = n21;
                                if (n21 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (n21 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((o22, p22) => {
                                this.radioHeight = Number(p22.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((d22, e22) => {
                            If.create();
                            if (n21 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((i22, j22) => {
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
                    this.observeComponentCreation2(q21, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(i21, this.radioContent, k21, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((a21, b21) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((u20, v20) => {
                if (v20) {
                    let w20 = new CustomDialogContentComponent(this, {
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
                    }, undefined, u20, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 505, col: 5 });
                    ViewPU.create(w20);
                    let x20 = () => {
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
                    w20.paramsGenerator_ = x20;
                } else {
                    this.updateStateVarsOfChildByElmtId(u20, {});
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
    constructor(k20, l20, m20, n20 = -1, o20 = undefined, p20) {
        super(k20, m20, n20, p20);
        if (typeof o20 === 'function') {
            this.paramsGenerator_ = o20;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(l20.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (r20) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(l20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j20) {
        if (j20.textIndex !== undefined) {
            this.textIndex = j20.textIndex;
        }
        if (j20.checkboxIndex !== undefined) {
            this.checkboxIndex = j20.checkboxIndex;
        }
        if (j20.updateTextAlign !== undefined) {
            this.updateTextAlign = j20.updateTextAlign;
        }
        if (j20.dialogBuilder !== undefined) {
            this.dialogBuilder = j20.dialogBuilder;
        }
    }

    updateStateVars(i20) {
    }

    purgeVariableDependenciesOnElmtId(h20) {
        this.__minContentHeight.purgeDependencyOnElmtId(h20);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(g20) {
        this.__minContentHeight.set(g20);
    }

    doNothingBuilder(f20 = null) {
    }

    onPlaceChildren(y19, z19, a20) {
        let b20 = 0;
        let c20 = 0;
        for (let d20 = 0; d20 < z19.length; d20++) {
            let e20 = z19[d20];
            e20.layout({ x: b20, y: c20 });
            c20 += e20.measureResult.height;
        }
    }

    onMeasureSize(m19, n19, o19) {
        let p19 = { width: Number(o19.maxWidth), height: 0 };
        let q19 = 2;
        if (n19.length < q19) {
            return p19;
        }
        this.updateTextAlign(p19.width);
        let r19 = 0;
        let s19 = n19[this.checkboxIndex];
        let t19 = {
            maxWidth: o19.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: o19.maxHeight
        };
        let u19 = s19.measure(t19);
        r19 += u19.height;
        let v19 = n19[this.textIndex];
        let w19 = {
            maxWidth: o19.maxWidth,
            maxHeight: Number(o19.maxHeight) - r19
        };
        let x19 = v19.measure(w19);
        r19 += x19.height;
        p19.height = r19;
        this.minContentHeight = Math.max(u19.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return p19;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(e19, f19, g19, h19 = -1, i19 = undefined, j19) {
        super(e19, g19, h19, j19);
        if (typeof i19 === 'function') {
            this.paramsGenerator_ = i19;
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
        this.updateTextAlign = (l19) => {
            if (this.content) {
                this.textAlign = getTextAlign(l19, this.content, `${BODY_L}fp`);
            }
        };
        this.setInitiallyProvidedValue(f19);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d19) {
        if (d19.controller !== undefined) {
            this.controller = d19.controller;
        }
        if (d19.title !== undefined) {
            this.title = d19.title;
        }
        if (d19.content !== undefined) {
            this.content = d19.content;
        }
        if (d19.checkTips !== undefined) {
            this.checkTips = d19.checkTips;
        }
        if (d19.isChecked !== undefined) {
            this.isChecked = d19.isChecked;
        }
        if (d19.primaryButton !== undefined) {
            this.primaryButton = d19.primaryButton;
        }
        if (d19.secondaryButton !== undefined) {
            this.secondaryButton = d19.secondaryButton;
        }
        if (d19.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = d19.fontColorWithTheme;
        }
        if (d19.theme !== undefined) {
            this.theme = d19.theme;
        }
        if (d19.themeColorMode !== undefined) {
            this.themeColorMode = d19.themeColorMode;
        }
        if (d19.onCheckedChange !== undefined) {
            this.onCheckedChange = d19.onCheckedChange;
        }
        if (d19.contentScroller !== undefined) {
            this.contentScroller = d19.contentScroller;
        }
        if (d19.buttons !== undefined) {
            this.buttons = d19.buttons;
        }
        if (d19.textAlign !== undefined) {
            this.textAlign = d19.textAlign;
        }
        if (d19.marginOffset !== undefined) {
            this.marginOffset = d19.marginOffset;
        }
        if (d19.fontSizeScale !== undefined) {
            this.fontSizeScale = d19.fontSizeScale;
        }
        if (d19.minContentHeight !== undefined) {
            this.minContentHeight = d19.minContentHeight;
        }
        if (d19.textIndex !== undefined) {
            this.textIndex = d19.textIndex;
        }
        if (d19.checkboxIndex !== undefined) {
            this.checkboxIndex = d19.checkboxIndex;
        }
        if (d19.updateTextAlign !== undefined) {
            this.updateTextAlign = d19.updateTextAlign;
        }
    }

    updateStateVars(c19) {
    }

    purgeVariableDependenciesOnElmtId(b19) {
        this.__isChecked.purgeDependencyOnElmtId(b19);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(b19);
        this.__textAlign.purgeDependencyOnElmtId(b19);
        this.__fontSizeScale.purgeDependencyOnElmtId(b19);
        this.__minContentHeight.purgeDependencyOnElmtId(b19);
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

    setController(a19) {
        this.controller = a19;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(z18) {
        this.__isChecked.set(z18);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(y18) {
        this.__fontColorWithTheme.set(y18);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(x18) {
        this.__textAlign.set(x18);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(w18) {
        this.__fontSizeScale.set(w18);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(v18) {
        this.__minContentHeight.set(v18);
    }

    textBuilder(g18 = null) {
        this.observeComponentCreation2((t18, u18) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((r18, s18) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((p18, q18) => {
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
        this.observeComponentCreation2((l18, m18) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(this.textAlign);
            Text.onKeyEvent((o18) => {
                if (o18) {
                    resolveKeyEvent(o18, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(t17 = null) {
        this.observeComponentCreation2((d18, e18) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((z17, a18) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((c18) => {
                this.isChecked = c18;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.accessibilityLevel('yes');
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((x17, y17) => {
            Text.create(this.checkTips);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_M'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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

    buildContent(f16 = null) {
        {
            this.observeComponentCreation2((h16, i16) => {
                if (i16) {
                    let j16 = new ConfirmDialogContentLayout(f16 ? f16 : this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((e17, f17) => {
                                ForEach.create();
                                const g17 = i17 => {
                                    const j17 = i17;
                                    this.observeComponentCreation2((l17, m17) => {
                                        If.create();
                                        if (j17 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.textBuilder.bind(this)(f16 ? f16 : this);
                                            });
                                        } else if (j17 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((q17, r17) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.checkBoxBuilder.bind(this)(f16 ? f16 : this);
                                                WithTheme.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(e17, [this.textIndex, this.checkboxIndex], g17);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, h16, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 708, col: 5 });
                    ViewPU.create(j16);
                    let k16 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((o16, p16) => {
                                    ForEach.create();
                                    const q16 = s16 => {
                                        const t16 = s16;
                                        this.observeComponentCreation2((v16, w16) => {
                                            If.create();
                                            if (t16 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.textBuilder.bind(this)(f16 ? f16 : this);
                                                });
                                            } else if (t16 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((a17, b17) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.checkBoxBuilder.bind(this)(f16 ? f16 : this);
                                                    WithTheme.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(o16, [this.textIndex, this.checkboxIndex], q16);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    j16.paramsGenerator_ = k16;
                } else {
                    this.updateStateVarsOfChildByElmtId(h16, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        this.observeComponentCreation2((d16, e16) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((x15, y15) => {
                if (y15) {
                    let z15 = new CustomDialogContentComponent(this, {
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
                    }, undefined, x15, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 722, col: 5 });
                    ViewPU.create(z15);
                    let a16 = () => {
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
                    z15.paramsGenerator_ = a16;
                } else {
                    this.updateStateVarsOfChildByElmtId(x15, {});
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
        this.updateDirtyElements();
    }
}

export class AlertDialog extends ViewPU {
    constructor(p15, q15, r15, s15 = -1, t15 = undefined, u15) {
        super(p15, r15, s15, u15);
        if (typeof t15 === 'function') {
            this.paramsGenerator_ = t15;
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
        this.setInitiallyProvidedValue(q15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o15) {
        if (o15.controller !== undefined) {
            this.controller = o15.controller;
        }
        if (o15.primaryTitle !== undefined) {
            this.primaryTitle = o15.primaryTitle;
        }
        if (o15.secondaryTitle !== undefined) {
            this.secondaryTitle = o15.secondaryTitle;
        }
        if (o15.content !== undefined) {
            this.content = o15.content;
        }
        if (o15.primaryButton !== undefined) {
            this.primaryButton = o15.primaryButton;
        }
        if (o15.secondaryButton !== undefined) {
            this.secondaryButton = o15.secondaryButton;
        }
        if (o15.buttons !== undefined) {
            this.buttons = o15.buttons;
        }
        if (o15.textAlign !== undefined) {
            this.textAlign = o15.textAlign;
        }
        if (o15.contentScroller !== undefined) {
            this.contentScroller = o15.contentScroller;
        }
        if (o15.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = o15.fontColorWithTheme;
        }
        if (o15.theme !== undefined) {
            this.theme = o15.theme;
        }
        if (o15.themeColorMode !== undefined) {
            this.themeColorMode = o15.themeColorMode;
        }
        if (o15.fontSizeScale !== undefined) {
            this.fontSizeScale = o15.fontSizeScale;
        }
        if (o15.minContentHeight !== undefined) {
            this.minContentHeight = o15.minContentHeight;
        }
    }

    updateStateVars(n15) {
    }

    purgeVariableDependenciesOnElmtId(m15) {
        this.__textAlign.purgeDependencyOnElmtId(m15);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(m15);
        this.__fontSizeScale.purgeDependencyOnElmtId(m15);
        this.__minContentHeight.purgeDependencyOnElmtId(m15);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(l15) {
        this.controller = l15;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(k15) {
        this.__textAlign.set(k15);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(j15) {
        this.__fontColorWithTheme.set(j15);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(i15) {
        this.__fontSizeScale.set(i15);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(h15) {
        this.__minContentHeight.set(h15);
    }

    initialRender() {
        this.observeComponentCreation2((f15, g15) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((z14, a15) => {
                if (a15) {
                    let b15 = new CustomDialogContentComponent(this, {
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
                    }, undefined, z14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 780, col: 5 });
                    ViewPU.create(b15);
                    let c15 = () => {
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
                    b15.paramsGenerator_ = c15;
                } else {
                    this.updateStateVarsOfChildByElmtId(z14, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(i14 = null) {
        this.observeComponentCreation2((v14, w14) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((t14, u14) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((m14, n14) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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
            Text.onAreaChange((r14, s14) => {
                this.updateTextAlign(Number(s14.width));
            });
            Text.onKeyEvent((q14) => {
                if (q14) {
                    resolveKeyEvent(q14, this.contentScroller);
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

    updateTextAlign(h14) {
        this.textAlign = getTextAlign(h14, this.content, {
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
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
        this.updateDirtyElements();
    }
}

export class CustomContentDialog extends ViewPU {
    constructor(b14, c14, d14, e14 = -1, f14 = undefined, g14) {
        super(b14, d14, e14, g14);
        if (typeof f14 === 'function') {
            this.paramsGenerator_ = f14;
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
        this.setInitiallyProvidedValue(c14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a14) {
        if (a14.controller !== undefined) {
            this.controller = a14.controller;
        }
        if (a14.primaryTitle !== undefined) {
            this.primaryTitle = a14.primaryTitle;
        }
        if (a14.secondaryTitle !== undefined) {
            this.secondaryTitle = a14.secondaryTitle;
        }
        if (a14.contentBuilder !== undefined) {
            this.contentBuilder = a14.contentBuilder;
        }
        if (a14.contentAreaPadding !== undefined) {
            this.contentAreaPadding = a14.contentAreaPadding;
        }
        if (a14.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = a14.localizedContentAreaPadding;
        }
        if (a14.buttons !== undefined) {
            this.buttons = a14.buttons;
        }
        if (a14.theme !== undefined) {
            this.theme = a14.theme;
        }
        if (a14.themeColorMode !== undefined) {
            this.themeColorMode = a14.themeColorMode;
        }
        if (a14.fontSizeScale !== undefined) {
            this.fontSizeScale = a14.fontSizeScale;
        }
        if (a14.minContentHeight !== undefined) {
            this.minContentHeight = a14.minContentHeight;
        }
    }

    updateStateVars(z13) {
    }

    purgeVariableDependenciesOnElmtId(y13) {
        this.__fontSizeScale.purgeDependencyOnElmtId(y13);
        this.__minContentHeight.purgeDependencyOnElmtId(y13);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(x13) {
        this.controller = x13;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(w13) {
        this.__fontSizeScale.set(w13);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(v13) {
        this.__minContentHeight.set(v13);
    }

    initialRender() {
        this.observeComponentCreation2((t13, u13) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((n13, o13) => {
                if (o13) {
                    let p13 = new CustomDialogContentComponent(this, {
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
                    }, undefined, n13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 873, col: 5 });
                    ViewPU.create(p13);
                    let q13 = () => {
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
                    p13.paramsGenerator_ = q13;
                } else {
                    this.updateStateVarsOfChildByElmtId(n13, {});
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
    constructor(k13) {
        super(k13);
        this.arg_ = k13;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(e13, f13, g13, h13 = -1, i13 = undefined, j13) {
        super(e13, g13, h13, j13);
        if (typeof i13 === 'function') {
            this.paramsGenerator_ = i13;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(f13.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(f13.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(f13.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(f13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d13) {
        if (d13.dialogBuilder !== undefined) {
            this.dialogBuilder = d13.dialogBuilder;
        }
        if (d13.titleIndex !== undefined) {
            this.titleIndex = d13.titleIndex;
        }
        if (d13.contentIndex !== undefined) {
            this.contentIndex = d13.contentIndex;
        }
        if (d13.buttonIndex !== undefined) {
            this.buttonIndex = d13.buttonIndex;
        }
    }

    updateStateVars(c13) {
    }

    purgeVariableDependenciesOnElmtId(b13) {
        this.__titleHeight.purgeDependencyOnElmtId(b13);
        this.__buttonHeight.purgeDependencyOnElmtId(b13);
        this.__titleMinHeight.purgeDependencyOnElmtId(b13);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(a13 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(z12) {
        this.__titleHeight.set(z12);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(y12) {
        this.__buttonHeight.set(y12);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(x12) {
        this.__titleMinHeight.set(x12);
    }

    onPlaceChildren(q12, r12, s12) {
        let t12 = 0;
        let u12 = 0;
        for (let v12 = 0; v12 < r12.length; v12++) {
            let w12 = r12[v12];
            w12.layout({ x: t12, y: u12 });
            u12 += w12.measureResult.height;
        }
    }

    onMeasureSize(c12, d12, e12) {
        let f12 = { width: Number(e12.maxWidth), height: 0 };
        let g12 = 3;
        if (d12.length < g12) {
            return f12;
        }
        let h12 = 0;
        let i12 = d12[this.titleIndex];
        let j12 = {
            maxWidth: e12.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: e12.maxHeight
        };
        let k12 = i12.measure(j12);
        this.titleHeight = k12.height;
        h12 += this.titleHeight;
        let l12 = d12[this.buttonIndex];
        let m12 = l12.measure(e12);
        this.buttonHeight = m12.height;
        h12 += this.buttonHeight;
        let n12 = d12[this.contentIndex];
        let o12 = {
            maxWidth: e12.maxWidth,
            maxHeight: Number(e12.maxHeight) - h12
        };
        let p12 = n12.measure(o12);
        h12 += p12.height;
        f12.height = h12;
        return f12;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(w11, x11, y11, z11 = -1, a12 = undefined, b12) {
        super(w11, y11, z11, b12);
        if (typeof a12 === 'function') {
            this.paramsGenerator_ = a12;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(x11.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(x11.fontSizeScale, this, 'fontSizeScale');
        this.__customStyle = new ObservedPropertySimplePU(undefined, this, 'customStyle');
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.__primaryTitleMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Title_S'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTitleMaxFontSize');
        this.__primaryTitleMinFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTitleMinFontSize');
        this.__secondaryTitleMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Subtitle_S'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTitleMaxFontSize');
        this.__secondaryTitleMinFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_S'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTitleMinFontSize');
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
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(x11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v11) {
        if (v11.controller !== undefined) {
            this.controller = v11.controller;
        }
        if (v11.primaryTitle !== undefined) {
            this.primaryTitle = v11.primaryTitle;
        }
        if (v11.secondaryTitle !== undefined) {
            this.secondaryTitle = v11.secondaryTitle;
        }
        if (v11.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = v11.localizedContentAreaPadding;
        }
        if (v11.contentBuilder !== undefined) {
            this.contentBuilder = v11.contentBuilder;
        }
        if (v11.buttons !== undefined) {
            this.buttons = v11.buttons;
        }
        if (v11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = v11.contentAreaPadding;
        }
        if (v11.keyIndex !== undefined) {
            this.keyIndex = v11.keyIndex;
        }
        if (v11.theme !== undefined) {
            this.theme = v11.theme;
        }
        if (v11.themeColorMode !== undefined) {
            this.themeColorMode = v11.themeColorMode;
        }
        if (v11.titleHeight !== undefined) {
            this.titleHeight = v11.titleHeight;
        }
        if (v11.buttonHeight !== undefined) {
            this.buttonHeight = v11.buttonHeight;
        }
        if (v11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = v11.contentMaxHeight;
        }
        if (v11.customStyle !== undefined) {
            this.customStyle = v11.customStyle;
        }
        if (v11.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = v11.buttonMaxFontSize;
        }
        if (v11.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = v11.buttonMinFontSize;
        }
        if (v11.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = v11.primaryTitleMaxFontSize;
        }
        if (v11.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = v11.primaryTitleMinFontSize;
        }
        if (v11.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = v11.secondaryTitleMaxFontSize;
        }
        if (v11.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = v11.secondaryTitleMinFontSize;
        }
        if (v11.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = v11.primaryTitleFontColorWithTheme;
        }
        if (v11.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = v11.secondaryTitleFontColorWithTheme;
        }
        if (v11.titleTextAlign !== undefined) {
            this.titleTextAlign = v11.titleTextAlign;
        }
        if (v11.isButtonVertical !== undefined) {
            this.isButtonVertical = v11.isButtonVertical;
        }
        if (v11.titleMinHeight !== undefined) {
            this.titleMinHeight = v11.titleMinHeight;
        }
        if (v11.titleIndex !== undefined) {
            this.titleIndex = v11.titleIndex;
        }
        if (v11.contentIndex !== undefined) {
            this.contentIndex = v11.contentIndex;
        }
        if (v11.buttonIndex !== undefined) {
            this.buttonIndex = v11.buttonIndex;
        }
    }

    updateStateVars(u11) {
    }

    purgeVariableDependenciesOnElmtId(t11) {
        this.__minContentHeight.purgeDependencyOnElmtId(t11);
        this.__titleHeight.purgeDependencyOnElmtId(t11);
        this.__buttonHeight.purgeDependencyOnElmtId(t11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(t11);
        this.__fontSizeScale.purgeDependencyOnElmtId(t11);
        this.__customStyle.purgeDependencyOnElmtId(t11);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(t11);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(t11);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(t11);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(t11);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(t11);
        this.__titleTextAlign.purgeDependencyOnElmtId(t11);
        this.__isButtonVertical.purgeDependencyOnElmtId(t11);
        this.__titleMinHeight.purgeDependencyOnElmtId(t11);
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

    set minContentHeight(s11) {
        this.__minContentHeight.set(s11);
    }

    defaultContentBuilder(r11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(q11) {
        this.__titleHeight.set(q11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(p11) {
        this.__buttonHeight.set(p11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(o11) {
        this.__contentMaxHeight.set(o11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(n11) {
        this.__fontSizeScale.set(n11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(m11) {
        this.__customStyle.set(m11);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(l11) {
        this.__buttonMaxFontSize.set(l11);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(k11) {
        this.__buttonMinFontSize.set(k11);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(j11) {
        this.__primaryTitleMaxFontSize.set(j11);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(i11) {
        this.__primaryTitleMinFontSize.set(i11);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(h11) {
        this.__secondaryTitleMaxFontSize.set(h11);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(g11) {
        this.__secondaryTitleMinFontSize.set(g11);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(f11) {
        this.__primaryTitleFontColorWithTheme.set(f11);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(e11) {
        this.__secondaryTitleFontColorWithTheme.set(e11);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(d11) {
        this.__titleTextAlign.set(d11);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(c11) {
        this.__isButtonVertical.set(c11);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(b11) {
        this.__titleMinHeight.set(b11);
    }

    initialRender() {
        this.observeComponentCreation2((z10, a11) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((x10, y10) => {
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
        this.observeComponentCreation2((v10, w10) => {
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
            this.observeComponentCreation2((r8, s8) => {
                if (s8) {
                    let t8 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((x9, y9) => {
                                ForEach.create();
                                const z9 = b10 => {
                                    const c10 = b10;
                                    this.observeComponentCreation2((e10, f10) => {
                                        If.create();
                                        if (c10 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((t10, u10) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)(this);
                                                WithTheme.pop();
                                            });
                                        } else if (c10 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((p10, q10) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((n10, o10) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.contentBuilder.bind(this)(this);
                                                WithTheme.pop();
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.observeComponentCreation2((i10, j10) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.ButtonBuilder.bind(this)(this);
                                                WithTheme.pop();
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(x9, [this.titleIndex, this.contentIndex, this.buttonIndex],
                                    z9);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, r8, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1009, col: 11 });
                    ViewPU.create(t8);
                    let u8 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((y8, z8) => {
                                    ForEach.create();
                                    const a9 = c9 => {
                                        const d9 = c9;
                                        this.observeComponentCreation2((f9, g9) => {
                                            If.create();
                                            if (d9 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((u9, v9) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)(this);
                                                    WithTheme.pop();
                                                });
                                            } else if (d9 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((q9, r9) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((o9, p9) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.contentBuilder.bind(this)(this);
                                                    WithTheme.pop();
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.observeComponentCreation2((j9, k9) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.ButtonBuilder.bind(this)(this);
                                                    WithTheme.pop();
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(y8,
                                        [this.titleIndex, this.contentIndex, this.buttonIndex], a9);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    t8.paramsGenerator_ = u8;
                } else {
                    this.updateStateVarsOfChildByElmtId(r8, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(d8, e8, f8) {
        let g8 = { width: d8.width, height: d8.height };
        let h8 = Number(f8.maxWidth);
        let i8 = Number(f8.maxHeight);
        this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(h8 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let j8 = 0;
        e8.forEach((l8) => {
            this.contentMaxHeight = '100%';
            let m8 = l8.measure(f8);
            if (i8 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                m8 = l8.measure(f8);
            }
            j8 += m8.height;
        });
        g8.height = j8;
        g8.width = h8;
        return g8;
    }

    aboutToAppear() {
        this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let c8 = this.controller;
            if (c8.arg_ && c8.arg_.customStyle && c8.arg_.customStyle === true) {
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
            this.primaryTitleMaxFontSize = TITLE_S * MAX_FONT_SCALE + 'vp';
            this.primaryTitleMinFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
            this.secondaryTitleMaxFontSize = SUBTITLE_S * MAX_FONT_SCALE + 'vp';
            this.secondaryTitleMinFontSize = BODY_S * MAX_FONT_SCALE + 'vp';
        } else {
            this.primaryTitleMaxFontSize = TITLE_S + 'fp';
            this.primaryTitleMinFontSize = BODY_L + 'fp';
            this.secondaryTitleMaxFontSize = SUBTITLE_S + 'fp';
            this.secondaryTitleMinFontSize = BODY_S + 'fp';
            this.buttonMaxFontSize = BODY_L + 'fp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
        }
    }

    updateFontScale() {
        try {
            let b8 = this.getUIContext().getHostContext();
            this.fontSizeScale = b8.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (y7) {
            let z7 = y7.code;
            let a8 = y7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${z7}, message: ${a8}`);
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

    titleBuilder(x6 = null) {
        this.observeComponentCreation2((w7, x7) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((u7, v7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((s7, t7) => {
            Text.create(this.primaryTitle);
            Text.fontWeight(FontWeight.Bold);
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTitleFontColorWithTheme));
            Text.textAlign(this.titleTextAlign);
            Text.maxFontSize(ObservedObject.GetRawObject(this.primaryTitleMaxFontSize));
            Text.minFontSize(ObservedObject.GetRawObject(this.primaryTitleMinFontSize));
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((i7, j7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q7, r7) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((o7, p7) => {
                        Divider.create();
                        Divider.margin({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.padding_level1'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Divider.color(Color.Transparent);
                    }, Divider);
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((g7, h7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((e7, f7) => {
            Text.create(this.secondaryTitle);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTitleFontColorWithTheme));
            Text.textAlign(this.titleTextAlign);
            Text.maxFontSize(ObservedObject.GetRawObject(this.secondaryTitleMaxFontSize));
            Text.minFontSize(ObservedObject.GetRawObject(this.secondaryTitleMinFontSize));
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
        let w6 = ALERT_TITLE_ALIGNMENT;
        if (w6 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (w6 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (w6 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (w6 === TextAlign.JUSTIFY) {
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

    ButtonBuilder(i6 = null) {
        this.observeComponentCreation2((u6, v6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((l6, m6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q6, r6) => {
                        If.create();
                        if (this.isButtonVertical) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.buildVerticalAlignButtons.bind(this)(i6 ? i6 : this);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.buildHorizontalAlignButtons.bind(this)(i6 ? i6 : this);
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

    buildSingleButton(n5, o5 = null) {
        this.observeComponentCreation2((q5, r5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(n5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g6, h6) => {
                        Button.createWithLabel(n5.value);
                        __Button__setButtonProperties(n5, this.controller);
                        Button.role(n5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (n5.background !== undefined && n5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((c6, d6) => {
                        Button.createWithLabel(n5.value);
                        __Button__setButtonProperties(n5, this.controller);
                        Button.backgroundColor(n5.background);
                        Button.fontColor(n5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (n5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((y5, z5) => {
                        Button.createWithLabel(n5.value);
                        __Button__setButtonProperties(n5, this.controller);
                        Button.backgroundColor(n5.background);
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
                    this.observeComponentCreation2((u5, v5) => {
                        Button.createWithLabel(n5.value);
                        __Button__setButtonProperties(n5, this.controller);
                        Button.fontColor(n5.fontColor);
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

    buildHorizontalAlignButtons(w4 = null) {
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l5, m5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], w4 ? w4 : this);
                    this.observeComponentCreation2((e5, f5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((j5, k5) => {
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
                                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1],
                                    w4 ? w4 : this);
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

    buildVerticalAlignButtons(d4 = null) {
        this.observeComponentCreation2((f4, g4) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u4, v4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((l4, m4) => {
                        ForEach.create();
                        const n4 = (r4, s4) => {
                            const t4 = r4;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - s4 - 1 : s4, d4 ? d4 : this);
                        };
                        this.forEachUpdateFunction(l4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), n4,
                            (q4) => q4.value.toString(), true, false);
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

    isNewPropertiesHighPriority(c4) {
        if (c4.role === ButtonRole.ERROR) {
            return true;
        }
        if (c4.buttonStyle !== undefined &&
            c4.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (c4.background === undefined && c4.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(k3, l3 = null) {
        this.observeComponentCreation2((n3, o3) => {
            If.create();
            if (this.buttons && this.buttons[k3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a4, b4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[k3], l3 ? l3 : this);
                    Row.pop();
                    this.observeComponentCreation2((t3, u3) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - k3 - 1 :
                            k3) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y3, z3) => {
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

    isVerticalAlignButton(e3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let f3 = false;
            let g3 = vp2px(e3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((i3) => {
                let j3 = measure.measureTextSize({
                    textContent: i3.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(j3.width) > g3) {
                    f3 = true;
                }
            });
            return f3;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(b3, c3) {
    Button.onClick(() => {
        if (b3.action) {
            b3.action();
        }
        c3?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(b3.buttonStyle ?? ALERT_BUTTON_STYLE);
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

function getNumberByResourceId(v2, w2) {
    try {
        let a3 = resourceManager.getSystemResourceManager().getNumber(v2);
        if (a3 > 0) {
            return a3;
        } else {
            return w2;
        }
    } catch (x2) {
        let y2 = x2.code;
        let z2 = x2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${y2}, message: ${z2}`);
        return w2;
    }
}

function getEnumNumberByResourceId(p2, q2) {
    try {
        let u2 = getContext().resourceManager.getNumber(p2);
        if (u2 > 0) {
            return u2;
        } else {
            return q2;
        }
    } catch (r2) {
        let s2 = r2.code;
        let t2 = r2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${s2}, message: ${t2}`);
        return q2;
    }
}

function getTextAlign(k2, l2, m2) {
    let n2 = measure.measureTextSize({
        textContent: l2,
        fontSize: m2,
        constraintWidth: k2,
    });
    let o2 = measure.measureTextSize({
        textContent: l2,
        fontSize: m2,
    });
    if (getTextHeight(n2) <= getTextHeight(o2)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}

function getTextHeight(j2) {
    if (j2 && j2.height !== null && j2.height !== undefined) {
        return Number(j2.height);
    }
    return 0;
}

function resolveKeyEvent(h2, i2) {
    if (h2.type == IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (h2.keyCode == KEYCODE_UP) {
        i2.scrollPage({ next: false });
        h2.stopPropagation();
    } else if (h2.keyCode == KEYCODE_DOWN) {
        if (i2.isAtEnd()) {
            return;
        } else {
            i2.scrollPage({ next: true });
            h2.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(b2, c2, d2, e2 = -1, f2 = undefined, g2) {
        super(b2, d2, e2, g2);
        if (typeof f2 === 'function') {
            this.paramsGenerator_ = f2;
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
        this.setInitiallyProvidedValue(c2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a2) {
        if (a2.controller !== undefined) {
            this.controller = a2.controller;
        }
        if (a2.content !== undefined) {
            this.content = a2.content;
        }
        if (a2.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = a2.fontColorWithTheme;
        }
        if (a2.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = a2.loadingProgressIconColorWithTheme;
        }
        if (a2.theme !== undefined) {
            this.theme = a2.theme;
        }
        if (a2.themeColorMode !== undefined) {
            this.themeColorMode = a2.themeColorMode;
        }
        if (a2.fontSizeScale !== undefined) {
            this.fontSizeScale = a2.fontSizeScale;
        }
        if (a2.minContentHeight !== undefined) {
            this.minContentHeight = a2.minContentHeight;
        }
    }

    updateStateVars(z1) {
    }

    purgeVariableDependenciesOnElmtId(y1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(y1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(y1);
        this.__fontSizeScale.purgeDependencyOnElmtId(y1);
        this.__minContentHeight.purgeDependencyOnElmtId(y1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(x1) {
        this.controller = x1;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(w1) {
        this.__fontColorWithTheme.set(w1);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(v1) {
        this.__loadingProgressIconColorWithTheme.set(v1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(u1) {
        this.__fontSizeScale.set(u1);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(t1) {
        this.__minContentHeight.set(t1);
    }

    initialRender() {
        this.observeComponentCreation2((r1, s1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((p1, q1) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((j1, k1) => {
                if (k1) {
                    let l1 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, j1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1580, col: 7 });
                    ViewPU.create(l1);
                    let m1 = () => {
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
                    l1.paramsGenerator_ = m1;
                } else {
                    this.updateStateVarsOfChildByElmtId(j1, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }

    contentBuilder(t = null) {
        this.observeComponentCreation2((e1, f1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((c1, d1) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((a1, b1) => {
            Text.create(this.content);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
            Text.maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES);
            Text.focusable(true);
            Text.defaultFocus(true);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((y, z) => {
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

export class PopupDialog extends ViewPU {
    constructor(n, o, p, q = -1, r = undefined, s) {
        super(n, p, q, s);
        if (typeof r === 'function') {
            this.paramsGenerator_ = r;
        }
        this.__show = new SynchedPropertySimpleTwoWayPU(o.show, this, 'show');
        this.__popup = new SynchedPropertyObjectOneWayPU(o.popup, this, 'popup');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popup.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(o);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m) {
        if (m.targetBuilder !== undefined) {
            this.targetBuilder = m.targetBuilder;
        }
        if (m.dialogWidth !== undefined) {
            this.dialogWidth = m.dialogWidth;
        }
    }

    updateStateVars(l) {
        this.__popup.reset(l.popup);
    }

    purgeVariableDependenciesOnElmtId(k) {
        this.__show.purgeDependencyOnElmtId(k);
        this.__popup.purgeDependencyOnElmtId(k);
        this.__dialogWidth.purgeDependencyOnElmtId(k);
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

    set show(j) {
        this.__show.set(j);
    }

    get popup() {
        return this.__popup.get();
    }

    set popup(i) {
        this.__popup.set(i);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(h) {
        this.__dialogWidth.set(h);
    }

    initialRender() {
        this.observeComponentCreation2((b, c) => {
            Column.create();
            Column.onClick(() => {
                let f = display.getDefaultDisplaySync();
                let g = px2vp(f.width);
                if (g - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
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
                onStateChange: this.popup?.onStateChange ?? ((e) => {
                    if (!e.isVisible) {
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
        this.targetBuilder.bind(this)(this);
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog, PopupDialog };