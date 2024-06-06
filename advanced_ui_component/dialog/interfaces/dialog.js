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
    constructor(j25) {
        this.colors = j25;
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
    constructor(b25, c25, d25, e25 = -1, f25 = undefined, g25) {
        super(b25, d25, e25, g25);
        if (typeof f25 === 'function') {
            this.paramsGenerator_ = f25;
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
        this.updateButtonHeight = (i25) => {
            this.buttonHeight = i25;
        };
        this.setInitiallyProvidedValue(c25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a25) {
        if (a25.controller !== undefined) {
            this.controller = a25.controller;
        }
        if (a25.imageRes !== undefined) {
            this.imageRes = a25.imageRes;
        }
        if (a25.imageSize !== undefined) {
            this.imageSize = a25.imageSize;
        }
        if (a25.title !== undefined) {
            this.title = a25.title;
        }
        if (a25.content !== undefined) {
            this.content = a25.content;
        }
        if (a25.checkAction !== undefined) {
            this.checkAction = a25.checkAction;
        }
        if (a25.onCheckedChange !== undefined) {
            this.onCheckedChange = a25.onCheckedChange;
        }
        if (a25.checkTips !== undefined) {
            this.checkTips = a25.checkTips;
        }
        if (a25.isChecked !== undefined) {
            this.isChecked = a25.isChecked;
        }
        if (a25.primaryButton !== undefined) {
            this.primaryButton = a25.primaryButton;
        }
        if (a25.secondaryButton !== undefined) {
            this.secondaryButton = a25.secondaryButton;
        }
        if (a25.buttons !== undefined) {
            this.buttons = a25.buttons;
        }
        if (a25.imageSizeHeight !== undefined) {
            this.imageSizeHeight = a25.imageSizeHeight;
        }
        if (a25.textAlignment !== undefined) {
            this.textAlignment = a25.textAlignment;
        }
        if (a25.marginOffset !== undefined) {
            this.marginOffset = a25.marginOffset;
        }
        if (a25.checkBoxHeight !== undefined) {
            this.checkBoxHeight = a25.checkBoxHeight;
        }
        if (a25.buttonHeight !== undefined) {
            this.buttonHeight = a25.buttonHeight;
        }
        if (a25.contentScroller !== undefined) {
            this.contentScroller = a25.contentScroller;
        }
        if (a25.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = a25.fontColorWithTheme;
        }
        if (a25.theme !== undefined) {
            this.theme = a25.theme;
        }
        if (a25.themeColorMode !== undefined) {
            this.themeColorMode = a25.themeColorMode;
        }
        if (a25.fontSizeScale !== undefined) {
            this.fontSizeScale = a25.fontSizeScale;
        }
        if (a25.windowSize !== undefined) {
            this.windowSize = a25.windowSize;
        }
        if (a25.updateButtonHeight !== undefined) {
            this.updateButtonHeight = a25.updateButtonHeight;
        }
    }

    updateStateVars(z24) {
    }

    purgeVariableDependenciesOnElmtId(y24) {
        this.__imageSize.purgeDependencyOnElmtId(y24);
        this.__isChecked.purgeDependencyOnElmtId(y24);
        this.__imageSizeHeight.purgeDependencyOnElmtId(y24);
        this.__textAlignment.purgeDependencyOnElmtId(y24);
        this.__checkBoxHeight.purgeDependencyOnElmtId(y24);
        this.__buttonHeight.purgeDependencyOnElmtId(y24);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(y24);
        this.__fontSizeScale.purgeDependencyOnElmtId(y24);
        this.__windowSize.purgeDependencyOnElmtId(y24);
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

    setController(x24) {
        this.controller = x24;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(w24) {
        this.__imageSize.set(w24);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(v24) {
        this.__isChecked.set(v24);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(u24) {
        this.__imageSizeHeight.set(u24);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(t24) {
        this.__textAlignment.set(t24);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(s24) {
        this.__checkBoxHeight.set(s24);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(r24) {
        this.__buttonHeight.set(r24);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(q24) {
        this.__fontColorWithTheme.set(q24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(p24) {
        this.__fontSizeScale.set(p24);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(o24) {
        this.__windowSize.set(o24);
    }

    initialRender() {
        this.observeComponentCreation2((m24, n24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((g24, h24) => {
                if (h24) {
                    let i24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, g24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 113, col: 5 });
                    ViewPU.create(i24);
                    let j24 = () => {
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
                    i24.paramsGenerator_ = j24;
                } else {
                    this.updateStateVarsOfChildByElmtId(g24, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(n23 = null) {
        this.observeComponentCreation2((c24, d24) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(n23 ? n23 : this);
        this.observeComponentCreation2((v23, w23) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a24, b24) => {
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
                    this.textPart.bind(this)(n23 ? n23 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((r23, s23) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, n23 ? n23 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(w22, x22 = null) {
        this.observeComponentCreation2((i23, j23) => {
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
            Row.onAreaChange((l23, m23) => {
                this.checkBoxHeight = Number(m23.height);
            });
        }, Row);
        this.observeComponentCreation2((e23, f23) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((h23) => {
                this.isChecked = h23;
                if (this.checkAction) {
                    this.checkAction(h23);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(h23);
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
        this.observeComponentCreation2((b23, c23) => {
            Text.create(w22);
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

    imagePart(m22 = null) {
        this.observeComponentCreation2((r22, s22) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((u22, v22) => {
                this.imageSizeHeight = Number(v22.height);
            });
        }, Column);
        this.observeComponentCreation2((p22, q22) => {
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

    textPart(e21 = null) {
        this.observeComponentCreation2((k22, l22) => {
            Scroll.create(this.contentScroller);
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((i22, j22) => {
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
        this.observeComponentCreation2((y21, z21) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g22, h22) => {
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
                    this.observeComponentCreation2((e22, f22) => {
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
        this.observeComponentCreation2((j21, k21) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w21, x21) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((p21, q21) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((v21) => {
                            if (v21) {
                                resolveKeyEvent(v21, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((t21, u21) => {
                            this.getTextAlign(Number(u21.width));
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

    getTextAlign(a21) {
        let b21 = this.getContentFontSize();
        let c21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: b21,
            constraintWidth: a21,
        });
        let d21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: b21,
        });
        if (this.getTextHeight(c21) <= this.getTextHeight(d21)) {
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

    getTextHeight(z20) {
        if (z20 && z20.height !== null && z20.height !== undefined) {
            return Number(z20.height);
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
    constructor(t20, u20, v20, w20 = -1, x20 = undefined, y20) {
        super(t20, v20, w20, y20);
        if (typeof x20 === 'function') {
            this.paramsGenerator_ = x20;
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
        this.setInitiallyProvidedValue(u20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s20) {
        if (s20.controller !== undefined) {
            this.controller = s20.controller;
        }
        if (s20.title !== undefined) {
            this.title = s20.title;
        }
        if (s20.content !== undefined) {
            this.content = s20.content;
        }
        if (s20.selectedIndex !== undefined) {
            this.selectedIndex = s20.selectedIndex;
        }
        if (s20.confirm !== undefined) {
            this.confirm = s20.confirm;
        }
        if (s20.radioContent !== undefined) {
            this.radioContent = s20.radioContent;
        }
        if (s20.buttons !== undefined) {
            this.buttons = s20.buttons;
        }
        if (s20.contentPadding !== undefined) {
            this.contentPadding = s20.contentPadding;
        }
        if (s20.isFocus !== undefined) {
            this.isFocus = s20.isFocus;
        }
        if (s20.currentFocusIndex !== undefined) {
            this.currentFocusIndex = s20.currentFocusIndex;
        }
        if (s20.radioHeight !== undefined) {
            this.radioHeight = s20.radioHeight;
        }
        if (s20.itemHeight !== undefined) {
            this.itemHeight = s20.itemHeight;
        }
        if (s20.contentBuilder !== undefined) {
            this.contentBuilder = s20.contentBuilder;
        }
        if (s20.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = s20.fontColorWithTheme;
        }
        if (s20.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = s20.dividerColorWithTheme;
        }
        if (s20.theme !== undefined) {
            this.theme = s20.theme;
        }
        if (s20.themeColorMode !== undefined) {
            this.themeColorMode = s20.themeColorMode;
        }
        if (s20.contentScroller !== undefined) {
            this.contentScroller = s20.contentScroller;
        }
        if (s20.fontSizeScale !== undefined) {
            this.fontSizeScale = s20.fontSizeScale;
        }
        if (s20.windowSize !== undefined) {
            this.windowSize = s20.windowSize;
        }
    }

    updateStateVars(r20) {
    }

    purgeVariableDependenciesOnElmtId(q20) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(q20);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(q20);
        this.__fontSizeScale.purgeDependencyOnElmtId(q20);
        this.__windowSize.purgeDependencyOnElmtId(q20);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(p20) {
        this.controller = p20;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(o20) {
        this.__fontColorWithTheme.set(o20);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(n20) {
        this.__dividerColorWithTheme.set(n20);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(m20) {
        this.__fontSizeScale.set(m20);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(l20) {
        this.__windowSize.set(l20);
    }

    buildContent(m17 = null) {
        this.observeComponentCreation2((f20, g20) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.onDidScroll((i20, j20) => {
                let k20 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (j20 > 0) {
                            this.contentScroller.scrollBy(0, k20);
                        } else if (j20 < 0) {
                            this.contentScroller.scrollBy(0, 0 - k20);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((d20, e20) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((t19, u19) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b20, c20) => {
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
                    this.observeComponentCreation2((z19, a20) => {
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
        this.observeComponentCreation2((q19, r19) => {
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
        this.observeComponentCreation2((s17, t17) => {
            ForEach.create();
            const u17 = (w17, x17) => {
                const y17 = w17;
                {
                    const z17 = (o19, p19) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o19);
                        a18(o19, p19);
                        if (!p19) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const a18 = (j19, k19) => {
                        ListItem.create(b18, true);
                        ListItem.onSizeChange((m19, n19) => {
                            this.itemHeight = Number(n19.height);
                        });
                    };
                    const b18 = (f18, g18) => {
                        z17(f18, g18);
                        this.observeComponentCreation2((h19, i19) => {
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
                        this.observeComponentCreation2((e19, f19) => {
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
                                y17.action && y17.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((c19, d19) => {
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
                        this.observeComponentCreation2((a19, b19) => {
                            Text.create(y17.title);
                            Text.fontSize(this.getListFontSize());
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((u18, v18) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === x17);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(x17));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = x17;
                                if (x17 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (x17 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((y18, z18) => {
                                this.radioHeight = Number(z18.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((n18, o18) => {
                            If.create();
                            if (x17 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((s18, t18) => {
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
                    this.observeComponentCreation2(a18, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(s17, this.radioContent, u17, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((k17, l17) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((e17, f17) => {
                if (f17) {
                    let g17 = new CustomDialogContentComponent(this, {
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
                    }, undefined, e17, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 455, col: 5 });
                    ViewPU.create(g17);
                    let h17 = () => {
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
                    g17.paramsGenerator_ = h17;
                } else {
                    this.updateStateVarsOfChildByElmtId(e17, {});
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
    constructor(s16, t16, u16, v16 = -1, w16 = undefined, x16) {
        super(s16, u16, v16, x16);
        if (typeof w16 === 'function') {
            this.paramsGenerator_ = w16;
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
        this.updateTitleHeight = (b17) => {
            this.titleHeight = b17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (a17) => {
            this.buttonHeight = a17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(t16);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r16) {
        if (r16.controller !== undefined) {
            this.controller = r16.controller;
        }
        if (r16.title !== undefined) {
            this.title = r16.title;
        }
        if (r16.content !== undefined) {
            this.content = r16.content;
        }
        if (r16.checkTips !== undefined) {
            this.checkTips = r16.checkTips;
        }
        if (r16.isChecked !== undefined) {
            this.isChecked = r16.isChecked;
        }
        if (r16.primaryButton !== undefined) {
            this.primaryButton = r16.primaryButton;
        }
        if (r16.secondaryButton !== undefined) {
            this.secondaryButton = r16.secondaryButton;
        }
        if (r16.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = r16.fontColorWithTheme;
        }
        if (r16.theme !== undefined) {
            this.theme = r16.theme;
        }
        if (r16.themeColorMode !== undefined) {
            this.themeColorMode = r16.themeColorMode;
        }
        if (r16.onCheckedChange !== undefined) {
            this.onCheckedChange = r16.onCheckedChange;
        }
        if (r16.contentScroller !== undefined) {
            this.contentScroller = r16.contentScroller;
        }
        if (r16.buttons !== undefined) {
            this.buttons = r16.buttons;
        }
        if (r16.marginOffset !== undefined) {
            this.marginOffset = r16.marginOffset;
        }
        if (r16.titleHeight !== undefined) {
            this.titleHeight = r16.titleHeight;
        }
        if (r16.buttonHeight !== undefined) {
            this.buttonHeight = r16.buttonHeight;
        }
        if (r16.checkBoxHeight !== undefined) {
            this.checkBoxHeight = r16.checkBoxHeight;
        }
        if (r16.fontSizeScale !== undefined) {
            this.fontSizeScale = r16.fontSizeScale;
        }
        if (r16.windowSize !== undefined) {
            this.windowSize = r16.windowSize;
        }
        if (r16.maxContentHeight !== undefined) {
            this.maxContentHeight = r16.maxContentHeight;
        }
        if (r16.updateTitleHeight !== undefined) {
            this.updateTitleHeight = r16.updateTitleHeight;
        }
        if (r16.updateButtonHeight !== undefined) {
            this.updateButtonHeight = r16.updateButtonHeight;
        }
    }

    updateStateVars(q16) {
    }

    purgeVariableDependenciesOnElmtId(p16) {
        this.__isChecked.purgeDependencyOnElmtId(p16);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(p16);
        this.__titleHeight.purgeDependencyOnElmtId(p16);
        this.__buttonHeight.purgeDependencyOnElmtId(p16);
        this.__checkBoxHeight.purgeDependencyOnElmtId(p16);
        this.__fontSizeScale.purgeDependencyOnElmtId(p16);
        this.__windowSize.purgeDependencyOnElmtId(p16);
        this.__maxContentHeight.purgeDependencyOnElmtId(p16);
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

    setController(o16) {
        this.controller = o16;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(n16) {
        this.__isChecked.set(n16);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(m16) {
        this.__fontColorWithTheme.set(m16);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(l16) {
        this.__titleHeight.set(l16);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(k16) {
        this.__buttonHeight.set(k16);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(j16) {
        this.__checkBoxHeight.set(j16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(i16) {
        this.__fontSizeScale.set(i16);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(h16) {
        this.__windowSize.set(h16);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(g16) {
        this.__maxContentHeight.set(g16);
    }

    buildContent(x14 = null) {
        this.observeComponentCreation2((e16, f16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((p15, q15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c16, d16) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((a16, b16) => {
                        Scroll.create(this.contentScroller);
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((w15, x15) => {
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
                        Text.onKeyEvent((z15) => {
                            if (z15) {
                                resolveKeyEvent(z15, this.contentScroller);
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
        this.observeComponentCreation2((k15, l15) => {
            Row.create();
            Row.onSizeChange((n15, o15) => {
                this.checkBoxHeight = Number(o15.height);
                this.maxContentHeight =
                    `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((g15, h15) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((j15) => {
                this.isChecked = j15;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((d15, e15) => {
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
        this.observeComponentCreation2((v14, w14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p14, q14) => {
                if (q14) {
                    let r14 = new CustomDialogContentComponent(this, {
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
                    }, undefined, p14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 638, col: 5 });
                    ViewPU.create(r14);
                    let s14 = () => {
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
                    r14.paramsGenerator_ = s14;
                } else {
                    this.updateStateVarsOfChildByElmtId(p14, {});
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
    constructor(h14, i14, j14, k14 = -1, l14 = undefined, m14) {
        super(h14, j14, k14, m14);
        if (typeof l14 === 'function') {
            this.paramsGenerator_ = l14;
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
        this.setInitiallyProvidedValue(i14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g14) {
        if (g14.controller !== undefined) {
            this.controller = g14.controller;
        }
        if (g14.primaryTitle !== undefined) {
            this.primaryTitle = g14.primaryTitle;
        }
        if (g14.secondaryTitle !== undefined) {
            this.secondaryTitle = g14.secondaryTitle;
        }
        if (g14.content !== undefined) {
            this.content = g14.content;
        }
        if (g14.primaryButton !== undefined) {
            this.primaryButton = g14.primaryButton;
        }
        if (g14.secondaryButton !== undefined) {
            this.secondaryButton = g14.secondaryButton;
        }
        if (g14.buttons !== undefined) {
            this.buttons = g14.buttons;
        }
        if (g14.textAlign !== undefined) {
            this.textAlign = g14.textAlign;
        }
        if (g14.contentScroller !== undefined) {
            this.contentScroller = g14.contentScroller;
        }
        if (g14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = g14.fontColorWithTheme;
        }
        if (g14.theme !== undefined) {
            this.theme = g14.theme;
        }
        if (g14.themeColorMode !== undefined) {
            this.themeColorMode = g14.themeColorMode;
        }
        if (g14.windowSize !== undefined) {
            this.windowSize = g14.windowSize;
        }
        if (g14.fontSizeScale !== undefined) {
            this.fontSizeScale = g14.fontSizeScale;
        }
    }

    updateStateVars(f14) {
    }

    purgeVariableDependenciesOnElmtId(e14) {
        this.__textAlign.purgeDependencyOnElmtId(e14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(e14);
        this.__windowSize.purgeDependencyOnElmtId(e14);
        this.__fontSizeScale.purgeDependencyOnElmtId(e14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(d14) {
        this.controller = d14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(c14) {
        this.__textAlign.set(c14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(b14) {
        this.__fontColorWithTheme.set(b14);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(a14) {
        this.__windowSize.set(a14);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(z13) {
        this.__fontSizeScale.set(z13);
    }

    initialRender() {
        this.observeComponentCreation2((x13, y13) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((r13, s13) => {
                if (s13) {
                    let t13 = new CustomDialogContentComponent(this, {
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
                    }, undefined, r13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 698, col: 5 });
                    ViewPU.create(t13);
                    let u13 = () => {
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
                    t13.paramsGenerator_ = u13;
                } else {
                    this.updateStateVarsOfChildByElmtId(r13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(a13 = null) {
        this.observeComponentCreation2((n13, o13) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((l13, m13) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((e13, f13) => {
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
            Text.onAreaChange((j13, k13) => {
                this.getTextAlign(Number(k13.width));
            });
            Text.onKeyEvent((i13) => {
                if (i13) {
                    resolveKeyEvent(i13, this.contentScroller);
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

    getTextAlign(w12) {
        let x12 = this.getContentFontSize();
        let y12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: x12,
            constraintWidth: w12,
        });
        let z12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: x12,
        });
        if (this.getTextHeight(y12) <= this.getTextHeight(z12)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(v12) {
        if (v12 && v12.height !== null && v12.height !== undefined) {
            return Number(v12.height);
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
    constructor(p12, q12, r12, s12 = -1, t12 = undefined, u12) {
        super(p12, r12, s12, u12);
        if (typeof t12 === 'function') {
            this.paramsGenerator_ = t12;
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
        this.setInitiallyProvidedValue(q12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o12) {
        if (o12.controller !== undefined) {
            this.controller = o12.controller;
        }
        if (o12.primaryTitle !== undefined) {
            this.primaryTitle = o12.primaryTitle;
        }
        if (o12.secondaryTitle !== undefined) {
            this.secondaryTitle = o12.secondaryTitle;
        }
        if (o12.contentBuilder !== undefined) {
            this.contentBuilder = o12.contentBuilder;
        }
        if (o12.contentAreaPadding !== undefined) {
            this.contentAreaPadding = o12.contentAreaPadding;
        }
        if (o12.buttons !== undefined) {
            this.buttons = o12.buttons;
        }
        if (o12.theme !== undefined) {
            this.theme = o12.theme;
        }
        if (o12.themeColorMode !== undefined) {
            this.themeColorMode = o12.themeColorMode;
        }
        if (o12.fontSizeScale !== undefined) {
            this.fontSizeScale = o12.fontSizeScale;
        }
        if (o12.windowSize !== undefined) {
            this.windowSize = o12.windowSize;
        }
    }

    updateStateVars(n12) {
    }

    purgeVariableDependenciesOnElmtId(m12) {
        this.__fontSizeScale.purgeDependencyOnElmtId(m12);
        this.__windowSize.purgeDependencyOnElmtId(m12);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(l12) {
        this.controller = l12;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k12) {
        this.__fontSizeScale.set(k12);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(j12) {
        this.__windowSize.set(j12);
    }

    initialRender() {
        this.observeComponentCreation2((h12, i12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((b12, c12) => {
                if (c12) {
                    let d12 = new CustomDialogContentComponent(this, {
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
                    }, undefined, b12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 816, col: 5 });
                    ViewPU.create(d12);
                    let e12 = () => {
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
                    d12.paramsGenerator_ = e12;
                } else {
                    this.updateStateVarsOfChildByElmtId(b12, {});
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
    constructor(t11, u11, v11, w11 = -1, x11 = undefined, y11) {
        super(t11, v11, w11, y11);
        if (typeof x11 === 'function') {
            this.paramsGenerator_ = x11;
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
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(u11.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(u11.windowSize, this, 'windowSize');
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
        this.setInitiallyProvidedValue(u11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s11) {
        if (s11.controller !== undefined) {
            this.controller = s11.controller;
        }
        if (s11.primaryTitle !== undefined) {
            this.primaryTitle = s11.primaryTitle;
        }
        if (s11.secondaryTitle !== undefined) {
            this.secondaryTitle = s11.secondaryTitle;
        }
        if (s11.contentBuilder !== undefined) {
            this.contentBuilder = s11.contentBuilder;
        }
        if (s11.buttons !== undefined) {
            this.buttons = s11.buttons;
        }
        if (s11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = s11.contentAreaPadding;
        }
        if (s11.keyIndex !== undefined) {
            this.keyIndex = s11.keyIndex;
        }
        if (s11.theme !== undefined) {
            this.theme = s11.theme;
        }
        if (s11.themeColorMode !== undefined) {
            this.themeColorMode = s11.themeColorMode;
        }
        if (s11.titleHeight !== undefined) {
            this.titleHeight = s11.titleHeight;
        }
        if (s11.buttonHeight !== undefined) {
            this.buttonHeight = s11.buttonHeight;
        }
        if (s11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = s11.contentMaxHeight;
        }
        if (s11.updateTitleHeight !== undefined) {
            this.updateTitleHeight = s11.updateTitleHeight;
        }
        if (s11.updateButtonHeight !== undefined) {
            this.updateButtonHeight = s11.updateButtonHeight;
        }
        if (s11.targetSdk !== undefined) {
            this.targetSdk = s11.targetSdk;
        }
        if (s11.customStyle !== undefined) {
            this.customStyle = s11.customStyle;
        }
        if (s11.needResponseScale !== undefined) {
            this.needResponseScale = s11.needResponseScale;
        }
        if (s11.screenSize !== undefined) {
            this.screenSize = s11.screenSize;
        }
        if (s11.initCustomStyle !== undefined) {
            this.initCustomStyle = s11.initCustomStyle;
        }
        if (s11.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = s11.buttonMaxFontSize;
        }
        if (s11.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = s11.buttonMinFontSize;
        }
    }

    updateStateVars(r11) {
    }

    purgeVariableDependenciesOnElmtId(q11) {
        this.__titleHeight.purgeDependencyOnElmtId(q11);
        this.__buttonHeight.purgeDependencyOnElmtId(q11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(q11);
        this.__fontSizeScale.purgeDependencyOnElmtId(q11);
        this.__windowSize.purgeDependencyOnElmtId(q11);
        this.__customStyle.purgeDependencyOnElmtId(q11);
        this.__needResponseScale.purgeDependencyOnElmtId(q11);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(q11);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(q11);
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

    defaultContentBuilder(p11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(o11) {
        this.__titleHeight.set(o11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(n11) {
        this.__buttonHeight.set(n11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(m11) {
        this.__contentMaxHeight.set(m11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(l11) {
        this.__fontSizeScale.set(l11);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(k11) {
        this.__windowSize.set(k11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(j11) {
        this.__customStyle.set(j11);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(i11) {
        this.__needResponseScale.set(i11);
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(h11) {
        this.__buttonMaxFontSize.set(h11);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(g11) {
        this.__buttonMinFontSize.set(g11);
    }

    initialRender() {
        this.observeComponentCreation2((e11, f11) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((c11, d11) => {
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
        this.observeComponentCreation2((a11, b11) => {
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
            this.observeComponentCreation2((u10, v10) => {
                if (v10) {
                    let w10 = new TitleComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        titleHeight: this.__titleHeight,
                        needResponseScale: this.__needResponseScale,
                        theme: this.theme
                    }, undefined, u10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 869, col: 11 });
                    ViewPU.create(w10);
                    let x10 = () => {
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
                    w10.paramsGenerator_ = x10;
                } else {
                    this.updateStateVarsOfChildByElmtId(u10, {});
                }
            }, { name: 'TitleComponent' });
        }
        this.observeComponentCreation2((r10, s10) => {
            Column.create();
            Column.padding(this.getContentPadding());
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
        }, Column);
        this.contentBuilder.bind(this)(this);
        Column.pop();
        {
            this.observeComponentCreation2((l10, m10) => {
                if (m10) {
                    let n10 = new ButtonComponent(this, {
                        buttons: this.buttons,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        needResponseScale: this.__needResponseScale,
                        buttonHeight: this.__buttonHeight,
                        controller: this.controller,
                        theme: this.theme,
                        buttonMaxFontSize: this.__buttonMaxFontSize,
                        buttonMinFontSize: this.__buttonMinFontSize
                    }, undefined, l10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 885, col: 11 });
                    ViewPU.create(n10);
                    let o10 = () => {
                        return {
                            buttons: this.buttons,
                            windowSize: this.windowSize,
                            fontSizeScale: this.fontSizeScale,
                            needResponseScale: this.needResponseScale,
                            buttonHeight: this.buttonHeight,
                            controller: this.controller,
                            theme: this.theme,
                            buttonMaxFontSize: this.buttonMaxFontSize,
                            buttonMinFontSize: this.buttonMinFontSize
                        };
                    };
                    n10.paramsGenerator_ = o10;
                } else {
                    this.updateStateVarsOfChildByElmtId(l10, {});
                }
            }, { name: 'ButtonComponent' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(x9, y9, z9) {
        let a10 = { width: x9.width, height: x9.height };
        let b10 = Number(z9.maxWidth);
        let c10 = Number(z9.maxHeight);
        this.windowSize = { width: b10, height: c10 };
        this.updateFontScale();
        this.updateNeedResponseScale();
        this.updateCustomStyle(Number(z9.maxWidth), Number(z9.maxHeight));
        this.updateFontSize();
        y9.forEach((e10) => {
            let f10 = e10.measure(z9);
            if (this.updateButtonHeight) {
                this.updateButtonHeight(this.buttonHeight);
            }
            if (this.updateTitleHeight) {
                this.updateTitleHeight(this.titleHeight);
            }
            if (c10 - this.buttonHeight - this.titleHeight < MIN_CONTENT_HEIGHT) {
                this.contentMaxHeight = `${MAX_CONTENT_HEIGHT}vp`;
            } else {
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            }
            f10 = e10.measure(z9);
            a10.height = f10.height;
            a10.width = f10.width;
        });
        return a10;
    }

    updateCustomStyle(v9, w9) {
        if (this.initCustomStyle) {
            return;
        }
        if (this.targetSdk >= VERSION_TWELVE) {
            return;
        }
        if (this.screenSize.width > MAX_DIALOG_WIDTH) {
            this.customStyle = v9 > MAX_DIALOG_WIDTH;
        } else {
            this.customStyle = v9 >= this.screenSize.width;
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
            let u9 = display.getDefaultDisplaySync();
            this.screenSize = { width: px2vp(u9.width), height: px2vp(u9.height) };
        } catch (r9) {
            let s9 = r9.code;
            let t9 = r9.message;
            hilog.error(0x3900, 'Ace', `Faild to init windowsize,cause, code: ${s9}, message: ${t9}`);
        }
        this.updateFontScale();
        try {
            let q9 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            this.targetSdk = bundleManager.getBundleInfoForSelfSync(q9).targetVersion;
        } catch (n9) {
            let o9 = n9.code;
            let p9 = n9.message;
            hilog.error(0x3900, 'Ace', `Faild to init bundle info,cause, code: ${o9}, message: ${p9}`);
        }
    }

    updateFontScale() {
        try {
            let m9 = this.getUIContext().getHostContext();
            this.fontSizeScale = m9.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (j9) {
            let k9 = j9.code;
            let l9 = j9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${k9}, message: ${l9}`);
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
    constructor(d9, e9, f9, g9 = -1, h9 = undefined, i9) {
        super(d9, f9, g9, i9);
        if (typeof h9 === 'function') {
            this.paramsGenerator_ = h9;
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
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(e9.needResponseScale, this, 'needResponseScale');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(e9.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(e9.windowSize, this, 'windowSize');
        this.__titleHeight = new SynchedPropertyObjectTwoWayPU(e9.titleHeight, this, 'titleHeight');
        this.setInitiallyProvidedValue(e9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c9) {
        if (c9.primaryTitle !== undefined) {
            this.primaryTitle = c9.primaryTitle;
        }
        if (c9.secondaryTitle !== undefined) {
            this.secondaryTitle = c9.secondaryTitle;
        }
        if (c9.theme !== undefined) {
            this.theme = c9.theme;
        }
        if (c9.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = c9.primaryTitleFontColorWithTheme;
        }
        if (c9.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = c9.secondaryTitleFontColorWithTheme;
        }
        if (c9.titleTextAlign !== undefined) {
            this.titleTextAlign = c9.titleTextAlign;
        }
        if (c9.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = c9.primaryTitleMaxFontSize;
        }
        if (c9.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = c9.primaryTitleMinFontSize;
        }
        if (c9.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = c9.secondaryTitleMaxFontSize;
        }
        if (c9.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = c9.secondaryTitleMinFontSize;
        }
    }

    updateStateVars(b9) {
    }

    purgeVariableDependenciesOnElmtId(a9) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(a9);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(a9);
        this.__titleTextAlign.purgeDependencyOnElmtId(a9);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(a9);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(a9);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(a9);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(a9);
        this.__needResponseScale.purgeDependencyOnElmtId(a9);
        this.__fontSizeScale.purgeDependencyOnElmtId(a9);
        this.__windowSize.purgeDependencyOnElmtId(a9);
        this.__titleHeight.purgeDependencyOnElmtId(a9);
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

    set primaryTitleFontColorWithTheme(z8) {
        this.__primaryTitleFontColorWithTheme.set(z8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(y8) {
        this.__secondaryTitleFontColorWithTheme.set(y8);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(x8) {
        this.__titleTextAlign.set(x8);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(w8) {
        this.__primaryTitleMaxFontSize.set(w8);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(v8) {
        this.__primaryTitleMinFontSize.set(v8);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(u8) {
        this.__secondaryTitleMaxFontSize.set(u8);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(t8) {
        this.__secondaryTitleMinFontSize.set(t8);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(s8) {
        this.__needResponseScale.set(s8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(r8) {
        this.__fontSizeScale.set(r8);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(q8) {
        this.__windowSize.set(q8);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(p8) {
        this.__titleHeight.set(p8);
    }

    initialRender() {
        this.observeComponentCreation2((n8, o8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((l8, m8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((j8, k8) => {
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
        this.observeComponentCreation2((z7, a8) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h8, i8) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((f8, g8) => {
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
        this.observeComponentCreation2((x7, y7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((v7, w7) => {
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

    onMeasureSize(h7, i7, j7) {
        let k7 = { width: h7.width, height: h7.height };
        this.updateFontSize();
        let l7 = {
            minWidth: j7.minWidth,
            minHeight: this.getTitleAreaMinHeight(),
            maxWidth: j7.maxWidth,
            maxHeight: j7.maxHeight
        };
        i7.forEach((n7) => {
            let o7 = n7.measure(l7);
            k7.height = o7.height;
            k7.width = o7.width;
        });
        this.titleHeight = k7.height;
        return k7;
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
        let g7 = getEnumNumberByResource('alert_title_alignment');
        if (g7 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (g7 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (g7 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (g7 === TextAlign.JUSTIFY) {
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
    constructor(a7, b7, c7, d7 = -1, e7 = undefined, f7) {
        super(a7, c7, d7, f7);
        if (typeof e7 === 'function') {
            this.paramsGenerator_ = e7;
        }
        this.controller = undefined;
        this.buttons = undefined;
        this.__buttonMaxFontSize = new SynchedPropertyObjectTwoWayPU(b7.buttonMaxFontSize, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new SynchedPropertyObjectTwoWayPU(b7.buttonMinFontSize, this, 'buttonMinFontSize');
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.__singleButtonHeight = new ObservedPropertySimplePU(BUTTON_DEFAULT_HEIGHT, this, 'singleButtonHeight');
        this.__isButtonVertical = new ObservedPropertySimplePU(false, this, 'isButtonVertical');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(b7.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(b7.windowSize, this, 'windowSize');
        this.__buttonHeight = new SynchedPropertyObjectTwoWayPU(b7.buttonHeight, this, 'buttonHeight');
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(b7.needResponseScale, this, 'needResponseScale');
        this.setInitiallyProvidedValue(b7);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z6) {
        if (z6.controller !== undefined) {
            this.controller = z6.controller;
        }
        if (z6.buttons !== undefined) {
            this.buttons = z6.buttons;
        }
        if (z6.keyIndex !== undefined) {
            this.keyIndex = z6.keyIndex;
        }
        if (z6.theme !== undefined) {
            this.theme = z6.theme;
        }
        if (z6.singleButtonHeight !== undefined) {
            this.singleButtonHeight = z6.singleButtonHeight;
        }
        if (z6.isButtonVertical !== undefined) {
            this.isButtonVertical = z6.isButtonVertical;
        }
    }

    updateStateVars(y6) {
    }

    purgeVariableDependenciesOnElmtId(x6) {
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(x6);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(x6);
        this.__singleButtonHeight.purgeDependencyOnElmtId(x6);
        this.__isButtonVertical.purgeDependencyOnElmtId(x6);
        this.__fontSizeScale.purgeDependencyOnElmtId(x6);
        this.__windowSize.purgeDependencyOnElmtId(x6);
        this.__buttonHeight.purgeDependencyOnElmtId(x6);
        this.__needResponseScale.purgeDependencyOnElmtId(x6);
    }

    aboutToBeDeleted() {
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        this.__singleButtonHeight.aboutToBeDeleted();
        this.__isButtonVertical.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__needResponseScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }

    set buttonMaxFontSize(w6) {
        this.__buttonMaxFontSize.set(w6);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(v6) {
        this.__buttonMinFontSize.set(v6);
    }

    get singleButtonHeight() {
        return this.__singleButtonHeight.get();
    }

    set singleButtonHeight(u6) {
        this.__singleButtonHeight.set(u6);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(t6) {
        this.__isButtonVertical.set(t6);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(s6) {
        this.__fontSizeScale.set(s6);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(r6) {
        this.__windowSize.set(r6);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(q6) {
        this.__buttonHeight.set(q6);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(p6) {
        this.__needResponseScale.set(p6);
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
        this.updateFontSize();
        this.isButtonVertical =
            this.isVerticalAlignButton(Math.min(this.windowSize.width - BUTTON_HORIZONTAL_MARGIN * 2,
                MAX_DIALOG_WIDTH));
    }

    onMeasureSize(v5, w5, x5) {
        let y5 = { width: v5.width, height: v5.height };
        this.updateFontSize();
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
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1541, col: 7 });
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
