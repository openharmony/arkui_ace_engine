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
          TabTitleDialog: this.item,
          TabTitleBarDialog: this.item.label ? this.item.label : '',
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
            TabTitleDialog: this.item,
            TabTitleBarDialog: this.item.label ? this.item.label : '',
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
  setInitiallyProvidedValue(x9) {
    if (x9.menuItems !== undefined) {
      this.menuItems = x9.menuItems;
    }
    if (x9.index !== undefined) {
      this.index = x9.index;
    }
    if (x9.item !== undefined) {
      this.item = x9.item;
    }
    if (x9.longPressTime !== undefined) {
      this.longPressTime = x9.longPressTime;
    }
    if (x9.minFontSize !== undefined) {
      this.minFontSize = x9.minFontSize;
    }
    if (x9.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = x9.isFollowingSystemFontScale;
    }
    if (x9.maxFontScale !== undefined) {
      this.maxFontScale = x9.maxFontScale;
    }
    if (x9.systemFontScale !== undefined) {
      this.systemFontScale = x9.systemFontScale;
    }
    if (x9.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = x9.firstFocusableIndex;
    }
    if (x9.isPopupShown !== undefined) {
      this.isPopupShown = x9.isPopupShown;
    }
    if (x9.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = x9.isMoreIconOnFocus;
    }
    if (x9.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = x9.isMoreIconOnHover;
    }
    if (x9.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = x9.isMoreIconOnClick;
    }
    if (x9.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (x9.dialogController !== undefined) {
      this.dialogController = x9.dialogController;
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
    let h = this.getUIContext();
    this.isFollowingSystemFontScale = h.isFollowingSystemFontScale();
    this.maxFontScale = h.getMaxFontScale();
    this.menuItems.forEach((o9, p9) => {
      if (o9.isEnabled && this.firstFocusableIndex == -1 &&
        p9 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + p9 + 1;
      }
    });
  }

  decideFontScale() {
    try {
      let m9 = this.getUIContext();
      this.systemFontScale = m9.getHostContext()?.config.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    }
    catch (j9) {
      let k9 = j9.code;
      let l9 = j9.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${k9}, message: ${l9}`);
      return 1;
    }
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
    this.TabItem = {};
    this.index = 0;
    this.maxIndex = 0;
    this.onCustomClick = undefined;
    this.onImageComplete = undefined;
    this.longPressTime = 500;
    this.minFontSize = 1.75;
    this.isFollowingSystemFontScale = false;
    this.maxFontScale = 1;
    this.systemFontScale = 1;
    this.__currentIndex = new SynchedPropertySimpleOneWayPU(t5.currentIndex, this, 'currentIndex');
    this.__fontSize = new SynchedPropertySimpleOneWayPU(t5.fontSize, this, 'fontSize');
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
    this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
    this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let y5 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          TabTitleDialog: this.ToTabItem(this.item),
          TabTitleBarDialog: this.ToTabItem(this.item).label ? this.ToTabItem(this.item).label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 421, col: 14 });
        y5.setController(this.dialogController);
        ViewPU.create(y5);
        let z5 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            TabTitleDialog: this.ToTabItem(this.item),
            TabTitleBarDialog: this.ToTabItem(this.item).label ? this.ToTabItem(this.item).label : '',
            fontSize: this.fontSize
          };
        };
        y5.paramsGenerator_ = z5;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(t5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(x5) {
    if (x5.item !== undefined) {
      this.item = x5.item;
    }
    if (x5.TabItem !== undefined) {
      this.TabItem = x5.TabItem;
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
    if (x5.longPressTime !== undefined) {
      this.longPressTime = x5.longPressTime;
    }
    if (x5.minFontSize !== undefined) {
      this.minFontSize = x5.minFontSize;
    }
    if (x5.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = x5.isFollowingSystemFontScale;
    }
    if (x5.maxFontScale !== undefined) {
      this.maxFontScale = x5.maxFontScale;
    }
    if (x5.systemFontScale !== undefined) {
      this.systemFontScale = x5.systemFontScale;
    }
    if (x5.fontSize === undefined) {
      this.__fontSize.set(1);
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
    if (x5.dialogController !== undefined) {
      this.dialogController = x5.dialogController;
    }
  }

  updateStateVars(w5) {
    this.__currentIndex.reset(w5.currentIndex);
    this.__fontSize.reset(w5.fontSize);
  }

  purgeVariableDependenciesOnElmtId(v5) {
    this.__currentIndex.purgeDependencyOnElmtId(v5);
    this.__fontSize.purgeDependencyOnElmtId(v5);
    this.__isOnFocus.purgeDependencyOnElmtId(v5);
    this.__isOnHover.purgeDependencyOnElmtId(v5);
    this.__isOnClick.purgeDependencyOnElmtId(v5);
    this.__tabWidth.purgeDependencyOnElmtId(v5);
    this.__imageWidth.purgeDependencyOnElmtId(v5);
    this.__imageHeight.purgeDependencyOnElmtId(v5);
  }

  aboutToBeDeleted() {
    this.__currentIndex.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
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
  set currentIndex(u5) {
    this.__currentIndex.set(u5);
  }

  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(t5) {
    this.__fontSize.set(t5);
  }

  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(s5) {
    this.__isOnFocus.set(s5);
  }

  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(r5) {
    this.__isOnHover.set(r5);
  }

  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(q5) {
    this.__isOnClick.set(q5);
  }

  get tabWidth() {
    return this.__tabWidth.get();
  }
  set tabWidth(p5) {
    this.__tabWidth.set(p5);
  }

  get imageWidth() {
    return this.__imageWidth.get();
  }
  set imageWidth(o5) {
    this.__imageWidth.set(o5);
  }

  get imageHeight() {
    return this.__imageHeight.get();
  }
  set imageHeight(n5) {
    this.__imageHeight.set(n5);
  }
  ToTabItem(m5) {
    if (m5.title) {
      this.TabItem.label = m5.title;
    }
    if (m5.icon) {
      this.TabItem.value = m5.icon;
    }
    return this.TabItem;
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

  aboutToAppear() {
    let h = this.getUIContext();
    this.isFollowingSystemFontScale = h.isFollowingSystemFontScale();
    this.maxFontScale = h.getMaxFontScale();
  }

  decideFontScale() {
    try {
      let l5 = this.getUIContext();
      this.systemFontScale = l5.getHostContext()?.config.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    }
    catch (i5) {
      let j5 = i5.code;
      let k5 = i5.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${j5}, message: ${k5}`);
      return 1;
    }
  }

  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation2((e5, f5) => {
      Stack.create();
      Stack.margin({
        left: this.index === 0 ? TabContentItem.marginFirst : 0,
        right: this.index === this.maxIndex ? 12 : 0
      });
    }, Stack);
    this.observeComponentCreation2((z4, a5) => {
      Row.create();
      Row.height(TabTitleBar.totalHeight);
      Row.alignItems(VerticalAlign.Center);
      Row.justifyContent(FlexAlign.Center);
      Row.borderRadius(TabContentItem.buttonBorderRadius);
      Row.backgroundColor(this.getBgColor());
      Row.onAreaChange((c5, d5) => {
        this.tabWidth = Number(d5.width);
      });
    }, Row);
    this.observeComponentCreation2((x4, y4) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
    }, Column);
    this.observeComponentCreation2((l3, m3) => {
      If.create();
      if (this.item.icon === undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((m4, n4) => {
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
            Text.onHover((w4) => this.isOnHover = w4);
            Text.onKeyEvent((v4) => {
              if (v4.keyCode !== KeyCode.KEYCODE_ENTER && v4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (v4.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (v4.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Text.onTouch((u4) => {
              if (u4.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (u4.type === TouchType.Up) {
                this.isOnClick = false;
              }
            });
            Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
          }, Text);
          Text.pop();
        });
      } else {
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
            Row.onHover((j4) => this.isOnHover = j4);
            Row.onKeyEvent((i4) => {
              if (i4.keyCode !== KeyCode.KEYCODE_ENTER && i4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (i4.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (i4.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Row.onTouch((h4) => {
              if (h4.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (h4.type === TouchType.Up || h4.type === TouchType.Cancel) {
                this.isOnClick = false;
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.close();
                }
              }
            });
            Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((i4) => {
              this.fontSize = this.decideFontScale();
              if (i4) {
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.open();
                }
              }
            });
            LongPressGesture.pop();
            Gesture.pop();
          }, Row);
          this.observeComponentCreation2((q3, r3) => {
            Image.create(this.item.icon);
            Context.animation({ duration: 300 });
            Image.alt(this.item.title);
            Image.width(this.getImageLayoutWidth());
            Image.height(TabContentItem.imageSize);
            Image.objectFit(ImageFit.Fill);
            Image.draggable(false);
            Image.scale({
              x: this.getImageScaleFactor(),
              y: this.getImageScaleFactor()
            });
            Context.animation(null);
            Image.hitTestBehavior(HitTestMode.None);
            Image.focusable(true);
            Image.onComplete((v3) => {
              if (!this.onImageComplete) {
                return;
              }
              this.imageWidth = px2vp(v3?.width);
              this.imageHeight = px2vp(v3?.height);
              this.onImageComplete(px2vp(v3?.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
            Image.onError((u3) => {
              if (!this.onImageComplete) {
                return;
              }
              this.onImageComplete(px2vp(u3.componentWidth) +
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
    this.observeComponentCreation2((e3, f3) => {
      If.create();
      if (this.isOnFocus && this.tabWidth > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j3, k3) => {
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
  constructor(p2, q2, r2, s2 = -1, t2 = undefined, u2) {
    super(p2, r2, s2, u2);
    if (typeof t2 === 'function') {
      this.paramsGenerator_ = t2;
    }
    this.item = { value: '' };
    this.index = 0;
    this.longPressTime = 500;
    this.minFontSize = 1.75;
    this.isFollowingSystemFontScale = false;
    this.maxFontScale = 1;
    this.systemFontScale = 1;
    this.__fontSize = new SynchedPropertySimpleOneWayPU(q2.fontSize, this, 'fontSize');
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let v2 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          TabTitleDialog: this.item,
          TabTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 645, col: 14 });
        v2.setController(this.dialogController);
        ViewPU.create(v2);
        let w2 = () => {
          return {
            cancel: () => {
            },
            confirm: () => {
            },
            TabTitleDialog: this.item,
            TabTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
            fontSize: this.fontSize
          };
        };
        v2.paramsGenerator_ = w2;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.setInitiallyProvidedValue(q2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(r2) {
    if (r2.item !== undefined) {
      this.item = r2.item;
    }
    if (r2.index !== undefined) {
      this.index = r2.index;
    }
    if (r2.longPressTime !== undefined) {
      this.longPressTime = r2.longPressTime;
    }
    if (r2.minFontSize !== undefined) {
      this.minFontSize = r2.minFontSize;
    }
    if (r2.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = r2.isFollowingSystemFontScale;
    }
    if (r2.maxFontScale !== undefined) {
      this.maxFontScale = r2.maxFontScale;
    }
    if (r2.systemFontScale !== undefined) {
      this.systemFontScale = r2.systemFontScale;
    }
    if (r2.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (r2.isOnFocus !== undefined) {
      this.isOnFocus = r2.isOnFocus;
    }
    if (r2.isOnHover !== undefined) {
      this.isOnHover = r2.isOnHover;
    }
    if (r2.isOnClick !== undefined) {
      this.isOnClick = r2.isOnClick;
    }
    if (r2.dialogController !== undefined) {
      this.dialogController = r2.dialogController;
    }
  }

  updateStateVars(q2) {
    this.__fontSize.reset(q2.fontSize);
  }

  purgeVariableDependenciesOnElmtId(p2) {
    this.__fontSize.purgeDependencyOnElmtId(p2);
    this.__isOnFocus.purgeDependencyOnElmtId(p2);
    this.__isOnHover.purgeDependencyOnElmtId(p2);
    this.__isOnClick.purgeDependencyOnElmtId(p2);
  }

  aboutToBeDeleted() {
    this.__fontSize.aboutToBeDeleted();
    this.__isOnFocus.aboutToBeDeleted();
    this.__isOnHover.aboutToBeDeleted();
    this.__isOnClick.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(o2) {
    this.__fontSize.set(o2);
  }

  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(n2) {
    this.__isOnFocus.set(n2);
  }

  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(m2) {
    this.__isOnHover.set(m2);
  }

  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(l2) {
    this.__isOnClick.set(l2);
  }

  textDialog() {
    if (this.item.value === PUBLIC_MORE) {
      return '';
    }
    else {
      return this.item.label ? this.item.label : '';
    }
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

  aboutToAppear() {
    let h = this.getUIContext();
    this.isFollowingSystemFontScale = h.isFollowingSystemFontScale();
    this.maxFontScale = h.getMaxFontScale();
  }

  decideFontScale() {
    try {
      let k2 = this.getUIContext();
      this.systemFontScale = k2.getHostContext()?.config.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    }
    catch (h2) {
      let i2 = h2.code;
      let j2 = h2.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${i2}, message: ${j2}`);
      return 1;
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
      Row.onHover((h2) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = h2;
      });
      Row.onKeyEvent((g2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (g2.keyCode !== KeyCode.KEYCODE_ENTER && g2.keyCode !== KeyCode.KEYCODE_SPACE) {
          return;
        }
        if (g2.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (g2.type === KeyType.Up) {
          this.isOnClick = false;
        }
      });
      Row.onTouch((f2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (f2.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (f2.type === TouchType.Up || f2.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize) {
            this.dialogController?.close();
          }
        }
      });
      Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
      Gesture.create(GesturePriority.Low);
      LongPressGesture.create({ repeat: false, duration: this.longPressTime });
      LongPressGesture.onAction((d2) => {
        this.fontSize = this.decideFontScale();
        if (d2) {
          if (this.fontSize >= this.minFontSize) {
            this.dialogController?.open();
          }
        }
      });
      LongPressGesture.pop();
      Gesture.pop();
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
    this.TabTitleDialog = { value: '' };
    this.callbackId = undefined;
    this.TabTitleBarDialog = '';
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
    if (h1.TabTitleDialog !== undefined) {
      this.TabTitleDialog = h1.TabTitleDialog;
    }
    if (h1.callbackId !== undefined) {
      this.callbackId = h1.callbackId;
    }
    if (h1.TabTitleBarDialog !== undefined) {
      this.TabTitleBarDialog = h1.TabTitleBarDialog;
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
      if (this.TabTitleBarDialog) {
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
            Image.create(this.TabTitleDialog.value);
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
            Text.create(this.TabTitleBarDialog);
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
      } else {
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
            Image.create(this.TabTitleDialog.value);
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