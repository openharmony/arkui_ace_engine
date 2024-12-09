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
 
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const MeasureText = requireNapi('measure');
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
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
export class TabTitleBar extends ViewPU {
    constructor(v15, w15, x15, y15 = -1, z15 = undefined, a16) {
        super(v15, x15, y15, a16);
        if (typeof z15 === 'function') {
            this.paramsGenerator_ = z15;
        }
        this.tabItems = [];
        this.menuItems = [];
        this.swiperContent = undefined;
        this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
        this.__currentIndex = new ObservedPropertySimplePU(0, this, 'currentIndex');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.menuSectionWidth = 0;
        this.tabOffsets = [];
        this.imageWidths = [];
        this.scroller = new Scroller();
        this.swiperController = new SwiperController();
        this.settings = new RenderingContextSettings(true);
        this.leftContext2D = new CanvasRenderingContext2D(this.settings);
        this.rightContext2D = new CanvasRenderingContext2D(this.settings);
        this.setInitiallyProvidedValue(w15);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u15) {
        if (u15.tabItems !== undefined) {
            this.tabItems = u15.tabItems;
        }
        if (u15.menuItems !== undefined) {
            this.menuItems = u15.menuItems;
        }
        if (u15.swiperContent !== undefined) {
            this.swiperContent = u15.swiperContent;
        }
        if (u15.tabWidth !== undefined) {
            this.tabWidth = u15.tabWidth;
        }
        if (u15.currentIndex !== undefined) {
            this.currentIndex = u15.currentIndex;
        }
        if (u15.fontSize !== undefined) {
            this.fontSize = u15.fontSize;
        }
        if (u15.menuSectionWidth !== undefined) {
            this.menuSectionWidth = u15.menuSectionWidth;
        }
        if (u15.tabOffsets !== undefined) {
            this.tabOffsets = u15.tabOffsets;
        }
        if (u15.imageWidths !== undefined) {
            this.imageWidths = u15.imageWidths;
        }
        if (u15.scroller !== undefined) {
            this.scroller = u15.scroller;
        }
        if (u15.swiperController !== undefined) {
            this.swiperController = u15.swiperController;
        }
        if (u15.settings !== undefined) {
            this.settings = u15.settings;
        }
        if (u15.leftContext2D !== undefined) {
            this.leftContext2D = u15.leftContext2D;
        }
        if (u15.rightContext2D !== undefined) {
            this.rightContext2D = u15.rightContext2D;
        }
    }
    updateStateVars(t15) {
    }
    purgeVariableDependenciesOnElmtId(s15) {
        this.__tabWidth.purgeDependencyOnElmtId(s15);
        this.__currentIndex.purgeDependencyOnElmtId(s15);
        this.__fontSize.purgeDependencyOnElmtId(s15);
    }
    aboutToBeDeleted() {
        this.__tabWidth.aboutToBeDeleted();
        this.__currentIndex.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get tabWidth() {
        return this.__tabWidth.get();
    }
    set tabWidth(r15) {
        this.__tabWidth.set(r15);
    }
    get currentIndex() {
        return this.__currentIndex.get();
    }
    set currentIndex(q15) {
        this.__currentIndex.set(q15);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(p15) {
        this.__fontSize.set(p15);
    }
    GradientMask(b15, c15, d15, e15, f15, g15 = null) {
        this.observeComponentCreation((n15, o15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n15);
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(TabTitleBar.gradientMaskWidth);
            Column.height(TabTitleBar.totalHeight);
            if (!o15) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((j15, k15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j15);
            Canvas.create(b15);
            Canvas.width(TabTitleBar.gradientMaskWidth);
            Canvas.height(TabTitleBar.totalHeight);
            Canvas.onReady(() => {
                let m15 = b15.createLinearGradient(c15, d15, e15, f15);
                m15.addColorStop(0.0, '#ffffffff');
                m15.addColorStop(1, '#00ffffff');
                b15.fillStyle = m15;
                b15.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
            });
            if (!k15) {
                Canvas.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        Canvas.pop();
        Column.pop();
    }
    emptyBuilder(a15 = null) {
    }
    aboutToAppear() {
        if (!this.swiperContent) {
            this.swiperContent = this.emptyBuilder;
        }
        this.tabItems.forEach((z14) => {
            this.imageWidths.push(0);
        });
        this.loadOffsets();
    }
    loadOffsets() {
        this.tabOffsets.length = 0;
        let u14 = 0;
        this.tabOffsets.push(u14);
        u14 += TabContentItem.marginFirst;
        this.tabItems.forEach((w14, x14) => {
            if (w14.icon !== undefined || w14.symbolIcon !== undefined) {
                if (Math.abs(this.imageWidths[x14]) > TabContentItem.imageHotZoneWidth) {
                    u14 += this.imageWidths[x14];
                }
                else {
                    u14 += TabContentItem.imageHotZoneWidth;
                }
            }
            else {
                u14 += TabContentItem.paddingLeft;
                u14 += px2vp(MeasureText.measureText({
                    textContent: w14.title.toString(),
                    fontSize: 18,
                    fontWeight: FontWeight.Medium,
                }));
                u14 += TabContentItem.paddingRight;
            }
            this.tabOffsets.push(u14);
        });
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((s14, t14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s14);
            Column.create();
            if (!t14) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((n14, o14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n14);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Flex.onAreaChange((q14, r14) => {
                this.tabWidth = Number(r14.width) - this.menuSectionWidth;
            });
            if (!o14) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((l14, m14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l14);
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            if (!m14) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((j14, k14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j14);
            Stack.create({ alignContent: Alignment.Start });
            if (!k14) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((h14, i14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h14);
            Column.create();
            if (!i14) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((f14, g14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f14);
            List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
            List.width('100%');
            List.height(TabTitleBar.totalHeight);
            List.constraintSize({ maxWidth: this.tabWidth });
            List.edgeEffect(EdgeEffect.Spring);
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            if (!g14) {
                List.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((b13, c13) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b13);
            ForEach.create();
            const d13 = (f13, g13) => {
                const h13 = f13;
                {
                    const i13 = (d14, e14) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d14);
                        j13(d14, e14);
                        if (!e14) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const j13 = (b14, c14) => {
                        ListItem.create(k13, true);
                    };
                    const k13 = (o13, p13) => {
                        i13(o13, p13);
                        this.updateFuncByElmtId.set(o13, i13);
                        {
                            this.observeComponentCreation((r13, s13) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(r13);
                                if (s13) {
                                    let t13 = new TabContentItem(this, {
                                        item: h13,
                                        index: g13,
                                        maxIndex: this.tabItems.length - 1,
                                        currentIndex: this.currentIndex,
                                        onCustomClick: (a14) => this.currentIndex = a14,
                                        onImageComplete: (z13) => {
                                            this.imageWidths[g13] = z13;
                                            this.loadOffsets();
                                        }
                                    }, undefined, r13, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 175, col: 21 });
                                    ViewPU.create(t13);
                                    let u13 = () => {
                                        return {
                                            item: h13,
                                            index: g13,
                                            maxIndex: this.tabItems.length - 1,
                                            currentIndex: this.currentIndex,
                                            onCustomClick: (y13) => this.currentIndex = y13,
                                            onImageComplete: (x13) => {
                                                this.imageWidths[g13] = x13;
                                                this.loadOffsets();
                                            }
                                        };
                                    };
                                    t13.paramsGenerator_ = u13;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(r13, {
                                        currentIndex: this.currentIndex
                                    });
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        }
                        ListItem.pop();
                    };
                    this.observeComponentCreation(i13);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(b13, this.tabItems, d13, undefined, true, false);
            if (!c13) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        List.pop();
        Column.pop();
        this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.observeComponentCreation((k12, l12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k12);
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((w12, x12) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w12);
                        __Common__.create();
                        __Common__.height(TabTitleBar.totalHeight);
                        __Common__.onAreaChange((z12, a13) => {
                            this.menuSectionWidth = Number(a13.width);
                        });
                        if (!x12) {
                            __Common__.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    {
                        this.observeComponentCreation((q12, r12) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(q12);
                            if (r12) {
                                let s12 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ }, undefined, q12, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 205, col: 11 });
                                ViewPU.create(s12);
                                let t12 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + TabTitleBar.instanceCount++
                                    };
                                };
                                s12.paramsGenerator_ = t12;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q12, {});
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!l12) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Flex.pop();
        this.observeComponentCreation((i12, j12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i12);
            Column.create();
            if (!j12) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((c12, d12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c12);
            Swiper.create(this.swiperController);
            Swiper.index(this.currentIndex);
            Swiper.itemSpace(0);
            Swiper.indicator(false);
            Swiper.width('100%');
            Swiper.height('100%');
            Swiper.curve(Curve.Friction);
            Swiper.onChange((g12) => {
                const h12 = this.tabOffsets[g12] + TabTitleBar.correctionOffset;
                this.currentIndex = g12;
                this.scroller.scrollTo({
                    xOffset: h12 > 0 ? h12 : 0,
                    yOffset: 0,
                    animation: {
                        duration: 300,
                        curve: Curve.EaseInOut
                    }
                });
            });
            Swiper.onAppear(() => {
                this.scroller.scrollToIndex(this.currentIndex);
                this.scroller.scrollBy(TabTitleBar.correctionOffset, 0);
            });
            if (!d12) {
                Swiper.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.swiperContent.bind(this)();
        Swiper.pop();
        Column.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
TabTitleBar.totalHeight = 56;
TabTitleBar.correctionOffset = -40.0;
TabTitleBar.gradientMaskWidth = 24;
TabTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
    constructor(i11, j11, k11, l11 = -1, m11 = undefined, n11) {
        super(i11, k11, l11, n11);
        if (typeof m11 === 'function') {
            this.paramsGenerator_ = m11;
        }
        this.menuItems = [];
        this.index = 0;
        this.item = {
            value: PUBLIC_MORE,
            symbolValue: new SymbolGlyphModifier(PUBLIC_MORE),
            label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
        this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
        this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
        this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(j11.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let o11 = new TabTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    tabTitleDialog: this.item,
                    tabTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 274, col: 14 });
                o11.setController(this.dialogController);
                ViewPU.create(o11);
                let p11 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        tabTitleDialog: this.item,
                        tabTitleBarDialog: this.item.label ? this.item.label : '',
                        fontSize: this.fontSize
                    };
                };
                o11.paramsGenerator_ = p11;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(j11);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(h11) {
        if (h11.menuItems !== undefined) {
            this.menuItems = h11.menuItems;
        }
        if (h11.index !== undefined) {
            this.index = h11.index;
        }
        if (h11.item !== undefined) {
            this.item = h11.item;
        }
        if (h11.minFontSize !== undefined) {
            this.minFontSize = h11.minFontSize;
        }
        if (h11.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = h11.isFollowingSystemFontScale;
        }
        if (h11.maxFontScale !== undefined) {
            this.maxFontScale = h11.maxFontScale;
        }
        if (h11.systemFontScale !== undefined) {
            this.systemFontScale = h11.systemFontScale;
        }
        if (h11.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = h11.firstFocusableIndex;
        }
        if (h11.isPopupShown !== undefined) {
            this.isPopupShown = h11.isPopupShown;
        }
        if (h11.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = h11.isMoreIconOnFocus;
        }
        if (h11.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = h11.isMoreIconOnHover;
        }
        if (h11.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = h11.isMoreIconOnClick;
        }
        if (h11.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (h11.dialogController !== undefined) {
            this.dialogController = h11.dialogController;
        }
        if (h11.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = h11.buttonGestureModifier;
        }
    }
    updateStateVars(g11) {
        this.__fontSize.reset(g11.fontSize);
    }
    purgeVariableDependenciesOnElmtId(f11) {
        this.__isPopupShown.purgeDependencyOnElmtId(f11);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(f11);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(f11);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(f11);
        this.__fontSize.purgeDependencyOnElmtId(f11);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(f11);
    }
    aboutToBeDeleted() {
        this.__isPopupShown.aboutToBeDeleted();
        this.__isMoreIconOnFocus.aboutToBeDeleted();
        this.__isMoreIconOnHover.aboutToBeDeleted();
        this.__isMoreIconOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isPopupShown() {
        return this.__isPopupShown.get();
    }
    set isPopupShown(e11) {
        this.__isPopupShown.set(e11);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(d11) {
        this.__isMoreIconOnFocus.set(d11);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(c11) {
        this.__isMoreIconOnHover.set(c11);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(b11) {
        this.__isMoreIconOnClick.set(b11);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a11) {
        this.__fontSize.set(a11);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(z10) {
        this.__buttonGestureModifier.set(z10);
    }
    getMoreIconFgColor() {
        return this.isMoreIconOnClick
            ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
            let y10 = this.getUIContext();
            this.isFollowingSystemFontScale = y10.isFollowingSystemFontScale();
            this.maxFontScale = y10.getMaxFontScale();
        }
        catch (v10) {
            let w10 = v10.code;
            let x10 = v10.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${w10}, message: ${x10}`);
        }
        this.menuItems.forEach((t10, u10) => {
            if (t10.isEnabled && this.firstFocusableIndex === -1 &&
                u10 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + u10 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let r10 = this.getUIContext();
        this.systemFontScale = r10.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((p10, q10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p10);
            Column.create();
            Column.height('100%');
            Column.justifyContent(FlexAlign.Center);
            if (!q10) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((n10, o10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n10);
            Row.create();
            if (!o10) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((p8, q8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p8);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((z9, a10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z9);
                        ForEach.create();
                        const b10 = (d10, e10) => {
                            const f10 = d10;
                            {
                                this.observeComponentCreation((h10, i10) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(h10);
                                    if (i10) {
                                        let j10 = new ImageMenuItem(this, { item: f10, index: this.index * 1000 + e10 + 1 }, undefined, h10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 343, col: 13 });
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
                        this.forEachUpdateFunction(z9, this.menuItems, b10, undefined, true, false);
                        if (!a10) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((j9, k9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j9);
                        ForEach.create();
                        const l9 = (n9, o9) => {
                            const p9 = n9;
                            {
                                this.observeComponentCreation((r9, s9) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r9);
                                    if (s9) {
                                        let t9 = new ImageMenuItem(this, { item: p9, index: this.index * 1000 + o9 + 1 }, undefined, r9, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 348, col: 15 });
                                        ViewPU.create(t9);
                                        let u9 = () => {
                                            return {
                                                item: p9,
                                                index: this.index * 1000 + o9 + 1
                                            };
                                        };
                                        t9.paramsGenerator_ = u9;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(r9, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(j9, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), l9, undefined, true, false);
                        if (!k9) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                    this.observeComponentCreation((x8, y8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x8);
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
                        Button.onHover((i9) => this.isMoreIconOnHover = i9);
                        Button.onKeyEvent((h9) => {
                            if (h9.keyCode !== KeyCode.KEYCODE_ENTER && h9.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (h9.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (h9.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((g9) => {
                            if (g9.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (g9.type === TouchType.Up || g9.type === TouchType.Cancel) {
                                this.isMoreIconOnClick = false;
                                if (this.fontSize >= this.minFontSize) {
                                    this.dialogController?.close();
                                }
                            }
                        });
                        Button.onClick(() => this.isPopupShown = true);
                        Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                        Button.bindPopup(this.isPopupShown, {
                            builder: { builder: this.popupBuilder.bind(this) },
                            placement: Placement.Bottom,
                            popupColor: Color.White,
                            enableArrow: false,
                            onStateChange: (f9) => {
                                this.isPopupShown = f9.isVisible;
                                if (!f9.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                        if (!y8) {
                            Button.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((v8, w8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(v8);
                        SymbolGlyph.create(PUBLIC_MORE);
                        SymbolGlyph.fontSize(TabContentItem.symbolSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.focusable(true);
                        if (!w8) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Button.pop();
                });
            }
            if (!q8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(s7 = null) {
        this.observeComponentCreation((j8, k8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j8);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
            if (!k8) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((v7, w7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v7);
            ForEach.create();
            const x7 = (z7, a8) => {
                const b8 = z7;
                {
                    this.observeComponentCreation((d8, e8) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d8);
                        if (e8) {
                            let f8 = new ImageMenuItem(this, { item: b8, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + a8 }, undefined, d8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 431, col: 11 });
                            ViewPU.create(f8);
                            let g8 = () => {
                                return {
                                    item: b8,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + a8
                                };
                            };
                            f8.paramsGenerator_ = g8;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(d8, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                }
            };
            this.forEachUpdateFunction(v7, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), x7, undefined, true, false);
            if (!w7) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Column.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 1;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class TabContentItem extends ViewPU {
    constructor(m7, n7, o7, p7 = -1, q7 = undefined, r7) {
        super(m7, o7, p7, r7);
        if (typeof q7 === 'function') {
            this.paramsGenerator_ = q7;
        }
        this.item = { title: '' };
        this.index = 0;
        this.maxIndex = 0;
        this.onCustomClick = undefined;
        this.onImageComplete = undefined;
        this.__currentIndex = new SynchedPropertySimpleOneWayPU(n7.currentIndex, this, 'currentIndex');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
        this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
        this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
        this.setInitiallyProvidedValue(n7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l7) {
        if (l7.item !== undefined) {
            this.item = l7.item;
        }
        if (l7.index !== undefined) {
            this.index = l7.index;
        }
        if (l7.maxIndex !== undefined) {
            this.maxIndex = l7.maxIndex;
        }
        if (l7.onCustomClick !== undefined) {
            this.onCustomClick = l7.onCustomClick;
        }
        if (l7.onImageComplete !== undefined) {
            this.onImageComplete = l7.onImageComplete;
        }
        if (l7.isOnFocus !== undefined) {
            this.isOnFocus = l7.isOnFocus;
        }
        if (l7.isOnHover !== undefined) {
            this.isOnHover = l7.isOnHover;
        }
        if (l7.isOnClick !== undefined) {
            this.isOnClick = l7.isOnClick;
        }
        if (l7.tabWidth !== undefined) {
            this.tabWidth = l7.tabWidth;
        }
        if (l7.imageWidth !== undefined) {
            this.imageWidth = l7.imageWidth;
        }
        if (l7.imageHeight !== undefined) {
            this.imageHeight = l7.imageHeight;
        }
    }
    updateStateVars(k7) {
        this.__currentIndex.reset(k7.currentIndex);
    }
    purgeVariableDependenciesOnElmtId(j7) {
        this.__currentIndex.purgeDependencyOnElmtId(j7);
        this.__isOnFocus.purgeDependencyOnElmtId(j7);
        this.__isOnHover.purgeDependencyOnElmtId(j7);
        this.__isOnClick.purgeDependencyOnElmtId(j7);
        this.__tabWidth.purgeDependencyOnElmtId(j7);
        this.__imageWidth.purgeDependencyOnElmtId(j7);
        this.__imageHeight.purgeDependencyOnElmtId(j7);
    }
    aboutToBeDeleted() {
        this.__currentIndex.aboutToBeDeleted();
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__tabWidth.aboutToBeDeleted();
        this.__imageWidth.aboutToBeDeleted();
        this.__imageHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get currentIndex() {
        return this.__currentIndex.get();
    }
    set currentIndex(i7) {
        this.__currentIndex.set(i7);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(h7) {
        this.__isOnFocus.set(h7);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(g7) {
        this.__isOnHover.set(g7);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(f7) {
        this.__isOnClick.set(f7);
    }
    get tabWidth() {
        return this.__tabWidth.get();
    }
    set tabWidth(e7) {
        this.__tabWidth.set(e7);
    }
    get imageWidth() {
        return this.__imageWidth.get();
    }
    set imageWidth(d7) {
        this.__imageWidth.set(d7);
    }
    get imageHeight() {
        return this.__imageHeight.get();
    }
    set imageHeight(c7) {
        this.__imageHeight.set(c7);
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
    getBorderAttr() {
        if (this.isOnFocus) {
            return {
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: TabContentItem.focusBorderWidth,
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                style: BorderStyle.Solid
            };
        }
        return { width: 0 };
    }
    getImageScaleFactor() {
        return this.index === this.currentIndex ? TabContentItem.imageMagnificationFactor : 1;
    }
    getImageLayoutWidth() {
        return TabContentItem.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth;
    }
    toStringFormat(x6) {
        if (typeof x6 === 'string') {
            return x6;
        }
        else if (typeof x6 === 'undefined') {
            return '';
        }
        else {
            let y6 = '';
            try {
                y6 = getContext()?.resourceManager?.getStringSync(x6);
            }
            catch (z6) {
                let a7 = z6?.code;
                let b7 = z6?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${a7},message:${b7}`);
            }
            return y6;
        }
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((v6, w6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v6);
            Stack.create();
            Stack.margin({
                left: this.index === 0 ? TabContentItem.marginFirst : 0,
                right: this.index === this.maxIndex ? 12 : 0
            });
            if (!w6) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((q6, r6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q6);
            Button.createWithChild();
            Button.height(TabTitleBar.totalHeight);
            Button.borderRadius(TabContentItem.buttonBorderRadius);
            Button.backgroundColor(this.getBgColor());
            Button.onAreaChange((t6, u6) => {
                this.tabWidth = Number(u6.width);
            });
            if (!r6) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((o6, p6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o6);
            Column.create();
            Column.justifyContent(FlexAlign.Center);
            if (!p6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((x4, y4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x4);
            If.create();
            if (this.item.icon === undefined && this.item.symbolIcon === undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((d6, e6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d6);
                        Text.create(this.item.title);
                        Context.animation({ duration: 300 });
                        Text.fontSize(this.index === this.currentIndex
                            ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline9'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(this.index === this.currentIndex
                            ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text_off'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontWeight(FontWeight.Medium);
                        Text.focusable(true);
                        Context.animation(null);
                        Text.padding({
                            top: this.index === this.currentIndex ? 6 : 10,
                            left: TabContentItem.paddingLeft,
                            bottom: 2,
                            right: TabContentItem.paddingRight
                        });
                        Text.onFocus(() => this.isOnFocus = true);
                        Text.onBlur(() => this.isOnFocus = false);
                        Text.onHover((n6) => this.isOnHover = n6);
                        Text.onKeyEvent((m6) => {
                            if (m6.keyCode !== KeyCode.KEYCODE_ENTER && m6.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (m6.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (m6.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Text.onTouch((l6) => {
                            if (l6.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (l6.type === TouchType.Up || l6.type === TouchType.Cancel) {
                                this.isOnClick = false;
                            }
                        });
                        Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                        Text.accessibilitySelected(this.index === this.currentIndex);
                        if (!e6) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((q5, r5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q5);
                        Row.create();
                        Context.animation({ duration: 300 });
                        Row.width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
                        TabContentItem.paddingLeft + TabContentItem.paddingRight);
                        Row.constraintSize({
                            minWidth: TabContentItem.imageHotZoneWidth,
                            minHeight: TabContentItem.imageHotZoneWidth
                        });
                        Context.animation(null);
                        Row.justifyContent(FlexAlign.Center);
                        Row.onFocus(() => this.isOnFocus = true);
                        Row.onBlur(() => this.isOnFocus = false);
                        Row.onHover((a6) => this.isOnHover = a6);
                        Row.onKeyEvent((z5) => {
                            if (z5.keyCode !== KeyCode.KEYCODE_ENTER && z5.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (z5.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (z5.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onTouch((y5) => {
                            if (y5.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (y5.type === TouchType.Up || y5.type === TouchType.Cancel) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                        Row.accessibilitySelected(this.index === this.currentIndex);
                        if (!r5) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((c5, d5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c5);
                        If.create();
                        if (this.item.symbolIcon) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((o5, p5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(o5);
                                    SymbolGlyph.create();
                                    Context.animation({ duration: 300 });
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolIcon);
                                    SymbolGlyph.fontSize(TabContentItem.symbolSize);
                                    SymbolGlyph.width(this.getImageLayoutWidth());
                                    SymbolGlyph.height(TabContentItem.imageSize);
                                    SymbolGlyph.accessibilityText(this.toStringFormat(this.item.title));
                                    SymbolGlyph.scale({
                                        x: this.getImageScaleFactor(),
                                        y: this.getImageScaleFactor()
                                    });
                                    Context.animation(null);
                                    SymbolGlyph.hitTestBehavior(HitTestMode.None);
                                    SymbolGlyph.focusable(true);
                                    if (!p5) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((g5, h5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(g5);
                                    Image.create(this.item.icon);
                                    Context.animation({ duration: 300 });
                                    Image.alt(this.item.title);
                                    Image.width(this.getImageLayoutWidth());
                                    Image.height(TabContentItem.imageSize);
                                    Image.objectFit(ImageFit.Fill);
                                    Image.accessibilityText(this.toStringFormat(this.item.title));
                                    Image.scale({
                                        x: this.getImageScaleFactor(),
                                        y: this.getImageScaleFactor()
                                    });
                                    Context.animation(null);
                                    Image.hitTestBehavior(HitTestMode.None);
                                    Image.focusable(true);
                                    Image.onComplete((l5) => {
                                        if (!this.onImageComplete) {
                                            return;
                                        }
                                        this.imageWidth = px2vp(l5?.width);
                                        this.imageHeight = px2vp(l5?.height);
                                        this.onImageComplete(px2vp(l5?.componentWidth) +
                                        TabContentItem.paddingLeft + TabContentItem.paddingRight);
                                    });
                                    Image.onError((k5) => {
                                        if (!this.onImageComplete) {
                                            return;
                                        }
                                        this.onImageComplete(px2vp(k5.componentWidth) +
                                        TabContentItem.paddingLeft + TabContentItem.paddingRight);
                                    });
                                    if (!h5) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        if (!d5) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    Row.pop();
                });
            }
            if (!y4) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Button.pop();
        this.observeComponentCreation((q4, r4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q4);
            If.create();
            if (this.isOnFocus && this.tabWidth > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((v4, w4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(v4);
                        Row.create();
                        Row.width(this.tabWidth);
                        Row.height(TabTitleBar.totalHeight);
                        Row.hitTestBehavior(HitTestMode.None);
                        Row.borderRadius(TabContentItem.buttonBorderRadius);
                        ViewStackProcessor.visualState('focused');
                        Row.border(this.getBorderAttr());
                        ViewStackProcessor.visualState('normal');
                        Row.border({
                            radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            width: 0
                        });
                        ViewStackProcessor.visualState();
                        if (!w4) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!r4) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Stack.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
TabContentItem.imageSize = 24;
TabContentItem.symbolSize = '24vp';
TabContentItem.imageHotZoneWidth = 48;
TabContentItem.imageMagnificationFactor = 1.4;
TabContentItem.buttonBorderRadius = 8;
TabContentItem.focusBorderWidth = 2;
TabContentItem.paddingLeft = 8;
TabContentItem.paddingRight = 8;
TabContentItem.marginFirst = 16;
class ImageMenuItem extends ViewPU {
    constructor(b4, c4, d4, e4 = -1, f4 = undefined, g4) {
        super(b4, d4, e4, g4);
        if (typeof f4 === 'function') {
            this.paramsGenerator_ = f4;
        }
        this.item = { value: '' };
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = false;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(c4.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let h4 = new TabTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    tabTitleDialog: this.item,
                    tabTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 705, col: 14 });
                h4.setController(this.dialogController);
                ViewPU.create(h4);
                let i4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        tabTitleDialog: this.item,
                        tabTitleBarDialog: this.item.label ? this.item.label : '',
                        fontSize: this.fontSize
                    };
                };
                h4.paramsGenerator_ = i4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(c4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a4) {
        if (a4.item !== undefined) {
            this.item = a4.item;
        }
        if (a4.index !== undefined) {
            this.index = a4.index;
        }
        if (a4.minFontSize !== undefined) {
            this.minFontSize = a4.minFontSize;
        }
        if (a4.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a4.isFollowingSystemFontScale;
        }
        if (a4.maxFontScale !== undefined) {
            this.maxFontScale = a4.maxFontScale;
        }
        if (a4.systemFontScale !== undefined) {
            this.systemFontScale = a4.systemFontScale;
        }
        if (a4.isPopup !== undefined) {
            this.isPopup = a4.isPopup;
        }
        if (a4.isOnFocus !== undefined) {
            this.isOnFocus = a4.isOnFocus;
        }
        if (a4.isOnHover !== undefined) {
            this.isOnHover = a4.isOnHover;
        }
        if (a4.isOnClick !== undefined) {
            this.isOnClick = a4.isOnClick;
        }
        if (a4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (a4.dialogController !== undefined) {
            this.dialogController = a4.dialogController;
        }
        if (a4.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = a4.buttonGestureModifier;
        }
    }
    updateStateVars(z3) {
        this.__fontSize.reset(z3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(y3) {
        this.__isOnFocus.purgeDependencyOnElmtId(y3);
        this.__isOnHover.purgeDependencyOnElmtId(y3);
        this.__isOnClick.purgeDependencyOnElmtId(y3);
        this.__fontSize.purgeDependencyOnElmtId(y3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(y3);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(x3) {
        this.__isOnFocus.set(x3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(w3) {
        this.__isOnHover.set(w3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(v3) {
        this.__isOnClick.set(v3);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u3) {
        this.__fontSize.set(u3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(t3) {
        this.__buttonGestureModifier.set(t3);
    }
    textDialog() {
        if (this.item.value === PUBLIC_MORE) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
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
    toStringFormat(o3) {
        if (typeof o3 === 'string') {
            return o3;
        }
        else if (typeof o3 === 'undefined') {
            return '';
        }
        else {
            let p3 = '';
            try {
                p3 = getContext()?.resourceManager?.getStringSync(o3);
            }
            catch (q3) {
                let r3 = q3?.code;
                let s3 = q3?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${r3},message:${s3}`);
            }
            return p3;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_MORE) {
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
    onPlaceChildren(j3, k3, l3) {
        k3.forEach((n3) => {
            n3.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    aboutToAppear() {
        try {
            let i3 = this.getUIContext();
            this.isFollowingSystemFontScale = i3.isFollowingSystemFontScale();
            this.maxFontScale = i3.getMaxFontScale();
        }
        catch (f3) {
            let g3 = f3.code;
            let h3 = f3.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${g3}, message: ${h3}`);
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let e3 = this.getUIContext();
        this.systemFontScale = e3.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((t2, u2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t2);
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.accessibilityText(this.getAccessibilityReadText());
            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
            Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneWidth);
            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            Button.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
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
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((d3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = d3;
            });
            Button.onKeyEvent((c3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (c3.keyCode !== KeyCode.KEYCODE_ENTER && c3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (c3.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (c3.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((b3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (b3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (b3.type === TouchType.Up || b3.type === TouchType.Cancel) {
                    this.isOnClick = false;
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.close();
                    }
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            if (!u2) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((j2, k2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j2);
            If.create();
            if (this.item.symbolValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((r2, s2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r2);
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.item.symbolValue);
                        SymbolGlyph.fontSize(TabContentItem.symbolSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        if (!s2) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((n2, o2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n2);
                        Image.create(this.item.value);
                        Image.width(ImageMenuItem.imageSize);
                        Image.height(ImageMenuItem.imageSize);
                        Image.focusable(this.item.isEnabled);
                        Image.key(ImageMenuItem.focusablePrefix + this.index);
                        Image.draggable(false);
                        if (!o2) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            if (!k2) {
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
ImageMenuItem.focusablePrefix = 'Id-TabTitleBar-ImageMenuItem-';
class TabTitleBarDialog extends ViewPU {
    constructor(z1, a2, b2, c2 = -1, d2 = undefined, e2) {
        super(z1, b2, c2, e2);
        if (typeof d2 === 'function') {
            this.paramsGenerator_ = d2;
        }
        this.tabTitleDialog = { value: '' };
        this.callbackId = undefined;
        this.tabTitleBarDialog = '';
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
        this.setInitiallyProvidedValue(a2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y1) {
        if (y1.tabTitleDialog !== undefined) {
            this.tabTitleDialog = y1.tabTitleDialog;
        }
        if (y1.callbackId !== undefined) {
            this.callbackId = y1.callbackId;
        }
        if (y1.tabTitleBarDialog !== undefined) {
            this.tabTitleBarDialog = y1.tabTitleBarDialog;
        }
        if (y1.mainWindowStage !== undefined) {
            this.mainWindowStage = y1.mainWindowStage;
        }
        if (y1.controller !== undefined) {
            this.controller = y1.controller;
        }
        if (y1.minFontSize !== undefined) {
            this.minFontSize = y1.minFontSize;
        }
        if (y1.maxFontSize !== undefined) {
            this.maxFontSize = y1.maxFontSize;
        }
        if (y1.screenWidth !== undefined) {
            this.screenWidth = y1.screenWidth;
        }
        if (y1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = y1.verticalScreenLines;
        }
        if (y1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = y1.horizontalsScreenLines;
        }
        if (y1.fontSize !== undefined) {
            this.fontSize = y1.fontSize;
        }
        if (y1.maxLines !== undefined) {
            this.maxLines = y1.maxLines;
        }
        if (y1.cancel !== undefined) {
            this.cancel = y1.cancel;
        }
        if (y1.confirm !== undefined) {
            this.confirm = y1.confirm;
        }
    }
    updateStateVars(x1) {
    }
    purgeVariableDependenciesOnElmtId(w1) {
        this.__mainWindow.purgeDependencyOnElmtId(w1);
        this.__fontSize.purgeDependencyOnElmtId(w1);
        this.__maxLines.purgeDependencyOnElmtId(w1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(w1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(v1) {
        this.controller = v1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(u1) {
        this.__mainWindow.set(u1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t1) {
        this.__fontSize.set(t1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(s1) {
        this.__maxLines.set(s1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(r1) {
        this.__windowStandardHeight.set(r1);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e, f) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            if (this.tabTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((p1, q1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p1);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!q1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((e1, f1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e1);
                        If.create();
                        if (this.tabTitleDialog.symbolValue) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((n1, o1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n1);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolValue);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    if (!o1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else if (this.tabTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((j1, k1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(j1);
                                    Image.create(this.tabTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!k1) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                        if (!f1) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((c1, d1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c1);
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        if (!d1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((a1, b1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(a1);
                        Text.create(this.tabTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!b1) {
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
                    this.observeComponentCreation((t, u) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                        if (!u) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((j, k) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j);
                        If.create();
                        if (this.tabTitleDialog.symbolValue) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((r, s) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolValue);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                    if (!s) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((n, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n);
                                    Image.create(this.tabTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!o) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        if (!k) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    Column.pop();
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
TabTitleBar: TabTitleBar,
IconResource: IconResource,
};
