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
    constructor(s23) {
        this.colors = s23;
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
    constructor(l23, m23, n23, o23 = -1, p23 = undefined, q23) {
        super(l23, n23, o23, q23);
        if (typeof p23 === 'function') {
            this.paramsGenerator_ = p23;
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
        this.updateTextAlign = (r23) => {
            if (this.content) {
                this.textAlignment = getTextAlign(r23, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(m23);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k23) {
        if (k23.controller !== undefined) {
            this.controller = k23.controller;
        }
        if (k23.imageRes !== undefined) {
            this.imageRes = k23.imageRes;
        }
        if (k23.imageSize !== undefined) {
            this.imageSize = k23.imageSize;
        }
        if (k23.title !== undefined) {
            this.title = k23.title;
        }
        if (k23.content !== undefined) {
            this.content = k23.content;
        }
        if (k23.checkAction !== undefined) {
            this.checkAction = k23.checkAction;
        }
        if (k23.onCheckedChange !== undefined) {
            this.onCheckedChange = k23.onCheckedChange;
        }
        if (k23.checkTips !== undefined) {
            this.checkTips = k23.checkTips;
        }
        if (k23.isChecked !== undefined) {
            this.isChecked = k23.isChecked;
        }
        if (k23.primaryButton !== undefined) {
            this.primaryButton = k23.primaryButton;
        }
        if (k23.secondaryButton !== undefined) {
            this.secondaryButton = k23.secondaryButton;
        }
        if (k23.buttons !== undefined) {
            this.buttons = k23.buttons;
        }
        if (k23.textAlignment !== undefined) {
            this.textAlignment = k23.textAlignment;
        }
        if (k23.marginOffset !== undefined) {
            this.marginOffset = k23.marginOffset;
        }
        if (k23.contentScroller !== undefined) {
            this.contentScroller = k23.contentScroller;
        }
        if (k23.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = k23.fontColorWithTheme;
        }
        if (k23.theme !== undefined) {
            this.theme = k23.theme;
        }
        if (k23.themeColorMode !== undefined) {
            this.themeColorMode = k23.themeColorMode;
        }
        if (k23.fontSizeScale !== undefined) {
            this.fontSizeScale = k23.fontSizeScale;
        }
        if (k23.minContentHeight !== undefined) {
            this.minContentHeight = k23.minContentHeight;
        }
        if (k23.updateTextAlign !== undefined) {
            this.updateTextAlign = k23.updateTextAlign;
        }
        if (k23.imageIndex !== undefined) {
            this.imageIndex = k23.imageIndex;
        }
        if (k23.textIndex !== undefined) {
            this.textIndex = k23.textIndex;
        }
        if (k23.checkBoxIndex !== undefined) {
            this.checkBoxIndex = k23.checkBoxIndex;
        }
    }

    updateStateVars(j23) {
    }

    purgeVariableDependenciesOnElmtId(i23) {
        this.__imageSize.purgeDependencyOnElmtId(i23);
        this.__isChecked.purgeDependencyOnElmtId(i23);
        this.__textAlignment.purgeDependencyOnElmtId(i23);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(i23);
        this.__fontSizeScale.purgeDependencyOnElmtId(i23);
        this.__minContentHeight.purgeDependencyOnElmtId(i23);
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

    setController(h23) {
        this.controller = h23;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(g23) {
        this.__imageSize.set(g23);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(f23) {
        this.__isChecked.set(f23);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(e23) {
        this.__textAlignment.set(e23);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(d23) {
        this.__fontColorWithTheme.set(d23);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(c23) {
        this.__fontSizeScale.set(c23);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(b23) {
        this.__minContentHeight.set(b23);
    }

    initialRender() {
        this.observeComponentCreation2((z22, a23) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((v22, w22) => {
                if (w22) {
                    let x22 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, v22, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 122, col: 5 });
                    ViewPU.create(x22);
                    let y22 = () => {
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
                    x22.paramsGenerator_ = y22;
                } else {
                    this.updateStateVarsOfChildByElmtId(v22, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(q21 = null) {
        {
            this.observeComponentCreation2((r21, s21) => {
                if (s21) {
                    let t21 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((i22, j22) => {
                                ForEach.create();
                                const k22 = l22 => {
                                    const m22 = l22;
                                    this.observeComponentCreation2((n22, o22) => {
                                        If.create();
                                        if (m22 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (m22 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((t22, u22) => {
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
                                                this.observeComponentCreation2((r22, s22) => {
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
                                                this.observeComponentCreation2((p22, q22) => {
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
                                this.forEachUpdateFunction(i22, [this.imageIndex, this.textIndex,
                                    this.checkBoxIndex], k22);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, r21, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 137, col: 5 });
                    ViewPU.create(t21);
                    let u21 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((v21, w21) => {
                                    ForEach.create();
                                    const x21 = y21 => {
                                        const z21 = y21;
                                        this.observeComponentCreation2((a22, b22) => {
                                            If.create();
                                            if (z21 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (z21 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((g22, h22) => {
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
                                                    this.observeComponentCreation2((e22, f22) => {
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
                                                    this.observeComponentCreation2((c22, d22) => {
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
                                    this.forEachUpdateFunction(v21,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], x21);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    t21.paramsGenerator_ = u21;
                } else {
                    this.updateStateVarsOfChildByElmtId(r21, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(g21 = null) {
        this.observeComponentCreation2((o21, p21) => {
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
        this.observeComponentCreation2((h21, i21) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l21, m21) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((n21) => {
                            this.isChecked = n21;
                            if (this.checkAction) {
                                this.checkAction(n21);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(n21);
                            }
                        });
                        Checkbox.accessibilityLevel('yes');
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(CHECK_BOX_MARGIN_END)
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((j21, k21) => {
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

    imagePart(b21 = null) {
        this.observeComponentCreation2((e21, f21) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((c21, d21) => {
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

    textPart(j20 = null) {
        this.observeComponentCreation2((z20, a21) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((x20, y20) => {
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
        this.observeComponentCreation2((r20, s20) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v20, w20) => {
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
                    this.observeComponentCreation2((t20, u20) => {
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
        this.observeComponentCreation2((k20, l20) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p20, q20) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((m20, n20) => {
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
                        Text.onKeyEvent((o20) => {
                            if (o20) {
                                resolveKeyEvent(o20, this.contentScroller);
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
    constructor(c20, d20, e20, f20 = -1, g20 = undefined, h20) {
        super(c20, e20, f20, h20);
        if (typeof g20 === 'function') {
            this.paramsGenerator_ = g20;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (i20) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(d20.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(d20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b20) {
        if (b20.title !== undefined) {
            this.title = b20.title;
        }
        if (b20.content !== undefined) {
            this.content = b20.content;
        }
        if (b20.checkTips !== undefined) {
            this.checkTips = b20.checkTips;
        }
        if (b20.updateTextAlign !== undefined) {
            this.updateTextAlign = b20.updateTextAlign;
        }
        if (b20.dialogBuilder !== undefined) {
            this.dialogBuilder = b20.dialogBuilder;
        }
        if (b20.imageIndex !== undefined) {
            this.imageIndex = b20.imageIndex;
        }
        if (b20.textIndex !== undefined) {
            this.textIndex = b20.textIndex;
        }
        if (b20.checkBoxIndex !== undefined) {
            this.checkBoxIndex = b20.checkBoxIndex;
        }
        if (b20.childrenSize !== undefined) {
            this.childrenSize = b20.childrenSize;
        }
    }

    updateStateVars(a20) {
    }

    purgeVariableDependenciesOnElmtId(z19) {
        this.__minContentHeight.purgeDependencyOnElmtId(z19);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(y19 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(x19) {
        this.__minContentHeight.set(x19);
    }

    onPlaceChildren(q19, r19, s19) {
        let t19 = 0;
        let u19 = 0;
        for (let v19 = 0; v19 < r19.length; v19++) {
            let w19 = r19[v19];
            w19.layout({ x: t19, y: u19 });
            u19 += w19.measureResult.height;
        }
    }

    onMeasureSize(y18, z18, a19) {
        let b19 = { width: Number(a19.maxWidth), height: 0 };
        if (z18.length < this.childrenSize) {
            return b19;
        }
        let c19 = 0;
        let d19 = 0;
        if (this.checkTips !== null) {
            let n19 = z18[this.checkBoxIndex];
            let o19 = {
                maxWidth: a19.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: a19.maxHeight
            };
            let p19 = n19.measure(o19);
            d19 = p19.height;
            c19 += d19;
        }
        let e19 = z18[this.imageIndex];
        let f19 = 0;
        if (this.title !== null || this.content !== null) {
            f19 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let g19 = Number(a19.maxHeight) - d19 - f19;
        let h19 = {
            maxWidth: a19.maxWidth,
            maxHeight: g19
        };
        let i19 = e19.measure(h19);
        c19 += i19.height;
        if (this.title !== null || this.content !== null) {
            let j19 = z18[this.textIndex];
            this.updateTextAlign(b19.width);
            let k19 = Number(a19.maxHeight) - i19.height - d19;
            let l19 = {
                maxWidth: a19.maxWidth,
                maxHeight: Math.max(k19, TEXT_MIN_HEIGHT)
            };
            let m19 = j19.measure(l19);
            c19 += m19.height;
        }
        b19.height = c19;
        this.minContentHeight = Math.max(d19 + i19.height + f19, MIN_CONTENT_HEIGHT);
        return b19;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(s18, t18, u18, v18 = -1, w18 = undefined, x18) {
        super(s18, u18, v18, x18);
        if (typeof w18 === 'function') {
            this.paramsGenerator_ = w18;
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
        this.setInitiallyProvidedValue(t18);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r18) {
        if (r18.controller !== undefined) {
            this.controller = r18.controller;
        }
        if (r18.title !== undefined) {
            this.title = r18.title;
        }
        if (r18.content !== undefined) {
            this.content = r18.content;
        }
        if (r18.confirm !== undefined) {
            this.confirm = r18.confirm;
        }
        if (r18.radioContent !== undefined) {
            this.radioContent = r18.radioContent;
        }
        if (r18.buttons !== undefined) {
            this.buttons = r18.buttons;
        }
        if (r18.contentPadding !== undefined) {
            this.contentPadding = r18.contentPadding;
        }
        if (r18.isFocus !== undefined) {
            this.isFocus = r18.isFocus;
        }
        if (r18.currentFocusIndex !== undefined) {
            this.currentFocusIndex = r18.currentFocusIndex;
        }
        if (r18.radioHeight !== undefined) {
            this.radioHeight = r18.radioHeight;
        }
        if (r18.itemHeight !== undefined) {
            this.itemHeight = r18.itemHeight;
        }
        if (r18.selectedIndex !== undefined) {
            this.selectedIndex = r18.selectedIndex;
        }
        if (r18.contentBuilder !== undefined) {
            this.contentBuilder = r18.contentBuilder;
        }
        if (r18.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = r18.fontColorWithTheme;
        }
        if (r18.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = r18.dividerColorWithTheme;
        }
        if (r18.theme !== undefined) {
            this.theme = r18.theme;
        }
        if (r18.themeColorMode !== undefined) {
            this.themeColorMode = r18.themeColorMode;
        }
        if (r18.contentScroller !== undefined) {
            this.contentScroller = r18.contentScroller;
        }
        if (r18.fontSizeScale !== undefined) {
            this.fontSizeScale = r18.fontSizeScale;
        }
        if (r18.minContentHeight !== undefined) {
            this.minContentHeight = r18.minContentHeight;
        }
    }

    updateStateVars(q18) {
    }

    purgeVariableDependenciesOnElmtId(p18) {
        this.__selectedIndex.purgeDependencyOnElmtId(p18);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(p18);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(p18);
        this.__fontSizeScale.purgeDependencyOnElmtId(p18);
        this.__minContentHeight.purgeDependencyOnElmtId(p18);
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

    setController(o18) {
        this.controller = o18;
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(n18) {
        this.__selectedIndex.set(n18);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m18) {
        this.__fontColorWithTheme.set(m18);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(l18) {
        this.__dividerColorWithTheme.set(l18);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k18) {
        this.__fontSizeScale.set(k18);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(j18) {
        this.__minContentHeight.set(j18);
    }
    buildContent(j16 = null) {
        this.observeComponentCreation2((d18, e18) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((f18, g18) => {
                let h18 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (g18 > 0) {
                            this.contentScroller.scrollBy(0, h18);
                        } else if (g18 < 0) {
                            this.contentScroller.scrollBy(0, 0 - h18);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((b18, c18) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((v17, w17) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z17, a18) => {
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
                    this.observeComponentCreation2((x17, y17) => {
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
        this.observeComponentCreation2((t17, u17) => {
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
        this.observeComponentCreation2((k16, l16) => {
            ForEach.create();
            const m16 = (n16, o16) => {
                const p16 = n16;
                {
                    const q16 = (r17, s17) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r17);
                        r16(r17, s17);
                        if (!s17) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const r16 = (n17, o17) => {
                        ListItem.create(s16, true);
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
                        ListItem.onSizeChange((p17, q17) => {
                            this.itemHeight = Number(q17.height);
                        });
                    };
                    const s16 = (t16, u16) => {
                        q16(t16, u16);
                        this.observeComponentCreation2((l17, m17) => {
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
                            Column.accessibilityText(getAccessibilityText(p16.title, this.selectedIndex === o16));
                            Column.onClick(() => {
                                this.selectedIndex = o16;
                                p16.action && p16.action();
                                this.controller?.close();
                            });
                        }, Column);
                        this.observeComponentCreation2((h17, i17) => {
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
                        this.observeComponentCreation2((f17, g17) => {
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
                        this.observeComponentCreation2((d17, e17) => {
                            Text.create(p16.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((z16, a17) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === o16);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(o16));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = o16;
                                if (o16 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (o16 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((b17, c17) => {
                                this.radioHeight = Number(c17.height);
                            });
                        }, Radio);
                        Row.pop();
                        Row.pop();
                        this.observeComponentCreation2((v16, w16) => {
                            If.create();
                            if (o16 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((x16, y16) => {
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
                    this.observeComponentCreation2(r16, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(k16, this.radioContent, m16, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((h16, i16) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((d16, e16) => {
                if (e16) {
                    let f16 = new CustomDialogContentComponent(this, {
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
                    }, undefined, d16, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 530, col: 5 });
                    ViewPU.create(f16);
                    let g16 = () => {
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
                    f16.paramsGenerator_ = g16;
                } else {
                    this.updateStateVarsOfChildByElmtId(d16, {});
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
    constructor(v15, w15, x15, y15 = -1, z15 = undefined, a16) {
        super(v15, x15, y15, a16);
        if (typeof z15 === 'function') {
            this.paramsGenerator_ = z15;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(w15.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (b16) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(w15);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(u15) {
        if (u15.textIndex !== undefined) {
            this.textIndex = u15.textIndex;
        }
        if (u15.checkboxIndex !== undefined) {
            this.checkboxIndex = u15.checkboxIndex;
        }
        if (u15.updateTextAlign !== undefined) {
            this.updateTextAlign = u15.updateTextAlign;
        }
        if (u15.dialogBuilder !== undefined) {
            this.dialogBuilder = u15.dialogBuilder;
        }
    }

    updateStateVars(t15) {
    }

    purgeVariableDependenciesOnElmtId(s15) {
        this.__minContentHeight.purgeDependencyOnElmtId(s15);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(r15) {
        this.__minContentHeight.set(r15);
    }

    doNothingBuilder(q15 = null) {
    }

    onPlaceChildren(j15, k15, l15) {
        let m15 = 0;
        let n15 = 0;
        for (let o15 = 0; o15 < k15.length; o15++) {
            let p15 = k15[o15];
            p15.layout({ x: m15, y: n15 });
            n15 += p15.measureResult.height;
        }
    }

    onMeasureSize(x14, y14, z14) {
        let a15 = { width: Number(z14.maxWidth), height: 0 };
        let b15 = 2;
        if (y14.length < b15) {
            return a15;
        }
        this.updateTextAlign(a15.width);
        let c15 = 0;
        let d15 = y14[this.checkboxIndex];
        let e15 = {
            maxWidth: z14.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: z14.maxHeight
        };
        let f15 = d15.measure(e15);
        c15 += f15.height;
        let g15 = y14[this.textIndex];
        let h15 = {
            maxWidth: z14.maxWidth,
            maxHeight: Number(z14.maxHeight) - c15
        };
        let i15 = g15.measure(h15);
        c15 += i15.height;
        a15.height = c15;
        this.minContentHeight = Math.max(f15.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return a15;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(q14, r14, s14, t14 = -1, u14 = undefined, v14) {
        super(q14, s14, t14, v14);
        if (typeof u14 === 'function') {
            this.paramsGenerator_ = u14;
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
        this.updateTextAlign = (w14) => {
            if (this.content) {
                this.textAlign = getTextAlign(w14, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(r14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p14) {
        if (p14.controller !== undefined) {
            this.controller = p14.controller;
        }
        if (p14.title !== undefined) {
            this.title = p14.title;
        }
        if (p14.content !== undefined) {
            this.content = p14.content;
        }
        if (p14.checkTips !== undefined) {
            this.checkTips = p14.checkTips;
        }
        if (p14.isChecked !== undefined) {
            this.isChecked = p14.isChecked;
        }
        if (p14.primaryButton !== undefined) {
            this.primaryButton = p14.primaryButton;
        }
        if (p14.secondaryButton !== undefined) {
            this.secondaryButton = p14.secondaryButton;
        }
        if (p14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = p14.fontColorWithTheme;
        }
        if (p14.theme !== undefined) {
            this.theme = p14.theme;
        }
        if (p14.themeColorMode !== undefined) {
            this.themeColorMode = p14.themeColorMode;
        }
        if (p14.onCheckedChange !== undefined) {
            this.onCheckedChange = p14.onCheckedChange;
        }
        if (p14.contentScroller !== undefined) {
            this.contentScroller = p14.contentScroller;
        }
        if (p14.buttons !== undefined) {
            this.buttons = p14.buttons;
        }
        if (p14.textAlign !== undefined) {
            this.textAlign = p14.textAlign;
        }
        if (p14.marginOffset !== undefined) {
            this.marginOffset = p14.marginOffset;
        }
        if (p14.fontSizeScale !== undefined) {
            this.fontSizeScale = p14.fontSizeScale;
        }
        if (p14.minContentHeight !== undefined) {
            this.minContentHeight = p14.minContentHeight;
        }
        if (p14.textIndex !== undefined) {
            this.textIndex = p14.textIndex;
        }
        if (p14.checkboxIndex !== undefined) {
            this.checkboxIndex = p14.checkboxIndex;
        }
        if (p14.updateTextAlign !== undefined) {
            this.updateTextAlign = p14.updateTextAlign;
        }
    }

    updateStateVars(o14) {
    }

    purgeVariableDependenciesOnElmtId(n14) {
        this.__isChecked.purgeDependencyOnElmtId(n14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(n14);
        this.__textAlign.purgeDependencyOnElmtId(n14);
        this.__fontSizeScale.purgeDependencyOnElmtId(n14);
        this.__minContentHeight.purgeDependencyOnElmtId(n14);
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

    setController(m14) {
        this.controller = m14;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(l14) {
        this.__isChecked.set(l14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(k14) {
        this.__fontColorWithTheme.set(k14);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(j14) {
        this.__textAlign.set(j14);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(i14) {
        this.__fontSizeScale.set(i14);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(h14) {
        this.__minContentHeight.set(h14);
    }

    textBuilder(x13 = null) {
        this.observeComponentCreation2((f14, g14) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((d14, e14) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((b14, c14) => {
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
        this.observeComponentCreation2((y13, z13) => {
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
            Text.onKeyEvent((a14) => {
                if (a14) {
                    resolveKeyEvent(a14, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(p13 = null) {
        this.observeComponentCreation2((v13, w13) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((s13, t13) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((u13) => {
                this.isChecked = u13;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.accessibilityLevel('yes');
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((q13, r13) => {
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

    buildContent(o12 = null) {
        {
            this.observeComponentCreation2((p12, q12) => {
                if (q12) {
                    let r12 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((e13, f13) => {
                                ForEach.create();
                                const g13 = h13 => {
                                    const i13 = h13;
                                    this.observeComponentCreation2((j13, k13) => {
                                        If.create();
                                        if (i13 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((n13, o13) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (i13 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((l13, m13) => {
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
                                this.forEachUpdateFunction(e13, [this.textIndex, this.checkboxIndex],
                                    g13);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, p12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 744, col: 5 });
                    ViewPU.create(r12);
                    let s12 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((t12, u12) => {
                                    ForEach.create();
                                    const v12 = w12 => {
                                        const x12 = w12;
                                        this.observeComponentCreation2((y12, z12) => {
                                            If.create();
                                            if (x12 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((c13, d13) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (x12 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((a13, b13) => {
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
                                    this.forEachUpdateFunction(t12, [this.textIndex, this.checkboxIndex],
                                        v12);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    r12.paramsGenerator_ = s12;
                } else {
                    this.updateStateVarsOfChildByElmtId(p12, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        this.observeComponentCreation2((m12, n12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((i12, j12) => {
                if (j12) {
                    let k12 = new CustomDialogContentComponent(this, {
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
                    }, undefined, i12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 760, col: 5 });
                    ViewPU.create(k12);
                    let l12 = () => {
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
                    k12.paramsGenerator_ = l12;
                } else {
                    this.updateStateVarsOfChildByElmtId(i12, {});
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
    constructor(c12, d12, e12, f12 = -1, g12 = undefined, h12) {
        super(c12, e12, f12, h12);
        if (typeof g12 === 'function') {
            this.paramsGenerator_ = g12;
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
        this.setInitiallyProvidedValue(d12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b12) {
        if (b12.controller !== undefined) {
            this.controller = b12.controller;
        }
        if (b12.primaryTitle !== undefined) {
            this.primaryTitle = b12.primaryTitle;
        }
        if (b12.secondaryTitle !== undefined) {
            this.secondaryTitle = b12.secondaryTitle;
        }
        if (b12.content !== undefined) {
            this.content = b12.content;
        }
        if (b12.primaryButton !== undefined) {
            this.primaryButton = b12.primaryButton;
        }
        if (b12.secondaryButton !== undefined) {
            this.secondaryButton = b12.secondaryButton;
        }
        if (b12.buttons !== undefined) {
            this.buttons = b12.buttons;
        }
        if (b12.textAlign !== undefined) {
            this.textAlign = b12.textAlign;
        }
        if (b12.contentScroller !== undefined) {
            this.contentScroller = b12.contentScroller;
        }
        if (b12.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b12.fontColorWithTheme;
        }
        if (b12.theme !== undefined) {
            this.theme = b12.theme;
        }
        if (b12.themeColorMode !== undefined) {
            this.themeColorMode = b12.themeColorMode;
        }
        if (b12.fontSizeScale !== undefined) {
            this.fontSizeScale = b12.fontSizeScale;
        }
        if (b12.minContentHeight !== undefined) {
            this.minContentHeight = b12.minContentHeight;
        }
    }

    updateStateVars(a12) {
    }

    purgeVariableDependenciesOnElmtId(z11) {
        this.__textAlign.purgeDependencyOnElmtId(z11);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z11);
        this.__fontSizeScale.purgeDependencyOnElmtId(z11);
        this.__minContentHeight.purgeDependencyOnElmtId(z11);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(y11) {
        this.controller = y11;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(x11) {
        this.__textAlign.set(x11);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(w11) {
        this.__fontColorWithTheme.set(w11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(v11) {
        this.__fontSizeScale.set(v11);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(u11) {
        this.__minContentHeight.set(u11);
    }

    initialRender() {
        this.observeComponentCreation2((s11, t11) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((o11, p11) => {
                if (p11) {
                    let q11 = new CustomDialogContentComponent(this, {
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
                    }, undefined, o11, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 818, col: 5 });
                    ViewPU.create(q11);
                    let r11 = () => {
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
                    q11.paramsGenerator_ = r11;
                } else {
                    this.updateStateVarsOfChildByElmtId(o11, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(e11 = null) {
        this.observeComponentCreation2((m11, n11) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(this.getMargin()) });
        }, Column);
        this.observeComponentCreation2((k11, l11) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((f11, g11) => {
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
            Text.onAreaChange((i11, j11) => {
                this.updateTextAlign(Number(j11.width));
            });
            Text.onKeyEvent((h11) => {
                if (h11) {
                    resolveKeyEvent(h11, this.contentScroller);
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

    updateTextAlign(d11) {
        this.textAlign = getTextAlign(d11, this.content, `${BODY_L * this.fontSizeScale}vp`);
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
    constructor(x10, y10, z10, a11 = -1, b11 = undefined, c11) {
        super(x10, z10, a11, c11);
        if (typeof b11 === 'function') {
            this.paramsGenerator_ = b11;
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
        this.setInitiallyProvidedValue(y10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w10) {
        if (w10.controller !== undefined) {
            this.controller = w10.controller;
        }
        if (w10.primaryTitle !== undefined) {
            this.primaryTitle = w10.primaryTitle;
        }
        if (w10.secondaryTitle !== undefined) {
            this.secondaryTitle = w10.secondaryTitle;
        }
        if (w10.contentBuilder !== undefined) {
            this.contentBuilder = w10.contentBuilder;
        }
        if (w10.contentAreaPadding !== undefined) {
            this.contentAreaPadding = w10.contentAreaPadding;
        }
        if (w10.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = w10.localizedContentAreaPadding;
        }
        if (w10.buttons !== undefined) {
            this.buttons = w10.buttons;
        }
        if (w10.theme !== undefined) {
            this.theme = w10.theme;
        }
        if (w10.themeColorMode !== undefined) {
            this.themeColorMode = w10.themeColorMode;
        }
        if (w10.fontSizeScale !== undefined) {
            this.fontSizeScale = w10.fontSizeScale;
        }
        if (w10.minContentHeight !== undefined) {
            this.minContentHeight = w10.minContentHeight;
        }
    }

    updateStateVars(v10) {
    }

    purgeVariableDependenciesOnElmtId(u10) {
        this.__fontSizeScale.purgeDependencyOnElmtId(u10);
        this.__minContentHeight.purgeDependencyOnElmtId(u10);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(t10) {
        this.controller = t10;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(s10) {
        this.__fontSizeScale.set(s10);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(r10) {
        this.__minContentHeight.set(r10);
    }

    initialRender() {
        this.observeComponentCreation2((p10, q10) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((l10, m10) => {
                if (m10) {
                    let n10 = new CustomDialogContentComponent(this, {
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
                    }, undefined, l10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 914, col: 5 });
                    ViewPU.create(n10);
                    let o10 = () => {
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
                    n10.paramsGenerator_ = o10;
                } else {
                    this.updateStateVarsOfChildByElmtId(l10, {});
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
    constructor(k10) {
        super(k10);
        this.arg_ = k10;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(e10, f10, g10, h10 = -1, i10 = undefined, j10) {
        super(e10, g10, h10, j10);
        if (typeof i10 === 'function') {
            this.paramsGenerator_ = i10;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(f10.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(f10.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(f10.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(f10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d10) {
        if (d10.dialogBuilder !== undefined) {
            this.dialogBuilder = d10.dialogBuilder;
        }
        if (d10.titleIndex !== undefined) {
            this.titleIndex = d10.titleIndex;
        }
        if (d10.contentIndex !== undefined) {
            this.contentIndex = d10.contentIndex;
        }
        if (d10.buttonIndex !== undefined) {
            this.buttonIndex = d10.buttonIndex;
        }
    }

    updateStateVars(c10) {
    }

    purgeVariableDependenciesOnElmtId(b10) {
        this.__titleHeight.purgeDependencyOnElmtId(b10);
        this.__buttonHeight.purgeDependencyOnElmtId(b10);
        this.__titleMinHeight.purgeDependencyOnElmtId(b10);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(a10 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(z9) {
        this.__titleHeight.set(z9);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(y9) {
        this.__buttonHeight.set(y9);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(x9) {
        this.__titleMinHeight.set(x9);
    }

    onPlaceChildren(q9, r9, s9) {
        let t9 = 0;
        let u9 = 0;
        for (let v9 = 0; v9 < r9.length; v9++) {
            let w9 = r9[v9];
            w9.layout({ x: t9, y: u9 });
            u9 += w9.measureResult.height;
        }
    }

    onMeasureSize(c9, d9, e9) {
        let f9 = { width: Number(e9.maxWidth), height: 0 };
        let g9 = 3;
        if (d9.length < g9) {
            return f9;
        }
        let h9 = 0;
        let i9 = d9[this.titleIndex];
        let j9 = {
            maxWidth: e9.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: e9.maxHeight
        };
        let k9 = i9.measure(j9);
        this.titleHeight = k9.height;
        h9 += this.titleHeight;
        let l9 = d9[this.buttonIndex];
        let m9 = l9.measure(e9);
        this.buttonHeight = m9.height;
        h9 += this.buttonHeight;
        let n9 = d9[this.contentIndex];
        let o9 = {
            maxWidth: e9.maxWidth,
            maxHeight: Number(e9.maxHeight) - h9
        };
        let p9 = n9.measure(o9);
        h9 += p9.height;
        f9.height = h9;
        return f9;
    }

    initialRender() {
        this.dialogBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(w8, x8, y8, z8 = -1, a9 = undefined, b9) {
        super(w8, y8, z8, b9);
        if (typeof a9 === 'function') {
            this.paramsGenerator_ = a9;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(x8.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(x8.fontSizeScale, this, 'fontSizeScale');
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
        this.setInitiallyProvidedValue(x8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(v8) {
        if (v8.controller !== undefined) {
            this.controller = v8.controller;
        }
        if (v8.primaryTitle !== undefined) {
            this.primaryTitle = v8.primaryTitle;
        }
        if (v8.secondaryTitle !== undefined) {
            this.secondaryTitle = v8.secondaryTitle;
        }
        if (v8.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = v8.localizedContentAreaPadding;
        }
        if (v8.contentBuilder !== undefined) {
            this.contentBuilder = v8.contentBuilder;
        }
        if (v8.buttons !== undefined) {
            this.buttons = v8.buttons;
        }
        if (v8.contentAreaPadding !== undefined) {
            this.contentAreaPadding = v8.contentAreaPadding;
        }
        if (v8.keyIndex !== undefined) {
            this.keyIndex = v8.keyIndex;
        }
        if (v8.theme !== undefined) {
            this.theme = v8.theme;
        }
        if (v8.themeColorMode !== undefined) {
            this.themeColorMode = v8.themeColorMode;
        }
        if (v8.titleHeight !== undefined) {
            this.titleHeight = v8.titleHeight;
        }
        if (v8.buttonHeight !== undefined) {
            this.buttonHeight = v8.buttonHeight;
        }
        if (v8.contentMaxHeight !== undefined) {
            this.contentMaxHeight = v8.contentMaxHeight;
        }
        if (v8.customStyle !== undefined) {
            this.customStyle = v8.customStyle;
        }
        if (v8.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = v8.buttonMaxFontSize;
        }
        if (v8.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = v8.buttonMinFontSize;
        }
        if (v8.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = v8.primaryTitleMaxFontSize;
        }
        if (v8.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = v8.primaryTitleMinFontSize;
        }
        if (v8.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = v8.secondaryTitleMaxFontSize;
        }
        if (v8.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = v8.secondaryTitleMinFontSize;
        }
        if (v8.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = v8.primaryTitleFontColorWithTheme;
        }
        if (v8.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = v8.secondaryTitleFontColorWithTheme;
        }
        if (v8.titleTextAlign !== undefined) {
            this.titleTextAlign = v8.titleTextAlign;
        }
        if (v8.isButtonVertical !== undefined) {
            this.isButtonVertical = v8.isButtonVertical;
        }
        if (v8.titleMinHeight !== undefined) {
            this.titleMinHeight = v8.titleMinHeight;
        }
        if (v8.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = v8.isFollowingSystemFontScale;
        }
        if (v8.appMaxFontScale !== undefined) {
            this.appMaxFontScale = v8.appMaxFontScale;
        }
        if (v8.titleIndex !== undefined) {
            this.titleIndex = v8.titleIndex;
        }
        if (v8.contentIndex !== undefined) {
            this.contentIndex = v8.contentIndex;
        }
        if (v8.buttonIndex !== undefined) {
            this.buttonIndex = v8.buttonIndex;
        }
    }

    updateStateVars(u8) {
    }

    purgeVariableDependenciesOnElmtId(t8) {
        this.__minContentHeight.purgeDependencyOnElmtId(t8);
        this.__titleHeight.purgeDependencyOnElmtId(t8);
        this.__buttonHeight.purgeDependencyOnElmtId(t8);
        this.__contentMaxHeight.purgeDependencyOnElmtId(t8);
        this.__fontSizeScale.purgeDependencyOnElmtId(t8);
        this.__customStyle.purgeDependencyOnElmtId(t8);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(t8);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(t8);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(t8);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(t8);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(t8);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(t8);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(t8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(t8);
        this.__titleTextAlign.purgeDependencyOnElmtId(t8);
        this.__isButtonVertical.purgeDependencyOnElmtId(t8);
        this.__titleMinHeight.purgeDependencyOnElmtId(t8);
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

    set minContentHeight(s8) {
        this.__minContentHeight.set(s8);
    }

    defaultContentBuilder(r8 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(q8) {
        this.__titleHeight.set(q8);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(p8) {
        this.__buttonHeight.set(p8);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(o8) {
        this.__contentMaxHeight.set(o8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(n8) {
        this.__fontSizeScale.set(n8);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(m8) {
        this.__customStyle.set(m8);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(l8) {
        this.__buttonMaxFontSize.set(l8);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(k8) {
        this.__buttonMinFontSize.set(k8);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(j8) {
        this.__primaryTitleMaxFontSize.set(j8);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(i8) {
        this.__primaryTitleMinFontSize.set(i8);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(h8) {
        this.__secondaryTitleMaxFontSize.set(h8);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(g8) {
        this.__secondaryTitleMinFontSize.set(g8);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(f8) {
        this.__primaryTitleFontColorWithTheme.set(f8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(e8) {
        this.__secondaryTitleFontColorWithTheme.set(e8);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(d8) {
        this.__titleTextAlign.set(d8);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(c8) {
        this.__isButtonVertical.set(c8);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(b8) {
        this.__titleMinHeight.set(b8);
    }
    initialRender() {
        this.observeComponentCreation2((z7, a8) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((x7, y7) => {
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
        this.observeComponentCreation2((v7, w7) => {
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
            this.observeComponentCreation2((n6, o6) => {
                if (o6) {
                    let p6 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((g7, h7) => {
                                ForEach.create();
                                const i7 = j7 => {
                                    const k7 = j7;
                                    this.observeComponentCreation2((l7, m7) => {
                                        If.create();
                                        if (k7 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((t7, u7) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (k7 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((r7, s7) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((p7, q7) => {
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
                                                this.observeComponentCreation2((n7, o7) => {
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
                                this.forEachUpdateFunction(g7, [this.titleIndex, this.contentIndex,
                                    this.buttonIndex], i7);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, n6, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1052, col: 11 });
                    ViewPU.create(p6);
                    let q6 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((r6, s6) => {
                                    ForEach.create();
                                    const t6 = u6 => {
                                        const v6 = u6;
                                        this.observeComponentCreation2((w6, x6) => {
                                            If.create();
                                            if (v6 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((e7, f7) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (v6 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((c7, d7) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((a7, b7) => {
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
                                                    this.observeComponentCreation2((y6, z6) => {
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
                                    this.forEachUpdateFunction(r6, [this.titleIndex, this.contentIndex,
                                        this.buttonIndex], t6);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    p6.paramsGenerator_ = q6;
                } else {
                    this.updateStateVarsOfChildByElmtId(n6, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(e6, f6, g6) {
        let h6 = { width: e6.width, height: e6.height };
        let i6 = Number(g6.maxWidth);
        let j6 = Number(g6.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(i6 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let k6 = 0;
        f6.forEach((l6) => {
            this.contentMaxHeight = '100%';
            let m6 = l6.measure(g6);
            if (j6 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                m6 = l6.measure(g6);
            }
            k6 += m6.height;
        });
        h6.height = k6;
        h6.width = i6;
        return h6;
    }

    aboutToAppear() {
        let c6 = this.getUIContext();
        this.isFollowingSystemFontScale = c6.isFollowingSystemFontScale();
        this.appMaxFontScale = c6.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let d6 = this.controller;
            if (d6.arg_ && d6.arg_.customStyle && d6.arg_.customStyle === true) {
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
            let a6 = this.getUIContext();
            let b6 = a6.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(b6, this.appMaxFontScale);
        } catch (x5) {
            let y5 = x5.code;
            let z5 = x5.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${y5}, message: ${z5}`);
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

    titleBuilder(i5 = null) {
        this.observeComponentCreation2((v5, w5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((t5, u5) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((r5, s5) => {
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
        this.observeComponentCreation2((n5, o5) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p5, q5) => {
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
        this.observeComponentCreation2((l5, m5) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((j5, k5) => {
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
        let h5 = ALERT_TITLE_ALIGNMENT;
        if (h5 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        }
        else if (h5 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        }
        else if (h5 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        }
        else if (h5 === TextAlign.JUSTIFY) {
            this.titleTextAlign = TextAlign.JUSTIFY;
        }
        else {
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

    ButtonBuilder(a5 = null) {
        this.observeComponentCreation2((f5, g5) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((b5, c5) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d5, e5) => {
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
    buildSingleButton(o4, p4 = null) {
        this.observeComponentCreation2((q4, r4) => {
            If.create();
            if (this.isNewPropertiesHighPriority(o4)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y4, z4) => {
                        Button.createWithLabel(o4.value);
                        __Button__setButtonProperties(o4, this.controller);
                        Button.role(o4.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (o4.background !== undefined && o4.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w4, x4) => {
                        Button.createWithLabel(o4.value);
                        __Button__setButtonProperties(o4, this.controller);
                        Button.backgroundColor(o4.background);
                        Button.fontColor(o4.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (o4.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((u4, v4) => {
                        Button.createWithLabel(o4.value);
                        __Button__setButtonProperties(o4, this.controller);
                        Button.backgroundColor(o4.background);
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
                    this.observeComponentCreation2((s4, t4) => {
                        Button.createWithLabel(o4.value);
                        __Button__setButtonProperties(o4, this.controller);
                        Button.fontColor(o4.fontColor);
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

    buildHorizontalAlignButtons(d4 = null) {
        this.observeComponentCreation2((e4, f4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m4, n4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((g4, h4) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k4, l4) => {
                                    Row.create();
                                    Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                                    Row.justifyContent(FlexAlign.Center);
                                }, Row);
                                this.observeComponentCreation2((i4, j4) => {
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

    buildVerticalAlignButtons(r3 = null) {
        this.observeComponentCreation2((s3, t3) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b4, c4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((u3, v3) => {
                        ForEach.create();
                        const w3 = (y3, z3) => {
                            const a4 = y3;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - z3 - 1 : z3);
                        };
                        this.forEachUpdateFunction(u3, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT),
                            w3, (x3) => x3.value.toString(), true, false);
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

    /**
     * is button buttonStyle and role properties high priority
     *
     * @param buttonOptions button properties
     * @returns check result
     */
    isNewPropertiesHighPriority(q3) {
        if (q3.role === ButtonRole.ERROR) {
            return true;
        }
        if (q3.buttonStyle !== undefined &&
            q3.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (q3.background === undefined && q3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(g3, h3 = null) {
        this.observeComponentCreation2((i3, j3) => {
            If.create();
            if (this.buttons && this.buttons[g3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o3, p3) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[g3]);
                    Row.pop();
                    this.observeComponentCreation2((k3, l3) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - g3 - 1 : g3) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m3, n3) => {
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

    isVerticalAlignButton(b3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let c3 = false;
            let d3 = vp2px(b3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((e3) => {
                let f3 = measure.measureTextSize({
                    textContent: e3.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(f3.width) > d3) {
                    c3 = true;
                }
            });
            return c3;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(z2, a3) {
    Button.onClick(() => {
        if (z2.action) {
            z2.action();
        }
        a3?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(z2.buttonStyle ?? ALERT_BUTTON_STYLE);
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.ROUNDED_RECTANGLE);
}

function getNumberByResourceId(s2, t2, u2) {
    try {
        let y2 = resourceManager.getSystemResourceManager().getNumber(s2);
        if (y2 > 0 || u2) {
            return y2;
        } else {
            return t2;
        }
    } catch (v2) {
        let w2 = v2.code;
        let x2 = v2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${w2}, message: ${x2}`);
        return t2;
    }
}
function getEnumNumberByResourceId(m2, n2) {
    try {
        let r2 = getContext().resourceManager.getNumber(m2);
        if (r2 > 0) {
            return r2;
        } else {
            return n2;
        }
    } catch (o2) {
        let p2 = o2.code;
        let q2 = o2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${p2}, message: ${q2}`);
        return n2;
    }
}

function getAccessibilityText(f2, g2) {
    try {
        let k2 = getContext().resourceManager.getStringSync(125833934);
        let w3 = '';
        if (typeof f2 === 'string') {
            w3 = f2;
        }
        else {
            w3 = getContext().resourceManager.getStringSync(f2);
        }
        return g2 ? `${k2},${w3}` : w3;
    }
    catch (h2) {
        let i2 = h2.code;
        let j2 = h2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${i2}, message: ${j2}`);
        return '';
    }
}

function getTextAlign(a2, b2, c2) {
    let d2 = measure.measureTextSize({
        textContent: b2,
        fontSize: c2,
        constraintWidth: a2,
    });
    let e2 = measure.measureTextSize({
        textContent: b2,
        fontSize: c2,
    });
    if (getTextHeight(d2) <= getTextHeight(e2)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}


function getTextHeight(z1) {
    if (z1 && z1.height !== null && z1.height !== undefined) {
        return Number(z1.height);
    }
    return 0;
}

function resolveKeyEvent(x1, y1) {
    if (x1.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (x1.keyCode === KEYCODE_UP) {
        y1.scrollPage({ next: false });
        x1.stopPropagation();
    } else if (x1.keyCode === KEYCODE_DOWN) {
        if (y1.isAtEnd()) {
            return;
        } else {
            y1.scrollPage({ next: true });
            x1.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(r1, s1, t1, u1 = -1, v1 = undefined, w1) {
        super(r1, t1, u1, w1);
        if (typeof v1 === 'function') {
            this.paramsGenerator_ = v1;
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
        this.setInitiallyProvidedValue(s1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q1) {
        if (q1.controller !== undefined) {
            this.controller = q1.controller;
        }
        if (q1.content !== undefined) {
            this.content = q1.content;
        }
        if (q1.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q1.fontColorWithTheme;
        }
        if (q1.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = q1.loadingProgressIconColorWithTheme;
        }
        if (q1.theme !== undefined) {
            this.theme = q1.theme;
        }
        if (q1.themeColorMode !== undefined) {
            this.themeColorMode = q1.themeColorMode;
        }
        if (q1.fontSizeScale !== undefined) {
            this.fontSizeScale = q1.fontSizeScale;
        }
        if (q1.minContentHeight !== undefined) {
            this.minContentHeight = q1.minContentHeight;
        }
    }

    updateStateVars(p1) {
    }

    purgeVariableDependenciesOnElmtId(o1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(o1);
        this.__fontSizeScale.purgeDependencyOnElmtId(o1);
        this.__minContentHeight.purgeDependencyOnElmtId(o1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(n1) {
        this.controller = n1;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m1) {
        this.__fontColorWithTheme.set(m1);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(l1) {
        this.__loadingProgressIconColorWithTheme.set(l1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k1) {
        this.__fontSizeScale.set(k1);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(j1) {
        this.__minContentHeight.set(j1);
    }

    initialRender() {
        this.observeComponentCreation2((h1, i1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((f1, g1) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((b1, c1) => {
                if (c1) {
                    let d1 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, b1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1656, col: 7 });
                    ViewPU.create(d1);
                    let e1 = () => {
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
                    d1.paramsGenerator_ = e1;
                } else {
                    this.updateStateVarsOfChildByElmtId(b1, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }

    contentBuilder(s = null) {
        this.observeComponentCreation2((z, a1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((x, y) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((v, w) => {
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
        this.observeComponentCreation2((t, u) => {
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
    constructor(m, n, o, p = -1, q = undefined, r) {
        super(m, o, p, r);
        if (typeof q === 'function') {
            this.paramsGenerator_ = q;
        }
        this.__visible = new SynchedPropertySimpleTwoWayPU(n.visible, this, 'visible');
        this.__popover = new SynchedPropertyObjectOneWayPU(n.popover, this, 'popover');
        this.targetBuilder = undefined;
        this.__dialogWidth = new ObservedPropertyObjectPU(this.popover?.width, this, 'dialogWidth');
        this.setInitiallyProvidedValue(n);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l) {
        if (l.targetBuilder !== undefined) {
            this.targetBuilder = l.targetBuilder;
        }
        if (l.dialogWidth !== undefined) {
            this.dialogWidth = l.dialogWidth;
        }
    }

    updateStateVars(k) {
        this.__popover.reset(k.popover);
    }

    purgeVariableDependenciesOnElmtId(j) {
        this.__visible.purgeDependencyOnElmtId(j);
        this.__popover.purgeDependencyOnElmtId(j);
        this.__dialogWidth.purgeDependencyOnElmtId(j);
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

    set visible(i) {
        this.__visible.set(i);
    }

    get popover() {
        return this.__popover.get();
    }

    set popover(h) {
        this.__popover.set(h);
    }

    get dialogWidth() {
        return this.__dialogWidth.get();
    }

    set dialogWidth(g) {
        this.__dialogWidth.set(g);
    }

    emptyBuilder(f = null) {
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
                let d = display.getDefaultDisplaySync();
                let e = px2vp(d.width);
                if (e - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
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