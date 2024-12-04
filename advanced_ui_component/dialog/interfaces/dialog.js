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
const accessibility = requireNapi('accessibility');

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

class CustomThemeImpl {
    constructor(m35) {
        this.colors = m35;
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
    constructor(f35, g35, h35, i35 = -1, j35 = undefined, k35) {
        super(f35, h35, i35, k35);
        if (typeof j35 === 'function') {
            this.paramsGenerator_ = j35;
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
        this.updateTextAlign = (l35) => {
            if (this.content) {
                this.textAlignment = getTextAlign(l35, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(g35);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(e35) {
        if (e35.controller !== undefined) {
            this.controller = e35.controller;
        }
        if (e35.imageRes !== undefined) {
            this.imageRes = e35.imageRes;
        }
        if (e35.imageSize !== undefined) {
            this.imageSize = e35.imageSize;
        }
        if (e35.title !== undefined) {
            this.title = e35.title;
        }
        if (e35.content !== undefined) {
            this.content = e35.content;
        }
        if (e35.checkAction !== undefined) {
            this.checkAction = e35.checkAction;
        }
        if (e35.onCheckedChange !== undefined) {
            this.onCheckedChange = e35.onCheckedChange;
        }
        if (e35.checkTips !== undefined) {
            this.checkTips = e35.checkTips;
        }
        if (e35.isChecked !== undefined) {
            this.isChecked = e35.isChecked;
        }
        if (e35.primaryButton !== undefined) {
            this.primaryButton = e35.primaryButton;
        }
        if (e35.secondaryButton !== undefined) {
            this.secondaryButton = e35.secondaryButton;
        }
        if (e35.buttons !== undefined) {
            this.buttons = e35.buttons;
        }
        if (e35.textAlignment !== undefined) {
            this.textAlignment = e35.textAlignment;
        }
        if (e35.marginOffset !== undefined) {
            this.marginOffset = e35.marginOffset;
        }
        if (e35.contentScroller !== undefined) {
            this.contentScroller = e35.contentScroller;
        }
        if (e35.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = e35.fontColorWithTheme;
        }
        if (e35.theme !== undefined) {
            this.theme = e35.theme;
        }
        if (e35.themeColorMode !== undefined) {
            this.themeColorMode = e35.themeColorMode;
        }
        if (e35.fontSizeScale !== undefined) {
            this.fontSizeScale = e35.fontSizeScale;
        }
        if (e35.minContentHeight !== undefined) {
            this.minContentHeight = e35.minContentHeight;
        }
        if (e35.updateTextAlign !== undefined) {
            this.updateTextAlign = e35.updateTextAlign;
        }
        if (e35.imageIndex !== undefined) {
            this.imageIndex = e35.imageIndex;
        }
        if (e35.textIndex !== undefined) {
            this.textIndex = e35.textIndex;
        }
        if (e35.checkBoxIndex !== undefined) {
            this.checkBoxIndex = e35.checkBoxIndex;
        }
        if (e35.appMaxFontScale !== undefined) {
            this.appMaxFontScale = e35.appMaxFontScale;
        }
    }
    updateStateVars(d35) {
    }
    purgeVariableDependenciesOnElmtId(c35) {
        this.__imageSize.purgeDependencyOnElmtId(c35);
        this.__isChecked.purgeDependencyOnElmtId(c35);
        this.__textAlignment.purgeDependencyOnElmtId(c35);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(c35);
        this.__fontSizeScale.purgeDependencyOnElmtId(c35);
        this.__minContentHeight.purgeDependencyOnElmtId(c35);
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
    setController(b35) {
        this.controller = b35;
    }
    get imageSize() {
        return this.__imageSize.get();
    }
    set imageSize(a35) {
        this.__imageSize.set(a35);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(z34) {
        this.__isChecked.set(z34);
    }
    get textAlignment() {
        return this.__textAlignment.get();
    }
    set textAlignment(y34) {
        this.__textAlignment.set(y34);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(x34) {
        this.__fontColorWithTheme.set(x34);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(w34) {
        this.__fontSizeScale.set(w34);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(v34) {
        this.__minContentHeight.set(v34);
    }
    initialRender() {
        this.observeComponentCreation2((t34, u34) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((p34, q34) => {
                if (q34) {
                    let r34 = new CustomDialogContentComponent(this, {
                        controller: this.controller,
                        contentBuilder: () => {
                            this.contentBuilder();
                        },
                        buttons: this.buttons,
                        theme: this.theme,
                        themeColorMode: this.themeColorMode,
                        fontSizeScale: this.__fontSizeScale,
                        minContentHeight: this.__minContentHeight,
                    }, undefined, p34, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 124, col: 5 });
                    ViewPU.create(r34);
                    let s34 = () => {
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
                    r34.paramsGenerator_ = s34;
                } else {
                    this.updateStateVarsOfChildByElmtId(p34, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }
    contentBuilder(k33 = null) {
        {
            this.observeComponentCreation2((l33, m33) => {
                if (m33) {
                    let n33 = new TipsDialogContentLayout(this, {
                        title: this.title,
                        content: this.content,
                        checkTips: this.checkTips,
                        minContentHeight: this.__minContentHeight,
                        updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((c34, d34) => {
                                ForEach.create();
                                const e34 = f34 => {
                                    const g34 = f34;
                                    this.observeComponentCreation2((h34, i34) => {
                                        If.create();
                                        if (g34 === this.imageIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.imagePart.bind(this)();
                                            });
                                        } else if (g34 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((n34, o34) => {
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
                                                this.observeComponentCreation2((l34, m34) => {
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
                                                this.observeComponentCreation2((j34, k34) => {
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
                                this.forEachUpdateFunction(c34, [this.imageIndex, this.textIndex,
                                    this.checkBoxIndex], e34);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, l33, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 139, col: 5 });
                    ViewPU.create(n33);
                    let o33 = () => {
                        return {
                            title: this.title,
                            content: this.content,
                            checkTips: this.checkTips,
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((p33, q33) => {
                                    ForEach.create();
                                    const r33 = s33 => {
                                        const t33 = s33;
                                        this.observeComponentCreation2((u33, v33) => {
                                            If.create();
                                            if (t33 === this.imageIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.imagePart.bind(this)();
                                                });
                                            } else if (t33 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((a34, b34) => {
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
                                                    this.observeComponentCreation2((y33, z33) => {
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
                                                    this.observeComponentCreation2((w33, x33) => {
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
                                    this.forEachUpdateFunction(p33,
                                        [this.imageIndex, this.textIndex, this.checkBoxIndex], r33);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    n33.paramsGenerator_ = o33;
                } else {
                    this.updateStateVarsOfChildByElmtId(l33, {});
                }
            }, { name: 'TipsDialogContentLayout' });
        }
    }
    checkBoxPart(z32 = null) {
        this.observeComponentCreation2((h33, i33) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked));
            Row.accessibilityDescription(this.isChecked ? {
                'id': -1,
                'type': 10003,
                params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10003,
                params: ['sys.string.slider_accessibility_unselectedDesc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
                if (this.checkAction) {
                    this.checkAction(this.isChecked);
                }
                let j33 = ({
                    type: 'announceForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: this.isChecked ?
                    getContext().resourceManager.getStringSync(125833934) :
                    getContext().resourceManager.getStringSync(125833935)
                });
                accessibility.sendAccessibilityEvent(j33).then(() => {
                    console.info(`Accessibility send event`);
                });
            });
            Row.padding({ top: 8, bottom: 8 });
            Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((a33, b33) => {
            If.create();
            if (this.checkTips !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e33, f33) => {
                        Checkbox.create({ name: '', group: 'checkboxGroup' });
                        Checkbox.select(this.isChecked);
                        Checkbox.onChange((g33) => {
                            this.isChecked = g33;
                            if (this.checkAction) {
                                this.checkAction(g33);
                            }
                            if (this.onCheckedChange) {
                                this.onCheckedChange(g33);
                            }
                        });
                        Checkbox.margin({
                            start: LengthMetrics.vp(0),
                            end: LengthMetrics.vp(CHECK_BOX_MARGIN_END)
                        });
                    }, Checkbox);
                    Checkbox.pop();
                    this.observeComponentCreation2((c33, d33) => {
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
    imagePart(u32 = null) {
        this.observeComponentCreation2((x32, y32) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((v32, w32) => {
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
    textPart(c32 = null) {
        this.observeComponentCreation2((s32, t32) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((q32, r32) => {
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
        this.observeComponentCreation2((k32, l32) => {
            If.create();
            if (this.title !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o32, p32) => {
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
                    this.observeComponentCreation2((m32, n32) => {
                        Text.create(this.title);
                        Text.fontSize(`${TITLE_S}fp`);
                        Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
        this.observeComponentCreation2((d32, e32) => {
            If.create();
            if (this.content !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i32, j32) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((f32, g32) => {
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
                        Text.onKeyEvent((h32) => {
                            if (h32) {
                                resolveKeyEvent(h32, this.contentScroller);
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
        let b32 = this.getUIContext();
        this.appMaxFontScale = b32.getMaxFontScale();
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
    constructor(u31, v31, w31, x31 = -1, y31 = undefined, z31) {
        super(u31, w31, x31, z31);
        if (typeof y31 === 'function') {
            this.paramsGenerator_ = y31;
        }
        this.title = null;
        this.content = null;
        this.checkTips = null;
        this.updateTextAlign = (a32) => {
        };
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(v31.minContentHeight, this, 'minContentHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.imageIndex = 0;
        this.textIndex = 1;
        this.checkBoxIndex = 2;
        this.childrenSize = 3;
        this.setInitiallyProvidedValue(v31);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(t31) {
        if (t31.title !== undefined) {
            this.title = t31.title;
        }
        if (t31.content !== undefined) {
            this.content = t31.content;
        }
        if (t31.checkTips !== undefined) {
            this.checkTips = t31.checkTips;
        }
        if (t31.updateTextAlign !== undefined) {
            this.updateTextAlign = t31.updateTextAlign;
        }
        if (t31.dialogBuilder !== undefined) {
            this.dialogBuilder = t31.dialogBuilder;
        }
        if (t31.imageIndex !== undefined) {
            this.imageIndex = t31.imageIndex;
        }
        if (t31.textIndex !== undefined) {
            this.textIndex = t31.textIndex;
        }
        if (t31.checkBoxIndex !== undefined) {
            this.checkBoxIndex = t31.checkBoxIndex;
        }
        if (t31.childrenSize !== undefined) {
            this.childrenSize = t31.childrenSize;
        }
    }
    updateStateVars(s31) {
    }
    purgeVariableDependenciesOnElmtId(r31) {
        this.__minContentHeight.purgeDependencyOnElmtId(r31);
    }
    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(q31 = null) {
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(p31) {
        this.__minContentHeight.set(p31);
    }
    onPlaceChildren(i31, j31, k31) {
        let l31 = 0;
        let m31 = 0;
        for (let n31 = 0; n31 < j31.length; n31++) {
            let o31 = j31[n31];
            o31.layout({ x: l31, y: m31 });
            m31 += o31.measureResult.height;
        }
    }
    onMeasureSize(q30, r30, s30) {
        let t30 = { width: Number(s30.maxWidth), height: 0 };
        if (r30.length < this.childrenSize) {
            return t30;
        }
        let u30 = 0;
        let v30 = 0;
        if (this.checkTips !== null) {
            let f31 = r30[this.checkBoxIndex];
            let g31 = {
                maxWidth: s30.maxWidth,
                minHeight: CHECKBOX_CONTAINER_HEIGHT,
                maxHeight: s30.maxHeight
            };
            let h31 = f31.measure(g31);
            v30 = h31.height;
            u30 += v30;
        }
        let w30 = r30[this.imageIndex];
        let x30 = 0;
        if (this.title !== null || this.content !== null) {
            x30 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
        }
        let y30 = Number(s30.maxHeight) - v30 - x30;
        let z30 = {
            maxWidth: s30.maxWidth,
            maxHeight: y30
        };
        let a31 = w30.measure(z30);
        u30 += a31.height;
        if (this.title !== null || this.content !== null) {
            let b31 = r30[this.textIndex];
            this.updateTextAlign(t30.width);
            let c31 = Number(s30.maxHeight) - a31.height - v30;
            let d31 = {
                maxWidth: s30.maxWidth,
                maxHeight: Math.max(c31, TEXT_MIN_HEIGHT)
            };
            let e31 = b31.measure(d31);
            u30 += e31.height;
        }
        t30.height = u30;
        this.minContentHeight = Math.max(v30 + a31.height + x30, MIN_CONTENT_HEIGHT);
        return t30;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class SelectDialog extends ViewPU {
    constructor(k30, l30, m30, n30 = -1, o30 = undefined, p30) {
        super(k30, m30, n30, p30);
        if (typeof o30 === 'function') {
            this.paramsGenerator_ = o30;
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
        this.setInitiallyProvidedValue(l30);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j30) {
        if (j30.controller !== undefined) {
            this.controller = j30.controller;
        }
        if (j30.title !== undefined) {
            this.title = j30.title;
        }
        if (j30.content !== undefined) {
            this.content = j30.content;
        }
        if (j30.confirm !== undefined) {
            this.confirm = j30.confirm;
        }
        if (j30.radioContent !== undefined) {
            this.radioContent = j30.radioContent;
        }
        if (j30.buttons !== undefined) {
            this.buttons = j30.buttons;
        }
        if (j30.contentPadding !== undefined) {
            this.contentPadding = j30.contentPadding;
        }
        if (j30.isFocus !== undefined) {
            this.isFocus = j30.isFocus;
        }
        if (j30.currentFocusIndex !== undefined) {
            this.currentFocusIndex = j30.currentFocusIndex;
        }
        if (j30.radioHeight !== undefined) {
            this.radioHeight = j30.radioHeight;
        }
        if (j30.itemHeight !== undefined) {
            this.itemHeight = j30.itemHeight;
        }
        if (j30.selectedIndex !== undefined) {
            this.selectedIndex = j30.selectedIndex;
        }
        if (j30.contentBuilder !== undefined) {
            this.contentBuilder = j30.contentBuilder;
        }
        if (j30.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = j30.fontColorWithTheme;
        }
        if (j30.dividerColorWithTheme !== undefined) {
            this.dividerColorWithTheme = j30.dividerColorWithTheme;
        }
        if (j30.theme !== undefined) {
            this.theme = j30.theme;
        }
        if (j30.themeColorMode !== undefined) {
            this.themeColorMode = j30.themeColorMode;
        }
        if (j30.contentScroller !== undefined) {
            this.contentScroller = j30.contentScroller;
        }
        if (j30.fontSizeScale !== undefined) {
            this.fontSizeScale = j30.fontSizeScale;
        }
        if (j30.minContentHeight !== undefined) {
            this.minContentHeight = j30.minContentHeight;
        }
    }
    updateStateVars(i30) {
    }
    purgeVariableDependenciesOnElmtId(h30) {
        this.__selectedIndex.purgeDependencyOnElmtId(h30);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(h30);
        this.__dividerColorWithTheme.purgeDependencyOnElmtId(h30);
        this.__fontSizeScale.purgeDependencyOnElmtId(h30);
        this.__minContentHeight.purgeDependencyOnElmtId(h30);
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
    setController(g30) {
        this.controller = g30;
    }
    get selectedIndex() {
        return this.__selectedIndex.get();
    }
    set selectedIndex(f30) {
        this.__selectedIndex.set(f30);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(e30) {
        this.__fontColorWithTheme.set(e30);
    }
    get dividerColorWithTheme() {
        return this.__dividerColorWithTheme.get();
    }
    set dividerColorWithTheme(d30) {
        this.__dividerColorWithTheme.set(d30);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(c30) {
        this.__fontSizeScale.set(c30);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(b30) {
        this.__minContentHeight.set(b30);
    }
    buildContent(e28 = null) {
        this.observeComponentCreation2((w29, x29) => {
            Scroll.create(this.contentScroller);
            Scroll.scrollBar(BarState.Auto);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.onDidScroll((y29, z29) => {
                let a30 = (this.itemHeight - this.radioHeight) / 2;
                if (this.isFocus) {
                    if (this.currentFocusIndex === this.radioContent.length - 1) {
                        this.contentScroller.scrollEdge(Edge.Bottom);
                        this.currentFocusIndex = -1;
                    } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
                        this.contentScroller.scrollEdge(Edge.Top);
                        this.currentFocusIndex = -1;
                    } else {
                        if (z29 > 0) {
                            this.contentScroller.scrollBy(0, a30);
                        } else if (z29 < 0) {
                            this.contentScroller.scrollBy(0, 0 - a30);
                        }
                    }
                    this.isFocus = false;
                }
            });
        }, Scroll);
        this.observeComponentCreation2((u29, v29) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((o29, p29) => {
            If.create();
            if (this.content) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s29, t29) => {
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
                    this.observeComponentCreation2((q29, r29) => {
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
        this.observeComponentCreation2((m29, n29) => {
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
        this.observeComponentCreation2((f28, g28) => {
            ForEach.create();
            const h28 = (i28, j28) => {
                const k28 = i28;
                {
                    const l28 = (k29, l29) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(k29);
                        m28(k29, l29);
                        if (!l29) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const m28 = (g29, h29) => {
                        ListItem.create(n28, true);
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
                        ListItem.onSizeChange((i29, j29) => {
                            this.itemHeight = Number(j29.height);
                        });
                    };
                    const n28 = (o28, p28) => {
                        l28(o28, p28);
                        this.observeComponentCreation2((e29, f29) => {
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
                            Column.accessibilityText(getAccessibilityText(k28.title, this.selectedIndex === j28));
                            Column.onClick(() => {
                                this.selectedIndex = j28;
                                k28.action && k28.action();
                                this.controller?.close();
                            });
                        }, Column);
                        this.observeComponentCreation2((c29, d29) => {
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
                        this.observeComponentCreation2((a29, b29) => {
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
                        this.observeComponentCreation2((y28, z28) => {
                            Text.create(k28.title);
                            Text.fontSize(`${BODY_L}fp`);
                            Text.fontWeight(FontWeight.Medium);
                            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
                            Text.layoutWeight(1);
                        }, Text);
                        Text.pop();
                        this.observeComponentCreation2((u28, v28) => {
                            Radio.create({ value: 'item.title', group: 'radioGroup' });
                            Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
                            Radio.checked(this.selectedIndex === j28);
                            Radio.hitTestBehavior(HitTestMode.None);
                            Radio.id(String(j28));
                            Radio.focusable(false);
                            Radio.accessibilityLevel('no');
                            Radio.onFocus(() => {
                                this.isFocus = true;
                                this.currentFocusIndex = j28;
                                if (j28 === FIRST_ITEM_INDEX) {
                                    this.contentScroller.scrollEdge(Edge.Top);
                                } else if (j28 === this.radioContent.length - 1) {
                                    this.contentScroller.scrollEdge(Edge.Bottom);
                                }
                            });
                            Radio.onSizeChange((w28, x28) => {
                                this.radioHeight = Number(x28.height);
                            });
                        }, Radio);
                        Row.pop();
                        Button.pop();
                        this.observeComponentCreation2((q28, r28) => {
                            If.create();
                            if (j28 < this.radioContent.length - 1) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((s28, t28) => {
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
                    this.observeComponentCreation2(m28, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(f28, this.radioContent, h28, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        Scroll.pop();
    }
    initialRender() {
        this.observeComponentCreation2((c28, d28) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((y27, z27) => {
                if (z27) {
                    let a28 = new CustomDialogContentComponent(this, {
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
                    }, undefined, y27, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 534, col: 5 });
                    ViewPU.create(a28);
                    let b28 = () => {
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
                    a28.paramsGenerator_ = b28;
                } else {
                    this.updateStateVarsOfChildByElmtId(y27, {});
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
    constructor(r27, s27, t27, u27 = -1, v27 = undefined, w27) {
        super(r27, t27, u27, w27);
        if (typeof v27 === 'function') {
            this.paramsGenerator_ = v27;
        }
        this.textIndex = 0;
        this.checkboxIndex = 1;
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(s27.minContentHeight, this, 'minContentHeight');
        this.updateTextAlign = (x27) => {
        };
        this.dialogBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(s27);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q27) {
        if (q27.textIndex !== undefined) {
            this.textIndex = q27.textIndex;
        }
        if (q27.checkboxIndex !== undefined) {
            this.checkboxIndex = q27.checkboxIndex;
        }
        if (q27.updateTextAlign !== undefined) {
            this.updateTextAlign = q27.updateTextAlign;
        }
        if (q27.dialogBuilder !== undefined) {
            this.dialogBuilder = q27.dialogBuilder;
        }
    }
    updateStateVars(p27) {
    }
    purgeVariableDependenciesOnElmtId(o27) {
        this.__minContentHeight.purgeDependencyOnElmtId(o27);
    }
    aboutToBeDeleted() {
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(n27) {
        this.__minContentHeight.set(n27);
    }
    doNothingBuilder(m27 = null) {
    }
    onPlaceChildren(f27, g27, h27) {
        let i27 = 0;
        let j27 = 0;
        for (let k27 = 0; k27 < g27.length; k27++) {
            let l27 = g27[k27];
            l27.layout({ x: i27, y: j27 });
            j27 += l27.measureResult.height;
        }
    }
    onMeasureSize(t26, u26, v26) {
        let w26 = { width: Number(v26.maxWidth), height: 0 };
        let x26 = 2;
        if (u26.length < x26) {
            return w26;
        }
        this.updateTextAlign(w26.width);
        let y26 = 0;
        let z26 = u26[this.checkboxIndex];
        let a27 = {
            maxWidth: v26.maxWidth,
            minHeight: CHECKBOX_CONTAINER_HEIGHT,
            maxHeight: v26.maxHeight
        };
        let b27 = z26.measure(a27);
        y26 += b27.height;
        let c27 = u26[this.textIndex];
        let d27 = {
            maxWidth: v26.maxWidth,
            maxHeight: Number(v26.maxHeight) - y26
        };
        let e27 = c27.measure(d27);
        y26 += e27.height;
        w26.height = y26;
        this.minContentHeight = Math.max(b27.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
        return w26;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ConfirmDialog extends ViewPU {
    constructor(m26, n26, o26, p26 = -1, q26 = undefined, r26) {
        super(m26, o26, p26, r26);
        if (typeof q26 === 'function') {
            this.paramsGenerator_ = q26;
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
        this.updateTextAlign = (s26) => {
            if (this.content) {
                this.textAlign = getTextAlign(s26, this.content, `${BODY_L * this.fontSizeScale}vp`);
            }
        };
        this.setInitiallyProvidedValue(n26);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l26) {
        if (l26.controller !== undefined) {
            this.controller = l26.controller;
        }
        if (l26.title !== undefined) {
            this.title = l26.title;
        }
        if (l26.content !== undefined) {
            this.content = l26.content;
        }
        if (l26.checkTips !== undefined) {
            this.checkTips = l26.checkTips;
        }
        if (l26.isChecked !== undefined) {
            this.isChecked = l26.isChecked;
        }
        if (l26.primaryButton !== undefined) {
            this.primaryButton = l26.primaryButton;
        }
        if (l26.secondaryButton !== undefined) {
            this.secondaryButton = l26.secondaryButton;
        }
        if (l26.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = l26.fontColorWithTheme;
        }
        if (l26.theme !== undefined) {
            this.theme = l26.theme;
        }
        if (l26.themeColorMode !== undefined) {
            this.themeColorMode = l26.themeColorMode;
        }
        if (l26.onCheckedChange !== undefined) {
            this.onCheckedChange = l26.onCheckedChange;
        }
        if (l26.contentScroller !== undefined) {
            this.contentScroller = l26.contentScroller;
        }
        if (l26.buttons !== undefined) {
            this.buttons = l26.buttons;
        }
        if (l26.textAlign !== undefined) {
            this.textAlign = l26.textAlign;
        }
        if (l26.marginOffset !== undefined) {
            this.marginOffset = l26.marginOffset;
        }
        if (l26.fontSizeScale !== undefined) {
            this.fontSizeScale = l26.fontSizeScale;
        }
        if (l26.minContentHeight !== undefined) {
            this.minContentHeight = l26.minContentHeight;
        }
        if (l26.textIndex !== undefined) {
            this.textIndex = l26.textIndex;
        }
        if (l26.checkboxIndex !== undefined) {
            this.checkboxIndex = l26.checkboxIndex;
        }
        if (l26.updateTextAlign !== undefined) {
            this.updateTextAlign = l26.updateTextAlign;
        }
    }
    updateStateVars(k26) {
    }
    purgeVariableDependenciesOnElmtId(j26) {
        this.__isChecked.purgeDependencyOnElmtId(j26);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(j26);
        this.__textAlign.purgeDependencyOnElmtId(j26);
        this.__fontSizeScale.purgeDependencyOnElmtId(j26);
        this.__minContentHeight.purgeDependencyOnElmtId(j26);
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
    setController(i26) {
        this.controller = i26;
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(h26) {
        this.__isChecked.set(h26);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(g26) {
        this.__fontColorWithTheme.set(g26);
    }
    get textAlign() {
        return this.__textAlign.get();
    }
    set textAlign(f26) {
        this.__textAlign.set(f26);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(e26) {
        this.__fontSizeScale.set(e26);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(d26) {
        this.__minContentHeight.set(d26);
    }
    textBuilder(t25 = null) {
        this.observeComponentCreation2((b26, c26) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((z25, a26) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
            Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
        }, Scroll);
        this.observeComponentCreation2((x25, y25) => {
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
        this.observeComponentCreation2((u25, v25) => {
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
            Text.onKeyEvent((w25) => {
                if (w25) {
                    resolveKeyEvent(w25, this.contentScroller);
                }
            });
            Text.width('100%');
        }, Text);
        Text.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    checkBoxBuilder(k25 = null) {
        this.observeComponentCreation2((q25, r25) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked));
            Row.accessibilityDescription(this.isChecked ? {
                'id': -1,
                'type': 10003,
                params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10003,
                params: ['sys.string.slider_accessibility_unselectedDesc'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.onClick(() => {
                this.isChecked = !this.isChecked;
                let s25 = ({
                    type: 'announceForAccessibility',
                    bundleName: getContext()?.abilityInfo?.bundleName,
                    triggerAction: 'click',
                    textAnnouncedForAccessibility: this.isChecked ?
                    getContext().resourceManager.getStringSync(125833934) :
                    getContext().resourceManager.getStringSync(125833935)
                });
                accessibility.sendAccessibilityEvent(s25).then(() => {
                    console.info(`Accessibility send event`);
                });
            });
            Row.width('100%');
            Row.padding({ top: 8, bottom: 8 });
        }, Row);
        this.observeComponentCreation2((n25, o25) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isChecked);
            Checkbox.onChange((p25) => {
                this.isChecked = p25;
                if (this.onCheckedChange) {
                    this.onCheckedChange(this.isChecked);
                }
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
        }, Checkbox);
        Checkbox.pop();
        this.observeComponentCreation2((l25, m25) => {
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
    buildContent(j24 = null) {
        {
            this.observeComponentCreation2((k24, l24) => {
                if (l24) {
                    let m24 = new ConfirmDialogContentLayout(this, {
                        minContentHeight: this.__minContentHeight, updateTextAlign: this.updateTextAlign,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((z24, a25) => {
                                ForEach.create();
                                const b25 = c25 => {
                                    const d25 = c25;
                                    this.observeComponentCreation2((e25, f25) => {
                                        If.create();
                                        if (d25 === this.textIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((i25, j25) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.textBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (d25 === this.checkboxIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((g25, h25) => {
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
                                this.forEachUpdateFunction(z24,
                                    [this.textIndex, this.checkboxIndex], b25);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, k24, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 753, col: 5 });
                    ViewPU.create(m24);
                    let n24 = () => {
                        return {
                            minContentHeight: this.minContentHeight,
                            updateTextAlign: this.updateTextAlign,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((o24, p24) => {
                                    ForEach.create();
                                    const q24 = r24 => {
                                        const s24 = r24;
                                        this.observeComponentCreation2((t24, u24) => {
                                            If.create();
                                            if (s24 === this.textIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((x24, y24) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.textBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (s24 === this.checkboxIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((v24, w24) => {
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
                                    this.forEachUpdateFunction(o24,
                                        [this.textIndex, this.checkboxIndex], q24);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    m24.paramsGenerator_ = n24;
                } else {
                    this.updateStateVarsOfChildByElmtId(k24, {});
                }
            }, { name: 'ConfirmDialogContentLayout' });
        }
    }
    initialRender() {
        this.observeComponentCreation2((h24, i24) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((d24, e24) => {
                if (e24) {
                    let f24 = new CustomDialogContentComponent(this, {
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
                    }, undefined, d24, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 769, col: 5 });
                    ViewPU.create(f24);
                    let g24 = () => {
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
                    f24.paramsGenerator_ = g24;
                } else {
                    this.updateStateVarsOfChildByElmtId(d24, {});
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
    constructor(x23, y23, z23, a24 = -1, b24 = undefined, c24) {
        super(x23, z23, a24, c24);
        if (typeof b24 === 'function') {
            this.paramsGenerator_ = b24;
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
        this.setInitiallyProvidedValue(y23);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(w23) {
        if (w23.controller !== undefined) {
            this.controller = w23.controller;
        }
        if (w23.primaryTitle !== undefined) {
            this.primaryTitle = w23.primaryTitle;
        }
        if (w23.secondaryTitle !== undefined) {
            this.secondaryTitle = w23.secondaryTitle;
        }
        if (w23.content !== undefined) {
            this.content = w23.content;
        }
        if (w23.primaryButton !== undefined) {
            this.primaryButton = w23.primaryButton;
        }
        if (w23.secondaryButton !== undefined) {
            this.secondaryButton = w23.secondaryButton;
        }
        if (w23.buttons !== undefined) {
            this.buttons = w23.buttons;
        }
        if (w23.textAlign !== undefined) {
            this.textAlign = w23.textAlign;
        }
        if (w23.contentScroller !== undefined) {
            this.contentScroller = w23.contentScroller;
        }
        if (w23.fontColorWithTheme !== undefined) {
            this.fontColorWithTheme = w23.fontColorWithTheme;
        }
        if (w23.theme !== undefined) {
            this.theme = w23.theme;
        }
        if (w23.themeColorMode !== undefined) {
            this.themeColorMode = w23.themeColorMode;
        }
        if (w23.fontSizeScale !== undefined) {
            this.fontSizeScale = w23.fontSizeScale;
        }
        if (w23.minContentHeight !== undefined) {
            this.minContentHeight = w23.minContentHeight;
        }
    }
    updateStateVars(v23) {
    }
    purgeVariableDependenciesOnElmtId(u23) {
        this.__textAlign.purgeDependencyOnElmtId(u23);
        this.__fontColorWithTheme.purgeDependencyOnElmtId(u23);
        this.__fontSizeScale.purgeDependencyOnElmtId(u23);
        this.__minContentHeight.purgeDependencyOnElmtId(u23);
    }
    aboutToBeDeleted() {
        this.__textAlign.aboutToBeDeleted();
        this.__fontColorWithTheme.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(t23) {
        this.controller = t23;
    }
    get textAlign() {
        return this.__textAlign.get();
    }
    set textAlign(s23) {
        this.__textAlign.set(s23);
    }
    get fontColorWithTheme() {
        return this.__fontColorWithTheme.get();
    }
    set fontColorWithTheme(r23) {
        this.__fontColorWithTheme.set(r23);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(q23) {
        this.__fontSizeScale.set(q23);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(p23) {
        this.__minContentHeight.set(p23);
    }
    initialRender() {
        this.observeComponentCreation2((n23, o23) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((j23, k23) => {
                if (k23) {
                    let l23 = new CustomDialogContentComponent(this, {
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
                    }, undefined, j23, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 827, col: 5 });
                    ViewPU.create(l23);
                    let m23 = () => {
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
                    l23.paramsGenerator_ = m23;
                } else {
                    this.updateStateVarsOfChildByElmtId(j23, {});
                }
            }, { name: 'CustomDialogContentComponent' });
        }
        __Common__.pop();
    }
    AlertDialogContentBuilder(z22 = null) {
        this.observeComponentCreation2((h23, i23) => {
            Column.create();
            Column.margin({ end: LengthMetrics.vp(this.getMargin()) });
        }, Column);
        this.observeComponentCreation2((f23, g23) => {
            Scroll.create(this.contentScroller);
            Scroll.nestedScroll({
                scrollForward: NestedScrollMode.PARALLEL,
                scrollBackward: NestedScrollMode.PARALLEL
            });
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((a23, b23) => {
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
            Text.onSizeChange((d23, e23) => {
                this.updateTextAlign(Number(e23.width));
            });
            Text.onKeyEvent((c23) => {
                if (c23) {
                    resolveKeyEvent(c23, this.contentScroller);
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
    updateTextAlign(y22) {
        this.textAlign = getTextAlign(y22, this.content, `${BODY_L * this.fontSizeScale}vp`);
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
    constructor(s22, t22, u22, v22 = -1, w22 = undefined, x22) {
        super(s22, u22, v22, x22);
        if (typeof w22 === 'function') {
            this.paramsGenerator_ = w22;
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
        this.setInitiallyProvidedValue(t22);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r22) {
        if (r22.controller !== undefined) {
            this.controller = r22.controller;
        }
        if (r22.primaryTitle !== undefined) {
            this.primaryTitle = r22.primaryTitle;
        }
        if (r22.secondaryTitle !== undefined) {
            this.secondaryTitle = r22.secondaryTitle;
        }
        if (r22.contentBuilder !== undefined) {
            this.contentBuilder = r22.contentBuilder;
        }
        if (r22.contentAreaPadding !== undefined) {
            this.contentAreaPadding = r22.contentAreaPadding;
        }
        if (r22.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = r22.localizedContentAreaPadding;
        }
        if (r22.buttons !== undefined) {
            this.buttons = r22.buttons;
        }
        if (r22.theme !== undefined) {
            this.theme = r22.theme;
        }
        if (r22.themeColorMode !== undefined) {
            this.themeColorMode = r22.themeColorMode;
        }
        if (r22.fontSizeScale !== undefined) {
            this.fontSizeScale = r22.fontSizeScale;
        }
        if (r22.minContentHeight !== undefined) {
            this.minContentHeight = r22.minContentHeight;
        }
    }
    updateStateVars(q22) {
    }
    purgeVariableDependenciesOnElmtId(p22) {
        this.__fontSizeScale.purgeDependencyOnElmtId(p22);
        this.__minContentHeight.purgeDependencyOnElmtId(p22);
    }
    aboutToBeDeleted() {
        this.__fontSizeScale.aboutToBeDeleted();
        this.__minContentHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(o22) {
        this.controller = o22;
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(n22) {
        this.__fontSizeScale.set(n22);
    }
    get minContentHeight() {
        return this.__minContentHeight.get();
    }
    set minContentHeight(m22) {
        this.__minContentHeight.set(m22);
    }
    initialRender() {
        this.observeComponentCreation2((k22, l22) => {
            __Common__.create();
            __Common__.constraintSize({ maxHeight: '100%' });
        }, __Common__);
        {
            this.observeComponentCreation2((g22, h22) => {
                if (h22) {
                    let i22 = new CustomDialogContentComponent(this, {
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
                    }, undefined, g22, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 923, col: 5 });
                    ViewPU.create(i22);
                    let j22 = () => {
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
                    i22.paramsGenerator_ = j22;
                } else {
                    this.updateStateVarsOfChildByElmtId(g22, {});
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
    constructor(f22) {
        super(f22);
        this.arg_ = f22;
    }
}
class CustomDialogLayout extends ViewPU {
    constructor(z21, a22, b22, c22 = -1, d22 = undefined, e22) {
        super(z21, b22, c22, e22);
        if (typeof d22 === 'function') {
            this.paramsGenerator_ = d22;
        }
        this.__titleHeight = new SynchedPropertySimpleTwoWayPU(a22.titleHeight, this, 'titleHeight');
        this.__buttonHeight = new SynchedPropertySimpleTwoWayPU(a22.buttonHeight, this, 'buttonHeight');
        this.__titleMinHeight = new SynchedPropertyObjectTwoWayPU(a22.titleMinHeight, this, 'titleMinHeight');
        this.dialogBuilder = this.doNothingBuilder;
        this.titleIndex = 0;
        this.contentIndex = 1;
        this.buttonIndex = 2;
        this.setInitiallyProvidedValue(a22);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y21) {
        if (y21.dialogBuilder !== undefined) {
            this.dialogBuilder = y21.dialogBuilder;
        }
        if (y21.titleIndex !== undefined) {
            this.titleIndex = y21.titleIndex;
        }
        if (y21.contentIndex !== undefined) {
            this.contentIndex = y21.contentIndex;
        }
        if (y21.buttonIndex !== undefined) {
            this.buttonIndex = y21.buttonIndex;
        }
    }
    updateStateVars(x21) {
    }
    purgeVariableDependenciesOnElmtId(w21) {
        this.__titleHeight.purgeDependencyOnElmtId(w21);
        this.__buttonHeight.purgeDependencyOnElmtId(w21);
        this.__titleMinHeight.purgeDependencyOnElmtId(w21);
    }
    aboutToBeDeleted() {
        this.__titleHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__titleMinHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    doNothingBuilder(v21 = null) {
    }
    get titleHeight() {
        return this.__titleHeight.get();
    }
    set titleHeight(u21) {
        this.__titleHeight.set(u21);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(t21) {
        this.__buttonHeight.set(t21);
    }
    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }
    set titleMinHeight(s21) {
        this.__titleMinHeight.set(s21);
    }
    onPlaceChildren(l21, m21, n21) {
        let o21 = 0;
        let p21 = 0;
        for (let q21 = 0; q21 < m21.length; q21++) {
            let r21 = m21[q21];
            r21.layout({ x: o21, y: p21 });
            p21 += r21.measureResult.height;
        }
    }
    onMeasureSize(x20, y20, z20) {
        let a21 = { width: Number(z20.maxWidth), height: 0 };
        let b21 = 3;
        if (y20.length < b21) {
            return a21;
        }
        let c21 = 0;
        let d21 = y20[this.titleIndex];
        let e21 = {
            maxWidth: z20.maxWidth,
            minHeight: this.titleMinHeight,
            maxHeight: z20.maxHeight
        };
        let f21 = d21.measure(e21);
        this.titleHeight = f21.height;
        c21 += this.titleHeight;
        let g21 = y20[this.buttonIndex];
        let h21 = g21.measure(z20);
        this.buttonHeight = h21.height;
        c21 += this.buttonHeight;
        let i21 = y20[this.contentIndex];
        let j21 = {
            maxWidth: z20.maxWidth,
            maxHeight: Number(z20.maxHeight) - c21
        };
        let k21 = i21.measure(j21);
        c21 += k21.height;
        a21.height = c21;
        return a21;
    }
    initialRender() {
        this.dialogBuilder.bind(this)();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class CustomDialogContentComponent extends ViewPU {
    constructor(r20, s20, t20, u20 = -1, v20 = undefined, w20) {
        super(r20, t20, u20, w20);
        if (typeof v20 === 'function') {
            this.paramsGenerator_ = v20;
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
        this.__minContentHeight = new SynchedPropertySimpleTwoWayPU(s20.minContentHeight, this, 'minContentHeight');
        this.__titleHeight = new ObservedPropertySimplePU(0, this, 'titleHeight');
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, 'buttonHeight');
        this.__contentMaxHeight = new ObservedPropertyObjectPU('100%', this, 'contentMaxHeight');
        this.__fontSizeScale = new SynchedPropertySimpleTwoWayPU(s20.fontSizeScale, this, 'fontSizeScale');
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
        this.setInitiallyProvidedValue(s20);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q20) {
        if (q20.controller !== undefined) {
            this.controller = q20.controller;
        }
        if (q20.primaryTitle !== undefined) {
            this.primaryTitle = q20.primaryTitle;
        }
        if (q20.secondaryTitle !== undefined) {
            this.secondaryTitle = q20.secondaryTitle;
        }
        if (q20.localizedContentAreaPadding !== undefined) {
            this.localizedContentAreaPadding = q20.localizedContentAreaPadding;
        }
        if (q20.contentBuilder !== undefined) {
            this.contentBuilder = q20.contentBuilder;
        }
        if (q20.buttons !== undefined) {
            this.buttons = q20.buttons;
        }
        if (q20.contentAreaPadding !== undefined) {
            this.contentAreaPadding = q20.contentAreaPadding;
        }
        if (q20.keyIndex !== undefined) {
            this.keyIndex = q20.keyIndex;
        }
        if (q20.theme !== undefined) {
            this.theme = q20.theme;
        }
        if (q20.themeColorMode !== undefined) {
            this.themeColorMode = q20.themeColorMode;
        }
        if (q20.titleHeight !== undefined) {
            this.titleHeight = q20.titleHeight;
        }
        if (q20.buttonHeight !== undefined) {
            this.buttonHeight = q20.buttonHeight;
        }
        if (q20.contentMaxHeight !== undefined) {
            this.contentMaxHeight = q20.contentMaxHeight;
        }
        if (q20.customStyle !== undefined) {
            this.customStyle = q20.customStyle;
        }
        if (q20.buttonMaxFontSize !== undefined) {
            this.buttonMaxFontSize = q20.buttonMaxFontSize;
        }
        if (q20.buttonMinFontSize !== undefined) {
            this.buttonMinFontSize = q20.buttonMinFontSize;
        }
        if (q20.primaryTitleMaxFontSize !== undefined) {
            this.primaryTitleMaxFontSize = q20.primaryTitleMaxFontSize;
        }
        if (q20.primaryTitleMinFontSize !== undefined) {
            this.primaryTitleMinFontSize = q20.primaryTitleMinFontSize;
        }
        if (q20.secondaryTitleMaxFontSize !== undefined) {
            this.secondaryTitleMaxFontSize = q20.secondaryTitleMaxFontSize;
        }
        if (q20.secondaryTitleMinFontSize !== undefined) {
            this.secondaryTitleMinFontSize = q20.secondaryTitleMinFontSize;
        }
        if (q20.primaryTitleFontColorWithTheme !== undefined) {
            this.primaryTitleFontColorWithTheme = q20.primaryTitleFontColorWithTheme;
        }
        if (q20.secondaryTitleFontColorWithTheme !== undefined) {
            this.secondaryTitleFontColorWithTheme = q20.secondaryTitleFontColorWithTheme;
        }
        if (q20.titleTextAlign !== undefined) {
            this.titleTextAlign = q20.titleTextAlign;
        }
        if (q20.isButtonVertical !== undefined) {
            this.isButtonVertical = q20.isButtonVertical;
        }
        if (q20.titleMinHeight !== undefined) {
            this.titleMinHeight = q20.titleMinHeight;
        }
        if (q20.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = q20.isFollowingSystemFontScale;
        }
        if (q20.appMaxFontScale !== undefined) {
            this.appMaxFontScale = q20.appMaxFontScale;
        }
        if (q20.titleIndex !== undefined) {
            this.titleIndex = q20.titleIndex;
        }
        if (q20.contentIndex !== undefined) {
            this.contentIndex = q20.contentIndex;
        }
        if (q20.buttonIndex !== undefined) {
            this.buttonIndex = q20.buttonIndex;
        }
    }
    updateStateVars(p20) {
    }
    purgeVariableDependenciesOnElmtId(o20) {
        this.__minContentHeight.purgeDependencyOnElmtId(o20);
        this.__titleHeight.purgeDependencyOnElmtId(o20);
        this.__buttonHeight.purgeDependencyOnElmtId(o20);
        this.__contentMaxHeight.purgeDependencyOnElmtId(o20);
        this.__fontSizeScale.purgeDependencyOnElmtId(o20);
        this.__customStyle.purgeDependencyOnElmtId(o20);
        this.__buttonMaxFontSize.purgeDependencyOnElmtId(o20);
        this.__buttonMinFontSize.purgeDependencyOnElmtId(o20);
        this.__primaryTitleMaxFontSize.purgeDependencyOnElmtId(o20);
        this.__primaryTitleMinFontSize.purgeDependencyOnElmtId(o20);
        this.__secondaryTitleMaxFontSize.purgeDependencyOnElmtId(o20);
        this.__secondaryTitleMinFontSize.purgeDependencyOnElmtId(o20);
        this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(o20);
        this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(o20);
        this.__titleTextAlign.purgeDependencyOnElmtId(o20);
        this.__isButtonVertical.purgeDependencyOnElmtId(o20);
        this.__titleMinHeight.purgeDependencyOnElmtId(o20);
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
    set minContentHeight(n20) {
        this.__minContentHeight.set(n20);
    }
    defaultContentBuilder(m20 = null) {
    }
    get titleHeight() {
        return this.__titleHeight.get();
    }
    set titleHeight(l20) {
        this.__titleHeight.set(l20);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(k20) {
        this.__buttonHeight.set(k20);
    }
    get contentMaxHeight() {
        return this.__contentMaxHeight.get();
    }
    set contentMaxHeight(j20) {
        this.__contentMaxHeight.set(j20);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(i20) {
        this.__fontSizeScale.set(i20);
    }
    get customStyle() {
        return this.__customStyle.get();
    }
    set customStyle(h20) {
        this.__customStyle.set(h20);
    }
    get buttonMaxFontSize() {
        return this.__buttonMaxFontSize.get();
    }
    set buttonMaxFontSize(g20) {
        this.__buttonMaxFontSize.set(g20);
    }
    get buttonMinFontSize() {
        return this.__buttonMinFontSize.get();
    }
    set buttonMinFontSize(f20) {
        this.__buttonMinFontSize.set(f20);
    }
    get primaryTitleMaxFontSize() {
        return this.__primaryTitleMaxFontSize.get();
    }
    set primaryTitleMaxFontSize(e20) {
        this.__primaryTitleMaxFontSize.set(e20);
    }
    get primaryTitleMinFontSize() {
        return this.__primaryTitleMinFontSize.get();
    }
    set primaryTitleMinFontSize(d20) {
        this.__primaryTitleMinFontSize.set(d20);
    }
    get secondaryTitleMaxFontSize() {
        return this.__secondaryTitleMaxFontSize.get();
    }
    set secondaryTitleMaxFontSize(c20) {
        this.__secondaryTitleMaxFontSize.set(c20);
    }
    get secondaryTitleMinFontSize() {
        return this.__secondaryTitleMinFontSize.get();
    }
    set secondaryTitleMinFontSize(b20) {
        this.__secondaryTitleMinFontSize.set(b20);
    }
    get primaryTitleFontColorWithTheme() {
        return this.__primaryTitleFontColorWithTheme.get();
    }
    set primaryTitleFontColorWithTheme(a20) {
        this.__primaryTitleFontColorWithTheme.set(a20);
    }
    get secondaryTitleFontColorWithTheme() {
        return this.__secondaryTitleFontColorWithTheme.get();
    }
    set secondaryTitleFontColorWithTheme(z19) {
        this.__secondaryTitleFontColorWithTheme.set(z19);
    }
    get titleTextAlign() {
        return this.__titleTextAlign.get();
    }
    set titleTextAlign(y19) {
        this.__titleTextAlign.set(y19);
    }
    get isButtonVertical() {
        return this.__isButtonVertical.get();
    }
    set isButtonVertical(x19) {
        this.__isButtonVertical.set(x19);
    }
    get titleMinHeight() {
        return this.__titleMinHeight.get();
    }
    set titleMinHeight(w19) {
        this.__titleMinHeight.set(w19);
    }
    initialRender() {
        this.observeComponentCreation2((u19, v19) => {
            WithTheme.create({ theme: this.theme, colorMode: this.themeColorMode });
        }, WithTheme);
        this.observeComponentCreation2((s19, t19) => {
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
        this.observeComponentCreation2((q19, r19) => {
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
                bottom: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_dialog_margin_bottom'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
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
            this.observeComponentCreation2((l7, m7) => {
                if (m7) {
                    let n7 = new CustomDialogLayout(this, {
                        buttonHeight: this.__buttonHeight,
                        titleHeight: this.__titleHeight,
                        titleMinHeight: this.__titleMinHeight,
                        dialogBuilder: () => {
                            this.observeComponentCreation2((o12, r12) => {
                                ForEach.create();
                                const y12 = e19 => {
                                    const f19 = e19;
                                    this.observeComponentCreation2((g19, h19) => {
                                        If.create();
                                        if (f19 === this.titleIndex) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((o19, p19) => {
                                                    WithTheme.create({
                                                        theme: this.theme,
                                                        colorMode: this.themeColorMode
                                                    });
                                                }, WithTheme);
                                                this.titleBuilder.bind(this)();
                                                WithTheme.pop();
                                            });
                                        } else if (f19 === this.contentIndex) {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((m19, n19) => {
                                                    Column.create();
                                                    Column.padding(this.getContentPadding());
                                                }, Column);
                                                this.observeComponentCreation2((k19, l19) => {
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
                                                this.observeComponentCreation2((i19, j19) => {
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
                                this.forEachUpdateFunction(o12, [this.titleIndex, this.contentIndex, this.buttonIndex], y12);
                            }, ForEach);
                            ForEach.pop();
                        }
                    }, undefined, l7, () => {
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1061, col: 11 });
                    ViewPU.create(n7);
                    let o7 = () => {
                        return {
                            buttonHeight: this.buttonHeight,
                            titleHeight: this.titleHeight,
                            titleMinHeight: this.titleMinHeight,
                            dialogBuilder: () => {
                                this.observeComponentCreation2((p7, q7) => {
                                    ForEach.create();
                                    const r7 = s7 => {
                                        const t7 = s7;
                                        this.observeComponentCreation2((u7, v7) => {
                                            If.create();
                                            if (t7 === this.titleIndex) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((k11, v11) => {
                                                        WithTheme.create({
                                                            theme: this.theme,
                                                            colorMode: this.themeColorMode
                                                        });
                                                    }, WithTheme);
                                                    this.titleBuilder.bind(this)();
                                                    WithTheme.pop();
                                                });
                                            } else if (t7 === this.contentIndex) {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((a8, b8) => {
                                                        Column.create();
                                                        Column.padding(this.getContentPadding());
                                                    }, Column);
                                                    this.observeComponentCreation2((y7, z7) => {
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
                                                    this.observeComponentCreation2((w7, x7) => {
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
                                    this.forEachUpdateFunction(p7, [this.titleIndex, this.contentIndex,
                                        this.buttonIndex], r7);
                                }, ForEach);
                                ForEach.pop();
                            }
                        };
                    };
                    n7.paramsGenerator_ = o7;
                } else {
                    this.updateStateVarsOfChildByElmtId(l7, {});
                }
            }, { name: 'CustomDialogLayout' });
        }
        Column.pop();
        Scroll.pop();
        WithTheme.pop();
    }
    onMeasureSize(c7, d7, e7) {
        let f7 = { width: c7.width, height: c7.height };
        let g7 = Number(e7.maxWidth);
        let h7 = Number(e7.maxHeight);
        this.fontSizeScale = this.updateFontScale();
        this.updateFontSize();
        this.isButtonVertical = this.isVerticalAlignButton(g7 - BUTTON_HORIZONTAL_MARGIN * 2);
        this.titleMinHeight = this.getTitleAreaMinHeight();
        let i7 = 0;
        d7.forEach((j7) => {
            this.contentMaxHeight = '100%';
            let k7 = j7.measure(e7);
            if (h7 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
                this.contentMaxHeight = MAX_CONTENT_HEIGHT;
                k7 = j7.measure(e7);
            }
            i7 += k7.height;
        });
        f7.height = i7;
        f7.width = g7;
        return f7;
    }

    aboutToAppear() {
        let a7 = this.getUIContext();
        this.isFollowingSystemFontScale = a7.isFollowingSystemFontScale();
        this.appMaxFontScale = a7.getMaxFontScale();
        this.fontSizeScale = this.updateFontScale();
        if (this.controller && this.customStyle === undefined) {
            let b7 = this.controller;
            if (b7.arg_ && b7.arg_.customStyle && b7.arg_.customStyle === true) {
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
            let y6 = this.getUIContext();
            let z6 = y6.getHostContext()?.config.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(z6, this.appMaxFontScale);
        } catch (v6) {
            let w6 = v6.code;
            let x6 = v6.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${w6}, message: ${x6}`);
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
    titleBuilder(d6 = null) {
        this.observeComponentCreation2((t6, u6) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            Column.width('100%');
            Column.padding(this.getTitleAreaPadding());
        }, Column);
        this.observeComponentCreation2((r6, s6) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((p6, q6) => {
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
        this.observeComponentCreation2((k6, l6) => {
            If.create();
            if (this.primaryTitle && this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m6, n6) => {
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
        this.observeComponentCreation2((h6, i6) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((e6, g6) => {
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
        let c6 = ALERT_TITLE_ALIGNMENT;
        if (c6 === TextAlign.Start) {
            this.titleTextAlign = TextAlign.Start;
        } else if (c6 === TextAlign.Center) {
            this.titleTextAlign = TextAlign.Center;
        } else if (c6 === TextAlign.End) {
            this.titleTextAlign = TextAlign.End;
        } else if (c6 === TextAlign.JUSTIFY) {
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
    ButtonBuilder(v5 = null) {
        this.observeComponentCreation2((a6, b6) => {
            Column.create();
            Column.width('100%');
            Column.padding(this.getOperationAreaPadding());
        }, Column);
        this.observeComponentCreation2((w5, x5) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y5, z5) => {
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
    buildSingleButton(i5, j5 = null) {
        this.observeComponentCreation2((k5, m5) => {
            If.create();
            if (this.isNewPropertiesHighPriority(i5)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t5, u5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.buttons, this.controller);
                        Button.role(i5.role ?? ButtonRole.NORMAL);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (i5.background !== undefined && i5.fontColor !== undefined) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((r5, s5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.buttons, this.controller);
                        Button.backgroundColor(i5.background);
                        Button.fontColor(i5.fontColor);
                        Button.key(`advanced_dialog_button_${this.keyIndex++}`);
                        Button.labelStyle({
                            maxLines: 1,
                            maxFontSize: this.buttonMaxFontSize,
                            minFontSize: this.buttonMinFontSize
                        });
                    }, Button);
                    Button.pop();
                });
            } else if (i5.background !== undefined) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((p5, q5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.buttons, this.controller);
                        Button.backgroundColor(i5.background);
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
                    this.observeComponentCreation2((n5, o5) => {
                        Button.createWithLabel(i5.value);
                        __Button__setButtonProperties(i5, this.buttons, this.controller);
                        Button.fontColor(i5.fontColor);
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
    buildHorizontalAlignButtons(x4 = null) {
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.buttons && this.buttons.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g5, h5) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[0]);
                    this.observeComponentCreation2((a5, b5) => {
                        If.create();
                        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e5, f5) => {
                                    Row.create();
                                    Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                                    Row.justifyContent(FlexAlign.Center);
                                }, Row);
                                this.observeComponentCreation2((c5, d5) => {
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
    buildVerticalAlignButtons(l4 = null) {
        this.observeComponentCreation2((m4, n4) => {
            If.create();
            if (this.buttons) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v4, w4) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((o4, p4) => {
                        ForEach.create();
                        const q4 = (s4, t4) => {
                            const u4 = s4;
                            this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                                HORIZON_BUTTON_MAX_COUNT - t4 - 1 : t4);
                        };
                        this.forEachUpdateFunction(o4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT),
                            q4, (r4) => r4.value.toString(), true, false);
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
    isNewPropertiesHighPriority(k4) {
        if (k4.role === ButtonRole.ERROR) {
            return true;
        }
        if (k4.buttonStyle !== undefined &&
            k4.buttonStyle !== ALERT_BUTTON_STYLE) {
            return true;
        }
        if (k4.background === undefined && k4.fontColor === undefined) {
            return true;
        }
        return false;
    }
    buildButtonWithDivider(x3, z3 = null) {
        this.observeComponentCreation2((a4, b4) => {
            If.create();
            if (this.buttons && this.buttons[x3]) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h4, i4) => {
                        Row.create();
                    }, Row);
                    this.buildSingleButton.bind(this)(this.buttons[x3]);
                    Row.pop();
                    this.observeComponentCreation2((c4, e4) => {
                        If.create();
                        if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - x3 - 1 : x3) <
                            Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f4, g4) => {
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
    isVerticalAlignButton(r3) {
        if (this.buttons) {
            if (this.buttons.length === 1) {
                return false;
            }
            if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
                return true;
            }
            let t3 = false;
            let u3 = vp2px(r3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
                BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
            this.buttons.forEach((v3) => {
                let w3 = measure.measureTextSize({
                    textContent: v3.value,
                    fontSize: this.buttonMaxFontSize
                });
                if (Number(w3.width) > u3) {
                    t3 = true;
                }
            });
            return t3;
        }
        return false;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function __Button__setButtonProperties(o3, p3, q3) {
    Button.onClick(() => {
        if (o3.action) {
            o3.action();
        }
        q3?.close();
    });
    Button.defaultFocus(o3.defaultFocus ? true : isHasDefaultFocus(p3) ? false : true);
    Button.buttonStyle(o3.buttonStyle ?? ALERT_BUTTON_STYLE);
    Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
    Button.type(ButtonType.ROUNDED_RECTANGLE);
}
function isHasDefaultFocus(i3) {
    try {
        let m3 = false;
        i3?.forEach((n3) => {
            if (n3.defaultFocus) {
                m3 = true;
            }
        });
        return m3;
    } catch (j3) {
        let k3 = j3.code;
        let l3 = j3.message;
        hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${k3}, message: ${l3}`);
        return false;
    }
}
function getNumberByResourceId(b3, c3, d3) {
    try {
        let h3 = resourceManager.getSystemResourceManager().getNumber(b3);
        if (h3 > 0 || d3) {
            return h3;
        } else {
            return c3;
        }
    } catch (e3) {
        let f3 = e3.code;
        let g3 = e3.message;
        hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${f3}, message: ${g3}`);
        return c3;
    }
}
function getEnumNumberByResourceId(v2, w2) {
    try {
        let a3 = getContext().resourceManager.getNumber(v2);
        if (a3 > 0) {
            return a3;
        } else {
            return w2;
        }
    } catch (x2) {
        let y2 = x2.code;
        let z2 = x2.message;
        hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${y2}, message: ${z2}`);
        return w2;
    }
}
function getAccessibilityText(o2, p2) {
    try {
        let t2 = getContext().resourceManager.getStringSync(125833934);
        let u2 = '';
        if (typeof o2 === 'string') {
            u2 = o2;
        } else {
            u2 = getContext().resourceManager.getStringSync(o2);
        }
        return p2 ? `${t2},${u2}` : u2;
    } catch (q2) {
        let r2 = q2.code;
        let s2 = q2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${r2}, message: ${s2}`);
        return '';
    }
}
function getTextAlign(j2, k2, l2) {
    let m2 = measure.measureTextSize({
        textContent: k2,
        fontSize: l2,
        constraintWidth: j2,
    });
    let n2 = measure.measureTextSize({
        textContent: k2,
        fontSize: l2,
    });
    if (getTextHeight(m2) <= getTextHeight(n2)) {
        return TextAlign.Center;
    }
    return TextAlign.Start;
}
function getTextHeight(i2) {
    if (i2 && i2.height !== null && i2.height !== undefined) {
        return Number(i2.height);
    }
    return 0;
}
function resolveKeyEvent(g2, h2) {
    if (g2.type === IGNORE_KEY_EVENT_TYPE) {
        return;
    }
    if (g2.keyCode === KEYCODE_UP) {
        h2.scrollPage({ next: false });
        g2.stopPropagation();
    } else if (g2.keyCode === KEYCODE_DOWN) {
        if (h2.isAtEnd()) {
            return;
        } else {
            h2.scrollPage({ next: true });
            g2.stopPropagation();
        }
    }
}

function getCheckTipsAccessibilityText(x1, y1) {
    try {
        let c2 = getContext().resourceManager.getStringSync(125833934);
        let d2 = getContext().resourceManager.getStringSync(125833935);
        let e2 = getContext().resourceManager.getStringSync(125834329);
        let f2 = '';
        if (typeof x1 === 'string') {
            f2 = x1;
        } else {
            f2 = getContext().resourceManager.getStringSync(x1);
        }
        return y1 ? `${c2},${f2},${e2}` :
            `${d2},${f2},${e2}`;
    } catch (z1) {
        let a2 = z1.code;
        let b2 = z1.message;
        hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${a2}, message: ${b2}`);
        return '';
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
                    }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1713, col: 7 });
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