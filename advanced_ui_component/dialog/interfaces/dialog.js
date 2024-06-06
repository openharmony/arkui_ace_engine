/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

const display = requireNapi('display');
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const resourceManager = requireNapi('resourceManager');
const bundleManager = requireNapi('bundleManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

class CustomThemeImpl {
    constructor(h25) {
        this.colors = h25;
    }
}

const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_DEFAULT_HEIGHT = 40;
const BUTTON_LAYOUT_WEIGHT = 1;
const CHECKBOX_CONTAINER_HEIGHT = 48;
const CONTENT_MAX_LINES = 2;
const DIVIDER_CONTAINER_WIDTH = 16;
const DIVIDER_HEIGHT = 24;
const DIVIDER_WIDTH = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 40;
const ITEM_TEXT_SIZE = 14;
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
const MAX_DIALOG_WIDTH = getNumberByResource('alert_container_max_width') ?? 400;
const BUTTON_HORIZONTAL_MARGIN = getNumberByResource('alert_right_padding_horizontal') ?? 16;
const BUTTON_HORIZONTAL_PADDING = getNumberByResource('padding_level8') ?? 16;
const BUTTON_HORIZONTAL_SPACE = getNumberByResource('alert_button_horizontal_space') ?? 8;
const BUTTON_HORIZONTAL_BOTTOM_MARGIN = getNumberByResource('alert_button_bottom_padding_horizontal') ?? 16;
const BUTTON_VERTICAL_BOTTOM_MARGIN = getNumberByResource('alert_button_bottom_padding_vertical') ?? 8;
const BUTTON_VERTICAL_PADDING = getNumberByResource('alert_button_top_padding') ?? 8;
const BUTTON_VERTICAL_SPACE = getNumberByResource('alert_button_vertical_space') ?? 4;
const MAX_BIG_BUTTON_SIZE = 3;
const MAX_WINDOW_HORIZONTAL_HEIGHT = 540;
const MAX_FONT_SCALE = 2;
const BODY_L = getNumberByResource('Body_L') ?? 16;
const BODY_M = getNumberByResource('Body_M') ?? 14;
const BODY_S = getNumberByResource('Body_S') ?? 12;
const TITLE_S = getNumberByResource('Title_S') ?? 20;
const SUBTITLE_S = getNumberByResource('Subtitle_S') ?? 14;
const BUTTON_MIN_FONT_SIZE = 9;

export class TipsDialog extends ViewPU {
    constructor(z24, a25, b25, c25 = -1, d25 = undefined, e25) {
        super(z24, b25, c25, e25);
        if (typeof d25 === 'function') {
            this.paramsGenerator_ = d25;
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
        this.__imageSizeHeight = new ObservedPropertySimplePU(0, this, 'imageSizeHeight');
        this.__textAlignment = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlignment');
        this.marginOffset = 0;
        this.__checkBoxHeight = new ObservedPropertySimplePU(0, this, 'checkBoxHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.updateButtonHeight = (g25) => {
            this.buttonHeight = g25;
        };
        this.setInitiallyProvidedValue(a25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y24) {
        if (y24.controller !== undefined) {
            this.controller = y24.controller;
        }
        if (y24.imageRes !== undefined) {
            this.imageRes = y24.imageRes;
        }
        if (y24.imageSize !== undefined) {
            this.imageSize = y24.imageSize;
        }
        if (y24.title !== undefined) {
            this.title = y24.title;
        }
        if (y24.content !== undefined) {
            this.content = y24.content;
        }
        if (y24.checkAction !== undefined) {
            this.checkAction = y24.checkAction;
        }
        if (y24.onCheckedChange !== undefined) {
            this.onCheckedChange = y24.onCheckedChange;
        }
        if (y24.checkTips !== undefined) {
            this.checkTips = y24.checkTips;
        }
        if (y24.isChecked !== undefined) {
            this.isChecked = y24.isChecked;
        }
        if (y24.primaryButton !== undefined) {
            this.primaryButton = y24.primaryButton;
        }
        if (y24.secondaryButton !== undefined) {
            this.secondaryButton = y24.secondaryButton;
        }
        if (y24.buttons !== undefined) {
            this.buttons = y24.buttons;
        }
        if (y24.imageSizeHeight !== undefined) {
            this.imageSizeHeight = y24.imageSizeHeight;
        }
        if (y24.textAlignment !== undefined) {
            this.textAlignment = y24.textAlignment;
        }
        if (y24.marginOffset !== undefined) {
            this.marginOffset = y24.marginOffset;
        }
        if (y24.checkBoxHeight !== undefined) {
            this.checkBoxHeight = y24.checkBoxHeight;
        }
        if (y24.buttonHeight !== undefined) {
            this.buttonHeight = y24.buttonHeight;
        }
        if (y24.contentScroller !== undefined) {
            this.contentScroller = y24.contentScroller;
        }
        if (y24.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = y24.fontColorWithTheme;
        }
        if (y24.theme !== undefined) {
            this.theme = y24.theme;
        }
        if (y24.themeColorMode !== undefined) {
            this.themeColorMode = y24.themeColorMode;
        }
        if (y24.fontSizeScale !== undefined) {
            this.fontSizeScale = y24.fontSizeScale;
        }
        if (y24.windowSize !== undefined) {
            this.windowSize = y24.windowSize;
        }
        if (y24.updateButtonHeight !== undefined) {
            this.updateButtonHeight = y24.updateButtonHeight;
        }
    }

    updateStateVars(x24) {
    }

    purgeVariableDependenciesOnElmtId(w24) {
        this.__imageSize.purgeDependencyOnElmtId(w24);
        this.__isChecked.purgeDependencyOnElmtId(w24);
        this.__imageSizeHeight.purgeDependencyOnElmtId(w24);
        this.__textAlignment.purgeDependencyOnElmtId(w24);
        this.__checkBoxHeight.purgeDependencyOnElmtId(w24);
        this.__buttonHeight.purgeDependencyOnElmtId(w24);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(w24);
        this.__fontSizeScale.purgeDependencyOnElmtId(w24);
        this.__windowSize.purgeDependencyOnElmtId(w24);
    }

    aboutToBeDeleted() {
        this.__imageSize.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        this.__imageSizeHeight.aboutToBeDeleted();
        this.__textAlignment.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(v24) {
        this.controller = v24;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(u24) {
        this.__imageSize.set(u24);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(t24) {
        this.__isChecked.set(t24);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(s24) {
        this.__imageSizeHeight.set(s24);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(r24) {
        this.__textAlignment.set(r24);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(q24) {
        this.__checkBoxHeight.set(q24);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(p24) {
        this.__buttonHeight.set(p24);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(o24) {
        this.__fontColorWithTheme.set(o24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(n24) {
        this.__fontSizeScale.set(n24);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(m24) {
        this.__windowSize.set(m24);
    }

    initialRender() {
        this.observeComponentCreation2((k24, l24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((e24, f24) => {
                if (f24) {
                    let g24 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize,
                        updateButtonHeight: this.updateButtonHeight
                    }, undefined, e24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 113, col: 5 });
                    ViewPU.create(g24);
                    let h24 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize,
                            updateButtonHeight: this.updateButtonHeight
                        };
                    };
                    g24.paramsGenerator_ = h24;
                } else {
                    this.updateStateVarsOfChildByElmtId(e24, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(l23 = null) {
        this.observeComponentCreation2((a24, b24) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(l23 ? l23 : this);
        this.observeComponentCreation2((t23, u23) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y23, z23) => {
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
                        Column.constraintSize({
                            maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.imageSizeHeight}vp - ${this.buttonHeight}vp)`
                        });
                    }, Column);
                    this.textPart.bind(this)(l23 ? l23 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p23, q23) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, l23 ? l23 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(u22, v22 = null) {
        this.observeComponentCreation2((g23, h23) => {
            Row.create();
            Row.padding({
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.onAreaChange((j23, k23) => {
                this.checkBoxHeight = Number(k23.height);
            });
        }, Row);
        this.observeComponentCreation2((c23, d23) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((f23) => {
                this.isChecked = f23;
                if (this.checkAction) {
                    this.checkAction(f23);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(f23);
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
        this.observeComponentCreation2((z22, a23) => {
            Text.create(u22);
            Text.fontSize(this.getCheckBoxFontSize());
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
        Row.pop();
    }

    imagePart(k22 = null) {
        this.observeComponentCreation2((p22, q22) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((s22, t22) => {
                this.imageSizeHeight = Number(t22.height);
            });
        }, Column);
        this.observeComponentCreation2((n22, o22) => {
            Image.create(this.imageRes);
            Image.size(ObservedObject.GetRawObject(this.imageSize));
            Image.objectFit(ImageFit.Contain);
            Image.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.corner_radius_level6'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.constraintSize({
                maxWidth: '100%',
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
        }, Image);
        Column.pop();
    }

    textPart(c21 = null) {
        this.observeComponentCreation2((i22, j22) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((g22, h22) => {
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
        this.observeComponentCreation2((w21, x21) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e22, f22) => {
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
                    this.observeComponentCreation2((c22, d22) => {
                        Text.create(this.title);
                        Text.fontSize(this.getTitleFontSize());
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
        this.observeComponentCreation2((h21, i21) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u21, v21) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((n21, o21) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((t21) => {
                            if (t21) {
                                resolveKeyEvent(t21, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((r21, s21) => {
                            this.getTextAlign(Number(s21.width));
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

    getTextAlign(y20) {
        let z20 = this.getContentFontSize();
        let a21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: z20,
            constraintWidth: y20,
        });
        let b21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: z20,
        });
        if (this.getTextHeight(a21) <= this.getTextHeight(b21)) {
            this.textAlignment = TextAlign.Center;
        }
    }

    getTitleFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return TITLE_S * MAX_FONT_SCALE + 'vp';
        }
        return TITLE_S + 'fp';
    }

    getContentFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_L * MAX_FONT_SCALE + 'vp';
        }
        return BODY_L + 'fp';
    }

    getCheckBoxFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_M * MAX_FONT_SCALE + 'vp';
        }
        return BODY_M + 'fp';
    }

    getTextHeight(x20) {
        if (x20 && x20.height !== null && x20.height !== undefined) {
            return Number(x20.height);
        }
        return 0;
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
        this.marginOffset = 0 - getNumberByResource('padding_level8');
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(r20, s20, t20, u20 = -1, v20 = undefined, w20) {
        super(r20, t20, u20, w20);
        if (typeof v20 === 'function') {
            this.paramsGenerator_ = v20;
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.setInitiallyProvidedValue(s20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q20) {
        if (q20.controller !== undefined) {
            this.controller = q20.controller;
        }
        if (q20.title !== undefined) {
            this.title = q20.title;
        }
        if (q20.content !== undefined) {
            this.content = q20.content;
        }
        if (q20.selectedIndex !== undefined) {
            this.selectedIndex = q20.selectedIndex;
        }
        if (q20.confirm !== undefined) {
            this.confirm = q20.confirm;
        }
        if (q20.radioContent !== undefined) {
            this.radioContent = q20.radioContent;
        }
        if (q20.buttons !== undefined) {
            this.buttons = q20.buttons;
        }
        if (q20.contentPadding !== undefined) {
            this.contentPadding = q20.contentPadding;
        }
        if (q20.isFocus !== undefined) {
            this.isFocus = q20.isFocus;
        }
        if (q20.currentFocusIndex !== undefined) {
            this.currentFocusIndex = q20.currentFocusIndex;
        }
        if (q20.radioHeight !== undefined) {
            this.radioHeight = q20.radioHeight;
        }
        if (q20.itemHeight !== undefined) {
            this.itemHeight = q20.itemHeight;
        }
        if (q20.contentBuilder !== undefined) {
            this.contentBuilder = q20.contentBuilder;
        }
        if (q20.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q20.fontColorWithTheme;
        }
        if (q20.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = q20.dividerColorWithTheme;
        }
        if (q20.theme !== undefined) {
            this.theme = q20.theme;
        }
        if (q20.themeColorMode !== undefined) {
            this.themeColorMode = q20.themeColorMode;
        }
        if (q20.contentScroller !== undefined) {
            this.contentScroller = q20.contentScroller;
        }
        if (q20.fontSizeScale !== undefined) {
            this.fontSizeScale = q20.fontSizeScale;
        }
        if (q20.windowSize !== undefined) {
            this.windowSize = q20.windowSize;
        }
    }

    updateStateVars(p20) {
    }

    purgeVariableDependenciesOnElmtId(o20) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o20);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(o20);
        this.__fontSizeScale.purgeDependencyOnElmtId(o20);
        this.__windowSize.purgeDependencyOnElmtId(o20);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(n20) {
        this.controller = n20;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m20) {
        this.__fontColorWithTheme.set(m20);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(l20) {
        this.__dividerColorWithTheme.set(l20);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k20) {
        this.__fontSizeScale.set(k20);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(j20) {
        this.__windowSize.set(j20);
    }

    buildContent(k17 = null) {
        this.observeComponentCreation2((d20, e20) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((g20, h20) => {
                let i20 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (h20 > 0) {
                            this.contentScroller.scrollBy(0, i20);
                        } else if (h20 < 0) {
                            this.contentScroller.scrollBy(0, 0 - i20);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((b20, c20) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((r19, s19) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z19, a20) => {
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
                    this.observeComponentCreation2((x19, y19) => {
                        Text.create(this.content);
                        Text.fontSize(this.getContentFontSize());
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
        this.observeComponentCreation2((o19, p19) => {
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
        this.observeComponentCreation2((q17, r17) => {
            ForEach.create();
            const s17 = (u17, v17) => {
                const w17 = u17;
                {
                    const x17 = (m19, n19) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m19);
                        y17(m19, n19);
                        if (!n19) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const y17 = (h19, i19) => {
                        ListItem.create(z17, true);
                        ListItem.onSizeChange((k19, l19) => {
                            this.itemHeight = Number(l19.height);
                        });
                    };
                    const z17 = (d18, e18) => {
                        x17(d18, e18);
                        this.observeComponentCreation2((f19, g19) => {
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
                        this.observeComponentCreation2((c19, d19) => {
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
                                w17.action && w17.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((a19, b19) => {
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
                        this.observeComponentCreation2((y18, z18) => {
                            Text.create(w17.title);
                            Text.fontSize(this.getListFontSize());
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((s18, t18) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === v17);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(v17));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = v17;
                                if (v17 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (v17 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((w18, x18) => {
                                this.radioHeight = Number(x18.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((l18, m18) => {
                            If.create();
                            if (v17 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((q18, r18) => {
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
                    this.observeComponentCreation2(y17, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(q17, this.radioContent, s17, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((i17, j17) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((c17, d17) => {
                if (d17) {
                    let e17 = new CustomDialogContentComponent(this, {
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
                        windowSize: this.__windowSize
                    }, undefined, c17, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 457, col: 5 });
                    ViewPU.create(e17);
                    let f17 = () => {
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
                            windowSize: this.windowSize
                        };
                    };
                    e17.paramsGenerator_ = f17;
                } else {
                    this.updateStateVarsOfChildByElmtId(c17, {});
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

    getContentFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_M * MAX_FONT_SCALE + 'vp';
        }
        return BODY_M + 'fp';
    }

    getListFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_L * MAX_FONT_SCALE + 'vp';
        }
        return BODY_L + 'fp';
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class ConfirmDialog extends ViewPU {
    constructor(q16, r16, s16, t16 = -1, u16 = undefined, v16) {
        super(q16, s16, t16, v16);
        if (typeof u16 === 'function') {
            this.paramsGenerator_ = u16;
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
        this.marginOffset = 0;
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__checkBoxHeight = new ObservedPropertySimplePU(CHECKBOX_CONTAINER_HEIGHT, this, 'checkBoxHeight');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.__maxContentHeight =
            new ObservedPropertySimplePU(`calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`,
                this, 'maxContentHeight');
        this.updateTitleHeight = (z16) => {
            this.titleHeight = z16;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (y16) => {
            this.buttonHeight = y16;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(r16);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(p16) {
        if (p16.controller !== undefined) {
            this.controller = p16.controller;
        }
        if (p16.title !== undefined) {
            this.title = p16.title;
        }
        if (p16.content !== undefined) {
            this.content = p16.content;
        }
        if (p16.checkTips !== undefined) {
            this.checkTips = p16.checkTips;
        }
        if (p16.isChecked !== undefined) {
            this.isChecked = p16.isChecked;
        }
        if (p16.primaryButton !== undefined) {
            this.primaryButton = p16.primaryButton;
        }
        if (p16.secondaryButton !== undefined) {
            this.secondaryButton = p16.secondaryButton;
        }
        if (p16.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = p16.fontColorWithTheme;
        }
        if (p16.theme !== undefined) {
            this.theme = p16.theme;
        }
        if (p16.themeColorMode !== undefined) {
            this.themeColorMode = p16.themeColorMode;
        }
        if (p16.onCheckedChange !== undefined) {
            this.onCheckedChange = p16.onCheckedChange;
        }
        if (p16.contentScroller !== undefined) {
            this.contentScroller = p16.contentScroller;
        }
        if (p16.buttons !== undefined) {
            this.buttons = p16.buttons;
        }
        if (p16.marginOffset !== undefined) {
            this.marginOffset = p16.marginOffset;
        }
        if (p16.titleHeight !== undefined) {
            this.titleHeight = p16.titleHeight;
        }
        if (p16.buttonHeight !== undefined) {
            this.buttonHeight = p16.buttonHeight;
        }
        if (p16.checkBoxHeight !== undefined) {
            this.checkBoxHeight = p16.checkBoxHeight;
        }
        if (p16.fontSizeScale !== undefined) {
            this.fontSizeScale = p16.fontSizeScale;
        }
        if (p16.windowSize !== undefined) {
            this.windowSize = p16.windowSize;
        }
        if (p16.maxContentHeight !== undefined) {
            this.maxContentHeight = p16.maxContentHeight;
        }
        if (p16.updateTitleHeight !== undefined) {
            this.updateTitleHeight = p16.updateTitleHeight;
        }
        if (p16.updateButtonHeight !== undefined) {
            this.updateButtonHeight = p16.updateButtonHeight;
        }
    }

    updateStateVars(o16) {
    }

    purgeVariableDependenciesOnElmtId(n16) {
        this.__isChecked.purgeDependencyOnElmtId(n16);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(n16);
        this.__titleHeight.purgeDependencyOnElmtId(n16);
        this.__buttonHeight.purgeDependencyOnElmtId(n16);
        this.__checkBoxHeight.purgeDependencyOnElmtId(n16);
        this.__fontSizeScale.purgeDependencyOnElmtId(n16);
        this.__windowSize.purgeDependencyOnElmtId(n16);
        this.__maxContentHeight.purgeDependencyOnElmtId(n16);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__maxContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(m16) {
        this.controller = m16;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(l16) {
        this.__isChecked.set(l16);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(k16) {
        this.__fontColorWithTheme.set(k16);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(j16) {
        this.__titleHeight.set(j16);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(i16) {
        this.__buttonHeight.set(i16);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(h16) {
        this.__checkBoxHeight.set(h16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(g16) {
        this.__fontSizeScale.set(g16);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(f16) {
        this.__windowSize.set(f16);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(e16) {
        this.__maxContentHeight.set(e16);
    }

    buildContent(v14 = null) {
        this.observeComponentCreation2((c16, d16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((n15, o15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a16, b16) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((y15, z15) => {
                        Scroll.create(this.contentScroller);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.PARALLEL,
                            scrollBackward: NestedScrollMode.PARALLEL
                        });
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((u15, v15) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(TextAlign.Start);
                        Text.margin({
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Text.onKeyEvent((x15) => {
                            if (x15) {
                                resolveKeyEvent(x15, this.contentScroller);
                            }
                        });
                        Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((i15, j15) => {
            Row.create();
            Row.onSizeChange((l15, m15) => {
                this.checkBoxHeight = Number(m15.height);
                this.maxContentHeight =
                    `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((e15, f15) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((h15) => {
                this.isChecked = h15;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((b15, c15) => {
            Text.create(this.checkTips);
            Text.fontSize(this.getCheckBoxFontSize());
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
        Column.pop();
    }

    getContentFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_L * MAX_FONT_SCALE + 'vp';
        }
        return BODY_L + 'fp';
    }

    getCheckBoxFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_M * MAX_FONT_SCALE + 'vp';
        }
        return BODY_M + 'fp';
    }

    initialRender() {
        this.observeComponentCreation2((t14, u14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((n14, o14) => {
                if (o14) {
                    let p14 = new CustomDialogContentComponent(this, {
                        primaryTitle: this.title,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.buildContent();
                        },
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, n14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 641, col: 5 });
                    ViewPU.create(p14);
                    let q14 = () => {
                        return {
                            primaryTitle: this.title,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.buildContent();
                            },
                            updateTitleHeight: this.updateTitleHeight,
                            updateButtonHeight: this.updateButtonHeight,
                            buttons: this.buttons,
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    p14.paramsGenerator_ = q14;
                } else {
                    this.updateStateVarsOfChildByElmtId(n14, {});
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
        this.marginOffset = 0 - getNumberByResource('padding_level8');
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
    constructor(f14, g14, h14, i14 = -1, j14 = undefined, k14) {
        super(f14, h14, i14, k14);
        if (typeof j14 === 'function') {
            this.paramsGenerator_ = j14;
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: MAX_DIALOG_WIDTH, height: 0 }, this, 'windowSize');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.setInitiallyProvidedValue(g14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e14) {
        if (e14.controller !== undefined) {
            this.controller = e14.controller;
        }
        if (e14.primaryTitle !== undefined) {
            this.primaryTitle = e14.primaryTitle;
        }
        if (e14.secondaryTitle !== undefined) {
            this.secondaryTitle = e14.secondaryTitle;
        }
        if (e14.content !== undefined) {
            this.content = e14.content;
        }
        if (e14.primaryButton !== undefined) {
            this.primaryButton = e14.primaryButton;
        }
        if (e14.secondaryButton !== undefined) {
            this.secondaryButton = e14.secondaryButton;
        }
        if (e14.buttons !== undefined) {
            this.buttons = e14.buttons;
        }
        if (e14.textAlign !== undefined) {
            this.textAlign = e14.textAlign;
        }
        if (e14.contentScroller !== undefined) {
            this.contentScroller = e14.contentScroller;
        }
        if (e14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = e14.fontColorWithTheme;
        }
        if (e14.theme !== undefined) {
            this.theme = e14.theme;
        }
        if (e14.themeColorMode !== undefined) {
            this.themeColorMode = e14.themeColorMode;
        }
        if (e14.windowSize !== undefined) {
            this.windowSize = e14.windowSize;
        }
        if (e14.fontSizeScale !== undefined) {
            this.fontSizeScale = e14.fontSizeScale;
        }
    }

    updateStateVars(d14) {
    }

    purgeVariableDependenciesOnElmtId(c14) {
        this.__textAlign.purgeDependencyOnElmtId(c14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(c14);
        this.__windowSize.purgeDependencyOnElmtId(c14);
        this.__fontSizeScale.purgeDependencyOnElmtId(c14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(b14) {
        this.controller = b14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(a14) {
        this.__textAlign.set(a14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(z13) {
        this.__fontColorWithTheme.set(z13);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(y13) {
        this.__windowSize.set(y13);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(x13) {
        this.__fontSizeScale.set(x13);
    }

    initialRender() {
        this.observeComponentCreation2((v13, w13) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p13, q13) => {
                if (q13) {
                    let r13 = new CustomDialogContentComponent(this, {
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
                        windowSize: this.__windowSize,
                    }, undefined, p13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 701, col: 5 });
                    ViewPU.create(r13);
                    let s13 = () => {
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
                            windowSize: this.windowSize
                        };
                    };
                    r13.paramsGenerator_ = s13;
                } else {
                    this.updateStateVarsOfChildByElmtId(p13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(y12 = null) {
        this.observeComponentCreation2((l13, m13) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((j13, k13) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((c13, d13) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.fontSize(this.getContentFontSize());
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
            Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
            Text.textAlign(this.textAlign);
            Text.onAreaChange((h13, i13) => {
                this.getTextAlign(Number(i13.width));
            });
            Text.onKeyEvent((g13) => {
                if (g13) {
                    resolveKeyEvent(g13, this.contentScroller);
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

    getContentFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_L * MAX_FONT_SCALE + 'vp';
        } else {
            return BODY_L + 'fp';
        }
    }

    getTextAlign(u12) {
        let v12 = this.getContentFontSize();
        let w12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: v12,
            constraintWidth: u12,
        });
        let x12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: v12,
        });
        if (this.getTextHeight(w12) <= this.getTextHeight(x12)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(t12) {
        if (t12 && t12.height !== null && t12.height !== undefined) {
            return Number(t12.height);
        }
        return 0;
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
        return 0 - getNumberByResource('padding_level8');
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
    constructor(n12, o12, p12, q12 = -1, r12 = undefined, s12) {
        super(n12, p12, q12, s12);
        if (typeof r12 === 'function') {
            this.paramsGenerator_ = r12;
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.setInitiallyProvidedValue(o12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m12) {
        if (m12.controller !== undefined) {
            this.controller = m12.controller;
        }
        if (m12.primaryTitle !== undefined) {
            this.primaryTitle = m12.primaryTitle;
        }
        if (m12.secondaryTitle !== undefined) {
            this.secondaryTitle = m12.secondaryTitle;
        }
        if (m12.contentBuilder !== undefined) {
            this.contentBuilder = m12.contentBuilder;
        }
        if (m12.contentAreaPadding !== undefined) {
            this.contentAreaPadding = m12.contentAreaPadding;
        }
        if (m12.buttons !== undefined) {
            this.buttons = m12.buttons;
        }
        if (m12.theme !== undefined) {
            this.theme = m12.theme;
        }
        if (m12.themeColorMode !== undefined) {
            this.themeColorMode = m12.themeColorMode;
        }
        if (m12.fontSizeScale !== undefined) {
            this.fontSizeScale = m12.fontSizeScale;
        }
        if (m12.windowSize !== undefined) {
            this.windowSize = m12.windowSize;
        }
    }

    updateStateVars(l12) {
    }

    purgeVariableDependenciesOnElmtId(k12) {
        this.__fontSizeScale.purgeDependencyOnElmtId(k12);
        this.__windowSize.purgeDependencyOnElmtId(k12);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(j12) {
        this.controller = j12;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(i12) {
        this.__fontSizeScale.set(i12);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(h12) {
        this.__windowSize.set(h12);
    }

    initialRender() {
        this.observeComponentCreation2((f12, g12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((z11, a12) => {
                if (a12) {
                    let b12 = new CustomDialogContentComponent(this, {
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
                        windowSize: this.__windowSize
                    }, undefined, z11, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 820, col: 5 });
                    ViewPU.create(b12);
                    let c12 = () => {
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
                            windowSize: this.windowSize
                        };
                    };
                    b12.paramsGenerator_ = c12;
                } else {
                    this.updateStateVarsOfChildByElmtId(z11, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(r11, s11, t11, u11 = -1, v11 = undefined, w11) {
        super(r11, t11, u11, w11);
        if (typeof v11 === 'function') {
            this.paramsGenerator_ = v11;
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
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight =
            new ObservedPropertySimplePU(`calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`, this,
                'contentMaxHeight');
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
        this.targetSdk = VERSION_TWELVE;
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(s11.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(s11.windowSize, this, 'windowSize');
        this.__customStyle = new ObservedPropertySimplePU(false, this, 'customStyle');
        this.__needResponseScale = new ObservedPropertySimplePU(true, this, 'needResponseScale');
        this.screenSize = { width: 0, height: 0 };
        this.initCustomStyle = false;
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.setInitiallyProvidedValue(s11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q11) {
        if (q11.controller !== undefined) {
            this.controller = q11.controller;
        }
        if (q11.primaryTitle !== undefined) {
            this.primaryTitle = q11.primaryTitle;
        }
        if (q11.secondaryTitle !== undefined) {
            this.secondaryTitle = q11.secondaryTitle;
        }
        if (q11.contentBuilder !== undefined) {
            this.contentBuilder = q11.contentBuilder;
        }
        if (q11.buttons !== undefined) {
            this.buttons = q11.buttons;
        }
        if (q11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = q11.contentAreaPadding;
        }
        if (q11.keyIndex !== undefined) {
            this.keyIndex = q11.keyIndex;
        }
        if (q11.theme !== undefined) {
            this.theme = q11.theme;
        }
        if (q11.themeColorMode !== undefined) {
            this.themeColorMode = q11.themeColorMode;
        }
        if (q11.titleHeight !== undefined) {
            this.titleHeight = q11.titleHeight;
        }
        if (q11.buttonHeight !== undefined) {
            this.buttonHeight = q11.buttonHeight;
        }
        if (q11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = q11.contentMaxHeight;
        }
        if (q11.updateTitleHeight !== undefined) {
            this.updateTitleHeight = q11.updateTitleHeight;
        }
        if (q11.updateButtonHeight !== undefined) {
            this.updateButtonHeight = q11.updateButtonHeight;
        }
        if (q11.targetSdk !== undefined) {
            this.targetSdk = q11.targetSdk;
        }
        if (q11.customStyle !== undefined) {
            this.customStyle = q11.customStyle;
        }
        if (q11.needResponseScale !== undefined) {
            this.needResponseScale = q11.needResponseScale;
        }
        if (q11.screenSize !== undefined) {
            this.screenSize = q11.screenSize;
        }
        if (q11.initCustomStyle !== undefined) {
            this.initCustomStyle = q11.initCustomStyle;
        }
        if (q11.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = q11.buttonMaxFontSize;
        }
        if (q11.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = q11.buttonMinFontSize;
        }
    }

    updateStateVars(p11) {
    }

    purgeVariableDependenciesOnElmtId(o11) {
        this.__titleHeight.purgeDependencyOnElmtId(o11);
        this.__buttonHeight.purgeDependencyOnElmtId(o11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(o11);
        this.__fontSizeScale.purgeDependencyOnElmtId(o11);
        this.__windowSize.purgeDependencyOnElmtId(o11);
        this.__customStyle.purgeDependencyOnElmtId(o11);
        this.__needResponseScale.purgeDependencyOnElmtId(o11);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(o11);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(o11);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__contentMaxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__customStyle.aboutToBeDeleted();
        this.__needResponseScale.aboutToBeDeleted();
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    defaultContentBuilder(n11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(m11) {
        this.__titleHeight.set(m11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(l11) {
        this.__buttonHeight.set(l11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(k11) {
        this.__contentMaxHeight.set(k11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j11) {
        this.__fontSizeScale.set(j11);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(i11) {
        this.__windowSize.set(i11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(h11) {
        this.__customStyle.set(h11);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(g11) {
        this.__needResponseScale.set(g11);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(f11) {
        this.__buttonMaxFontSize.set(f11);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(e11) {
        this.__buttonMinFontSize.set(e11);
    }

    initialRender() {
        this.observeComponentCreation2((c11, d11) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((a11, b11) => {
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
        this.observeComponentCreation2((y10, z10) => {
            Column.create();
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
            this.observeComponentCreation2((s10, t10) => {
                if (t10) {
                    let u10 = new TitleComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        titleHeight: this.__titleHeight,
                        needResponseScale: this.__needResponseScale,
                        theme: this.theme
                    }, undefined, s10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 873, col: 11 });
                    ViewPU.create(u10);
                    let v10 = () => {
                        return {
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            windowSize: this.windowSize,
                            fontSizeScale: this.fontSizeScale,
                            titleHeight: this.titleHeight,
                            needResponseScale: this.needResponseScale,
                            theme: this.theme
                        };
                    };
                    u10.paramsGenerator_ = v10;
                } else {
                    this.updateStateVarsOfChildByElmtId(s10, {});
                }
            }, { name: 'TitleComponent' });
        }
        this.observeComponentCreation2((p10, q10) => {
            Column.create();
            Column.padding(this.getContentPadding());
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
        }, Column);
        this.contentBuilder.bind(this)(this);
        Column.pop();
        {
            this.observeComponentCreation2((j10, k10) => {
                if (k10) {
                    let l10 = new ButtonComponent(this, {
                        buttons: this.buttons,
                        windowSize: this.__windowSize,
                        buttonHeight: this.__buttonHeight,
                        controller: this.controller,
                        theme: this.theme,
                        buttonMaxFontSize: this.__buttonMaxFontSize,
                        buttonMinFontSize: this.__buttonMinFontSize
                    }, undefined, j10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 889, col: 11 });
                    ViewPU.create(l10);
                    let m10 = () => {
                        return {
                            buttons: this.buttons,
                            windowSize: this.windowSize,
                            buttonHeight: this.buttonHeight,
                            controller: this.controller,
                            theme: this.theme,
                            buttonMaxFontSize: this.buttonMaxFontSize,
                            buttonMinFontSize: this.buttonMinFontSize
                        };
                    };
                    l10.paramsGenerator_ = m10;
                } else {
                    this.updateStateVarsOfChildByElmtId(j10, {});
                }
            }, { name: 'ButtonComponent' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(v9, w9, x9) {
        let y9 = { width: v9.width, height: v9.height };
        let z9 = Number(x9.maxWidth);
        let a10 = Number(x9.maxHeight);
        this.windowSize = { width: z9, height: a10 };
        this.updateFontScale();
        this.updateNeedResponseScale();
        this.updateCustomStyle(Number(x9.maxWidth), Number(x9.maxHeight));
        this.updateFontSize();
        w9.forEach((c10) => {
            let d10 = c10.measure(x9);
            if (this.updateButtonHeight) {
                this.updateButtonHeight(this.buttonHeight);
            }
            if (this.updateTitleHeight) {
                this.updateTitleHeight(this.titleHeight);
            }
            if (a10 - this.buttonHeight - this.titleHeight < MIN_CONTENT_HEIGHT) {
                this.contentMaxHeight = `${MAX_CONTENT_HEIGHT}vp`;
            } else {
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            }
            d10 = c10.measure(x9);
            y9.height = d10.height;
            y9.width = d10.width;
        });
        return y9;
    }

    updateCustomStyle(t9, u9) {
        if (this.initCustomStyle) {
            return;
        }
        if (this.targetSdk >= VERSION_TWELVE) {
            return;
        }
        if (this.screenSize.width > MAX_DIALOG_WIDTH) {
            this.customStyle = t9 > MAX_DIALOG_WIDTH;
        } else {
            this.customStyle = t9 >= this.screenSize.width;
        }
        this.initCustomStyle = true;
    }

    updateNeedResponseScale() {
        if (this.buttons && this.buttons.length >= MAX_BIG_BUTTON_SIZE &&
            this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            this.needResponseScale = false;
        } else {
            this.needResponseScale = true;
        }
    }

    aboutToAppear() {
        this.initEnvInfo();
    }

    updateFontSize() {
        if (this.needResponseScale) {
            if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
                this.buttonMaxFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
                this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE * MAX_FONT_SCALE + 'vp';
            } else {
                this.buttonMaxFontSize = BODY_L + 'fp';
                this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
            }
        } else {
            this.buttonMaxFontSize = BODY_L + 'vp';
            this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'vp';
        }
    }

    initEnvInfo() {
        try {
            let s9 = display.getDefaultDisplaySync();
            this.screenSize = { width: px2vp(s9.width), height: px2vp(s9.height) };
        } catch (p9) {
            let q9 = p9.code;
            let r9 = p9.message;
            hilog.error(0x3900, 'Ace', `Faild to init windowsize,cause, code: ${q9}, message: ${r9}`);
        }
        this.updateFontScale();
        try {
            let o9 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            this.targetSdk = bundleManager.getBundleInfoForSelfSync(o9).targetVersion;
        } catch (l9) {
            let m9 = l9.code;
            let n9 = l9.message;
            hilog.error(0x3900, 'Ace', `Faild to init bundle info,cause, code: ${m9}, message: ${n9}`);
        }
    }

    updateFontScale() {
        try {
            let k9 = this.getUIContext().getHostContext();
            this.fontSizeScale = k9.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (h9) {
            let i9 = h9.code;
            let j9 = h9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${i9}, message: ${j9}`);
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

    rerender() {
        this.updateDirtyElements();
    }
}

class TitleComponent extends ViewPU {
    constructor(b9, c9, d9, e9 = -1, f9 = undefined, g9) {
        super(b9, d9, e9, g9);
        if (typeof f9 === 'function') {
            this.paramsGenerator_ = f9;
        }
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.theme = new CustomThemeImpl({});
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
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(c9.needResponseScale, this, 'needResponseScale');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(c9.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(c9.windowSize, this, 'windowSize');
        this.__titleHeight = new SynchedPropertyObjectTwoWayPU(c9.titleHeight, this, 'titleHeight');
        this.setInitiallyProvidedValue(c9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a9) {
        if (a9.primaryTitle !== undefined) {
            this.primaryTitle = a9.primaryTitle;
        }
        if (a9.secondaryTitle !== undefined) {
            this.secondaryTitle = a9.secondaryTitle;
        }
        if (a9.theme !== undefined) {
            this.theme = a9.theme;
        }
        if (a9.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = a9.primaryTitleFontColorWithTheme;
        }
        if (a9.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = a9.secondaryTitleFontColorWithTheme;
        }
        if (a9.titleTextAlign !== undefined) {
            this.titleTextAlign = a9.titleTextAlign;
        }
        if (a9.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = a9.primaryTitleMaxFontSize;
        }
        if (a9.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = a9.primaryTitleMinFontSize;
        }
        if (a9.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = a9.secondaryTitleMaxFontSize;
        }
        if (a9.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = a9.secondaryTitleMinFontSize;
        }
    }

    updateStateVars(z8) {
    }

    purgeVariableDependenciesOnElmtId(y8) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(y8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(y8);
        this.__titleTextAlign.purgeDependencyOnElmtId(y8);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(y8);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(y8);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(y8);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(y8);
        this.__needResponseScale.purgeDependencyOnElmtId(y8);
        this.__fontSizeScale.purgeDependencyOnElmtId(y8);
        this.__windowSize.purgeDependencyOnElmtId(y8);
        this.__titleHeight.purgeDependencyOnElmtId(y8);
    }

    aboutToBeDeleted() {
        this.__primaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__secondaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__titleTextAlign.aboutToBeDeleted();
        this.__primaryTitleMaxFontSize.aboutToBeDeleted();
        this.__primaryTitleMinFontSize.aboutToBeDeleted();
        this.__secondaryTitleMaxFontSize.aboutToBeDeleted();
        this.__secondaryTitleMinFontSize.aboutToBeDeleted();
        this.__needResponseScale.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(x8) {
        this.__primaryTitleFontColorWithTheme.set(x8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(w8) {
        this.__secondaryTitleFontColorWithTheme.set(w8);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(v8) {
        this.__titleTextAlign.set(v8);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(u8) {
        this.__primaryTitleMaxFontSize.set(u8);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(t8) {
        this.__primaryTitleMinFontSize.set(t8);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(s8) {
        this.__secondaryTitleMaxFontSize.set(s8);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(r8) {
        this.__secondaryTitleMinFontSize.set(r8);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(q8) {
        this.__needResponseScale.set(q8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(p8) {
        this.__fontSizeScale.set(p8);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(o8) {
        this.__windowSize.set(o8);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(n8) {
        this.__titleHeight.set(n8);
    }

    initialRender() {
        this.observeComponentCreation2((l8, m8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((j8, k8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((h8, i8) => {
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
        this.observeComponentCreation2((x7, y7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f8, g8) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((d8, e8) => {
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
        this.observeComponentCreation2((v7, w7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((t7, u7) => {
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

    aboutToAppear() {
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
        this.updateFontSize();
    }

    onMeasureSize(f7, g7, h7) {
        let i7 = { width: f7.width, height: f7.height };
        this.updateFontSize();
        let j7 = {
            minWidth: h7.minWidth,
            minHeight: this.getTitleAreaMinHeight(),
            maxWidth: h7.maxWidth,
            maxHeight: h7.maxHeight
        };
        g7.forEach((l7) => {
            let m7 = l7.measure(j7);
            i7.height = m7.height;
            i7.width = m7.width;
        });
        this.titleHeight = i7.height;
        return i7;
    }

    updateFontSize() {
        if (this.needResponseScale) {
            if (this.fontSizeScale > MAX_FONT_SCALE) {
                this.primaryTitleMaxFontSize = TITLE_S * MAX_FONT_SCALE + 'vp';
                this.primaryTitleMinFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
                this.secondaryTitleMaxFontSize = SUBTITLE_S * MAX_FONT_SCALE + 'vp';
                this.secondaryTitleMinFontSize = BODY_S * MAX_FONT_SCALE + 'vp';
            } else {
                this.primaryTitleMaxFontSize = TITLE_S + 'fp';
                this.primaryTitleMinFontSize = BODY_L + 'fp';
                this.secondaryTitleMaxFontSize = SUBTITLE_S + 'fp';
                this.secondaryTitleMinFontSize = BODY_S + 'fp';
            }
        } else {
            this.primaryTitleMaxFontSize = TITLE_S + 'vp';
            this.primaryTitleMinFontSize = BODY_L + 'vp';
            this.secondaryTitleMaxFontSize = SUBTITLE_S + 'vp';
            this.secondaryTitleMinFontSize = BODY_S + 'vp';
        }
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
        let e7 = getEnumNumberByResource('alert_title_alignment');
        if (e7 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (e7 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (e7 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (e7 === TextAlign.JUSTIFY) {
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

    rerender() {
        this.updateDirtyElements();
    }
}

class ButtonComponent extends ViewPU {
    constructor(y6, z6, a7, b7 = -1, c7 = undefined, d7) {
        super(y6, a7, b7, d7);
        if (typeof c7 === 'function') {
            this.paramsGenerator_ = c7;
        }
        this.controller = undefined;
        this.buttons = undefined;
        this.__buttonMaxFontSize = new SynchedPropertyObjectTwoWayPU(z6.buttonMaxFontSize, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new SynchedPropertyObjectTwoWayPU(z6.buttonMinFontSize, this, 'buttonMinFontSize');
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.__singleButtonHeight = new ObservedPropertySimplePU(BUTTON_DEFAULT_HEIGHT, this, 'singleButtonHeight');
        this.__isButtonVertical = new ObservedPropertySimplePU(false, this, 'isButtonVertical');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(z6.windowSize, this, 'windowSize');
        this.__buttonHeight = new SynchedPropertyObjectTwoWayPU(z6.buttonHeight, this, 'buttonHeight');
        this.setInitiallyProvidedValue(z6);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x6) {
        if (x6.controller !== undefined) {
            this.controller = x6.controller;
        }
        if (x6.buttons !== undefined) {
            this.buttons = x6.buttons;
        }
        if (x6.keyIndex !== undefined) {
            this.keyIndex = x6.keyIndex;
        }
        if (x6.theme !== undefined) {
            this.theme = x6.theme;
        }
        if (x6.singleButtonHeight !== undefined) {
            this.singleButtonHeight = x6.singleButtonHeight;
        }
        if (x6.isButtonVertical !== undefined) {
            this.isButtonVertical = x6.isButtonVertical;
        }
    }

    updateStateVars(w6) {
    }

    purgeVariableDependenciesOnElmtId(v6) {
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(v6);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(v6);
        this.__singleButtonHeight.purgeDependencyOnElmtId(v6);
        this.__isButtonVertical.purgeDependencyOnElmtId(v6);
        this.__windowSize.purgeDependencyOnElmtId(v6);
        this.__buttonHeight.purgeDependencyOnElmtId(v6);
    }

    aboutToBeDeleted() {
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        this.__singleButtonHeight.aboutToBeDeleted();
        this.__isButtonVertical.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(u6) {
        this.__buttonMaxFontSize.set(u6);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(t6) {
        this.__buttonMinFontSize.set(t6);
    }

    get singleButtonHeight() {
        return this.__singleButtonHeight.get();
    }

    set singleButtonHeight(s6) {
        this.__singleButtonHeight.set(s6);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(r6) {
        this.__isButtonVertical.set(r6);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(q6) {
        this.__windowSize.set(q6);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(p6) {
        this.__buttonHeight.set(p6);
    }

    initialRender() {
        this.observeComponentCreation2((n6, o6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((e6, f6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j6, k6) => {
                        If.create();
                        if (this.isButtonVertical) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.buildVerticalAlignButtons.bind(this)(this);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.buildHorizontalAlignButtons.bind(this)(this);
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

    aboutToAppear() {
        this.isButtonVertical =
            this.isVerticalAlignButton(Math.min(this.windowSize.width - BUTTON_HORIZONTAL_MARGIN * 2,
                MAX_DIALOG_WIDTH));
    }

    onMeasureSize(v5, w5, x5) {
        let y5 = { width: v5.width, height: v5.height };
        this.isButtonVertical = this.isVerticalAlignButton(Number(x5.maxWidth));
        w5.forEach((a6) => {
            let b6 = a6.measure(x5);
            y5.height = b6.height;
            y5.width = b6.width;
        });
        this.buttonHeight = Number(y5.height);
        return y5;
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

    buildSingleButton(a5, b5 = null) {
        this.observeComponentCreation2((d5, e5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(a5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t5, u5) => {
                        Button.createWithLabel(a5.value);
                        __Button__setButtonProperties(a5, this.controller);
                        Button.role(a5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (a5.background !== undefined && a5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p5, q5) => {
                        Button.createWithLabel(a5.value);
                        __Button__setButtonProperties(a5, this.controller);
                        Button.backgroundColor(a5.background);
                        Button.fontColor(a5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (a5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((l5, m5) => {
                        Button.createWithLabel(a5.value);
                        __Button__setButtonProperties(a5, this.controller);
                        Button.backgroundColor(a5.background);
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
                    this.observeComponentCreation2((h5, i5) => {
                        Button.createWithLabel(a5.value);
                        __Button__setButtonProperties(a5, this.controller);
                        Button.fontColor(a5.fontColor);
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

    buildHorizontalAlignButtons(j4 = null) {
        this.observeComponentCreation2((l4, m4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y4, z4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], j4 ? j4 : this);
                    this.observeComponentCreation2((r4, s4) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w4, x4) => {
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
                                    j4 ? j4 : this);
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

    buildVerticalAlignButtons(q3 = null) {
        this.observeComponentCreation2((s3, t3) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h4, i4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((y3, z3) => {
                        ForEach.create();
                        const a4 = (e4, f4) => {
                            const g4 = e4;
                            this.buildButtonWithDivider.bind(this)(f4, q3 ? q3 : this);
                        };
                        this.forEachUpdateFunction(y3, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), a4,
                            (d4) => d4.value.toString(), true, false);
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
        if (!this.buttons || this.buttons.length === 0 || !getNumberByResource('dialog_divider_show')) {
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

    isNewPropertiesHighPriority(p3) {
        if (p3.role === ButtonRole.ERROR) {
            return true;
        }
        if (p3.buttonStyle !== undefined &&
            p3.buttonStyle !== getNumberByResource('alert_button_style')) {
            return true;
        }
        if (p3.background === undefined && p3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(x2, y2 = null) {
        this.observeComponentCreation2((a3, b3) => {
            If.create();
            if (this.buttons && this.buttons[x2]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n3, o3) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[x2], y2 ? y2 : this);
                    Row.pop();
                    this.observeComponentCreation2((g3, h3) => {
                        If.create();
                        if (x2 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l3, m3) => {
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

    isVerticalAlignButton(r2) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let s2 = false;
            let t2 = vp2px(r2 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((v2) => {
                let w2 = measure.measureTextSize({
                    textContent: v2.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(w2.width) > t2) {
                    s2 = true;
                }
            });
            return s2;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(o2, p2) {
    Button.onClick(() => {
        if (o2.action) {
            o2.action();
        }
        p2?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(o2.buttonStyle ?? getNumberByResource('alert_button_style'));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}

function getNumberByResource(k2) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(k2);
    } catch (l2) {
        let m2 = l2.code;
        let n2 = l2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${m2}, message: ${n2}`);
        return 0;
    }
}

function getEnumNumberByResource(g2) {
    try {
        return getContext().resourceManager.getNumberByName(g2);
    } catch (h2) {
        let i2 = h2.code;
        let j2 = h2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${i2}, message: ${j2}`);
        return -1;
    }
}

function resolveKeyEvent(e2, f2) {
    if (e2.type == IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (e2.keyCode == KEYCODE_UP) {
        f2.scrollPage({ next: false });
        e2.stopPropagation();
    } else if (e2.keyCode == KEYCODE_DOWN) {
        if (f2.isAtEnd()) {
            return;
        } else {
            f2.scrollPage({ next: true });
            e2.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(y1, z1, a2, b2 = -1, c2 = undefined, d2) {
        super(y1, a2, b2, d2);
        if (typeof c2 === 'function') {
            this.paramsGenerator_ = c2;
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.setInitiallyProvidedValue(z1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x1) {
        if (x1.controller !== undefined) {
            this.controller = x1.controller;
        }
        if (x1.content !== undefined) {
            this.content = x1.content;
        }
        if (x1.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = x1.fontColorWithTheme;
        }
        if (x1.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = x1.loadingProgressIconColorWithTheme;
        }
        if (x1.theme !== undefined) {
            this.theme = x1.theme;
        }
        if (x1.themeColorMode !== undefined) {
            this.themeColorMode = x1.themeColorMode;
        }
        if (x1.fontSizeScale !== undefined) {
            this.fontSizeScale = x1.fontSizeScale;
        }
        if (x1.windowSize !== undefined) {
            this.windowSize = x1.windowSize;
        }
    }

    updateStateVars(w1) {
    }

    purgeVariableDependenciesOnElmtId(v1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(v1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(v1);
        this.__fontSizeScale.purgeDependencyOnElmtId(v1);
        this.__windowSize.purgeDependencyOnElmtId(v1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(u1) {
        this.controller = u1;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(t1) {
        this.__fontColorWithTheme.set(t1);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(s1) {
        this.__loadingProgressIconColorWithTheme.set(s1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(r1) {
        this.__fontSizeScale.set(r1);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(q1) {
        this.__windowSize.set(q1);
    }

    initialRender() {
        this.observeComponentCreation2((o1, p1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((m1, n1) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((g1, h1) => {
                if (h1) {
                    let i1 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, g1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1524, col: 7 });
                    ViewPU.create(i1);
                    let j1 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            theme: this.theme,
                            themeColorMode: this.themeColorMode,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    i1.paramsGenerator_ = j1;
                } else {
                    this.updateStateVarsOfChildByElmtId(g1, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
        Column.pop();
    }

    contentBuilder(q = null) {
        this.observeComponentCreation2((b1, c1) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((z, a1) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((x, y) => {
            Text.create(this.content);
            Text.fontSize(this.getFontSize());
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
            Text.maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES);
            Text.focusable(true);
            Text.defaultFocus(true);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((v, w) => {
            LoadingProgress.create();
            LoadingProgress.color(ObservedObject.GetRawObject(this.loadingProgressIconColorWithTheme));
            LoadingProgress.width(LOADING_PROGRESS_WIDTH);
            LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
            LoadingProgress.margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) });
        }, LoadingProgress);
        Row.pop();
        Column.pop();
    }

    getFontSize() {
        if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
            return BODY_L * MAX_FONT_SCALE + 'vp';
        } else {
            return BODY_L;
        }
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
    constructor(k, l, m, n = -1, o = undefined, p) {
        super(k, m, n, p);
        if (typeof o === 'function') {
            this.paramsGenerator_ = o;
        }
        this.__show = new SynchedPropertySimpleTwoWayPU(l.show, this, 'show');
        this.__popup = new SynchedPropertyObjectOneWayPU(l.popup, this, 'popup');
        this.targetBuilder = undefined;
        this.setInitiallyProvidedValue(l);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j) {
        if (j.targetBuilder !== undefined) {
            this.targetBuilder = j.targetBuilder;
        }
    }

    updateStateVars(i) {
        this.__popup.reset(i.popup);
    }

    purgeVariableDependenciesOnElmtId(h) {
        this.__show.purgeDependencyOnElmtId(h);
        this.__popup.purgeDependencyOnElmtId(h);
    }

    aboutToBeDeleted() {
        this.__show.aboutToBeDeleted();
        this.__popup.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get show() {
        return this.__show.get();
    }

    set show(g) {
        this.__show.set(g);
    }

    get popup() {
        return this.__popup.get();
    }

    set popup(f) {
        this.__popup.set(f);
    }

    initialRender() {
        this.observeComponentCreation2((b, c) => {
            Column.create();
            Column.onClick(() => {
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
