/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
const RESOURCE_TYPE_SYMBOL = 40000;
class ButtonGestureModifier {
    constructor(k11) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = k11;
    }
    applyGesture(j11) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            j11.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (j11) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            j11.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class TabTitleBar extends ViewPU {
    constructor(d11, e11, f11, g11 = -1, h11 = undefined, i11) {
        super(d11, f11, g11, i11);
        if (typeof h11 === 'function') {
            this.paramsGenerator_ = h11;
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
        this.setInitiallyProvidedValue(e11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c11) {
        if (c11.tabItems !== undefined) {
            this.tabItems = c11.tabItems;
        }
        if (c11.menuItems !== undefined) {
            this.menuItems = c11.menuItems;
        }
        if (c11.swiperContent !== undefined) {
            this.swiperContent = c11.swiperContent;
        }
        if (c11.tabWidth !== undefined) {
            this.tabWidth = c11.tabWidth;
        }
        if (c11.currentIndex !== undefined) {
            this.currentIndex = c11.currentIndex;
        }
        if (c11.fontSize !== undefined) {
            this.fontSize = c11.fontSize;
        }
        if (c11.menuSectionWidth !== undefined) {
            this.menuSectionWidth = c11.menuSectionWidth;
        }
        if (c11.tabOffsets !== undefined) {
            this.tabOffsets = c11.tabOffsets;
        }
        if (c11.imageWidths !== undefined) {
            this.imageWidths = c11.imageWidths;
        }
        if (c11.scroller !== undefined) {
            this.scroller = c11.scroller;
        }
        if (c11.swiperController !== undefined) {
            this.swiperController = c11.swiperController;
        }
        if (c11.settings !== undefined) {
            this.settings = c11.settings;
        }
        if (c11.leftContext2D !== undefined) {
            this.leftContext2D = c11.leftContext2D;
        }
        if (c11.rightContext2D !== undefined) {
            this.rightContext2D = c11.rightContext2D;
        }
    }
    updateStateVars(b11) {
    }
    purgeVariableDependenciesOnElmtId(a11) {
        this.__tabWidth.purgeDependencyOnElmtId(a11);
        this.__currentIndex.purgeDependencyOnElmtId(a11);
        this.__fontSize.purgeDependencyOnElmtId(a11);
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
    set tabWidth(z10) {
        this.__tabWidth.set(z10);
    }
    get currentIndex() {
        return this.__currentIndex.get();
    }
    set currentIndex(y10) {
        this.__currentIndex.set(y10);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(x10) {
        this.__fontSize.set(x10);
    }
    GradientMask(m10, n10, o10, p10, q10, r10 = null) {
        this.observeComponentCreation2((v10, w10) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(TabTitleBar.gradientMaskWidth);
            Column.height(TabTitleBar.totalHeight);
        }, Column);
        this.observeComponentCreation2((s10, t10) => {
            Canvas.create(m10);
            Canvas.width(TabTitleBar.gradientMaskWidth);
            Canvas.height(TabTitleBar.totalHeight);
            Canvas.onReady(() => {
                let u10 = m10.createLinearGradient(n10, o10, p10, q10);
                u10.addColorStop(0.0, '#ffffffff');
                u10.addColorStop(1, '#00ffffff');
                m10.fillStyle = u10;
                m10.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
            });
        }, Canvas);
        Canvas.pop();
        Column.pop();
    }
    emptyBuilder(l10 = null) {
    }
    aboutToAppear() {
        if (!this.swiperContent) {
            this.swiperContent = this.emptyBuilder;
        }
        this.tabItems.forEach((k10) => {
            this.imageWidths.push(0);
        });
        this.loadOffsets();
    }
    loadOffsets() {
        this.tabOffsets.length = 0;
        let h10 = 0;
        this.tabOffsets.push(h10);
        h10 += TabContentItem.marginFirst;
        this.tabItems.forEach((i10, j10) => {
            if (i10.icon !== undefined || i10.symbolStyle !== undefined) {
                if (Math.abs(this.imageWidths[j10]) > TabContentItem.imageHotZoneWidth) {
                    h10 += this.imageWidths[j10];
                }
                else {
                    h10 += TabContentItem.imageHotZoneWidth;
                }
            }
            else {
                h10 += TabContentItem.paddingLeft;
                h10 += px2vp(MeasureText.measureText({
                    textContent: i10.title.toString(),
                    fontSize: 18,
                    fontWeight: FontWeight.Medium,
                }));
                h10 += TabContentItem.paddingRight;
            }
            this.tabOffsets.push(h10);
        });
    }
    initialRender() {
        this.observeComponentCreation2((f10, g10) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((b10, c10) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Flex.onAreaChange((d10, e10) => {
                this.tabWidth = Number(e10.width) - this.menuSectionWidth;
            });
        }, Flex);
        this.observeComponentCreation2((z9, a10) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((x9, y9) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((v9, w9) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((t9, u9) => {
            List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
            List.width('100%');
            List.height(TabTitleBar.totalHeight);
            List.constraintSize({ maxWidth: this.tabWidth });
            List.edgeEffect(EdgeEffect.Spring);
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
        }, List);
        this.observeComponentCreation2((w8, x8) => {
            ForEach.create();
            const y8 = (z8, a9) => {
                const b9 = z8;
                {
                    const c9 = (r9, s9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r9);
                        d9(r9, s9);
                        if (!s9) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const d9 = (p9, q9) => {
                        ListItem.create(e9, true);
                    };
                    const e9 = (f9, g9) => {
                        c9(f9, g9);
                        {
                            this.observeComponentCreation2((h9, i9) => {
                                if (i9) {
                                    let j9 = new TabContentItem(this, {
                                        item: b9,
                                        index: a9,
                                        maxIndex: this.tabItems.length - 1,
                                        currentIndex: this.currentIndex,
                                        onCustomClick: (o9) => this.currentIndex = o9,
                                        onImageComplete: (n9) => {
                                            this.imageWidths[a9] = n9;
                                            this.loadOffsets();
                                        }
                                    }, undefined, h9, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 174, col: 21 });
                                    ViewPU.create(j9);
                                    let k9 = () => {
                                        return {
                                            item: b9,
                                            index: a9,
                                            maxIndex: this.tabItems.length - 1,
                                            currentIndex: this.currentIndex,
                                            onCustomClick: (m9) => this.currentIndex = m9,
                                            onImageComplete: (l9) => {
                                                this.imageWidths[a9] = l9;
                                                this.loadOffsets();
                                            }
                                        };
                                    };
                                    j9.paramsGenerator_ = k9;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(h9, {
                                        currentIndex: this.currentIndex
                                    });
                                }
                            }, { name: 'TabContentItem' });
                        }
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(d9, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(w8, this.tabItems, y8, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.observeComponentCreation2((m8, n8) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s8, t8) => {
                        __Common__.create();
                        __Common__.height(TabTitleBar.totalHeight);
                        __Common__.onAreaChange((u8, v8) => {
                            this.menuSectionWidth = Number(v8.width);
                        });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((o8, p8) => {
                            if (p8) {
                                let q8 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ }, undefined, o8, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 204, col: 11 });
                                ViewPU.create(q8);
                                let r8 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + TabTitleBar.instanceCount++
                                    };
                                };
                                q8.paramsGenerator_ = r8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o8, {});
                            }
                        }, { name: 'CollapsibleMenuSection' });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        this.observeComponentCreation2((k8, l8) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((g8, h8) => {
            Swiper.create(this.swiperController);
            Swiper.index(this.currentIndex);
            Swiper.itemSpace(0);
            Swiper.indicator(false);
            Swiper.width('100%');
            Swiper.height('100%');
            Swiper.curve(Curve.Friction);
            Swiper.onChange((i8) => {
                const j8 = this.tabOffsets[i8] + TabTitleBar.correctionOffset;
                this.currentIndex = i8;
                this.scroller.scrollTo({
                    xOffset: j8 > 0 ? j8 : 0,
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
        }, Swiper);
        this.swiperContent.bind(this)();
        Swiper.pop();
        Column.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
TabTitleBar.totalHeight = 56;
TabTitleBar.correctionOffset = -40.0;
TabTitleBar.gradientMaskWidth = 24;
TabTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
    constructor(y7, z7, a8, b8 = -1, c8 = undefined, d8) {
        super(y7, a8, b8, d8);
        if (typeof c8 === 'function') {
            this.paramsGenerator_ = c8;
        }
        this.menuItems = [];
        this.index = 0;
        this.item = {
            value: PUBLIC_MORE,
            symbolStyle: new SymbolGlyphModifier(PUBLIC_MORE),
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(z7.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let e8 = new TabTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    tabTitleDialog: this.item,
                    tabTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 273, col: 14 });
                e8.setController(this.dialogController);
                ViewPU.create(e8);
                let f8 = () => {
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
                e8.paramsGenerator_ = f8;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(z7);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x7) {
        if (x7.menuItems !== undefined) {
            this.menuItems = x7.menuItems;
        }
        if (x7.index !== undefined) {
            this.index = x7.index;
        }
        if (x7.item !== undefined) {
            this.item = x7.item;
        }
        if (x7.minFontSize !== undefined) {
            this.minFontSize = x7.minFontSize;
        }
        if (x7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = x7.isFollowingSystemFontScale;
        }
        if (x7.maxFontScale !== undefined) {
            this.maxFontScale = x7.maxFontScale;
        }
        if (x7.systemFontScale !== undefined) {
            this.systemFontScale = x7.systemFontScale;
        }
        if (x7.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = x7.firstFocusableIndex;
        }
        if (x7.isPopupShown !== undefined) {
            this.isPopupShown = x7.isPopupShown;
        }
        if (x7.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = x7.isMoreIconOnFocus;
        }
        if (x7.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = x7.isMoreIconOnHover;
        }
        if (x7.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = x7.isMoreIconOnClick;
        }
        if (x7.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (x7.dialogController !== undefined) {
            this.dialogController = x7.dialogController;
        }
        if (x7.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = x7.buttonGestureModifier;
        }
    }
    updateStateVars(w7) {
        this.__fontSize.reset(w7.fontSize);
    }
    purgeVariableDependenciesOnElmtId(v7) {
        this.__isPopupShown.purgeDependencyOnElmtId(v7);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(v7);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(v7);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(v7);
        this.__fontSize.purgeDependencyOnElmtId(v7);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(v7);
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
    set isPopupShown(u7) {
        this.__isPopupShown.set(u7);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(t7) {
        this.__isMoreIconOnFocus.set(t7);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(s7) {
        this.__isMoreIconOnHover.set(s7);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(r7) {
        this.__isMoreIconOnClick.set(r7);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(q7) {
        this.__fontSize.set(q7);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(p7) {
        this.__buttonGestureModifier.set(p7);
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
            let o7 = this.getUIContext();
            this.isFollowingSystemFontScale = o7.isFollowingSystemFontScale();
            this.maxFontScale = o7.getMaxFontScale();
        }
        catch (l7) {
            let m7 = l7.code;
            let n7 = l7.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${m7}, message: ${n7}`);
        }
        this.menuItems.forEach((j7, k7) => {
            if (j7.isEnabled && this.firstFocusableIndex === -1 &&
                k7 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + k7 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let i7 = this.getUIContext();
        this.systemFontScale = i7.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((g7, h7) => {
            Column.create();
            Column.height('100%');
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((e7, f7) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((a6, b6) => {
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u6, v6) => {
                        ForEach.create();
                        const w6 = (x6, y6) => {
                            const z6 = x6;
                            {
                                this.observeComponentCreation2((a7, b7) => {
                                    if (b7) {
                                        let c7 = new ImageMenuItem(this, { item: z6, index: this.index * 1000 + y6 + 1 }, undefined, a7, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 342, col: 13 });
                                        ViewPU.create(c7);
                                        let d7 = () => {
                                            return {
                                                item: z6,
                                                index: this.index * 1000 + y6 + 1
                                            };
                                        };
                                        c7.paramsGenerator_ = d7;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(a7, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(u6, this.menuItems, w6, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((k6, l6) => {
                        ForEach.create();
                        const m6 = (n6, o6) => {
                            const p6 = n6;
                            {
                                this.observeComponentCreation2((q6, r6) => {
                                    if (r6) {
                                        let s6 = new ImageMenuItem(this, { item: p6, index: this.index * 1000 + o6 + 1 }, undefined, q6, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 347, col: 15 });
                                        ViewPU.create(s6);
                                        let t6 = () => {
                                            return {
                                                item: p6,
                                                index: this.index * 1000 + o6 + 1
                                            };
                                        };
                                        s6.paramsGenerator_ = t6;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(q6, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(k6, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), m6, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    this.observeComponentCreation2((e6, f6) => {
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
                        Button.onHover((j6) => this.isMoreIconOnHover = j6);
                        Button.onKeyEvent((i6) => {
                            if (i6.keyCode !== KeyCode.KEYCODE_ENTER && i6.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (i6.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (i6.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((h6) => {
                            if (h6.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (h6.type === TouchType.Up || h6.type === TouchType.Cancel) {
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
                            onStateChange: (g6) => {
                                this.isPopupShown = g6.isVisible;
                                if (!g6.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                    }, Button);
                    this.observeComponentCreation2((c6, d6) => {
                        SymbolGlyph.create(PUBLIC_MORE);
                        SymbolGlyph.fontSize(TabContentItem.symbolSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.focusable(true);
                    }, SymbolGlyph);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Column.pop();
    }
    onPlaceChildren(w5, x5, y5) {
        x5.forEach((z5) => {
            z5.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(j5 = null) {
        this.observeComponentCreation2((u5, v5) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((k5, l5) => {
            ForEach.create();
            const m5 = (n5, o5) => {
                const p5 = n5;
                {
                    this.observeComponentCreation2((q5, r5) => {
                        if (r5) {
                            let s5 = new ImageMenuItem(this, { item: p5, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + o5 }, undefined, q5, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 437, col: 11 });
                            ViewPU.create(s5);
                            let t5 = () => {
                                return {
                                    item: p5,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + o5
                                };
                            };
                            s5.paramsGenerator_ = t5;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(q5, {});
                        }
                    }, { name: 'ImageMenuItem' });
                }
            };
            this.forEachUpdateFunction(k5, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), m5, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 1;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class TabContentItem extends ViewPU {
    constructor(d5, e5, f5, g5 = -1, h5 = undefined, i5) {
        super(d5, f5, g5, i5);
        if (typeof h5 === 'function') {
            this.paramsGenerator_ = h5;
        }
        this.item = { title: '' };
        this.index = 0;
        this.maxIndex = 0;
        this.onCustomClick = undefined;
        this.onImageComplete = undefined;
        this.__currentIndex = new SynchedPropertySimpleOneWayPU(e5.currentIndex, this, 'currentIndex');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
        this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
        this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
        this.setInitiallyProvidedValue(e5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c5) {
        if (c5.item !== undefined) {
            this.item = c5.item;
        }
        if (c5.index !== undefined) {
            this.index = c5.index;
        }
        if (c5.maxIndex !== undefined) {
            this.maxIndex = c5.maxIndex;
        }
        if (c5.onCustomClick !== undefined) {
            this.onCustomClick = c5.onCustomClick;
        }
        if (c5.onImageComplete !== undefined) {
            this.onImageComplete = c5.onImageComplete;
        }
        if (c5.isOnFocus !== undefined) {
            this.isOnFocus = c5.isOnFocus;
        }
        if (c5.isOnHover !== undefined) {
            this.isOnHover = c5.isOnHover;
        }
        if (c5.isOnClick !== undefined) {
            this.isOnClick = c5.isOnClick;
        }
        if (c5.tabWidth !== undefined) {
            this.tabWidth = c5.tabWidth;
        }
        if (c5.imageWidth !== undefined) {
            this.imageWidth = c5.imageWidth;
        }
        if (c5.imageHeight !== undefined) {
            this.imageHeight = c5.imageHeight;
        }
    }
    updateStateVars(b5) {
        this.__currentIndex.reset(b5.currentIndex);
    }
    purgeVariableDependenciesOnElmtId(a5) {
        this.__currentIndex.purgeDependencyOnElmtId(a5);
        this.__isOnFocus.purgeDependencyOnElmtId(a5);
        this.__isOnHover.purgeDependencyOnElmtId(a5);
        this.__isOnClick.purgeDependencyOnElmtId(a5);
        this.__tabWidth.purgeDependencyOnElmtId(a5);
        this.__imageWidth.purgeDependencyOnElmtId(a5);
        this.__imageHeight.purgeDependencyOnElmtId(a5);
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
    set currentIndex(z4) {
        this.__currentIndex.set(z4);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(y4) {
        this.__isOnFocus.set(y4);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(x4) {
        this.__isOnHover.set(x4);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(w4) {
        this.__isOnClick.set(w4);
    }
    get tabWidth() {
        return this.__tabWidth.get();
    }
    set tabWidth(v4) {
        this.__tabWidth.set(v4);
    }
    get imageWidth() {
        return this.__imageWidth.get();
    }
    set imageWidth(u4) {
        this.__imageWidth.set(u4);
    }
    get imageHeight() {
        return this.__imageHeight.get();
    }
    set imageHeight(t4) {
        this.__imageHeight.set(t4);
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
    toStringFormat(o4) {
        if (typeof o4 === 'string') {
            return o4;
        }
        else if (typeof o4 === 'undefined') {
            return '';
        }
        else {
            let p4 = '';
            try {
                p4 = getContext()?.resourceManager?.getStringSync(o4);
            }
            catch (q4) {
                let r4 = q4?.code;
                let s4 = q4?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${r4},message:${s4}`);
            }
            return p4;
        }
    }
    initialRender() {
        this.observeComponentCreation2((m4, n4) => {
            Stack.create();
            Stack.margin({
                left: this.index === 0 ? TabContentItem.marginFirst : 0,
                right: this.index === this.maxIndex ? 12 : 0
            });
        }, Stack);
        this.observeComponentCreation2((i4, j4) => {
            Row.create();
            Row.height(TabTitleBar.totalHeight);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius(TabContentItem.buttonBorderRadius);
            Row.backgroundColor(this.getBgColor());
            Row.onAreaChange((k4, l4) => {
                this.tabWidth = Number(l4.width);
            });
        }, Row);
        this.observeComponentCreation2((g4, h4) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((i3, j3) => {
            If.create();
            if (this.item.icon === undefined && this.item.symbolStyle === undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b4, c4) => {
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
                        Text.onHover((f4) => this.isOnHover = f4);
                        Text.onKeyEvent((e4) => {
                            if (e4.keyCode !== KeyCode.KEYCODE_ENTER && e4.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (e4.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (e4.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Text.onTouch((d4) => {
                            if (d4.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (d4.type === TouchType.Up || d4.type === TouchType.Cancel) {
                                this.isOnClick = false;
                            }
                        });
                        Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                        Text.accessibilitySelected(this.index === this.currentIndex);
                    }, Text);
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w3, x3) => {
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
                        Row.onHover((a4) => this.isOnHover = a4);
                        Row.onKeyEvent((z3) => {
                            if (z3.keyCode !== KeyCode.KEYCODE_ENTER && z3.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (z3.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (z3.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onTouch((y3) => {
                            if (y3.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (y3.type === TouchType.Up || y3.type === TouchType.Cancel) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                        Row.accessibilitySelected(this.index === this.currentIndex);
                    }, Row);
                    this.observeComponentCreation2((k3, l3) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u3, v3) => {
                                    SymbolGlyph.create();
                                    Context.animation({ duration: 300 });
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
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
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((m3, n3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.icon)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((s3, t3) => {
                                                SymbolGlyph.create(this.item.icon);
                                                Context.animation({ duration: 300 });
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
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
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((o3, p3) => {
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
                                                Image.onComplete((r3) => {
                                                    if (!this.onImageComplete) {
                                                        return;
                                                    }
                                                    this.imageWidth = px2vp(r3?.width);
                                                    this.imageHeight = px2vp(r3?.height);
                                                    this.onImageComplete(px2vp(r3?.componentWidth) +
                                                    TabContentItem.paddingLeft + TabContentItem.paddingRight);
                                                });
                                                Image.onError((q3) => {
                                                    if (!this.onImageComplete) {
                                                        return;
                                                    }
                                                    this.onImageComplete(px2vp(q3.componentWidth) +
                                                    TabContentItem.paddingLeft + TabContentItem.paddingRight);
                                                });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Column.pop();
        Row.pop();
        this.observeComponentCreation2((e3, f3) => {
            If.create();
            if (this.isOnFocus && this.tabWidth > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g3, h3) => {
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
                    }, Row);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
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
    constructor(y2, z2, a3, b3 = -1, c3 = undefined, d3) {
        super(y2, a3, b3, d3);
        if (typeof c3 === 'function') {
            this.paramsGenerator_ = c3;
        }
        this.item = { value: '' };
        this.index = 0;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.setInitiallyProvidedValue(z2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x2) {
        if (x2.item !== undefined) {
            this.item = x2.item;
        }
        if (x2.index !== undefined) {
            this.index = x2.index;
        }
        if (x2.isOnFocus !== undefined) {
            this.isOnFocus = x2.isOnFocus;
        }
        if (x2.isOnHover !== undefined) {
            this.isOnHover = x2.isOnHover;
        }
        if (x2.isOnClick !== undefined) {
            this.isOnClick = x2.isOnClick;
        }
    }
    updateStateVars(w2) {
    }
    purgeVariableDependenciesOnElmtId(v2) {
        this.__isOnFocus.purgeDependencyOnElmtId(v2);
        this.__isOnHover.purgeDependencyOnElmtId(v2);
        this.__isOnClick.purgeDependencyOnElmtId(v2);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(u2) {
        this.__isOnFocus.set(u2);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(t2) {
        this.__isOnHover.set(t2);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(s2) {
        this.__isOnClick.set(s2);
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
    toStringFormat(n2) {
        if (typeof n2 === 'string') {
            return n2;
        }
        else if (typeof n2 === 'undefined') {
            return '';
        }
        else {
            let o2 = '';
            try {
                o2 = getContext()?.resourceManager?.getStringSync(n2);
            }
            catch (p2) {
                let q2 = p2?.code;
                let r2 = p2?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${q2},message:${r2}`);
            }
            return o2;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_MORE) {
            return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
        }
        else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        }
        else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    initialRender() {
        this.observeComponentCreation2((i2, j2) => {
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
            Button.onHover((m2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = m2;
            });
            Button.onKeyEvent((l2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (l2.keyCode !== KeyCode.KEYCODE_ENTER && l2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (l2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (l2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((k2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (k2.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (k2.type === TouchType.Up || k2.type === TouchType.Cancel) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        this.observeComponentCreation2((y1, z1) => {
            If.create();
            if (this.item.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g2, h2) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                        SymbolGlyph.fontSize(TabContentItem.symbolSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((a2, b2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e2, f2) => {
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.fontSize(TabContentItem.symbolSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((c2, d2) => {
                                    Image.create(this.item.value);
                                    Image.width(ImageMenuItem.imageSize);
                                    Image.height(ImageMenuItem.imageSize);
                                    Image.focusable(this.item.isEnabled);
                                    Image.key(ImageMenuItem.focusablePrefix + this.index);
                                    Image.draggable(false);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-TabTitleBar-ImageMenuItem-';
class TabTitleBarDialog extends ViewPU {
    constructor(s1, t1, u1, v1 = -1, w1 = undefined, x1) {
        super(s1, u1, v1, x1);
        if (typeof w1 === 'function') {
            this.paramsGenerator_ = w1;
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
        this.setInitiallyProvidedValue(t1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r1) {
        if (r1.tabTitleDialog !== undefined) {
            this.tabTitleDialog = r1.tabTitleDialog;
        }
        if (r1.callbackId !== undefined) {
            this.callbackId = r1.callbackId;
        }
        if (r1.tabTitleBarDialog !== undefined) {
            this.tabTitleBarDialog = r1.tabTitleBarDialog;
        }
        if (r1.mainWindowStage !== undefined) {
            this.mainWindowStage = r1.mainWindowStage;
        }
        if (r1.controller !== undefined) {
            this.controller = r1.controller;
        }
        if (r1.minFontSize !== undefined) {
            this.minFontSize = r1.minFontSize;
        }
        if (r1.maxFontSize !== undefined) {
            this.maxFontSize = r1.maxFontSize;
        }
        if (r1.screenWidth !== undefined) {
            this.screenWidth = r1.screenWidth;
        }
        if (r1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = r1.verticalScreenLines;
        }
        if (r1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = r1.horizontalsScreenLines;
        }
        if (r1.fontSize !== undefined) {
            this.fontSize = r1.fontSize;
        }
        if (r1.maxLines !== undefined) {
            this.maxLines = r1.maxLines;
        }
        if (r1.cancel !== undefined) {
            this.cancel = r1.cancel;
        }
        if (r1.confirm !== undefined) {
            this.confirm = r1.confirm;
        }
    }
    updateStateVars(q1) {
    }
    purgeVariableDependenciesOnElmtId(p1) {
        this.__mainWindow.purgeDependencyOnElmtId(p1);
        this.__fontSize.purgeDependencyOnElmtId(p1);
        this.__maxLines.purgeDependencyOnElmtId(p1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(p1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(o1) {
        this.controller = o1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(n1) {
        this.__mainWindow.set(n1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(m1) {
        this.__fontSize.set(m1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(l1) {
        this.__maxLines.set(l1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(k1) {
        this.__windowStandardHeight.set(k1);
    }
    initialRender() {
        this.observeComponentCreation2((g, h) => {
            If.create();
            if (this.tabTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i1, j1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((y, z) => {
                        If.create();
                        if (this.tabTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((g1, h1) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.tabTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((a1, b1) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.tabTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((e1, f1) => {
                                                SymbolGlyph.create(this.tabTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((c1, d1) => {
                                                Image.create(this.tabTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((w, x) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((u, v) => {
                        Text.create(this.tabTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((s, t) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((i, j) => {
                        If.create();
                        if (this.tabTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q, r) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.tabTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k, l) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.tabTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o, p) => {
                                                SymbolGlyph.create(this.tabTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((m, n) => {
                                                Image.create(this.tabTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let d = this.getUIContext().getHostContext();
        this.mainWindowStage = d.windowStage.getMainWindowSync();
        let e = this.mainWindowStage.getWindowProperties();
        let f = e.windowRect;
        if (px2vp(f.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        }
        else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class Util {
    static isSymbolResource(b) {
        if (!Util.isResourceType(b)) {
            return false;
        }
        let c = b;
        return c.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(a) {
        if (!a) {
            return false;
        }
        if (typeof a === 'string' || typeof a === 'undefined') {
            return false;
        }
        return true;
    }
}

export default {
  TabTitleBar: TabTitleBar
};