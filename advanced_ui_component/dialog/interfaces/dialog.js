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
    constructor(l21) {
        this.colors = l21;
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
const LOADING_TEXT_LAYOUT_WEIGHT = 1;
const LOADING_TEXT_MARGIN_LEFT = 12;
const LOADING_MIN_HEIGHT = 48;
const LIST_MIN_HEIGHT = 48;
const CHECKBOX_CONTAINER_LENGTH = 20;
const TEXT_MIN_HEIGHT = 48;
const DEFAULT_IMAGE_SIZE = 64;
const KEYCODE_UP = 2012;
const KEYCODE_DOWN = 2013;
const IGNORE_KEY_EVENT_TYPE = 1;
const FIRST_ITEM_INDEX = 0;
const VERSION_TWELVE = 50000012;

export class TipsDialog extends ViewPU {
    constructor(f21, g21, h21, i21 = -1, j21 = undefined, k21) {
        super(f21, h21, i21, k21);
        if (typeof j21 === 'function') {
            this.paramsGenerator_ = j21;
        }
        this.controller = undefined;
        this.imageRes = null;
        this.__imageSize =
            new ObservedPropertyObjectPU({ width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE }, this, 'imageSize');
        this.title = null;
        this.content = null;
        this.checkAction = undefined;
        this.checkTips = null;
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.primaryButton = null;
        this.secondaryButton = null;
        this.buttons = undefined;
        this.__imageSizeHeight = new ObservedPropertySimplePU(0, this, 'imageSizeHeight');
        this.__textAlignment = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlignment');
        this.marginOffset = 0;
        this.__checkBoxHeight = new ObservedPropertySimplePU(0, this, 'checkBoxHeight');
        this.buttonHeight = 0;
        this.contentScroller = new Scroller();
        this.__fontColorWithTheme = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'fontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.setInitiallyProvidedValue(g21);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e21) {
        if (e21.controller !== undefined) {
            this.controller = e21.controller;
        }
        if (e21.imageRes !== undefined) {
            this.imageRes = e21.imageRes;
        }
        if (e21.imageSize !== undefined) {
            this.imageSize = e21.imageSize;
        }
        if (e21.title !== undefined) {
            this.title = e21.title;
        }
        if (e21.content !== undefined) {
            this.content = e21.content;
        }
        if (e21.checkAction !== undefined) {
            this.checkAction = e21.checkAction;
        }
        if (e21.checkTips !== undefined) {
            this.checkTips = e21.checkTips;
        }
        if (e21.isChecked !== undefined) {
            this.isChecked = e21.isChecked;
        }
        if (e21.primaryButton !== undefined) {
            this.primaryButton = e21.primaryButton;
        }
        if (e21.secondaryButton !== undefined) {
            this.secondaryButton = e21.secondaryButton;
        }
        if (e21.buttons !== undefined) {
            this.buttons = e21.buttons;
        }
        if (e21.imageSizeHeight !== undefined) {
            this.imageSizeHeight = e21.imageSizeHeight;
        }
        if (e21.textAlignment !== undefined) {
            this.textAlignment = e21.textAlignment;
        }
        if (e21.marginOffset !== undefined) {
            this.marginOffset = e21.marginOffset;
        }
        if (e21.checkBoxHeight !== undefined) {
            this.checkBoxHeight = e21.checkBoxHeight;
        }
        if (e21.buttonHeight !== undefined) {
            this.buttonHeight = e21.buttonHeight;
        }
        if (e21.contentScroller !== undefined) {
            this.contentScroller = e21.contentScroller;
        }
        if (e21.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = e21.fontColorWithTheme;
        }
        if (e21.theme !== undefined) {
            this.theme = e21.theme;
        }
    }

    updateStateVars(d21) {
    }

    purgeVariableDependenciesOnElmtId(c21) {
        this.__imageSize.purgeDependencyOnElmtId(c21);
        this.__isChecked.purgeDependencyOnElmtId(c21);
        this.__imageSizeHeight.purgeDependencyOnElmtId(c21);
        this.__textAlignment.purgeDependencyOnElmtId(c21);
        this.__checkBoxHeight.purgeDependencyOnElmtId(c21);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(c21);
    }

    aboutToBeDeleted() {
        this.__imageSize.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        this.__imageSizeHeight.aboutToBeDeleted();
        this.__textAlignment.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(b21) {
        this.controller = b21;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(a21) {
        this.__imageSize.set(a21);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(z20) {
        this.__isChecked.set(z20);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(y20) {
        this.__imageSizeHeight.set(y20);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(x20) {
        this.__textAlignment.set(x20);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(w20) {
        this.__checkBoxHeight.set(w20);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(v20) {
        this.__fontColorWithTheme.set(v20);
    }

    initialRender() {
        {
            this.observeComponentCreation2((p20, q20) => {
                if (q20) {
                    let r20 = new CustomDialogComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, p20, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 85, col: 5 });
                    ViewPU.create(r20);
                    let s20 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme
                        };
                    };
                    r20.paramsGenerator_ = s20;
                } else {
                    this.updateStateVarsOfChildByElmtId(p20, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
    }

    contentBuilder(x19 = null) {
        this.observeComponentCreation2((m20, n20) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(x19 ? x19 : this);
        this.observeComponentCreation2((f20, g20) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k20, l20) => {
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
                    this.textPart.bind(this)(x19 ? x19 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((b20, c20) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, x19 ? x19 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(g19, h19 = null) {
        this.observeComponentCreation2((s19, t19) => {
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
            Row.onAreaChange((v19, w19) => {
                this.checkBoxHeight = Number(w19.height);
            });
        }, Row);
        this.observeComponentCreation2((o19, p19) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((r19) => {
                this.isChecked = r19;
                if (this.checkAction) {
                    this.checkAction(r19);
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
        this.observeComponentCreation2((l19, m19) => {
            Text.create(g19);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_M'],
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

    imagePart(w18 = null) {
        this.observeComponentCreation2((b19, c19) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((e19, f19) => {
                this.imageSizeHeight = Number(f19.height);
            });
        }, Column);
        this.observeComponentCreation2((z18, a19) => {
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

    textPart(o17 = null) {
        this.observeComponentCreation2((u18, v18) => {
            Scroll.create(this.contentScroller);
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((s18, t18) => {
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
        this.observeComponentCreation2((i18, j18) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q18, r18) => {
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
                    this.observeComponentCreation2((o18, p18) => {
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
                        Text.minFontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_L'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.maxFontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Title_S'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
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
        this.observeComponentCreation2((t17, u17) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g18, h18) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((z17, a18) => {
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
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.textAlign(this.textAlignment);
                        Text.width('100%');
                        Text.onKeyEvent((f18) => {
                            if (f18) {
                                resolveKeyEvent(f18, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((d18, e18) => {
                            this.getTextAlign(Number(e18.width));
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

    getTextAlign(l17) {
        let m17 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            constraintWidth: l17,
        });
        let n17 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        });
        if (this.getTextHeight(m17) <= this.getTextHeight(n17)) {
            this.textAlignment = TextAlign.Center;
        }
    }

    getTextHeight(k17) {
        if (k17 && k17.height !== null && k17.height !== undefined) {
            return Number(k17.height);
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
        this.buttonHeight = this.getButtonsHeight();
    }

    getButtonsHeight() {
        if (!this.buttons || this.buttons.length === 0) {
            return 0;
        }
        let j17 = getNumberByResource('alert_button_top_padding');
        j17 += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
        return j17;
    }

    initMargin() {
        this.marginOffset = 0 - getNumberByResource('padding_level8');
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(z16, a17, b17, c17 = -1, d17 = undefined, e17) {
        super(z16, b17, c17, e17);
        if (typeof d17 === 'function') {
            this.paramsGenerator_ = d17;
        }
        this.title = '';
        this.content = '';
        this.selectedIndex = -1;
        this.confirm = null;
        this.radioContent = [];
        this.buttons = [];
        this.contentPadding = undefined;
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
        this.controller = new CustomDialogController({
            builder: () => {
                let f17 = new CustomContentDialog(this, {
                    primaryTitle: this.title,
                    contentBuilder: () => {
                        this.contentBuilder();
                    },
                    buttons: this.buttons,
                }, undefined, -1, () => {
                }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 289, col: 14 });
                f17.setController(this.controller);
                ViewPU.create(f17);
                let g17 = () => {
                    return {
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons
                    };
                };
                f17.paramsGenerator_ = g17;
            }
        }, this);
        this.contentScroller = new Scroller();
        this.setInitiallyProvidedValue(a17);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(y16) {
        if (y16.title !== undefined) {
            this.title = y16.title;
        }
        if (y16.content !== undefined) {
            this.content = y16.content;
        }
        if (y16.selectedIndex !== undefined) {
            this.selectedIndex = y16.selectedIndex;
        }
        if (y16.confirm !== undefined) {
            this.confirm = y16.confirm;
        }
        if (y16.radioContent !== undefined) {
            this.radioContent = y16.radioContent;
        }
        if (y16.buttons !== undefined) {
            this.buttons = y16.buttons;
        }
        if (y16.contentPadding !== undefined) {
            this.contentPadding = y16.contentPadding;
        }
        if (y16.contentBuilder !== undefined) {
            this.contentBuilder = y16.contentBuilder;
        }
        if (y16.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = y16.fontColorWithTheme;
        }
        if (y16.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = y16.dividerColorWithTheme;
        }
        if (y16.theme !== undefined) {
            this.theme = y16.theme;
        }
        if (y16.controller !== undefined) {
            this.controller = y16.controller;
        }
        if (y16.contentScroller !== undefined) {
            this.contentScroller = y16.contentScroller;
        }
    }

    updateStateVars(x16) {
    }

    purgeVariableDependenciesOnElmtId(w16) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(w16);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(w16);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__dividerColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(v16) {
        this.__fontColorWithTheme.set(v16);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(u16) {
        this.__dividerColorWithTheme.set(u16);
    }

    setController(t16) {
        this.controller = t16;
    }

    buildContent(e14 = null) {
        this.observeComponentCreation2((r16, s16) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
        }, Scroll);
        this.observeComponentCreation2((p16, q16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((f16, g16) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n16, o16) => {
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
                    this.observeComponentCreation2((l16, m16) => {
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
        this.observeComponentCreation2((c16, d16) => {
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
        this.observeComponentCreation2((k14, l14) => {
            ForEach.create();
            const m14 = (o14, p14) => {
                const q14 = o14;
                {
                    const r14 = (a16, b16) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a16);
                        s14(a16, b16);
                        if (!b16) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const s14 = (y15, z15) => {
                        ListItem.create(t14, true);
                    };
                    const t14 = (x14, y14) => {
                        r14(x14, y14);
                        this.observeComponentCreation2((w15, x15) => {
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
                        this.observeComponentCreation2((t15, u15) => {
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
                                q14.action && q14.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((r15, s15) => {
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
                        this.observeComponentCreation2((p15, q15) => {
                            Text.create(q14.title);
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
                        this.observeComponentCreation2((m15, n15) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === p14);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(p14));
                            Radio.onFocus(() => {
                                if (p14 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (p14 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((f15, g15) => {
                            If.create();
                            if (p14 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((k15, l15) => {
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
                    this.observeComponentCreation2(s14, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(k14, this.radioContent, m14, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        {
            this.observeComponentCreation2((y13, z13) => {
                if (z13) {
                    let a14 = new CustomDialogComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        contentAreaPadding: this.contentPadding,
                        theme: this.theme,
                    }, undefined, y13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 384, col: 5 });
                    ViewPU.create(a14);
                    let b14 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.title,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            contentAreaPadding: this.contentPadding,
                            theme: this.theme
                        };
                    };
                    a14.paramsGenerator_ = b14;
                } else {
                    this.updateStateVarsOfChildByElmtId(y13, {});
                }
            }, { name: 'CustomDialogComponent' });
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
    constructor(r13, s13, t13, u13 = -1, v13 = undefined, w13) {
        super(r13, t13, u13, w13);
        if (typeof v13 === 'function') {
            this.paramsGenerator_ = v13;
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
        this.setInitiallyProvidedValue(s13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q13) {
        if (q13.controller !== undefined) {
            this.controller = q13.controller;
        }
        if (q13.title !== undefined) {
            this.title = q13.title;
        }
        if (q13.content !== undefined) {
            this.content = q13.content;
        }
        if (q13.checkTips !== undefined) {
            this.checkTips = q13.checkTips;
        }
        if (q13.isChecked !== undefined) {
            this.isChecked = q13.isChecked;
        }
        if (q13.primaryButton !== undefined) {
            this.primaryButton = q13.primaryButton;
        }
        if (q13.secondaryButton !== undefined) {
            this.secondaryButton = q13.secondaryButton;
        }
        if (q13.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = q13.fontColorWithTheme;
        }
        if (q13.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = q13.buttonFontColorWithTheme;
        }
        if (q13.theme !== undefined) {
            this.theme = q13.theme;
        }
    }

    updateStateVars(p13) {
    }

    purgeVariableDependenciesOnElmtId(o13) {
        this.__isChecked.purgeDependencyOnElmtId(o13);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(o13);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(o13);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__buttonFontColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(n13) {
        this.controller = n13;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(m13) {
        this.__isChecked.set(m13);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(l13) {
        this.__fontColorWithTheme.set(l13);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(k13) {
        this.__buttonFontColorWithTheme.set(k13);
    }

    initialRender() {
        this.observeComponentCreation2((i13, j13) => {
            Column.create();
            Column.backgroundBlurStyle(BlurStyle.Thick);
            Column.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_dialog'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Column.margin({
                start: LengthMetrics.vp(getNumberByResource('sys.float.ohos_id_dialog_margin_start')),
                end: LengthMetrics.vp(getNumberByResource('sys.float.ohos_id_dialog_margin_end')),
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_bottom'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Column.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_dialog_bg'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Column);
        this.observeComponentCreation2((g13, h13) => {
            Row.create();
            Row.padding({ start: LengthMetrics.vp(24), end: LengthMetrics.vp(24), top: 24 });
            Row.constraintSize({ minHeight: 56 });
        }, Row);
        this.observeComponentCreation2((e13, f13) => {
            Text.create(this.title);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_dialog_tittle'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight(FontWeight.Medium);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.minFontSize(15);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(TextAlign.Start);
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((u12, v12) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c13, d13) => {
                        Row.create();
                        Row.padding({
                            start: LengthMetrics.vp(24),
                            end: LengthMetrics.vp(24),
                            top: 8,
                            bottom: 8
                        });
                        Row.width('100%');
                        Row.constraintSize({ minHeight: 36 });
                    }, Row);
                    this.observeComponentCreation2((a13, b13) => {
                        Text.create(this.content);
                        Text.focusable(true);
                        Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body1'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                        Text.maxLines(CONTENT_MAX_LINES);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.minFontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
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
        this.observeComponentCreation2((s12, t12) => {
            Row.create();
            Row.height(CHECKBOX_CONTAINER_HEIGHT);
            Row.width('100%');
            Row.padding({
                start: LengthMetrics.vp(24),
                end: LengthMetrics.vp(24),
                top: 8,
                bottom: 8
            });
        }, Row);
        this.observeComponentCreation2((q12, r12) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((m12, n12) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((p12) => {
                this.isChecked = p12;
            });
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        WithTheme.pop();
        this.observeComponentCreation2((j12, k12) => {
            Text.create(this.checkTips);
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.maxLines(CONTENT_MAX_LINES);
            Text.layoutWeight(1);
            Text.focusable(false);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.onClick(() => {
                this.isChecked = !this.isChecked;
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((h12, i12) => {
            Row.create();
            Row.width('100%');
            Row.padding({
                start: LengthMetrics.vp(16),
                end: LengthMetrics.vp(16),
                top: 16,
                bottom: 16
            });
        }, Row);
        this.observeComponentCreation2((z11, a12) => {
            If.create();
            if (this.primaryButton?.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e12, f12) => {
                        Button.createWithLabel(this.primaryButton.value);
                        Button.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button1'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.fontWeight(FontWeight.Medium);
                        Button.layoutWeight(1);
                        Button.defaultFocus(true);
                        Button.backgroundColor(this.primaryButton.background ? this.primaryButton.background : {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor :
                        this.buttonFontColorWithTheme);
                        Button.onClick(() => {
                            if (this.primaryButton?.action) {
                                this.primaryButton.action();
                            }
                            this.controller.close();
                        });
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((k11, l11) => {
            If.create();
            if (this.secondaryButton?.value && this.primaryButton?.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x11, y11) => {
                        Column.create();
                        Column.width(DIVIDER_CONTAINER_WIDTH);
                        Column.alignItems(HorizontalAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((q11, r11) => {
                        If.create();
                        if (!this.secondaryButton.background) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v11, w11) => {
                                    Divider.create();
                                    Divider.width(DIVIDER_WIDTH);
                                    Divider.height(DIVIDER_HEIGHT);
                                    Divider.color({
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_list_separator'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    Divider.vertical(true);
                                }, Divider);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((c11, d11) => {
            If.create();
            if (this.secondaryButton?.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h11, i11) => {
                        Button.createWithLabel(this.secondaryButton.value);
                        Button.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_button1'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.fontWeight(FontWeight.Medium);
                        Button.layoutWeight(1);
                        Button.defaultFocus(true);
                        Button.backgroundColor(this.secondaryButton.background ? this.secondaryButton.background : {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Button.fontColor(this.secondaryButton.fontColor ?
                        this.secondaryButton.fontColor : this.buttonFontColorWithTheme);
                        Button.onClick(() => {
                            if (this.secondaryButton?.action) {
                                this.secondaryButton.action();
                            }
                            this.controller.close();
                        });
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
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
        this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
        this.theme.colors.fontEmphasize : {
                'id': -1,
                'type': 10001,
                params: ['sys.color.font_emphasize'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class AlertDialog extends ViewPU {
    constructor(k10, l10, m10, n10 = -1, o10 = undefined, p10) {
        super(k10, m10, n10, p10);
        if (typeof o10 === 'function') {
            this.paramsGenerator_ = o10;
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
        this.setInitiallyProvidedValue(l10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j10) {
        if (j10.controller !== undefined) {
            this.controller = j10.controller;
        }
        if (j10.primaryTitle !== undefined) {
            this.primaryTitle = j10.primaryTitle;
        }
        if (j10.secondaryTitle !== undefined) {
            this.secondaryTitle = j10.secondaryTitle;
        }
        if (j10.content !== undefined) {
            this.content = j10.content;
        }
        if (j10.primaryButton !== undefined) {
            this.primaryButton = j10.primaryButton;
        }
        if (j10.secondaryButton !== undefined) {
            this.secondaryButton = j10.secondaryButton;
        }
        if (j10.buttons !== undefined) {
            this.buttons = j10.buttons;
        }
        if (j10.textAlign !== undefined) {
            this.textAlign = j10.textAlign;
        }
        if (j10.contentScroller !== undefined) {
            this.contentScroller = j10.contentScroller;
        }
        if (j10.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = j10.fontColorWithTheme;
        }
        if (j10.theme !== undefined) {
            this.theme = j10.theme;
        }
    }

    updateStateVars(i10) {
    }

    purgeVariableDependenciesOnElmtId(h10) {
        this.__textAlign.purgeDependencyOnElmtId(h10);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(h10);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(g10) {
        this.controller = g10;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(f10) {
        this.__textAlign.set(f10);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(e10) {
        this.__fontColorWithTheme.set(e10);
    }

    initialRender() {
        {
            this.observeComponentCreation2((y9, z9) => {
                if (z9) {
                    let a10 = new CustomDialogComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.AlertDialogContentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, y9, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 584, col: 5 });
                    ViewPU.create(a10);
                    let b10 = () => {
                        return {
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.AlertDialogContentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme
                        };
                    };
                    a10.paramsGenerator_ = b10;
                } else {
                    this.updateStateVarsOfChildByElmtId(y9, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
    }

    AlertDialogContentBuilder(i9 = null) {
        this.observeComponentCreation2((v9, w9) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((t9, u9) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((m9, n9) => {
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
            Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
            Text.textAlign(this.textAlign);
            Text.onAreaChange((r9, s9) => {
                this.getTextAlign(Number(s9.width));
            });
            Text.onKeyEvent((q9) => {
                if (q9) {
                    resolveKeyEvent(q9, this.contentScroller);
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

    getTextAlign(f9) {
        let g9 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            constraintWidth: f9,
        });
        let h9 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        });
        if (this.getTextHeight(g9) <= this.getTextHeight(h9)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(e9) {
        if (e9 && e9.height !== null && e9.height !== undefined) {
            return Number(e9.height);
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
    constructor(y8, z8, a9, b9 = -1, c9 = undefined, d9) {
        super(y8, a9, b9, d9);
        if (typeof c9 === 'function') {
            this.paramsGenerator_ = c9;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.setInitiallyProvidedValue(z8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x8) {
        if (x8.controller !== undefined) {
            this.controller = x8.controller;
        }
        if (x8.primaryTitle !== undefined) {
            this.primaryTitle = x8.primaryTitle;
        }
        if (x8.secondaryTitle !== undefined) {
            this.secondaryTitle = x8.secondaryTitle;
        }
        if (x8.contentBuilder !== undefined) {
            this.contentBuilder = x8.contentBuilder;
        }
        if (x8.contentAreaPadding !== undefined) {
            this.contentAreaPadding = x8.contentAreaPadding;
        }
        if (x8.buttons !== undefined) {
            this.buttons = x8.buttons;
        }
        if (x8.theme !== undefined) {
            this.theme = x8.theme;
        }
    }

    updateStateVars(w8) {
    }

    purgeVariableDependenciesOnElmtId(v8) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(u8) {
        this.controller = u8;
    }

    initialRender() {
        {
            this.observeComponentCreation2((o8, p8) => {
                if (p8) {
                    let q8 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, o8, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 688, col: 5 });
                    ViewPU.create(q8);
                    let r8 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            contentAreaPadding: this.contentAreaPadding,
                            buttons: this.buttons,
                            theme: this.theme
                        };
                    };
                    q8.paramsGenerator_ = r8;
                } else {
                    this.updateStateVarsOfChildByElmtId(o8, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(h8, i8, j8, k8 = -1, l8 = undefined, m8) {
        super(h8, j8, k8, m8);
        if (typeof l8 === 'function') {
            this.paramsGenerator_ = l8;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = this.defaultContentBuilder;
        this.buttons = undefined;
        this.contentAreaPadding = undefined;
        this.keyIndex = 0;
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
        this.__buttonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'buttonFontColorWithTheme');
        this.__errorButtonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'errorButtonFontColorWithTheme');
        this.theme = new CustomThemeImpl({});
        this.titleHeight = 0;
        this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
        this.setInitiallyProvidedValue(i8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g8) {
        if (g8.controller !== undefined) {
            this.controller = g8.controller;
        }
        if (g8.primaryTitle !== undefined) {
            this.primaryTitle = g8.primaryTitle;
        }
        if (g8.secondaryTitle !== undefined) {
            this.secondaryTitle = g8.secondaryTitle;
        }
        if (g8.contentBuilder !== undefined) {
            this.contentBuilder = g8.contentBuilder;
        }
        if (g8.buttons !== undefined) {
            this.buttons = g8.buttons;
        }
        if (g8.contentAreaPadding !== undefined) {
            this.contentAreaPadding = g8.contentAreaPadding;
        }
        if (g8.keyIndex !== undefined) {
            this.keyIndex = g8.keyIndex;
        }
        if (g8.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = g8.primaryTitleFontColorWithTheme;
        }
        if (g8.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = g8.secondaryTitleFontColorWithTheme;
        }
        if (g8.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = g8.buttonFontColorWithTheme;
        }
        if (g8.errorButtonFontColorWithTheme !== undefined) {
            this.errorButtonFontColorWithTheme = g8.errorButtonFontColorWithTheme;
        }
        if (g8.theme !== undefined) {
            this.theme = g8.theme;
        }
        if (g8.titleHeight !== undefined) {
            this.titleHeight = g8.titleHeight;
        }
        if (g8.contentMaxHeight !== undefined) {
            this.contentMaxHeight = g8.contentMaxHeight;
        }
    }

    updateStateVars(f8) {
    }

    purgeVariableDependenciesOnElmtId(e8) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(e8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(e8);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(e8);
        this.__errorButtonFontColorWithTheme.purgeDependencyOnElmtId(e8);
        this.__contentMaxHeight.purgeDependencyOnElmtId(e8);
    }

    aboutToBeDeleted() {
        this.__primaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__secondaryTitleFontColorWithTheme.aboutToBeDeleted();
        this.__buttonFontColorWithTheme.aboutToBeDeleted();
        this.__errorButtonFontColorWithTheme.aboutToBeDeleted();
        this.__contentMaxHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }

    set primaryTitleFontColorWithTheme(d8) {
        this.__primaryTitleFontColorWithTheme.set(d8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(c8) {
        this.__secondaryTitleFontColorWithTheme.set(c8);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(b8) {
        this.__buttonFontColorWithTheme.set(b8);
    }

    get errorButtonFontColorWithTheme() {
        return this.__errorButtonFontColorWithTheme.get();
    }

    set errorButtonFontColorWithTheme(a8) {
        this.__errorButtonFontColorWithTheme.set(a8);
    }

    defaultContentBuilder(z7 = null) {
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(y7) {
        this.__contentMaxHeight.set(y7);
    }

    initialRender() {
        this.observeComponentCreation2((w7, x7) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((u7, v7) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.buildTitles.bind(this)(this);
        this.observeComponentCreation2((s7, t7) => {
            Column.create();
            Column.padding(this.getContentPadding());
            Column.constraintSize({ maxHeight: this.contentMaxHeight });
        }, Column);
        this.contentBuilder.bind(this)(this);
        Column.pop();
        this.buildButtons.bind(this)(this);
        Column.pop();
        WithTheme.pop();
    }

    buildTitles(l6 = null) {
        this.observeComponentCreation2((k7, l7) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
            Column.onAreaChange((n7, o7) => {
                this.titleHeight = Number(o7.height);
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
            });
        }, Column);
        this.observeComponentCreation2((i7, j7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((g7, h7) => {
            Text.create(this.primaryTitle);
            Text.fontWeight(FontWeight.Bold);
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTitleFontColorWithTheme));
            Text.textAlign(this.getTitleTextAlign());
            Text.maxFontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Title_S'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((w6, x6) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e7, f7) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((c7, d7) => {
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
        this.observeComponentCreation2((u6, v6) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((s6, t6) => {
            Text.create(this.secondaryTitle);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTitleFontColorWithTheme));
            Text.textAlign(this.getTitleTextAlign());
            Text.maxFontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Subtitle_S'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_S'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
        }, Text);
        Text.pop();
        Row.pop();
        Column.pop();
    }

    buildButtons(h6 = null) {
        this.observeComponentCreation2((j6, k6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.buildHorizontalAlignButtons.bind(this)(h6 ? h6 : this);
        this.buildVerticalAlignButtons.bind(this)(h6 ? h6 : this);
        Column.pop();
    }

    buildSingleButton(i5, j5 = null) {
        this.observeComponentCreation2((l5, m5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(i5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f6, g6) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.controller);
                        Button.role(i5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (i5.background !== undefined && i5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b6, c6) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.controller);
                        Button.backgroundColor(i5.background);
                        Button.fontColor(i5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (i5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((x5, y5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.controller);
                        Button.backgroundColor(i5.background);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (i5.background !== undefined && i5.fontColor === undefined || '') {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((t5, u5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.controller);
                        Button.backgroundColor(i5.background);
                        Button.fontColor(i5.role === ButtonRole.ERROR ?
                        this.errorButtonFontColorWithTheme : this.buttonFontColorWithTheme);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.observeComponentCreation2((p5, q5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.controller);
                        Button.fontColor(i5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
    }

    buildHorizontalAlignButtons(r4 = null) {
        this.observeComponentCreation2((t4, u4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g5, h5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], r4 ? r4 : this);
                    this.observeComponentCreation2((z4, a5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e5, f5) => {
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
                                    r4 ? r4 : this);
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

    buildVerticalAlignButtons(y3 = null) {
        this.observeComponentCreation2((a4, b4) => {
            If.create();
            if (this.buttons && this.isVerticalAlignButton()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p4, q4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((g4, h4) => {
                        ForEach.create();
                        const i4 = (m4, n4) => {
                            const o4 = m4;
                            this.buildButtonWithDivider.bind(this)(n4, y3 ? y3 : this);
                        };
                        this.forEachUpdateFunction(g4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), i4,
                            (l4) => l4.value.toString(), true, false);
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

    aboutToAppear() {
        if (this.primaryTitle) {
            this.titleHeight = getNumberByResource('alert_title_primary_height');
        }
        if (this.secondaryTitle) {
            this.titleHeight = getNumberByResource('alert_title_secondary_height');
        }
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
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
        this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
        this.theme.colors.fontEmphasize : '';
        this.errorButtonFontColorWithTheme = this.theme?.colors?.warning ?
        this.theme.colors.warning : '';
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

    getButtonsHeight() {
        if (!this.buttons || this.buttons.length === 0) {
            return 0;
        }
        let f3 = getNumberByResource('alert_button_top_padding');
        if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
            f3 += BUTTON_DEFAULT_HEIGHT +
            getNumberByResource('alert_button_bottom_padding_horizontal');
        } else {
            f3 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
                (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
            getNumberByResource('alert_button_bottom_padding_vertical');
        }
        return f3;
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

    isVerticalAlignButton() {
        if (this.buttons) {
            return this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
        }
        return false;
    }

    getOperationAreaPadding() {
        if (this.isVerticalAlignButton()) {
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

    isNewPropertiesHighPriority(e3) {
        if (e3.role === ButtonRole.ERROR) {
            return true;
        }
        if (e3.buttonStyle !== undefined &&
            e3.buttonStyle !== getNumberByResource('alert_button_style')) {
            return true;
        }
        if (e3.background === undefined && e3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    getTitleTextAlign() {
        let d3 = getEnumNumberByResource('alert_title_alignment');
        if (d3 === TextAlign.Start) {
            return TextAlign.Start;
        } else if (d3 === TextAlign.Center) {
            return TextAlign.Center;
        } else if (d3 === TextAlign.End) {
            return TextAlign.End;
        } else if (d3 === TextAlign.JUSTIFY) {
            return TextAlign.JUSTIFY;
        } else {
            return TextAlign.Center;
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class CustomDialogComponent extends ViewPU {
    constructor(x2, y2, z2, a3 = -1, b3 = undefined, c3) {
        super(x2, z2, a3, c3);
        if (typeof b3 === 'function') {
            this.paramsGenerator_ = b3;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.buttons = undefined;
        this.contentAreaPadding = undefined;
        this.screenWidth = 0;
        this.__columnModifier = new ObservedPropertyObjectPU(new ColumnModifier(), this, 'columnModifier');
        this.isFirstInit = true;
        this.theme = new CustomThemeImpl({});
        this.targetSdk = VERSION_TWELVE;
        this.dialogWidth = 0;
        this.setInitiallyProvidedValue(y2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w2) {
        if (w2.controller !== undefined) {
            this.controller = w2.controller;
        }
        if (w2.primaryTitle !== undefined) {
            this.primaryTitle = w2.primaryTitle;
        }
        if (w2.secondaryTitle !== undefined) {
            this.secondaryTitle = w2.secondaryTitle;
        }
        if (w2.contentBuilder !== undefined) {
            this.contentBuilder = w2.contentBuilder;
        }
        if (w2.buttons !== undefined) {
            this.buttons = w2.buttons;
        }
        if (w2.contentAreaPadding !== undefined) {
            this.contentAreaPadding = w2.contentAreaPadding;
        }
        if (w2.screenWidth !== undefined) {
            this.screenWidth = w2.screenWidth;
        }
        if (w2.columnModifier !== undefined) {
            this.columnModifier = w2.columnModifier;
        }
        if (w2.isFirstInit !== undefined) {
            this.isFirstInit = w2.isFirstInit;
        }
        if (w2.theme !== undefined) {
            this.theme = w2.theme;
        }
        if (w2.targetSdk !== undefined) {
            this.targetSdk = w2.targetSdk;
        }
        if (w2.dialogWidth !== undefined) {
            this.dialogWidth = w2.dialogWidth;
        }
    }

    updateStateVars(v2) {
    }

    purgeVariableDependenciesOnElmtId(u2) {
        this.__columnModifier.purgeDependencyOnElmtId(u2);
    }

    aboutToBeDeleted() {
        this.__columnModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get columnModifier() {
        return this.__columnModifier.get();
    }

    set columnModifier(t2) {
        this.__columnModifier.set(t2);
    }

    initialRender() {
        this.observeComponentCreation2((o2, p2) => {
            Column.create();
            Column.onAreaChange((r2, s2) => {
                if (!this.isFirstInit) {
                    return;
                }
                this.dialogWidth = s2.width;
                this.updateCustomStyle();
                this.isFirstInit = false;
            });
        }, Column);
        this.observeComponentCreation2((m2, n2) => {
            Column.create();
            Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.columnModifier));
        }, Column);
        {
            this.observeComponentCreation2((g2, h2) => {
                if (h2) {
                    let i2 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        contentAreaPadding: this.contentAreaPadding,
                        theme: this.theme,
                    }, undefined, g2, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1114, col: 9 });
                    ViewPU.create(i2);
                    let j2 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            contentAreaPadding: this.contentAreaPadding,
                            theme: this.theme
                        };
                    };
                    i2.paramsGenerator_ = j2;
                } else {
                    this.updateStateVarsOfChildByElmtId(g2, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        Column.pop();
        Column.pop();
    }

    updateCustomStyle() {
        if (this.targetSdk >= VERSION_TWELVE) {
            return;
        }
        if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
            this.columnModifier.customStyle = this.dialogWidth > getNumberByResource('alert_container_max_width');
        } else {
            this.columnModifier.customStyle = this.dialogWidth >= this.screenWidth;
        }
    }

    aboutToAppear() {
        try {
            this.screenWidth = px2vp(display.getDefaultDisplaySync().width);
            let y1 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            bundleManager.getBundleInfoForSelf(y1).then((c2) => {
                this.targetSdk = c2.targetVersion;
                this.updateCustomStyle();
            }).catch((b2) => {
                hilog.error(0x3900, 'Ace', 'getBundleInfoForSelf failed Cause: %{public}s', b2.message);
            });
        } catch (x1) {
            hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(x1)}`);
        }
        ;
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class ColumnModifier {
    constructor() {
        this.customStyle = false;
    }

    applyNormalAttribute(w1) {
        if (!this.customStyle) {
            return;
        }
        w1.backgroundBlurStyle(BlurStyle.Thick);
        w1.borderRadius({
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_dialog'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
        w1.margin({
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
        });
        w1.backgroundColor({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_dialog_bg'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
    }
}

function __Button__setButtonProperties(t1, u1) {
    Button.onClick(() => {
        if (t1.action) {
            t1.action();
        }
        u1?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(t1.buttonStyle ?? getNumberByResource('alert_button_style'));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}

function getNumberByResource(p1) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(p1);
    } catch (q1) {
        let r1 = q1.code;
        let s1 = q1.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${r1}, message: ${s1}`);
        return 0;
    }
}

function getEnumNumberByResource(l1) {
    try {
        return getContext().resourceManager.getNumberByName(l1);
    } catch (m1) {
        let n1 = m1.code;
        let o1 = m1.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${n1}, message: ${o1}`);
        return -1;
    }
}

function resolveKeyEvent(j1, k1) {
    if (j1.type == IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (j1.keyCode == KEYCODE_UP) {
        k1.scrollPage({ next: false });
        j1.stopPropagation();
    } else if (j1.keyCode == KEYCODE_DOWN) {
        if (k1.isAtEnd()) {
            return;
        } else {
            k1.scrollPage({ next: true });
            j1.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(d1, e1, f1, g1 = -1, h1 = undefined, i1) {
        super(d1, f1, g1, i1);
        if (typeof h1 === 'function') {
            this.paramsGenerator_ = h1;
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
        this.setInitiallyProvidedValue(e1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c1) {
        if (c1.controller !== undefined) {
            this.controller = c1.controller;
        }
        if (c1.content !== undefined) {
            this.content = c1.content;
        }
        if (c1.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = c1.fontColorWithTheme;
        }
        if (c1.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = c1.loadingProgressIconColorWithTheme;
        }
        if (c1.theme !== undefined) {
            this.theme = c1.theme;
        }
    }

    updateStateVars(b1) {
    }

    purgeVariableDependenciesOnElmtId(a1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(a1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(a1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(z) {
        this.controller = z;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(y) {
        this.__fontColorWithTheme.set(y);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(x) {
        this.__loadingProgressIconColorWithTheme.set(x);
    }

    initialRender() {
        this.observeComponentCreation2((v, w) => {
            Column.create();
        }, Column);
        {
            this.observeComponentCreation2((p, q) => {
                if (q) {
                    let r = new CustomDialogComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                    }, undefined, p, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1266, col: 7 });
                    ViewPU.create(r);
                    let s = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            theme: this.theme
                        };
                    };
                    r.paramsGenerator_ = s;
                } else {
                    this.updateStateVarsOfChildByElmtId(p, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
        Column.pop();
    }

    contentBuilder(a = null) {
        this.observeComponentCreation2((l, m) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((j, k) => {
            Row.create();
            Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
        }, Row);
        this.observeComponentCreation2((h, i) => {
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
            Text.maxLines(LOADING_MAX_LINES);
            Text.focusable(true);
            Text.defaultFocus(true);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((f, g) => {
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

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog };
