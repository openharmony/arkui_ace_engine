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
    constructor(p34) {
        this.colors = p34;
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
    constructor(i34, j34, k34, l34 = -1, m34 = undefined, n34) {
        super(i34, k34, l34, n34);
        if (typeof m34 === 'function') {
            this.paramsGenerator_ = m34;
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
        this.updateTextAlign = (o34) => {
            if (this.content) {
                this.textAlignment = getTextAlign(o34, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(j34);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h34) {
        if (h34.controller !== undefined) {
            this.controller = h34.controller;
        }
        if (h34.imageRes !== undefined) {
            this.imageRes = h34.imageRes;
        }
        if (h34.imageSize !== undefined) {
            this.imageSize = h34.imageSize;
        }
        if (h34.title !== undefined) {
            this.title = h34.title;
        }
        if (h34.content !== undefined) {
            this.content = h34.content;
        }
        if (h34.checkAction !== undefined) {
            this.checkAction = h34.checkAction;
        }
        if (h34.onCheckedChange !== undefined) {
            this.onCheckedChange = h34.onCheckedChange;
        }
        if (h34.checkTips !== undefined) {
            this.checkTips = h34.checkTips;
        }
        if (h34.isChecked !== undefined) {
            this.isChecked = h34.isChecked;
        }
        if (h34.primaryButton !== undefined) {
            this.primaryButton = h34.primaryButton;
        }
        if (h34.secondaryButton !== undefined) {
            this.secondaryButton = h34.secondaryButton;
        }
        if (h34.buttons !== undefined) {
            this.buttons = h34.buttons;
        }
        if (h34.textAlignment !== undefined) {
            this.textAlignment = h34.textAlignment;
        }
        if (h34.marginOffset !== undefined) {
            this.marginOffset = h34.marginOffset;
        }
        if (h34.contentScroller !== undefined) {
            this.contentScroller = h34.contentScroller;
        }
        if (h34.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = h34.fontColorWithTheme;
        }
        if (h34.theme !== undefined) {
            this.theme = h34.theme;
        }
        if (h34.themeColorMode !== undefined) {
            this.themeColorMode = h34.themeColorMode;
        }
        if (h34.fontSizeScale !== undefined) {
            this.fontSizeScale = h34.fontSizeScale;
        }
        if (h34.minContentHeight !== undefined) {
            this.minContentHeight = h34.minContentHeight;
        }
        if (h34.updateTextAlign !== undefined) {
            this.updateTextAlign = h34.updateTextAlign;
        }
        if (h34.imageIndex !== undefined) {
            this.imageIndex = h34.imageIndex;
        }
        if (h34.textIndex !== undefined) {
            this.textIndex = h34.textIndex;
        }
        if (h34.checkBoxIndex !== undefined) {
            this.checkBoxIndex = h34.checkBoxIndex;
        }
    }

    updateStateVars(g34) {
    }

    purgeVariableDependenciesOnElmtId(f34) {
        this.__imageSize.purgeDependencyOnElmtId(f34);
        this.__isChecked.purgeDependencyOnElmtId(f34);
        this.__textAlignment.purgeDependencyOnElmtId(f34);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(f34);
        this.__fontSizeScale.purgeDependencyOnElmtId(f34);
        this.__minContentHeight.purgeDependencyOnElmtId(f34);
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

    setController(e34) {
        this.controller = e34;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(d34) {
        this.__imageSize.set(d34);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(c34) {
        this.__isChecked.set(c34);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(b34) {
        this.__textAlignment.set(b34);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(a34) {
        this.__fontColorWithTheme.set(a34);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(z33) {
        this.__fontSizeScale.set(z33);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(y33) {
        this.__minContentHeight.set(y33);
    }

    initialRender() {
        this.observeComponentCreation2((w33, x33) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((s33, t33) => {
                if (t33) {
                    let u33 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, s33, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 131, col: 5 });
                    ViewPU.create(u33);
                    let t = () => {
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
                    u33.paramsGenerator_ = t;
                } else {
                    this.updateStateVarsOfChildByElmtId(s33, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(n32 = null) {
        {
            this.observeComponentCreation2((o32, p32) => {
                if (p32) {
                    let q32 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((f33, g33) => {
                                ForEach.create();
                                const s = i33 => {
                                    const j33 = i33;
                                    this.observeComponentCreation2((k33, l33) => {
                                        If.create();
                                        if (j33 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (j33 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((q33, r33) => {
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
                                                this.observeComponentCreation2((o33, p33) => {
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
                                                this.observeComponentCreation2((m33, n33) => {
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
                                this.forEachUpdateFunction(f33, [this.imageIndex, this.textIndex,
                                    this.checkBoxIndex], s);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, o32, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 146, col: 5 });
                    ViewPU.create(q32);
                    let q = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((s32, t32) => {
                                    ForEach.create();
                                    const r = v32 => {
                                        const w32 = v32;
                                        this.observeComponentCreation2((x32, y32) => {
                                            If.create();
                                            if (w32 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (w32 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((d33, e33) => {
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
                                                    this.observeComponentCreation2((b33, c33) => {
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
                                                    this.observeComponentCreation2((z32, a33) => {
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
                                    this.forEachUpdateFunction(s32,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], r);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    q32.paramsGenerator_ = q;
                } else {
                    this.updateStateVarsOfChildByElmtId(o32, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(d32 = null) {
        this.observeComponentCreation2((l32, m32) => {
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
        this.observeComponentCreation2((e32, f32) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i32, j32) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((k32) => {
                            this.isChecked = k32;
                            if (this.checkAction) {
                                this.checkAction(k32);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(k32);
                            }
                        });
                        Checkbox.accessibilityLevel('yes');
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(CHECK_BOX_MARGIN_END)
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((g32, h32) => {
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

    imagePart(y31 = null) {
        this.observeComponentCreation2((b32, c32) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((z31, a32) => {
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

    textPart(g31 = null) {
        this.observeComponentCreation2((w31, x31) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((u31, v31) => {
            Column.create();
            Column.margin({
                end: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                })
            });
        }, Column);
        this.observeComponentCreation2((o31, p31) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s31, t31) => {
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
                    this.observeComponentCreation2((q31, r31) => {
                        Text.create(this.title);
                        Text.fontSize(`${TITLE_S}fp`);
                        Text.fontWeight(FontWeight.Bold);
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
        this.observeComponentCreation2((h31, i31) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m31, n31) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((j31, k31) => {
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
                        Text.onKeyEvent((l31) => {
                            if (l31) {
                                resolveKeyEvent(l31, this.contentScroller);
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
    constructor(z30, a31, b31, c31 = -1, d31 = undefined, e31) {
        super(z30, b31, c31, e31);
        if (typeof d31 === "function") {
            this.paramsGenerator_ = d31;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (f31) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(a31.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(a31);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y30) {
        if (y30.title !== undefined) {
            this.title = y30.title;
        }
        if (y30.content !== undefined) {
            this.content = y30.content;
        }
        if (y30.checkTips !== undefined) {
            this.checkTips = y30.checkTips;
        }
        if (y30.updateTextAlign !== undefined) {
            this.updateTextAlign = y30.updateTextAlign;
        }
        if (y30.dialogBuilder !== undefined) {
            this.dialogBuilder = y30.dialogBuilder;
        }
        if (y30.imageIndex !== undefined) {
            this.imageIndex = y30.imageIndex;
        }
        if (y30.textIndex !== undefined) {
            this.textIndex = y30.textIndex;
        }
        if (y30.checkBoxIndex !== undefined) {
            this.checkBoxIndex = y30.checkBoxIndex;
        }
        if (y30.childrenSize !== undefined) {
            this.childrenSize = y30.childrenSize;
        }
    }

    updateStateVars(x30) {
    }

    purgeVariableDependenciesOnElmtId(w30) {
        this.__minContentHeight.purgeDependencyOnElmtId(w30);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(v30 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(u30) {
        this.__minContentHeight.set(u30);
    }

    onPlaceChildren(n30, o30, p30) {
        let q30 = 0;
        let r30 = 0;
        for (let s30 = 0; s30 < o30.length; s30++) {
            let t30 = o30[s30];
            t30.layout({ x: q30, y: r30 });
            r30 += t30.measureResult.height;
        }
    }

    onMeasureSize(v29, w29, x29) {
        let y29 = { width: Number(x29.maxWidth), height: 0 };
        if (w29.length < this.childrenSize) {
            return y29;
        }
        let z29 = 0;
        let a30 = 0;
        if (this.checkTips !== null) {
            let k30 = w29[this.checkBoxIndex];
            let l30 = {
                maxWidth: x29.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: x29.maxHeight
            };
            let m30 = k30.measure(l30);
            a30 = m30.height;
            z29 += a30;
        }
        let b30 = w29[this.imageIndex];
        let c30 = 0;
        if (this.title !== null || this.content !== null) {
            c30 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let d30 = Number(x29.maxHeight) - a30 - c30;
        let e30 = {
            maxWidth: x29.maxWidth,
            maxHeight: d30
        };
        let f30 = b30.measure(e30);
        z29 += f30.height;
        if (this.title !== null || this.content !== null) {
            let g30 = w29[this.textIndex];
            this.updateTextAlign(y29.width);
            let h30 = Number(x29.maxHeight) - f30.height - a30;
            let i30 = {
                maxWidth: x29.maxWidth,
                maxHeight: Math.max(h30, TEXT_MIN_HEIGHT)
            };
            let j30 = g30.measure(i30);
            z29 += j30.height;
        }
        y29.height = z29;
        this.minContentHeight = Math.max(a30 + f30.height + c30, MIN_CONTENT_HEIGHT);
        return y29;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(p29, q29, r29, s29 = -1, t29 = undefined, u29) {
        super(p29, r29, s29, u29);
        if (typeof t29 === 'function') {
            this.paramsGenerator_ = t29;
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
        this.setInitiallyProvidedValue(q29);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o29) {
        if (o29.controller !== undefined) {
            this.controller = o29.controller;
        }
        if (o29.title !== undefined) {
            this.title = o29.title;
        }
        if (o29.content !== undefined) {
            this.content = o29.content;
        }
        if (o29.confirm !== undefined) {
            this.confirm = o29.confirm;
        }
        if (o29.radioContent !== undefined) {
            this.radioContent = o29.radioContent;
        }
        if (o29.buttons !== undefined) {
            this.buttons = o29.buttons;
        }
        if (o29.contentPadding !== undefined) {
            this.contentPadding = o29.contentPadding;
        }
        if (o29.isFocus !== undefined) {
            this.isFocus = o29.isFocus;
        }
        if (o29.currentFocusIndex !== undefined) {
            this.currentFocusIndex = o29.currentFocusIndex;
        }
        if (o29.radioHeight !== undefined) {
            this.radioHeight = o29.radioHeight;
        }
        if (o29.itemHeight !== undefined) {
            this.itemHeight = o29.itemHeight;
        }
        if (o29.selectedIndex !== undefined) {
            this.selectedIndex = o29.selectedIndex;
        }
        if (o29.contentBuilder !== undefined) {
            this.contentBuilder = o29.contentBuilder;
        }
        if (o29.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = o29.fontColorWithTheme;
        }
        if (o29.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = o29.dividerColorWithTheme;
        }
        if (o29.theme !== undefined) {
            this.theme = o29.theme;
        }
        if (o29.themeColorMode !== undefined) {
            this.themeColorMode = o29.themeColorMode;
        }
        if (o29.contentScroller !== undefined) {
            this.contentScroller = o29.contentScroller;
        }
        if (o29.fontSizeScale !== undefined) {
            this.fontSizeScale = o29.fontSizeScale;
        }
        if (o29.minContentHeight !== undefined) {
            this.minContentHeight = o29.minContentHeight;
        }
    }

    updateStateVars(n29) {
    }

    purgeVariableDependenciesOnElmtId(m29) {
        this.__selectedIndex.purgeDependencyOnElmtId(m29);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(m29);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(m29);
        this.__fontSizeScale.purgeDependencyOnElmtId(m29);
        this.__minContentHeight.purgeDependencyOnElmtId(m29);
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

    setController(l29) {
        this.controller = l29;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(k29) {
        this.__selectedIndex.set(k29);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(j29) {
        this.__fontColorWithTheme.set(j29);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(i29) {
        this.__dividerColorWithTheme.set(i29);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(h29) {
        this.__fontSizeScale.set(h29);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(g29) {
        this.__minContentHeight.set(g29);
    }
    buildContent(j27 = null) {
        this.observeComponentCreation2((b29, c29) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((d29, e29) => {
                let f29 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (e29 > 0) {
                            this.contentScroller.scrollBy(0, f29);
                        } else if (e29 < 0) {
                            this.contentScroller.scrollBy(0, 0 - f29);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((z28, a29) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((t28, u28) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x28, y28) => {
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
                    this.observeComponentCreation2((v28, w28) => {
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
        this.observeComponentCreation2((r28, s28) => {
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
        this.observeComponentCreation2((k27, l27) => {
            ForEach.create();
            const m = (n27, o27) => {
                const p27 = n27;
                {
                    const n = (p28, q28) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p28);
                        o(p28, q28);
                        if (!q28) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const o = (l28, m28) => {
                        ListItem.create(p, true);
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
                        ListItem.onSizeChange((n28, o28) => {
                            this.itemHeight = Number(o28.height);
                        });
                    };
                    const p = (t27, u27) => {
                        n(t27, u27);
                        this.observeComponentCreation2((j28, k28) => {
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
                            Column.accessibilityText(getAccessibilityText(p27.title, this.selectedIndex === o27));
                            Column.onClick(() => {
                                this.selectedIndex = o27;
                                p27.action && p27.action();
                                this.controller?.close();
                            });
                        }, Column);
                        this.observeComponentCreation2((h28, i28) => {
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
                        this.observeComponentCreation2((f28, g28) => {
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
                        this.observeComponentCreation2((d28, e28) => {
                            Text.create(p27.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((z27, a28) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === o27);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(o27));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = o27;
                                if (o27 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (o27 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((b28, c28) => {
                                this.radioHeight = Number(c28.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((v27, w27) => {
                            If.create();
                            if (o27 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((x27, y27) => {
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
                    this.observeComponentCreation2(o, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(k27, this.radioContent, m, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((h27, i27) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((d27, e27) => {
                if (e27) {
                    let f27 = new CustomDialogContentComponent(this, {
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
                    }, undefined, d27, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 526, col: 5 });
                    ViewPU.create(f27);
                    let l = () => {
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
                    f27.paramsGenerator_ = l;
                } else {
                    this.updateStateVarsOfChildByElmtId(d27, {});
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
    constructor(w26, x26, y26, z26 = -1, a27 = undefined, b27) {
        super(w26, y26, z26, b27);
        if (typeof a27 === 'function') {
            this.paramsGenerator_ = a27;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(x26.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (c27) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(x26);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v26) {
        if (v26.textIndex !== undefined) {
            this.textIndex = v26.textIndex;
        }
        if (v26.checkboxIndex !== undefined) {
            this.checkboxIndex = v26.checkboxIndex;
        }
        if (v26.updateTextAlign !== undefined) {
            this.updateTextAlign = v26.updateTextAlign;
        }
        if (v26.dialogBuilder !== undefined) {
            this.dialogBuilder = v26.dialogBuilder;
        }
    }

    updateStateVars(u26) {
    }

    purgeVariableDependenciesOnElmtId(t26) {
        this.__minContentHeight.purgeDependencyOnElmtId(t26);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(s26) {
        this.__minContentHeight.set(s26);
    }

    doNothingBuilder(r26 = null) {
    }

    onPlaceChildren(k26, l26, m26) {
        let n26 = 0;
        let o26 = 0;
        for (let p26 = 0; p26 < l26.length; p26++) {
            let q26 = l26[p26];
            q26.layout({ x: n26, y: o26 });
            o26 += q26.measureResult.height;
        }
    }

    onMeasureSize(y25, z25, a26) {
        let b26 = { width: Number(a26.maxWidth), height: 0 };
        let c26 = 2;
        if (z25.length < c26) {
            return b26;
        }
        this.updateTextAlign(b26.width);
        let d26 = 0;
        let e26 = z25[this.checkboxIndex];
        let f26 = {
            maxWidth: a26.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: a26.maxHeight
        };
        let g26 = e26.measure(f26);
        d26 += g26.height;
        let h26 = z25[this.textIndex];
        let i26 = {
            maxWidth: a26.maxWidth,
            maxHeight: Number(a26.maxHeight) - d26
        };
        let j26 = h26.measure(i26);
        d26 += j26.height;
        b26.height = d26;
        this.minContentHeight = Math.max(g26.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return b26;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(r25, s25, t25, u25 = -1, v25 = undefined, w25) {
        super(r25, t25, u25, w25);
        if (typeof v25 === 'function') {
            this.paramsGenerator_ = v25;
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
        this.updateTextAlign = (x25) => {
            if (this.content) {
                this.textAlign = getTextAlign(x25, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(s25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q25) {
        if (q25.controller !== undefined) {
            this.controller = q25.controller;
        }
        if (q25.title !== undefined) {
            this.title = q25.title;
        }
        if (q25.content !== undefined) {
            this.content = q25.content;
        }
        if (q25.checkTips !== undefined) {
            this.checkTips = q25.checkTips;
        }
        if (q25.isChecked !== undefined) {
            this.isChecked = q25.isChecked;
        }
        if (q25.primaryButton !== undefined) {
            this.primaryButton = q25.primaryButton;
        }
        if (q25.secondaryButton !== undefined) {
            this.secondaryButton = q25.secondaryButton;
        }
        if (q25.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q25.fontColorWithTheme;
        }
        if (q25.theme !== undefined) {
            this.theme = q25.theme;
        }
        if (q25.themeColorMode !== undefined) {
            this.themeColorMode = q25.themeColorMode;
        }
        if (q25.onCheckedChange !== undefined) {
            this.onCheckedChange = q25.onCheckedChange;
        }
        if (q25.contentScroller !== undefined) {
            this.contentScroller = q25.contentScroller;
        }
        if (q25.buttons !== undefined) {
            this.buttons = q25.buttons;
        }
        if (q25.textAlign !== undefined) {
            this.textAlign = q25.textAlign;
        }
        if (q25.marginOffset !== undefined) {
            this.marginOffset = q25.marginOffset;
        }
        if (q25.fontSizeScale !== undefined) {
            this.fontSizeScale = q25.fontSizeScale;
        }
        if (q25.minContentHeight !== undefined) {
            this.minContentHeight = q25.minContentHeight;
        }
        if (q25.textIndex !== undefined) {
            this.textIndex = q25.textIndex;
        }
        if (q25.checkboxIndex !== undefined) {
            this.checkboxIndex = q25.checkboxIndex;
        }
        if (q25.updateTextAlign !== undefined) {
            this.updateTextAlign = q25.updateTextAlign;
        }
    }

    updateStateVars(p25) {
    }

    purgeVariableDependenciesOnElmtId(o25) {
        this.__isChecked.purgeDependencyOnElmtId(o25);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o25);
        this.__textAlign.purgeDependencyOnElmtId(o25);
        this.__fontSizeScale.purgeDependencyOnElmtId(o25);
        this.__minContentHeight.purgeDependencyOnElmtId(o25);
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

    setController(n25) {
        this.controller = n25;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(m25) {
        this.__isChecked.set(m25);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(l25) {
        this.__fontColorWithTheme.set(l25);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(k25) {
        this.__textAlign.set(k25);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j25) {
        this.__fontSizeScale.set(j25);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(i25) {
        this.__minContentHeight.set(i25);
    }

    textBuilder(y24 = null) {
        this.observeComponentCreation2((g25, h25) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((e25, f25) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((c25, d25) => {
            Column.create();
            Column.margin({ end: LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            })
            });
        }, Column);
        this.observeComponentCreation2((z24, a25) => {
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
            Text.onKeyEvent((b25) => {
                if (b25) {
                    resolveKeyEvent(b25, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(q24 = null) {
        this.observeComponentCreation2((w24, x24) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((t24, u24) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((v24) => {
                this.isChecked = v24;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.accessibilityLevel('yes');
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((r24, s24) => {
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

    buildContent(p23 = null) {
        {
            this.observeComponentCreation2((q23, r23) => {
                if (r23) {
                    let s23 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((f24, g24) => {
                                ForEach.create();
                                const k = i24 => {
                                    const j24 = i24;
                                    this.observeComponentCreation2((k24, l24) => {
                                        If.create();
                                        if (j24 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((o24, p24) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (j24 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((m24, n24) => {
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
                                this.forEachUpdateFunction(f24, [this.textIndex, this.checkboxIndex], k);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, q23, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 733, col: 5 });
                    ViewPU.create(s23);
                    let i = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((u23, v23) => {
                                    ForEach.create();
                                    const j = x23 => {
                                        const y23 = x23;
                                        this.observeComponentCreation2((z23, a24) => {
                                            If.create();
                                            if (y23 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((d24, e24) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (y23 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((b24, c24) => {
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
                                    this.forEachUpdateFunction(u23, [this.textIndex, this.checkboxIndex], j);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    s23.paramsGenerator_ = i;
                } else {
                    this.updateStateVarsOfChildByElmtId(q23, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        this.observeComponentCreation2((n23, o23) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((j23, k23) => {
                if (k23) {
                    let l23 = new CustomDialogContentComponent(this, {
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
                    }, undefined, j23, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 749, col: 5 });
                    ViewPU.create(l23);
                    let h = () => {
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
                    l23.paramsGenerator_ = h;
                } else {
                    this.updateStateVarsOfChildByElmtId(j23, {});
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
    constructor(d23, e23, f23, g23 = -1, h23 = undefined, i23) {
        super(d23, f23, g23, i23);
        if (typeof h23 === 'function') {
            this.paramsGenerator_ = h23;
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
        this.setInitiallyProvidedValue(e23);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c23) {
        if (c23.controller !== undefined) {
            this.controller = c23.controller;
        }
        if (c23.primaryTitle !== undefined) {
            this.primaryTitle = c23.primaryTitle;
        }
        if (c23.secondaryTitle !== undefined) {
            this.secondaryTitle = c23.secondaryTitle;
        }
        if (c23.content !== undefined) {
            this.content = c23.content;
        }
        if (c23.primaryButton !== undefined) {
            this.primaryButton = c23.primaryButton;
        }
        if (c23.secondaryButton !== undefined) {
            this.secondaryButton = c23.secondaryButton;
        }
        if (c23.buttons !== undefined) {
            this.buttons = c23.buttons;
        }
        if (c23.textAlign !== undefined) {
            this.textAlign = c23.textAlign;
        }
        if (c23.contentScroller !== undefined) {
            this.contentScroller = c23.contentScroller;
        }
        if (c23.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = c23.fontColorWithTheme;
        }
        if (c23.theme !== undefined) {
            this.theme = c23.theme;
        }
        if (c23.themeColorMode !== undefined) {
            this.themeColorMode = c23.themeColorMode;
        }
        if (c23.fontSizeScale !== undefined) {
            this.fontSizeScale = c23.fontSizeScale;
        }
        if (c23.minContentHeight !== undefined) {
            this.minContentHeight = c23.minContentHeight;
        }
    }

    updateStateVars(b23) {
    }

    purgeVariableDependenciesOnElmtId(a23) {
        this.__textAlign.purgeDependencyOnElmtId(a23);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(a23);
        this.__fontSizeScale.purgeDependencyOnElmtId(a23);
        this.__minContentHeight.purgeDependencyOnElmtId(a23);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(z22) {
        this.controller = z22;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(y22) {
        this.__textAlign.set(y22);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(x22) {
        this.__fontColorWithTheme.set(x22);
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

    initialRender() {
        this.observeComponentCreation2((t22, u22) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p22, q22) => {
                if (q22) {
                    let r22 = new CustomDialogContentComponent(this, {
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
                    }, undefined, p22, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 807, col: 5 });
                    ViewPU.create(r22);
                    let g = () => {
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
                    r22.paramsGenerator_ = g;
                } else {
                    this.updateStateVarsOfChildByElmtId(p22, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(f22 = null) {
        this.observeComponentCreation2((n22, o22) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(this.getMargin()) });
        }, Column);
        this.observeComponentCreation2((l22, m22) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((g22, h22) => {
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
                end: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                })
            });
            Text.width(`calc(100% - ${PADDING_LEVEL_8}vp)`);
            Text.textAlign(this.textAlign);
            Text.onAreaChange((j22, k22) => {
                this.updateTextAlign(Number(k22.width));
            });
            Text.onKeyEvent((i22) => {
                if (i22) {
                    resolveKeyEvent(i22, this.contentScroller);
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

    updateTextAlign(e22) {
        this.textAlign = getTextAlign(e22, this.content, `${BODY_L * this.fontSizeScale}vp`);
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
    constructor(y21, z21, a22, b22 = -1, c22 = undefined, d22) {
        super(y21, a22, b22, d22);
        if (typeof c22 === 'function') {
            this.paramsGenerator_ = c22;
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
        this.setInitiallyProvidedValue(z21);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x21) {
        if (x21.controller !== undefined) {
            this.controller = x21.controller;
        }
        if (x21.primaryTitle !== undefined) {
            this.primaryTitle = x21.primaryTitle;
        }
        if (x21.secondaryTitle !== undefined) {
            this.secondaryTitle = x21.secondaryTitle;
        }
        if (x21.contentBuilder !== undefined) {
            this.contentBuilder = x21.contentBuilder;
        }
        if (x21.contentAreaPadding !== undefined) {
            this.contentAreaPadding = x21.contentAreaPadding;
        }
        if (x21.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = x21.localizedContentAreaPadding;
        }
        if (x21.buttons !== undefined) {
            this.buttons = x21.buttons;
        }
        if (x21.theme !== undefined) {
            this.theme = x21.theme;
        }
        if (x21.themeColorMode !== undefined) {
            this.themeColorMode = x21.themeColorMode;
        }
        if (x21.fontSizeScale !== undefined) {
            this.fontSizeScale = x21.fontSizeScale;
        }
        if (x21.minContentHeight !== undefined) {
            this.minContentHeight = x21.minContentHeight;
        }
    }

    updateStateVars(w21) {
    }

    purgeVariableDependenciesOnElmtId(v21) {
        this.__fontSizeScale.purgeDependencyOnElmtId(v21);
        this.__minContentHeight.purgeDependencyOnElmtId(v21);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(u21) {
        this.controller = u21;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(t21) {
        this.__fontSizeScale.set(t21);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(s21) {
        this.__minContentHeight.set(s21);
    }

    initialRender() {
        this.observeComponentCreation2((q21, r21) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((m21, n21) => {
                if (n21) {
                    let o21 = new CustomDialogContentComponent(this, {
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
                    }, undefined, m21, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 903, col: 5 });
                    ViewPU.create(o21);
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
                    o21.paramsGenerator_ = f;
                } else {
                    this.updateStateVarsOfChildByElmtId(m21, {});
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
    constructor(l21) {
        super(l21);
        this.arg_ = l21;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(f21, g21, h21, i21 = -1, j21 = undefined, k21) {
        super(f21, h21, i21, k21);
        if (typeof j21 === 'function') {
            this.paramsGenerator_ = j21;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(g21.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(g21.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(g21.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(g21);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e21) {
        if (e21.dialogBuilder !== undefined) {
            this.dialogBuilder = e21.dialogBuilder;
        }
        if (e21.titleIndex !== undefined) {
            this.titleIndex = e21.titleIndex;
        }
        if (e21.contentIndex !== undefined) {
            this.contentIndex = e21.contentIndex;
        }
        if (e21.buttonIndex !== undefined) {
            this.buttonIndex = e21.buttonIndex;
        }
    }

    updateStateVars(d21) {
    }

    purgeVariableDependenciesOnElmtId(c21) {
        this.__titleHeight.purgeDependencyOnElmtId(c21);
        this.__buttonHeight.purgeDependencyOnElmtId(c21);
        this.__titleMinHeight.purgeDependencyOnElmtId(c21);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(b21 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(a21) {
        this.__titleHeight.set(a21);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(z20) {
        this.__buttonHeight.set(z20);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(y20) {
        this.__titleMinHeight.set(y20);
    }

    onPlaceChildren(r20, s20, t20) {
        let u20 = 0;
        let v20 = 0;
        for (let w20 = 0; w20 < s20.length; w20++) {
            let x20 = s20[w20];
            x20.layout({ x: u20, y: v20 });
            v20 += x20.measureResult.height;
        }
    }

    onMeasureSize(d20, e20, f20) {
        let g20 = { width: Number(f20.maxWidth), height: 0 };
        let h20 = 3;
        if (e20.length < h20) {
            return g20;
        }
        let i20 = 0;
        let j20 = e20[this.titleIndex];
        let k20 = {
            maxWidth: f20.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: f20.maxHeight
        };
        let l20 = j20.measure(k20);
        this.titleHeight = l20.height;
        i20 += this.titleHeight;
        let m20 = e20[this.buttonIndex];
        let n20 = m20.measure(f20);
        this.buttonHeight = n20.height;
        i20 += this.buttonHeight;
        let o20 = e20[this.contentIndex];
        let p20 = {
            maxWidth: f20.maxWidth,
            maxHeight: Number(f20.maxHeight) - i20
        };
        let q20 = o20.measure(p20);
        i20 += q20.height;
        g20.height = i20;
        return g20;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(x19, y19, z19, a20 = -1, b20 = undefined, c20) {
        super(x19, z19, a20, c20);
        if (typeof b20 === 'function') {
            this.paramsGenerator_ = b20;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(y19.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(y19.fontSizeScale, this, 'fontSizeScale');
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
        this.setInitiallyProvidedValue(y19);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w19) {
        if (w19.controller !== undefined) {
            this.controller = w19.controller;
        }
        if (w19.primaryTitle !== undefined) {
            this.primaryTitle = w19.primaryTitle;
        }
        if (w19.secondaryTitle !== undefined) {
            this.secondaryTitle = w19.secondaryTitle;
        }
        if (w19.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = w19.localizedContentAreaPadding;
        }
        if (w19.contentBuilder !== undefined) {
            this.contentBuilder = w19.contentBuilder;
        }
        if (w19.buttons !== undefined) {
            this.buttons = w19.buttons;
        }
        if (w19.contentAreaPadding !== undefined) {
            this.contentAreaPadding = w19.contentAreaPadding;
        }
        if (w19.keyIndex !== undefined) {
            this.keyIndex = w19.keyIndex;
        }
        if (w19.theme !== undefined) {
            this.theme = w19.theme;
        }
        if (w19.themeColorMode !== undefined) {
            this.themeColorMode = w19.themeColorMode;
        }
        if (w19.titleHeight !== undefined) {
            this.titleHeight = w19.titleHeight;
        }
        if (w19.buttonHeight !== undefined) {
            this.buttonHeight = w19.buttonHeight;
        }
        if (w19.contentMaxHeight !== undefined) {
            this.contentMaxHeight = w19.contentMaxHeight;
        }
        if (w19.customStyle !== undefined) {
            this.customStyle = w19.customStyle;
        }
        if (w19.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = w19.buttonMaxFontSize;
        }
        if (w19.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = w19.buttonMinFontSize;
        }
        if (w19.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = w19.primaryTitleMaxFontSize;
        }
        if (w19.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = w19.primaryTitleMinFontSize;
        }
        if (w19.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = w19.secondaryTitleMaxFontSize;
        }
        if (w19.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = w19.secondaryTitleMinFontSize;
        }
        if (w19.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = w19.primaryTitleFontColorWithTheme;
        }
        if (w19.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = w19.secondaryTitleFontColorWithTheme;
        }
        if (w19.titleTextAlign !== undefined) {
            this.titleTextAlign = w19.titleTextAlign;
        }
        if (w19.isButtonVertical !== undefined) {
            this.isButtonVertical = w19.isButtonVertical;
        }
        if (w19.titleMinHeight !== undefined) {
            this.titleMinHeight = w19.titleMinHeight;
        }
        if (w19.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = w19.isFollowingSystemFontScale;
        }
        if (w19.appMaxFontScale !== undefined) {
            this.appMaxFontScale = w19.appMaxFontScale;
        }
        if (w19.titleIndex !== undefined) {
            this.titleIndex = w19.titleIndex;
        }
        if (w19.contentIndex !== undefined) {
            this.contentIndex = w19.contentIndex;
        }
        if (w19.buttonIndex !== undefined) {
            this.buttonIndex = w19.buttonIndex;
        }
    }

   updateStateVars(v19) {
    }

    purgeVariableDependenciesOnElmtId(u19) {
        this.__minContentHeight.purgeDependencyOnElmtId(u19);
        this.__titleHeight.purgeDependencyOnElmtId(u19);
        this.__buttonHeight.purgeDependencyOnElmtId(u19);
        this.__contentMaxHeight.purgeDependencyOnElmtId(u19);
        this.__fontSizeScale.purgeDependencyOnElmtId(u19);
        this.__customStyle.purgeDependencyOnElmtId(u19);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(u19);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(u19);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(u19);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(u19);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(u19);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(u19);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(u19);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(u19);
        this.__titleTextAlign.purgeDependencyOnElmtId(u19);
        this.__isButtonVertical.purgeDependencyOnElmtId(u19);
        this.__titleMinHeight.purgeDependencyOnElmtId(u19);
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

    set minContentHeight(t19) {
        this.__minContentHeight.set(t19);
    }

    defaultContentBuilder(s19 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(r19) {
        this.__titleHeight.set(r19);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(q19) {
        this.__buttonHeight.set(q19);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(p19) {
        this.__contentMaxHeight.set(p19);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(o19) {
        this.__fontSizeScale.set(o19);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(n19) {
        this.__customStyle.set(n19);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(m19) {
        this.__buttonMaxFontSize.set(m19);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(l19) {
        this.__buttonMinFontSize.set(l19);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(k19) {
        this.__primaryTitleMaxFontSize.set(k19);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(j19) {
        this.__primaryTitleMinFontSize.set(j19);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(i19) {
        this.__secondaryTitleMaxFontSize.set(i19);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(h19) {
        this.__secondaryTitleMinFontSize.set(h19);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(g19) {
        this.__primaryTitleFontColorWithTheme.set(g19);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(f19) {
        this.__secondaryTitleFontColorWithTheme.set(f19);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(e19) {
        this.__titleTextAlign.set(e19);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(d19) {
        this.__isButtonVertical.set(d19);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(c19) {
        this.__titleMinHeight.set(c19);
    }
    initialRender() {
        this.observeComponentCreation2((a19, b19) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((y18, z18) => {
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
        this.observeComponentCreation2((w18, x18) => {
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
            this.observeComponentCreation2((o17, p17) => {
                if (p17) {
                    let q17 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((h18, i18) => {
                                ForEach.create();
                                const e = k18 => {
                                    const l18 = k18;
                                    this.observeComponentCreation2((m18, n18) => {
                                        If.create();
                                        if (l18 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((u18, v18) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (l18 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((s18, t18) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((q18, r18) => {
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
                                                this.observeComponentCreation2((o18, p18) => {
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
                                this.forEachUpdateFunction(h18, [this.titleIndex, this.contentIndex,
                                    this.buttonIndex], e);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, o17, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1041, col: 11 });
                    ViewPU.create(q17);
                    let c = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((s17, t17) => {
                                    ForEach.create();
                                    const d = v17 => {
                                        const w17 = v17;
                                        this.observeComponentCreation2((x17, y17) => {
                                            If.create();
                                            if (w17 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((f18, g18) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (w17 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((d18, e18) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((b18, c18) => {
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
                                                    this.observeComponentCreation2((z17, a18) => {
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
                                    this.forEachUpdateFunction(s17, [this.titleIndex, this.contentIndex,
                                        this.buttonIndex], d);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    q17.paramsGenerator_ = c;
                } else {
                    this.updateStateVarsOfChildByElmtId(o17, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(f17, g17, h17) {
        let i17 = { width: f17.width, height: f17.height };
        let j17 = Number(h17.maxWidth);
        let k17 = Number(h17.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(j17 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let l17 = 0;
        g17.forEach((m17) => {
            this.contentMaxHeight = '100%';
            let n17 = m17.measure(h17);
            if (k17 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                n17 = m17.measure(h17);
            }
            l17 += n17.height;
        });
        i17.height = l17;
        i17.width = j17;
        return i17;
    }

    aboutToAppear() {
        let d17 = this.getUIContext();
        this.isFollowingSystemFontScale = d17.isFollowingSystemFontScale();
        this.appMaxFontScale = d17.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let e17 = this.controller;
            if (e17.arg_ && e17.arg_.customStyle && e17.arg_.customStyle === true) {
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
            let b17 = this.getUIContext();
            let c17 = b17.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(c17, this.appMaxFontScale);
        } catch (y16) {
            let z16 = y16.code;
            let a17 = y16.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${z16}, message: ${a17}`);
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

    titleBuilder(j16 = null) {
        this.observeComponentCreation2((w16, x16) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((u16, v16) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((s16, t16) => {
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
        this.observeComponentCreation2((o16, p16) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q16, r16) => {
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
        this.observeComponentCreation2((m16, n16) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((k16, l16) => {
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
        let i16 = ALERT_TITLE_ALIGNMENT;
        if (i16 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (i16 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (i16 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (i16 === TextAlign.JUSTIFY) {
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

    ButtonBuilder(b16 = null) {
        this.observeComponentCreation2((g16, h16) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((c16, d16) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e16, f16) => {
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
    buildSingleButton(p15, q15 = null) {
        this.observeComponentCreation2((r15, s15) => {
            If.create();
            if (this.isNewPropertiesHighPriority(p15)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z15, a16) => {
                        Button.createWithLabel(p15.value);
                        __Button__setButtonProperties(p15, this.buttons, this.controller);
                        Button.role(p15.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (p15.background !== undefined && p15.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((x15, y15) => {
                        Button.createWithLabel(p15.value);
                        __Button__setButtonProperties(p15, this.buttons, this.controller);
                        Button.backgroundColor(p15.background);
                        Button.fontColor(p15.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (p15.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((v15, w15) => {
                        Button.createWithLabel(p15.value);
                        __Button__setButtonProperties(p15, this.buttons, this.controller);
                        Button.backgroundColor(p15.background);
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
                    this.observeComponentCreation2((t15, u15) => {
                        Button.createWithLabel(p15.value);
                        __Button__setButtonProperties(p15, this.buttons, this.controller);
                        Button.fontColor(p15.fontColor);
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

    buildHorizontalAlignButtons(e15 = null) {
        this.observeComponentCreation2((f15, g15) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n15, o15) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((h15, i15) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l15, m15) => {
                                    Row.create();
                                    Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                                    Row.justifyContent(FlexAlign.Center);
                                }, Row);
                                this.observeComponentCreation2((j15, k15) => {
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

    buildVerticalAlignButtons(s14 = null) {
        this.observeComponentCreation2((t14, u14) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c15, d15) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((v14, w14) => {
                        ForEach.create();
                        const b = (z14, a15) => {
                            const b15 = z14;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - a15 - 1 : a15);
                        };
                        this.forEachUpdateFunction(v14, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT),
                            b, (y14) => y14.value.toString(), true, false);
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

    isNewPropertiesHighPriority(r14) {
        if (r14.role === ButtonRole.ERROR) {
            return true;
        }
        if (r14.buttonStyle !== undefined &&
            r14.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (r14.background === undefined && r14.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(h14, i14 = null) {
        this.observeComponentCreation2((j14, k14) => {
            If.create();
            if (this.buttons && this.buttons[h14]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p14, q14) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[h14]);
                    Row.pop();
                    this.observeComponentCreation2((l14, m14) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ?
                            HORIZON_BUTTON_MAX_COUNT - h14 - 1 : h14) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n14, o14) => {
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

    isVerticalAlignButton(c14) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let d14 = false;
            let e14 = vp2px(c14 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((f14) => {
                let g14 = measure.measureTextSize({
                    textContent: f14.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(g14.width) > e14) {
                    d14 = true;
                }
            });
            return d14;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(z13, a14, b14) {
    Button.onClick(() => {
        if (z13.action) {
            z13.action();
        }
        b14?.close();
    });
    Button.defaultFocus(z13.defaultFocus ? true : isHasDefaultFocus(a14) ? false : true);
    Button.buttonStyle(z13.buttonStyle ?? ALERT_BUTTON_STYLE);
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.ROUNDED_RECTANGLE);
}

function isHasDefaultFocus(t13) {
    try {
        let x13 = false;
        t13?.forEach((y13) => {
            if (y13.defaultFocus) {
                x13 = true;
            }
        });
        return x13;
    } catch (u13) {
        let v13 = u13.code;
        let w13 = u13.message;
        hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${v13}, message: ${w13}`);
        return false;
    }
}

function getNumberByResourceId(m13, n13, o13) {
    try {
        let s13 = resourceManager.getSystemResourceManager().getNumber(m13);
        if (s13 > 0 || o13) {
            return s13;
        } else {
            return n13;
        }
    } catch (p13) {
        let q13 = p13.code;
        let r13 = p13.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${q13}, message: ${r13}`);
        return n13;
    }
}

function getEnumNumberByResourceId(g13, h13) {
    try {
        let l13 = getContext().resourceManager.getNumber(g13);
        if (l13 > 0) {
            return l13;
        } else {
            return h13;
        }
    } catch (i13) {
        let j13 = i13.code;
        let k13 = i13.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${j13}, message: ${k13}`);
        return h13;
    }
}

function getAccessibilityText(z12, a13) {
    try {
        let e13 = getContext().resourceManager.getStringSync(125833934);
        let f13 = '';
        if (typeof z12 === 'string') {
            f13 = z12;
        } else {
            f13 = getContext().resourceManager.getStringSync(z12);
        }
        return a13 ? `${e13},${f13}` : f13;
    } catch (b13) {
        let c13 = b13.code;
        let d13 = b13.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${c13}, message: ${d13}`);
        return '';
    }
}

function getTextAlign(u12, v12, w12) {
    let x12 = measure.measureTextSize({
        textContent: v12,
        fontSize: w12,
        constraintWidth: u12,
    });
    let y12 = measure.measureTextSize({
        textContent: v12,
        fontSize: w12,
    });
    if (getTextHeight(x12) <= getTextHeight(y12)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}

function getTextHeight(t12) {
    if (t12 && t12.height !== null && t12.height !== undefined) {
        return Number(t12.height);
    }
    return 0;
}

function resolveKeyEvent(r12, s12) {
    if (r12.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (r12.keyCode === KEYCODE_UP) {
        s12.scrollPage({ next: false });
        r12.stopPropagation();
    } else if (r12.keyCode === KEYCODE_DOWN) {
        if (s12.isAtEnd()) {
            return;
        } else {
            s12.scrollPage({ next: true });
            r12.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(l12, m12, n12, o12 = -1, p12 = undefined, q12) {
        super(l12, n12, o12, q12);
        if (typeof p12 === 'function') {
            this.paramsGenerator_ = p12;
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
        this.setInitiallyProvidedValue(m12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k12) {
        if (k12.controller !== undefined) {
            this.controller = k12.controller;
        }
        if (k12.content !== undefined) {
            this.content = k12.content;
        }
        if (k12.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = k12.fontColorWithTheme;
        }
        if (k12.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = k12.loadingProgressIconColorWithTheme;
        }
        if (k12.theme !== undefined) {
            this.theme = k12.theme;
        }
        if (k12.themeColorMode !== undefined) {
            this.themeColorMode = k12.themeColorMode;
        }
        if (k12.fontSizeScale !== undefined) {
            this.fontSizeScale = k12.fontSizeScale;
        }
        if (k12.minContentHeight !== undefined) {
            this.minContentHeight = k12.minContentHeight;
        }
    }

    updateStateVars(j12) {
    }

    purgeVariableDependenciesOnElmtId(i12) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(i12);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(i12);
        this.__fontSizeScale.purgeDependencyOnElmtId(i12);
        this.__minContentHeight.purgeDependencyOnElmtId(i12);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(h12) {
        this.controller = h12;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(g12) {
        this.__fontColorWithTheme.set(g12);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(f12) {
        this.__loadingProgressIconColorWithTheme.set(f12);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(e12) {
        this.__fontSizeScale.set(e12);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(d12) {
        this.__minContentHeight.set(d12);
    }

    initialRender() {
        this.observeComponentCreation2((b12, c12) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((z11, a12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((v11, w11) => {
                if (w11) {
                    let x11 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, v11, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1661, col: 7 });
                    ViewPU.create(x11);
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
                    x11.paramsGenerator_ = a;
                } else {
                    this.updateStateVarsOfChildByElmtId(v11, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }

    contentBuilder(m11 = null) {
        this.observeComponentCreation2((t11, u11) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((r11, s11) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((p11, q11) => {
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
        this.observeComponentCreation2((n11, o11) => {
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
    constructor(g11, h11, i11, j11 = -1, k11 = undefined, l11) {
        super(g11, i11, j11, l11);
        if (typeof k11 === 'function') {
            this.paramsGenerator_ = k11;
        }
        this.__visible = new SynchedPropertySimpleTwoWayPU(h11.visible, this, 'visible');
        this.__popover = new SynchedPropertyObjectOneWayPU(h11.popover, this, 'popover');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popover?.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(h11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f11) {
        if (f11.targetBuilder !== undefined) {
            this.targetBuilder = f11.targetBuilder;
        }
        if (f11.dialogWidth !== undefined) {
            this.dialogWidth = f11.dialogWidth;
        }
    }

    updateStateVars(e11) {
        this.__popover.reset(e11.popover);
    }

    purgeVariableDependenciesOnElmtId(d11) {
        this.__visible.purgeDependencyOnElmtId(d11);
        this.__popover.purgeDependencyOnElmtId(d11);
        this.__dialogWidth.purgeDependencyOnElmtId(d11);
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

    set visible(c11) {
        this.__visible.set(c11);
    }

    get popover() {
        return this.__popover.get();
    }

    set popover(b11) {
        this.__popover.set(b11);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(a11) {
        this.__dialogWidth.set(a11);
    }

    emptyBuilder(z10 = null) {
    }

    aboutToAppear() {
        if (this.targetBuilder === undefined || this.targetBuilder === null) {
            this.targetBuilder = this.emptyBuilder;
        }
    }

    initialRender() {
        this.observeComponentCreation2((k3, v3) => {
            Column.create();
            Column.onClick(() => {
                let r4 = display.getDefaultDisplaySync();
                let y4 = px2vp(r4.width);
                if (y4 - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
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
                onStateChange: this.popover?.onStateChange ?? ((o4) => {
                    if (!o4.isVisible) {
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