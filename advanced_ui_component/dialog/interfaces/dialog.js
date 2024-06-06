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
    constructor(i25) {
        this.colors = i25;
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
    constructor(a25, b25, c25, d25 = -1, e25 = undefined, f25) {
        super(a25, c25, d25, f25);
        if (typeof e25 === 'function') {
            this.paramsGenerator_ = e25;
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
        this.updateButtonHeight = (h25) => {
            this.buttonHeight = h25;
        };
        this.setInitiallyProvidedValue(b25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z24) {
        if (z24.controller !== undefined) {
            this.controller = z24.controller;
        }
        if (z24.imageRes !== undefined) {
            this.imageRes = z24.imageRes;
        }
        if (z24.imageSize !== undefined) {
            this.imageSize = z24.imageSize;
        }
        if (z24.title !== undefined) {
            this.title = z24.title;
        }
        if (z24.content !== undefined) {
            this.content = z24.content;
        }
        if (z24.checkAction !== undefined) {
            this.checkAction = z24.checkAction;
        }
        if (z24.onCheckedChange !== undefined) {
            this.onCheckedChange = z24.onCheckedChange;
        }
        if (z24.checkTips !== undefined) {
            this.checkTips = z24.checkTips;
        }
        if (z24.isChecked !== undefined) {
            this.isChecked = z24.isChecked;
        }
        if (z24.primaryButton !== undefined) {
            this.primaryButton = z24.primaryButton;
        }
        if (z24.secondaryButton !== undefined) {
            this.secondaryButton = z24.secondaryButton;
        }
        if (z24.buttons !== undefined) {
            this.buttons = z24.buttons;
        }
        if (z24.imageSizeHeight !== undefined) {
            this.imageSizeHeight = z24.imageSizeHeight;
        }
        if (z24.textAlignment !== undefined) {
            this.textAlignment = z24.textAlignment;
        }
        if (z24.marginOffset !== undefined) {
            this.marginOffset = z24.marginOffset;
        }
        if (z24.checkBoxHeight !== undefined) {
            this.checkBoxHeight = z24.checkBoxHeight;
        }
        if (z24.buttonHeight !== undefined) {
            this.buttonHeight = z24.buttonHeight;
        }
        if (z24.contentScroller !== undefined) {
            this.contentScroller = z24.contentScroller;
        }
        if (z24.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = z24.fontColorWithTheme;
        }
        if (z24.theme !== undefined) {
            this.theme = z24.theme;
        }
        if (z24.themeColorMode !== undefined) {
            this.themeColorMode = z24.themeColorMode;
        }
        if (z24.fontSizeScale !== undefined) {
            this.fontSizeScale = z24.fontSizeScale;
        }
        if (z24.windowSize !== undefined) {
            this.windowSize = z24.windowSize;
        }
        if (z24.updateButtonHeight !== undefined) {
            this.updateButtonHeight = z24.updateButtonHeight;
        }
    }

    updateStateVars(y24) {
    }

    purgeVariableDependenciesOnElmtId(x24) {
        this.__imageSize.purgeDependencyOnElmtId(x24);
        this.__isChecked.purgeDependencyOnElmtId(x24);
        this.__imageSizeHeight.purgeDependencyOnElmtId(x24);
        this.__textAlignment.purgeDependencyOnElmtId(x24);
        this.__checkBoxHeight.purgeDependencyOnElmtId(x24);
        this.__buttonHeight.purgeDependencyOnElmtId(x24);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(x24);
        this.__fontSizeScale.purgeDependencyOnElmtId(x24);
        this.__windowSize.purgeDependencyOnElmtId(x24);
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

    setController(w24) {
        this.controller = w24;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(v24) {
        this.__imageSize.set(v24);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(u24) {
        this.__isChecked.set(u24);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(t24) {
        this.__imageSizeHeight.set(t24);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(s24) {
        this.__textAlignment.set(s24);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(r24) {
        this.__checkBoxHeight.set(r24);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(q24) {
        this.__buttonHeight.set(q24);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(p24) {
        this.__fontColorWithTheme.set(p24);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(o24) {
        this.__fontSizeScale.set(o24);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(n24) {
        this.__windowSize.set(n24);
    }

    initialRender() {
        this.observeComponentCreation2((l24, m24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((f24, g24) => {
                if (g24) {
                    let h24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, f24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 113, col: 5 });
                    ViewPU.create(h24);
                    let i24 = () => {
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
                    h24.paramsGenerator_ = i24;
                } else {
                    this.updateStateVarsOfChildByElmtId(f24, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(m23 = null) {
        this.observeComponentCreation2((b24, c24) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(m23 ? m23 : this);
        this.observeComponentCreation2((u23, v23) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z23, a24) => {
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
                    this.textPart.bind(this)(m23 ? m23 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((q23, r23) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, m23 ? m23 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(v22, w22 = null) {
        this.observeComponentCreation2((h23, i23) => {
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
            Row.onAreaChange((k23, l23) => {
                this.checkBoxHeight = Number(l23.height);
            });
        }, Row);
        this.observeComponentCreation2((d23, e23) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((g23) => {
                this.isChecked = g23;
                if (this.checkAction) {
                    this.checkAction(g23);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(g23);
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
        this.observeComponentCreation2((a23, b23) => {
            Text.create(v22);
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

    imagePart(l22 = null) {
        this.observeComponentCreation2((q22, r22) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((t22, u22) => {
                this.imageSizeHeight = Number(u22.height);
            });
        }, Column);
        this.observeComponentCreation2((o22, p22) => {
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

    textPart(d21 = null) {
        this.observeComponentCreation2((j22, k22) => {
            Scroll.create(this.contentScroller);
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((h22, i22) => {
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
        this.observeComponentCreation2((x21, y21) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f22, g22) => {
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
                    this.observeComponentCreation2((d22, e22) => {
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
        this.observeComponentCreation2((i21, j21) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v21, w21) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((o21, p21) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((u21) => {
                            if (u21) {
                                resolveKeyEvent(u21, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((s21, t21) => {
                            this.getTextAlign(Number(t21.width));
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

    getTextAlign(z20) {
        let a21 = this.getContentFontSize();
        let b21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: a21,
            constraintWidth: z20,
        });
        let c21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: a21,
        });
        if (this.getTextHeight(b21) <= this.getTextHeight(c21)) {
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

    getTextHeight(y20) {
        if (y20 && y20.height !== null && y20.height !== undefined) {
            return Number(y20.height);
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
    constructor(s20, t20, u20, v20 = -1, w20 = undefined, x20) {
        super(s20, u20, v20, x20);
        if (typeof w20 === 'function') {
            this.paramsGenerator_ = w20;
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
        this.setInitiallyProvidedValue(t20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r20) {
        if (r20.controller !== undefined) {
            this.controller = r20.controller;
        }
        if (r20.title !== undefined) {
            this.title = r20.title;
        }
        if (r20.content !== undefined) {
            this.content = r20.content;
        }
        if (r20.selectedIndex !== undefined) {
            this.selectedIndex = r20.selectedIndex;
        }
        if (r20.confirm !== undefined) {
            this.confirm = r20.confirm;
        }
        if (r20.radioContent !== undefined) {
            this.radioContent = r20.radioContent;
        }
        if (r20.buttons !== undefined) {
            this.buttons = r20.buttons;
        }
        if (r20.contentPadding !== undefined) {
            this.contentPadding = r20.contentPadding;
        }
        if (r20.isFocus !== undefined) {
            this.isFocus = r20.isFocus;
        }
        if (r20.currentFocusIndex !== undefined) {
            this.currentFocusIndex = r20.currentFocusIndex;
        }
        if (r20.radioHeight !== undefined) {
            this.radioHeight = r20.radioHeight;
        }
        if (r20.itemHeight !== undefined) {
            this.itemHeight = r20.itemHeight;
        }
        if (r20.contentBuilder !== undefined) {
            this.contentBuilder = r20.contentBuilder;
        }
        if (r20.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = r20.fontColorWithTheme;
        }
        if (r20.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = r20.dividerColorWithTheme;
        }
        if (r20.theme !== undefined) {
            this.theme = r20.theme;
        }
        if (r20.themeColorMode !== undefined) {
            this.themeColorMode = r20.themeColorMode;
        }
        if (r20.contentScroller !== undefined) {
            this.contentScroller = r20.contentScroller;
        }
        if (r20.fontSizeScale !== undefined) {
            this.fontSizeScale = r20.fontSizeScale;
        }
        if (r20.windowSize !== undefined) {
            this.windowSize = r20.windowSize;
        }
    }

    updateStateVars(q20) {
    }

    purgeVariableDependenciesOnElmtId(p20) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(p20);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(p20);
        this.__fontSizeScale.purgeDependencyOnElmtId(p20);
        this.__windowSize.purgeDependencyOnElmtId(p20);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(o20) {
        this.controller = o20;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(n20) {
        this.__fontColorWithTheme.set(n20);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(m20) {
        this.__dividerColorWithTheme.set(m20);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(l20) {
        this.__fontSizeScale.set(l20);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(k20) {
        this.__windowSize.set(k20);
    }

    buildContent(l17 = null) {
        this.observeComponentCreation2((e20, f20) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.onDidScroll((h20, i20) => {
                let j20 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (i20 > 0) {
                            this.contentScroller.scrollBy(0, j20);
                        } else if (i20 < 0) {
                            this.contentScroller.scrollBy(0, 0 - j20);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((c20, d20) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((s19, t19) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a20, b20) => {
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
                    this.observeComponentCreation2((y19, z19) => {
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
        this.observeComponentCreation2((p19, q19) => {
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
        this.observeComponentCreation2((r17, s17) => {
            ForEach.create();
            const t17 = (v17, w17) => {
                const x17 = v17;
                {
                    const y17 = (n19, o19) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n19);
                        z17(n19, o19);
                        if (!o19) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const z17 = (i19, j19) => {
                        ListItem.create(a18, true);
                        ListItem.onSizeChange((l19, m19) => {
                            this.itemHeight = Number(m19.height);
                        });
                    };
                    const a18 = (e18, f18) => {
                        y17(e18, f18);
                        this.observeComponentCreation2((g19, h19) => {
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
                        this.observeComponentCreation2((d19, e19) => {
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
                                x17.action && x17.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((b19, c19) => {
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
                        this.observeComponentCreation2((z18, a19) => {
                            Text.create(x17.title);
                            Text.fontSize(this.getListFontSize());
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((t18, u18) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === w17);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(w17));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = w17;
                                if (w17 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (w17 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((x18, y18) => {
                                this.radioHeight = Number(y18.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((m18, n18) => {
                            If.create();
                            if (w17 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((r18, s18) => {
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
                    this.observeComponentCreation2(z17, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(r17, this.radioContent, t17, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((j17, k17) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((d17, e17) => {
                if (e17) {
                    let f17 = new CustomDialogContentComponent(this, {
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
                    }, undefined, d17, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 455, col: 5 });
                    ViewPU.create(f17);
                    let g17 = () => {
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
                    f17.paramsGenerator_ = g17;
                } else {
                    this.updateStateVarsOfChildByElmtId(d17, {});
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
    constructor(r16, s16, t16, u16 = -1, v16 = undefined, w16) {
        super(r16, t16, u16, w16);
        if (typeof v16 === 'function') {
            this.paramsGenerator_ = v16;
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
        this.updateTitleHeight = (a17) => {
            this.titleHeight = a17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (z16) => {
            this.buttonHeight = z16;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(s16);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q16) {
        if (q16.controller !== undefined) {
            this.controller = q16.controller;
        }
        if (q16.title !== undefined) {
            this.title = q16.title;
        }
        if (q16.content !== undefined) {
            this.content = q16.content;
        }
        if (q16.checkTips !== undefined) {
            this.checkTips = q16.checkTips;
        }
        if (q16.isChecked !== undefined) {
            this.isChecked = q16.isChecked;
        }
        if (q16.primaryButton !== undefined) {
            this.primaryButton = q16.primaryButton;
        }
        if (q16.secondaryButton !== undefined) {
            this.secondaryButton = q16.secondaryButton;
        }
        if (q16.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q16.fontColorWithTheme;
        }
        if (q16.theme !== undefined) {
            this.theme = q16.theme;
        }
        if (q16.themeColorMode !== undefined) {
            this.themeColorMode = q16.themeColorMode;
        }
        if (q16.onCheckedChange !== undefined) {
            this.onCheckedChange = q16.onCheckedChange;
        }
        if (q16.contentScroller !== undefined) {
            this.contentScroller = q16.contentScroller;
        }
        if (q16.buttons !== undefined) {
            this.buttons = q16.buttons;
        }
        if (q16.marginOffset !== undefined) {
            this.marginOffset = q16.marginOffset;
        }
        if (q16.titleHeight !== undefined) {
            this.titleHeight = q16.titleHeight;
        }
        if (q16.buttonHeight !== undefined) {
            this.buttonHeight = q16.buttonHeight;
        }
        if (q16.checkBoxHeight !== undefined) {
            this.checkBoxHeight = q16.checkBoxHeight;
        }
        if (q16.fontSizeScale !== undefined) {
            this.fontSizeScale = q16.fontSizeScale;
        }
        if (q16.windowSize !== undefined) {
            this.windowSize = q16.windowSize;
        }
        if (q16.maxContentHeight !== undefined) {
            this.maxContentHeight = q16.maxContentHeight;
        }
        if (q16.updateTitleHeight !== undefined) {
            this.updateTitleHeight = q16.updateTitleHeight;
        }
        if (q16.updateButtonHeight !== undefined) {
            this.updateButtonHeight = q16.updateButtonHeight;
        }
    }

    updateStateVars(p16) {
    }

    purgeVariableDependenciesOnElmtId(o16) {
        this.__isChecked.purgeDependencyOnElmtId(o16);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o16);
        this.__titleHeight.purgeDependencyOnElmtId(o16);
        this.__buttonHeight.purgeDependencyOnElmtId(o16);
        this.__checkBoxHeight.purgeDependencyOnElmtId(o16);
        this.__fontSizeScale.purgeDependencyOnElmtId(o16);
        this.__windowSize.purgeDependencyOnElmtId(o16);
        this.__maxContentHeight.purgeDependencyOnElmtId(o16);
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

    setController(n16) {
        this.controller = n16;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(m16) {
        this.__isChecked.set(m16);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(l16) {
        this.__fontColorWithTheme.set(l16);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(k16) {
        this.__titleHeight.set(k16);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(j16) {
        this.__buttonHeight.set(j16);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(i16) {
        this.__checkBoxHeight.set(i16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(h16) {
        this.__fontSizeScale.set(h16);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(g16) {
        this.__windowSize.set(g16);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(f16) {
        this.__maxContentHeight.set(f16);
    }

    buildContent(w14 = null) {
        this.observeComponentCreation2((d16, e16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((o15, p15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b16, c16) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((z15, a16) => {
                        Scroll.create(this.contentScroller);
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((v15, w15) => {
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
                        Text.onKeyEvent((y15) => {
                            if (y15) {
                                resolveKeyEvent(y15, this.contentScroller);
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
        this.observeComponentCreation2((j15, k15) => {
            Row.create();
            Row.onSizeChange((m15, n15) => {
                this.checkBoxHeight = Number(n15.height);
                this.maxContentHeight =
                    `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((f15, g15) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((i15) => {
                this.isChecked = i15;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((c15, d15) => {
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
        this.observeComponentCreation2((u14, v14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((o14, p14) => {
                if (p14) {
                    let q14 = new CustomDialogContentComponent(this, {
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
                    }, undefined, o14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 638, col: 5 });
                    ViewPU.create(q14);
                    let r14 = () => {
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
                    q14.paramsGenerator_ = r14;
                } else {
                    this.updateStateVarsOfChildByElmtId(o14, {});
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
    constructor(g14, h14, i14, j14 = -1, k14 = undefined, l14) {
        super(g14, i14, j14, l14);
        if (typeof k14 === 'function') {
            this.paramsGenerator_ = k14;
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
        this.setInitiallyProvidedValue(h14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(f14) {
        if (f14.controller !== undefined) {
            this.controller = f14.controller;
        }
        if (f14.primaryTitle !== undefined) {
            this.primaryTitle = f14.primaryTitle;
        }
        if (f14.secondaryTitle !== undefined) {
            this.secondaryTitle = f14.secondaryTitle;
        }
        if (f14.content !== undefined) {
            this.content = f14.content;
        }
        if (f14.primaryButton !== undefined) {
            this.primaryButton = f14.primaryButton;
        }
        if (f14.secondaryButton !== undefined) {
            this.secondaryButton = f14.secondaryButton;
        }
        if (f14.buttons !== undefined) {
            this.buttons = f14.buttons;
        }
        if (f14.textAlign !== undefined) {
            this.textAlign = f14.textAlign;
        }
        if (f14.contentScroller !== undefined) {
            this.contentScroller = f14.contentScroller;
        }
        if (f14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = f14.fontColorWithTheme;
        }
        if (f14.theme !== undefined) {
            this.theme = f14.theme;
        }
        if (f14.themeColorMode !== undefined) {
            this.themeColorMode = f14.themeColorMode;
        }
        if (f14.windowSize !== undefined) {
            this.windowSize = f14.windowSize;
        }
        if (f14.fontSizeScale !== undefined) {
            this.fontSizeScale = f14.fontSizeScale;
        }
    }

    updateStateVars(e14) {
    }

    purgeVariableDependenciesOnElmtId(d14) {
        this.__textAlign.purgeDependencyOnElmtId(d14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(d14);
        this.__windowSize.purgeDependencyOnElmtId(d14);
        this.__fontSizeScale.purgeDependencyOnElmtId(d14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(c14) {
        this.controller = c14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(b14) {
        this.__textAlign.set(b14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(a14) {
        this.__fontColorWithTheme.set(a14);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(z13) {
        this.__windowSize.set(z13);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(y13) {
        this.__fontSizeScale.set(y13);
    }

    initialRender() {
        this.observeComponentCreation2((w13, x13) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((q13, r13) => {
                if (r13) {
                    let s13 = new CustomDialogContentComponent(this, {
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
                    }, undefined, q13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 698, col: 5 });
                    ViewPU.create(s13);
                    let t13 = () => {
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
                    s13.paramsGenerator_ = t13;
                } else {
                    this.updateStateVarsOfChildByElmtId(q13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(z12 = null) {
        this.observeComponentCreation2((m13, n13) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((k13, l13) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((d13, e13) => {
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
            Text.onAreaChange((i13, j13) => {
                this.getTextAlign(Number(j13.width));
            });
            Text.onKeyEvent((h13) => {
                if (h13) {
                    resolveKeyEvent(h13, this.contentScroller);
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

    getTextAlign(v12) {
        let w12 = this.getContentFontSize();
        let x12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: w12,
            constraintWidth: v12,
        });
        let y12 = measure.measureTextSize({
            textContent: this.content,
            fontSize: w12,
        });
        if (this.getTextHeight(x12) <= this.getTextHeight(y12)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(u12) {
        if (u12 && u12.height !== null && u12.height !== undefined) {
            return Number(u12.height);
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
    constructor(o12, p12, q12, r12 = -1, s12 = undefined, t12) {
        super(o12, q12, r12, t12);
        if (typeof s12 === 'function') {
            this.paramsGenerator_ = s12;
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
        this.setInitiallyProvidedValue(p12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(n12) {
        if (n12.controller !== undefined) {
            this.controller = n12.controller;
        }
        if (n12.primaryTitle !== undefined) {
            this.primaryTitle = n12.primaryTitle;
        }
        if (n12.secondaryTitle !== undefined) {
            this.secondaryTitle = n12.secondaryTitle;
        }
        if (n12.contentBuilder !== undefined) {
            this.contentBuilder = n12.contentBuilder;
        }
        if (n12.contentAreaPadding !== undefined) {
            this.contentAreaPadding = n12.contentAreaPadding;
        }
        if (n12.buttons !== undefined) {
            this.buttons = n12.buttons;
        }
        if (n12.theme !== undefined) {
            this.theme = n12.theme;
        }
        if (n12.themeColorMode !== undefined) {
            this.themeColorMode = n12.themeColorMode;
        }
        if (n12.fontSizeScale !== undefined) {
            this.fontSizeScale = n12.fontSizeScale;
        }
        if (n12.windowSize !== undefined) {
            this.windowSize = n12.windowSize;
        }
    }

    updateStateVars(m12) {
    }

    purgeVariableDependenciesOnElmtId(l12) {
        this.__fontSizeScale.purgeDependencyOnElmtId(l12);
        this.__windowSize.purgeDependencyOnElmtId(l12);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(k12) {
        this.controller = k12;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(j12) {
        this.__fontSizeScale.set(j12);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(i12) {
        this.__windowSize.set(i12);
    }

    initialRender() {
        this.observeComponentCreation2((g12, h12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((a12, b12) => {
                if (b12) {
                    let c12 = new CustomDialogContentComponent(this, {
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
                    }, undefined, a12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 816, col: 5 });
                    ViewPU.create(c12);
                    let d12 = () => {
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
                    c12.paramsGenerator_ = d12;
                } else {
                    this.updateStateVarsOfChildByElmtId(a12, {});
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
    constructor(s11, t11, u11, v11 = -1, w11 = undefined, x11) {
        super(s11, u11, v11, x11);
        if (typeof w11 === 'function') {
            this.paramsGenerator_ = w11;
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
        this.__contentMaxHeight = new ObservedPropertySimplePU(`calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`, this, 'contentMaxHeight');
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
        this.targetSdk = VERSION_TWELVE;
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(t11.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(t11.windowSize, this, 'windowSize');
        this.__customStyle = new ObservedPropertySimplePU(false, this, 'customStyle');
        this.__needResponseScale = new ObservedPropertySimplePU(true, this, 'needResponseScale');
        this.screenSize = { width: 0, height: 0 };
        this.initCustomStyle = false;
        this.setInitiallyProvidedValue(t11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r11) {
        if (r11.controller !== undefined) {
            this.controller = r11.controller;
        }
        if (r11.primaryTitle !== undefined) {
            this.primaryTitle = r11.primaryTitle;
        }
        if (r11.secondaryTitle !== undefined) {
            this.secondaryTitle = r11.secondaryTitle;
        }
        if (r11.contentBuilder !== undefined) {
            this.contentBuilder = r11.contentBuilder;
        }
        if (r11.buttons !== undefined) {
            this.buttons = r11.buttons;
        }
        if (r11.contentAreaPadding !== undefined) {
            this.contentAreaPadding = r11.contentAreaPadding;
        }
        if (r11.keyIndex !== undefined) {
            this.keyIndex = r11.keyIndex;
        }
        if (r11.theme !== undefined) {
            this.theme = r11.theme;
        }
        if (r11.themeColorMode !== undefined) {
            this.themeColorMode = r11.themeColorMode;
        }
        if (r11.titleHeight !== undefined) {
            this.titleHeight = r11.titleHeight;
        }
        if (r11.buttonHeight !== undefined) {
            this.buttonHeight = r11.buttonHeight;
        }
        if (r11.contentMaxHeight !== undefined) {
            this.contentMaxHeight = r11.contentMaxHeight;
        }
        if (r11.updateTitleHeight !== undefined) {
            this.updateTitleHeight = r11.updateTitleHeight;
        }
        if (r11.updateButtonHeight !== undefined) {
            this.updateButtonHeight = r11.updateButtonHeight;
        }
        if (r11.targetSdk !== undefined) {
            this.targetSdk = r11.targetSdk;
        }
        if (r11.customStyle !== undefined) {
            this.customStyle = r11.customStyle;
        }
        if (r11.needResponseScale !== undefined) {
            this.needResponseScale = r11.needResponseScale;
        }
        if (r11.screenSize !== undefined) {
            this.screenSize = r11.screenSize;
        }
        if (r11.initCustomStyle !== undefined) {
            this.initCustomStyle = r11.initCustomStyle;
        }
    }

    updateStateVars(q11) {
    }

    purgeVariableDependenciesOnElmtId(p11) {
        this.__titleHeight.purgeDependencyOnElmtId(p11);
        this.__buttonHeight.purgeDependencyOnElmtId(p11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(p11);
        this.__fontSizeScale.purgeDependencyOnElmtId(p11);
        this.__windowSize.purgeDependencyOnElmtId(p11);
        this.__customStyle.purgeDependencyOnElmtId(p11);
        this.__needResponseScale.purgeDependencyOnElmtId(p11);
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

    defaultContentBuilder(o11 = null) {
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(n11) {
        this.__titleHeight.set(n11);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(m11) {
        this.__buttonHeight.set(m11);
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(l11) {
        this.__contentMaxHeight.set(l11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(k11) {
        this.__fontSizeScale.set(k11);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(j11) {
        this.__windowSize.set(j11);
    }

    get customStyle() {
        return this.__customStyle.get();
    }

    set customStyle(i11) {
        this.__customStyle.set(i11);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(h11) {
        this.__needResponseScale.set(h11);
    }

    initialRender() {
        this.observeComponentCreation2((f11, g11) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((d11, e11) => {
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
        this.observeComponentCreation2((b11, c11) => {
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
            this.observeComponentCreation2((v10, w10) => {
                if (w10) {
                    let x10 = new TitleComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        titleHeight: this.__titleHeight,
                        needResponseScale: this.__needResponseScale,
                        theme: this.theme
                    }, undefined, v10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 867, col: 11 });
                    ViewPU.create(x10);
                    let y10 = () => {
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
                    x10.paramsGenerator_ = y10;
                } else {
                    this.updateStateVarsOfChildByElmtId(v10, {});
                }
            }, { name: 'TitleComponent' });
        }
        this.observeComponentCreation2((s10, t10) => {
            Column.create();
            Column.padding(this.getContentPadding());
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
        }, Column);
        this.contentBuilder.bind(this)(this);
        Column.pop();
        {
            this.observeComponentCreation2((m10, n10) => {
                if (n10) {
                    let o10 = new ButtonComponent(this, {
                        buttons: this.buttons,
                        windowSize: this.__windowSize,
                        fontSizeScale: this.__fontSizeScale,
                        needResponseScale: this.__needResponseScale,
                        buttonHeight: this.__buttonHeight,
                        controller: this.controller,
                        theme: this.theme
                    }, undefined, m10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 883, col: 11 });
                    ViewPU.create(o10);
                    let p10 = () => {
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
                    o10.paramsGenerator_ = p10;
                } else {
                    this.updateStateVarsOfChildByElmtId(m10, {});
                }
            }, { name: 'ButtonComponent' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }

    onMeasureSize(y9, z9, a10) {
        let b10 = { width: y9.width, height: y9.height };
        let c10 = Number(a10.maxWidth);
        let d10 = Number(a10.maxHeight);
        this.windowSize = { width: c10, height: d10 };
        this.updateFontScale();
        this.updateNeedResponseScale();
        this.updateCustomStyle(Number(a10.maxWidth), Number(a10.maxHeight));
        z9.forEach((f10) => {
            let g10 = f10.measure(a10);
            if (this.updateButtonHeight) {
                this.updateButtonHeight(this.buttonHeight);
            }
            if (this.updateTitleHeight) {
                this.updateTitleHeight(this.titleHeight);
            }
            if (d10 - this.buttonHeight - this.titleHeight < MIN_CONTENT_HEIGHT) {
                this.contentMaxHeight = `${MAX_CONTENT_HEIGHT}vp`;
            } else {
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
            }
            g10 = f10.measure(a10);
            b10.height = g10.height;
        });
        b10.width = Number(a10.maxWidth);
        return b10;
    }

    updateCustomStyle(u9, v9) {
        if (this.initCustomStyle) {
            return;
        }
        if (this.targetSdk >= VERSION_TWELVE) {
            return;
        }
        let w9 = getNumberByResource('ohos_id_dialog_margin_start');
        let x9 = getNumberByResource('ohos_id_dialog_margin_end');
        if (Math.abs(u9 - this.screenSize.width) < w9 + x9 ||
            Math.abs(v9 - this.screenSize.height) < 1) {
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
            let t9 = display.getDefaultDisplaySync();
            this.windowSize = { width: px2vp(t9.width), height: px2vp(t9.height) };
            this.screenSize = { width: this.windowSize.width, height: this.windowSize.height };
        } catch (q9) {
            let r9 = q9.code;
            let s9 = q9.message;
            hilog.error(0x3900, 'Ace', `Faild to init windowsize,cause, code: ${r9}, message: ${s9}`);
        }
        this.updateFontScale();
        try {
            let p9 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            this.targetSdk = bundleManager.getBundleInfoForSelfSync(p9).targetVersion;
        } catch (m9) {
            let n9 = m9.code;
            let o9 = m9.message;
            hilog.error(0x3900, 'Ace', `Faild to init bundle info,cause, code: ${n9}, message: ${o9}`);
        }
    }

    updateFontScale() {
        try {
            let l9 = this.getUIContext().getHostContext();
            this.fontSizeScale = l9.config?.fontSizeScale ?? this.fontSizeScale;
        } catch (i9) {
            let j9 = i9.code;
            let k9 = i9.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${j9}, message: ${k9}`);
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
    constructor(c9, d9, e9, f9 = -1, g9 = undefined, h9) {
        super(c9, e9, f9, h9);
        if (typeof g9 === 'function') {
            this.paramsGenerator_ = g9;
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
        this.__needResponseScale = new SynchedPropertySimpleTwoWayPU(d9.needResponseScale, this, 'needResponseScale');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(d9.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(d9.windowSize, this, 'windowSize');
        this.__titleHeight = new SynchedPropertyObjectTwoWayPU(d9.titleHeight, this, 'titleHeight');
        this.setInitiallyProvidedValue(d9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(b9) {
        if (b9.primaryTitle !== undefined) {
            this.primaryTitle = b9.primaryTitle;
        }
        if (b9.secondaryTitle !== undefined) {
            this.secondaryTitle = b9.secondaryTitle;
        }
        if (b9.theme !== undefined) {
            this.theme = b9.theme;
        }
        if (b9.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = b9.primaryTitleFontColorWithTheme;
        }
        if (b9.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = b9.secondaryTitleFontColorWithTheme;
        }
        if (b9.titleTextAlign !== undefined) {
            this.titleTextAlign = b9.titleTextAlign;
        }
        if (b9.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = b9.primaryTitleMaxFontSize;
        }
        if (b9.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = b9.primaryTitleMinFontSize;
        }
        if (b9.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = b9.secondaryTitleMaxFontSize;
        }
        if (b9.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = b9.secondaryTitleMinFontSize;
        }
    }

    updateStateVars(a9) {
    }

    purgeVariableDependenciesOnElmtId(z8) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(z8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(z8);
        this.__titleTextAlign.purgeDependencyOnElmtId(z8);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(z8);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(z8);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(z8);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(z8);
        this.__needResponseScale.purgeDependencyOnElmtId(z8);
        this.__fontSizeScale.purgeDependencyOnElmtId(z8);
        this.__windowSize.purgeDependencyOnElmtId(z8);
        this.__titleHeight.purgeDependencyOnElmtId(z8);
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

    set primaryTitleFontColorWithTheme(y8) {
        this.__primaryTitleFontColorWithTheme.set(y8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(x8) {
        this.__secondaryTitleFontColorWithTheme.set(x8);
    }

    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }

    set titleTextAlign(w8) {
        this.__titleTextAlign.set(w8);
    }

    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }

    set primaryTitleMaxFontSize(v8) {
        this.__primaryTitleMaxFontSize.set(v8);
    }

    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }

    set primaryTitleMinFontSize(u8) {
        this.__primaryTitleMinFontSize.set(u8);
    }

    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }

    set secondaryTitleMaxFontSize(t8) {
        this.__secondaryTitleMaxFontSize.set(t8);
    }

    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }

    set secondaryTitleMinFontSize(s8) {
        this.__secondaryTitleMinFontSize.set(s8);
    }

    get needResponseScale() {
        return this.__needResponseScale.get();
    }

    set needResponseScale(r8) {
        this.__needResponseScale.set(r8);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(q8) {
        this.__fontSizeScale.set(q8);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(p8) {
        this.__windowSize.set(p8);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(o8) {
        this.__titleHeight.set(o8);
    }

    initialRender() {
        this.observeComponentCreation2((m8, n8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((k8, l8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((i8, j8) => {
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
        this.observeComponentCreation2((y7, z7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g8, h8) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((e8, f8) => {
                        Divider.create();
                        Divider.margin({
                            "id": -1,
                            "type": 10002,
                            params: ['sys.float.padding_level1'],
                            "bundleName": "__harDefaultBundleName__",
                            "moduleName": "__harDefaultModuleName__"
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
        this.observeComponentCreation2((w7, x7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((u7, v7) => {
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
        i7.forEach((m7) => {
            let n7 = m7.measure(j7);
            k7.height = n7.height;
        });
        k7.width = Number(j7.maxWidth);
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
        this.__buttonMaxFontSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.Body_L'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new ObservedPropertyObjectPU(9, this, 'buttonMinFontSize');
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
        if (z6.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = z6.buttonMaxFontSize;
        }
        if (z6.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = z6.buttonMinFontSize;
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
        this.isButtonVertical = this.isVerticalAlignButton(Math.min(this.windowSize.width - BUTTON_HORIZONTAL_MARGIN * 2, MAX_DIALOG_WIDTH));
    }

    onMeasureSize(v5, w5, x5) {
        let y5 = { width: v5.width, height: v5.height };
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(Number(x5.maxWidth));
        w5.forEach((a6) => {
            let b6 = a6.measure(x5);
            y5.height = b6.height;
        });
        y5.width = Number(x5.maxWidth);
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
                                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1], j4 ? j4 : this);
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
                        this.forEachUpdateFunction(y3, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), a4, (d4) => d4.value.toString(), true, false);
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
                    }, { page: 'library/src/main/ets/components/mainpage/dialog.ets', line: 1517, col: 7 });
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