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
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

class CustomThemeImpl {
    constructor(t29) {
        this.colors = t29;
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
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042) ?? 400;
const BUTTON_HORIZONTAL_MARGIN = getNumberByResourceId(125831054) ?? 16;
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927) ?? 16;
const BUTTON_HORIZONTAL_SPACE = getNumberByResourceId(125831051) ?? 8;
const BODY_L = getNumberByResourceId(125830970) ?? 16;
const BODY_S = getNumberByResourceId(125830972) ?? 12;
const TITLE_S = getNumberByResourceId(125830966) ?? 20;
const SUBTITLE_S = getNumberByResourceId(125830969) ?? 14;
const PADDING_LEVEL_8 = getNumberByResourceId(125830927);
const DIALOG_DIVIDER_SHOW = getNumberByResourceId(125831202);
const ALERT_BUTTON_STYLE = getNumberByResourceId(125831085);
const ALERT_TITLE_ALIGNMENT = getEnumNumberByResourceId(125831126);

export class TipsDialog extends ViewPU {
    constructor(l29, m29, n29, o29 = -1, p29 = undefined, q29) {
        super(l29, n29, o29, q29);
        if (typeof p29 === 'function') {
            this.paramsGenerator_ = p29;
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
        this.updateTextAlign = (s29) => {
            if (this.content) {
                this.textAlignment = getTextAlign(s29, this.content, `${BODY_L}fp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.setInitiallyProvidedValue(m29);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k29) {
        if (k29.controller !== undefined) {
            this.controller = k29.controller;
        }
        if (k29.imageRes !== undefined) {
            this.imageRes = k29.imageRes;
        }
        if (k29.imageSize !== undefined) {
            this.imageSize = k29.imageSize;
        }
        if (k29.title !== undefined) {
            this.title = k29.title;
        }
        if (k29.content !== undefined) {
            this.content = k29.content;
        }
        if (k29.checkAction !== undefined) {
            this.checkAction = k29.checkAction;
        }
        if (k29.onCheckedChange !== undefined) {
            this.onCheckedChange = k29.onCheckedChange;
        }
        if (k29.checkTips !== undefined) {
            this.checkTips = k29.checkTips;
        }
        if (k29.isChecked !== undefined) {
            this.isChecked = k29.isChecked;
        }
        if (k29.primaryButton !== undefined) {
            this.primaryButton = k29.primaryButton;
        }
        if (k29.secondaryButton !== undefined) {
            this.secondaryButton = k29.secondaryButton;
        }
        if (k29.buttons !== undefined) {
            this.buttons = k29.buttons;
        }
        if (k29.textAlignment !== undefined) {
            this.textAlignment = k29.textAlignment;
        }
        if (k29.marginOffset !== undefined) {
            this.marginOffset = k29.marginOffset;
        }
        if (k29.contentScroller !== undefined) {
            this.contentScroller = k29.contentScroller;
        }
        if (k29.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = k29.fontColorWithTheme;
        }
        if (k29.theme !== undefined) {
            this.theme = k29.theme;
        }
        if (k29.themeColorMode !== undefined) {
            this.themeColorMode = k29.themeColorMode;
        }
        if (k29.fontSizeScale !== undefined) {
            this.fontSizeScale = k29.fontSizeScale;
        }
        if (k29.minContentHeight !== undefined) {
            this.minContentHeight = k29.minContentHeight;
        }
        if (k29.updateTextAlign !== undefined) {
            this.updateTextAlign = k29.updateTextAlign;
        }
        if (k29.imageIndex !== undefined) {
            this.imageIndex = k29.imageIndex;
        }
        if (k29.textIndex !== undefined) {
            this.textIndex = k29.textIndex;
        }
        if (k29.checkBoxIndex !== undefined) {
            this.checkBoxIndex = k29.checkBoxIndex;
        }
    }

    updateStateVars(j29) {
    }

    purgeVariableDependenciesOnElmtId(i29) {
        this.__imageSize.purgeDependencyOnElmtId(i29);
        this.__isChecked.purgeDependencyOnElmtId(i29);
        this.__textAlignment.purgeDependencyOnElmtId(i29);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(i29);
        this.__fontSizeScale.purgeDependencyOnElmtId(i29);
        this.__minContentHeight.purgeDependencyOnElmtId(i29);
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

    setController(h29) {
        this.controller = h29;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(g29) {
        this.__imageSize.set(g29);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(f29) {
        this.__isChecked.set(f29);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(e29) {
        this.__textAlignment.set(e29);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(d29) {
        this.__fontColorWithTheme.set(d29);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(c29) {
        this.__fontSizeScale.set(c29);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(b29) {
        this.__minContentHeight.set(b29);
    }

    initialRender() {
        this.observeComponentCreation2((z28, a29) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((t28, u28) => {
                if (u28) {
                    let v28 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, t28, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 118, col: 5 });
                    ViewPU.create(v28);
                    let w28 = () => {
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
                    v28.paramsGenerator_ = w28;
                } else {
                    this.updateStateVarsOfChildByElmtId(t28, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(d27 = null) {
        {
            this.observeComponentCreation2((f27, g27) => {
                if (g27) {
                    let h27 = new TipsDialogContentLayout(d27 ? d27 : this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((c28, d28) => {
                                ForEach.create();
                                const e28 = g28 => {
                                    const h28 = g28;
                                    this.observeComponentCreation2((j28, k28) => {
                                        If.create();
                                        if (h28 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)(d27 ? d27 : this);
                                            });
                                        } else if (h28 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((o28, p28) => {
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
                                                this.textPart.bind(this)(d27 ? d27 : this);
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.checkBoxPart.bind(this)(d27 ? d27 : this);
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(c28, [this.imageIndex, this.textIndex, this.checkBoxIndex],
                                    e28);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, f27, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 133, col: 5 });
                    ViewPU.create(h27);
                    let i27 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((m27, n27) => {
                                    ForEach.create();
                                    const o27 = q27 => {
                                        const r27 = q27;
                                        this.observeComponentCreation2((t27, u27) => {
                                            If.create();
                                            if (r27 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)(d27 ? d27 : this);
                                                });
                                            } else if (r27 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((y27, z27) => {
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
                                                    this.textPart.bind(this)(d27 ? d27 : this);
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.checkBoxPart.bind(this)(d27 ? d27 : this);
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(m27,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], o27);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    h27.paramsGenerator_ = i27;
                } else {
                    this.updateStateVarsOfChildByElmtId(f27, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }

    checkBoxPart(l26 = null) {
        this.observeComponentCreation2((b27, c27) => {
            Row.create();
            Row.padding({ top: 8, bottom: 8 });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((o26, p26) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x26, y26) => {
                        Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((a27) => {
                            this.isChecked = a27;
                            if (this.checkAction) {
                                this.checkAction(a27);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(a27);
                            }
                        });
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
                    this.observeComponentCreation2((u26, v26) => {
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
                        Text.onClick(() => {
                            this.isChecked = !this.isChecked;
                            if (this.checkAction) {
                                this.checkAction(this.isChecked);
                            }
                        });
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

    imagePart(e26 = null) {
        this.observeComponentCreation2((j26, k26) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((h26, i26) => {
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

    textPart(z24 = null) {
        this.observeComponentCreation2((c26, d26) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((a26, b26) => {
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
        this.observeComponentCreation2((q25, r25) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y25, z25) => {
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
                    this.observeComponentCreation2((w25, x25) => {
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
        this.observeComponentCreation2((e25, f25) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o25, p25) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((k25, l25) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((n25) => {
                            if (n25) {
                                resolveKeyEvent(n25, this.contentScroller);
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
    constructor(r24, s24, t24, u24 = -1, v24 = undefined, w24) {
        super(r24, t24, u24, w24);
        if (typeof v24 === 'function') {
            this.paramsGenerator_ = v24;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (y24) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(s24.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(s24);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q24) {
        if (q24.title !== undefined) {
            this.title = q24.title;
        }
        if (q24.content !== undefined) {
            this.content = q24.content;
        }
        if (q24.checkTips !== undefined) {
            this.checkTips = q24.checkTips;
        }
        if (q24.updateTextAlign !== undefined) {
            this.updateTextAlign = q24.updateTextAlign;
        }
        if (q24.dialogBuilder !== undefined) {
            this.dialogBuilder = q24.dialogBuilder;
        }
        if (q24.imageIndex !== undefined) {
            this.imageIndex = q24.imageIndex;
        }
        if (q24.textIndex !== undefined) {
            this.textIndex = q24.textIndex;
        }
        if (q24.checkBoxIndex !== undefined) {
            this.checkBoxIndex = q24.checkBoxIndex;
        }
        if (q24.childrenSize !== undefined) {
            this.childrenSize = q24.childrenSize;
        }
    }

    updateStateVars(p24) {
    }

    purgeVariableDependenciesOnElmtId(o24) {
        this.__minContentHeight.purgeDependencyOnElmtId(o24);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(n24 = null) {
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(m24) {
        this.__minContentHeight.set(m24);
    }

    onPlaceChildren(f24, g24, h24) {
        let i24 = 0;
        let j24 = 0;
        for (let k24 = 0; k24 < g24.length; k24++) {
            let l24 = g24[k24];
            l24.layout({ x: i24, y: j24 });
            j24 += l24.measureResult.height;
        }
    }

    onMeasureSize(n23, o23, p23) {
        let q23 = { width: Number(p23.maxWidth), height: 0 };
        if (o23.length < this.childrenSize) {
            return q23;
        }
        let r23 = 0;
        let s23 = 0;
        if (this.checkTips !== null) {
            let c24 = o23[this.checkBoxIndex];
            let d24 = {
                maxWidth: p23.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: p23.maxHeight
            };
            let e24 = c24.measure(d24);
            s23 = e24.height;
            r23 += s23;
        }
        let t23 = o23[this.imageIndex];
        let u23 = 0;
        if (this.title !== null || this.content !== null) {
            u23 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let v23 = Number(p23.maxHeight) - s23 - u23;
        let w23 = {
            maxWidth: p23.maxWidth,
            maxHeight: v23
        };
        let x23 = t23.measure(w23);
        r23 += x23.height;
        if (this.title !== null || this.content !== null) {
            let y23 = o23[this.textIndex];
            this.updateTextAlign(q23.width);
            let z23 = Number(p23.maxHeight) - x23.height - s23;
            let a24 = {
                maxWidth: p23.maxWidth,
                maxHeight: Math.max(z23, TEXT_MIN_HEIGHT)
            };
            let b24 = y23.measure(a24);
            r23 += b24.height;
        }
        q23.height = r23;
        this.minContentHeight = Math.max(s23 + x23.height + u23, MIN_CONTENT_HEIGHT);
        return q23;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(h23, i23, j23, k23 = -1, l23 = undefined, m23) {
        super(h23, j23, k23, m23);
        if (typeof l23 === 'function') {
            this.paramsGenerator_ = l23;
        }
        this.controller = undefined;
        this.title = '';
        this.content = '';
        this.selectedIndex = -1;
        this.confirm = null;
        this.radioContent = [];
        this.buttons = [];
        this.contentPadding = undefined;
        this.isFocus = false;
        this.currentFocusIndex = -1;
        this.radioHeight = 0;
        this.itemHeight = 0;
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
        this.setInitiallyProvidedValue(i23);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g23) {
        if (g23.controller !== undefined) {
            this.controller = g23.controller;
        }
        if (g23.title !== undefined) {
            this.title = g23.title;
        }
        if (g23.content !== undefined) {
            this.content = g23.content;
        }
        if (g23.selectedIndex !== undefined) {
            this.selectedIndex = g23.selectedIndex;
        }
        if (g23.confirm !== undefined) {
            this.confirm = g23.confirm;
        }
        if (g23.radioContent !== undefined) {
            this.radioContent = g23.radioContent;
        }
        if (g23.buttons !== undefined) {
            this.buttons = g23.buttons;
        }
        if (g23.contentPadding !== undefined) {
            this.contentPadding = g23.contentPadding;
        }
        if (g23.isFocus !== undefined) {
            this.isFocus = g23.isFocus;
        }
        if (g23.currentFocusIndex !== undefined) {
            this.currentFocusIndex = g23.currentFocusIndex;
        }
        if (g23.radioHeight !== undefined) {
            this.radioHeight = g23.radioHeight;
        }
        if (g23.itemHeight !== undefined) {
            this.itemHeight = g23.itemHeight;
        }
        if (g23.contentBuilder !== undefined) {
            this.contentBuilder = g23.contentBuilder;
        }
        if (g23.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = g23.fontColorWithTheme;
        }
        if (g23.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = g23.dividerColorWithTheme;
        }
        if (g23.theme !== undefined) {
            this.theme = g23.theme;
        }
        if (g23.themeColorMode !== undefined) {
            this.themeColorMode = g23.themeColorMode;
        }
        if (g23.contentScroller !== undefined) {
            this.contentScroller = g23.contentScroller;
        }
        if (g23.fontSizeScale !== undefined) {
            this.fontSizeScale = g23.fontSizeScale;
        }
        if (g23.minContentHeight !== undefined) {
            this.minContentHeight = g23.minContentHeight;
        }
    }

    updateStateVars(f23) {
    }

    purgeVariableDependenciesOnElmtId(e23) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(e23);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(e23);
        this.__fontSizeScale.purgeDependencyOnElmtId(e23);
        this.__minContentHeight.purgeDependencyOnElmtId(e23);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(d23) {
        this.controller = d23;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(c23) {
        this.__fontColorWithTheme.set(c23);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(b23) {
        this.__dividerColorWithTheme.set(b23);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(a23) {
        this.__fontSizeScale.set(a23);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(z22) {
        this.__minContentHeight.set(z22);
    }

    buildContent(a20 = null) {
        this.observeComponentCreation2((t22, u22) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((w22, x22) => {
                let y22 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (x22 > 0) {
                            this.contentScroller.scrollBy(0, y22);
                        } else if (x22 < 0) {
                            this.contentScroller.scrollBy(0, 0 - y22);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((r22, s22) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((h22, i22) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p22, q22) => {
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
                    this.observeComponentCreation2((n22, o22) => {
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
        this.observeComponentCreation2((e22, f22) => {
            List.create({ space: 1 });
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
        this.observeComponentCreation2((g20, h20) => {
            ForEach.create();
            const i20 = (k20, l20) => {
                const m20 = k20;
                {
                    const n20 = (c22, d22) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c22);
                        o20(c22, d22);
                        if (!d22) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const o20 = (x21, y21) => {
                        ListItem.create(p20, true);
                        ListItem.onSizeChange((a22, b22) => {
                            this.itemHeight = Number(b22.height);
                        });
                    };
                    const p20 = (t20, u20) => {
                        n20(t20, u20);
                        this.observeComponentCreation2((v21, w21) => {
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
                        this.observeComponentCreation2((s21, t21) => {
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
                            Button.onClick(() => {
                                m20.action && m20.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((q21, r21) => {
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
                        this.observeComponentCreation2((o21, p21) => {
                            Text.create(m20.title);
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
                        this.observeComponentCreation2((i21, j21) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === l20);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(l20));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = l20;
                                if (l20 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (l20 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((m21, n21) => {
                                this.radioHeight = Number(n21.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((b21, c21) => {
                            If.create();
                            if (l20 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((g21, h21) => {
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
                    this.observeComponentCreation2(o20, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(g20, this.radioContent, i20, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((y19, z19) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((s19, t19) => {
                if (t19) {
                    let u19 = new CustomDialogContentComponent(this, {
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
                    }, undefined, s19, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 495, col: 5 });
                    ViewPU.create(u19);
                    let v19 = () => {
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
                    u19.paramsGenerator_ = v19;
                } else {
                    this.updateStateVarsOfChildByElmtId(s19, {});
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
    constructor(i19, j19, k19, l19 = -1, m19 = undefined, n19) {
        super(i19, k19, l19, n19);
        if (typeof m19 === 'function') {
            this.paramsGenerator_ = m19;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(j19.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (p19) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(j19);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h19) {
        if (h19.textIndex !== undefined) {
            this.textIndex = h19.textIndex;
        }
        if (h19.checkboxIndex !== undefined) {
            this.checkboxIndex = h19.checkboxIndex;
        }
        if (h19.updateTextAlign !== undefined) {
            this.updateTextAlign = h19.updateTextAlign;
        }
        if (h19.dialogBuilder !== undefined) {
            this.dialogBuilder = h19.dialogBuilder;
        }
    }

    updateStateVars(g19) {
    }

    purgeVariableDependenciesOnElmtId(f19) {
        this.__minContentHeight.purgeDependencyOnElmtId(f19);
    }

    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(e19) {
        this.__minContentHeight.set(e19);
    }

    doNothingBuilder(d19 = null) {
    }

    onPlaceChildren(w18, x18, y18) {
        let z18 = 0;
        let a19 = 0;
        for (let b19 = 0; b19 < x18.length; b19++) {
            let c19 = x18[b19];
            c19.layout({ x: z18, y: a19 });
            a19 += c19.measureResult.height;
        }
    }

    onMeasureSize(k18, l18, m18) {
        let n18 = { width: Number(m18.maxWidth), height: 0 };
        let o18 = 2;
        if (l18.length < o18) {
            return n18;
        }
        this.updateTextAlign(n18.width);
        let p18 = 0;
        let q18 = l18[this.checkboxIndex];
        let r18 = {
            maxWidth: m18.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: m18.maxHeight
        };
        let s18 = q18.measure(r18);
        p18 += s18.height;
        let t18 = l18[this.textIndex];
        let u18 = {
            maxWidth: m18.maxWidth,
            maxHeight: Number(m18.maxHeight) - p18
        };
        let v18 = t18.measure(u18);
        p18 += v18.height;
        n18.height = p18;
        this.minContentHeight = Math.max(s18.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return n18;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(c18, d18, e18, f18 = -1, g18 = undefined, h18) {
        super(c18, e18, f18, h18);
        if (typeof g18 === 'function') {
            this.paramsGenerator_ = g18;
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
        this.updateTextAlign = (j18) => {
            if (this.content) {
                this.textAlign = getTextAlign(j18, this.content, `${BODY_L}fp`);
            }
        };
        this.setInitiallyProvidedValue(d18);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b18) {
        if (b18.controller !== undefined) {
            this.controller = b18.controller;
        }
        if (b18.title !== undefined) {
            this.title = b18.title;
        }
        if (b18.content !== undefined) {
            this.content = b18.content;
        }
        if (b18.checkTips !== undefined) {
            this.checkTips = b18.checkTips;
        }
        if (b18.isChecked !== undefined) {
            this.isChecked = b18.isChecked;
        }
        if (b18.primaryButton !== undefined) {
            this.primaryButton = b18.primaryButton;
        }
        if (b18.secondaryButton !== undefined) {
            this.secondaryButton = b18.secondaryButton;
        }
        if (b18.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b18.fontColorWithTheme;
        }
        if (b18.theme !== undefined) {
            this.theme = b18.theme;
        }
        if (b18.themeColorMode !== undefined) {
            this.themeColorMode = b18.themeColorMode;
        }
        if (b18.onCheckedChange !== undefined) {
            this.onCheckedChange = b18.onCheckedChange;
        }
        if (b18.contentScroller !== undefined) {
            this.contentScroller = b18.contentScroller;
        }
        if (b18.buttons !== undefined) {
            this.buttons = b18.buttons;
        }
        if (b18.textAlign !== undefined) {
            this.textAlign = b18.textAlign;
        }
        if (b18.marginOffset !== undefined) {
            this.marginOffset = b18.marginOffset;
        }
        if (b18.fontSizeScale !== undefined) {
            this.fontSizeScale = b18.fontSizeScale;
        }
        if (b18.minContentHeight !== undefined) {
            this.minContentHeight = b18.minContentHeight;
        }
        if (b18.textIndex !== undefined) {
            this.textIndex = b18.textIndex;
        }
        if (b18.checkboxIndex !== undefined) {
            this.checkboxIndex = b18.checkboxIndex;
        }
        if (b18.updateTextAlign !== undefined) {
            this.updateTextAlign = b18.updateTextAlign;
        }
    }

    updateStateVars(a18) {
    }

    purgeVariableDependenciesOnElmtId(z17) {
        this.__isChecked.purgeDependencyOnElmtId(z17);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z17);
        this.__textAlign.purgeDependencyOnElmtId(z17);
        this.__fontSizeScale.purgeDependencyOnElmtId(z17);
        this.__minContentHeight.purgeDependencyOnElmtId(z17);
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

    setController(y17) {
        this.controller = y17;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(x17) {
        this.__isChecked.set(x17);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(w17) {
        this.__fontColorWithTheme.set(w17);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(v17) {
        this.__textAlign.set(v17);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(u17) {
        this.__fontSizeScale.set(u17);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(t17) {
        this.__minContentHeight.set(t17);
    }

    textBuilder(e17 = null) {
        this.observeComponentCreation2((r17, s17) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((p17, q17) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((n17, o17) => {
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
        this.observeComponentCreation2((j17, k17) => {
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
            Text.onKeyEvent((m17) => {
                if (m17) {
                    resolveKeyEvent(m17, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    checkBoxBuilder(r16 = null) {
        this.observeComponentCreation2((c17, d17) => {
            Row.create();
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((y16, z16) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((b17) => {
                this.isChecked = b17;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((v16, w16) => {
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
            Text.onClick(() => {
                this.isChecked = !this.isChecked;
            });
        }, Text);
        Text.pop();
        Row.pop();
    }

    buildContent(j15 = null) {
        {
            this.observeComponentCreation2((l15, m15) => {
                if (m15) {
                    let n15 = new ConfirmDialogContentLayout(j15 ? j15 : this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((f16, g16) => {
                                ForEach.create();
                                const h16 = j16 => {
                                    const k16 = j16;
                                    this.observeComponentCreation2((m16, n16) => {
                                        If.create();
                                        if (k16 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.textBuilder.bind(this)(j15 ? j15 : this);
                                            });
                                        } else if (k16 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.checkBoxBuilder.bind(this)(j15 ? j15 : this);
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(f16, [this.textIndex, this.checkboxIndex], h16);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, l15, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 696, col: 5 });
                    ViewPU.create(n15);
                    let o15 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((s15, t15) => {
                                    ForEach.create();
                                    const u15 = w15 => {
                                        const x15 = w15;
                                        this.observeComponentCreation2((z15, a16) => {
                                            If.create();
                                            if (x15 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.textBuilder.bind(this)(j15 ? j15 : this);
                                                });
                                            } else if (x15 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.checkBoxBuilder.bind(this)(j15 ? j15 : this);
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(s15, [this.textIndex, this.checkboxIndex], u15);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    n15.paramsGenerator_ = o15;
                } else {
                    this.updateStateVarsOfChildByElmtId(l15, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }

    initialRender() {
        this.observeComponentCreation2((h15, i15) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((b15, c15) => {
                if (c15) {
                    let d15 = new CustomDialogContentComponent(this, {
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
                    }, undefined, b15, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 708, col: 5 });
                    ViewPU.create(d15);
                    let e15 = () => {
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
                    d15.paramsGenerator_ = e15;
                } else {
                    this.updateStateVarsOfChildByElmtId(b15, {});
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
    constructor(t14, u14, v14, w14 = -1, x14 = undefined, y14) {
        super(t14, v14, w14, y14);
        if (typeof x14 === 'function') {
            this.paramsGenerator_ = x14;
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
        this.setInitiallyProvidedValue(u14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s14) {
        if (s14.controller !== undefined) {
            this.controller = s14.controller;
        }
        if (s14.primaryTitle !== undefined) {
            this.primaryTitle = s14.primaryTitle;
        }
        if (s14.secondaryTitle !== undefined) {
            this.secondaryTitle = s14.secondaryTitle;
        }
        if (s14.content !== undefined) {
            this.content = s14.content;
        }
        if (s14.primaryButton !== undefined) {
            this.primaryButton = s14.primaryButton;
        }
        if (s14.secondaryButton !== undefined) {
            this.secondaryButton = s14.secondaryButton;
        }
        if (s14.buttons !== undefined) {
            this.buttons = s14.buttons;
        }
        if (s14.textAlign !== undefined) {
            this.textAlign = s14.textAlign;
        }
        if (s14.contentScroller !== undefined) {
            this.contentScroller = s14.contentScroller;
        }
        if (s14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = s14.fontColorWithTheme;
        }
        if (s14.theme !== undefined) {
            this.theme = s14.theme;
        }
        if (s14.themeColorMode !== undefined) {
            this.themeColorMode = s14.themeColorMode;
        }
        if (s14.fontSizeScale !== undefined) {
            this.fontSizeScale = s14.fontSizeScale;
        }
        if (s14.minContentHeight !== undefined) {
            this.minContentHeight = s14.minContentHeight;
        }
    }

    updateStateVars(r14) {
    }

    purgeVariableDependenciesOnElmtId(q14) {
        this.__textAlign.purgeDependencyOnElmtId(q14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(q14);
        this.__fontSizeScale.purgeDependencyOnElmtId(q14);
        this.__minContentHeight.purgeDependencyOnElmtId(q14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(p14) {
        this.controller = p14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(o14) {
        this.__textAlign.set(o14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(n14) {
        this.__fontColorWithTheme.set(n14);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(m14) {
        this.__fontSizeScale.set(m14);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(l14) {
        this.__minContentHeight.set(l14);
    }

    initialRender() {
        this.observeComponentCreation2((j14, k14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((d14, e14) => {
                if (e14) {
                    let f14 = new CustomDialogContentComponent(this, {
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
                    }, undefined, d14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 766, col: 5 });
                    ViewPU.create(f14);
                    let g14 = () => {
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
                    f14.paramsGenerator_ = g14;
                } else {
                    this.updateStateVarsOfChildByElmtId(d14, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(m13 = null) {
        this.observeComponentCreation2((z13, a14) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((x13, y13) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((q13, r13) => {
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
            Text.onAreaChange((v13, w13) => {
                this.updateTextAlign(Number(w13.width));
            });
            Text.onKeyEvent((u13) => {
                if (u13) {
                    resolveKeyEvent(u13, this.contentScroller);
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

    updateTextAlign(l13) {
        this.textAlign = getTextAlign(l13, this.content, {
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
    constructor(f13, g13, h13, i13 = -1, j13 = undefined, k13) {
        super(f13, h13, i13, k13);
        if (typeof j13 === 'function') {
            this.paramsGenerator_ = j13;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__minContentHeight = new ObservedPropertySimplePU(MIN_CONTENT_HEIGHT, this, 'minContentHeight');
        this.setInitiallyProvidedValue(g13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e13) {
        if (e13.controller !== undefined) {
            this.controller = e13.controller;
        }
        if (e13.primaryTitle !== undefined) {
            this.primaryTitle = e13.primaryTitle;
        }
        if (e13.secondaryTitle !== undefined) {
            this.secondaryTitle = e13.secondaryTitle;
        }
        if (e13.contentBuilder !== undefined) {
            this.contentBuilder = e13.contentBuilder;
        }
        if (e13.contentAreaPadding !== undefined) {
            this.contentAreaPadding = e13.contentAreaPadding;
        }
        if (e13.buttons !== undefined) {
            this.buttons = e13.buttons;
        }
        if (e13.theme !== undefined) {
            this.theme = e13.theme;
        }
        if (e13.themeColorMode !== undefined) {
            this.themeColorMode = e13.themeColorMode;
        }
        if (e13.fontSizeScale !== undefined) {
            this.fontSizeScale = e13.fontSizeScale;
        }
        if (e13.minContentHeight !== undefined) {
            this.minContentHeight = e13.minContentHeight;
        }
    }

    updateStateVars(d13) {
    }

    purgeVariableDependenciesOnElmtId(c13) {
        this.__fontSizeScale.purgeDependencyOnElmtId(c13);
        this.__minContentHeight.purgeDependencyOnElmtId(c13);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(b13) {
        this.controller = b13;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(a13) {
        this.__fontSizeScale.set(a13);
    }

    get minContentHeight() {
        return this.__minContentHeight.get();
    }

    set minContentHeight(z12) {
        this.__minContentHeight.set(z12);
    }

    initialRender() {
        this.observeComponentCreation2((x12, y12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((r12, s12) => {
                if (s12) {
                    let t12 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, r12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 858, col: 5 });
                    ViewPU.create(t12);
                    let u12 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            contentAreaPadding: this.contentAreaPadding,
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            minContentHeight: this.minContentHeight
                        };
                    };
                    t12.paramsGenerator_ = u12;
                } else {
                    this.updateStateVarsOfChildByElmtId(r12, {});
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
    constructor(o12) {
        super(o12);
        this.arg_ = o12;
    }
}

class CustomDialogLayout extends ViewPU {
    constructor(i12, j12, k12, l12 = -1, m12 = undefined, n12) {
        super(i12, k12, l12, n12);
        if (typeof m12 === 'function') {
            this.paramsGenerator_ = m12;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(j12.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(j12.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(j12.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(j12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h12) {
        if (h12.dialogBuilder !== undefined) {
            this.dialogBuilder = h12.dialogBuilder;
        }
        if (h12.titleIndex !== undefined) {
            this.titleIndex = h12.titleIndex;
        }
        if (h12.contentIndex !== undefined) {
            this.contentIndex = h12.contentIndex;
        }
        if (h12.buttonIndex !== undefined) {
            this.buttonIndex = h12.buttonIndex;
        }
    }

    updateStateVars(g12) {
    }

    purgeVariableDependenciesOnElmtId(f12) {
        this.__titleHeight.purgeDependencyOnElmtId(f12);
        this.__buttonHeight.purgeDependencyOnElmtId(f12);
        this.__titleMinHeight.purgeDependencyOnElmtId(f12);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(e12 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(d12) {
        this.__titleHeight.set(d12);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(c12) {
        this.__buttonHeight.set(c12);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(b12) {
        this.__titleMinHeight.set(b12);
    }

    onPlaceChildren(u11, v11, w11) {
        let x11 = 0;
        let y11 = 0;
        for (let z11 = 0; z11 < v11.length; z11++) {
            let a12 = v11[z11];
            a12.layout({ x: x11, y: y11 });
            y11 += a12.measureResult.height;
        }
    }

    onMeasureSize(g11, h11, i11) {
        let j11 = { width: Number(i11.maxWidth), height: 0 };
        let k11 = 3;
        if (h11.length < k11) {
            return j11;
        }
        let l11 = 0;
        let m11 = h11[this.titleIndex];
        let n11 = {
            maxWidth: i11.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: i11.maxHeight
        };
        let o11 = m11.measure(n11);
        this.titleHeight = o11.height;
        l11 += this.titleHeight;
        let p11 = h11[this.buttonIndex];
        let q11 = p11.measure(i11);
        this.buttonHeight = q11.height;
        l11 += this.buttonHeight;
        let r11 = h11[this.contentIndex];
        let s11 = {
            maxWidth: i11.maxWidth,
            maxHeight: Number(i11.maxHeight) - l11
        };
        let t11 = r11.measure(s11);
        l11 += t11.height;
        j11.height = l11;
        return j11;
    }

    initialRender() {
        this.dialogBuilder.bind(this)(this);
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(a11, b11, c11, d11 = -1, e11 = undefined, f11) {
        super(a11, c11, d11, f11);
        if (typeof e11 === 'function') {
            this.paramsGenerator_ = e11;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = this.defaultContentBuilder;
        this.buttons = undefined;
        this.contentAreaPadding = undefined;
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.themeColorMode = ThemeColorMode.SYSTEM;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(b11.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(b11.fontSizeScale, this, 'fontSizeScale');
        this.__customStyle = new ObservedPropertySimplePU(false, this, 'customStyle');
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
        this.setInitiallyProvidedValue(b11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z10) {
        if (z10.controller !== undefined) {
            this.controller = z10.controller;
        }
        if (z10.primaryTitle !== undefined) {
            this.primaryTitle = z10.primaryTitle;
        }
        if (z10.secondaryTitle !== undefined) {
            this.secondaryTitle = z10.secondaryTitle;
        }
        if (z10.contentBuilder !== undefined) {
            this.contentBuilder = z10.contentBuilder;
        }
        if (z10.buttons !== undefined) {
            this.buttons = z10.buttons;
        }
        if (z10.contentAreaPadding !== undefined) {
            this.contentAreaPadding = z10.contentAreaPadding;
        }
        if (z10.keyIndex !== undefined) {
            this.keyIndex = z10.keyIndex;
        }
        if (z10.theme !== undefined) {
            this.theme = z10.theme;
        }
        if (z10.themeColorMode !== undefined) {
            this.themeColorMode = z10.themeColorMode;
        }
        if (z10.titleHeight !== undefined) {
            this.titleHeight = z10.titleHeight;
        }
        if (z10.buttonHeight !== undefined) {
            this.buttonHeight = z10.buttonHeight;
        }
        if (z10.contentMaxHeight !== undefined) {
            this.contentMaxHeight = z10.contentMaxHeight;
        }
        if (z10.customStyle !== undefined) {
            this.customStyle = z10.customStyle;
        }
        if (z10.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = z10.buttonMaxFontSize;
        }
        if (z10.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = z10.buttonMinFontSize;
        }
        if (z10.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = z10.primaryTitleMaxFontSize;
        }
        if (z10.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = z10.primaryTitleMinFontSize;
        }
        if (z10.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = z10.secondaryTitleMaxFontSize;
        }
        if (z10.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = z10.secondaryTitleMinFontSize;
        }
        if (z10.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = z10.primaryTitleFontColorWithTheme;
        }
        if (z10.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = z10.secondaryTitleFontColorWithTheme;
        }
        if (z10.titleTextAlign !== undefined) {
            this.titleTextAlign = z10.titleTextAlign;
        }
        if (z10.isButtonVertical !== undefined) {
            this.isButtonVertical = z10.isButtonVertical;
        }
        if (z10.titleMinHeight !== undefined) {
            this.titleMinHeight = z10.titleMinHeight;
        }
        if (z10.titleIndex !== undefined) {
            this.titleIndex = z10.titleIndex;
        }
        if (z10.contentIndex !== undefined) {
            this.contentIndex = z10.contentIndex;
        }
        if (z10.buttonIndex !== undefined) {
            this.buttonIndex = z10.buttonIndex;
        }
    }

    updateStateVars(y10) {
    }

    purgeVariableDependenciesOnElmtId(x10) {
        this.__minContentHeight.purgeDependencyOnElmtId(x10);
        this.__titleHeight.purgeDependencyOnElmtId(x10);
        this.__buttonHeight.purgeDependencyOnElmtId(x10);
        this.__contentMaxHeight.purgeDependencyOnElmtId(x10);
        this.__fontSizeScale.purgeDependencyOnElmtId(x10);
        this.__customStyle.purgeDependencyOnElmtId(x10);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(x10);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(x10);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(x10);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(x10);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(x10);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(x10);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(x10);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(x10);
        this.__titleTextAlign.purgeDependencyOnElmtId(x10);
        this.__isButtonVertical.purgeDependencyOnElmtId(x10);
        this.__titleMinHeight.purgeDependencyOnElmtId(x10);
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

    set minContentHeight(w10) {
        this.__minContentHeight.set(w10);
    }

    defaultContentBuilder(v10 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(u10) {
        this.__titleHeight.set(u10);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(t10) {
        this.__buttonHeight.set(t10);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(s10) {
        this.__contentMaxHeight.set(s10);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(r10) {
        this.__fontSizeScale.set(r10);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(q10) {
        this.__customStyle.set(q10);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(p10) {
        this.__buttonMaxFontSize.set(p10);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(o10) {
        this.__buttonMinFontSize.set(o10);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(n10) {
        this.__primaryTitleMaxFontSize.set(n10);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(m10) {
        this.__primaryTitleMinFontSize.set(m10);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(l10) {
        this.__secondaryTitleMaxFontSize.set(l10);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(k10) {
        this.__secondaryTitleMinFontSize.set(k10);
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(j10) {
        this.__primaryTitleFontColorWithTheme.set(j10);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(i10) {
        this.__secondaryTitleFontColorWithTheme.set(i10);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(h10) {
        this.__titleTextAlign.set(h10);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(g10) {
        this.__isButtonVertical.set(g10);
    }

    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }

    set titleMinHeight(f10) {
        this.__titleMinHeight.set(f10);
    }

    initialRender() {
        this.observeComponentCreation2((d10, e10) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((b10, c10) => {
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
        this.observeComponentCreation2((z9, a10) => {
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
            this.observeComponentCreation2((n8, o8) => {
                if (o8) {
                    let p8 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((k9, l9) => {
                                ForEach.create();
                                const m9 = o9 => {
                                    const p9 = o9;
                                    this.observeComponentCreation2((r9, s9) => {
                                        If.create();
                                        if (p9 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.titleBuilder.bind(this)(this);
                                            });
                                        } else if (p9 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((w9, x9) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.contentBuilder.bind(this)(this);
                                                Column.pop();
                                            });
                                        } else {
                                            this.ifElseBranchUpdateFunction(2, () => {
                                                this.ButtonBuilder.bind(this)(this);
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                };
                                this.forEachUpdateFunction(k9, [this.titleIndex, this.contentIndex, this.buttonIndex],
                                    m9);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, n8, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 991, col: 11 });
                    ViewPU.create(p8);
                    let q8 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((u8, v8) => {
                                    ForEach.create();
                                    const w8 = y8 => {
                                        const z8 = y8;
                                        this.observeComponentCreation2((b9, c9) => {
                                            If.create();
                                            if (z8 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.titleBuilder.bind(this)(this);
                                                });
                                            } else if (z8 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((g9, h9) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.contentBuilder.bind(this)(this);
                                                    Column.pop();
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(2, () => {
                                                    this.ButtonBuilder.bind(this)(this);
                                                });
                                            }
                                        }, If);
                                        If.pop();
                                    };
                                    this.forEachUpdateFunction(u8,
                                        [this.titleIndex, this.contentIndex, this.buttonIndex], w8);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    p8.paramsGenerator_ = q8;
                } else {
                    this.updateStateVarsOfChildByElmtId(n8, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(z7, a8, b8) {
        let c8 = { width: z7.width, height: z7.height };
        let d8 = Number(b8.maxWidth);
        let e8 = Number(b8.maxHeight);
        this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical =
            this.isVerticalAlignButton(Math.min(d8 - BUTTON_HORIZONTAL_MARGIN * 2, MAX_DIALOG_WIDTH));
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let f8 = 0;
        a8.forEach((h8) => {
            this.contentMaxHeight = '100%';
            let i8 = h8.measure(b8);
            if (e8 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                i8 = h8.measure(b8);
            }
            f8 += i8.height;
        });
        c8.height = f8;
        c8.width = d8;
        return c8;
    }

    aboutToAppear() {
        this.updateFontScale();
        if (this.controller) {
            let y7 = this.controller;
            if (y7.arg_ && y7.arg_.customStyle && y7.arg_.customStyle === true) {
                this.customStyle = true;
            }
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
            let x7 = this.getUIContext().getHostContext();
            this.fontSizeScale = x7.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (u7) {
            let v7 = u7.code;
            let w7 = u7.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${v7}, message: ${w7}`);
        }
    }

    getContentPadding() {
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

    titleBuilder(t6 = null) {
        this.observeComponentCreation2((s7, t7) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((q7, r7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((o7, p7) => {
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
        this.observeComponentCreation2((e7, f7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m7, n7) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((k7, l7) => {
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
        this.observeComponentCreation2((c7, d7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((a7, b7) => {
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
        let s6 = ALERT_TITLE_ALIGNMENT;
        if (s6 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (s6 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (s6 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (s6 === TextAlign.JUSTIFY) {
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

    ButtonBuilder(e6 = null) {
        this.observeComponentCreation2((q6, r6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((h6, i6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m6, n6) => {
                        If.create();
                        if (this.isButtonVertical) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.buildVerticalAlignButtons.bind(this)(e6 ? e6 : this);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.buildHorizontalAlignButtons.bind(this)(e6 ? e6 : this);
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

    buildSingleButton(j5, k5 = null) {
        this.observeComponentCreation2((m5, n5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(j5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c6, d6) => {
                        Button.createWithLabel(j5.value);
                        __Button__setButtonProperties(j5, this.controller);
                        Button.role(j5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (j5.background !== undefined && j5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((y5, z5) => {
                        Button.createWithLabel(j5.value);
                        __Button__setButtonProperties(j5, this.controller);
                        Button.backgroundColor(j5.background);
                        Button.fontColor(j5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (j5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((u5, v5) => {
                        Button.createWithLabel(j5.value);
                        __Button__setButtonProperties(j5, this.controller);
                        Button.backgroundColor(j5.background);
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
                    this.observeComponentCreation2((q5, r5) => {
                        Button.createWithLabel(j5.value);
                        __Button__setButtonProperties(j5, this.controller);
                        Button.fontColor(j5.fontColor);
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

    buildHorizontalAlignButtons(s4 = null) {
        this.observeComponentCreation2((u4, v4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h5, i5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], s4 ? s4 : this);
                    this.observeComponentCreation2((a5, b5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f5, g5) => {
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
                                    s4 ? s4 : this);
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

    buildVerticalAlignButtons(z3 = null) {
        this.observeComponentCreation2((b4, c4) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q4, r4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((h4, i4) => {
                        ForEach.create();
                        const j4 = (n4, o4) => {
                            const p4 = n4;
                            this.buildButtonWithDivider.bind(this)(o4, z3 ? z3 : this);
                        };
                        this.forEachUpdateFunction(h4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), j4,
                            (m4) => m4.value.toString(), true, false);
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

    isNewPropertiesHighPriority(y3) {
        if (y3.role === ButtonRole.ERROR) {
            return true;
        }
        if (y3.buttonStyle !== undefined &&
            y3.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (y3.background === undefined && y3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(g3, h3 = null) {
        this.observeComponentCreation2((j3, k3) => {
            If.create();
            if (this.buttons && this.buttons[g3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w3, x3) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[g3], h3 ? h3 : this);
                    Row.pop();
                    this.observeComponentCreation2((p3, q3) => {
                        If.create();
                        if (g3 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u3, v3) => {
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

    isVerticalAlignButton(a3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let b3 = false;
            let c3 = vp2px(a3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((e3) => {
                let f3 = measure.measureTextSize({
                    textContent: e3.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(f3.width) > c3) {
                    b3 = true;
                }
            });
            return b3;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(x2, y2) {
    Button.onClick(() => {
        if (x2.action) {
            x2.action();
        }
        y2?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(x2.buttonStyle ?? ALERT_BUTTON_STYLE);
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}

function getNumberByResourceId(t2) {
    try {
        return resourceManager.getSystemResourceManager().getNumber(t2);
    } catch (u2) {
        let v2 = u2.code;
        let w2 = u2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${v2}, message: ${w2}`);
        return 0;
    }
}

function getEnumNumberByResourceId(p2) {
    try {
        return getContext().resourceManager.getNumber(p2);
    } catch (q2) {
        let r2 = q2.code;
        let s2 = q2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${r2}, message: ${s2}`);
        return -1;
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
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1535, col: 7 });
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