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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const MeasureText = requireNapi('measure');
const hilog = requireNapi('hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_more'],
  'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
export class TabTitleBar extends ViewPU {
  constructor(g9, h9, i9, j9 = -1, k9 = undefined, l9) {
    super(g9, i9, j9, l9);
    if (typeof k9 === 'function') {
      this.paramsGenerator_ = k9;
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
    this.setInitiallyProvidedValue(h9);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(f9) {
    if (f9.tabItems !== undefined) {
      this.tabItems = f9.tabItems;
    }
    if (f9.menuItems !== undefined) {
      this.menuItems = f9.menuItems;
    }
    if (f9.swiperContent !== undefined) {
      this.swiperContent = f9.swiperContent;
    }
    if (f9.tabWidth !== undefined) {
      this.tabWidth = f9.tabWidth;
    }
    if (f9.currentIndex !== undefined) {
      this.currentIndex = f9.currentIndex;
    }
    if (f9.fontSize !== undefined) {
      this.fontSize = f9.fontSize;
    }
    if (f9.menuSectionWidth !== undefined) {
      this.menuSectionWidth = f9.menuSectionWidth;
    }
    if (f9.tabOffsets !== undefined) {
      this.tabOffsets = f9.tabOffsets;
    }
    if (f9.imageWidths !== undefined) {
      this.imageWidths = f9.imageWidths;
    }
    if (f9.scroller !== undefined) {
      this.scroller = f9.scroller;
    }
    if (f9.swiperController !== undefined) {
      this.swiperController = f9.swiperController;
    }
    if (f9.settings !== undefined) {
      this.settings = f9.settings;
    }
    if (f9.leftContext2D !== undefined) {
      this.leftContext2D = f9.leftContext2D;
    }
    if (f9.rightContext2D !== undefined) {
      this.rightContext2D = f9.rightContext2D;
    }
  }
  updateStateVars(e9) {
  }
  purgeVariableDependenciesOnElmtId(d9) {
    this.__tabWidth.purgeDependencyOnElmtId(d9);
    this.__currentIndex.purgeDependencyOnElmtId(d9);
    this.__fontSize.purgeDependencyOnElmtId(d9);
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
  set tabWidth(c9) {
    this.__tabWidth.set(c9);
  }
  get currentIndex() {
    return this.__currentIndex.get();
  }
  set currentIndex(b9) {
    this.__currentIndex.set(b9);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(a9) {
    this.__fontSize.set(a9);
  }
  GradientMask(p8, q8, r8, s8, t8, u8 = null) {
    this.observeComponentCreation2((y8, z8) => {
      Column.create();
      Column.blendMode(BlendMode.DST_OUT);
      Column.width(TabTitleBar.gradientMaskWidth);
      Column.height(TabTitleBar.totalHeight);
    }, Column);
    this.observeComponentCreation2((v8, w8) => {
      Canvas.create(p8);
      Canvas.width(TabTitleBar.gradientMaskWidth);
      Canvas.height(TabTitleBar.totalHeight);
      Canvas.onReady(() => {
        let x8 = p8.createLinearGradient(q8, r8, s8, t8);
        x8.addColorStop(0.0, '#ffffffff');
        x8.addColorStop(1, '#00ffffff');
        p8.fillStyle = x8;
        p8.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
      });
    }, Canvas);
    Canvas.pop();
    Column.pop();
  }
  emptyBuilder(o8 = null) {
  }
  aboutToAppear() {
    if (!this.swiperContent) {
      this.swiperContent = this.emptyBuilder;
    }
    this.tabItems.forEach((n8) => {
      this.imageWidths.push(0);
    });
    this.loadOffsets();
  }
  loadOffsets() {
    this.tabOffsets.length = 0;
    let k8 = 0;
    this.tabOffsets.push(k8);
    k8 += TabContentItem.marginFirst;
    this.tabItems.forEach((l8, m8) => {
      if (l8.icon !== undefined) {
        if (Math.abs(this.imageWidths[m8]) > TabContentItem.imageHotZoneWidth) {
          k8 += this.imageWidths[m8];
        } else {
          k8 += TabContentItem.imageHotZoneWidth;
        }
      } else {
        k8 += TabContentItem.paddingLeft;
        k8 += px2vp(MeasureText.measureText({
          textContent: l8.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        }));
        k8 += TabContentItem.paddingRight;
      }
      this.tabOffsets.push(k8);
    });
  }
  initialRender() {
    this.observeComponentCreation2((i8, j8) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((e8, f8) => {
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Flex.onAreaChange((g8, h8) => {
        this.tabWidth = Number(h8.width) - this.menuSectionWidth;
      });
    }, Flex);
    this.observeComponentCreation2((c8, d8) => {
      Stack.create({ alignContent: Alignment.End });
      Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
    }, Stack);
    this.observeComponentCreation2((a8, b8) => {
      Stack.create({ alignContent: Alignment.Start });
    }, Stack);
    this.observeComponentCreation2((y7, z7) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((w7, x7) => {
      List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
      List.width('100%');
      List.height(TabTitleBar.totalHeight);
      List.constraintSize({ maxWidth: this.tabWidth });
      List.edgeEffect(EdgeEffect.Spring);
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
    }, List);
    this.observeComponentCreation2((z6, a7) => {
      ForEach.create();
      const b7 = (c7, d7) => {
        const e7 = c7;
        {
          const f7 = (u7, v7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u7);
            g7(u7, v7);
            if (!v7) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const g7 = (s7, t7) => {
            ListItem.create(h7, true);
          };
          const h7 = (i7, j7) => {
            f7(i7, j7);
            {
              this.observeComponentCreation2((k7, l7) => {
                if (l7) {
                  let m7 = new TabContentItem(this, {
                    item: e7,
                    index: d7,
                    maxIndex: this.tabItems.length - 1,
                    currentIndex: this.currentIndex,
                    onCustomClick: (r7) => this.currentIndex = r7,
                    onImageComplete: (q7) => {
                      this.imageWidths[d7] = q7;
                      this.loadOffsets();
                    }
                  }, undefined, k7, () => { }, { page: 'library/src/main/ets/components/MainPage.ets',
                    line: 138, col: 21 });
                  ViewPU.create(m7);
                  let n7 = () => {
                    return {
                      item: e7,
                      index: d7,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (p7) => this.currentIndex = p7,
                      onImageComplete: (o7) => {
                        this.imageWidths[d7] = o7;
                        this.loadOffsets();
                      }
                    };
                  };
                  m7.paramsGenerator_ = n7;
                }
                else {
                  this.updateStateVarsOfChildByElmtId(k7, {
                    currentIndex: this.currentIndex
                  });
                }
              }, { name: 'TabContentItem' });
            }
            ListItem.pop();
          };
          this.observeComponentCreation2(g7, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(z6, this.tabItems, b7, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    List.pop();
    Column.pop();
    this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth,
      TabTitleBar.totalHeight / 2);
    Stack.pop();
    this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0,
      TabTitleBar.totalHeight / 2);
    Stack.pop();
    this.observeComponentCreation2((p6, q6) => {
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v6, w6) => {
            __Common__.create();
            __Common__.height(TabTitleBar.totalHeight);
            __Common__.onAreaChange((x6, y6) => {
              this.menuSectionWidth = Number(y6.width);
            });
          }, __Common__);
          {
            this.observeComponentCreation2((r6, s6) => {
              if (s6) {
                let t6 = new CollapsibleMenuSection(this, { menuItems: this.menuItems,
                  index: 1 + TabTitleBar.instanceCount++ }, undefined, r6, () => { },
                  { page: 'library/src/main/ets/components/MainPage.ets', line: 168, col: 11 });
                ViewPU.create(t6);
                let u6 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + TabTitleBar.instanceCount++
                  };
                };
                t6.paramsGenerator_ = u6;
              } else {
                this.updateStateVarsOfChildByElmtId(r6, {});
              }
            }, { name: 'CollapsibleMenuSection' });
          }
          __Common__.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Flex.pop();
    this.observeComponentCreation2((n6, o6) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((j6, k6) => {
      Swiper.create(this.swiperController);
      Swiper.index(this.currentIndex);
      Swiper.itemSpace(0);
      Swiper.indicator(false);
      Swiper.width('100%');
      Swiper.height('100%');
      Swiper.curve(Curve.Friction);
      Swiper.onChange((l6) => {
        const m6 = this.tabOffsets[l6] + TabTitleBar.correctionOffset;
        this.currentIndex = l6;
        this.scroller.scrollTo({
          xOffset: m6 > 0 ? m6 : 0,
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
  constructor(b6, c6, d6, e6 = -1, f6 = undefined, g6) {
    super(b6, d6, e6, g6);
    if (typeof f6 === 'function') {
      this.paramsGenerator_ = f6;
    }
    this.menuItems = [];
    this.index = 0;
    this.item = {
      value: PUBLIC_MORE,
      label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    };
    this.longPressTime = 500;
    this.minFontSize = 1.75;
    this.isFollowingSystemFontScale = false;
    this.maxFontScale = 1;
    this.systemFontScale = 1;
    this.firstFocusableIndex = -1;
    this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
    this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
    this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
    this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
    this.__fontSize = new SynchedPropertySimpleOneWayPU(c6.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let h6 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          tabTitleDialog: this.item,
          tabTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 237, col: 14 });
        h6.setController(this.dialogController);
        ViewPU.create(h6);
        let i6 = () => {
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
        h6.paramsGenerator_ = i6;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(c6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(a6) {
    if (a6.menuItems !== undefined) {
      this.menuItems = a6.menuItems;
    }
    if (a6.index !== undefined) {
      this.index = a6.index;
    }
    if (a6.item !== undefined) {
      this.item = a6.item;
    }
    if (a6.longPressTime !== undefined) {
      this.longPressTime = a6.longPressTime;
    }
    if (a6.minFontSize !== undefined) {
      this.minFontSize = a6.minFontSize;
    }
    if (a6.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = a6.isFollowingSystemFontScale;
    }
    if (a6.maxFontScale !== undefined) {
      this.maxFontScale = a6.maxFontScale;
    }
    if (a6.systemFontScale !== undefined) {
      this.systemFontScale = a6.systemFontScale;
    }
    if (a6.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = a6.firstFocusableIndex;
    }
    if (a6.isPopupShown !== undefined) {
      this.isPopupShown = a6.isPopupShown;
    }
    if (a6.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = a6.isMoreIconOnFocus;
    }
    if (a6.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = a6.isMoreIconOnHover;
    }
    if (a6.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = a6.isMoreIconOnClick;
    }
    if (a6.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (a6.dialogController !== undefined) {
      this.dialogController = a6.dialogController;
    }
  }
  updateStateVars(z5) {
    this.__fontSize.reset(z5.fontSize);
  }
  purgeVariableDependenciesOnElmtId(y5) {
    this.__isPopupShown.purgeDependencyOnElmtId(y5);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(y5);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(y5);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(y5);
    this.__fontSize.purgeDependencyOnElmtId(y5);
  }
  aboutToBeDeleted() {
    this.__isPopupShown.aboutToBeDeleted();
    this.__isMoreIconOnFocus.aboutToBeDeleted();
    this.__isMoreIconOnHover.aboutToBeDeleted();
    this.__isMoreIconOnClick.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get isPopupShown() {
    return this.__isPopupShown.get();
  }
  set isPopupShown(x5) {
    this.__isPopupShown.set(x5);
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }
  set isMoreIconOnFocus(w5) {
    this.__isMoreIconOnFocus.set(w5);
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }
  set isMoreIconOnHover(v5) {
    this.__isMoreIconOnHover.set(v5);
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }
  set isMoreIconOnClick(u5) {
    this.__isMoreIconOnClick.set(u5);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(t5) {
    this.__fontSize.set(t5);
  }
  getMoreIconFgColor() {
    return this.isMoreIconOnClick
      ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }
  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else if (this.isMoreIconOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else {
      return Color.Transparent;
    }
  }
  aboutToAppear() {
    try {
      let s5 = this.getUIContext();
      this.isFollowingSystemFontScale = s5.isFollowingSystemFontScale();
      this.maxFontScale = s5.getMaxFontScale();
    }
    catch (p5) {
      let q5 = p5.code;
      let r5 = p5.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${q5}, message: ${r5}`);
    }
    this.menuItems.forEach((n5, o5) => {
      if (n5.isEnabled && this.firstFocusableIndex === -1 &&
        o5 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + o5 + 1;
      }
    });
  }
  decideFontScale() {
    let m5 = this.getUIContext();
    this.systemFontScale = m5.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }
  initialRender() {
    this.observeComponentCreation2((k5, l5) => {
      Column.create();
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((i5, j5) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((d4, e4) => {
      If.create();
      if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y4, z4) => {
            ForEach.create();
            const a5 = (b5, c5) => {
              const d5 = b5;
              {
                this.observeComponentCreation2((e5, f5) => {
                  if (f5) {
                    let g5 = new ImageMenuItem(this, { item: d5, index: this.index * 1000 + c5 + 1 },
                      undefined, e5, () => { }, { page: 'library/src/main/ets/components/MainPage.ets',
                        line: 299, col: 13 });
                    ViewPU.create(g5);
                    let h5 = () => {
                      return {
                        item: d5,
                        index: this.index * 1000 + c5 + 1
                      };
                    };
                    g5.paramsGenerator_ = h5;
                  } else {
                    this.updateStateVarsOfChildByElmtId(e5, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(y4, this.menuItems, a5, undefined, true, false);
          }, ForEach);
          ForEach.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((o4, p4) => {
            ForEach.create();
            const q4 = (r4, s4) => {
              const t4 = r4;
              {
                this.observeComponentCreation2((u4, v4) => {
                  if (v4) {
                    let w4 = new ImageMenuItem(this, { item: t4, index: this.index * 1000 + s4 + 1 }, undefined, u4,
                      () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 304, col: 15 });
                    ViewPU.create(w4);
                    let x4 = () => {
                      return {
                        item: t4,
                        index: this.index * 1000 + s4 + 1
                      };
                    };
                    w4.paramsGenerator_ = x4;
                  } else {
                    this.updateStateVarsOfChildByElmtId(u4, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(o4, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              q4, undefined, true, false);
          }, ForEach);
          ForEach.pop();
          this.observeComponentCreation2((h4, i4) => {
            Row.create();
            Row.width(ImageMenuItem.imageHotZoneWidth);
            Row.height(ImageMenuItem.imageHotZoneWidth);
            Row.borderRadius(ImageMenuItem.buttonBorderRadius);
            Row.foregroundColor(this.getMoreIconFgColor());
            Row.backgroundColor(this.getMoreIconBgColor());
            Row.justifyContent(FlexAlign.Center);
            ViewStackProcessor.visualState('focused');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: ImageMenuItem.focusBorderWidth,
              color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              width: 0
            });
            ViewStackProcessor.visualState();
            Row.onFocus(() => this.isMoreIconOnFocus = true);
            Row.onBlur(() => this.isMoreIconOnFocus = false);
            Row.onHover((n4) => this.isMoreIconOnHover = n4);
            Row.onKeyEvent((m4) => {
              if (m4.keyCode !== KeyCode.KEYCODE_ENTER && m4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (m4.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (m4.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Row.onTouch((l4) => {
              if (l4.type === TouchType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (l4.type === TouchType.Up || l4.type === TouchType.Cancel) {
                this.isMoreIconOnClick = false;
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.close();
                }
              }
            });
            Row.onClick(() => this.isPopupShown = true);
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((k4) => {
              this.fontSize = this.decideFontScale();
              if (k4) {
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.open();
                }
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
            Row.bindPopup(this.isPopupShown, {
              builder: { builder: this.popupBuilder.bind(this) },
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (j4) => {
                this.isPopupShown = j4.isVisible;
                if (!j4.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              }
            });
          }, Row);
          this.observeComponentCreation2((f4, g4) => {
            Image.create(PUBLIC_MORE);
            Image.width(ImageMenuItem.imageSize);
            Image.height(ImageMenuItem.imageSize);
            Image.focusable(true);
            Image.draggable(false);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          Row.pop();
        });
      }
    }, If);
    If.pop();
    Row.pop();
    Column.pop();
  }
  popupBuilder(q3 = null) {
    this.observeComponentCreation2((b4, c4) => {
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
    }, Column);
    this.observeComponentCreation2((r3, s3) => {
      ForEach.create();
      const t3 = (u3, v3) => {
        const w3 = u3;
        {
          this.observeComponentCreation2((x3, y3) => {
            if (y3) {
              let z3 = new ImageMenuItem(this, { item: w3,
                index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + v3 }, undefined, x3,
                () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 397, col: 11 });
              ViewPU.create(z3);
              let a4 = () => {
                return {
                  item: w3,
                  index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + v3
                };
              };
              z3.paramsGenerator_ = a4;
            }
            else {
              this.updateStateVarsOfChildByElmtId(x3, {});
            }
          }, { name: 'ImageMenuItem' });
        }
      };
      this.forEachUpdateFunction(r3, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
        this.menuItems.length), t3, undefined, true, false);
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
  constructor(k3, l3, m3, n3 = -1, o3 = undefined, p3) {
    super(k3, m3, n3, p3);
    if (typeof o3 === 'function') {
      this.paramsGenerator_ = o3;
    }
    this.item = { title: '' };
    this.index = 0;
    this.maxIndex = 0;
    this.onCustomClick = undefined;
    this.onImageComplete = undefined;
    this.__currentIndex = new SynchedPropertySimpleOneWayPU(l3.currentIndex, this, 'currentIndex');
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
    this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
    this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
    this.setInitiallyProvidedValue(l3);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(j3) {
    if (j3.item !== undefined) {
      this.item = j3.item;
    }
    if (j3.index !== undefined) {
      this.index = j3.index;
    }
    if (j3.maxIndex !== undefined) {
      this.maxIndex = j3.maxIndex;
    }
    if (j3.onCustomClick !== undefined) {
      this.onCustomClick = j3.onCustomClick;
    }
    if (j3.onImageComplete !== undefined) {
      this.onImageComplete = j3.onImageComplete;
    }
    if (j3.isOnFocus !== undefined) {
      this.isOnFocus = j3.isOnFocus;
    }
    if (j3.isOnHover !== undefined) {
      this.isOnHover = j3.isOnHover;
    }
    if (j3.isOnClick !== undefined) {
      this.isOnClick = j3.isOnClick;
    }
    if (j3.tabWidth !== undefined) {
      this.tabWidth = j3.tabWidth;
    }
    if (j3.imageWidth !== undefined) {
      this.imageWidth = j3.imageWidth;
    }
    if (j3.imageHeight !== undefined) {
      this.imageHeight = j3.imageHeight;
    }
  }
  updateStateVars(i3) {
    this.__currentIndex.reset(i3.currentIndex);
  }
  purgeVariableDependenciesOnElmtId(h3) {
    this.__currentIndex.purgeDependencyOnElmtId(h3);
    this.__isOnFocus.purgeDependencyOnElmtId(h3);
    this.__isOnHover.purgeDependencyOnElmtId(h3);
    this.__isOnClick.purgeDependencyOnElmtId(h3);
    this.__tabWidth.purgeDependencyOnElmtId(h3);
    this.__imageWidth.purgeDependencyOnElmtId(h3);
    this.__imageHeight.purgeDependencyOnElmtId(h3);
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
  set currentIndex(g3) {
    this.__currentIndex.set(g3);
  }
  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(f3) {
    this.__isOnFocus.set(f3);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(e3) {
    this.__isOnHover.set(e3);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(d3) {
    this.__isOnClick.set(d3);
  }
  get tabWidth() {
    return this.__tabWidth.get();
  }
  set tabWidth(c3) {
    this.__tabWidth.set(c3);
  }
  get imageWidth() {
    return this.__imageWidth.get();
  }
  set imageWidth(b3) {
    this.__imageWidth.set(b3);
  }
  get imageHeight() {
    return this.__imageHeight.get();
  }
  set imageHeight(a3) {
    this.__imageHeight.set(a3);
  }
  getBgColor() {
    if (this.isOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }
  getBorderAttr() {
    if (this.isOnFocus) {
      return {
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: TabContentItem.focusBorderWidth,
        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
  initialRender() {
    this.observeComponentCreation2((y2, z2) => {
      Stack.create();
      Stack.margin({
        left: this.index === 0 ? TabContentItem.marginFirst : 0,
        right: this.index === this.maxIndex ? 12 : 0
      });
    }, Stack);
    this.observeComponentCreation2((u2, v2) => {
      Row.create();
      Row.height(TabTitleBar.totalHeight);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.borderRadius(TabContentItem.buttonBorderRadius);
      Row.backgroundColor(this.getBgColor());
      Row.onAreaChange((w2, x2) => {
        this.tabWidth = Number(x2.width);
      });
    }, Row);
    this.observeComponentCreation2((s2, t2) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((c2, d2) => {
      If.create();
      if (this.item.icon === undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((n2, o2) => {
            Text.create(this.item.title);
            Context.animation({ duration: 300 });
            Text.fontSize(this.index === this.currentIndex ?
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline9'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(this.index === this.currentIndex ?
              { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
              { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text_off'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
            Text.onHover((r2) => this.isOnHover = r2);
            Text.onKeyEvent((q2) => {
              if (q2.keyCode !== KeyCode.KEYCODE_ENTER && q2.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (q2.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (q2.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Text.onTouch((p2) => {
              if (p2.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (p2.type === TouchType.Up || p2.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            });
            Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
          }, Text);
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((i2, j2) => {
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
            Row.onHover((m2) => this.isOnHover = m2);
            Row.onKeyEvent((l2) => {
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
            Row.onTouch((k2) => {
              if (k2.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (k2.type === TouchType.Up || k2.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            });
            Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
          }, Row);
          this.observeComponentCreation2((e2, f2) => {
            Image.create(this.item.icon);
            Context.animation({ duration: 300 });
            Image.alt(this.item.title);
            Image.width(this.getImageLayoutWidth());
            Image.height(TabContentItem.imageSize);
            Image.objectFit(ImageFit.Fill);
            Image.scale({
              x: this.getImageScaleFactor(),
              y: this.getImageScaleFactor()
            });
            Context.animation(null);
            Image.hitTestBehavior(HitTestMode.None);
            Image.focusable(true);
            Image.onComplete((h2) => {
              if (!this.onImageComplete) {
                return;
              }
              this.imageWidth = px2vp(h2?.width);
              this.imageHeight = px2vp(h2?.height);
              this.onImageComplete(px2vp(h2?.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
            Image.onError((g2) => {
              if (!this.onImageComplete) {
                return;
              }
              this.onImageComplete(px2vp(g2.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
          }, Image);
          Row.pop();
        });
      }
    }, If);
    If.pop();
    Column.pop();
    Row.pop();
    this.observeComponentCreation2((y1, z1) => {
      If.create();
      if (this.isOnFocus && this.tabWidth > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a2, b2) => {
            Row.create();
            Row.width(this.tabWidth);
            Row.height(TabTitleBar.totalHeight);
            Row.hitTestBehavior(HitTestMode.None);
            Row.borderRadius(TabContentItem.buttonBorderRadius);
            ViewStackProcessor.visualState('focused');
            Row.border(this.getBorderAttr());
            ViewStackProcessor.visualState('normal');
            Row.border({
              radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
TabContentItem.imageHotZoneWidth = 48;
TabContentItem.imageMagnificationFactor = 1.4;
TabContentItem.buttonBorderRadius = 8;
TabContentItem.focusBorderWidth = 2;
TabContentItem.paddingLeft = 8;
TabContentItem.paddingRight = 8;
TabContentItem.marginFirst = 16;
class ImageMenuItem extends ViewPU {
  constructor(s1, t1, u1, v1 = -1, w1 = undefined, x1) {
    super(s1, u1, v1, x1);
    if (typeof w1 === 'function') {
      this.paramsGenerator_ = w1;
    }
    this.item = { value: '' };
    this.index = 0;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.setInitiallyProvidedValue(t1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(r1) {
    if (r1.item !== undefined) {
      this.item = r1.item;
    }
    if (r1.index !== undefined) {
      this.index = r1.index;
    }
    if (r1.isOnFocus !== undefined) {
      this.isOnFocus = r1.isOnFocus;
    }
    if (r1.isOnHover !== undefined) {
      this.isOnHover = r1.isOnHover;
    }
    if (r1.isOnClick !== undefined) {
      this.isOnClick = r1.isOnClick;
    }
  }
  updateStateVars(q1) {
  }
  purgeVariableDependenciesOnElmtId(p1) {
    this.__isOnFocus.purgeDependencyOnElmtId(p1);
    this.__isOnHover.purgeDependencyOnElmtId(p1);
    this.__isOnClick.purgeDependencyOnElmtId(p1);
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
  set isOnFocus(o1) {
    this.__isOnFocus.set(o1);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(n1) {
    this.__isOnHover.set(n1);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(m1) {
    this.__isOnClick.set(m1);
  }
  getFgColor() {
    return this.isOnClick ?
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } :
      { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
  }
  getBgColor() {
    if (this.isOnClick) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else if (this.isOnHover) {
      return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    } else {
      return Color.Transparent;
    }
  }
  initialRender() {
    this.observeComponentCreation2((h1, i1) => {
      Row.create();
      Row.width(ImageMenuItem.imageHotZoneWidth);
      Row.height(ImageMenuItem.imageHotZoneWidth);
      Row.borderRadius(ImageMenuItem.buttonBorderRadius);
      Row.foregroundColor(this.getFgColor());
      Row.backgroundColor(this.getBgColor());
      Row.justifyContent(FlexAlign.Center);
      Row.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
      ViewStackProcessor.visualState('focused');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: ImageMenuItem.focusBorderWidth,
        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        style: BorderStyle.Solid
      });
      ViewStackProcessor.visualState('normal');
      Row.border({
        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
          'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        width: 0
      });
      ViewStackProcessor.visualState();
      Row.onFocus(() => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      });
      Row.onBlur(() => this.isOnFocus = false);
      Row.onHover((l1) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = l1;
      });
      Row.onKeyEvent((k1) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (k1.keyCode !== KeyCode.KEYCODE_ENTER && k1.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (k1.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (k1.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((j1) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (j1.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (j1.type === TouchType.Up || j1.type === TouchType.Cancel) {
          this.isOnClick = false;
        }
      });
      Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
    }, Row);
    this.observeComponentCreation2((f1, g1) => {
      Image.create(this.item.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.draggable(false);
    }, Image);
    Row.pop();
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
  constructor(z, a1, b1, c1 = -1, d1 = undefined, e1) {
    super(z, b1, c1, e1);
    if (typeof d1 === 'function') {
      this.paramsGenerator_ = d1;
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
    this.setInitiallyProvidedValue(a1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(y) {
    if (y.tabTitleDialog !== undefined) {
      this.tabTitleDialog = y.tabTitleDialog;
    }
    if (y.callbackId !== undefined) {
      this.callbackId = y.callbackId;
    }
    if (y.tabTitleBarDialog !== undefined) {
      this.tabTitleBarDialog = y.tabTitleBarDialog;
    }
    if (y.mainWindowStage !== undefined) {
      this.mainWindowStage = y.mainWindowStage;
    }
    if (y.controller !== undefined) {
      this.controller = y.controller;
    }
    if (y.minFontSize !== undefined) {
      this.minFontSize = y.minFontSize;
    }
    if (y.maxFontSize !== undefined) {
      this.maxFontSize = y.maxFontSize;
    }
    if (y.screenWidth !== undefined) {
      this.screenWidth = y.screenWidth;
    }
    if (y.verticalScreenLines !== undefined) {
      this.verticalScreenLines = y.verticalScreenLines;
    }
    if (y.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = y.horizontalsScreenLines;
    }
    if (y.fontSize !== undefined) {
      this.fontSize = y.fontSize;
    }
    if (y.maxLines !== undefined) {
      this.maxLines = y.maxLines;
    }
    if (y.cancel !== undefined) {
      this.cancel = y.cancel;
    }
    if (y.confirm !== undefined) {
      this.confirm = y.confirm;
    }
  }
  updateStateVars(x) {
  }
  purgeVariableDependenciesOnElmtId(w) {
    this.__mainWindow.purgeDependencyOnElmtId(w);
    this.__fontSize.purgeDependencyOnElmtId(w);
    this.__maxLines.purgeDependencyOnElmtId(w);
    this.__windowStandardHeight.purgeDependencyOnElmtId(w);
  }
  aboutToBeDeleted() {
    this.__mainWindow.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__maxLines.aboutToBeDeleted();
    this.__windowStandardHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(v) {
    this.controller = v;
  }
  get mainWindow() {
    return this.__mainWindow.get();
  }
  set mainWindow(u) {
    this.__mainWindow.set(u);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(t) {
    this.__fontSize.set(t);
  }
  get maxLines() {
    return this.__maxLines.get();
  }
  set maxLines(s) {
    this.__maxLines.set(s);
  }
  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }
  set windowStandardHeight(r) {
    this.__windowStandardHeight.set(r);
  }
  initialRender() {
    this.observeComponentCreation2((d, e) => {
      If.create();
      if (this.tabTitleBarDialog) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p, q) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Column);
          this.observeComponentCreation2((n, o) => {
            Image.create(this.tabTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.margin({
              top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          this.observeComponentCreation2((l, m) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
          }, Column);
          this.observeComponentCreation2((j, k) => {
            Text.create(this.tabTitleBarDialog);
            Text.fontSize(TEXT_EDITABLE_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Text);
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((h, i) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((f, g) => {
            Image.create(this.tabTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Image);
          Column.pop();
        });
      }
    }, If);
    If.pop();
  }
  async aboutToAppear() {
    let a = this.getUIContext().getHostContext();
    this.mainWindowStage = a.windowStage.getMainWindowSync();
    let b = this.mainWindowStage.getWindowProperties();
    let c = b.windowRect;
    if (px2vp(c.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    } else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export default {
  TabTitleBar: TabTitleBar
};