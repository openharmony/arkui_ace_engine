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
    constructor(y47) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = y47;
    }
    applyGesture(x47) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            x47.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (x47) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            x47.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class TabTitleBar extends ViewPU {
    constructor(r47, s47, t47, u47 = -1, v47 = undefined, w47) {
        super(r47, t47, u47, w47);
        if (typeof v47 === 'function') {
            this.paramsGenerator_ = v47;
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
        this.setInitiallyProvidedValue(s47);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q47) {
        if (q47.tabItems !== undefined) {
            this.tabItems = q47.tabItems;
        }
        if (q47.menuItems !== undefined) {
            this.menuItems = q47.menuItems;
        }
        if (q47.swiperContent !== undefined) {
            this.swiperContent = q47.swiperContent;
        }
        if (q47.tabWidth !== undefined) {
            this.tabWidth = q47.tabWidth;
        }
        if (q47.currentIndex !== undefined) {
            this.currentIndex = q47.currentIndex;
        }
        if (q47.fontSize !== undefined) {
            this.fontSize = q47.fontSize;
        }
        if (q47.menuSectionWidth !== undefined) {
            this.menuSectionWidth = q47.menuSectionWidth;
        }
        if (q47.tabOffsets !== undefined) {
            this.tabOffsets = q47.tabOffsets;
        }
        if (q47.imageWidths !== undefined) {
            this.imageWidths = q47.imageWidths;
        }
        if (q47.scroller !== undefined) {
            this.scroller = q47.scroller;
        }
        if (q47.swiperController !== undefined) {
            this.swiperController = q47.swiperController;
        }
        if (q47.settings !== undefined) {
            this.settings = q47.settings;
        }
        if (q47.leftContext2D !== undefined) {
            this.leftContext2D = q47.leftContext2D;
        }
        if (q47.rightContext2D !== undefined) {
            this.rightContext2D = q47.rightContext2D;
        }
    }
    updateStateVars(p47) {
    }
    purgeVariableDependenciesOnElmtId(o47) {
        this.__tabWidth.purgeDependencyOnElmtId(o47);
        this.__currentIndex.purgeDependencyOnElmtId(o47);
        this.__fontSize.purgeDependencyOnElmtId(o47);
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
    set tabWidth(n47) {
        this.__tabWidth.set(n47);
    }
    get currentIndex() {
        return this.__currentIndex.get();
    }
    set currentIndex(m47) {
        this.__currentIndex.set(m47);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(l47) {
        this.__fontSize.set(l47);
    }
    GradientMask(a47, b47, c47, d47, e47, f47 = null) {
        this.observeComponentCreation2((j47, k47) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(TabTitleBar.gradientMaskWidth);
            Column.height(TabTitleBar.totalHeight);
        }, Column);
        this.observeComponentCreation2((g47, h47) => {
            Canvas.create(a47);
            Canvas.width(TabTitleBar.gradientMaskWidth);
            Canvas.height(TabTitleBar.totalHeight);
            Canvas.onReady(() => {
                let i47 = a47.createLinearGradient(b47, c47, d47, e47);
                i47.addColorStop(0.0, '#ffffffff');
                i47.addColorStop(1, '#00ffffff');
                a47.fillStyle = i47;
                a47.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
            });
        }, Canvas);
        Canvas.pop();
        Column.pop();
    }
    emptyBuilder(z46 = null) {
    }
    aboutToAppear() {
        if (!this.swiperContent) {
            this.swiperContent = this.emptyBuilder;
        }
        this.tabItems.forEach((y46) => {
            this.imageWidths.push(0);
        });
        this.loadOffsets();
    }
    loadOffsets() {
        this.tabOffsets.length = 0;
        let v46 = 0;
        this.tabOffsets.push(v46);
        v46 += TabContentItem.marginFirst;
        this.tabItems.forEach((w46, x46) => {
            if (w46.icon !== undefined || w46.symbolStyle !== undefined) {
                if (Math.abs(this.imageWidths[x46]) > TabContentItem.imageHotZoneWidth) {
                    v46 += this.imageWidths[x46];
                }
                else {
                    v46 += TabContentItem.imageHotZoneWidth;
                }
            }
            else {
                v46 += TabContentItem.paddingLeft;
                v46 += px2vp(MeasureText.measureText({
                    textContent: w46.title.toString(),
                    fontSize: 18,
                    fontWeight: FontWeight.Medium,
                }));
                v46 += TabContentItem.paddingRight;
            }
            this.tabOffsets.push(v46);
        });
    }
    initialRender() {
        this.observeComponentCreation2((t46, u46) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((p46, q46) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Flex.onAreaChange((r46, s46) => {
                this.tabWidth = Number(s46.width) - this.menuSectionWidth;
            });
        }, Flex);
        this.observeComponentCreation2((n46, o46) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((l46, m46) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((j46, k46) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((h46, i46) => {
            List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
            List.width('100%');
            List.height(TabTitleBar.totalHeight);
            List.constraintSize({ maxWidth: this.tabWidth });
            List.edgeEffect(EdgeEffect.Spring);
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
        }, List);
        this.observeComponentCreation2((k45, l45) => {
            ForEach.create();
            const a18 = (n45, o45) => {
                const p45 = n45;
                {
                    const b18 = (f46, g46) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f46);
                        c18(f46, g46);
                        if (!g46) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const c18 = (d46, e46) => {
                        ListItem.create(d18, true);
                    };
                    const d18 = (t45, u45) => {
                        b18(t45, u45);
                        {
                            this.observeComponentCreation2((v45, w45) => {
                                if (w45) {
                                    let x45 = new TabContentItem(this, {
                                        item: p45,
                                        index: o45,
                                        maxIndex: this.tabItems.length - 1,
                                        currentIndex: this.currentIndex,
                                        onCustomClick: (c46) => this.currentIndex = c46,
                                        onImageComplete: (b46) => {
                                            this.imageWidths[o45] = b46;
                                            this.loadOffsets();
                                        }
                                    }, undefined, v45, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 174, col: 21 });
                                    ViewPU.create(x45);
                                    let e18 = () => {
                                        return {
                                            item: p45,
                                            index: o45,
                                            maxIndex: this.tabItems.length - 1,
                                            currentIndex: this.currentIndex,
                                            onCustomClick: (a46) => this.currentIndex = a46,
                                            onImageComplete: (z45) => {
                                                this.imageWidths[o45] = z45;
                                                this.loadOffsets();
                                            }
                                        };
                                    };
                                    x45.paramsGenerator_ = e18;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(v45, {
                                        currentIndex: this.currentIndex
                                    });
                                }
                            }, { name: 'TabContentItem' });
                        }
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(c18, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(k45, this.tabItems, a18, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
        this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
        Stack.pop();
        this.observeComponentCreation2((a45, b45) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g45, h45) => {
                        __Common__.create();
                        __Common__.height(TabTitleBar.totalHeight);
                        __Common__.onAreaChange((i45, j45) => {
                            this.menuSectionWidth = Number(j45.width);
                        });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((c45, d45) => {
                            if (d45) {
                                let e45 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ }, undefined, c45, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 204, col: 11 });
                                ViewPU.create(e45);
                                let z17 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + TabTitleBar.instanceCount++
                                    };
                                };
                                e45.paramsGenerator_ = z17;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c45, {});
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
        this.observeComponentCreation2((y44, z44) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((u44, v44) => {
            Swiper.create(this.swiperController);
            Swiper.index(this.currentIndex);
            Swiper.itemSpace(0);
            Swiper.indicator(false);
            Swiper.width('100%');
            Swiper.height('100%');
            Swiper.curve(Curve.Friction);
            Swiper.onChange((w44) => {
                const x44 = this.tabOffsets[w44] + TabTitleBar.correctionOffset;
                this.currentIndex = w44;
                this.scroller.scrollTo({
                    xOffset: x44 > 0 ? x44 : 0,
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
    constructor(m44, n44, o44, p44 = -1, q44 = undefined, r44) {
        super(m44, o44, p44, r44);
        if (typeof q44 === 'function') {
            this.paramsGenerator_ = q44;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(n44.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let s44 = new TabTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    tabTitleDialog: this.item,
                    tabTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 273, col: 14 });
                s44.setController(this.dialogController);
                ViewPU.create(s44);
                let y17 = () => {
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
                s44.paramsGenerator_ = y17;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(n44);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l44) {
        if (l44.menuItems !== undefined) {
            this.menuItems = l44.menuItems;
        }
        if (l44.index !== undefined) {
            this.index = l44.index;
        }
        if (l44.item !== undefined) {
            this.item = l44.item;
        }
        if (l44.minFontSize !== undefined) {
            this.minFontSize = l44.minFontSize;
        }
        if (l44.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = l44.isFollowingSystemFontScale;
        }
        if (l44.maxFontScale !== undefined) {
            this.maxFontScale = l44.maxFontScale;
        }
        if (l44.systemFontScale !== undefined) {
            this.systemFontScale = l44.systemFontScale;
        }
        if (l44.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = l44.firstFocusableIndex;
        }
        if (l44.isPopupShown !== undefined) {
            this.isPopupShown = l44.isPopupShown;
        }
        if (l44.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = l44.isMoreIconOnFocus;
        }
        if (l44.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = l44.isMoreIconOnHover;
        }
        if (l44.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = l44.isMoreIconOnClick;
        }
        if (l44.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (l44.dialogController !== undefined) {
            this.dialogController = l44.dialogController;
        }
        if (l44.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = l44.buttonGestureModifier;
        }
    }
    updateStateVars(k44) {
        this.__fontSize.reset(k44.fontSize);
    }
    purgeVariableDependenciesOnElmtId(j44) {
        this.__isPopupShown.purgeDependencyOnElmtId(j44);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(j44);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(j44);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(j44);
        this.__fontSize.purgeDependencyOnElmtId(j44);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(j44);
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
    set isPopupShown(i44) {
        this.__isPopupShown.set(i44);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(h44) {
        this.__isMoreIconOnFocus.set(h44);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(g44) {
        this.__isMoreIconOnHover.set(g44);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(f44) {
        this.__isMoreIconOnClick.set(f44);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(e44) {
        this.__fontSize.set(e44);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(d44) {
        this.__buttonGestureModifier.set(d44);
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
            let c44 = this.getUIContext();
            this.isFollowingSystemFontScale = c44.isFollowingSystemFontScale();
            this.maxFontScale = c44.getMaxFontScale();
        }
        catch (z43) {
            let a44 = z43?.code;
            let b44 = z43?.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${a44}, message: ${b44}`);
        }
        this.menuItems.forEach((x43, y43) => {
            if (x43.isEnabled && this.firstFocusableIndex === -1 &&
                y43 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + y43 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
            let w43 = this.getUIContext();
            this.systemFontScale = w43.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((u43, v43) => {
            Column.create();
            Column.height('100%');
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((s43, t43) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((o42, p42) => {
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i43, j43) => {
                        ForEach.create();
                        const w17 = (l43, m43) => {
                            const n43 = l43;
                            {
                                this.observeComponentCreation2((o43, p43) => {
                                    if (p43) {
                                        let q43 = new ImageMenuItem(this, { item: n43, index: this.index * 1000 + m43 + 1 }, undefined, o43, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 342, col: 13 });
                                        ViewPU.create(q43);
                                        let x17 = () => {
                                            return {
                                                item: n43,
                                                index: this.index * 1000 + m43 + 1
                                            };
                                        };
                                        q43.paramsGenerator_ = x17;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(o43, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(i43, this.menuItems, w17, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((y42, z42) => {
                        ForEach.create();
                        const u17 = (b43, c43) => {
                            const d43 = b43;
                            {
                                this.observeComponentCreation2((e43, f43) => {
                                    if (f43) {
                                        let g43 = new ImageMenuItem(this, { item: d43, index: this.index * 1000 + c43 + 1 }, undefined, e43, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 347, col: 15 });
                                        ViewPU.create(g43);
                                        let v17 = () => {
                                            return {
                                                item: d43,
                                                index: this.index * 1000 + c43 + 1
                                            };
                                        };
                                        g43.paramsGenerator_ = v17;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(e43, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(y42, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), u17, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    this.observeComponentCreation2((s42, t42) => {
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
                        Button.onHover((x42) => this.isMoreIconOnHover = x42);
                        Button.onKeyEvent((w42) => {
                            if (w42.keyCode !== KeyCode.KEYCODE_ENTER && w42.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (w42.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (w42.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((v42) => {
                            if (v42.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (v42.type === TouchType.Up || v42.type === TouchType.Cancel) {
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
                            onStateChange: (u42) => {
                                this.isPopupShown = u42.isVisible;
                                if (!u42.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                    }, Button);
                    this.observeComponentCreation2((q42, r42) => {
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
    onPlaceChildren(k42, l42, m42) {
        l42.forEach((n42) => {
            n42.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(x41 = null) {
        this.observeComponentCreation2((i42, j42) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((y41, z41) => {
            ForEach.create();
            const s17 = (b42, c42) => {
                const d42 = b42;
                {
                    this.observeComponentCreation2((e42, f42) => {
                        if (f42) {
                            let g42 = new ImageMenuItem(this, { item: d42, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + c42 }, undefined, e42, () => { }, { page: 'library/src/main/ets/components/tabtitlebar.ets', line: 437, col: 11 });
                            ViewPU.create(g42);
                            let t17 = () => {
                                return {
                                    item: d42,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + c42
                                };
                            };
                            g42.paramsGenerator_ = t17;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(e42, {});
                        }
                    }, { name: 'ImageMenuItem' });
                }
            };
            this.forEachUpdateFunction(y41, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), s17, undefined, true, false);
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
    constructor(r41, s41, t41, u41 = -1, v41 = undefined, w41) {
        super(r41, t41, u41, w41);
        if (typeof v41 === 'function') {
            this.paramsGenerator_ = v41;
        }
        this.item = { title: '' };
        this.index = 0;
        this.maxIndex = 0;
        this.onCustomClick = undefined;
        this.onImageComplete = undefined;
        this.__currentIndex = new SynchedPropertySimpleOneWayPU(s41.currentIndex, this, 'currentIndex');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
        this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
        this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
        this.setInitiallyProvidedValue(s41);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q41) {
        if (q41.item !== undefined) {
            this.item = q41.item;
        }
        if (q41.index !== undefined) {
            this.index = q41.index;
        }
        if (q41.maxIndex !== undefined) {
            this.maxIndex = q41.maxIndex;
        }
        if (q41.onCustomClick !== undefined) {
            this.onCustomClick = q41.onCustomClick;
        }
        if (q41.onImageComplete !== undefined) {
            this.onImageComplete = q41.onImageComplete;
        }
        if (q41.isOnFocus !== undefined) {
            this.isOnFocus = q41.isOnFocus;
        }
        if (q41.isOnHover !== undefined) {
            this.isOnHover = q41.isOnHover;
        }
        if (q41.isOnClick !== undefined) {
            this.isOnClick = q41.isOnClick;
        }
        if (q41.tabWidth !== undefined) {
            this.tabWidth = q41.tabWidth;
        }
        if (q41.imageWidth !== undefined) {
            this.imageWidth = q41.imageWidth;
        }
        if (q41.imageHeight !== undefined) {
            this.imageHeight = q41.imageHeight;
        }
    }
    updateStateVars(p41) {
        this.__currentIndex.reset(p41.currentIndex);
    }
    purgeVariableDependenciesOnElmtId(o41) {
        this.__currentIndex.purgeDependencyOnElmtId(o41);
        this.__isOnFocus.purgeDependencyOnElmtId(o41);
        this.__isOnHover.purgeDependencyOnElmtId(o41);
        this.__isOnClick.purgeDependencyOnElmtId(o41);
        this.__tabWidth.purgeDependencyOnElmtId(o41);
        this.__imageWidth.purgeDependencyOnElmtId(o41);
        this.__imageHeight.purgeDependencyOnElmtId(o41);
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
    set currentIndex(n41) {
        this.__currentIndex.set(n41);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(m41) {
        this.__isOnFocus.set(m41);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(l41) {
        this.__isOnHover.set(l41);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(k41) {
        this.__isOnClick.set(k41);
    }
    get tabWidth() {
        return this.__tabWidth.get();
    }
    set tabWidth(j41) {
        this.__tabWidth.set(j41);
    }
    get imageWidth() {
        return this.__imageWidth.get();
    }
    set imageWidth(i41) {
        this.__imageWidth.set(i41);
    }
    get imageHeight() {
        return this.__imageHeight.get();
    }
    set imageHeight(h41) {
        this.__imageHeight.set(h41);
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
    toStringFormat(c41) {
        if (typeof c41 === 'string') {
            return c41;
        }
        else if (typeof c41 === 'undefined') {
            return '';
        }
        else {
            let d41 = '';
            try {
                d41 = getContext()?.resourceManager?.getStringSync(c41);
            }
            catch (e41) {
                let f41 = e41?.code;
                let g41 = e41?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${f41},message:${g41}`);
            }
            return d41;
        }
    }
    initialRender() {
        this.observeComponentCreation2((a41, b41) => {
            Stack.create();
            Stack.margin({
                left: this.index === 0 ? TabContentItem.marginFirst : 0,
                right: this.index === this.maxIndex ? 12 : 0
            });
        }, Stack);
        this.observeComponentCreation2((w40, x40) => {
            Row.create();
            Row.height(TabTitleBar.totalHeight);
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius(TabContentItem.buttonBorderRadius);
            Row.backgroundColor(this.getBgColor());
            Row.onAreaChange((y40, z40) => {
                this.tabWidth = Number(z40.width);
            });
        }, Row);
        this.observeComponentCreation2((u40, v40) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((w39, x39) => {
            If.create();
            if (this.item.icon === undefined && this.item.symbolStyle === undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p40, q40) => {
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
                        Text.onHover((t40) => this.isOnHover = t40);
                        Text.onKeyEvent((s40) => {
                            if (s40.keyCode !== KeyCode.KEYCODE_ENTER && s40.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (s40.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (s40.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Text.onTouch((r40) => {
                            if (r40.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (r40.type === TouchType.Up || r40.type === TouchType.Cancel) {
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
                    this.observeComponentCreation2((k40, l40) => {
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
                        Row.onHover((o40) => this.isOnHover = o40);
                        Row.onKeyEvent((n40) => {
                            if (n40.keyCode !== KeyCode.KEYCODE_ENTER && n40.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (n40.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (n40.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onTouch((m40) => {
                            if (m40.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (m40.type === TouchType.Up || m40.type === TouchType.Cancel) {
                                this.isOnClick = false;
                            }
                        });
                        Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                        Row.accessibilitySelected(this.index === this.currentIndex);
                    }, Row);
                    this.observeComponentCreation2((y39, z39) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i40, j40) => {
                                    SymbolGlyph.create();
                                    Context.animation({ duration: 300 });
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                    SymbolGlyph.fontSize(TabContentItem.symbolSize);
                                    SymbolGlyph.width(this.getImageLayoutWidth());
                                    SymbolGlyph.height(TabContentItem.imageSize);
                                    SymbolGlyph.accessibilityText(this.item.title);
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
                                this.observeComponentCreation2((a40, b40) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.icon)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((g40, h40) => {
                                                SymbolGlyph.create(this.item.icon);
                                                Context.animation({ duration: 300 });
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(TabContentItem.symbolSize);
                                                SymbolGlyph.width(this.getImageLayoutWidth());
                                                SymbolGlyph.height(TabContentItem.imageSize);
                                                SymbolGlyph.accessibilityText(this.item.title);
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
                                            this.observeComponentCreation2((c40, d40) => {
                                                Image.create(this.item.icon);
                                                Context.animation({ duration: 300 });
                                                Image.alt(this.item.title);
                                                Image.width(this.getImageLayoutWidth());
                                                Image.height(TabContentItem.imageSize);
                                                Image.objectFit(ImageFit.Fill);
                                                Image.accessibilityText(this.item.title);
                                                Image.scale({
                                                    x: this.getImageScaleFactor(),
                                                    y: this.getImageScaleFactor()
                                                });
                                                Context.animation(null);
                                                Image.hitTestBehavior(HitTestMode.None);
                                                Image.focusable(true);
                                                Image.onComplete((f40) => {
                                                    if (!this.onImageComplete) {
                                                        return;
                                                    }
                                                    this.imageWidth = px2vp(f40?.width);
                                                    this.imageHeight = px2vp(f40?.height);
                                                    this.onImageComplete(px2vp(f40?.componentWidth) +
                                                    TabContentItem.paddingLeft + TabContentItem.paddingRight);
                                                });
                                                Image.onError((e40) => {
                                                    if (!this.onImageComplete) {
                                                        return;
                                                    }
                                                    this.onImageComplete(px2vp(e40.componentWidth) +
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
        this.observeComponentCreation2((s39, t39) => {
            If.create();
            if (this.isOnFocus && this.tabWidth > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u39, v39) => {
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
    constructor(m39, n39, o39, p39 = -1, q39 = undefined, r39) {
        super(m39, o39, p39, r39);
        if (typeof q39 === 'function') {
            this.paramsGenerator_ = q39;
        }
        this.item = { value: '' };
        this.index = 0;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.setInitiallyProvidedValue(n39);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l39) {
        if (l39.item !== undefined) {
            this.item = l39.item;
        }
        if (l39.index !== undefined) {
            this.index = l39.index;
        }
        if (l39.isOnFocus !== undefined) {
            this.isOnFocus = l39.isOnFocus;
        }
        if (l39.isOnHover !== undefined) {
            this.isOnHover = l39.isOnHover;
        }
        if (l39.isOnClick !== undefined) {
            this.isOnClick = l39.isOnClick;
        }
    }
    updateStateVars(k39) {
    }
    purgeVariableDependenciesOnElmtId(j39) {
        this.__isOnFocus.purgeDependencyOnElmtId(j39);
        this.__isOnHover.purgeDependencyOnElmtId(j39);
        this.__isOnClick.purgeDependencyOnElmtId(j39);
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
    set isOnFocus(i39) {
        this.__isOnFocus.set(i39);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(h39) {
        this.__isOnHover.set(h39);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(g39) {
        this.__isOnClick.set(g39);
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
    toStringFormat(b39) {
        if (typeof b39 === 'string') {
            return b39;
        }
        else if (typeof b39 === 'undefined') {
            return '';
        }
        else {
            let c39 = '';
            try {
                c39 = getContext()?.resourceManager?.getStringSync(b39);
            }
            catch (d39) {
                let e39 = d39?.code;
                let f39 = d39?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${e39},message:${f39}`);
            }
            return c39;
        }
    }

    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_MORE) {
            try {
                return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
            } catch (d39) {
                let e39 = d39?.code;
                let f39 = d39?.message;
                hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${e39},message:${f39}`);
            }
        } else if (this.item.accessibilityText) {
            return this.item.accessibilityText;
        } else if (this.item.label) {
            return this.item.label;
        }
        return ' ';
    }
    initialRender() {
        this.observeComponentCreation2((w38, x38) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.accessibilityText(this.getAccessibilityReadText());
            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
            Button.accessibilityDescription(this.item?.accessibilityDescription);
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneWidth);
            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
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
            Button.onHover((a39) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = a39;
            });
            Button.onKeyEvent((z38) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (z38.keyCode !== KeyCode.KEYCODE_ENTER && z38.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (z38.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (z38.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((y38) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (y38.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (y38.type === TouchType.Up || y38.type === TouchType.Cancel) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        this.observeComponentCreation2((m38, n38) => {
            If.create();
            if (this.item.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u38, v38) => {
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
                    this.observeComponentCreation2((o38, p38) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s38, t38) => {
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
                                this.observeComponentCreation2((q38, r38) => {
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
    constructor(g38, h38, i38, j38 = -1, k38 = undefined, l38) {
        super(g38, i38, j38, l38);
        if (typeof k38 === 'function') {
            this.paramsGenerator_ = k38;
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
        this.setInitiallyProvidedValue(h38);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f38) {
        if (f38.tabTitleDialog !== undefined) {
            this.tabTitleDialog = f38.tabTitleDialog;
        }
        if (f38.callbackId !== undefined) {
            this.callbackId = f38.callbackId;
        }
        if (f38.tabTitleBarDialog !== undefined) {
            this.tabTitleBarDialog = f38.tabTitleBarDialog;
        }
        if (f38.mainWindowStage !== undefined) {
            this.mainWindowStage = f38.mainWindowStage;
        }
        if (f38.controller !== undefined) {
            this.controller = f38.controller;
        }
        if (f38.minFontSize !== undefined) {
            this.minFontSize = f38.minFontSize;
        }
        if (f38.maxFontSize !== undefined) {
            this.maxFontSize = f38.maxFontSize;
        }
        if (f38.screenWidth !== undefined) {
            this.screenWidth = f38.screenWidth;
        }
        if (f38.verticalScreenLines !== undefined) {
            this.verticalScreenLines = f38.verticalScreenLines;
        }
        if (f38.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = f38.horizontalsScreenLines;
        }
        if (f38.fontSize !== undefined) {
            this.fontSize = f38.fontSize;
        }
        if (f38.maxLines !== undefined) {
            this.maxLines = f38.maxLines;
        }
        if (f38.cancel !== undefined) {
            this.cancel = f38.cancel;
        }
        if (f38.confirm !== undefined) {
            this.confirm = f38.confirm;
        }
    }
    updateStateVars(e38) {
    }
    purgeVariableDependenciesOnElmtId(d38) {
        this.__mainWindow.purgeDependencyOnElmtId(d38);
        this.__fontSize.purgeDependencyOnElmtId(d38);
        this.__maxLines.purgeDependencyOnElmtId(d38);
        this.__windowStandardHeight.purgeDependencyOnElmtId(d38);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(c38) {
        this.controller = c38;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(b38) {
        this.__mainWindow.set(b38);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a38) {
        this.__fontSize.set(a38);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(z37) {
        this.__maxLines.set(z37);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(y37) {
        this.__windowStandardHeight.set(y37);
    }
    initialRender() {
        this.observeComponentCreation2((u36, v36) => {
            If.create();
            if (this.tabTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w37, x37) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((m37, n37) => {
                        If.create();
                        if (this.tabTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u37, v37) => {
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
                                this.observeComponentCreation2((o37, p37) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.tabTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((s37, t37) => {
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
                                            this.observeComponentCreation2((q37, r37) => {
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
                    this.observeComponentCreation2((k37, l37) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((i37, j37) => {
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
                    this.observeComponentCreation2((g37, h37) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((w36, x36) => {
                        If.create();
                        if (this.tabTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e37, f37) => {
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
                                this.observeComponentCreation2((y36, z36) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.tabTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((c37, d37) => {
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
                                            this.observeComponentCreation2((a37, b37) => {
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
        try {
            let r36 = this.getUIContext().getHostContext();
            this.mainWindowStage = r36.windowStage.getMainWindowSync();
            let s36 = this.mainWindowStage.getWindowProperties();
            let t36 = s36.windowRect;
            if (px2vp(t36.height) > this.screenWidth) {
                this.maxLines = this.verticalScreenLines;
            } else {
                this.maxLines = this.horizontalsScreenLines;
            }
        } catch (z43) {
            let a44 = z43?.code;
            let b44 = z43?.message;
            hilog.error(0x3900, 'tabTitleBar', `Faild to getSystemFontScale,cause, code: ${a44}, message: ${b44}`);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class Util {
    static isSymbolResource(p36) {
        if (!Util.isResourceType(p36)) {
            return false;
        }
        let q36 = p36;
        return q36.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(o36) {
        if (!o36) {
            return false;
        }
        if (typeof o36 === 'string' || typeof o36 === 'undefined') {
            return false;
        }
        return true;
    }
}

export default {
  TabTitleBar: TabTitleBar
};