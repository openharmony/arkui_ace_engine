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
 
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const SYMBOL_SIZE = '24vp';
class ButtonGestureModifier {
    constructor(e16) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = e16;
    }
    applyGesture(b16) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            b16.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (b16) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            b16.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(v15, w15, x15, y15 = -1, z15 = undefined, a16) {
        super(v15, x15, y15, a16);
        if (typeof z15 === 'function') {
            this.paramsGenerator_ = z15;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(w15);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u15) {
        if (u15.item !== undefined) {
            this.item = u15.item;
        }
        if (u15.title !== undefined) {
            this.title = u15.title;
        }
        if (u15.subtitle !== undefined) {
            this.subtitle = u15.subtitle;
        }
        if (u15.menuItems !== undefined) {
            this.menuItems = u15.menuItems;
        }
        if (u15.titleMaxWidth !== undefined) {
            this.titleMaxWidth = u15.titleMaxWidth;
        }
        if (u15.backActive !== undefined) {
            this.backActive = u15.backActive;
        }
        if (u15.fontSize !== undefined) {
            this.fontSize = u15.fontSize;
        }
    }
    updateStateVars(t15) {
    }
    purgeVariableDependenciesOnElmtId(s15) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(s15);
        this.__backActive.purgeDependencyOnElmtId(s15);
        this.__fontSize.purgeDependencyOnElmtId(s15);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(r15) {
        this.__titleMaxWidth.set(r15);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(q15) {
        this.__backActive.set(q15);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(p15) {
        this.__fontSize.set(p15);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((i15, j15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i15);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((l15, m15) => {
                let n15 = Number(m15.width);
                if (this.menuItems !== undefined) {
                    let o15 = this.menuItems.length;
                    if (o15 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        n15 = n15 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (o15 > 0) {
                        n15 = n15 - ImageMenuItem.imageHotZoneWidth * o15;
                    }
                }
                this.titleMaxWidth = n15;
                this.titleMaxWidth -= ComposeTitleBar.leftPadding;
                this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                    ComposeTitleBar.portraitImageSize +
                    ComposeTitleBar.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBar.rightPadding;
            });
            if (!j15) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((g15, h15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g15);
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!h15) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((e15, f15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e15);
            Navigator.create();
            Navigator.active(this.backActive);
            if (!f15) {
                Navigator.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Navigator.pop();
        {
            this.observeComponentCreation((y14, z14) => {
                ViewStackProcessor.StartGetAccessRecordingFor(y14);
                if (z14) {
                    let a15 = new ImageMenuItem(this, { symbolItem: {
                        value: PUBLIC_BACK,
                        symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK).fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]),
                        isEnabled: true,
                        action: () => this.backActive = true,
                    },
                        index: -1,
                        isLeftBackFlag: true,
                        isSymbol: true }, undefined, y14, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 100, col: 9 });
                    ViewPU.create(a15);
                    let b15 = () => {
                        return {
                            symbolItem: {
                                value: PUBLIC_BACK,
                                symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK).fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]),
                                isEnabled: true,
                                action: () => this.backActive = true,
                            },
                            index: -1,
                            isLeftBackFlag: true,
                            isSymbol: true
                        };
                    };
                    a15.paramsGenerator_ = b15;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(y14, {});
                }
                ViewStackProcessor.StopGetAccessRecording();
            });
        }
        this.observeComponentCreation((v14, w14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v14);
            Row.create();
            Row.accessibilityGroup(true);
            if (!w14) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((o14, p14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o14);
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t14, u14) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t14);
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBar.portraitImageSize);
                        Image.height(ComposeTitleBar.portraitImageSize);
                        Image.margin({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                        });
                        Image.focusable(false);
                        Image.borderRadius((ImageMenuItem.buttonBorderRadius));
                        if (!u14) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!p14) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((m14, n14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m14);
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!n14) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((c14, d14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c14);
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((k14, l14) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(k14);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!l14) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((i14, j14) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(i14);
                        Text.create(this.title);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                        if (!j14) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!d14) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((s13, t13) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s13);
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((a14, b14) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a14);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!b14) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((y13, z13) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y13);
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                        if (!z13) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!t13) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation((v12, w12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v12);
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((a13, b13) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a13);
                        If.create();
                        if (this.menuItems[0].symbolStyle !== undefined) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                {
                                    this.observeComponentCreation((m13, n13) => {
                                        ViewStackProcessor.StartGetAccessRecordingFor(m13);
                                        if (n13) {
                                            let o13 = new CollapsibleMenuSection(this, {
                                                symbolMenuItems: this.menuItems,
                                                index: 1 + ComposeTitleBar.instanceCount++
                                            }, undefined, m13, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 159, col: 11 });
                                            ViewPU.create(o13);
                                            let p13 = () => {
                                                return {
                                                    symbolMenuItems: this.menuItems,
                                                    index: 1 + ComposeTitleBar.instanceCount++
                                                };
                                            };
                                            o13.paramsGenerator_ = p13;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(m13, {});
                                        }
                                        ViewStackProcessor.StopGetAccessRecording();
                                    });
                                }
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                {
                                    this.observeComponentCreation((e13, f13) => {
                                        ViewStackProcessor.StartGetAccessRecordingFor(e13);
                                        if (f13) {
                                            let g13 = new CollapsibleMenuSection(this, {
                                                menuItems: this.menuItems,
                                                index: 1 + ComposeTitleBar.instanceCount++
                                            }, undefined, e13, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 163, col: 11 });
                                            ViewPU.create(g13);
                                            let h13 = () => {
                                                return {
                                                    menuItems: this.menuItems,
                                                    index: 1 + ComposeTitleBar.instanceCount++
                                                };
                                            };
                                            g13.paramsGenerator_ = h13;
                                        }
                                        else {
                                            this.updateStateVarsOfChildByElmtId(e13, {});
                                        }
                                        ViewStackProcessor.StopGetAccessRecording();
                                    });
                                }
                            });
                        }
                        if (!b13) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!w12) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Flex.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
    constructor(c12, d12, e12, f12 = -1, g12 = undefined, h12) {
        super(c12, e12, f12, h12);
        if (typeof g12 === 'function') {
            this.paramsGenerator_ = g12;
        }
        this.menuItems = [];
        this.symbolMenuItems = [];
        this.item = {
            value: PUBLIC_MORE,
            label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
        };
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
        this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
        this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
        this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(d12.fontSize, this, 'fontSize');
        this.__publicMoreCounter = new ObservedPropertySimplePU(-1, this, 'publicMoreCounter');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let i12 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 223, col: 14 });
                i12.setController(this.dialogController);
                ViewPU.create(i12);
                let j12 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemComposeTitleDialog: this.item,
                        composeTitleBarDialog: this.item.label ? this.item.label : '',
                        fontSize: this.fontSize
                    };
                };
                i12.paramsGenerator_ = j12;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(d12);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b12) {
        if (b12.menuItems !== undefined) {
            this.menuItems = b12.menuItems;
        }
        if (b12.symbolMenuItems !== undefined) {
            this.symbolMenuItems = b12.symbolMenuItems;
        }
        if (b12.item !== undefined) {
            this.item = b12.item;
        }
        if (b12.index !== undefined) {
            this.index = b12.index;
        }
        if (b12.minFontSize !== undefined) {
            this.minFontSize = b12.minFontSize;
        }
        if (b12.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = b12.isFollowingSystemFontScale;
        }
        if (b12.maxFontScale !== undefined) {
            this.maxFontScale = b12.maxFontScale;
        }
        if (b12.systemFontScale !== undefined) {
            this.systemFontScale = b12.systemFontScale;
        }
        if (b12.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = b12.firstFocusableIndex;
        }
        if (b12.isPopupShown !== undefined) {
            this.isPopupShown = b12.isPopupShown;
        }
        if (b12.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = b12.isMoreIconOnFocus;
        }
        if (b12.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = b12.isMoreIconOnHover;
        }
        if (b12.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = b12.isMoreIconOnClick;
        }
        if (b12.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (b12.publicMoreCounter !== undefined) {
            this.publicMoreCounter = b12.publicMoreCounter;
        }
        if (b12.dialogController !== undefined) {
            this.dialogController = b12.dialogController;
        }
        if (b12.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = b12.buttonGestureModifier;
        }
    }
    updateStateVars(a12) {
        this.__fontSize.reset(a12.fontSize);
    }
    purgeVariableDependenciesOnElmtId(z11) {
        this.__isPopupShown.purgeDependencyOnElmtId(z11);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(z11);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(z11);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(z11);
        this.__fontSize.purgeDependencyOnElmtId(z11);
        this.__publicMoreCounter.purgeDependencyOnElmtId(z11);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(z11);
    }
    aboutToBeDeleted() {
        this.__isPopupShown.aboutToBeDeleted();
        this.__isMoreIconOnFocus.aboutToBeDeleted();
        this.__isMoreIconOnHover.aboutToBeDeleted();
        this.__isMoreIconOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__publicMoreCounter.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isPopupShown() {
        return this.__isPopupShown.get();
    }
    set isPopupShown(y11) {
        this.__isPopupShown.set(y11);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(x11) {
        this.__isMoreIconOnFocus.set(x11);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(w11) {
        this.__isMoreIconOnHover.set(w11);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(v11) {
        this.__isMoreIconOnClick.set(v11);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u11) {
        this.__fontSize.set(u11);
    }
    get publicMoreCounter() {
        return this.__publicMoreCounter.get();
    }
    set publicMoreCounter(t11) {
        this.__publicMoreCounter.set(t11);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(s11) {
        this.__buttonGestureModifier.set(s11);
    }
    getMoreIconFgColor() {
        return this.isMoreIconOnClick ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    getMoreIconBgColor() {
        if (this.isMoreIconOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isMoreIconOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return Color.Transparent;
        }
    }
    aboutToAppear() {
        try {
            let r11 = this.getUIContext();
            this.isFollowingSystemFontScale = r11.isFollowingSystemFontScale();
            this.maxFontScale = r11.getMaxFontScale();
        }
        catch (o11) {
            let p11 = o11.code;
            let q11 = o11.message;
            hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}');
        }
        if (this.menuItems) {
            this.menuItems.forEach((m11, n11) => {
                if (m11.isEnabled && this.firstFocusableIndex == -1 &&
                    n11 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + n11 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let k11 = this.getUIContext();
            this.systemFontScale = k11.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (h11) {
            let i11 = h11.code;
            let j11 = h11.message;
            hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}');
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((f11, g11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f11);
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
            if (!g11) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((d11, e11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d11);
            Row.create();
            if (!e11) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((a9, b9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a9);
            If.create();
            if (this.menuItems != undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((f9, g9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f9);
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((p10, q10) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(p10);
                                    ForEach.create();
                                    const r10 = (t10, u10) => {
                                        const v10 = t10;
                                        {
                                            this.observeComponentCreation((x10, y10) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(x10);
                                                if (y10) {
                                                    let z10 = new ImageMenuItem(this, { item: v10, index: this.index * 1000 + u10 + 1 }, undefined, x10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 302, col: 15 });
                                                    ViewPU.create(z10);
                                                    let a11 = () => {
                                                        return {
                                                            item: v10,
                                                            index: this.index * 1000 + u10 + 1
                                                        };
                                                    };
                                                    z10.paramsGenerator_ = a11;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(x10, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(p10, this.menuItems, r10, undefined, true, false);
                                    if (!q10) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((z9, a10) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(z9);
                                    ForEach.create();
                                    const b10 = (d10, e10) => {
                                        const f10 = d10;
                                        {
                                            this.observeComponentCreation((h10, i10) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(h10);
                                                if (i10) {
                                                    let j10 = new ImageMenuItem(this, { item: f10, index: this.index * 1000 + e10 + 1 }, undefined, h10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 307, col: 17 });
                                                    ViewPU.create(j10);
                                                    let k10 = () => {
                                                        return {
                                                            item: f10,
                                                            index: this.index * 1000 + e10 + 1
                                                        };
                                                    };
                                                    j10.paramsGenerator_ = k10;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(h10, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(z9, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), b10, undefined, true, false);
                                    if (!a10) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                                this.observeComponentCreation((n9, o9) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n9);
                                    Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                                    Button.accessibilityText({ 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Button.width(ImageMenuItem.imageHotZoneWidth);
                                    Button.height(ImageMenuItem.imageHotZoneWidth);
                                    Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                                    Button.foregroundColor(this.getMoreIconFgColor());
                                    Button.backgroundColor(this.getMoreIconBgColor());
                                    ViewStackProcessor.visualState('focused');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: ImageMenuItem.focusBorderWidth,
                                        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        style: BorderStyle.Solid
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: 0
                                    });
                                    ViewStackProcessor.visualState();
                                    Button.onFocus(() => this.isMoreIconOnFocus = true);
                                    Button.onBlur(() => this.isMoreIconOnFocus = false);
                                    Button.onHover((y9) => this.isMoreIconOnHover = y9);
                                    Button.onKeyEvent((x9) => {
                                        if (!this.item?.isEnabled) {
                                            return;
                                        }
                                        if (x9.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            x9.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (x9.type == KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (x9.type == KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((w9) => {
                                        if (w9.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (w9.type === TouchType.Up || w9.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize) {
                                                this.dialogController?.close();
                                            }
                                        }
                                    });
                                    Button.onClick(() => {
                                        this.isPopupShown = true;
                                        this.publicMoreCounter += 1;
                                    });
                                    Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                                    Button.bindPopup(this.isPopupShown, {
                                        builder: { builder: this.popupBuilder.bind(this) },
                                        placement: Placement.Bottom,
                                        popupColor: Color.White,
                                        enableArrow: false,
                                        onStateChange: (v9) => {
                                            this.isPopupShown = v9.isVisible;
                                            if (!v9.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                    if (!o9) {
                                        Button.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((l9, m9) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(l9);
                                    SymbolGlyph.create(PUBLIC_MORE);
                                    SymbolGlyph.width(ImageMenuItem.imageSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(ImageMenuItem.imageSize);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter);
                                    if (!m9) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Button.pop();
                            });
                        }
                        if (!g9) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!b9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((x6, y6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x6);
            If.create();
            if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((c7, d7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c7);
                        If.create();
                        if (this.symbolMenuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((m8, n8) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(m8);
                                    ForEach.create();
                                    const o8 = (q8, r8) => {
                                        const s8 = q8;
                                        {
                                            this.observeComponentCreation((u8, v8) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(u8);
                                                if (v8) {
                                                    let w8 = new ImageMenuItem(this, { symbolItem: s8, isSymbol: true, index: this.index * 1000 + r8 + 1 }, undefined, u8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 393, col: 15 });
                                                    ViewPU.create(w8);
                                                    let x8 = () => {
                                                        return {
                                                            symbolItem: s8,
                                                            isSymbol: true,
                                                            index: this.index * 1000 + r8 + 1
                                                        };
                                                    };
                                                    w8.paramsGenerator_ = x8;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(u8, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(m8, this.symbolMenuItems, o8, undefined, true, false);
                                    if (!n8) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((w7, x7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(w7);
                                    ForEach.create();
                                    const y7 = (a8, b8) => {
                                        const c8 = a8;
                                        {
                                            this.observeComponentCreation((e8, f8) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(e8);
                                                if (f8) {
                                                    let g8 = new ImageMenuItem(this, { symbolItem: c8, isSymbol: true, index: this.index * 1000 + b8 + 1 }, undefined, e8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 398, col: 17 });
                                                    ViewPU.create(g8);
                                                    let h8 = () => {
                                                        return {
                                                            symbolItem: c8,
                                                            isSymbol: true,
                                                            index: this.index * 1000 + b8 + 1
                                                        };
                                                    };
                                                    g8.paramsGenerator_ = h8;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(e8, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(w7, this.symbolMenuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), y7, undefined, true, false);
                                    if (!x7) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                                this.observeComponentCreation((k7, l7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k7);
                                    Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                                    Button.width(ImageMenuItem.imageHotZoneWidth);
                                    Button.height(ImageMenuItem.imageHotZoneWidth);
                                    Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                                    Button.foregroundColor(this.getMoreIconFgColor());
                                    Button.backgroundColor(this.getMoreIconBgColor());
                                    ViewStackProcessor.visualState('focused');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: ImageMenuItem.focusBorderWidth,
                                        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        style: BorderStyle.Solid
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: 0
                                    });
                                    ViewStackProcessor.visualState();
                                    Button.onFocus(() => this.isMoreIconOnFocus = true);
                                    Button.onBlur(() => this.isMoreIconOnFocus = false);
                                    Button.onHover((v7) => this.isMoreIconOnHover = v7);
                                    Button.onKeyEvent((u7) => {
                                        if (u7.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            u7.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (u7.type == KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (u7.type == KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((t7) => {
                                        if (t7.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (t7.type === TouchType.Up || t7.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize) {
                                                this.dialogController?.close();
                                            }
                                        }
                                    });
                                    Button.onClick(() => {
                                        this.isPopupShown = true;
                                        this.publicMoreCounter += 1;
                                    });
                                    Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                                    Button.bindPopup(this.isPopupShown, {
                                        builder: { builder: this.popupBuilder.bind(this) },
                                        placement: Placement.Bottom,
                                        popupColor: Color.White,
                                        enableArrow: false,
                                        onStateChange: (s7) => {
                                            this.isPopupShown = s7.isVisible;
                                            if (!s7.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                    if (!l7) {
                                        Button.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((i7, j7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(i7);
                                    SymbolGlyph.create(PUBLIC_MORE);
                                    SymbolGlyph.width(ImageMenuItem.imageSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.height(ImageMenuItem.imageSize);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter);
                                    if (!j7) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Button.pop();
                            });
                        }
                        if (!d7) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!y6) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(a5 = null) {
        this.observeComponentCreation((q6, r6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q6);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                this.firstFocusableIndex);
            });
            if (!r6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((x5, y5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x5);
            If.create();
            if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((c6, d6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c6);
                        ForEach.create();
                        const e6 = (g6, h6) => {
                            const i6 = g6;
                            {
                                this.observeComponentCreation((k6, l6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k6);
                                    if (l6) {
                                        let m6 = new ImageMenuItem(this, { symbolItem: i6, isSymbol: true, index: this.index * 1000 +
                                        CollapsibleMenuSection.maxCountOfVisibleItems + h6, isPopup: true }, undefined, k6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 490, col: 13 });
                                        ViewPU.create(m6);
                                        let n6 = () => {
                                            return {
                                                symbolItem: i6,
                                                isSymbol: true,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + h6,
                                                isPopup: true
                                            };
                                        };
                                        m6.paramsGenerator_ = n6;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(k6, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(c6, this.symbolMenuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.symbolMenuItems.length), e6, undefined, true, false);
                        if (!d6) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!y5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((e5, f5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e5);
            If.create();
            if (this.menuItems != undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((j5, k5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j5);
                        ForEach.create();
                        const l5 = (n5, o5) => {
                            const p5 = n5;
                            {
                                this.observeComponentCreation((r5, s5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r5);
                                    if (s5) {
                                        let t5 = new ImageMenuItem(this, { item: p5, isSymbol: true, index: this.index * 1000 +
                                        CollapsibleMenuSection.maxCountOfVisibleItems + o5, isPopup: true }, undefined, r5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 499, col: 13 });
                                        ViewPU.create(t5);
                                        let u5 = () => {
                                            return {
                                                item: p5,
                                                isSymbol: true,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + o5,
                                                isPopup: true
                                            };
                                        };
                                        t5.paramsGenerator_ = u5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(r5, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(j5, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), l5, undefined, true, false);
                        if (!k5) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!f5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
    constructor(q4, r4, s4, t4 = -1, u4 = undefined, v4) {
        super(q4, s4, t4, v4);
        if (typeof u4 === 'function') {
            this.paramsGenerator_ = u4;
        }
        this.isLeftBackFlag = false;
        this.item = {};
        this.symbolItem = {};
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = false;
        this.isSymbol = false;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__publicBackCounter = new ObservedPropertySimplePU(-1, this, 'publicBackCounter');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(r4.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let w4 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    itemComposeTitleSymbolDialog: this.symbolItem,
                    isSymbol: this.isSymbol,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    composeTitleBarSymbolDialog: this.symbolItem.label ? this.symbolItem.label : this.textDialog(),
                    fontSize: this.fontSize
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 541, col: 14 });
                w4.setController(this.dialogController);
                ViewPU.create(w4);
                let x4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemComposeTitleDialog: this.item,
                        itemComposeTitleSymbolDialog: this.symbolItem,
                        isSymbol: this.isSymbol,
                        composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        composeTitleBarSymbolDialog: this.symbolItem.label ? this.symbolItem.label : this.textDialog(),
                        fontSize: this.fontSize
                    };
                };
                w4.paramsGenerator_ = x4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(r4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p4) {
        if (p4.isLeftBackFlag !== undefined) {
            this.isLeftBackFlag = p4.isLeftBackFlag;
        }
        if (p4.item !== undefined) {
            this.item = p4.item;
        }
        if (p4.symbolItem !== undefined) {
            this.symbolItem = p4.symbolItem;
        }
        if (p4.index !== undefined) {
            this.index = p4.index;
        }
        if (p4.minFontSize !== undefined) {
            this.minFontSize = p4.minFontSize;
        }
        if (p4.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = p4.isFollowingSystemFontScale;
        }
        if (p4.maxFontScale !== undefined) {
            this.maxFontScale = p4.maxFontScale;
        }
        if (p4.systemFontScale !== undefined) {
            this.systemFontScale = p4.systemFontScale;
        }
        if (p4.isPopup !== undefined) {
            this.isPopup = p4.isPopup;
        }
        if (p4.isSymbol !== undefined) {
            this.isSymbol = p4.isSymbol;
        }
        if (p4.isOnFocus !== undefined) {
            this.isOnFocus = p4.isOnFocus;
        }
        if (p4.isOnHover !== undefined) {
            this.isOnHover = p4.isOnHover;
        }
        if (p4.isOnClick !== undefined) {
            this.isOnClick = p4.isOnClick;
        }
        if (p4.publicBackCounter !== undefined) {
            this.publicBackCounter = p4.publicBackCounter;
        }
        if (p4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (p4.dialogController !== undefined) {
            this.dialogController = p4.dialogController;
        }
        if (p4.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = p4.buttonGestureModifier;
        }
    }
    updateStateVars(o4) {
        this.__fontSize.reset(o4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(n4) {
        this.__isOnFocus.purgeDependencyOnElmtId(n4);
        this.__isOnHover.purgeDependencyOnElmtId(n4);
        this.__isOnClick.purgeDependencyOnElmtId(n4);
        this.__publicBackCounter.purgeDependencyOnElmtId(n4);
        this.__fontSize.purgeDependencyOnElmtId(n4);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(n4);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__publicBackCounter.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(m4) {
        this.__isOnFocus.set(m4);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(l4) {
        this.__isOnHover.set(l4);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(k4) {
        this.__isOnClick.set(k4);
    }
    get publicBackCounter() {
        return this.__publicBackCounter.get();
    }
    set publicBackCounter(j4) {
        this.__publicBackCounter.set(j4);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(i4) {
        this.__fontSize.set(i4);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(h4) {
        this.__buttonGestureModifier.set(h4);
    }
    textDialog() {
        if (this.isSymbol) {
            if (this.symbolItem.value === PUBLIC_BACK) {
                return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            }
            else if (this.symbolItem.value === PUBLIC_MORE) {
                return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            }
            else {
                return this.item.label ? this.item.label : '';
            }
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    toStringFormat(c4) {
        if (typeof c4 === 'string') {
            return c4;
        }
        else if (typeof c4 === 'undefined') {
            return '';
        }
        else {
            let d4 = '';
            try {
                d4 = getContext()?.resourceManager?.getStringSync(c4);
            }
            catch (e4) {
                let f4 = e4?.code;
                let g4 = e4?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${f4},message:${g4}`);
            }
            return d4;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_BACK) {
            return this.toStringFormat({ 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        else if (this.item.value === PUBLIC_MORE) {
            return this.toStringFormat({ 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        }
        else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    onPlaceChildren(x3, y3, z3) {
        y3.forEach((b4) => {
            b4.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    getFgColor() {
        return this.isOnClick
            ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    getBgColor() {
        if (this.isOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return Color.Transparent;
        }
    }
    aboutToAppear() {
        try {
            let w3 = this.getUIContext();
            this.isFollowingSystemFontScale = w3.isFollowingSystemFontScale();
            this.maxFontScale = w3.getMaxFontScale();
        }
        catch (t3) {
            let u3 = t3.code;
            let v3 = t3.message;
            hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}');
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let s3 = this.getUIContext();
            this.systemFontScale = s3.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (p3) {
            let q3 = p3.code;
            let r3 = p3.message;
            hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}');
            return 1;
        }
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e3, f3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e3);
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.accessibilityText(this.getAccessibilityReadText());
            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
            Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneWidth);
            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            Button.opacity(this.item?.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: ImageMenuItem.focusBorderWidth,
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: 0
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((o3) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnHover = o3;
            });
            Button.onKeyEvent((n3) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (n3.keyCode !== KeyCode.KEYCODE_ENTER &&
                    n3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (n3.type == KeyType.Down) {
                    this.isOnClick = true;
                }
                if (n3.type == KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((m3) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (m3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (m3.type === TouchType.Up || m3.type === TouchType.Cancel) {
                    this.isOnClick = false;
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.close();
                    }
                }
            });
            Button.onClick(() => {
                if (this.isLeftBackFlag) {
                    this.publicBackCounter += 1;
                }
                if (this.isSymbol) {
                    return this.symbolItem.isEnabled && this.symbolItem.action?.();
                }
                else {
                    return this.item.isEnabled && this.item.action?.();
                }
            });
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            if (!f3) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((u2, v2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u2);
            If.create();
            if (this.isSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((c3, d3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c3);
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.symbolItem.symbolStyle);
                        SymbolGlyph.fontSize(SYMBOL_SIZE);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.symbolItem?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicBackCounter);
                        if (!d3) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((y2, z2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y2);
                        Image.create(this.item?.value);
                        Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
                        Image.width(ImageMenuItem.imageSize);
                        Image.draggable(false);
                        Image.height(ImageMenuItem.imageSize);
                        Image.focusable(this.item?.isEnabled);
                        Image.key(ImageMenuItem.focusablePrefix + this.index);
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!z2) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            if (!v2) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Button.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class ComposeTitleBarDialog extends ViewPU {
    constructor(k2, l2, m2, n2 = -1, o2 = undefined, p2) {
        super(k2, m2, n2, p2);
        if (typeof o2 === 'function') {
            this.paramsGenerator_ = o2;
        }
        this.itemComposeTitleDialog = {};
        this.itemComposeTitleSymbolDialog = {};
        this.isSymbol = false;
        this.callbackId = undefined;
        this.composeTitleBarDialog = '';
        this.composeTitleBarSymbolDialog = '';
        this.mainWindowStage = undefined;
        this.controller = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.setInitiallyProvidedValue(l2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j2) {
        if (j2.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = j2.itemComposeTitleDialog;
        }
        if (j2.itemComposeTitleSymbolDialog !== undefined) {
            this.itemComposeTitleSymbolDialog = j2.itemComposeTitleSymbolDialog;
        }
        if (j2.isSymbol !== undefined) {
            this.isSymbol = j2.isSymbol;
        }
        if (j2.callbackId !== undefined) {
            this.callbackId = j2.callbackId;
        }
        if (j2.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = j2.composeTitleBarDialog;
        }
        if (j2.composeTitleBarSymbolDialog !== undefined) {
            this.composeTitleBarSymbolDialog = j2.composeTitleBarSymbolDialog;
        }
        if (j2.mainWindowStage !== undefined) {
            this.mainWindowStage = j2.mainWindowStage;
        }
        if (j2.controller !== undefined) {
            this.controller = j2.controller;
        }
        if (j2.minFontSize !== undefined) {
            this.minFontSize = j2.minFontSize;
        }
        if (j2.maxFontSize !== undefined) {
            this.maxFontSize = j2.maxFontSize;
        }
        if (j2.screenWidth !== undefined) {
            this.screenWidth = j2.screenWidth;
        }
        if (j2.verticalScreenLines !== undefined) {
            this.verticalScreenLines = j2.verticalScreenLines;
        }
        if (j2.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = j2.horizontalsScreenLines;
        }
        if (j2.fontSize !== undefined) {
            this.fontSize = j2.fontSize;
        }
        if (j2.maxLines !== undefined) {
            this.maxLines = j2.maxLines;
        }
        if (j2.cancel !== undefined) {
            this.cancel = j2.cancel;
        }
        if (j2.confirm !== undefined) {
            this.confirm = j2.confirm;
        }
    }
    updateStateVars(i2) {
    }
    purgeVariableDependenciesOnElmtId(h2) {
        this.__mainWindow.purgeDependencyOnElmtId(h2);
        this.__fontSize.purgeDependencyOnElmtId(h2);
        this.__maxLines.purgeDependencyOnElmtId(h2);
        this.__windowStandardHeight.purgeDependencyOnElmtId(h2);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(g2) {
        this.controller = g2;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(f2) {
        this.__mainWindow.set(f2);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(e2) {
        this.__fontSize.set(e2);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(d2) {
        this.__maxLines.set(d2);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(c2) {
        this.__windowStandardHeight.set(c2);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e, f) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            if (this.isSymbol) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((g1, h1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g1);
                        If.create();
                        if (this.composeTitleBarSymbolDialog) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((a2, b2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(a2);
                                    Column.create();
                                    Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                                    Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                                    Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                    Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                    Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!b2) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((y1, z1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(y1);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleSymbolDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                                    });
                                    if (!z1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((w1, x1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(w1);
                                    Column.create();
                                    Column.width('100%');
                                    Column.padding({
                                        left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                                    });
                                    if (!x1) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((u1, v1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(u1);
                                    Text.create(this.composeTitleBarSymbolDialog);
                                    Text.fontSize(TEXT_EDITABLE_DIALOG);
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.maxLines(this.maxLines);
                                    Text.width('100%');
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!v1) {
                                        Text.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Text.pop();
                                Column.pop();
                                Column.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((n1, o1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n1);
                                    Column.create();
                                    Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                                    Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                                    Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                    Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                    Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Column.justifyContent(FlexAlign.Center);
                                    if (!o1) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((l1, m1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(l1);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleSymbolDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                                    });
                                    if (!m1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Column.pop();
                            });
                        }
                        if (!h1) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((i, j) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(i);
                        If.create();
                        if (this.composeTitleBarDialog) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((c1, d1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(c1);
                                    Column.create();
                                    Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                                    Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                                    Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                    Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                    Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!d1) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((a1, b1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(a1);
                                    Image.create(this.itemComposeTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                                    });
                                    if (!b1) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((y, z) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(y);
                                    Column.create();
                                    Column.width('100%');
                                    Column.padding({
                                        left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                                    });
                                    if (!z) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((w, x) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(w);
                                    Text.create(this.composeTitleBarSymbolDialog);
                                    Text.fontSize(TEXT_EDITABLE_DIALOG);
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                    Text.maxLines(this.maxLines);
                                    Text.width('100%');
                                    Text.textAlign(TextAlign.Center);
                                    Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!x) {
                                        Text.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Text.pop();
                                Column.pop();
                                Column.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((p, q) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(p);
                                    Column.create();
                                    Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                                    Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                                    Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                    Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                    Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Column.justifyContent(FlexAlign.Center);
                                    if (!q) {
                                        Column.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((n, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n);
                                    Image.create(this.itemComposeTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!o) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Column.pop();
                            });
                        }
                        if (!j) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            if (!f) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    async aboutToAppear() {
        let a = this.getUIContext().getHostContext();
        this.mainWindowStage = a.windowStage.getMainWindowSync();
        let b = this.mainWindowStage.getWindowProperties();
        let c = b.windowRect;
        if (px2vp(c.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        }
        else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
export default {
    ComposeTitleBar: ComposeTitleBar
};
