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
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const MeasureText = requireNapi('measure');
const hilog = requireNapi('hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
class ButtonGestureModifier {
  constructor(x14) {
    this.fontSize = 1;
    this.controller = null;
    this.controller = x14;
  }
  applyGesture(u14) {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      u14.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
        .onAction(() => {
          if (u14) {
            this.controller?.open();
          }
        })
        .onActionEnd(() => {
          this.controller?.close();
        }));
    }
    else {
      u14.clearGestures();
    }
  }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class TabTitleBar extends ViewPU {
  constructor(o14, p14, q14, r14 = -1, s14 = undefined, t14) {
    super(o14, q14, r14, t14);
    if (typeof s14 === 'function') {
      this.paramsGenerator_ = s14;
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
    this.setInitiallyProvidedValue(p14);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n14) {
    if (n14.tabItems !== undefined) {
      this.tabItems = n14.tabItems;
    }
    if (n14.menuItems !== undefined) {
      this.menuItems = n14.menuItems;
    }
    if (n14.swiperContent !== undefined) {
      this.swiperContent = n14.swiperContent;
    }
    if (n14.tabWidth !== undefined) {
      this.tabWidth = n14.tabWidth;
    }
    if (n14.currentIndex !== undefined) {
      this.currentIndex = n14.currentIndex;
    }
    if (n14.fontSize !== undefined) {
      this.fontSize = n14.fontSize;
    }
    if (n14.menuSectionWidth !== undefined) {
      this.menuSectionWidth = n14.menuSectionWidth;
    }
    if (n14.tabOffsets !== undefined) {
      this.tabOffsets = n14.tabOffsets;
    }
    if (n14.imageWidths !== undefined) {
      this.imageWidths = n14.imageWidths;
    }
    if (n14.scroller !== undefined) {
      this.scroller = n14.scroller;
    }
    if (n14.swiperController !== undefined) {
      this.swiperController = n14.swiperController;
    }
    if (n14.settings !== undefined) {
      this.settings = n14.settings;
    }
    if (n14.leftContext2D !== undefined) {
      this.leftContext2D = n14.leftContext2D;
    }
    if (n14.rightContext2D !== undefined) {
      this.rightContext2D = n14.rightContext2D;
    }
  }
  updateStateVars(m14) {
  }
  purgeVariableDependenciesOnElmtId(l14) {
    this.__tabWidth.purgeDependencyOnElmtId(l14);
    this.__currentIndex.purgeDependencyOnElmtId(l14);
    this.__fontSize.purgeDependencyOnElmtId(l14);
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
  set tabWidth(k14) {
    this.__tabWidth.set(k14);
  }
  get currentIndex() {
    return this.__currentIndex.get();
  }
  set currentIndex(j14) {
    this.__currentIndex.set(j14);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(i14) {
    this.__fontSize.set(i14);
  }
  GradientMask(u13, v13, w13, x13, y13, z13 = null) {
    this.observeComponentCreation((g14, h14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g14);
      Column.create();
      Column.blendMode(BlendMode.DST_OUT);
      Column.width(TabTitleBar.gradientMaskWidth);
      Column.height(TabTitleBar.totalHeight);
      if (!h14) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c14, d14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c14);
      Canvas.create(u13);
      Canvas.width(TabTitleBar.gradientMaskWidth);
      Canvas.height(TabTitleBar.totalHeight);
      Canvas.onReady(() => {
        let f14 = u13.createLinearGradient(v13, w13, x13, y13);
        f14.addColorStop(0.0, '#ffffffff');
        f14.addColorStop(1, '#00ffffff');
        u13.fillStyle = f14;
        u13.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
      });
      if (!d14) {
        Canvas.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Canvas.pop();
    Column.pop();
  }
  emptyBuilder(t13 = null) {
  }
  aboutToAppear() {
    if (!this.swiperContent) {
      this.swiperContent = this.emptyBuilder;
    }
    this.tabItems.forEach((s13) => {
      this.imageWidths.push(0);
    });
    this.loadOffsets();
  }
  loadOffsets() {
    this.tabOffsets.length = 0;
    let n13 = 0;
    this.tabOffsets.push(n13);
    n13 += TabContentItem.marginFirst;
    this.tabItems.forEach((p13, q13) => {
      if (p13.icon !== undefined) {
        if (Math.abs(this.imageWidths[q13]) > TabContentItem.imageHotZoneWidth) {
          n13 += this.imageWidths[q13];
        }
        else {
          n13 += TabContentItem.imageHotZoneWidth;
        }
      }
      else {
        n13 += TabContentItem.paddingLeft;
        n13 += px2vp(MeasureText.measureText({
          textContent: p13.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        }));
        n13 += TabContentItem.paddingRight;
      }
      this.tabOffsets.push(n13);
    });
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((l13, m13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l13);
      Column.create();
      if (!m13) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((g13, h13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g13);
      Flex.create({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      });
      Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Flex.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
      Flex.onAreaChange((j13, k13) => {
        this.tabWidth = Number(k13.width) - this.menuSectionWidth;
      });
      if (!h13) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((e13, f13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e13);
      Stack.create({ alignContent: Alignment.End });
      Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
      if (!f13) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((c13, d13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c13);
      Stack.create({ alignContent: Alignment.Start });
      if (!d13) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((a13, b13) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a13);
      Column.create();
      if (!b13) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y12, z12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y12);
      List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
      List.width('100%');
      List.height(TabTitleBar.totalHeight);
      List.constraintSize({ maxWidth: this.tabWidth });
      List.edgeEffect(EdgeEffect.Spring);
      List.listDirection(Axis.Horizontal);
      List.scrollBar(BarState.Off);
      if (!z12) {
        List.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((u11, v11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u11);
      ForEach.create();
      const w11 = (y11, z11) => {
        const a12 = y11;
        {
          const b12 = (w12, x12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w12);
            c12(w12, x12);
            if (!x12) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const c12 = (u12, v12) => {
            ListItem.create(d12, true);
          };
          const d12 = (h12, i12) => {
            b12(h12, i12);
            this.updateFuncByElmtId.set(h12, b12);
            {
              this.observeComponentCreation((k12, l12) => {
                ViewStackProcessor.StartGetAccessRecordingFor(k12);
                if (l12) {
                  let m12 = new TabContentItem(this, {
                    item: a12,
                    index: z11,
                    maxIndex: this.tabItems.length - 1,
                    currentIndex: this.currentIndex,
                    onCustomClick: (t12) => this.currentIndex = t12,
                    onImageComplete: (s12) => {
                      this.imageWidths[z11] = s12;
                      this.loadOffsets();
                    }
                  }, undefined, k12, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 170, col: 21 });
                  ViewPU.create(m12);
                  let n12 = () => {
                    return {
                      item: a12,
                      index: z11,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (r12) => this.currentIndex = r12,
                      onImageComplete: (q12) => {
                        this.imageWidths[z11] = q12;
                        this.loadOffsets();
                      }
                    };
                  };
                  m12.paramsGenerator_ = n12;
                }
                else {
                  this.updateStateVarsOfChildByElmtId(k12, {
                    currentIndex: this.currentIndex
                  });
                }
                ViewStackProcessor.StopGetAccessRecording();
              });
            }
            ListItem.pop();
          };
          this.observeComponentCreation(b12);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(u11, this.tabItems, w11, undefined, true, false);
      if (!v11) {
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
    this.observeComponentCreation((d11, e11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d11);
      If.create();
      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((p11, q11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p11);
            __Common__.create();
            __Common__.height(TabTitleBar.totalHeight);
            __Common__.onAreaChange((s11, t11) => {
              this.menuSectionWidth = Number(t11.width);
            });
            if (!q11) {
              __Common__.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          {
            this.observeComponentCreation((j11, k11) => {
              ViewStackProcessor.StartGetAccessRecordingFor(j11);
              if (k11) {
                let l11 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ }, undefined, j11, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 200, col: 11 });
                ViewPU.create(l11);
                let m11 = () => {
                  return {
                    menuItems: this.menuItems,
                    index: 1 + TabTitleBar.instanceCount++
                  };
                };
                l11.paramsGenerator_ = m11;
              }
              else {
                this.updateStateVarsOfChildByElmtId(j11, {});
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
      if (!e11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Flex.pop();
    this.observeComponentCreation((b11, c11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b11);
      Column.create();
      if (!c11) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((v10, w10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v10);
      Swiper.create(this.swiperController);
      Swiper.index(this.currentIndex);
      Swiper.itemSpace(0);
      Swiper.indicator(false);
      Swiper.width('100%');
      Swiper.height('100%');
      Swiper.curve(Curve.Friction);
      Swiper.onChange((z10) => {
        const a11 = this.tabOffsets[z10] + TabTitleBar.correctionOffset;
        this.currentIndex = z10;
        this.scroller.scrollTo({
          xOffset: a11 > 0 ? a11 : 0,
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
      if (!w10) {
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
  constructor(b10, c10, d10, e10 = -1, f10 = undefined, g10) {
    super(b10, d10, e10, g10);
    if (typeof f10 === 'function') {
      this.paramsGenerator_ = f10;
    }
    this.menuItems = [];
    this.index = 0;
    this.item = {
      value: PUBLIC_MORE,
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
    this.__fontSize = new SynchedPropertySimpleOneWayPU(c10.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let h10 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          tabTitleDialog: this.item,
          tabTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 268, col: 14 });
        h10.setController(this.dialogController);
        ViewPU.create(h10);
        let i10 = () => {
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
        h10.paramsGenerator_ = i10;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
    this.setInitiallyProvidedValue(c10);
    this.declareWatch('fontSize', this.onFontSizeUpdated);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(a10) {
    if (a10.menuItems !== undefined) {
      this.menuItems = a10.menuItems;
    }
    if (a10.index !== undefined) {
      this.index = a10.index;
    }
    if (a10.item !== undefined) {
      this.item = a10.item;
    }
    if (a10.minFontSize !== undefined) {
      this.minFontSize = a10.minFontSize;
    }
    if (a10.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = a10.isFollowingSystemFontScale;
    }
    if (a10.maxFontScale !== undefined) {
      this.maxFontScale = a10.maxFontScale;
    }
    if (a10.systemFontScale !== undefined) {
      this.systemFontScale = a10.systemFontScale;
    }
    if (a10.firstFocusableIndex !== undefined) {
      this.firstFocusableIndex = a10.firstFocusableIndex;
    }
    if (a10.isPopupShown !== undefined) {
      this.isPopupShown = a10.isPopupShown;
    }
    if (a10.isMoreIconOnFocus !== undefined) {
      this.isMoreIconOnFocus = a10.isMoreIconOnFocus;
    }
    if (a10.isMoreIconOnHover !== undefined) {
      this.isMoreIconOnHover = a10.isMoreIconOnHover;
    }
    if (a10.isMoreIconOnClick !== undefined) {
      this.isMoreIconOnClick = a10.isMoreIconOnClick;
    }
    if (a10.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (a10.dialogController !== undefined) {
      this.dialogController = a10.dialogController;
    }
    if (a10.buttonGestureModifier !== undefined) {
      this.buttonGestureModifier = a10.buttonGestureModifier;
    }
  }
  updateStateVars(z9) {
    this.__fontSize.reset(z9.fontSize);
  }
  purgeVariableDependenciesOnElmtId(y9) {
    this.__isPopupShown.purgeDependencyOnElmtId(y9);
    this.__isMoreIconOnFocus.purgeDependencyOnElmtId(y9);
    this.__isMoreIconOnHover.purgeDependencyOnElmtId(y9);
    this.__isMoreIconOnClick.purgeDependencyOnElmtId(y9);
    this.__fontSize.purgeDependencyOnElmtId(y9);
    this.__buttonGestureModifier.purgeDependencyOnElmtId(y9);
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
  set isPopupShown(x9) {
    this.__isPopupShown.set(x9);
  }
  get isMoreIconOnFocus() {
    return this.__isMoreIconOnFocus.get();
  }
  set isMoreIconOnFocus(w9) {
    this.__isMoreIconOnFocus.set(w9);
  }
  get isMoreIconOnHover() {
    return this.__isMoreIconOnHover.get();
  }
  set isMoreIconOnHover(v9) {
    this.__isMoreIconOnHover.set(v9);
  }
  get isMoreIconOnClick() {
    return this.__isMoreIconOnClick.get();
  }
  set isMoreIconOnClick(u9) {
    this.__isMoreIconOnClick.set(u9);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(t9) {
    this.__fontSize.set(t9);
  }
  get buttonGestureModifier() {
    return this.__buttonGestureModifier.get();
  }
  set buttonGestureModifier(s9) {
    this.__buttonGestureModifier.set(s9);
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
      let r9 = this.getUIContext();
      this.isFollowingSystemFontScale = r9.isFollowingSystemFontScale();
      this.maxFontScale = r9.getMaxFontScale();
    }
    catch (o9) {
      let p9 = o9.code;
      let q9 = o9.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${p9}, message: ${q9}`);
    }
    this.menuItems.forEach((m9, n9) => {
      if (m9.isEnabled && this.firstFocusableIndex === -1 &&
        n9 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + n9 + 1;
      }
    });
    this.fontSize = this.decideFontScale();
  }
  decideFontScale() {
    let k9 = this.getUIContext();
    this.systemFontScale = k9.getHostContext()?.config?.fontSizeScale ?? 1;
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
    this.observeComponentCreation((i9, j9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i9);
      Column.create();
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      if (!j9) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((g9, h9) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g9);
      Row.create();
      if (!h9) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((i7, j7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i7);
      If.create();
      if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((s8, t8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s8);
            ForEach.create();
            const u8 = (w8, x8) => {
              const y8 = w8;
              {
                this.observeComponentCreation((a9, b9) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(a9);
                  if (b9) {
                    let c9 = new ImageMenuItem(this, { item: y8, index: this.index * 1000 + x8 + 1 }, undefined, a9, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 337, col: 13 });
                    ViewPU.create(c9);
                    let d9 = () => {
                      return {
                        item: y8,
                        index: this.index * 1000 + x8 + 1
                      };
                    };
                    c9.paramsGenerator_ = d9;
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(a9, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(s8, this.menuItems, u8, undefined, true, false);
            if (!t8) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((c8, d8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c8);
            ForEach.create();
            const e8 = (g8, h8) => {
              const i8 = g8;
              {
                this.observeComponentCreation((k8, l8) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(k8);
                  if (l8) {
                    let m8 = new ImageMenuItem(this, { item: i8, index: this.index * 1000 + h8 + 1 }, undefined, k8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 342, col: 15 });
                    ViewPU.create(m8);
                    let n8 = () => {
                      return {
                        item: i8,
                        index: this.index * 1000 + h8 + 1
                      };
                    };
                    m8.paramsGenerator_ = n8;
                  }
                  else {
                    this.updateStateVarsOfChildByElmtId(k8, {});
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
              }
            };
            this.forEachUpdateFunction(c8, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), e8, undefined, true, false);
            if (!d8) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          this.observeComponentCreation((q7, r7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q7);
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
            Button.onHover((b8) => this.isMoreIconOnHover = b8);
            Button.onKeyEvent((a8) => {
              if (a8.keyCode !== KeyCode.KEYCODE_ENTER && a8.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (a8.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (a8.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            });
            Button.onTouch((z7) => {
              if (z7.type === TouchType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (z7.type === TouchType.Up || z7.type === TouchType.Cancel) {
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
              onStateChange: (y7) => {
                this.isPopupShown = y7.isVisible;
                if (!y7.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              }
            });
            if (!r7) {
              Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((o7, p7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o7);
            Image.create(PUBLIC_MORE);
            Image.width(ImageMenuItem.imageSize);
            Image.height(ImageMenuItem.imageSize);
            Image.focusable(true);
            Image.draggable(false);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!p7) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Button.pop();
        });
      }
      if (!j7) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Row.pop();
    Column.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  popupBuilder(l6 = null) {
    this.observeComponentCreation((c7, d7) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c7);
      Column.create();
      Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
      Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
      Column.onAppear(() => {
        focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
      });
      if (!d7) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((o6, p6) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o6);
      ForEach.create();
      const q6 = (s6, t6) => {
        const u6 = s6;
        {
          this.observeComponentCreation((w6, x6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w6);
            if (x6) {
              let y6 = new ImageMenuItem(this, { item: u6, index: this.index * 1000 +
              CollapsibleMenuSection.maxCountOfVisibleItems + t6 }, undefined, w6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 426, col: 11 });
              ViewPU.create(y6);
              let z6 = () => {
                return {
                  item: u6,
                  index: this.index * 1000 +
                  CollapsibleMenuSection.maxCountOfVisibleItems + t6
                };
              };
              y6.paramsGenerator_ = z6;
            }
            else {
              this.updateStateVarsOfChildByElmtId(w6, {});
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        }
      };
      this.forEachUpdateFunction(o6, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), q6, undefined, true, false);
      if (!p6) {
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
  constructor(f6, g6, h6, i6 = -1, j6 = undefined, k6) {
    super(f6, h6, i6, k6);
    if (typeof j6 === 'function') {
      this.paramsGenerator_ = j6;
    }
    this.item = { title: '' };
    this.index = 0;
    this.maxIndex = 0;
    this.onCustomClick = undefined;
    this.onImageComplete = undefined;
    this.__currentIndex = new SynchedPropertySimpleOneWayPU(g6.currentIndex, this, 'currentIndex');
    this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
    this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
    this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
    this.__tabWidth = new ObservedPropertySimplePU(0, this, 'tabWidth');
    this.__imageWidth = new ObservedPropertySimplePU(24, this, 'imageWidth');
    this.__imageHeight = new ObservedPropertySimplePU(24, this, 'imageHeight');
    this.setInitiallyProvidedValue(g6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(e6) {
    if (e6.item !== undefined) {
      this.item = e6.item;
    }
    if (e6.index !== undefined) {
      this.index = e6.index;
    }
    if (e6.maxIndex !== undefined) {
      this.maxIndex = e6.maxIndex;
    }
    if (e6.onCustomClick !== undefined) {
      this.onCustomClick = e6.onCustomClick;
    }
    if (e6.onImageComplete !== undefined) {
      this.onImageComplete = e6.onImageComplete;
    }
    if (e6.isOnFocus !== undefined) {
      this.isOnFocus = e6.isOnFocus;
    }
    if (e6.isOnHover !== undefined) {
      this.isOnHover = e6.isOnHover;
    }
    if (e6.isOnClick !== undefined) {
      this.isOnClick = e6.isOnClick;
    }
    if (e6.tabWidth !== undefined) {
      this.tabWidth = e6.tabWidth;
    }
    if (e6.imageWidth !== undefined) {
      this.imageWidth = e6.imageWidth;
    }
    if (e6.imageHeight !== undefined) {
      this.imageHeight = e6.imageHeight;
    }
  }
  updateStateVars(d6) {
    this.__currentIndex.reset(d6.currentIndex);
  }
  purgeVariableDependenciesOnElmtId(c6) {
    this.__currentIndex.purgeDependencyOnElmtId(c6);
    this.__isOnFocus.purgeDependencyOnElmtId(c6);
    this.__isOnHover.purgeDependencyOnElmtId(c6);
    this.__isOnClick.purgeDependencyOnElmtId(c6);
    this.__tabWidth.purgeDependencyOnElmtId(c6);
    this.__imageWidth.purgeDependencyOnElmtId(c6);
    this.__imageHeight.purgeDependencyOnElmtId(c6);
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
  set currentIndex(b6) {
    this.__currentIndex.set(b6);
  }
  get isOnFocus() {
    return this.__isOnFocus.get();
  }
  set isOnFocus(a6) {
    this.__isOnFocus.set(a6);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(z5) {
    this.__isOnHover.set(z5);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(y5) {
    this.__isOnClick.set(y5);
  }
  get tabWidth() {
    return this.__tabWidth.get();
  }
  set tabWidth(x5) {
    this.__tabWidth.set(x5);
  }
  get imageWidth() {
    return this.__imageWidth.get();
  }
  set imageWidth(w5) {
    this.__imageWidth.set(w5);
  }
  get imageHeight() {
    return this.__imageHeight.get();
  }
  set imageHeight(v5) {
    this.__imageHeight.set(v5);
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
  toStringFormat(q5) {
    if (typeof q5 === 'string') {
      return q5;
    }
    else if (typeof q5 === 'undefined') {
      return '';
    }
    else {
      let r5 = '';
      try {
        r5 = getContext()?.resourceManager?.getStringSync(q5);
      }
      catch (s5) {
        let t5 = s5?.code;
        let u5 = s5?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${t5},message:${u5}`);
      }
      return r5;
    }
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((o5, p5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o5);
      Stack.create();
      Stack.margin({
        left: this.index === 0 ? TabContentItem.marginFirst : 0,
        right: this.index === this.maxIndex ? 12 : 0
      });
      if (!p5) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j5, k5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j5);
      Button.createWithChild();
      Button.height(TabTitleBar.totalHeight);
      Button.borderRadius(TabContentItem.buttonBorderRadius);
      Button.backgroundColor(this.getBgColor());
      Button.onAreaChange((m5, n5) => {
        this.tabWidth = Number(n5.width);
      });
      if (!k5) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((h5, i5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h5);
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      if (!i5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y3, z3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y3);
      If.create();
      if (this.item.icon === undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w4, x4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w4);
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
            Text.onHover((g5) => this.isOnHover = g5);
            Text.onKeyEvent((f5) => {
              if (f5.keyCode !== KeyCode.KEYCODE_ENTER && f5.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (f5.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (f5.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Text.onTouch((e5) => {
              if (e5.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (e5.type === TouchType.Up || e5.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            });
            Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
            Text.accessibilitySelected(this.index === this.currentIndex);
            if (!x4) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((j4, k4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j4);
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
            Row.onHover((t4) => this.isOnHover = t4);
            Row.onKeyEvent((s4) => {
              if (s4.keyCode !== KeyCode.KEYCODE_ENTER && s4.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (s4.type === KeyType.Down) {
                this.isOnClick = true;
              }
              if (s4.type === KeyType.Up) {
                this.isOnClick = false;
              }
            });
            Row.onTouch((r4) => {
              if (r4.type === TouchType.Down) {
                this.isOnClick = true;
              }
              if (r4.type === TouchType.Up || r4.type === TouchType.Cancel) {
                this.isOnClick = false;
              }
            });
            Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
            Row.accessibilitySelected(this.index === this.currentIndex);
            if (!k4) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((d4, e4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d4);
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
            Image.onComplete((i4) => {
              if (!this.onImageComplete) {
                return;
              }
              this.imageWidth = px2vp(i4?.width);
              this.imageHeight = px2vp(i4?.height);
              this.onImageComplete(px2vp(i4?.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
            Image.onError((h4) => {
              if (!this.onImageComplete) {
                return;
              }
              this.onImageComplete(px2vp(h4.componentWidth) +
              TabContentItem.paddingLeft + TabContentItem.paddingRight);
            });
            if (!e4) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Row.pop();
        });
      }
      if (!z3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Button.pop();
    this.observeComponentCreation((r3, s3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r3);
      If.create();
      if (this.isOnFocus && this.tabWidth > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w3, x3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w3);
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
            if (!x3) {
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
      if (!s3) {
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
TabContentItem.imageHotZoneWidth = 48;
TabContentItem.imageMagnificationFactor = 1.4;
TabContentItem.buttonBorderRadius = 8;
TabContentItem.focusBorderWidth = 2;
TabContentItem.paddingLeft = 8;
TabContentItem.paddingRight = 8;
TabContentItem.marginFirst = 16;
class ImageMenuItem extends ViewPU {
  constructor(c3, d3, e3, f3 = -1, g3 = undefined, h3) {
    super(c3, e3, f3, h3);
    if (typeof g3 === 'function') {
      this.paramsGenerator_ = g3;
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
    this.__fontSize = new SynchedPropertySimpleOneWayPU(d3.fontSize, this, 'fontSize');
    this.dialogController = new CustomDialogController({
      builder: () => {
        let i3 = new TabTitleBarDialog(this, {
          cancel: () => {
          },
          confirm: () => {
          },
          tabTitleDialog: this.item,
          tabTitleBarDialog: this.item.label ? this.item.label : '',
          fontSize: this.fontSize,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 682, col: 14 });
        i3.setController(this.dialogController);
        ViewPU.create(i3);
        let j3 = () => {
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
        i3.paramsGenerator_ = j3;
      },
      maskColor: Color.Transparent,
      isModal: true,
      customStyle: true
    }, this);
    this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
    this.setInitiallyProvidedValue(d3);
    this.declareWatch('fontSize', this.onFontSizeUpdated);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(b3) {
    if (b3.item !== undefined) {
      this.item = b3.item;
    }
    if (b3.index !== undefined) {
      this.index = b3.index;
    }
    if (b3.minFontSize !== undefined) {
      this.minFontSize = b3.minFontSize;
    }
    if (b3.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = b3.isFollowingSystemFontScale;
    }
    if (b3.maxFontScale !== undefined) {
      this.maxFontScale = b3.maxFontScale;
    }
    if (b3.systemFontScale !== undefined) {
      this.systemFontScale = b3.systemFontScale;
    }
    if (b3.isPopup !== undefined) {
      this.isPopup = b3.isPopup;
    }
    if (b3.isOnFocus !== undefined) {
      this.isOnFocus = b3.isOnFocus;
    }
    if (b3.isOnHover !== undefined) {
      this.isOnHover = b3.isOnHover;
    }
    if (b3.isOnClick !== undefined) {
      this.isOnClick = b3.isOnClick;
    }
    if (b3.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (b3.dialogController !== undefined) {
      this.dialogController = b3.dialogController;
    }
    if (b3.buttonGestureModifier !== undefined) {
      this.buttonGestureModifier = b3.buttonGestureModifier;
    }
  }
  updateStateVars(a3) {
    this.__fontSize.reset(a3.fontSize);
  }
  purgeVariableDependenciesOnElmtId(z2) {
    this.__isOnFocus.purgeDependencyOnElmtId(z2);
    this.__isOnHover.purgeDependencyOnElmtId(z2);
    this.__isOnClick.purgeDependencyOnElmtId(z2);
    this.__fontSize.purgeDependencyOnElmtId(z2);
    this.__buttonGestureModifier.purgeDependencyOnElmtId(z2);
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
  set isOnFocus(y2) {
    this.__isOnFocus.set(y2);
  }
  get isOnHover() {
    return this.__isOnHover.get();
  }
  set isOnHover(x2) {
    this.__isOnHover.set(x2);
  }
  get isOnClick() {
    return this.__isOnClick.get();
  }
  set isOnClick(w2) {
    this.__isOnClick.set(w2);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(v2) {
    this.__fontSize.set(v2);
  }
  get buttonGestureModifier() {
    return this.__buttonGestureModifier.get();
  }
  set buttonGestureModifier(u2) {
    this.__buttonGestureModifier.set(u2);
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
  toStringFormat(p2) {
    if (typeof p2 === 'string') {
      return p2;
    }
    else if (typeof p2 === 'undefined') {
      return '';
    }
    else {
      let q2 = '';
      try {
        q2 = getContext()?.resourceManager?.getStringSync(p2);
      }
      catch (r2) {
        let s2 = r2?.code;
        let t2 = r2?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${s2},message:${t2}`);
      }
      return q2;
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
  onPlaceChildren(k2, l2, m2) {
    l2.forEach((o2) => {
      o2.layout({ x: 0, y: 0 });
    });
    this.fontSize = this.decideFontScale();
  }
  onFontSizeUpdated() {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }
  aboutToAppear() {
    try {
      let j2 = this.getUIContext();
      this.isFollowingSystemFontScale = j2.isFollowingSystemFontScale();
      this.maxFontScale = j2.getMaxFontScale();
    }
    catch (g2) {
      let h2 = g2.code;
      let i2 = g2.message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${h2}, message: ${i2}`);
    }
    this.fontSize = this.decideFontScale();
  }
  decideFontScale() {
    let f2 = this.getUIContext();
    this.systemFontScale = f2.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((u1, v1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u1);
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
      Button.onHover((e2) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = e2;
      });
      Button.onKeyEvent((d2) => {
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
      Button.onTouch((c2) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (c2.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (c2.type === TouchType.Up || c2.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize && this.isPopup === false) {
            this.dialogController?.close();
          }
        }
      });
      Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
      Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
      if (!v1) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((s1, t1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s1);
      Image.create(this.item.value);
      Image.width(ImageMenuItem.imageSize);
      Image.height(ImageMenuItem.imageSize);
      Image.focusable(this.item.isEnabled);
      Image.key(ImageMenuItem.focusablePrefix + this.index);
      Image.draggable(false);
      if (!t1) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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
    this.observeComponentCreation((e, f) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      if (this.tabTitleBarDialog) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((y, z) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y);
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!z) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((w, x) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w);
            Image.create(this.tabTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.margin({
              top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!x) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((u, v) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u);
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            if (!v) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((s, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s);
            Text.create(this.tabTitleBarDialog);
            Text.fontSize(TEXT_EDITABLE_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!t) {
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
          this.observeComponentCreation((l, m) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l);
            Column.create();
            Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Column.justifyContent(FlexAlign.Center);
            if (!m) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((j, k) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j);
            Image.create(this.tabTitleDialog.value);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!k) {
              Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
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
  TabTitleBar: TabTitleBar
};