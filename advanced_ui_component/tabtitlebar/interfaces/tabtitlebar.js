/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
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
  constructor(b14, c14, d14, e14 = -1, f14 = undefined, g14) {
    super(b14, d14, e14, g14);
    if (typeof f14 === 'function') {
      this.paramsGenerator_ = f14;
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
    this.setInitiallyProvidedValue(c14);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(a14) {
    if (a14.tabItems !== undefined) {
      this.tabItems = a14.tabItems;
    }
    if (a14.menuItems !== undefined) {
      this.menuItems = a14.menuItems;
    }
    if (a14.swiperContent !== undefined) {
      this.swiperContent = a14.swiperContent;
    }
    if (a14.tabWidth !== undefined) {
      this.tabWidth = a14.tabWidth;
    }
    if (a14.currentIndex !== undefined) {
      this.currentIndex = a14.currentIndex;
    }
    if (a14.fontSize !== undefined) {
      this.fontSize = a14.fontSize;
    }
    if (a14.menuSectionWidth !== undefined) {
      this.menuSectionWidth = a14.menuSectionWidth;
    }
    if (a14.tabOffsets !== undefined) {
      this.tabOffsets = a14.tabOffsets;
    }
    if (a14.imageWidths !== undefined) {
      this.imageWidths = a14.imageWidths;
    }
    if (a14.scroller !== undefined) {
      this.scroller = a14.scroller;
    }
    if (a14.swiperController !== undefined) {
      this.swiperController = a14.swiperController;
    }
    if (a14.settings !== undefined) {
      this.settings = a14.settings;
    }
    if (a14.leftContext2D !== undefined) {
      this.leftContext2D = a14.leftContext2D;
    }
    if (a14.rightContext2D !== undefined) {
      this.rightContext2D = a14.rightContext2D;
    }
  }

  updateStateVars(z13) {
  }

  purgeVariableDependenciesOnElmtId(y13) {
    this.__tabWidth.purgeDependencyOnElmtId(y13);
    this.__currentIndex.purgeDependencyOnElmtId(y13);
    this.__fontSize.purgeDependencyOnElmtId(y13);
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

  set tabWidth(x13) {
    this.__tabWidth.set(x13);
  }

  get currentIndex() {
    return this.__currentIndex.get();
  }

  set currentIndex(w13) {
    this.__currentIndex.set(w13);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(v13) {
    this.__fontSize.set(v13);
  }

  GradientMask(h13, i13, j13, k13, l13, m13 = null) {
    this.observeComponentCreation2((t13, u13) => {
      Column.create();
      Column.blendMode(BlendMode.DST_OUT);
      Column.width(TabTitleBar.gradientMaskWidth);
      Column.height(TabTitleBar.totalHeight);
    }, Column);
    this.observeComponentCreation2((p13, q13) => {
      Canvas.create(h13);
      Canvas.width(TabTitleBar.gradientMaskWidth);
      Canvas.height(TabTitleBar.totalHeight);
      Canvas.onReady(() => {
        let s13 = h13.createLinearGradient(i13, j13, k13, l13);
        s13.addColorStop(0.0, '#ffffffff');
        s13.addColorStop(1, '#00ffffff');
        h13.fillStyle = s13;
        h13.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
      });
    }, Canvas);
    Canvas.pop();
    Column.pop();
  }

  aboutToAppear() {
    this.tabItems.forEach((g13) => {
      this.imageWidths.push(0);
    });
    this.loadOffsets();
  }

  loadOffsets() {
    this.tabOffsets.length = 0;
    let b13 = 0;
    this.tabOffsets.push(b13);
    b13 += TabContentItem.marginFirst;
    this.tabItems.forEach((d13, e13) => {
      if (d13.icon !== undefined) {
        if (Math.abs(this.imageWidths[e13]) > TabContentItem.imageHotZoneWidth) {
          b13 += this.imageWidths[e13];
        } else {
          b13 += TabContentItem.imageHotZoneWidth;
        }
      } else {
        b13 += TabContentItem.paddingLeft;
        b13 += px2vp(MeasureText.measureText({
          textContent: d13.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        }));
        b13 += TabContentItem.paddingRight;
      }
      this.tabOffsets.push(b13);
    });
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((z12, a13) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((u12, v12) => {
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'],
        'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Flex.onAreaChange((x12, y12) => {
        this.tabWidth = Number(y12.width) - this.menuSectionWidth;
      });
    }, Flex);
    this.observeComponentCreation2((s12, t12) => {
      Stack.create({ alignContent: Alignment.End });
      Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
    }, Stack);
    this.observeComponentCreation2((q12, r12) => {
      Stack.create({ alignContent: Alignment.Start });
    }, Stack);
    this.observeComponentCreation2((o12, p12) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((m12, n12) => {
      List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
      List.width('100%');
      List.height(TabTitleBar.totalHeight);
      List.constraintSize({ maxWidth: this.tabWidth });
      List.edgeEffect(EdgeEffect.Spring);
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
    }, List);
    this.observeComponentCreation2((i11, j11) => {
      ForEach.create();
      const k11 = (m11, n11) => {
        const o11 = m11;
        {
          const p11 = (k12, l12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k12);
            q11(k12, l12);
            if (!l12) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const q11 = (i12, j12) => {
            ListItem.create(r11, true);
          };
          const r11 = (v11, w11) => {
            p11(v11, w11);
            {
              this.observeComponentCreation2((y11, z11) => {
                if (z11) {
                  let a12 = new TabContentItem(this, {
                    item: o11,
                    index: n11,
                    maxIndex: this.tabItems.length - 1,
                    currentIndex: this.currentIndex,
                    onCustomClick: (h12) => this.currentIndex = h12,
                    onImageComplete: (g12) => {
                      this.imageWidths[n11] = g12;
                      this.loadOffsets();
                    }
                  }, undefined, y11, () => { }, { page: 'library/src/main/ets/components/MainPage.ets',
                    line: 129, col: 21 });
                  ViewPU.create(a12);
                  let b12 = () => {
                    return {
                      item: o11,
                      index: n11,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (f12) => this.currentIndex = f12,
                      onImageComplete: (e12) => {
                        this.imageWidths[n11] = e12;
                        this.loadOffsets();
                      }
                    };
                  };
                  a12.paramsGenerator_ = b12;
                }
                else {
                  this.updateStateVarsOfChildByElmtId(y11, {
                    currentIndex: this.currentIndex
                  });
                }
              }, { name: 'TabContentItem' });
            }
            ListItem.pop();
          };
          this.observeComponentCreation2(q11, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(i11, this.tabItems, k11, undefined, true, false);
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
    this.observeComponentCreation2((r10, s10) => {
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((d11, e11) => {
            __Common__.create();
            __Common__.height(TabTitleBar.totalHeight);
            __Common__.onAreaChange((g11, h11) => {
              this.menuSectionWidth = Number(h11.width);
            });
          }, __Common__);
          {
            this.observeComponentCreation2((x10, y10) => {
              if (y10) {
                let z10 = new CollapsibleMenuSection(this, { menuItems: this.menuItems,
                  index: 1 + TabTitleBar.instanceCount++ }, undefined, x10, () => { },
                  { page: 'library/src/main/ets/components/MainPage.ets', line: 159, col: 11 });
                ViewPU.create(z10);
                let a11 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + TabTitleBar.instanceCount++
                  };
                };
                z10.paramsGenerator_ = a11;
              } else {
                this.updateStateVarsOfChildByElmtId(x10, {});
              }
            }, { name: 'CollapsibleMenuSection '});
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
    this.observeComponentCreation2((p10, q10) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((j10, k10) => {
      Swiper.create(this.swiperController);
      Swiper.index(this.currentIndex);
      Swiper.itemSpace(0);
      Swiper.indicator(false);
      Swiper.width('100%');
      Swiper.height('100%');
      Swiper.curve(Curve.Friction);
      Swiper.onChange((n10) => {
        const o10 = this.tabOffsets[n10] + TabTitleBar.correctionOffset;
        this.currentIndex = n10;
        this.scroller.scrollTo({
          xOffset: o10 > 0 ? o10 : 0,
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
  constructor(p9, q9, r9, s9 = -1, t9 = undefined, u9) {
    super(p9, r9, s9, u9);
    if (typeof t9 === 'function') {
      this.paramsGenerator_ = t9;
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
    this.__fontSize = new SynchedPropertySimpleOneWayPU(q9.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let v9 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          tabTitleDialog: this.item,
          tabTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 225, col: 14 });
        v9.setController(this.dialogController);
        ViewPU.create(v9);
        let w9 = () => {
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
        v9.paramsGenerator_ = w9;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(q9);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(b9) {
    if (b9.menuItems !== undefined) {
      this.menuItems = b9.menuItems;
    }
    if (b9.index !== undefined) {
      this.index = b9.index;
    }
    if (b9.item !== undefined) {
      this.item = b9.item;
    }
    if (b9.longPressTime !== undefined) {
      this.longPressTime = b9.longPressTime;
    }
    if (b9.minFontSize !== undefined) {
      this.minFontSize = b9.minFontSize;
    }
    if (b9.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = b9.isFollowingSystemFontScale;
    }
    if (b9.maxFontScale !== undefined) {
      this.maxFontScale = b9.maxFontScale;
    }
    if (b9.systemFontScale !== undefined) {
      this.systemFontScale = b9.systemFontScale;
    }
    if (b9.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = b9.firstFocusableIndex;
    }
    if (b9.isPopupShown !== undefined) {
      this.isPopupShown = b9.isPopupShown;
    }
    if (b9.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = b9.isMoreIconOnFocus;
    }
    if (b9.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = b9.isMoreIconOnHover;
    }
    if (b9.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = b9.isMoreIconOnClick;
    }
    if (b9.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (b9.dialogController !== undefined) {
      this.dialogController = b9.dialogController;
    }
  }

  updateStateVars(w9) {
    this.__fontSize.reset(w9.fontSize);
  }

  purgeVariableDependenciesOnElmtId(v9) {
    this.__isPopupShown.purgeDependencyOnElmtId(v9);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(v9);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(v9);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(v9);
    this.__fontSize.purgeDependencyOnElmtId(v9);
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
  set isPopupShown(u9) {
    this.__isPopupShown.set(u9);
  }

  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }

  set isMoreIconOnFocus(t9) {
    this.__isMoreIconOnFocus.set(t9);
  }

  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }

  set isMoreIconOnHover(s9) {
    this.__isMoreIconOnHover.set(s9);
  }

  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }

  set isMoreIconOnClick(r9) {
    this.__isMoreIconOnClick.set(r9);
  }

  get fontSize() {
    return this.__fontSize.get();
  }

  set fontSize(q9) {
    this.__fontSize.set(q9);
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
      let t8 = this.getUIContext();
      this.isFollowingSystemFontScale = t8.isFollowingSystemFontScale();
      this.maxFontScale = t8.getMaxFontScale();
    }
    catch (q8) {
      let r8 = q8.code;
      let s8 = q8.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${r8}, message: ${s8}`);
    }
    this.menuItems.forEach((o8, p8) => {
      if (o8.isEnabled && this.firstFocusableIndex === -1 &&
        p8 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + p8 + 1;
      }
    });
  }

  decideFontScale() {
    let m8 = this.getUIContext();
    this.systemFontScale = m8.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((c9, d9) => {
      Column.create();
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((a9, b9) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((z6, a7) => {
      If.create();
      if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((m8, n8) => {
            ForEach.create();
            const o8 = (q8, r8) => {
              const s8 = q8;
              {
                this.observeComponentCreation2((u8, v8) => {
                  if (v8) {
                    let w8 = new ImageMenuItem(this, { item: s8, index: this.index * 1000 + r8 + 1 }, undefined, u8,
                      () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 269, col: 13 });
                    ViewPU.create(w8);
                    let x8 = () => {
                      return {
                        item: s8,
                        index: this.index * 1000 + r8 + 1
                      };
                    };
                    w8.paramsGenerator_ = x8;
                  } else {
                    this.updateStateVarsOfChildByElmtId(u8, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(m8, this.menuItems, o8, undefined, true, false);
          }, ForEach);
          ForEach.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((w7, x7) => {
            ForEach.create();
            const y7 = (a8, b8) => {
              const c8 = a8;
              {
                this.observeComponentCreation2((e8, f8) => {
                  if (f8) {
                    let g8 = new ImageMenuItem(this, { item: c8, index: this.index * 1000 + b8 + 1 }, undefined, e8,
                      () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 274, col: 15 });
                    ViewPU.create(g8);
                    let h8 = () => {
                      return {
                        item: c8,
                        index: this.index * 1000 + b8 + 1
                      };
                    };
                    g8.paramsGenerator_ = h8;
                  } else {
                    this.updateStateVarsOfChildByElmtId(e8, {});
                  }
                }, { name: 'ImageMenuItem' });
              }
            };
            this.forEachUpdateFunction(w7, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              y7, undefined, true, false);
          }, ForEach);
          ForEach.pop();
          this.observeComponentCreation2((h7, i7) => {
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
            Row.onHover((v7) => this.isMoreIconOnHover = v7);
            Row.onKeyEvent((u7) => {
              if (u7.keyCode !== KeyCode.KEYCODE_ENTER && u7.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (u7.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (u7.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Row.onTouch((t7) => {
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
            Row.onClick(() => this.isPopupShown = true);
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((x7) => {
              this.fontSize = this.decideFontScale();
              if (x7) {
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
              onStateChange: (q7) => {
                this.isPopupShown = q7.isVisible;
                if (!q7.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              }
            });
          }, Row);
          this.observeComponentCreation2((f7, g7) => {
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }

  popupBuilder(c6 = null) {
    this.observeComponentCreation2((t6, u6) => {
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding
        * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
    }, Column);
    this.observeComponentCreation2((f6, g6) => {
      ForEach.create();
      const h6 = (j6, k6) => {
        const l6 = j6;
        {
          this.observeComponentCreation2((n6, o6) => {
            if (o6) {
              let p6 = new ImageMenuItem(this, { item: l6,
                index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + k6 }, undefined, n6,
                () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 368, col: 11 });
              ViewPU.create(p6);
              let q6 = () => {
                return {
                  item: l6,
                  index: this.index * 1000 + CollapsibleMenuSection.maxCountOfVisibleItems + k6
                };
              };
              p6.paramsGenerator_ = q6;
            }
            else {
              this.updateStateVarsOfChildByElmtId(n6, {});
            }
          }, { name: 'ImageMenuItem' });
        }
      };
      this.forEachUpdateFunction(f6, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
        this.menuItems.length), h6, undefined, true, false);
    }, ForEach);
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
  constructor(s5, t5, u5, v5 = -1, w5 = undefined, x5) {
    super(s5, u5, v5, x5);
    if (typeof w5 === 'function') {
      this.paramsGenerator_ = w5;
    }
    this.item = { title: '' };
    this.index = 0;
    this.maxIndex = 0;
    this.onCustomClick = undefined;
    this.onImageComplete = undefined;
    this.__currentIndex = new SynchedPropertySimpleOneWayPU(t5.currentIndex, this, 'currentIndex');
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
    this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
    this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
    this.setInitiallyProvidedValue(t5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(x5) {
    if (x5.item !== undefined) {
      this.item = x5.item;
    }
    if (x5.index !== undefined) {
      this.index = x5.index;
    }
    if (x5.maxIndex !== undefined) {
      this.maxIndex = x5.maxIndex;
    }
    if (x5.onCustomClick !== undefined) {
      this.onCustomClick = x5.onCustomClick;
    }
    if (x5.onImageComplete !== undefined) {
      this.onImageComplete = x5.onImageComplete;
    }
    if (x5.isOnFocus !== undefined) {
      this.isOnFocus = x5.isOnFocus;
    }
    if (x5.isOnHover !== undefined) {
      this.isOnHover = x5.isOnHover;
    }
    if (x5.isOnClick !== undefined) {
      this.isOnClick = x5.isOnClick;
    }
    if (x5.tabWidth !== undefined) {
      this.tabWidth = x5.tabWidth;
    }
    if (x5.imageWidth !== undefined) {
      this.imageWidth = x5.imageWidth;
    }
    if (x5.imageHeight !== undefined) {
      this.imageHeight = x5.imageHeight;
    }
  }
  updateStateVars(w5) {
    this.__currentIndex.reset(w5.currentIndex);
  }
  purgeVariableDependenciesOnElmtId(v5) {
    this.__currentIndex.purgeDependencyOnElmtId(v5);
    this.__isOnFocus.purgeDependencyOnElmtId(v5);
    this.__isOnHover.purgeDependencyOnElmtId(v5);
    this.__isOnClick.purgeDependencyOnElmtId(v5);
    this.__tabWidth.purgeDependencyOnElmtId(v5);
    this.__imageWidth.purgeDependencyOnElmtId(v5);
    this.__imageHeight.purgeDependencyOnElmtId(v5);
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
  set currentIndex(b5) {
    this.__currentIndex.set(b5);
  }
  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(a5) {
    this.__isOnFocus.set(a5);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(z4) {
    this.__isOnHover.set(z4);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(y4) {
    this.__isOnClick.set(y4);
  }
  get tabWidth() {
    return this.__tabWidth.get();
  }
  set tabWidth(x4) {
    this.__tabWidth.set(x4);
  }
  get imageWidth() {
    return this.__imageWidth.get();
  }
  set imageWidth(w4) {
    this.__imageWidth.set(w4);
  }
  get imageHeight() {
    return this.__imageHeight.get();
  }
  set imageHeight(v4) {
    this.__imageHeight.set(v4);
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((t4, u4) => {
      Stack.create();
      Stack.margin({
        left: this.index === 0 ? TabContentItem.marginFirst : 0,
        right: this.index === this.maxIndex ? 12 : 0
      });
    }, Stack);
    this.observeComponentCreation2((o4, p4) => {
      Row.create();
      Row.height(TabTitleBar.totalHeight);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.borderRadius(TabContentItem.buttonBorderRadius);
      Row.backgroundColor(this.getBgColor());
      Row.onAreaChange((r4, s4) => {
        this.tabWidth = Number(s4.width);
      });
    }, Row);
    this.observeComponentCreation2((m4, n4) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((d3, e3) => {
      If.create();
      if (this.item.icon === undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b4, c4) => {
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
            Text.onHover((l4) => this.isOnHover = l4);
            Text.onKeyEvent((k4) => {
              if (k4.keyCode !== KeyCode.KEYCODE_ENTER && k4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (k4.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (k4.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Text.onTouch((j4) => {
              if (j4.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (j4.type === TouchType.Up || j4.type === TouchType.Cancel) {
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
          this.observeComponentCreation2((o3, p3) => {
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
            Row.onHover((y3) => this.isOnHover = y3);
            Row.onKeyEvent((x3) => {
              if (x3.keyCode !== KeyCode.KEYCODE_ENTER && x3.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (x3.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (x3.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Row.onTouch((w3) => {
              if (w3.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (w3.type === TouchType.Up || w3.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            });
            Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
          }, Row);
          this.observeComponentCreation2((i3, j3) => {
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
            Image.onComplete((n3) => {
              if (!this.onImageComplete) {
                return;
              }
              this.imageWidth = px2vp(n3?.width);
              this.imageHeight = px2vp(n3?.height);
              this.onImageComplete(px2vp(n3?.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
            Image.onError((m3) => {
              if (!this.onImageComplete) {
                return;
              }
              this.onImageComplete(px2vp(m3.componentWidth) +
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
    this.observeComponentCreation2((w2, x2) => {
      If.create();
      if (this.isOnFocus && this.tabWidth > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b3, c3) => {
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
  constructor(l2, m2, n2, o2 = -1, p2 = undefined, q2) {
    super(l2, n2, o2, q2);
    if (typeof p2 === 'function') {
      this.paramsGenerator_ = p2;
    }
    this.item = { value: '' };
    this.index = 0;
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.setInitiallyProvidedValue(m2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(k2) {
    if (k2.item !== undefined) {
      this.item = k2.item;
    }
    if (k2.index !== undefined) {
      this.index = k2.index;
    }
    if (k2.isOnFocus !== undefined) {
      this.isOnFocus = k2.isOnFocus;
    }
    if (k2.isOnHover !== undefined) {
      this.isOnHover = k2.isOnHover;
    }
    if (k2.isOnClick !== undefined) {
      this.isOnClick = k2.isOnClick;
    }
  }
  updateStateVars(j2) {
  }
  purgeVariableDependenciesOnElmtId(i2) {
    this.__isOnFocus.purgeDependencyOnElmtId(i2);
    this.__isOnHover.purgeDependencyOnElmtId(i2);
    this.__isOnClick.purgeDependencyOnElmtId(i2);
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
  set isOnFocus(h2) {
    this.__isOnFocus.set(h2);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(g2) {
    this.__isOnHover.set(g2);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(f2) {
    this.__isOnClick.set(f2);
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((u1, v1) => {
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
      Row.onHover((e2) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = e2;
      });
      Row.onKeyEvent((d2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (d2.keyCode !== KeyCode.KEYCODE_ENTER && d2.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (d2.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (d2.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((c2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (c2.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (c2.type === TouchType.Up || c2.type === TouchType.Cancel) {
          this.isOnClick = false;
        }
      });
      Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
    }, Row);
    this.observeComponentCreation2((s1, t1) => {
      Image.create(this.item.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.draggable(false);
    }, Image);
    Row.pop();
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
  constructor(i1, j1, k1, l1 = -1, m1 = undefined, n1) {
    super(i1, k1, l1, n1);
    if (typeof m1 === 'function') {
      this.paramsGenerator_ = m1;
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
    this.setInitiallyProvidedValue(j1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(h1) {
    if (h1.tabTitleDialog !== undefined) {
      this.tabTitleDialog = h1.tabTitleDialog;
    }
    if (h1.callbackId !== undefined) {
      this.callbackId = h1.callbackId;
    }
    if (h1.tabTitleBarDialog !== undefined) {
      this.tabTitleBarDialog = h1.tabTitleBarDialog;
    }
    if (h1.mainWindowStage !== undefined) {
      this.mainWindowStage = h1.mainWindowStage;
    }
    if (h1.controller !== undefined) {
      this.controller = h1.controller;
    }
    if (h1.minFontSize !== undefined) {
      this.minFontSize = h1.minFontSize;
    }
    if (h1.maxFontSize !== undefined) {
      this.maxFontSize = h1.maxFontSize;
    }
    if (h1.screenWidth !== undefined) {
      this.screenWidth = h1.screenWidth;
    }
    if (h1.verticalScreenLines !== undefined) {
      this.verticalScreenLines = h1.verticalScreenLines;
    }
    if (h1.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = h1.horizontalsScreenLines;
    }
    if (h1.fontSize !== undefined) {
      this.fontSize = h1.fontSize;
    }
    if (h1.maxLines !== undefined) {
      this.maxLines = h1.maxLines;
    }
    if (h1.cancel !== undefined) {
      this.cancel = h1.cancel;
    }
    if (h1.confirm !== undefined) {
      this.confirm = h1.confirm;
    }
  }
  updateStateVars(g1) {
  }
  purgeVariableDependenciesOnElmtId(f1) {
    this.__mainWindow.purgeDependencyOnElmtId(f1);
    this.__fontSize.purgeDependencyOnElmtId(f1);
    this.__maxLines.purgeDependencyOnElmtId(f1);
    this.__windowStandardHeight.purgeDependencyOnElmtId(f1);
  }
  aboutToBeDeleted() {
    this.__mainWindow.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__maxLines.aboutToBeDeleted();
    this.__windowStandardHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(e1) {
    this.controller = e1;
  }
  get mainWindow() {
    return this.__mainWindow.get();
  }
  set mainWindow(d1) {
    this.__mainWindow.set(d1);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(c1) {
    this.__fontSize.set(c1);
  }
  get maxLines() {
    return this.__maxLines.get();
  }
  set maxLines(b1) {
    this.__maxLines.set(b1);
  }
  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }
  set windowStandardHeight(a1) {
    this.__windowStandardHeight.set(a1);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((e, f) => {
      If.create();
      if (this.tabTitleBarDialog) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y, z) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
          }, Column);
          this.observeComponentCreation2((w, x) => {
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
          this.observeComponentCreation2((u, v) => {
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
          this.observeComponentCreation2((s, t) => {
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
          this.observeComponentCreation2((l, m) => {
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'],
              'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((j, k) => {
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
export default {
  TabTitleBar: TabTitleBar
};