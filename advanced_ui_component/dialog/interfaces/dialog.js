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
const bundleManager = requireNapi('bundleManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

class CustomThemeImpl {
    constructor(v25) {
        this.colors = v25;
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
const MAX_FONT_SCALE = 2;
const BODY_L = getNumberByResource('Body_L') ?? 16;
const BODY_M = getNumberByResource('Body_M') ?? 14;
const BODY_S = getNumberByResource('Body_S') ?? 12;
const TITLE_S = getNumberByResource('Title_S') ?? 20;
const SUBTITLE_S = getNumberByResource('Subtitle_S') ?? 14;
const BUTTON_MIN_FONT_SIZE = 9;

export class TipsDialog extends ViewPU {
    constructor(n25, o25, p25, q25 = -1, r25 = undefined, s25) {
        super(n25, p25, q25, s25);
        if (typeof r25 === 'function') {
            this.paramsGenerator_ = r25;
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
        this.updateButtonHeight = (u25) => {
            this.buttonHeight = u25;
        };
        this.setInitiallyProvidedValue(o25);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m25) {
        if (m25.controller !== undefined) {
            this.controller = m25.controller;
        }
        if (m25.imageRes !== undefined) {
            this.imageRes = m25.imageRes;
        }
        if (m25.imageSize !== undefined) {
            this.imageSize = m25.imageSize;
        }
        if (m25.title !== undefined) {
            this.title = m25.title;
        }
        if (m25.content !== undefined) {
            this.content = m25.content;
        }
        if (m25.checkAction !== undefined) {
            this.checkAction = m25.checkAction;
        }
        if (m25.onCheckedChange !== undefined) {
            this.onCheckedChange = m25.onCheckedChange;
        }
        if (m25.checkTips !== undefined) {
            this.checkTips = m25.checkTips;
        }
        if (m25.isChecked !== undefined) {
            this.isChecked = m25.isChecked;
        }
        if (m25.primaryButton !== undefined) {
            this.primaryButton = m25.primaryButton;
        }
        if (m25.secondaryButton !== undefined) {
            this.secondaryButton = m25.secondaryButton;
        }
        if (m25.buttons !== undefined) {
            this.buttons = m25.buttons;
        }
        if (m25.imageSizeHeight !== undefined) {
            this.imageSizeHeight = m25.imageSizeHeight;
        }
        if (m25.textAlignment !== undefined) {
            this.textAlignment = m25.textAlignment;
        }
        if (m25.marginOffset !== undefined) {
            this.marginOffset = m25.marginOffset;
        }
        if (m25.checkBoxHeight !== undefined) {
            this.checkBoxHeight = m25.checkBoxHeight;
        }
        if (m25.buttonHeight !== undefined) {
            this.buttonHeight = m25.buttonHeight;
        }
        if (m25.contentScroller !== undefined) {
            this.contentScroller = m25.contentScroller;
        }
        if (m25.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = m25.fontColorWithTheme;
        }
        if (m25.theme !== undefined) {
            this.theme = m25.theme;
        }
        if (m25.themeColorMode !== undefined) {
            this.themeColorMode = m25.themeColorMode;
        }
        if (m25.fontSizeScale !== undefined) {
            this.fontSizeScale = m25.fontSizeScale;
        }
        if (m25.windowSize !== undefined) {
            this.windowSize = m25.windowSize;
        }
        if (m25.updateButtonHeight !== undefined) {
            this.updateButtonHeight = m25.updateButtonHeight;
        }
    }

    updateStateVars(l25) {
    }

    purgeVariableDependenciesOnElmtId(k25) {
        this.__imageSize.purgeDependencyOnElmtId(k25);
        this.__isChecked.purgeDependencyOnElmtId(k25);
        this.__imageSizeHeight.purgeDependencyOnElmtId(k25);
        this.__textAlignment.purgeDependencyOnElmtId(k25);
        this.__checkBoxHeight.purgeDependencyOnElmtId(k25);
        this.__buttonHeight.purgeDependencyOnElmtId(k25);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(k25);
        this.__fontSizeScale.purgeDependencyOnElmtId(k25);
        this.__windowSize.purgeDependencyOnElmtId(k25);
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

    setController(j25) {
        this.controller = j25;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(i25) {
        this.__imageSize.set(i25);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(h25) {
        this.__isChecked.set(h25);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(g25) {
        this.__imageSizeHeight.set(g25);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(f25) {
        this.__textAlignment.set(f25);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(e25) {
        this.__checkBoxHeight.set(e25);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(d25) {
        this.__buttonHeight.set(d25);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(c25) {
        this.__fontColorWithTheme.set(c25);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(b25) {
        this.__fontSizeScale.set(b25);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(a25) {
        this.__windowSize.set(a25);
    }

    initialRender() {
        this.observeComponentCreation2((y24, z24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((s24, t24) => {
                if (t24) {
                    let u24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, s24, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 112, col: 5 });
                    ViewPU.create(u24);
                    let v24 = () => {
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
                    u24.paramsGenerator_ = v24;
                } else {
                    this.updateStateVarsOfChildByElmtId(s24, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    contentBuilder(z23 = null) {
        this.observeComponentCreation2((o24, p24) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(z23 ? z23 : this);
        this.observeComponentCreation2((h24, i24) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m24, n24) => {
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
                    this.textPart.bind(this)(z23 ? z23 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((d24, e24) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, z23 ? z23 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(i23, j23 = null) {
        this.observeComponentCreation2((u23, v23) => {
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
            Row.onAreaChange((x23, y23) => {
                this.checkBoxHeight = Number(y23.height);
            });
        }, Row);
        this.observeComponentCreation2((q23, r23) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((t23) => {
                this.isChecked = t23;
                if (this.checkAction) {
                    this.checkAction(t23);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(t23);
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
        this.observeComponentCreation2((n23, o23) => {
            Text.create(i23);
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
        Row.pop();
    }

    imagePart(y22 = null) {
        this.observeComponentCreation2((d23, e23) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((g23, h23) => {
                this.imageSizeHeight = Number(h23.height);
            });
        }, Column);
        this.observeComponentCreation2((b23, c23) => {
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

    textPart(q21 = null) {
        this.observeComponentCreation2((w22, x22) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((u22, v22) => {
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
        this.observeComponentCreation2((k22, l22) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s22, t22) => {
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
                    this.observeComponentCreation2((q22, r22) => {
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
        this.observeComponentCreation2((v21, w21) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i22, j22) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((b22, c22) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((h22) => {
                            if (h22) {
                                resolveKeyEvent(h22, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((f22, g22) => {
                            this.getTextAlign(Number(g22.width));
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

    getTextAlign(m21) {
        let n21 = this.getContentFontSize();
        let o21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: n21,
            constraintWidth: m21,
        });
        let p21 = measure.measureTextSize({
            textContent: this.content,
            fontSize: n21,
        });
        if (this.getTextHeight(o21) <= this.getTextHeight(p21)) {
            this.textAlignment = TextAlign.Center;
        }
    }

    getContentFontSize() {
        return BODY_L + 'fp';
    }

    getTextHeight(l21) {
        if (l21 && l21.height !== null && l21.height !== undefined) {
            return Number(l21.height);
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
    constructor(f21, g21, h21, i21 = -1, j21 = undefined, k21) {
        super(f21, h21, i21, k21);
        if (typeof j21 === 'function') {
            this.paramsGenerator_ = j21;
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
        this.setInitiallyProvidedValue(g21);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e21) {
        if (e21.controller !== undefined) {
            this.controller = e21.controller;
        }
        if (e21.title !== undefined) {
            this.title = e21.title;
        }
        if (e21.content !== undefined) {
            this.content = e21.content;
        }
        if (e21.selectedIndex !== undefined) {
            this.selectedIndex = e21.selectedIndex;
        }
        if (e21.confirm !== undefined) {
            this.confirm = e21.confirm;
        }
        if (e21.radioContent !== undefined) {
            this.radioContent = e21.radioContent;
        }
        if (e21.buttons !== undefined) {
            this.buttons = e21.buttons;
        }
        if (e21.contentPadding !== undefined) {
            this.contentPadding = e21.contentPadding;
        }
        if (e21.isFocus !== undefined) {
            this.isFocus = e21.isFocus;
        }
        if (e21.currentFocusIndex !== undefined) {
            this.currentFocusIndex = e21.currentFocusIndex;
        }
        if (e21.radioHeight !== undefined) {
            this.radioHeight = e21.radioHeight;
        }
        if (e21.itemHeight !== undefined) {
            this.itemHeight = e21.itemHeight;
        }
        if (e21.contentBuilder !== undefined) {
            this.contentBuilder = e21.contentBuilder;
        }
        if (e21.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = e21.fontColorWithTheme;
        }
        if (e21.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = e21.dividerColorWithTheme;
        }
        if (e21.theme !== undefined) {
            this.theme = e21.theme;
        }
        if (e21.themeColorMode !== undefined) {
            this.themeColorMode = e21.themeColorMode;
        }
        if (e21.contentScroller !== undefined) {
            this.contentScroller = e21.contentScroller;
        }
        if (e21.fontSizeScale !== undefined) {
            this.fontSizeScale = e21.fontSizeScale;
        }
        if (e21.windowSize !== undefined) {
            this.windowSize = e21.windowSize;
        }
    }

    updateStateVars(d21) {
    }

    purgeVariableDependenciesOnElmtId(c21) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(c21);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(c21);
        this.__fontSizeScale.purgeDependencyOnElmtId(c21);
        this.__windowSize.purgeDependencyOnElmtId(c21);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(b21) {
        this.controller = b21;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(a21) {
        this.__fontColorWithTheme.set(a21);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(z20) {
        this.__dividerColorWithTheme.set(z20);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(y20) {
        this.__fontSizeScale.set(y20);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(x20) {
        this.__windowSize.set(x20);
    }

    buildContent(y17 = null) {
        this.observeComponentCreation2((r20, s20) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((u20, v20) => {
                let w20 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (v20 > 0) {
                            this.contentScroller.scrollBy(0, w20);
                        } else if (v20 < 0) {
                            this.contentScroller.scrollBy(0, 0 - w20);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((p20, q20) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((f20, g20) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n20, o20) => {
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
                    this.observeComponentCreation2((l20, m20) => {
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
        this.observeComponentCreation2((c20, d20) => {
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
        this.observeComponentCreation2((e18, f18) => {
            ForEach.create();
            const g18 = (i18, j18) => {
                const k18 = i18;
                {
                    const l18 = (a20, b20) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a20);
                        m18(a20, b20);
                        if (!b20) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const m18 = (v19, w19) => {
                        ListItem.create(n18, true);
                        ListItem.onSizeChange((y19, z19) => {
                            this.itemHeight = Number(z19.height);
                        });
                    };
                    const n18 = (r18, s18) => {
                        l18(r18, s18);
                        this.observeComponentCreation2((t19, u19) => {
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
                        this.observeComponentCreation2((q19, r19) => {
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
                                k18.action && k18.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((o19, p19) => {
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
                        this.observeComponentCreation2((m19, n19) => {
                            Text.create(k18.title);
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
                        this.observeComponentCreation2((g19, h19) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === j18);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(j18));
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = j18;
                                if (j18 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (j18 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((k19, l19) => {
                                this.radioHeight = Number(l19.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((z18, a19) => {
                            If.create();
                            if (j18 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((e19, f19) => {
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
                    this.observeComponentCreation2(m18, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(e18, this.radioContent, g18, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        this.observeComponentCreation2((w17, x17) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((q17, r17) => {
                if (r17) {
                    let s17 = new CustomDialogContentComponent(this, {
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
                    }, undefined, q17, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 439, col: 5 });
                    ViewPU.create(s17);
                    let t17 = () => {
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
                    s17.paramsGenerator_ = t17;
                } else {
                    this.updateStateVarsOfChildByElmtId(q17, {});
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

export class ConfirmDialog extends ViewPU {
    constructor(e17, f17, g17, h17 = -1, i17 = undefined, j17) {
        super(e17, g17, h17, j17);
        if (typeof i17 === 'function') {
            this.paramsGenerator_ = i17;
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
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__checkBoxHeight = new ObservedPropertySimplePU(CHECKBOX_CONTAINER_HEIGHT, this, 'checkBoxHeight');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
        this.__maxContentHeight =
            new ObservedPropertySimplePU(`calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`,
                this, 'maxContentHeight');
        this.updateTitleHeight = (n17) => {
            this.titleHeight = n17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (m17) => {
            this.buttonHeight = m17;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(f17);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(d17) {
        if (d17.controller !== undefined) {
            this.controller = d17.controller;
        }
        if (d17.title !== undefined) {
            this.title = d17.title;
        }
        if (d17.content !== undefined) {
            this.content = d17.content;
        }
        if (d17.checkTips !== undefined) {
            this.checkTips = d17.checkTips;
        }
        if (d17.isChecked !== undefined) {
            this.isChecked = d17.isChecked;
        }
        if (d17.primaryButton !== undefined) {
            this.primaryButton = d17.primaryButton;
        }
        if (d17.secondaryButton !== undefined) {
            this.secondaryButton = d17.secondaryButton;
        }
        if (d17.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = d17.fontColorWithTheme;
        }
        if (d17.theme !== undefined) {
            this.theme = d17.theme;
        }
        if (d17.themeColorMode !== undefined) {
            this.themeColorMode = d17.themeColorMode;
        }
        if (d17.onCheckedChange !== undefined) {
            this.onCheckedChange = d17.onCheckedChange;
        }
        if (d17.contentScroller !== undefined) {
            this.contentScroller = d17.contentScroller;
        }
        if (d17.buttons !== undefined) {
            this.buttons = d17.buttons;
        }
        if (d17.textAlign !== undefined) {
            this.textAlign = d17.textAlign;
        }
        if (d17.marginOffset !== undefined) {
            this.marginOffset = d17.marginOffset;
        }
        if (d17.titleHeight !== undefined) {
            this.titleHeight = d17.titleHeight;
        }
        if (d17.buttonHeight !== undefined) {
            this.buttonHeight = d17.buttonHeight;
        }
        if (d17.checkBoxHeight !== undefined) {
            this.checkBoxHeight = d17.checkBoxHeight;
        }
        if (d17.fontSizeScale !== undefined) {
            this.fontSizeScale = d17.fontSizeScale;
        }
        if (d17.windowSize !== undefined) {
            this.windowSize = d17.windowSize;
        }
        if (d17.maxContentHeight !== undefined) {
            this.maxContentHeight = d17.maxContentHeight;
        }
        if (d17.updateTitleHeight !== undefined) {
            this.updateTitleHeight = d17.updateTitleHeight;
        }
        if (d17.updateButtonHeight !== undefined) {
            this.updateButtonHeight = d17.updateButtonHeight;
        }
    }

    updateStateVars(c17) {
    }

    purgeVariableDependenciesOnElmtId(b17) {
        this.__isChecked.purgeDependencyOnElmtId(b17);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(b17);
        this.__textAlign.purgeDependencyOnElmtId(b17);
        this.__titleHeight.purgeDependencyOnElmtId(b17);
        this.__buttonHeight.purgeDependencyOnElmtId(b17);
        this.__checkBoxHeight.purgeDependencyOnElmtId(b17);
        this.__fontSizeScale.purgeDependencyOnElmtId(b17);
        this.__windowSize.purgeDependencyOnElmtId(b17);
        this.__maxContentHeight.purgeDependencyOnElmtId(b17);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__textAlign.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__maxContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(a17) {
        this.controller = a17;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(z16) {
        this.__isChecked.set(z16);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(y16) {
        this.__fontColorWithTheme.set(y16);
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(x16) {
        this.__textAlign.set(x16);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(w16) {
        this.__titleHeight.set(w16);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(v16) {
        this.__buttonHeight.set(v16);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(u16) {
        this.__checkBoxHeight.set(u16);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(t16) {
        this.__fontSizeScale.set(t16);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(s16) {
        this.__windowSize.set(s16);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(r16) {
        this.__maxContentHeight.set(r16);
    }

    buildContent(f15 = null) {
        this.observeComponentCreation2((p16, q16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((x15, y15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n16, o16) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((l16, m16) => {
                        Scroll.create(this.contentScroller);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.PARALLEL,
                            scrollBackward: NestedScrollMode.PARALLEL
                        });
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((e16, f16) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
                        Text.fontSize(this.getContentFontSize());
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlign);
                        Text.onAreaChange((j16, k16) => this.getTextAlign(Number(k16.width)));
                        Text.margin({
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.padding_level8'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            }
                        });
                        Text.onKeyEvent((i16) => {
                            if (i16) {
                                resolveKeyEvent(i16, this.contentScroller);
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
        this.observeComponentCreation2((o15, p15) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((r15) => {
                this.isChecked = r15;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((l15, m15) => {
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
        Column.pop();
    }

    getContentFontSize() {
        return BODY_L + 'fp';
    }

    getTextAlign(b15) {
        let c15 = this.getContentFontSize();
        let d15 = measure.measureTextSize({
            textContent: this.content,
            fontSize: c15,
            constraintWidth: b15,
        });
        let e15 = measure.measureTextSize({
            textContent: this.content,
            fontSize: c15,
        });
        if (this.getTextHeight(d15) <= this.getTextHeight(e15)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(a15) {
        if (a15 && a15.height !== null && a15.height !== undefined) {
            return Number(a15.height);
        }
        return 0;
    }

    initialRender() {
        this.observeComponentCreation2((y14, z14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((s14, t14) => {
                if (t14) {
                    let u14 = new CustomDialogContentComponent(this, {
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
                    }, undefined, s14, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 625, col: 5 });
                    ViewPU.create(u14);
                    let v14 = () => {
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
                    u14.paramsGenerator_ = v14;
                } else {
                    this.updateStateVarsOfChildByElmtId(s14, {});
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
    constructor(k14, l14, m14, n14 = -1, o14 = undefined, p14) {
        super(k14, m14, n14, p14);
        if (typeof o14 === 'function') {
            this.paramsGenerator_ = o14;
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
        this.setInitiallyProvidedValue(l14);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j14) {
        if (j14.controller !== undefined) {
            this.controller = j14.controller;
        }
        if (j14.primaryTitle !== undefined) {
            this.primaryTitle = j14.primaryTitle;
        }
        if (j14.secondaryTitle !== undefined) {
            this.secondaryTitle = j14.secondaryTitle;
        }
        if (j14.content !== undefined) {
            this.content = j14.content;
        }
        if (j14.primaryButton !== undefined) {
            this.primaryButton = j14.primaryButton;
        }
        if (j14.secondaryButton !== undefined) {
            this.secondaryButton = j14.secondaryButton;
        }
        if (j14.buttons !== undefined) {
            this.buttons = j14.buttons;
        }
        if (j14.textAlign !== undefined) {
            this.textAlign = j14.textAlign;
        }
        if (j14.contentScroller !== undefined) {
            this.contentScroller = j14.contentScroller;
        }
        if (j14.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = j14.fontColorWithTheme;
        }
        if (j14.theme !== undefined) {
            this.theme = j14.theme;
        }
        if (j14.themeColorMode !== undefined) {
            this.themeColorMode = j14.themeColorMode;
        }
        if (j14.windowSize !== undefined) {
            this.windowSize = j14.windowSize;
        }
        if (j14.fontSizeScale !== undefined) {
            this.fontSizeScale = j14.fontSizeScale;
        }
    }

    updateStateVars(i14) {
    }

    purgeVariableDependenciesOnElmtId(h14) {
        this.__textAlign.purgeDependencyOnElmtId(h14);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(h14);
        this.__windowSize.purgeDependencyOnElmtId(h14);
        this.__fontSizeScale.purgeDependencyOnElmtId(h14);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(g14) {
        this.controller = g14;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(f14) {
        this.__textAlign.set(f14);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(e14) {
        this.__fontColorWithTheme.set(e14);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(d14) {
        this.__windowSize.set(d14);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(c14) {
        this.__fontSizeScale.set(c14);
    }

    initialRender() {
        this.observeComponentCreation2((a14, b14) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((u13, v13) => {
                if (v13) {
                    let w13 = new CustomDialogContentComponent(this, {
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
                    }, undefined, u13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 685, col: 5 });
                    ViewPU.create(w13);
                    let x13 = () => {
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
                    w13.paramsGenerator_ = x13;
                } else {
                    this.updateStateVarsOfChildByElmtId(u13, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }

    AlertDialogContentBuilder(d13 = null) {
        this.observeComponentCreation2((q13, r13) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((o13, p13) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((h13, i13) => {
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
            Text.onAreaChange((m13, n13) => {
                this.getTextAlign(Number(n13.width));
            });
            Text.onKeyEvent((l13) => {
                if (l13) {
                    resolveKeyEvent(l13, this.contentScroller);
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
        return BODY_L + 'fp';
    }

    getTextAlign(z12) {
        let a13 = this.getContentFontSize();
        let b13 = measure.measureTextSize({
            textContent: this.content,
            fontSize: a13,
            constraintWidth: z12,
        });
        let c13 = measure.measureTextSize({
            textContent: this.content,
            fontSize: a13,
        });
        if (this.getTextHeight(b13) <= this.getTextHeight(c13)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(y12) {
        if (y12 && y12.height !== null && y12.height !== undefined) {
            return Number(y12.height);
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
    constructor(s12, t12, u12, v12 = -1, w12 = undefined, x12) {
        super(s12, u12, v12, x12);
        if (typeof w12 === 'function') {
            this.paramsGenerator_ = w12;
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
        this.setInitiallyProvidedValue(t12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(r12) {
        if (r12.controller !== undefined) {
            this.controller = r12.controller;
        }
        if (r12.primaryTitle !== undefined) {
            this.primaryTitle = r12.primaryTitle;
        }
        if (r12.secondaryTitle !== undefined) {
            this.secondaryTitle = r12.secondaryTitle;
        }
        if (r12.contentBuilder !== undefined) {
            this.contentBuilder = r12.contentBuilder;
        }
        if (r12.contentAreaPadding !== undefined) {
            this.contentAreaPadding = r12.contentAreaPadding;
        }
        if (r12.buttons !== undefined) {
            this.buttons = r12.buttons;
        }
        if (r12.theme !== undefined) {
            this.theme = r12.theme;
        }
        if (r12.themeColorMode !== undefined) {
            this.themeColorMode = r12.themeColorMode;
        }
        if (r12.fontSizeScale !== undefined) {
            this.fontSizeScale = r12.fontSizeScale;
        }
        if (r12.windowSize !== undefined) {
            this.windowSize = r12.windowSize;
        }
    }

    updateStateVars(q12) {
    }

    purgeVariableDependenciesOnElmtId(p12) {
        this.__fontSizeScale.purgeDependencyOnElmtId(p12);
        this.__windowSize.purgeDependencyOnElmtId(p12);
    }

    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(o12) {
        this.controller = o12;
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(n12) {
        this.__fontSizeScale.set(n12);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(m12) {
        this.__windowSize.set(m12);
    }

    initialRender() {
        this.observeComponentCreation2((k12, l12) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((e12, f12) => {
                if (f12) {
                    let g12 = new CustomDialogContentComponent(this, {
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
                    }, undefined, e12, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 800, col: 5 });
                    ViewPU.create(g12);
                    let h12 = () => {
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
                    g12.paramsGenerator_ = h12;
                } else {
                    this.updateStateVarsOfChildByElmtId(e12, {});
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
    constructor(w11, x11, y11, z11 = -1, a12 = undefined, b12) {
        super(w11, y11, z11, b12);
        if (typeof a12 === 'function') {
            this.paramsGenerator_ = a12;
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
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(x11.fontSizeScale, this, 'fontSizeScale');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(x11.windowSize, this, 'windowSize');
        this.__customStyle = new ObservedPropertySimplePU(false, this, 'customStyle');
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
        if (v11.updateTitleHeight !== undefined) {
            this.updateTitleHeight = v11.updateTitleHeight;
        }
        if (v11.updateButtonHeight !== undefined) {
            this.updateButtonHeight = v11.updateButtonHeight;
        }
        if (v11.targetSdk !== undefined) {
            this.targetSdk = v11.targetSdk;
        }
        if (v11.customStyle !== undefined) {
            this.customStyle = v11.customStyle;
        }
        if (v11.screenSize !== undefined) {
            this.screenSize = v11.screenSize;
        }
        if (v11.initCustomStyle !== undefined) {
            this.initCustomStyle = v11.initCustomStyle;
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
    }

    updateStateVars(u11) {
    }

    purgeVariableDependenciesOnElmtId(t11) {
        this.__titleHeight.purgeDependencyOnElmtId(t11);
        this.__buttonHeight.purgeDependencyOnElmtId(t11);
        this.__contentMaxHeight.purgeDependencyOnElmtId(t11);
        this.__fontSizeScale.purgeDependencyOnElmtId(t11);
        this.__windowSize.purgeDependencyOnElmtId(t11);
        this.__customStyle.purgeDependencyOnElmtId(t11);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(t11);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(t11);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(t11);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(t11);
    }

    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__contentMaxHeight.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
        this.__customStyle.aboutToBeDeleted();
        this.__buttonMaxFontSize.aboutToBeDeleted();
        this.__buttonMinFontSize.aboutToBeDeleted();
        this.__primaryTitleMaxFontSize.aboutToBeDeleted();
        this.__primaryTitleMinFontSize.aboutToBeDeleted();
        this.__secondaryTitleMaxFontSize.aboutToBeDeleted();
        this.__secondaryTitleMinFontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
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

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(n11) {
        this.__windowSize.set(n11);
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
                        theme: this.theme,
                        primaryTitleMaxFontSize: this.__primaryTitleMaxFontSize,
                        primaryTitleMinFontSize: this.__primaryTitleMinFontSize,
                        secondaryTitleMaxFontSize: this.__secondaryTitleMaxFontSize,
                        secondaryTitleMinFontSize: this.__secondaryTitleMinFontSize
                    }, undefined, u10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 856, col: 11 });
                    ViewPU.create(w10);
                    let x10 = () => {
                        return {
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            windowSize: this.windowSize,
                            fontSizeScale: this.fontSizeScale,
                            titleHeight: this.titleHeight,
                            theme: this.theme,
                            primaryTitleMaxFontSize: this.primaryTitleMaxFontSize,
                            primaryTitleMinFontSize: this.primaryTitleMinFontSize,
                            secondaryTitleMaxFontSize: this.secondaryTitleMaxFontSize,
                            secondaryTitleMinFontSize: this.secondaryTitleMinFontSize
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
                        buttonHeight: this.__buttonHeight,
                        controller: this.controller,
                        theme: this.theme,
                        buttonMaxFontSize: this.__buttonMaxFontSize,
                        buttonMinFontSize: this.__buttonMinFontSize
                    }, undefined, l10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 875, col: 11 });
                    ViewPU.create(n10);
                    let o10 = () => {
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

    aboutToAppear() {
        this.initEnvInfo();
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
        this.__primaryTitleMaxFontSize =
            new SynchedPropertyObjectTwoWayPU(e9.primaryTitleMaxFontSize, this, 'primaryTitleMaxFontSize');
        this.__primaryTitleMinFontSize =
            new SynchedPropertyObjectTwoWayPU(e9.primaryTitleMinFontSize, this, 'primaryTitleMinFontSize');
        this.__secondaryTitleMaxFontSize =
            new SynchedPropertyObjectTwoWayPU(e9.secondaryTitleMaxFontSize, this, 'secondaryTitleMaxFontSize');
        this.__secondaryTitleMinFontSize =
            new SynchedPropertyObjectTwoWayPU(e9.secondaryTitleMinFontSize, this, 'secondaryTitleMinFontSize');
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

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(s8) {
        this.__fontSizeScale.set(s8);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(r8) {
        this.__windowSize.set(r8);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(q8) {
        this.__titleHeight.set(q8);
    }

    initialRender() {
        this.observeComponentCreation2((o8, p8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((m8, n8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((k8, l8) => {
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
        this.observeComponentCreation2((a8, b8) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i8, j8) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((g8, h8) => {
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
        this.observeComponentCreation2((y7, z7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((w7, x7) => {
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
    }

    onMeasureSize(i7, j7, k7) {
        let l7 = { width: i7.width, height: i7.height };
        let m7 = {
            minWidth: k7.minWidth,
            minHeight: this.getTitleAreaMinHeight(),
            maxWidth: k7.maxWidth,
            maxHeight: k7.maxHeight
        };
        j7.forEach((o7) => {
            let p7 = o7.measure(m7);
            l7.height = p7.height;
            l7.width = p7.width;
        });
        this.titleHeight = l7.height;
        return l7;
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
        let h7 = getEnumNumberByResource('alert_title_alignment');
        if (h7 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (h7 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (h7 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (h7 === TextAlign.JUSTIFY) {
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
    constructor(b7, c7, d7, e7 = -1, f7 = undefined, g7) {
        super(b7, d7, e7, g7);
        if (typeof f7 === 'function') {
            this.paramsGenerator_ = f7;
        }
        this.controller = undefined;
        this.buttons = undefined;
        this.__buttonMaxFontSize = new SynchedPropertyObjectTwoWayPU(c7.buttonMaxFontSize, this, 'buttonMaxFontSize');
        this.__buttonMinFontSize = new SynchedPropertyObjectTwoWayPU(c7.buttonMinFontSize, this, 'buttonMinFontSize');
        this.keyIndex = 0;
        this.theme = new CustomThemeImpl({});
        this.__singleButtonHeight = new ObservedPropertySimplePU(BUTTON_DEFAULT_HEIGHT, this, 'singleButtonHeight');
        this.__isButtonVertical = new ObservedPropertySimplePU(false, this, 'isButtonVertical');
        this.__windowSize = new SynchedPropertyObjectTwoWayPU(c7.windowSize, this, 'windowSize');
        this.__buttonHeight = new SynchedPropertyObjectTwoWayPU(c7.buttonHeight, this, 'buttonHeight');
        this.setInitiallyProvidedValue(c7);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a7) {
        if (a7.controller !== undefined) {
            this.controller = a7.controller;
        }
        if (a7.buttons !== undefined) {
            this.buttons = a7.buttons;
        }
        if (a7.keyIndex !== undefined) {
            this.keyIndex = a7.keyIndex;
        }
        if (a7.theme !== undefined) {
            this.theme = a7.theme;
        }
        if (a7.singleButtonHeight !== undefined) {
            this.singleButtonHeight = a7.singleButtonHeight;
        }
        if (a7.isButtonVertical !== undefined) {
            this.isButtonVertical = a7.isButtonVertical;
        }
    }

    updateStateVars(z6) {
    }

    purgeVariableDependenciesOnElmtId(y6) {
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(y6);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(y6);
        this.__singleButtonHeight.purgeDependencyOnElmtId(y6);
        this.__isButtonVertical.purgeDependencyOnElmtId(y6);
        this.__windowSize.purgeDependencyOnElmtId(y6);
        this.__buttonHeight.purgeDependencyOnElmtId(y6);
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

    set buttonMaxFontSize(x6) {
        this.__buttonMaxFontSize.set(x6);
    }

    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }

    set buttonMinFontSize(w6) {
        this.__buttonMinFontSize.set(w6);
    }

    get singleButtonHeight() {
        return this.__singleButtonHeight.get();
    }

    set singleButtonHeight(v6) {
        this.__singleButtonHeight.set(v6);
    }

    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }

    set isButtonVertical(u6) {
        this.__isButtonVertical.set(u6);
    }

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(t6) {
        this.__windowSize.set(t6);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(s6) {
        this.__buttonHeight.set(s6);
    }

    initialRender() {
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

    onMeasureSize(y5, z5, a6) {
        let b6 = { width: y5.width, height: y5.height };
        this.isButtonVertical = this.isVerticalAlignButton(Number(a6.maxWidth));
        z5.forEach((d6) => {
            let e6 = d6.measure(a6);
            b6.height = e6.height;
            b6.width = e6.width;
        });
        this.buttonHeight = Number(b6.height);
        return b6;
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

    buildSingleButton(d5, e5 = null) {
        this.observeComponentCreation2((g5, h5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(d5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        Button.createWithLabel(d5.value);
                        __Button__setButtonProperties(d5, this.controller);
                        Button.role(d5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (d5.background !== undefined && d5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s5, t5) => {
                        Button.createWithLabel(d5.value);
                        __Button__setButtonProperties(d5, this.controller);
                        Button.backgroundColor(d5.background);
                        Button.fontColor(d5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (d5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((o5, p5) => {
                        Button.createWithLabel(d5.value);
                        __Button__setButtonProperties(d5, this.controller);
                        Button.backgroundColor(d5.background);
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
                    this.observeComponentCreation2((k5, l5) => {
                        Button.createWithLabel(d5.value);
                        __Button__setButtonProperties(d5, this.controller);
                        Button.fontColor(d5.fontColor);
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

    buildHorizontalAlignButtons(m4 = null) {
        this.observeComponentCreation2((o4, p4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b5, c5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], m4 ? m4 : this);
                    this.observeComponentCreation2((u4, v4) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z4, a5) => {
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
                                    m4 ? m4 : this);
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

    buildVerticalAlignButtons(t3 = null) {
        this.observeComponentCreation2((v3, w3) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k4, l4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((b4, c4) => {
                        ForEach.create();
                        const d4 = (h4, i4) => {
                            const j4 = h4;
                            this.buildButtonWithDivider.bind(this)(i4, t3 ? t3 : this);
                        };
                        this.forEachUpdateFunction(b4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), d4,
                            (g4) => g4.value.toString(), true, false);
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

    isNewPropertiesHighPriority(s3) {
        if (s3.role === ButtonRole.ERROR) {
            return true;
        }
        if (s3.buttonStyle !== undefined &&
            s3.buttonStyle !== getNumberByResource('alert_button_style')) {
            return true;
        }
        if (s3.background === undefined && s3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    buildButtonWithDivider(a3, b3 = null) {
        this.observeComponentCreation2((d3, e3) => {
            If.create();
            if (this.buttons && this.buttons[a3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q3, r3) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[a3], b3 ? b3 : this);
                    Row.pop();
                    this.observeComponentCreation2((j3, k3) => {
                        If.create();
                        if (a3 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((o3, p3) => {
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

    isVerticalAlignButton(u2) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let v2 = false;
            let w2 = vp2px(u2 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((y2) => {
                let z2 = measure.measureTextSize({
                    textContent: y2.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(z2.width) > w2) {
                    v2 = true;
                }
            });
            return v2;
        }
        return false;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function __Button__setButtonProperties(r2, s2) {
    Button.onClick(() => {
        if (r2.action) {
            r2.action();
        }
        s2?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(r2.buttonStyle ?? getNumberByResource('alert_button_style'));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}

function getNumberByResource(n2) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(n2);
    } catch (o2) {
        let p2 = o2.code;
        let q2 = o2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${p2}, message: ${q2}`);
        return 0;
    }
}

function getEnumNumberByResource(j2) {
    try {
        return getContext().resourceManager.getNumberByName(j2);
    } catch (k2) {
        let l2 = k2.code;
        let m2 = k2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${l2}, message: ${m2}`);
        return -1;
    }
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
        this.__windowSize = new ObservedPropertyObjectPU({ width: 0, height: 0 }, this, 'windowSize');
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
        if (a2.windowSize !== undefined) {
            this.windowSize = a2.windowSize;
        }
    }

    updateStateVars(z1) {
    }

    purgeVariableDependenciesOnElmtId(y1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(y1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(y1);
        this.__fontSizeScale.purgeDependencyOnElmtId(y1);
        this.__windowSize.purgeDependencyOnElmtId(y1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__windowSize.aboutToBeDeleted();
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

    get windowSize() {
        return this.__windowSize.get();
    }

    set windowSize(t1) {
        this.__windowSize.set(t1);
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
                        windowSize: this.__windowSize
                    }, undefined, j1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1478, col: 7 });
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
                            windowSize: this.windowSize
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
