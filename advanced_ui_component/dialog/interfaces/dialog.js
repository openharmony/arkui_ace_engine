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
    constructor(s25) {
        this.colors = s25;
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
    constructor(k25, l25, m25, n25 = -1, o25 = undefined, p25) {
        super(k25, m25, n25, p25);
        if (typeof o25 === 'function') {
            this.paramsGenerator_ = o25;
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
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.updateButtonHeight = (r25) => {
            this.buttonHeight = r25;
        };
        this.setInitiallyProvidedValue(l25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j25) {
        if (j25.controller !== undefined) {
            this.controller = j25.controller;
        }
        if (j25.imageRes !== undefined) {
            this.imageRes = j25.imageRes;
        }
        if (j25.imageSize !== undefined) {
            this.imageSize = j25.imageSize;
        }
        if (j25.title !== undefined) {
            this.title = j25.title;
        }
        if (j25.content !== undefined) {
            this.content = j25.content;
        }
        if (j25.checkAction !== undefined) {
            this.checkAction = j25.checkAction;
        }
        if (j25.onCheckedChange !== undefined) {
            this.onCheckedChange = j25.onCheckedChange;
        }
        if (j25.checkTips !== undefined) {
            this.checkTips = j25.checkTips;
        }
        if (j25.isChecked !== undefined) {
            this.isChecked = j25.isChecked;
        }
        if (j25.primaryButton !== undefined) {
            this.primaryButton = j25.primaryButton;
        }
        if (j25.secondaryButton !== undefined) {
            this.secondaryButton = j25.secondaryButton;
        }
        if (j25.buttons !== undefined) {
            this.buttons = j25.buttons;
        }
        if (j25.imageSizeHeight !== undefined) {
            this.imageSizeHeight = j25.imageSizeHeight;
        }
        if (j25.textAlignment !== undefined) {
            this.textAlignment = j25.textAlignment;
        }
        if (j25.marginOffset !== undefined) {
            this.marginOffset = j25.marginOffset;
        }
        if (j25.checkBoxHeight !== undefined) {
            this.checkBoxHeight = j25.checkBoxHeight;
        }
        if (j25.buttonHeight !== undefined) {
            this.buttonHeight = j25.buttonHeight;
        }
        if (j25.contentScroller !== undefined) {
            this.contentScroller = j25.contentScroller;
        }
        if (j25.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = j25.fontColorWithTheme;
        }
        if (j25.theme !== undefined) {
            this.theme = j25.theme;
        }
        if (j25.fontSizeScale !== undefined) {
            this.fontSizeScale = j25.fontSizeScale;
        }
        if (j25.windowSize !== undefined) {
            this.windowSize = j25.windowSize;
        }
        if (j25.updateButtonHeight !== undefined) {
            this.updateButtonHeight = j25.updateButtonHeight;
        }
    }

    updateStateVars(i25) {
    }

    purgeVariableDependenciesOnElmtId(h25) {
        this.__imageSize.purgeDependencyOnElmtId(h25);
        this.__isChecked.purgeDependencyOnElmtId(h25);
        this.__imageSizeHeight.purgeDependencyOnElmtId(h25);
        this.__textAlignment.purgeDependencyOnElmtId(h25);
        this.__checkBoxHeight.purgeDependencyOnElmtId(h25);
        this.__buttonHeight.purgeDependencyOnElmtId(h25);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(h25);
        this.__fontSizeScale.purgeDependencyOnElmtId(h25);
        this.__windowSize.purgeDependencyOnElmtId(h25);
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

    setController(g25) {
        this.controller = g25;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(f25) {
        this.__imageSize.set(f25);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(e25) {
        this.__isChecked.set(e25);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(d25) {
        this.__imageSizeHeight.set(d25);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(c25) {
        this.__textAlignment.set(c25);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(b25) {
        this.__checkBoxHeight.set(b25);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(a25) {
        this.__buttonHeight.set(a25);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(z24) {
        this.__fontColorWithTheme.set(z24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(y24) {
        this.__fontSizeScale.set(y24);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(x24) {
        this.__windowSize.set(x24);
    }

    initialRender() {
        this.observeComponentCreation2((v24, w24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p24, q24) => {
                if (q24) {
                    let r24 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize,
                        updateButtonHeight: this.updateButtonHeight
                    }, undefined, p24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 112, col: 5 });
                    ViewPU.create(r24);
                    let s24 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize,
                            updateButtonHeight: this.updateButtonHeight
                        };
                    };
                    r24.paramsGenerator_ = s24;
                } else {
                    this.updateStateVarsOfChildByElmtId(p24, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(w23 = null) {
        this.observeComponentCreation2((l24, m24) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(w23 ? w23 : this);
        this.observeComponentCreation2((e24, f24) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j24, k24) => {
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
                    this.textPart.bind(this)(w23 ? w23 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((a24, b24) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, w23 ? w23 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(f23, g23 = null) {
        this.observeComponentCreation2((r23, s23) => {
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
            Row.onAreaChange((u23, v23) => {
                this.checkBoxHeight = Number(v23.height);
            });
        }, Row);
        this.observeComponentCreation2((n23, o23) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((q23) => {
                this.isChecked = q23;
                if (this.checkAction) {
                    this.checkAction(q23);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(q23);
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
        this.observeComponentCreation2((k23, l23) => {
            Text.create(f23);
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

    imagePart(v22 = null) {
        this.observeComponentCreation2((a23, b23) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((d23, e23) => {
                this.imageSizeHeight = Number(e23.height);
            });
        }, Column);
        this.observeComponentCreation2((y22, z22) => {
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

    textPart(n21 = null) {
        this.observeComponentCreation2((t22, u22) => {
            Scroll.create(this.contentScroller);
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((r22, s22) => {
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
        this.observeComponentCreation2((h22, i22) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p22, q22) => {
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
                    this.observeComponentCreation2((n22, o22) => {
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
        this.observeComponentCreation2((s21, t21) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f22, g22) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((y21, z21) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((e22) => {
                            if (e22) {
                                resolveKeyEvent(e22, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((c22, d22) => {
                            this.getTextAlign(Number(d22.width));
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

    getTextAlign(j21) {
        let k21 = this.getContentFontSize();
        let l21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: k21,
            constraintWidth: j21,
        });
        let m21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: k21,
        });
        if (this.getTextHeight(l21) <= this.getTextHeight(m21)) {
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

    getTextHeight(i21) {
        if (i21 && i21.height !== null && i21.height !== undefined) {
            return Number(i21.height);
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
    constructor(c21, d21, e21, f21 = -1, g21 = undefined, h21) {
        super(c21, e21, f21, h21);
        if (typeof g21 === 'function') {
            this.paramsGenerator_ = g21;
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
        this.contentScroller = new Scroller();
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.setInitiallyProvidedValue(d21);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b21) {
        if (b21.controller !== undefined) {
            this.controller = b21.controller;
        }
        if (b21.title !== undefined) {
            this.title = b21.title;
        }
        if (b21.content !== undefined) {
            this.content = b21.content;
        }
        if (b21.selectedIndex !== undefined) {
            this.selectedIndex = b21.selectedIndex;
        }
        if (b21.confirm !== undefined) {
            this.confirm = b21.confirm;
        }
        if (b21.radioContent !== undefined) {
            this.radioContent = b21.radioContent;
        }
        if (b21.buttons !== undefined) {
            this.buttons = b21.buttons;
        }
        if (b21.contentPadding !== undefined) {
            this.contentPadding = b21.contentPadding;
        }
        if (b21.isFocus !== undefined) {
            this.isFocus = b21.isFocus;
        }
        if (b21.currentFocusIndex !== undefined) {
            this.currentFocusIndex = b21.currentFocusIndex;
        }
        if (b21.radioHeight !== undefined) {
            this.radioHeight = b21.radioHeight;
        }
        if (b21.itemHeight !== undefined) {
            this.itemHeight = b21.itemHeight;
        }
        if (b21.contentBuilder !== undefined) {
            this.contentBuilder = b21.contentBuilder;
        }
        if (b21.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = b21.fontColorWithTheme;
        }
        if (b21.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = b21.dividerColorWithTheme;
        }
        if (b21.theme !== undefined) {
            this.theme = b21.theme;
        }
        if (b21.contentScroller !== undefined) {
            this.contentScroller = b21.contentScroller;
        }
        if (b21.fontSizeScale !== undefined) {
            this.fontSizeScale = b21.fontSizeScale;
        }
        if (b21.windowSize !== undefined) {
            this.windowSize = b21.windowSize;
        }
    }

    updateStateVars(a21) {
    }

    purgeVariableDependenciesOnElmtId(z20) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(z20);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(z20);
        this.__fontSizeScale.purgeDependencyOnElmtId(z20);
        this.__windowSize.purgeDependencyOnElmtId(z20);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(y20) {
        this.controller = y20;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(x20) {
        this.__fontColorWithTheme.set(x20);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(w20) {
        this.__dividerColorWithTheme.set(w20);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(v20) {
        this.__fontSizeScale.set(v20);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(u20) {
        this.__windowSize.set(u20);
    }

    buildContent(v17 = null) {
        this.observeComponentCreation2((o20, p20) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.onDidScroll((r20, s20) => {
                let t20 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (s20 > 0) {
                            this.contentScroller.scrollBy(0, t20);
                        } else if (s20 < 0) {
                            this.contentScroller.scrollBy(0, 0 - t20);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((m20, n20) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((c20, d20) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k20, l20) => {
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
                    this.observeComponentCreation2((i20, j20) => {
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
        this.observeComponentCreation2((z19, a20) => {
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
        this.observeComponentCreation2((b18, c18) => {
            ForEach.create();
            const d18 = (f18, g18) => {
                const h18 = f18;
                {
                    const i18 = (x19, y19) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x19);
                        j18(x19, y19);
                        if (!y19) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const j18 = (s19, t19) => {
                        ListItem.create(k18, true);
                        ListItem.onSizeChange((v19, w19) => {
                            this.itemHeight = Number(w19.height);
                        });
                    };
                    const k18 = (o18, p18) => {
                        i18(o18, p18);
                        this.observeComponentCreation2((q19, r19) => {
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
                        this.observeComponentCreation2((n19, o19) => {
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
                                h18.action && h18.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((l19, m19) => {
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
                        this.observeComponentCreation2((j19, k19) => {
                            Text.create(h18.title);
                            Text.fontSize(this.getListFontSize());
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((d19, e19) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === g18);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(g18));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = g18;
                                if (g18 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (g18 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((h19, i19) => {
                                this.radioHeight = Number(i19.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((w18, x18) => {
                            If.create();
                            if (g18 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((b19, c19) => {
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
                    this.observeComponentCreation2(j18, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(b18, this.radioContent, d18, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((t17, u17) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((n17, o17) => {
                if (o17) {
                    let p17 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        contentAreaPadding: this.contentPadding,
                        theme: this.theme,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, n17, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 452, col: 5 });
                    ViewPU.create(p17);
                    let q17 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.title,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            contentAreaPadding: this.contentPadding,
                            theme: this.theme,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    p17.paramsGenerator_ = q17;
                } else {
                    this.updateStateVarsOfChildByElmtId(n17, {});
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
    constructor(b17, c17, d17, e17 = -1, f17 = undefined, g17) {
        super(b17, d17, e17, g17);
        if (typeof f17 === 'function') {
            this.paramsGenerator_ = f17;
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
        this.__buttonFontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonFontColorWithTheme');
        this.theme = new CustomThemeImpl({});
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
        this.updateTitleHeight = (k17) => {
            this.titleHeight = k17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (j17) => {
            this.buttonHeight = j17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(c17);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a17) {
        if (a17.controller !== undefined) {
            this.controller = a17.controller;
        }
        if (a17.title !== undefined) {
            this.title = a17.title;
        }
        if (a17.content !== undefined) {
            this.content = a17.content;
        }
        if (a17.checkTips !== undefined) {
            this.checkTips = a17.checkTips;
        }
        if (a17.isChecked !== undefined) {
            this.isChecked = a17.isChecked;
        }
        if (a17.primaryButton !== undefined) {
            this.primaryButton = a17.primaryButton;
        }
        if (a17.secondaryButton !== undefined) {
            this.secondaryButton = a17.secondaryButton;
        }
        if (a17.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = a17.fontColorWithTheme;
        }
        if (a17.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = a17.buttonFontColorWithTheme;
        }
        if (a17.theme !== undefined) {
            this.theme = a17.theme;
        }
        if (a17.onCheckedChange !== undefined) {
            this.onCheckedChange = a17.onCheckedChange;
        }
        if (a17.contentScroller !== undefined) {
            this.contentScroller = a17.contentScroller;
        }
        if (a17.buttons !== undefined) {
            this.buttons = a17.buttons;
        }
        if (a17.marginOffset !== undefined) {
            this.marginOffset = a17.marginOffset;
        }
        if (a17.titleHeight !== undefined) {
            this.titleHeight = a17.titleHeight;
        }
        if (a17.buttonHeight !== undefined) {
            this.buttonHeight = a17.buttonHeight;
        }
        if (a17.checkBoxHeight !== undefined) {
            this.checkBoxHeight = a17.checkBoxHeight;
        }
        if (a17.fontSizeScale !== undefined) {
            this.fontSizeScale = a17.fontSizeScale;
        }
        if (a17.windowSize !== undefined) {
            this.windowSize = a17.windowSize;
        }
        if (a17.maxContentHeight !== undefined) {
            this.maxContentHeight = a17.maxContentHeight;
        }
        if (a17.updateTitleHeight !== undefined) {
            this.updateTitleHeight = a17.updateTitleHeight;
        }
        if (a17.updateButtonHeight !== undefined) {
            this.updateButtonHeight = a17.updateButtonHeight;
        }
    }

    updateStateVars(z16) {
    }

    purgeVariableDependenciesOnElmtId(y16) {
        this.__isChecked.purgeDependencyOnElmtId(y16);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(y16);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(y16);
        this.__titleHeight.purgeDependencyOnElmtId(y16);
        this.__buttonHeight.purgeDependencyOnElmtId(y16);
        this.__checkBoxHeight.purgeDependencyOnElmtId(y16);
        this.__fontSizeScale.purgeDependencyOnElmtId(y16);
        this.__windowSize.purgeDependencyOnElmtId(y16);
        this.__maxContentHeight.purgeDependencyOnElmtId(y16);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__buttonFontColorWithTheme.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__maxContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(x16) {
        this.controller = x16;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(w16) {
        this.__isChecked.set(w16);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(v16) {
        this.__fontColorWithTheme.set(v16);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(u16) {
        this.__buttonFontColorWithTheme.set(u16);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(t16) {
        this.__titleHeight.set(t16);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(s16) {
        this.__buttonHeight.set(s16);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(r16) {
        this.__checkBoxHeight.set(r16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(q16) {
        this.__fontSizeScale.set(q16);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(p16) {
        this.__windowSize.set(p16);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(o16) {
        this.__maxContentHeight.set(o16);
    }

    buildContent(c15 = null) {
        this.observeComponentCreation2((m16, n16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((x15, y15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k16, l16) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((i16, j16) => {
                        Scroll.create(this.contentScroller);
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((e16, f16) => {
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
                        Text.onKeyEvent((h16) => {
                            if (h16) {
                                resolveKeyEvent(h16, this.contentScroller);
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
        this.observeComponentCreation2((s15, t15) => {
            Row.create();
            Row.onSizeChange((v15, w15) => {
                this.checkBoxHeight = Number(w15.height);
                this.maxContentHeight =
                    `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((q15, r15) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((m15, n15) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((p15) => {
                this.isChecked = p15;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        WithTheme.pop();
        this.observeComponentCreation2((j15, k15) => {
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
        this.observeComponentCreation2((a15, b15) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((u14, v14) => {
                if (v14) {
                    let w14 = new CustomDialogContentComponent(this, {
                        primaryTitle: this.title,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.buildContent();
                        },
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        theme: this.theme,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, u14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 636, col: 5 });
                    ViewPU.create(w14);
                    let x14 = () => {
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
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    w14.paramsGenerator_ = x14;
                } else {
                    this.updateStateVarsOfChildByElmtId(u14, {});
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
        this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
        this.theme.colors.fontEmphasize : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_emphasize'],
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
    constructor(m14, n14, o14, p14 = -1, q14 = undefined, r14) {
        super(m14, o14, p14, r14);
        if (typeof q14 === 'function') {
            this.paramsGenerator_ = q14;
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: MAX_DIALOG_WIDTH, height: 0 }, this, 'windowSize');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.setInitiallyProvidedValue(n14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(l14) {
        if (l14.controller !== undefined) {
            this.controller = l14.controller;
        }
        if (l14.primaryTitle !== undefined) {
            this.primaryTitle = l14.primaryTitle;
        }
        if (l14.secondaryTitle !== undefined) {
            this.secondaryTitle = l14.secondaryTitle;
        }
        if (l14.content !== undefined) {
            this.content = l14.content;
        }
        if (l14.primaryButton !== undefined) {
            this.primaryButton = l14.primaryButton;
        }
        if (l14.secondaryButton !== undefined) {
            this.secondaryButton = l14.secondaryButton;
        }
        if (l14.buttons !== undefined) {
            this.buttons = l14.buttons;
        }
        if (l14.textAlign !== undefined) {
            this.textAlign = l14.textAlign;
        }
        if (l14.contentScroller !== undefined) {
            this.contentScroller = l14.contentScroller;
        }
        if (l14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = l14.fontColorWithTheme;
        }
        if (l14.theme !== undefined) {
            this.theme = l14.theme;
        }
        if (l14.windowSize !== undefined) {
            this.windowSize = l14.windowSize;
        }
        if (l14.fontSizeScale !== undefined) {
            this.fontSizeScale = l14.fontSizeScale;
        }
    }

    updateStateVars(k14) {
    }

    purgeVariableDependenciesOnElmtId(j14) {
        this.__textAlign.purgeDependencyOnElmtId(j14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(j14);
        this.__windowSize.purgeDependencyOnElmtId(j14);
        this.__fontSizeScale.purgeDependencyOnElmtId(j14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(i14) {
        this.controller = i14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(h14) {
        this.__textAlign.set(h14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(g14) {
        this.__fontColorWithTheme.set(g14);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(f14) {
        this.__windowSize.set(f14);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(e14) {
        this.__fontSizeScale.set(e14);
    }

    initialRender() {
        this.observeComponentCreation2((c14, d14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((w13, x13) => {
                if (x13) {
                    let y13 = new CustomDialogContentComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.AlertDialogContentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize,
                    }, undefined, w13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 696, col: 5 });
                    ViewPU.create(y13);
                    let z13 = () => {
                        return {
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.AlertDialogContentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme,
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    y13.paramsGenerator_ = z13;
                } else {
                    this.updateStateVarsOfChildByElmtId(w13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(f13 = null) {
        this.observeComponentCreation2((s13, t13) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((q13, r13) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((j13, k13) => {
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
            Text.onAreaChange((o13, p13) => {
                this.getTextAlign(Number(p13.width));
            });
            Text.onKeyEvent((n13) => {
                if (n13) {
                    resolveKeyEvent(n13, this.contentScroller);
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

    getTextAlign(b13) {
        let c13 = this.getContentFontSize();
        let d13 = measure.measureTextSize({
            textContent: this.content,
            fontSize: c13,
            constraintWidth: b13,
        });
        let e13 = measure.measureTextSize({
            textContent: this.content,
            fontSize: c13,
        });
        if (this.getTextHeight(d13) <= this.getTextHeight(e13)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(a13) {
        if (a13 && a13.height !== null && a13.height !== undefined) {
            return Number(a13.height);
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
    constructor(u12, v12, w12, x12 = -1, y12 = undefined, z12) {
        super(u12, w12, x12, z12);
        if (typeof y12 === 'function') {
            this.paramsGenerator_ = y12;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.setInitiallyProvidedValue(v12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(t12) {
        if (t12.controller !== undefined) {
            this.controller = t12.controller;
        }
        if (t12.primaryTitle !== undefined) {
            this.primaryTitle = t12.primaryTitle;
        }
        if (t12.secondaryTitle !== undefined) {
            this.secondaryTitle = t12.secondaryTitle;
        }
        if (t12.contentBuilder !== undefined) {
            this.contentBuilder = t12.contentBuilder;
        }
        if (t12.contentAreaPadding !== undefined) {
            this.contentAreaPadding = t12.contentAreaPadding;
        }
        if (t12.buttons !== undefined) {
            this.buttons = t12.buttons;
        }
        if (t12.theme !== undefined) {
            this.theme = t12.theme;
        }
        if (t12.fontSizeScale !== undefined) {
            this.fontSizeScale = t12.fontSizeScale;
        }
        if (t12.windowSize !== undefined) {
            this.windowSize = t12.windowSize;
        }
    }

    updateStateVars(s12) {
    }

    purgeVariableDependenciesOnElmtId(r12) {
        this.__fontSizeScale.purgeDependencyOnElmtId(r12);
        this.__windowSize.purgeDependencyOnElmtId(r12);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(q12) {
        this.controller = q12;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(p12) {
        this.__fontSizeScale.set(p12);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(o12) {
        this.__windowSize.set(o12);
    }

    initialRender() {
        this.observeComponentCreation2((m12, n12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((g12, h12) => {
                if (h12) {
                    let i12 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, g12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 812, col: 5 });
                    ViewPU.create(i12);
                    let j12 = () => {
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
                            fontSizeScale: this.fontSizeScale,
                            windowSize: this.windowSize
                        };
                    };
                    i12.paramsGenerator_ = j12;
                } else {
                    this.updateStateVarsOfChildByElmtId(g12, {});
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
    constructor(y11, z11, a12, b12 = -1, c12 = undefined, d12) {
        super(y11, a12, b12, d12);
        if (typeof c12 === 'function') {
            this.paramsGenerator_ = c12;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = this.defaultContentBuilder;
        this.buttons = undefined;
        this.contentAreaPadding = undefined;
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight =
            new ObservedPropertySimplePU(`calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`, this,
                'contentMaxHeight');
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
        this.targetSdk = VERSION_TWELVE;
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(z11.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(z11.windowSize, this, 'windowSize');
        this.__customStyle = new ObservedPropertySimplePU(false, this, 'customStyle');
        this.__needResponseScale = new ObservedPropertySimplePU(true, this, 'needResponseScale');
        this.screenSize = { width: 0, height: 0 };
        this.initCustomStyle = false;
        this.setInitiallyProvidedValue(z11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x11) {
        if (x11.controller !== undefined) {
            this.controller = x11.controller;
        }
        if (x11.primaryTitle !== undefined) {
            this.primaryTitle = x11.primaryTitle;
        }
        if (x11.secondaryTitle !== undefined) {
            this.secondaryTitle = x11.secondaryTitle;
        }
        if (x11.contentBuilder !== undefined) {
            this.contentBuilder = x11.contentBuilder;
        }
        if (x11.buttons !== undefined) {
            this.buttons = x11.buttons;
        }
        if (x11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = x11.contentAreaPadding;
        }
        if (x11.keyIndex !== undefined) {
            this.keyIndex = x11.keyIndex;
        }
        if (x11.theme !== undefined) {
            this.theme = x11.theme;
        }
        if (x11.titleHeight !== undefined) {
            this.titleHeight = x11.titleHeight;
        }
        if (x11.buttonHeight !== undefined) {
            this.buttonHeight = x11.buttonHeight;
        }
        if (x11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = x11.contentMaxHeight;
        }
        if (x11.updateTitleHeight !== undefined) {
            this.updateTitleHeight = x11.updateTitleHeight;
        }
        if (x11.updateButtonHeight !== undefined) {
            this.updateButtonHeight = x11.updateButtonHeight;
        }
        if (x11.targetSdk !== undefined) {
            this.targetSdk = x11.targetSdk;
        }
        if (x11.customStyle !== undefined) {
            this.customStyle = x11.customStyle;
        }
        if (x11.needResponseScale !== undefined) {
            this.needResponseScale = x11.needResponseScale;
        }
        if (x11.screenSize !== undefined) {
            this.screenSize = x11.screenSize;
        }
        if (x11.initCustomStyle !== undefined) {
            this.initCustomStyle = x11.initCustomStyle;
        }
    }

    updateStateVars(w11) {
    }

    purgeVariableDependenciesOnElmtId(v11) {
        this.__titleHeight.purgeDependencyOnElmtId(v11);
        this.__buttonHeight.purgeDependencyOnElmtId(v11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(v11);
        this.__fontSizeScale.purgeDependencyOnElmtId(v11);
        this.__windowSize.purgeDependencyOnElmtId(v11);
        this.__customStyle.purgeDependencyOnElmtId(v11);
        this.__needResponseScale.purgeDependencyOnElmtId(v11);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__contentMaxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__customStyle.aboutToBeDeleted();
        this.__needResponseScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    defaultContentBuilder(u11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(t11) {
        this.__titleHeight.set(t11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(s11) {
        this.__buttonHeight.set(s11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(r11) {
        this.__contentMaxHeight.set(r11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(q11) {
        this.__fontSizeScale.set(q11);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(p11) {
        this.__windowSize.set(p11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(o11) {
        this.__customStyle.set(o11);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(n11) {
        this.__needResponseScale.set(n11);
    }

    initialRender() {
        this.observeComponentCreation2((l11, m11) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((j11, k11) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((h11, i11) => {
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
            this.observeComponentCreation2((b11, c11) => {
                if (c11) {
                    let d11 = new TitleComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        titleHeight: this.__titleHeight,
                        needResponseScale: this.__needResponseScale,
                        theme: this.theme
                    }, undefined, b11, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 861, col: 11 });
                    ViewPU.create(d11);
                    let e11 = () => {
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
                    d11.paramsGenerator_ = e11;
                } else {
                    this.updateStateVarsOfChildByElmtId(b11, {});
                }
            }, { name: 'TitleComponent' });
        }
        this.observeComponentCreation2((y10, z10) => {
            Column.create();
            Column.padding(this.getContentPadding());
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
        }, Column);
        this.contentBuilder.bind(this)(this);
        Column.pop();
        {
            this.observeComponentCreation2((s10, t10) => {
                if (t10) {
                    let u10 = new ButtonComponent(this, {
                        buttons: this.buttons,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        needResponseScale: this.__needResponseScale,
                        buttonHeight: this.__buttonHeight,
                        controller: this.controller,
                        theme: this.theme
                    }, undefined, s10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 877, col: 11 });
                    ViewPU.create(u10);
                    let v10 = () => {
                        return {
                            buttons: this.buttons,
                            windowSize: this.windowSize,
                            fontSizeScale: this.fontSizeScale,
                            needResponseScale: this.needResponseScale,
                            buttonHeight: this.buttonHeight,
                            controller: this.controller,
                            theme: this.theme
                        };
                    };
                    u10.paramsGenerator_ = v10;
                } else {
                    this.updateStateVarsOfChildByElmtId(s10, {});
                }
            }, { name: 'ButtonComponent' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(e10, f10, g10) {
        let h10 = { width: e10.width, height: e10.height };
        let i10 = Number(g10.maxWidth);
        let j10 = Number(g10.maxHeight);
        this.windowSize = { width: i10, height: j10 };
        this.updateFontScale();
        this.updateNeedResponseScale();
        this.updateCustomStyle(Number(g10.maxWidth), Number(g10.maxHeight));
        f10.forEach((l10) => {
            let m10 = l10.measure(g10);
            if (this.updateButtonHeight) {
                this.updateButtonHeight(this.buttonHeight);
            }
            if (this.updateTitleHeight) {
                this.updateTitleHeight(this.titleHeight);
            }
            if (j10 - this.buttonHeight - this.titleHeight < MIN_CONTENT_HEIGHT) {
                this.contentMaxHeight = `${MAX_CONTENT_HEIGHT}vp`;
            } else {
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            }
            m10 = l10.measure(g10);
            h10.height = m10.height;
        });
        h10.width = Number(g10.maxWidth);
        return h10;
    }

    updateCustomStyle(a10, b10) {
        if (this.initCustomStyle) {
            return;
        }
        if (this.targetSdk >= VERSION_TWELVE) {
            return;
        }
        let c10 = getNumberByResource('ohos_id_dialog_margin_start');
        let d10 = getNumberByResource('ohos_id_dialog_margin_end');
        if (Math.abs(a10 - this.screenSize.width) < c10 + d10 ||
            Math.abs(b10 - this.screenSize.height) < 1) {
            this.customStyle = true;
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

    initEnvInfo() {
        try {
            let z9 = display.getDefaultDisplaySync();
            this.windowSize = { width: px2vp(z9.width), height: px2vp(z9.height) };
            this.screenSize = { width: this.windowSize.width, height: this.windowSize.height };
        } catch (w9) {
            let x9 = w9.code;
            let y9 = w9.message;
            hilog.error(0x3900, 'Ace', `Faild to init windowsize,cause, code: ${x9}, message: ${y9}`);
        }
        this.updateFontScale();
        try {
            let v9 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            this.targetSdk = bundleManager.getBundleInfoForSelfSync(v9).targetVersion;
        } catch (s9) {
            let t9 = s9.code;
            let u9 = s9.message;
            hilog.error(0x3900, 'Ace', `Faild to init bundle info,cause, code: ${t9}, message: ${u9}`);
        }
    }

    updateFontScale() {
        try {
            let r9 = this.getUIContext().getHostContext();
            this.fontSizeScale = r9.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (o9) {
            let p9 = o9.code;
            let q9 = o9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${p9}, message: ${q9}`);
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
    constructor(i9, j9, k9, l9 = -1, m9 = undefined, n9) {
        super(i9, k9, l9, n9);
        if (typeof m9 === 'function') {
            this.paramsGenerator_ = m9;
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
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(j9.needResponseScale, this, 'needResponseScale');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(j9.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(j9.windowSize, this, 'windowSize');
        this.__titleHeight = new SynchedPropertyObjectTwoWayPU(j9.titleHeight, this, 'titleHeight');
        this.setInitiallyProvidedValue(j9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(h9) {
        if (h9.primaryTitle !== undefined) {
            this.primaryTitle = h9.primaryTitle;
        }
        if (h9.secondaryTitle !== undefined) {
            this.secondaryTitle = h9.secondaryTitle;
        }
        if (h9.theme !== undefined) {
            this.theme = h9.theme;
        }
        if (h9.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = h9.primaryTitleFontColorWithTheme;
        }
        if (h9.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = h9.secondaryTitleFontColorWithTheme;
        }
        if (h9.titleTextAlign !== undefined) {
            this.titleTextAlign = h9.titleTextAlign;
        }
        if (h9.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = h9.primaryTitleMaxFontSize;
        }
        if (h9.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = h9.primaryTitleMinFontSize;
        }
        if (h9.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = h9.secondaryTitleMaxFontSize;
        }
        if (h9.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = h9.secondaryTitleMinFontSize;
        }
    }

    updateStateVars(g9) {
    }

    purgeVariableDependenciesOnElmtId(f9) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(f9);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(f9);
        this.__titleTextAlign.purgeDependencyOnElmtId(f9);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(f9);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(f9);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(f9);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(f9);
        this.__needResponseScale.purgeDependencyOnElmtId(f9);
        this.__fontSizeScale.purgeDependencyOnElmtId(f9);
        this.__windowSize.purgeDependencyOnElmtId(f9);
        this.__titleHeight.purgeDependencyOnElmtId(f9);
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

    set primaryTitleFontColorWithTheme(e9) {
        this.__primaryTitleFontColorWithTheme.set(e9);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(d9) {
        this.__secondaryTitleFontColorWithTheme.set(d9);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(c9) {
        this.__titleTextAlign.set(c9);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(b9) {
        this.__primaryTitleMaxFontSize.set(b9);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(a9) {
        this.__primaryTitleMinFontSize.set(a9);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(z8) {
        this.__secondaryTitleMaxFontSize.set(z8);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(y8) {
        this.__secondaryTitleMinFontSize.set(y8);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(x8) {
        this.__needResponseScale.set(x8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(w8) {
        this.__fontSizeScale.set(w8);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(v8) {
        this.__windowSize.set(v8);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(u8) {
        this.__titleHeight.set(u8);
    }

    initialRender() {
        this.observeComponentCreation2((s8, t8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((q8, r8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((o8, p8) => {
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
        this.observeComponentCreation2((e8, f8) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m8, n8) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((k8, l8) => {
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
        this.observeComponentCreation2((c8, d8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((a8, b8) => {
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

    onMeasureSize(n7, o7, p7) {
        let q7 = { width: n7.width, height: n7.height };
        this.updateFontSize();
        o7.forEach((s7) => {
            let t7 = s7.measure(p7);
            q7.height = t7.height;
        });
        q7.width = Number(p7.maxWidth);
        this.titleHeight = q7.height;
        return q7;
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
        let m7 = getEnumNumberByResource('alert_title_alignment');
        if (m7 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (m7 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (m7 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (m7 === TextAlign.JUSTIFY) {
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
    constructor(g7, h7, i7, j7 = -1, k7 = undefined, l7) {
        super(g7, i7, j7, l7);
        if (typeof k7 === 'function') {
            this.paramsGenerator_ = k7;
        }
        this.controller = undefined;
        this.buttons = undefined;
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
        this.keyIndex = 0;
        this.__buttonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'buttonFontColorWithTheme');
        this.__errorButtonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'errorButtonFontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.__singleButtonHeight = new ObservedPropertySimplePU(BUTTON_DEFAULT_HEIGHT, this, 'singleButtonHeight');
        this.__isButtonVertical = new ObservedPropertySimplePU(false, this, 'isButtonVertical');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(h7.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(h7.windowSize, this, 'windowSize');
        this.__buttonHeight = new SynchedPropertyObjectTwoWayPU(h7.buttonHeight, this, 'buttonHeight');
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(h7.needResponseScale, this, 'needResponseScale');
        this.setInitiallyProvidedValue(h7);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f7) {
        if (f7.controller !== undefined) {
            this.controller = f7.controller;
        }
        if (f7.buttons !== undefined) {
            this.buttons = f7.buttons;
        }
        if (f7.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = f7.buttonMaxFontSize;
        }
        if (f7.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = f7.buttonMinFontSize;
        }
        if (f7.keyIndex !== undefined) {
            this.keyIndex = f7.keyIndex;
        }
        if (f7.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = f7.buttonFontColorWithTheme;
        }
        if (f7.errorButtonFontColorWithTheme !== undefined) {
            this.errorButtonFontColorWithTheme = f7.errorButtonFontColorWithTheme;
        }
        if (f7.theme !== undefined) {
            this.theme = f7.theme;
        }
        if (f7.singleButtonHeight !== undefined) {
            this.singleButtonHeight = f7.singleButtonHeight;
        }
        if (f7.isButtonVertical !== undefined) {
            this.isButtonVertical = f7.isButtonVertical;
        }
    }

    updateStateVars(e7) {
    }

    purgeVariableDependenciesOnElmtId(d7) {
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(d7);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(d7);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(d7);
        this.__errorButtonFontColorWithTheme.purgeDependencyOnElmtId(d7);
        this.__singleButtonHeight.purgeDependencyOnElmtId(d7);
        this.__isButtonVertical.purgeDependencyOnElmtId(d7);
        this.__fontSizeScale.purgeDependencyOnElmtId(d7);
        this.__windowSize.purgeDependencyOnElmtId(d7);
        this.__buttonHeight.purgeDependencyOnElmtId(d7);
        this.__needResponseScale.purgeDependencyOnElmtId(d7);
    }

    aboutToBeDeleted() {
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        this.__buttonFontColorWithTheme.aboutToBeDeleted();
        this.__errorButtonFontColorWithTheme.aboutToBeDeleted();
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

    set buttonMaxFontSize(c7) {
        this.__buttonMaxFontSize.set(c7);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(b7) {
        this.__buttonMinFontSize.set(b7);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(a7) {
        this.__buttonFontColorWithTheme.set(a7);
    }

    get errorButtonFontColorWithTheme() {
        return this.__errorButtonFontColorWithTheme.get();
    }

    set errorButtonFontColorWithTheme(z6) {
        this.__errorButtonFontColorWithTheme.set(z6);
    }

    get singleButtonHeight() {
        return this.__singleButtonHeight.get();
    }

    set singleButtonHeight(y6) {
        this.__singleButtonHeight.set(y6);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(x6) {
        this.__isButtonVertical.set(x6);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(w6) {
        this.__fontSizeScale.set(w6);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(v6) {
        this.__windowSize.set(v6);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(u6) {
        this.__buttonHeight.set(u6);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(t6) {
        this.__needResponseScale.set(t6);
    }

    initialRender() {
        this.observeComponentCreation2((r6, s6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((i6, j6) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n6, o6) => {
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
        this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
        this.theme.colors.fontEmphasize : '';
        this.errorButtonFontColorWithTheme = this.theme?.colors?.warning ?
        this.theme.colors.warning : '';
        this.updateFontSize();
        this.isButtonVertical =
            this.isVerticalAlignButton(Math.min(this.windowSize.width - BUTTON_HORIZONTAL_MARGIN * 2,
                MAX_DIALOG_WIDTH));
    }

    onMeasureSize(z5, a6, b6) {
        let c6 = { width: z5.width, height: z5.height };
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(Number(b6.maxWidth));
        a6.forEach((e6) => {
            let f6 = e6.measure(b6);
            c6.height = f6.height;
        });
        c6.width = Number(b6.maxWidth);
        this.buttonHeight = Number(c6.height);
        return c6;
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
                    this.observeComponentCreation2((x5, y5) => {
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
                    this.observeComponentCreation2((t5, u5) => {
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
                    this.observeComponentCreation2((p5, q5) => {
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
            } else if (a5.background !== undefined && a5.fontColor === undefined || '') {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((l5, m5) => {
                        Button.createWithLabel(a5.value);
                        __Button__setButtonProperties(a5, this.controller);
                        Button.backgroundColor(a5.background);
                        Button.fontColor(a5.role === ButtonRole.ERROR ?
                        this.errorButtonFontColorWithTheme : this.buttonFontColorWithTheme);
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
                this.ifElseBranchUpdateFunction(4, () => {
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
                        fontSizeScale: this.__fontSizeScale,
                        windowSize: this.__windowSize
                    }, undefined, g1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1523, col: 7 });
                    ViewPU.create(i1);
                    let j1 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            theme: this.theme,
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