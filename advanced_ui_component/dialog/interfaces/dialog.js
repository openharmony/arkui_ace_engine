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
        if (e21.onCheckedChange !== undefined) {
            this.onCheckedChange = e21.onCheckedChange;
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
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 86, col: 5 });
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
                if (this.onCheckedChange) {
                    this.onCheckedChange(r19);
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
                }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 293, col: 14 });
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
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 388, col: 5 });
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
    constructor(n13, o13, p13, q13 = -1, r13 = undefined, s13) {
        super(n13, p13, q13, s13);
        if (typeof r13 === 'function') {
            this.paramsGenerator_ = r13;
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
        this.__maxContentHeight =
            new ObservedPropertySimplePU(`calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`,
                this, 'maxContentHeight');
        this.updateTitleHeight = (w13) => {
            this.titleHeight = w13;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (v13) => {
            this.buttonHeight = v13;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(o13);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m13) {
        if (m13.controller !== undefined) {
            this.controller = m13.controller;
        }
        if (m13.title !== undefined) {
            this.title = m13.title;
        }
        if (m13.content !== undefined) {
            this.content = m13.content;
        }
        if (m13.checkTips !== undefined) {
            this.checkTips = m13.checkTips;
        }
        if (m13.isChecked !== undefined) {
            this.isChecked = m13.isChecked;
        }
        if (m13.primaryButton !== undefined) {
            this.primaryButton = m13.primaryButton;
        }
        if (m13.secondaryButton !== undefined) {
            this.secondaryButton = m13.secondaryButton;
        }
        if (m13.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = m13.fontColorWithTheme;
        }
        if (m13.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = m13.buttonFontColorWithTheme;
        }
        if (m13.theme !== undefined) {
            this.theme = m13.theme;
        }
        if (m13.onCheckedChange !== undefined) {
            this.onCheckedChange = m13.onCheckedChange;
        }
        if (m13.contentScroller !== undefined) {
            this.contentScroller = m13.contentScroller;
        }
        if (m13.buttons !== undefined) {
            this.buttons = m13.buttons;
        }
        if (m13.marginOffset !== undefined) {
            this.marginOffset = m13.marginOffset;
        }
        if (m13.titleHeight !== undefined) {
            this.titleHeight = m13.titleHeight;
        }
        if (m13.buttonHeight !== undefined) {
            this.buttonHeight = m13.buttonHeight;
        }
        if (m13.checkBoxHeight !== undefined) {
            this.checkBoxHeight = m13.checkBoxHeight;
        }
        if (m13.maxContentHeight !== undefined) {
            this.maxContentHeight = m13.maxContentHeight;
        }
        if (m13.updateTitleHeight !== undefined) {
            this.updateTitleHeight = m13.updateTitleHeight;
        }
        if (m13.updateButtonHeight !== undefined) {
            this.updateButtonHeight = m13.updateButtonHeight;
        }
    }

    updateStateVars(l13) {
    }

    purgeVariableDependenciesOnElmtId(k13) {
        this.__isChecked.purgeDependencyOnElmtId(k13);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(k13);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(k13);
        this.__titleHeight.purgeDependencyOnElmtId(k13);
        this.__buttonHeight.purgeDependencyOnElmtId(k13);
        this.__checkBoxHeight.purgeDependencyOnElmtId(k13);
        this.__maxContentHeight.purgeDependencyOnElmtId(k13);
    }

    aboutToBeDeleted() {
        this.__isChecked.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__buttonFontColorWithTheme.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__checkBoxHeight.aboutToBeDeleted();
        this.__maxContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(j13) {
        this.controller = j13;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(i13) {
        this.__isChecked.set(i13);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(h13) {
        this.__fontColorWithTheme.set(h13);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(g13) {
        this.__buttonFontColorWithTheme.set(g13);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(f13) {
        this.__titleHeight.set(f13);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(e13) {
        this.__buttonHeight.set(e13);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(d13) {
        this.__checkBoxHeight.set(d13);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(c13) {
        this.__maxContentHeight.set(c13);
    }

    buildContent(q11 = null) {
        this.observeComponentCreation2((a13, b13) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((l12, m12) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y12, z12) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((w12, x12) => {
                        Scroll.create(this.contentScroller);
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((s12, t12) => {
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
                        Text.onKeyEvent((v12) => {
                            if (v12) {
                                resolveKeyEvent(v12, this.contentScroller);
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
        this.observeComponentCreation2((g12, h12) => {
            Row.create();
            Row.onSizeChange((j12, k12) => {
                this.checkBoxHeight = Number(k12.height);
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((e12, f12) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((a12, b12) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((d12) => {
                this.isChecked = d12;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        WithTheme.pop();
        this.observeComponentCreation2((x11, y11) => {
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

    initialRender() {
        {
            this.observeComponentCreation2((k11, l11) => {
                if (l11) {
                    let m11 = new CustomDialogComponent(this, {
                        primaryTitle: this.title,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.buildContent();
                        },
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, k11, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 538, col: 5 });
                    ViewPU.create(m11);
                    let n11 = () => {
                        return {
                            primaryTitle: this.title,
                            controller: this.controller,
                            contentBuilder: () => {
                                this.buildContent();
                            },
                            updateTitleHeight: this.updateTitleHeight,
                            updateButtonHeight: this.updateButtonHeight,
                            buttons: this.buttons,
                            theme: this.theme
                        };
                    };
                    m11.paramsGenerator_ = n11;
                } else {
                    this.updateStateVarsOfChildByElmtId(k11, {});
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
    constructor(d11, e11, f11, g11 = -1, h11 = undefined, i11) {
        super(d11, f11, g11, i11);
        if (typeof h11 === 'function') {
            this.paramsGenerator_ = h11;
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
        this.setInitiallyProvidedValue(e11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c11) {
        if (c11.controller !== undefined) {
            this.controller = c11.controller;
        }
        if (c11.primaryTitle !== undefined) {
            this.primaryTitle = c11.primaryTitle;
        }
        if (c11.secondaryTitle !== undefined) {
            this.secondaryTitle = c11.secondaryTitle;
        }
        if (c11.content !== undefined) {
            this.content = c11.content;
        }
        if (c11.primaryButton !== undefined) {
            this.primaryButton = c11.primaryButton;
        }
        if (c11.secondaryButton !== undefined) {
            this.secondaryButton = c11.secondaryButton;
        }
        if (c11.buttons !== undefined) {
            this.buttons = c11.buttons;
        }
        if (c11.textAlign !== undefined) {
            this.textAlign = c11.textAlign;
        }
        if (c11.contentScroller !== undefined) {
            this.contentScroller = c11.contentScroller;
        }
        if (c11.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = c11.fontColorWithTheme;
        }
        if (c11.theme !== undefined) {
            this.theme = c11.theme;
        }
    }

    updateStateVars(b11) {
    }

    purgeVariableDependenciesOnElmtId(a11) {
        this.__textAlign.purgeDependencyOnElmtId(a11);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(a11);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(z10) {
        this.controller = z10;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(y10) {
        this.__textAlign.set(y10);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(x10) {
        this.__fontColorWithTheme.set(x10);
    }

    initialRender() {
        {
            this.observeComponentCreation2((r10, s10) => {
                if (s10) {
                    let t10 = new CustomDialogComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.AlertDialogContentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, r10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 594, col: 5 });
                    ViewPU.create(t10);
                    let u10 = () => {
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
                    t10.paramsGenerator_ = u10;
                } else {
                    this.updateStateVarsOfChildByElmtId(r10, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
    }

    AlertDialogContentBuilder(b10 = null) {
        this.observeComponentCreation2((o10, p10) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((m10, n10) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((f10, g10) => {
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
            Text.onAreaChange((k10, l10) => {
                this.getTextAlign(Number(l10.width));
            });
            Text.onKeyEvent((j10) => {
                if (j10) {
                    resolveKeyEvent(j10, this.contentScroller);
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

    getTextAlign(y9) {
        let z9 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            constraintWidth: y9,
        });
        let a10 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        });
        if (this.getTextHeight(z9) <= this.getTextHeight(a10)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(x9) {
        if (x9 && x9.height !== null && x9.height !== undefined) {
            return Number(x9.height);
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
    constructor(r9, s9, t9, u9 = -1, v9 = undefined, w9) {
        super(r9, t9, u9, w9);
        if (typeof v9 === 'function') {
            this.paramsGenerator_ = v9;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.setInitiallyProvidedValue(s9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(q9) {
        if (q9.controller !== undefined) {
            this.controller = q9.controller;
        }
        if (q9.primaryTitle !== undefined) {
            this.primaryTitle = q9.primaryTitle;
        }
        if (q9.secondaryTitle !== undefined) {
            this.secondaryTitle = q9.secondaryTitle;
        }
        if (q9.contentBuilder !== undefined) {
            this.contentBuilder = q9.contentBuilder;
        }
        if (q9.contentAreaPadding !== undefined) {
            this.contentAreaPadding = q9.contentAreaPadding;
        }
        if (q9.buttons !== undefined) {
            this.buttons = q9.buttons;
        }
        if (q9.theme !== undefined) {
            this.theme = q9.theme;
        }
    }

    updateStateVars(p9) {
    }

    purgeVariableDependenciesOnElmtId(o9) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(n9) {
        this.controller = n9;
    }

    initialRender() {
        {
            this.observeComponentCreation2((h9, i9) => {
                if (i9) {
                    let j9 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, h9, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 698, col: 5 });
                    ViewPU.create(j9);
                    let k9 = () => {
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
                    j9.paramsGenerator_ = k9;
                } else {
                    this.updateStateVarsOfChildByElmtId(h9, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(a9, b9, c9, d9 = -1, e9 = undefined, f9) {
        super(a9, c9, d9, f9);
        if (typeof e9 === 'function') {
            this.paramsGenerator_ = e9;
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
        this.buttonHeight = 0;
        this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
        this.setInitiallyProvidedValue(b9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z8) {
        if (z8.controller !== undefined) {
            this.controller = z8.controller;
        }
        if (z8.primaryTitle !== undefined) {
            this.primaryTitle = z8.primaryTitle;
        }
        if (z8.secondaryTitle !== undefined) {
            this.secondaryTitle = z8.secondaryTitle;
        }
        if (z8.contentBuilder !== undefined) {
            this.contentBuilder = z8.contentBuilder;
        }
        if (z8.buttons !== undefined) {
            this.buttons = z8.buttons;
        }
        if (z8.contentAreaPadding !== undefined) {
            this.contentAreaPadding = z8.contentAreaPadding;
        }
        if (z8.keyIndex !== undefined) {
            this.keyIndex = z8.keyIndex;
        }
        if (z8.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = z8.primaryTitleFontColorWithTheme;
        }
        if (z8.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = z8.secondaryTitleFontColorWithTheme;
        }
        if (z8.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = z8.buttonFontColorWithTheme;
        }
        if (z8.errorButtonFontColorWithTheme !== undefined) {
            this.errorButtonFontColorWithTheme = z8.errorButtonFontColorWithTheme;
        }
        if (z8.theme !== undefined) {
            this.theme = z8.theme;
        }
        if (z8.titleHeight !== undefined) {
            this.titleHeight = z8.titleHeight;
        }
        if (z8.buttonHeight !== undefined) {
            this.buttonHeight = z8.buttonHeight;
        }
        if (z8.contentMaxHeight !== undefined) {
            this.contentMaxHeight = z8.contentMaxHeight;
        }
        if (z8.updateTitleHeight !== undefined) {
            this.updateTitleHeight = z8.updateTitleHeight;
        }
        if (z8.updateButtonHeight !== undefined) {
            this.updateButtonHeight = z8.updateButtonHeight;
        }
    }

    updateStateVars(y8) {
    }

    purgeVariableDependenciesOnElmtId(x8) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(x8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(x8);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(x8);
        this.__errorButtonFontColorWithTheme.purgeDependencyOnElmtId(x8);
        this.__contentMaxHeight.purgeDependencyOnElmtId(x8);
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

    set primaryTitleFontColorWithTheme(w8) {
        this.__primaryTitleFontColorWithTheme.set(w8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(v8) {
        this.__secondaryTitleFontColorWithTheme.set(v8);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(u8) {
        this.__buttonFontColorWithTheme.set(u8);
    }

    get errorButtonFontColorWithTheme() {
        return this.__errorButtonFontColorWithTheme.get();
    }

    set errorButtonFontColorWithTheme(t8) {
        this.__errorButtonFontColorWithTheme.set(t8);
    }

    defaultContentBuilder(s8 = null) {
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(r8) {
        this.__contentMaxHeight.set(r8);
    }

    initialRender() {
        this.observeComponentCreation2((p8, q8) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((n8, o8) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.buildTitles.bind(this)(this);
        this.observeComponentCreation2((l8, m8) => {
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

    buildTitles(e7 = null) {
        this.observeComponentCreation2((d8, e8) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
            Column.onAreaChange((g8, h8) => {
                this.titleHeight = Number(h8.height);
                if (this.updateTitleHeight) {
                    this.updateTitleHeight(this.titleHeight);
                }
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
            });
        }, Column);
        this.observeComponentCreation2((b8, c8) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((z7, a8) => {
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
        this.observeComponentCreation2((p7, q7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x7, y7) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((v7, w7) => {
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
        this.observeComponentCreation2((n7, o7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((l7, m7) => {
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

    buildButtons(x6 = null) {
        this.observeComponentCreation2((z6, a7) => {
            Column.create();
            Column.width('100%');
            Column.onSizeChange((c7, d7) => {
                this.buttonHeight = Number(d7.height);
                if (this.updateButtonHeight) {
                    this.updateButtonHeight(this.buttonHeight);
                }
            });
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.buildHorizontalAlignButtons.bind(this)(x6 ? x6 : this);
        this.buildVerticalAlignButtons.bind(this)(x6 ? x6 : this);
        Column.pop();
    }

    buildSingleButton(y5, z5 = null) {
        this.observeComponentCreation2((b6, c6) => {
            If.create();
            if (this.isNewPropertiesHighPriority(y5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v6, w6) => {
                        Button.createWithLabel(y5.value);
                        __Button__setButtonProperties(y5, this.controller);
                        Button.role(y5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (y5.background !== undefined && y5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r6, s6) => {
                        Button.createWithLabel(y5.value);
                        __Button__setButtonProperties(y5, this.controller);
                        Button.backgroundColor(y5.background);
                        Button.fontColor(y5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (y5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((n6, o6) => {
                        Button.createWithLabel(y5.value);
                        __Button__setButtonProperties(y5, this.controller);
                        Button.backgroundColor(y5.background);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else if (y5.background !== undefined && y5.fontColor === undefined || '') {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.observeComponentCreation2((j6, k6) => {
                        Button.createWithLabel(y5.value);
                        __Button__setButtonProperties(y5, this.controller);
                        Button.backgroundColor(y5.background);
                        Button.fontColor(y5.role === ButtonRole.ERROR ?
                        this.errorButtonFontColorWithTheme : this.buttonFontColorWithTheme);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.observeComponentCreation2((f6, g6) => {
                        Button.createWithLabel(y5.value);
                        __Button__setButtonProperties(y5, this.controller);
                        Button.fontColor(y5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                    }, Button);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
    }

    buildHorizontalAlignButtons(h5 = null) {
        this.observeComponentCreation2((j5, k5) => {
            If.create();
            if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0], h5 ? h5 : this);
                    this.observeComponentCreation2((p5, q5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u5, v5) => {
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
                                    h5 ? h5 : this);
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

    buildVerticalAlignButtons(o4 = null) {
        this.observeComponentCreation2((q4, r4) => {
            If.create();
            if (this.buttons && this.isVerticalAlignButton()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f5, g5) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((w4, x4) => {
                        ForEach.create();
                        const y4 = (c5, d5) => {
                            const e5 = c5;
                            this.buildButtonWithDivider.bind(this)(d5, o4 ? o4 : this);
                        };
                        this.forEachUpdateFunction(w4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), y4,
                            (b5) => b5.value.toString(), true, false);
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

    buildButtonWithDivider(w3, x3 = null) {
        this.observeComponentCreation2((z3, a4) => {
            If.create();
            if (this.buttons && this.buttons[w3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m4, n4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[w3], x3 ? x3 : this);
                    Row.pop();
                    this.observeComponentCreation2((f4, g4) => {
                        If.create();
                        if (w3 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k4, l4) => {
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
        if (this.updateButtonHeight) {
            this.updateButtonHeight(this.buttonHeight);
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
        let v3 = getNumberByResource('alert_button_top_padding');
        if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
            v3 += BUTTON_DEFAULT_HEIGHT +
            getNumberByResource('alert_button_bottom_padding_horizontal');
        } else {
            v3 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
                (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
            getNumberByResource('alert_button_bottom_padding_vertical');
        }
        this.buttonHeight = v3;
        return v3;
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

    isNewPropertiesHighPriority(u3) {
        if (u3.role === ButtonRole.ERROR) {
            return true;
        }
        if (u3.buttonStyle !== undefined &&
            u3.buttonStyle !== getNumberByResource('alert_button_style')) {
            return true;
        }
        if (u3.background === undefined && u3.fontColor === undefined) {
            return true;
        }
        return false;
    }

    getTitleTextAlign() {
        let t3 = getEnumNumberByResource('alert_title_alignment');
        if (t3 === TextAlign.Start) {
            return TextAlign.Start;
        } else if (t3 === TextAlign.Center) {
            return TextAlign.Center;
        } else if (t3 === TextAlign.End) {
            return TextAlign.End;
        } else if (t3 === TextAlign.JUSTIFY) {
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
    constructor(n3, o3, p3, q3 = -1, r3 = undefined, s3) {
        super(n3, p3, q3, s3);
        if (typeof r3 === 'function') {
            this.paramsGenerator_ = r3;
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
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
        this.setInitiallyProvidedValue(o3);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m3) {
        if (m3.controller !== undefined) {
            this.controller = m3.controller;
        }
        if (m3.primaryTitle !== undefined) {
            this.primaryTitle = m3.primaryTitle;
        }
        if (m3.secondaryTitle !== undefined) {
            this.secondaryTitle = m3.secondaryTitle;
        }
        if (m3.contentBuilder !== undefined) {
            this.contentBuilder = m3.contentBuilder;
        }
        if (m3.buttons !== undefined) {
            this.buttons = m3.buttons;
        }
        if (m3.contentAreaPadding !== undefined) {
            this.contentAreaPadding = m3.contentAreaPadding;
        }
        if (m3.screenWidth !== undefined) {
            this.screenWidth = m3.screenWidth;
        }
        if (m3.columnModifier !== undefined) {
            this.columnModifier = m3.columnModifier;
        }
        if (m3.isFirstInit !== undefined) {
            this.isFirstInit = m3.isFirstInit;
        }
        if (m3.theme !== undefined) {
            this.theme = m3.theme;
        }
        if (m3.targetSdk !== undefined) {
            this.targetSdk = m3.targetSdk;
        }
        if (m3.dialogWidth !== undefined) {
            this.dialogWidth = m3.dialogWidth;
        }
        if (m3.updateTitleHeight !== undefined) {
            this.updateTitleHeight = m3.updateTitleHeight;
        }
        if (m3.updateButtonHeight !== undefined) {
            this.updateButtonHeight = m3.updateButtonHeight;
        }
    }

    updateStateVars(l3) {
    }

    purgeVariableDependenciesOnElmtId(k3) {
        this.__columnModifier.purgeDependencyOnElmtId(k3);
    }

    aboutToBeDeleted() {
        this.__columnModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get columnModifier() {
        return this.__columnModifier.get();
    }

    set columnModifier(j3) {
        this.__columnModifier.set(j3);
    }

    initialRender() {
        this.observeComponentCreation2((e3, f3) => {
            Column.create();
            Column.onAreaChange((h3, i3) => {
                if (!this.isFirstInit) {
                    return;
                }
                this.dialogWidth = i3.width;
                this.updateCustomStyle();
                this.isFirstInit = false;
            });
        }, Column);
        this.observeComponentCreation2((c3, d3) => {
            Column.create();
            Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.columnModifier));
        }, Column);
        {
            this.observeComponentCreation2((w2, x2) => {
                if (x2) {
                    let y2 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        contentAreaPadding: this.contentAreaPadding,
                        theme: this.theme,
                    }, undefined, w2, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1141, col: 9 });
                    ViewPU.create(y2);
                    let z2 = () => {
                        return {
                            controller: this.controller,
                            primaryTitle: this.primaryTitle,
                            secondaryTitle: this.secondaryTitle,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            updateTitleHeight: this.updateTitleHeight,
                            updateButtonHeight: this.updateButtonHeight,
                            buttons: this.buttons,
                            contentAreaPadding: this.contentAreaPadding,
                            theme: this.theme
                        };
                    };
                    y2.paramsGenerator_ = z2;
                } else {
                    this.updateStateVarsOfChildByElmtId(w2, {});
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
            let o2 = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
            bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
            bundleManager.getBundleInfoForSelf(o2).then((s2) => {
                this.targetSdk = s2.targetVersion;
                this.updateCustomStyle();
            }).catch((r2) => {
                hilog.error(0x3900, 'Ace', 'getBundleInfoForSelf failed Cause: %{public}s', r2.message);
            });
        } catch (n2) {
            hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(n2)}`);
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

    applyNormalAttribute(m2) {
        if (!this.customStyle) {
            return;
        }
        m2.backgroundBlurStyle(BlurStyle.Thick);
        m2.borderRadius({
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_corner_radius_dialog'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
        m2.margin({
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
        m2.backgroundColor({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_dialog_bg'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        });
    }
}

function __Button__setButtonProperties(j2, k2) {
    Button.onClick(() => {
        if (j2.action) {
            j2.action();
        }
        k2?.close();
    });
    Button.defaultFocus(true);
    Button.buttonStyle(j2.buttonStyle ?? getNumberByResource('alert_button_style'));
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}

function getNumberByResource(f2) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(f2);
    } catch (g2) {
        let h2 = g2.code;
        let i2 = g2.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${h2}, message: ${i2}`);
        return 0;
    }
}

function getEnumNumberByResource(b2) {
    try {
        return getContext().resourceManager.getNumberByName(b2);
    } catch (c2) {
        let d2 = c2.code;
        let e2 = c2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${d2}, message: ${e2}`);
        return -1;
    }
}

function resolveKeyEvent(z1, a2) {
    if (z1.type == IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (z1.keyCode == KEYCODE_UP) {
        a2.scrollPage({ next: false });
        z1.stopPropagation();
    } else if (z1.keyCode == KEYCODE_DOWN) {
        if (a2.isAtEnd()) {
            return;
        } else {
            a2.scrollPage({ next: true });
            z1.stopPropagation();
        }
    }
}

export class LoadingDialog extends ViewPU {
    constructor(t1, u1, v1, w1 = -1, x1 = undefined, y1) {
        super(t1, v1, w1, y1);
        if (typeof x1 === 'function') {
            this.paramsGenerator_ = x1;
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
        this.setInitiallyProvidedValue(u1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s1) {
        if (s1.controller !== undefined) {
            this.controller = s1.controller;
        }
        if (s1.content !== undefined) {
            this.content = s1.content;
        }
        if (s1.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = s1.fontColorWithTheme;
        }
        if (s1.loadingProgressIconColorWithTheme !== undefined) {
            this.loadingProgressIconColorWithTheme = s1.loadingProgressIconColorWithTheme;
        }
        if (s1.theme !== undefined) {
            this.theme = s1.theme;
        }
    }

    updateStateVars(r1) {
    }

    purgeVariableDependenciesOnElmtId(q1) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(q1);
        this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(q1);
    }

    aboutToBeDeleted() {
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(p1) {
        this.controller = p1;
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(o1) {
        this.__fontColorWithTheme.set(o1);
    }

    get loadingProgressIconColorWithTheme() {
        return this.__loadingProgressIconColorWithTheme.get();
    }

    set loadingProgressIconColorWithTheme(n1) {
        this.__loadingProgressIconColorWithTheme.set(n1);
    }

    initialRender() {
        this.observeComponentCreation2((l1, m1) => {
            Column.create();
        }, Column);
        {
            this.observeComponentCreation2((f1, g1) => {
                if (g1) {
                    let h1 = new CustomDialogComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        theme: this.theme,
                    }, undefined, f1, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1296, col: 7 });
                    ViewPU.create(h1);
                    let i1 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            theme: this.theme
                        };
                    };
                    h1.paramsGenerator_ = i1;
                } else {
                    this.updateStateVarsOfChildByElmtId(f1, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
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