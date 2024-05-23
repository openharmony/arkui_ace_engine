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
    constructor(v20) {
        this.colors = v20;
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
    constructor(p20, q20, r20, s20 = -1, t20 = undefined, u20) {
        super(p20, r20, s20, u20);
        if (typeof t20 === 'function') {
            this.paramsGenerator_ = t20;
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
        this.setInitiallyProvidedValue(q20);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(o20) {
        if (o20.controller !== undefined) {
            this.controller = o20.controller;
        }
        if (o20.imageRes !== undefined) {
            this.imageRes = o20.imageRes;
        }
        if (o20.imageSize !== undefined) {
            this.imageSize = o20.imageSize;
        }
        if (o20.title !== undefined) {
            this.title = o20.title;
        }
        if (o20.content !== undefined) {
            this.content = o20.content;
        }
        if (o20.checkAction !== undefined) {
            this.checkAction = o20.checkAction;
        }
        if (o20.onCheckedChange !== undefined) {
            this.onCheckedChange = o20.onCheckedChange;
        }
        if (o20.checkTips !== undefined) {
            this.checkTips = o20.checkTips;
        }
        if (o20.isChecked !== undefined) {
            this.isChecked = o20.isChecked;
        }
        if (o20.primaryButton !== undefined) {
            this.primaryButton = o20.primaryButton;
        }
        if (o20.secondaryButton !== undefined) {
            this.secondaryButton = o20.secondaryButton;
        }
        if (o20.buttons !== undefined) {
            this.buttons = o20.buttons;
        }
        if (o20.imageSizeHeight !== undefined) {
            this.imageSizeHeight = o20.imageSizeHeight;
        }
        if (o20.textAlignment !== undefined) {
            this.textAlignment = o20.textAlignment;
        }
        if (o20.marginOffset !== undefined) {
            this.marginOffset = o20.marginOffset;
        }
        if (o20.checkBoxHeight !== undefined) {
            this.checkBoxHeight = o20.checkBoxHeight;
        }
        if (o20.buttonHeight !== undefined) {
            this.buttonHeight = o20.buttonHeight;
        }
        if (o20.contentScroller !== undefined) {
            this.contentScroller = o20.contentScroller;
        }
        if (o20.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = o20.fontColorWithTheme;
        }
        if (o20.theme !== undefined) {
            this.theme = o20.theme;
        }
    }

    updateStateVars(n20) {
    }

    purgeVariableDependenciesOnElmtId(m20) {
        this.__imageSize.purgeDependencyOnElmtId(m20);
        this.__isChecked.purgeDependencyOnElmtId(m20);
        this.__imageSizeHeight.purgeDependencyOnElmtId(m20);
        this.__textAlignment.purgeDependencyOnElmtId(m20);
        this.__checkBoxHeight.purgeDependencyOnElmtId(m20);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(m20);
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

    setController(l20) {
        this.controller = l20;
    }

    get imageSize() {
        return this.__imageSize.get();
    }

    set imageSize(k20) {
        this.__imageSize.set(k20);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(j20) {
        this.__isChecked.set(j20);
    }

    get imageSizeHeight() {
        return this.__imageSizeHeight.get();
    }

    set imageSizeHeight(i20) {
        this.__imageSizeHeight.set(i20);
    }

    get textAlignment() {
        return this.__textAlignment.get();
    }

    set textAlignment(h20) {
        this.__textAlignment.set(h20);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(g20) {
        this.__checkBoxHeight.set(g20);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(f20) {
        this.__fontColorWithTheme.set(f20);
    }

    initialRender() {
        {
            this.observeComponentCreation2((z19, a20) => {
                if (a20) {
                    let b20 = new CustomDialogComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, z19, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 86, col: 5 });
                    ViewPU.create(b20);
                    let c20 = () => {
                        return {
                            controller: this.controller,
                            contentBuilder: () => {
                                this.contentBuilder();
                            },
                            buttons: this.buttons,
                            theme: this.theme
                        };
                    };
                    b20.paramsGenerator_ = c20;
                } else {
                    this.updateStateVarsOfChildByElmtId(z19, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
    }

    contentBuilder(h19 = null) {
        this.observeComponentCreation2((w19, x19) => {
            Column.create();
        }, Column);
        this.imagePart.bind(this)(h19 ? h19 : this);
        this.observeComponentCreation2((p19, q19) => {
            If.create();
            if (this.title != null || this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u19, v19) => {
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
                    this.textPart.bind(this)(h19 ? h19 : this);
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((l19, m19) => {
            If.create();
            if (this.checkTips != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.checkBoxPart.bind(this)(this.checkTips, h19 ? h19 : this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }

    checkBoxPart(q18, r18 = null) {
        this.observeComponentCreation2((c19, d19) => {
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
            Row.onAreaChange((f19, g19) => {
                this.checkBoxHeight = Number(g19.height);
            });
        }, Row);
        this.observeComponentCreation2((y18, z18) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((b19) => {
                this.isChecked = b19;
                if (this.checkAction) {
                    this.checkAction(b19);
                }
                if (this.onCheckedChange) {
                    this.onCheckedChange(b19);
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
        this.observeComponentCreation2((v18, w18) => {
            Text.create(q18);
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

    imagePart(g18 = null) {
        this.observeComponentCreation2((l18, m18) => {
            Column.create();
            Column.width('100%');
            Column.constraintSize({
                maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
            });
            Column.onAreaChange((o18, p18) => {
                this.imageSizeHeight = Number(p18.height);
            });
        }, Column);
        this.observeComponentCreation2((j18, k18) => {
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

    textPart(y16 = null) {
        this.observeComponentCreation2((e18, f18) => {
            Scroll.create(this.contentScroller);
            Scroll.margin({ right: `${this.marginOffset}vp` });
        }, Scroll);
        this.observeComponentCreation2((c18, d18) => {
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
        this.observeComponentCreation2((s17, t17) => {
            If.create();
            if (this.title != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a18, b18) => {
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
                    this.observeComponentCreation2((y17, z17) => {
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
        this.observeComponentCreation2((d17, e17) => {
            If.create();
            if (this.content != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q17, r17) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((j17, k17) => {
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
                        Text.onKeyEvent((p17) => {
                            if (p17) {
                                resolveKeyEvent(p17, this.contentScroller);
                            }
                        });
                        Text.onAreaChange((n17, o17) => {
                            this.getTextAlign(Number(o17.width));
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

    getTextAlign(v16) {
        let w16 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            constraintWidth: v16,
        });
        let x16 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        });
        if (this.getTextHeight(w16) <= this.getTextHeight(x16)) {
            this.textAlignment = TextAlign.Center;
        }
    }

    getTextHeight(u16) {
        if (u16 && u16.height !== null && u16.height !== undefined) {
            return Number(u16.height);
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
        let t16 = getNumberByResource('alert_button_top_padding');
        t16 += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
        return t16;
    }

    initMargin() {
        this.marginOffset = 0 - getNumberByResource('padding_level8');
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export class SelectDialog extends ViewPU {
    constructor(j16, k16, l16, m16 = -1, n16 = undefined, o16) {
        super(j16, l16, m16, o16);
        if (typeof n16 === 'function') {
            this.paramsGenerator_ = n16;
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
                let p16 = new CustomContentDialog(this, {
                    primaryTitle: this.title,
                    contentBuilder: () => {
                        this.contentBuilder();
                    },
                    buttons: this.buttons,
                }, undefined, -1, () => {
                }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 293, col: 14 });
                p16.setController(this.controller);
                ViewPU.create(p16);
                let q16 = () => {
                    return {
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons
                    };
                };
                p16.paramsGenerator_ = q16;
            }
        }, this);
        this.contentScroller = new Scroller();
        this.setInitiallyProvidedValue(k16);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i16) {
        if (i16.title !== undefined) {
            this.title = i16.title;
        }
        if (i16.content !== undefined) {
            this.content = i16.content;
        }
        if (i16.selectedIndex !== undefined) {
            this.selectedIndex = i16.selectedIndex;
        }
        if (i16.confirm !== undefined) {
            this.confirm = i16.confirm;
        }
        if (i16.radioContent !== undefined) {
            this.radioContent = i16.radioContent;
        }
        if (i16.buttons !== undefined) {
            this.buttons = i16.buttons;
        }
        if (i16.contentPadding !== undefined) {
            this.contentPadding = i16.contentPadding;
        }
        if (i16.contentBuilder !== undefined) {
            this.contentBuilder = i16.contentBuilder;
        }
        if (i16.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = i16.fontColorWithTheme;
        }
        if (i16.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = i16.dividerColorWithTheme;
        }
        if (i16.theme !== undefined) {
            this.theme = i16.theme;
        }
        if (i16.controller !== undefined) {
            this.controller = i16.controller;
        }
        if (i16.contentScroller !== undefined) {
            this.contentScroller = i16.contentScroller;
        }
    }

    updateStateVars(h16) {
    }

    purgeVariableDependenciesOnElmtId(g16) {
        this.__fontColorWithTheme.purgeDependencyOnElmtId(g16);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(g16);
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

    set fontColorWithTheme(f16) {
        this.__fontColorWithTheme.set(f16);
    }

    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }

    set dividerColorWithTheme(e16) {
        this.__dividerColorWithTheme.set(e16);
    }

    setController(d16) {
        this.controller = d16;
    }

    buildContent(o13 = null) {
        this.observeComponentCreation2((b16, c16) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
        }, Scroll);
        this.observeComponentCreation2((z15, a16) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((p15, q15) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x15, y15) => {
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
                    this.observeComponentCreation2((v15, w15) => {
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
        this.observeComponentCreation2((m15, n15) => {
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
        this.observeComponentCreation2((u13, v13) => {
            ForEach.create();
            const w13 = (y13, z13) => {
                const a14 = y13;
                {
                    const b14 = (k15, l15) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(k15);
                        c14(k15, l15);
                        if (!l15) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const c14 = (i15, j15) => {
                        ListItem.create(d14, true);
                    };
                    const d14 = (h14, i14) => {
                        b14(h14, i14);
                        this.observeComponentCreation2((g15, h15) => {
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
                        this.observeComponentCreation2((d15, e15) => {
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
                                a14.action && a14.action();
                                this.controller.close();
                            });
                        }, Button);
                        this.observeComponentCreation2((b15, c15) => {
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
                        this.observeComponentCreation2((z14, a15) => {
                            Text.create(a14.title);
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
                        this.observeComponentCreation2((w14, x14) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === z13);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(z13));
                            Radio.onFocus(() => {
                                if (z13 == FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (z13 == this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((p14, q14) => {
                            If.create();
                            if (z13 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((u14, v14) => {
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
                    this.observeComponentCreation2(c14, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(u13, this.radioContent, w13, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }

    initialRender() {
        {
            this.observeComponentCreation2((i13, j13) => {
                if (j13) {
                    let k13 = new CustomDialogComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.title,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        contentAreaPadding: this.contentPadding,
                        theme: this.theme,
                    }, undefined, i13, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 388, col: 5 });
                    ViewPU.create(k13);
                    let l13 = () => {
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
                    k13.paramsGenerator_ = l13;
                } else {
                    this.updateStateVarsOfChildByElmtId(i13, {});
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
    constructor(x12, y12, z12, a13 = -1, b13 = undefined, c13) {
        super(x12, z12, a13, c13);
        if (typeof b13 === 'function') {
            this.paramsGenerator_ = b13;
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
        this.updateTitleHeight = (g13) => {
            this.titleHeight = g13;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.updateButtonHeight = (f13) => {
            this.buttonHeight = f13;
            this.maxContentHeight =
                `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
        };
        this.setInitiallyProvidedValue(y12);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(w12) {
        if (w12.controller !== undefined) {
            this.controller = w12.controller;
        }
        if (w12.title !== undefined) {
            this.title = w12.title;
        }
        if (w12.content !== undefined) {
            this.content = w12.content;
        }
        if (w12.checkTips !== undefined) {
            this.checkTips = w12.checkTips;
        }
        if (w12.isChecked !== undefined) {
            this.isChecked = w12.isChecked;
        }
        if (w12.primaryButton !== undefined) {
            this.primaryButton = w12.primaryButton;
        }
        if (w12.secondaryButton !== undefined) {
            this.secondaryButton = w12.secondaryButton;
        }
        if (w12.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = w12.fontColorWithTheme;
        }
        if (w12.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = w12.buttonFontColorWithTheme;
        }
        if (w12.theme !== undefined) {
            this.theme = w12.theme;
        }
        if (w12.onCheckedChange !== undefined) {
            this.onCheckedChange = w12.onCheckedChange;
        }
        if (w12.contentScroller !== undefined) {
            this.contentScroller = w12.contentScroller;
        }
        if (w12.buttons !== undefined) {
            this.buttons = w12.buttons;
        }
        if (w12.marginOffset !== undefined) {
            this.marginOffset = w12.marginOffset;
        }
        if (w12.titleHeight !== undefined) {
            this.titleHeight = w12.titleHeight;
        }
        if (w12.buttonHeight !== undefined) {
            this.buttonHeight = w12.buttonHeight;
        }
        if (w12.checkBoxHeight !== undefined) {
            this.checkBoxHeight = w12.checkBoxHeight;
        }
        if (w12.maxContentHeight !== undefined) {
            this.maxContentHeight = w12.maxContentHeight;
        }
        if (w12.updateTitleHeight !== undefined) {
            this.updateTitleHeight = w12.updateTitleHeight;
        }
        if (w12.updateButtonHeight !== undefined) {
            this.updateButtonHeight = w12.updateButtonHeight;
        }
    }

    updateStateVars(v12) {
    }

    purgeVariableDependenciesOnElmtId(u12) {
        this.__isChecked.purgeDependencyOnElmtId(u12);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(u12);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(u12);
        this.__titleHeight.purgeDependencyOnElmtId(u12);
        this.__buttonHeight.purgeDependencyOnElmtId(u12);
        this.__checkBoxHeight.purgeDependencyOnElmtId(u12);
        this.__maxContentHeight.purgeDependencyOnElmtId(u12);
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

    setController(t12) {
        this.controller = t12;
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(s12) {
        this.__isChecked.set(s12);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(r12) {
        this.__fontColorWithTheme.set(r12);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(q12) {
        this.__buttonFontColorWithTheme.set(q12);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(p12) {
        this.__titleHeight.set(p12);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(o12) {
        this.__buttonHeight.set(o12);
    }

    get checkBoxHeight() {
        return this.__checkBoxHeight.get();
    }

    set checkBoxHeight(n12) {
        this.__checkBoxHeight.set(n12);
    }

    get maxContentHeight() {
        return this.__maxContentHeight.get();
    }

    set maxContentHeight(m12) {
        this.__maxContentHeight.set(m12);
    }

    buildContent(a11 = null) {
        this.observeComponentCreation2((k12, l12) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((v11, w11) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i12, j12) => {
                        Row.create();
                        Row.padding({ bottom: 8 });
                        Row.margin({ right: `${this.marginOffset}vp` });
                        Row.constraintSize({
                            minHeight: 36,
                            maxHeight: this.maxContentHeight
                        });
                    }, Row);
                    this.observeComponentCreation2((g12, h12) => {
                        Scroll.create(this.contentScroller);
                        Scroll.width('100%');
                    }, Scroll);
                    this.observeComponentCreation2((c12, d12) => {
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
                        Text.onKeyEvent((f12) => {
                            if (f12) {
                                resolveKeyEvent(f12, this.contentScroller);
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
        this.observeComponentCreation2((q11, r11) => {
            Row.create();
            Row.onSizeChange((t11, u11) => {
                this.checkBoxHeight = Number(u11.height);
            });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((o11, p11) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((k11, l11) => {
            Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((n11) => {
                this.isChecked = n11;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) });
        }, Checkbox);
        Checkbox.pop();
        WithTheme.pop();
        this.observeComponentCreation2((h11, i11) => {
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
            this.observeComponentCreation2((u10, v10) => {
                if (v10) {
                    let w10 = new CustomDialogComponent(this, {
                        primaryTitle: this.title,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.buildContent();
                        },
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, u10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 538, col: 5 });
                    ViewPU.create(w10);
                    let x10 = () => {
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
                    w10.paramsGenerator_ = x10;
                } else {
                    this.updateStateVarsOfChildByElmtId(u10, {});
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
    constructor(n10, o10, p10, q10 = -1, r10 = undefined, s10) {
        super(n10, p10, q10, s10);
        if (typeof r10 === 'function') {
            this.paramsGenerator_ = r10;
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
        this.setInitiallyProvidedValue(o10);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(m10) {
        if (m10.controller !== undefined) {
            this.controller = m10.controller;
        }
        if (m10.primaryTitle !== undefined) {
            this.primaryTitle = m10.primaryTitle;
        }
        if (m10.secondaryTitle !== undefined) {
            this.secondaryTitle = m10.secondaryTitle;
        }
        if (m10.content !== undefined) {
            this.content = m10.content;
        }
        if (m10.primaryButton !== undefined) {
            this.primaryButton = m10.primaryButton;
        }
        if (m10.secondaryButton !== undefined) {
            this.secondaryButton = m10.secondaryButton;
        }
        if (m10.buttons !== undefined) {
            this.buttons = m10.buttons;
        }
        if (m10.textAlign !== undefined) {
            this.textAlign = m10.textAlign;
        }
        if (m10.contentScroller !== undefined) {
            this.contentScroller = m10.contentScroller;
        }
        if (m10.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = m10.fontColorWithTheme;
        }
        if (m10.theme !== undefined) {
            this.theme = m10.theme;
        }
    }

    updateStateVars(l10) {
    }

    purgeVariableDependenciesOnElmtId(k10) {
        this.__textAlign.purgeDependencyOnElmtId(k10);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(k10);
    }

    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(j10) {
        this.controller = j10;
    }

    get textAlign() {
        return this.__textAlign.get();
    }

    set textAlign(i10) {
        this.__textAlign.set(i10);
    }

    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }

    set fontColorWithTheme(h10) {
        this.__fontColorWithTheme.set(h10);
    }

    initialRender() {
        {
            this.observeComponentCreation2((b10, c10) => {
                if (c10) {
                    let d10 = new CustomDialogComponent(this, {
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        controller: this.controller,
                        contentBuilder: () => {
                            this.AlertDialogContentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, b10, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 594, col: 5 });
                    ViewPU.create(d10);
                    let e10 = () => {
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
                    d10.paramsGenerator_ = e10;
                } else {
                    this.updateStateVarsOfChildByElmtId(b10, {});
                }
            }, { name: 'CustomDialogComponent' });
        }
    }

    AlertDialogContentBuilder(l9 = null) {
        this.observeComponentCreation2((y9, z9) => {
            Column.create();
            Column.margin({ right: `${this.getMargin()}vp`, });
        }, Column);
        this.observeComponentCreation2((w9, x9) => {
            Scroll.create(this.contentScroller);
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((p9, q9) => {
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
            Text.onAreaChange((u9, v9) => {
                this.getTextAlign(Number(v9.width));
            });
            Text.onKeyEvent((t9) => {
                if (t9) {
                    resolveKeyEvent(t9, this.contentScroller);
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

    getTextAlign(i9) {
        let j9 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
            constraintWidth: i9,
        });
        let k9 = measure.measureTextSize({
            textContent: this.content,
            fontSize: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            },
        });
        if (this.getTextHeight(j9) <= this.getTextHeight(k9)) {
            this.textAlign = TextAlign.Center;
        }
    }

    getTextHeight(h9) {
        if (h9 && h9.height !== null && h9.height !== undefined) {
            return Number(h9.height);
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
    constructor(b9, c9, d9, e9 = -1, f9 = undefined, g9) {
        super(b9, d9, e9, g9);
        if (typeof f9 === 'function') {
            this.paramsGenerator_ = f9;
        }
        this.controller = undefined;
        this.primaryTitle = undefined;
        this.secondaryTitle = undefined;
        this.contentBuilder = undefined;
        this.contentAreaPadding = undefined;
        this.buttons = undefined;
        this.theme = new CustomThemeImpl({});
        this.setInitiallyProvidedValue(c9);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(a9) {
        if (a9.controller !== undefined) {
            this.controller = a9.controller;
        }
        if (a9.primaryTitle !== undefined) {
            this.primaryTitle = a9.primaryTitle;
        }
        if (a9.secondaryTitle !== undefined) {
            this.secondaryTitle = a9.secondaryTitle;
        }
        if (a9.contentBuilder !== undefined) {
            this.contentBuilder = a9.contentBuilder;
        }
        if (a9.contentAreaPadding !== undefined) {
            this.contentAreaPadding = a9.contentAreaPadding;
        }
        if (a9.buttons !== undefined) {
            this.buttons = a9.buttons;
        }
        if (a9.theme !== undefined) {
            this.theme = a9.theme;
        }
    }

    updateStateVars(z8) {
    }

    purgeVariableDependenciesOnElmtId(y8) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    setController(x8) {
        this.controller = x8;
    }

    initialRender() {
        {
            this.observeComponentCreation2((r8, s8) => {
                if (s8) {
                    let t8 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        primaryTitle: this.primaryTitle,
                        secondaryTitle: this.secondaryTitle,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        contentAreaPadding: this.contentAreaPadding,
                        buttons: this.buttons,
                        theme: this.theme,
                    }, undefined, r8, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 698, col: 5 });
                    ViewPU.create(t8);
                    let u8 = () => {
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
                    t8.paramsGenerator_ = u8;
                } else {
                    this.updateStateVarsOfChildByElmtId(r8, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class CustomDialogContentComponent extends ViewPU {
    constructor(k8, l8, m8, n8 = -1, o8 = undefined, p8) {
        super(k8, m8, n8, p8);
        if (typeof o8 === 'function') {
            this.paramsGenerator_ = o8;
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
        this.setInitiallyProvidedValue(l8);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(j8) {
        if (j8.controller !== undefined) {
            this.controller = j8.controller;
        }
        if (j8.primaryTitle !== undefined) {
            this.primaryTitle = j8.primaryTitle;
        }
        if (j8.secondaryTitle !== undefined) {
            this.secondaryTitle = j8.secondaryTitle;
        }
        if (j8.contentBuilder !== undefined) {
            this.contentBuilder = j8.contentBuilder;
        }
        if (j8.buttons !== undefined) {
            this.buttons = j8.buttons;
        }
        if (j8.contentAreaPadding !== undefined) {
            this.contentAreaPadding = j8.contentAreaPadding;
        }
        if (j8.keyIndex !== undefined) {
            this.keyIndex = j8.keyIndex;
        }
        if (j8.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = j8.primaryTitleFontColorWithTheme;
        }
        if (j8.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = j8.secondaryTitleFontColorWithTheme;
        }
        if (j8.buttonFontColorWithTheme !== undefined) {
            this.buttonFontColorWithTheme = j8.buttonFontColorWithTheme;
        }
        if (j8.errorButtonFontColorWithTheme !== undefined) {
            this.errorButtonFontColorWithTheme = j8.errorButtonFontColorWithTheme;
        }
        if (j8.theme !== undefined) {
            this.theme = j8.theme;
        }
        if (j8.titleHeight !== undefined) {
            this.titleHeight = j8.titleHeight;
        }
        if (j8.buttonHeight !== undefined) {
            this.buttonHeight = j8.buttonHeight;
        }
        if (j8.contentMaxHeight !== undefined) {
            this.contentMaxHeight = j8.contentMaxHeight;
        }
        if (j8.updateTitleHeight !== undefined) {
            this.updateTitleHeight = j8.updateTitleHeight;
        }
        if (j8.updateButtonHeight !== undefined) {
            this.updateButtonHeight = j8.updateButtonHeight;
        }
    }

    updateStateVars(i8) {
    }

    purgeVariableDependenciesOnElmtId(h8) {
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(h8);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(h8);
        this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(h8);
        this.__errorButtonFontColorWithTheme.purgeDependencyOnElmtId(h8);
        this.__contentMaxHeight.purgeDependencyOnElmtId(h8);
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

    set primaryTitleFontColorWithTheme(g8) {
        this.__primaryTitleFontColorWithTheme.set(g8);
    }

    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }

    set secondaryTitleFontColorWithTheme(f8) {
        this.__secondaryTitleFontColorWithTheme.set(f8);
    }

    get buttonFontColorWithTheme() {
        return this.__buttonFontColorWithTheme.get();
    }

    set buttonFontColorWithTheme(e8) {
        this.__buttonFontColorWithTheme.set(e8);
    }

    get errorButtonFontColorWithTheme() {
        return this.__errorButtonFontColorWithTheme.get();
    }

    set errorButtonFontColorWithTheme(d8) {
        this.__errorButtonFontColorWithTheme.set(d8);
    }

    defaultContentBuilder(c8 = null) {
    }

    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }

    set contentMaxHeight(b8) {
        this.__contentMaxHeight.set(b8);
    }

    initialRender() {
        this.observeComponentCreation2((z7, a8) => {
            WithTheme.create({ theme: this.theme });
        }, WithTheme);
        this.observeComponentCreation2((x7, y7) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.buildTitles.bind(this)(this);
        this.observeComponentCreation2((v7, w7) => {
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

    buildTitles(o6 = null) {
        this.observeComponentCreation2((n7, o7) => {
            Column.create();
            Column.constraintSize({
                minHeight: this.getTitleAreaMinHeight(),
            });
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
            Column.onAreaChange((q7, r7) => {
                this.titleHeight = Number(r7.height);
                if (this.updateTitleHeight) {
                    this.updateTitleHeight(this.titleHeight);
                }
                this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
            });
        }, Column);
        this.observeComponentCreation2((l7, m7) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((j7, k7) => {
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
        this.observeComponentCreation2((z6, a7) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h7, i7) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((f7, g7) => {
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
        this.observeComponentCreation2((x6, y6) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((v6, w6) => {
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
            Column.onSizeChange((m6, n6) => {
                this.buttonHeight = Number(n6.height);
                if (this.updateButtonHeight) {
                    this.updateButtonHeight(this.buttonHeight);
                }
            });
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
        let f3 = getNumberByResource('alert_button_top_padding');
        if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
            f3 += BUTTON_DEFAULT_HEIGHT +
            getNumberByResource('alert_button_bottom_padding_horizontal');
        } else {
            f3 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
                (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
            getNumberByResource('alert_button_bottom_padding_vertical');
        }
        this.buttonHeight = f3;
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
        this.updateTitleHeight = undefined;
        this.updateButtonHeight = undefined;
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
        if (w2.updateTitleHeight !== undefined) {
            this.updateTitleHeight = w2.updateTitleHeight;
        }
        if (w2.updateButtonHeight !== undefined) {
            this.updateButtonHeight = w2.updateButtonHeight;
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
                if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
                    this.columnModifier.customStyle = s2.width > getNumberByResource('alert_container_max_width');
                } else {
                    this.columnModifier.customStyle = s2.width >= this.screenWidth;
                }
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
                        updateTitleHeight: this.updateTitleHeight,
                        updateButtonHeight: this.updateButtonHeight,
                        buttons: this.buttons,
                        contentAreaPadding: this.contentAreaPadding,
                        theme: this.theme,
                    }, undefined, g2, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1141, col: 9 });
                    ViewPU.create(i2);
                    let j2 = () => {
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
                    }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1301, col: 7 });
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