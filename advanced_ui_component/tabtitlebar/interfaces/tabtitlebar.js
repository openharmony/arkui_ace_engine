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
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
  });
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const MeasureText = requireNapi('measure');
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const o = {
  'id': -1,
  'type': 40000,
  params: ['sys.symbol.dot_grid_2x2'],
  'bundleName': '__harDefaultBundleName__',
  'moduleName': '__harDefaultModuleName__'
};
const u = '18.3fp';
const a1 = '64vp';
const b1 = '256vp';
const c1 = '216vp';
const t = 40000;

class b2 {
  constructor(controller) {
      this.fontSize = 1;
      this.controller = null;
      this.controller = controller;
  }

  applyGesture(event) {
      if (this.fontSize >= b2.minFontSize) {
          event.addGesture(new LongPressGestureHandler({ repeat: false, duration: b2.longPressTime })
              .onAction(() => {
                  if (event) {
                      this.controller?.open();
                  }
              })
              .onActionEnd(() => {
                  this.controller?.close();
              }));
      } else {
          event.clearGestures();
      }
  }
}

b2.longPressTime = 500;
b2.minFontSize = 1.75;

export class TabTitleBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === 'function') {
          this.paramsGenerator_ = paramsLambda;
      }
      this.tabItems = [];
      this.menuItems = [];
      this.swiperContent = undefined;
      this.e2 = new ObservedPropertySimplePU(0, this, 'tabWidth');
      this.f2 = new ObservedPropertySimplePU(0, this, 'currentIndex');
      this.i1 = new ObservedPropertySimplePU(1, this, 'fontSize');
      this.menuSectionWidth = 0;
      this.tabOffsets = [];
      this.imageWidths = [];
      this.scroller = new Scroller();
      this.swiperController = new SwiperController();
      this.settings = new RenderingContextSettings(true);
      this.leftContext2D = new CanvasRenderingContext2D(this.settings);
      this.rightContext2D = new CanvasRenderingContext2D(this.settings);
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
      if (params.tabItems !== undefined) {
          this.tabItems = params.tabItems;
      }
      if (params.menuItems !== undefined) {
          this.menuItems = params.menuItems;
      }
      if (params.swiperContent !== undefined) {
          this.swiperContent = params.swiperContent;
      }
      if (params.tabWidth !== undefined) {
          this.tabWidth = params.tabWidth;
      }
      if (params.currentIndex !== undefined) {
          this.currentIndex = params.currentIndex;
      }
      if (params.fontSize !== undefined) {
          this.fontSize = params.fontSize;
      }
      if (params.menuSectionWidth !== undefined) {
          this.menuSectionWidth = params.menuSectionWidth;
      }
      if (params.tabOffsets !== undefined) {
          this.tabOffsets = params.tabOffsets;
      }
      if (params.imageWidths !== undefined) {
          this.imageWidths = params.imageWidths;
      }
      if (params.scroller !== undefined) {
          this.scroller = params.scroller;
      }
      if (params.swiperController !== undefined) {
          this.swiperController = params.swiperController;
      }
      if (params.settings !== undefined) {
          this.settings = params.settings;
      }
      if (params.leftContext2D !== undefined) {
          this.leftContext2D = params.leftContext2D;
      }
      if (params.rightContext2D !== undefined) {
          this.rightContext2D = params.rightContext2D;
      }
  }

  updateStateVars(params) {
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.e2.purgeDependencyOnElmtId(rmElmtId);
      this.f2.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
      this.e2.aboutToBeDeleted();
      this.f2.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }

  get tabWidth() {
      return this.e2.get();
  }

  set tabWidth(newValue) {
      this.e2.set(newValue);
  }

  get currentIndex() {
      return this.f2.get();
  }

  set currentIndex(newValue) {
      this.f2.set(newValue);
  }

  get fontSize() {
      return this.i1.get();
  }

  set fontSize(newValue) {
      this.i1.set(newValue);
  }

  GradientMask(v2, x0, y0, x1, y1, parent = null) {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.blendMode(BlendMode.DST_OUT);
          Column.width(TabTitleBar.gradientMaskWidth);
          Column.height(TabTitleBar.totalHeight);
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Canvas.create(v2);
          Canvas.width(TabTitleBar.gradientMaskWidth);
          Canvas.height(TabTitleBar.totalHeight);
          Canvas.onReady(() => {
              let w2 = v2.createLinearGradient(x0, y0, x1, y1);
              w2.addColorStop(0.0, '#ffffffff');
              w2.addColorStop(1, '#00ffffff');
              v2.fillStyle = w2;
              v2.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
          });
      }, Canvas);
      Canvas.pop();
      Column.pop();
  }

  emptyBuilder(parent = null) {
  }

  aboutToAppear() {
      if (!this.swiperContent) {
          this.swiperContent = this.emptyBuilder;
      }
      this.tabItems.forEach((u2) => {
          this.imageWidths.push(0);
      });
      this.loadOffsets();
  }

  loadOffsets() {
      this.tabOffsets.length = 0;
      let s2 = 0;
      this.tabOffsets.push(s2);
      s2 += c2.marginFirst;
      this.tabItems.forEach((t2, index) => {
          if (t2.icon !== undefined || t2.symbolStyle !== undefined) {
              if (Math.abs(this.imageWidths[index]) > c2.imageHotZoneWidth) {
                  s2 += this.imageWidths[index];
              } else {
                  s2 += c2.imageHotZoneWidth;
              }
          } else {
              s2 += c2.paddingLeft;
              s2 += px2vp(MeasureText.measureText({
                  textContent: t2.title.toString(),
                  fontSize: 18,
                  fontWeight: FontWeight.Medium,
              }));
              s2 += c2.paddingRight;
          }
          this.tabOffsets.push(s2);
      });
  }

  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Flex.create({
              justifyContent: FlexAlign.SpaceBetween,
              alignItems: ItemAlign.Stretch
          });
          Flex.backgroundColor({
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_background'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          });
          Flex.margin({
              right: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_max_padding_end'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              }
          });
          Flex.onAreaChange((r2, newValue) => {
              this.tabWidth = Number(newValue.width) - this.menuSectionWidth;
          });
      }, Flex);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Stack.create({ alignContent: Alignment.End });
          Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
      }, Stack);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Stack.create({ alignContent: Alignment.Start });
      }, Stack);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          List.create({ initialIndex: 0, scroller: this.scroller, space: 0 });
          List.width('100%');
          List.height(TabTitleBar.totalHeight);
          List.constraintSize({ maxWidth: this.tabWidth });
          List.edgeEffect(EdgeEffect.Spring);
          List.listDirection(Axis.Horizontal);
          List.scrollBar(BarState.Off);
      }, List);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          ForEach.create();
          const forEachItemGenFunction = (_item, index) => {
              const q2 = _item;
              {
                  const itemCreation = (elmtId, isInitialRender) => {
                      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                      itemCreation2(elmtId, isInitialRender);
                      if (!isInitialRender) {
                          ListItem.pop();
                      }
                      ViewStackProcessor.StopGetAccessRecording();
                  };
                  const itemCreation2 = (elmtId, isInitialRender) => {
                      ListItem.create(deepRenderFunction, true);
                  };
                  const deepRenderFunction = (elmtId, isInitialRender) => {
                      itemCreation(elmtId, isInitialRender);
                      {
                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                              if (isInitialRender) {
                                  let componentCall = new c2(this, {
                                      item: q2,
                                      index: index,
                                      maxIndex: this.tabItems.length - 1,
                                      currentIndex: this.currentIndex,
                                      onCustomClick: (itemIndex) => this.currentIndex = itemIndex,
                                      onImageComplete: (width) => {
                                          this.imageWidths[index] = width;
                                          this.loadOffsets();
                                      }
                                  }, undefined, elmtId, () => {
                                  }, {
                                      page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets',
                                      line: 174,
                                      j1: 21
                                  });
                                  ViewPU.create(componentCall);
                                  let paramsLambda = () => {
                                      return {
                                          item: q2,
                                          index: index,
                                          maxIndex: this.tabItems.length - 1,
                                          currentIndex: this.currentIndex,
                                          onCustomClick: (itemIndex) => this.currentIndex = itemIndex,
                                          onImageComplete: (width) => {
                                              this.imageWidths[index] = width;
                                              this.loadOffsets();
                                          }
                                      };
                                  };
                                  componentCall.paramsGenerator_ = paramsLambda;
                              } else {
                                  this.updateStateVarsOfChildByElmtId(elmtId, {
                                      currentIndex: this.currentIndex
                                  });
                              }
                          }, { name: 'TabContentItem' });
                      }
                      ListItem.pop();
                  };
                  this.observeComponentCreation2(itemCreation2, ListItem);
                  ListItem.pop();
              }
          };
          this.forEachUpdateFunction(elmtId, this.tabItems, forEachItemGenFunction, undefined, true, false);
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
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems !== undefined && this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      __Common__.create();
                      __Common__.height(TabTitleBar.totalHeight);
                      __Common__.onAreaChange((o2, newValue) => {
                          this.menuSectionWidth = Number(newValue.width);
                      });
                  }, __Common__);
                  {
                      this.observeComponentCreation2((elmtId, isInitialRender) => {
                          if (isInitialRender) {
                              let componentCall =
                                  new d1(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ },
                                      undefined, elmtId, () => {
                                      }, {
                                          page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets',
                                          line: 204,
                                          j1: 11
                                      });
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                  return {
                                      menuItems: this.menuItems,
                                      index: 1 + TabTitleBar.instanceCount++
                                  };
                              };
                              componentCall.paramsGenerator_ = paramsLambda;
                          } else {
                              this.updateStateVarsOfChildByElmtId(elmtId, {});
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
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Swiper.create(this.swiperController);
          Swiper.index(this.currentIndex);
          Swiper.itemSpace(0);
          Swiper.indicator(false);
          Swiper.width('100%');
          Swiper.height('100%');
          Swiper.curve(Curve.Friction);
          Swiper.onChange((index) => {
              const offset = this.tabOffsets[index] + TabTitleBar.correctionOffset;
              this.currentIndex = index;
              this.scroller.scrollTo({
                  xOffset: offset > 0 ? offset : 0,
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

class d1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === 'function') {
          this.paramsGenerator_ = paramsLambda;
      }
      this.menuItems = [];
      this.index = 0;
      this.item = {
          value: o,
          symbolStyle: new SymbolGlyphModifier(o),
          label: {
              'id': -1,
              'type': 10003,
              params: ['sys.string.ohos_toolbar_more'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          },
      };
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.firstFocusableIndex = -1;
      this.l1 = new ObservedPropertySimplePU(false, this, 'isPopupShown');
      this.m1 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
      this.n1 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
      this.o1 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
      this.i1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new d2(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  tabTitleDialog: this.item,
                  tabTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize,
              }, undefined, -1, () => {
              }, { page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets', line: 273, j1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
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
              jsDialog.paramsGenerator_ = paramsLambda;
          },
          maskColor: Color.Transparent,
          isModal: true,
          customStyle: true
      }, this);
      this.g2 = new ObservedPropertyObjectPU(new b2(this.dialogController), this, 'buttonGestureModifier');
      this.setInitiallyProvidedValue(params);
      this.declareWatch('fontSize', this.onFontSizeUpdated);
      this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
      if (params.menuItems !== undefined) {
          this.menuItems = params.menuItems;
      }
      if (params.index !== undefined) {
          this.index = params.index;
      }
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.minFontSize !== undefined) {
          this.minFontSize = params.minFontSize;
      }
      if (params.isFollowingSystemFontScale !== undefined) {
          this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
      }
      if (params.maxFontScale !== undefined) {
          this.maxFontScale = params.maxFontScale;
      }
      if (params.systemFontScale !== undefined) {
          this.systemFontScale = params.systemFontScale;
      }
      if (params.firstFocusableIndex !== undefined) {
          this.firstFocusableIndex = params.firstFocusableIndex;
      }
      if (params.isPopupShown !== undefined) {
          this.isPopupShown = params.isPopupShown;
      }
      if (params.isMoreIconOnFocus !== undefined) {
          this.isMoreIconOnFocus = params.isMoreIconOnFocus;
      }
      if (params.isMoreIconOnHover !== undefined) {
          this.isMoreIconOnHover = params.isMoreIconOnHover;
      }
      if (params.isMoreIconOnClick !== undefined) {
          this.isMoreIconOnClick = params.isMoreIconOnClick;
      }
      if (params.fontSize === undefined) {
          this.i1.set(1);
      }
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
      if (params.buttonGestureModifier !== undefined) {
          this.buttonGestureModifier = params.buttonGestureModifier;
      }
  }

  updateStateVars(params) {
      this.i1.reset(params.fontSize);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.l1.purgeDependencyOnElmtId(rmElmtId);
      this.m1.purgeDependencyOnElmtId(rmElmtId);
      this.n1.purgeDependencyOnElmtId(rmElmtId);
      this.o1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
      this.g2.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
      this.l1.aboutToBeDeleted();
      this.m1.aboutToBeDeleted();
      this.n1.aboutToBeDeleted();
      this.o1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
      this.g2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }

  get isPopupShown() {
      return this.l1.get();
  }

  set isPopupShown(newValue) {
      this.l1.set(newValue);
  }

  get isMoreIconOnFocus() {
      return this.m1.get();
  }

  set isMoreIconOnFocus(newValue) {
      this.m1.set(newValue);
  }

  get isMoreIconOnHover() {
      return this.n1.get();
  }

  set isMoreIconOnHover(newValue) {
      this.n1.set(newValue);
  }

  get isMoreIconOnClick() {
      return this.o1.get();
  }

  set isMoreIconOnClick(newValue) {
      this.o1.set(newValue);
  }

  get fontSize() {
      return this.i1.get();
  }

  set fontSize(newValue) {
      this.i1.set(newValue);
  }

  get buttonGestureModifier() {
      return this.g2.get();
  }

  set buttonGestureModifier(newValue) {
      this.g2.set(newValue);
  }

  getMoreIconFgColor() {
      return this.isMoreIconOnClick
          ? {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          } : {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_titlebar_icon'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
  }

  getMoreIconBgColor() {
      if (this.isMoreIconOnClick) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_click_effect'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else if (this.isMoreIconOnHover) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else {
          return Color.Transparent;
      }
  }

  aboutToAppear() {
      try {
          let n2 = this.getUIContext();
          this.isFollowingSystemFontScale = n2.isFollowingSystemFontScale();
          this.maxFontScale = n2.getMaxFontScale();
      } catch (m2) {
          let code = m2.code;
          let message = m2.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      }
      this.menuItems.forEach((item, index) => {
          if (item.isEnabled && this.firstFocusableIndex === -1 &&
              index > d1.maxCountOfVisibleItems - 2) {
              this.firstFocusableIndex = this.index * 1000 + index + 1;
          }
      });
      this.fontSize = this.decideFontScale();
  }

  decideFontScale() {
      let l2 = this.getUIContext();
      this.systemFontScale = l2.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
          return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
  }

  onFontSizeUpdated() {
      this.buttonGestureModifier.fontSize = this.fontSize;
  }

  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.height('100%');
          Column.justifyContent(FlexAlign.Center);
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems.length <= d1.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall =
                                          new e1(this, { item: item, index: this.index * 1000 + index + 1 },
                                              undefined, elmtId, () => {
                                              }, {
                                                  page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets',
                                                  line: 342,
                                                  j1: 13
                                              });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              item: item,
                                              index: this.index * 1000 + index + 1
                                          };
                                      };
                                      componentCall.paramsGenerator_ = paramsLambda;
                                  } else {
                                      this.updateStateVarsOfChildByElmtId(elmtId, {});
                                  }
                              }, { name: 'ImageMenuItem' });
                          }
                      };
                      this.forEachUpdateFunction(elmtId, this.menuItems, forEachItemGenFunction, undefined, true,
                          false);
                  }, ForEach);
                  ForEach.pop();
              });
          } else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall =
                                          new e1(this, { item: item, index: this.index * 1000 + index + 1 },
                                              undefined, elmtId, () => {
                                              }, {
                                                  page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets',
                                                  line: 347,
                                                  j1: 15
                                              });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              item: item,
                                              index: this.index * 1000 + index + 1
                                          };
                                      };
                                      componentCall.paramsGenerator_ = paramsLambda;
                                  } else {
                                      this.updateStateVarsOfChildByElmtId(elmtId, {});
                                  }
                              }, { name: 'ImageMenuItem' });
                          }
                      };
                      this.forEachUpdateFunction(elmtId, this.menuItems.slice(0, d1.maxCountOfVisibleItems - 1),
                          forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                      Button.accessibilityText({
                          'id': -1,
                          'type': 10003,
                          params: ['sys.string.ohos_toolbar_more'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      });
                      Button.width(e1.imageHotZoneWidth);
                      Button.height(e1.imageHotZoneWidth);
                      Button.borderRadius(e1.buttonBorderRadius);
                      Button.foregroundColor(this.getMoreIconFgColor());
                      Button.backgroundColor(this.getMoreIconBgColor());
                      ViewStackProcessor.visualState('focused');
                      Button.border({
                          radius: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.ohos_id_corner_radius_clicked'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          width: e1.focusBorderWidth,
                          color: {
                              'id': -1,
                              'type': 10001,
                              params: ['sys.color.ohos_id_color_focused_outline'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          style: BorderStyle.Solid
                      });
                      ViewStackProcessor.visualState('normal');
                      Button.border({
                          radius: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.ohos_id_corner_radius_clicked'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          width: 0
                      });
                      ViewStackProcessor.visualState();
                      Button.onFocus(() => this.isMoreIconOnFocus = true);
                      Button.onBlur(() => this.isMoreIconOnFocus = false);
                      Button.onHover((isOn) => this.isMoreIconOnHover = isOn);
                      Button.onKeyEvent((event) => {
                          if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                              return;
                          }
                          if (event.type === KeyType.Down) {
                              this.isMoreIconOnClick = true;
                          }
                          if (event.type === KeyType.Up) {
                              this.isMoreIconOnClick = false;
                          }
                      });
                      Button.onTouch((event) => {
                          if (event.type === TouchType.Down) {
                              this.isMoreIconOnClick = true;
                          }
                          if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
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
                          onStateChange: (e) => {
                              this.isPopupShown = e.isVisible;
                              if (!e.isVisible) {
                                  this.isMoreIconOnClick = false;
                              }
                          }
                      });
                  }, Button);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create(o);
                      SymbolGlyph.fontSize(c2.symbolSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.fontColor([{
                          'id': -1,
                          'type': 10001,
                          params: ['sys.color.icon_primary'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      }]);
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

  popupBuilder(parent = null) {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.width(e1.imageHotZoneWidth + d1.focusPadding * d1.marginsNum);
          Column.margin({ top: d1.focusPadding, bottom: d1.focusPadding });
          Column.onAppear(() => {
              focusControl.requestFocus(e1.focusablePrefix + this.firstFocusableIndex);
          });
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          ForEach.create();
          const forEachItemGenFunction = (_item, index) => {
              const item = _item;
              {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      if (isInitialRender) {
                          let componentCall = new e1(this, {
                              item: item, index: this.index * 1000 +
                              d1.maxCountOfVisibleItems + index
                          }, undefined, elmtId, () => {
                          }, { page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets', line: 430, j1: 11 });
                          ViewPU.create(componentCall);
                          let paramsLambda = () => {
                              return {
                                  item: item,
                                  index: this.index * 1000 +
                                  d1.maxCountOfVisibleItems + index
                              };
                          };
                          componentCall.paramsGenerator_ = paramsLambda;
                      } else {
                          this.updateStateVarsOfChildByElmtId(elmtId, {});
                      }
                  }, { name: 'ImageMenuItem' });
              }
          };
          this.forEachUpdateFunction(elmtId,
              this.menuItems.slice(d1.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction,
              undefined, true, false);
      }, ForEach);
      ForEach.pop();
      Column.pop();
  }

  rerender() {
      this.updateDirtyElements();
  }
}

d1.maxCountOfVisibleItems = 1;
d1.focusPadding = 4;
d1.marginsNum = 2;

class c2 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === 'function') {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = { title: '' };
      this.index = 0;
      this.maxIndex = 0;
      this.onCustomClick = undefined;
      this.onImageComplete = undefined;
      this.f2 = new SynchedPropertySimpleOneWayPU(params.currentIndex, this, 'currentIndex');
      this.q1 = new ObservedPropertySimplePU(false, this, 'isOnFocus');
      this.s1 = new ObservedPropertySimplePU(false, this, 'isOnHover');
      this.t1 = new ObservedPropertySimplePU(false, this, 'isOnClick');
      this.e2 = new ObservedPropertySimplePU(0, this, 'tabWidth');
      this.h2 = new ObservedPropertySimplePU(24, this, 'imageWidth');
      this.i2 = new ObservedPropertySimplePU(24, this, 'imageHeight');
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.index !== undefined) {
          this.index = params.index;
      }
      if (params.maxIndex !== undefined) {
          this.maxIndex = params.maxIndex;
      }
      if (params.onCustomClick !== undefined) {
          this.onCustomClick = params.onCustomClick;
      }
      if (params.onImageComplete !== undefined) {
          this.onImageComplete = params.onImageComplete;
      }
      if (params.isOnFocus !== undefined) {
          this.isOnFocus = params.isOnFocus;
      }
      if (params.isOnHover !== undefined) {
          this.isOnHover = params.isOnHover;
      }
      if (params.isOnClick !== undefined) {
          this.isOnClick = params.isOnClick;
      }
      if (params.tabWidth !== undefined) {
          this.tabWidth = params.tabWidth;
      }
      if (params.imageWidth !== undefined) {
          this.imageWidth = params.imageWidth;
      }
      if (params.imageHeight !== undefined) {
          this.imageHeight = params.imageHeight;
      }
  }

  updateStateVars(params) {
      this.f2.reset(params.currentIndex);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.f2.purgeDependencyOnElmtId(rmElmtId);
      this.q1.purgeDependencyOnElmtId(rmElmtId);
      this.s1.purgeDependencyOnElmtId(rmElmtId);
      this.t1.purgeDependencyOnElmtId(rmElmtId);
      this.e2.purgeDependencyOnElmtId(rmElmtId);
      this.h2.purgeDependencyOnElmtId(rmElmtId);
      this.i2.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
      this.f2.aboutToBeDeleted();
      this.q1.aboutToBeDeleted();
      this.s1.aboutToBeDeleted();
      this.t1.aboutToBeDeleted();
      this.e2.aboutToBeDeleted();
      this.h2.aboutToBeDeleted();
      this.i2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }

  get currentIndex() {
      return this.f2.get();
  }

  set currentIndex(newValue) {
      this.f2.set(newValue);
  }

  get isOnFocus() {
      return this.q1.get();
  }

  set isOnFocus(newValue) {
      this.q1.set(newValue);
  }

  get isOnHover() {
      return this.s1.get();
  }

  set isOnHover(newValue) {
      this.s1.set(newValue);
  }

  get isOnClick() {
      return this.t1.get();
  }

  set isOnClick(newValue) {
      this.t1.set(newValue);
  }

  get tabWidth() {
      return this.e2.get();
  }

  set tabWidth(newValue) {
      this.e2.set(newValue);
  }

  get imageWidth() {
      return this.h2.get();
  }

  set imageWidth(newValue) {
      this.h2.set(newValue);
  }

  get imageHeight() {
      return this.i2.get();
  }

  set imageHeight(newValue) {
      this.i2.set(newValue);
  }

  getBgColor() {
      if (this.isOnClick) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_click_effect'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else if (this.isOnHover) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else {
          return Color.Transparent;
      }
  }

  getBorderAttr() {
      if (this.isOnFocus) {
          return {
              radius: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_corner_radius_clicked'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              },
              width: c2.focusBorderWidth,
              color: {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_focused_outline'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              },
              style: BorderStyle.Solid
          };
      }
      return { width: 0 };
  }

  getImageScaleFactor() {
      return this.index === this.currentIndex ? c2.imageMagnificationFactor : 1;
  }

  getImageLayoutWidth() {
      return c2.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth;
  }

  toStringFormat(resource) {
      if (typeof resource === 'string') {
          return resource;
      } else if (typeof resource === 'undefined') {
          return '';
      } else {
          let k2 = '';
          try {
              k2 = getContext()?.resourceManager?.getStringSync(resource);
          } catch (err) {
              let code = err?.code;
              let message = err?.message;
              hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
          }
          return k2;
      }
  }

  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Stack.create();
          Stack.margin({
              left: this.index === 0 ? c2.marginFirst : 0,
              right: this.index === this.maxIndex ? 12 : 0
          });
      }, Stack);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.height(TabTitleBar.totalHeight);
          Row.alignItems(VerticalAlign.Center);
          Row.justifyContent(FlexAlign.Center);
          Row.borderRadius(c2.buttonBorderRadius);
          Row.backgroundColor(this.getBgColor());
          Row.onAreaChange((j2, newValue) => {
              this.tabWidth = Number(newValue.width);
          });
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.justifyContent(FlexAlign.Center);
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.item.icon === undefined && this.item.symbolStyle === undefined) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.item.title);
                      Context.animation({ duration: 300 });
                      Text.fontSize(this.index === this.currentIndex
                          ? {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.ohos_id_text_size_headline7'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          } : {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.ohos_id_text_size_headline9'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          });
                      Text.fontColor(this.index === this.currentIndex
                          ? {
                              'id': -1,
                              'type': 10001,
                              params: ['sys.color.ohos_id_color_titlebar_text'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          } : {
                              'id': -1,
                              'type': 10001,
                              params: ['sys.color.ohos_id_color_titlebar_text_off'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          });
                      Text.fontWeight(FontWeight.Medium);
                      Text.focusable(true);
                      Context.animation(null);
                      Text.padding({
                          top: this.index === this.currentIndex ? 6 : 10,
                          left: c2.paddingLeft,
                          bottom: 2,
                          right: c2.paddingRight
                      });
                      Text.onFocus(() => this.isOnFocus = true);
                      Text.onBlur(() => this.isOnFocus = false);
                      Text.onHover((isOn) => this.isOnHover = isOn);
                      Text.onKeyEvent((event) => {
                          if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                              return;
                          }
                          if (event.type === KeyType.Down) {
                              this.isOnClick = true;
                          }
                          if (event.type === KeyType.Up) {
                              this.isOnClick = false;
                          }
                      });
                      Text.onTouch((event) => {
                          if (event.type === TouchType.Down) {
                              this.isOnClick = true;
                          }
                          if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                              this.isOnClick = false;
                          }
                      });
                      Text.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                      Text.accessibilitySelected(this.index === this.currentIndex);
                  }, Text);
                  Text.pop();
              });
          } else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Context.animation({ duration: 300 });
                      Row.width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
                      c2.paddingLeft + c2.paddingRight);
                      Row.constraintSize({
                          minWidth: c2.imageHotZoneWidth,
                          minHeight: c2.imageHotZoneWidth
                      });
                      Context.animation(null);
                      Row.justifyContent(FlexAlign.Center);
                      Row.onFocus(() => this.isOnFocus = true);
                      Row.onBlur(() => this.isOnFocus = false);
                      Row.onHover((isOn) => this.isOnHover = isOn);
                      Row.onKeyEvent((event) => {
                          if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                              return;
                          }
                          if (event.type === KeyType.Down) {
                              this.isOnClick = true;
                          }
                          if (event.type === KeyType.Up) {
                              this.isOnClick = false;
                          }
                      });
                      Row.onTouch((event) => {
                          if (event.type === TouchType.Down) {
                              this.isOnClick = true;
                          }
                          if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                              this.isOnClick = false;
                          }
                      });
                      Row.onClick(() => this.onCustomClick && this.onCustomClick(this.index));
                      Row.accessibilitySelected(this.index === this.currentIndex);
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.item.symbolStyle) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  Context.animation({ duration: 300 });
                                  SymbolGlyph.fontColor([{
                                      'id': -1,
                                      'type': 10001,
                                      params: ['sys.color.icon_primary'],
                                      'bundleName': '__harDefaultBundleName__',
                                      'moduleName': '__harDefaultModuleName__'
                                  }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                  SymbolGlyph.fontSize(c2.symbolSize);
                                  SymbolGlyph.width(this.getImageLayoutWidth());
                                  SymbolGlyph.height(c2.imageSize);
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
                      } else {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  If.create();
                                  if (Util.u1(this.item.icon)) {
                                      this.ifElseBranchUpdateFunction(0, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              SymbolGlyph.create(this.item.icon);
                                              Context.animation({ duration: 300 });
                                              SymbolGlyph.fontColor([{
                                                  'id': -1,
                                                  'type': 10001,
                                                  params: ['sys.color.icon_primary'],
                                                  'bundleName': '__harDefaultBundleName__',
                                                  'moduleName': '__harDefaultModuleName__'
                                              }]);
                                              SymbolGlyph.fontSize(c2.symbolSize);
                                              SymbolGlyph.width(this.getImageLayoutWidth());
                                              SymbolGlyph.height(c2.imageSize);
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
                                  } else {
                                      this.ifElseBranchUpdateFunction(1, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              Image.create(this.item.icon);
                                              Context.animation({ duration: 300 });
                                              Image.alt(this.item.title);
                                              Image.width(this.getImageLayoutWidth());
                                              Image.height(c2.imageSize);
                                              Image.objectFit(ImageFit.Fill);
                                              Image.accessibilityText(this.toStringFormat(this.item.title));
                                              Image.scale({
                                                  x: this.getImageScaleFactor(),
                                                  y: this.getImageScaleFactor()
                                              });
                                              Context.animation(null);
                                              Image.hitTestBehavior(HitTestMode.None);
                                              Image.focusable(true);
                                              Image.onComplete((event) => {
                                                  if (!this.onImageComplete) {
                                                      return;
                                                  }
                                                  this.imageWidth = px2vp(event?.width);
                                                  this.imageHeight = px2vp(event?.height);
                                                  this.onImageComplete(px2vp(event?.componentWidth) +
                                                  c2.paddingLeft + c2.paddingRight);
                                              });
                                              Image.onError((event) => {
                                                  if (!this.onImageComplete) {
                                                      return;
                                                  }
                                                  this.onImageComplete(px2vp(event.componentWidth) +
                                                  c2.paddingLeft + c2.paddingRight);
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
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.isOnFocus && this.tabWidth > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.width(this.tabWidth);
                      Row.height(TabTitleBar.totalHeight);
                      Row.hitTestBehavior(HitTestMode.None);
                      Row.borderRadius(c2.buttonBorderRadius);
                      ViewStackProcessor.visualState('focused');
                      Row.border(this.getBorderAttr());
                      ViewStackProcessor.visualState('normal');
                      Row.border({
                          radius: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.ohos_id_corner_radius_clicked'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          width: 0
                      });
                      ViewStackProcessor.visualState();
                  }, Row);
                  Row.pop();
              });
          } else {
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

c2.imageSize = 24;
c2.symbolSize = '24vp';
c2.imageHotZoneWidth = 48;
c2.imageMagnificationFactor = 1.4;
c2.buttonBorderRadius = 8;
c2.focusBorderWidth = 2;
c2.paddingLeft = 8;
c2.paddingRight = 8;
c2.marginFirst = 16;

class e1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === 'function') {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = { value: '' };
      this.index = 0;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.isPopup = false;
      this.q1 = new ObservedPropertySimplePU(false, this, 'isOnFocus');
      this.s1 = new ObservedPropertySimplePU(false, this, 'isOnHover');
      this.t1 = new ObservedPropertySimplePU(false, this, 'isOnClick');
      this.i1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new d2(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  tabTitleDialog: this.item,
                  tabTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize,
              }, undefined, -1, () => {
              }, { page: 'library/src/main/ets/components/mainpage/TabTitleBar.ets', line: 722, j1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
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
              jsDialog.paramsGenerator_ = paramsLambda;
          },
          maskColor: Color.Transparent,
          isModal: true,
          customStyle: true
      }, this);
      this.g2 = new ObservedPropertyObjectPU(new b2(this.dialogController), this, 'buttonGestureModifier');
      this.setInitiallyProvidedValue(params);
      this.declareWatch('fontSize', this.onFontSizeUpdated);
      this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.index !== undefined) {
          this.index = params.index;
      }
      if (params.minFontSize !== undefined) {
          this.minFontSize = params.minFontSize;
      }
      if (params.isFollowingSystemFontScale !== undefined) {
          this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
      }
      if (params.maxFontScale !== undefined) {
          this.maxFontScale = params.maxFontScale;
      }
      if (params.systemFontScale !== undefined) {
          this.systemFontScale = params.systemFontScale;
      }
      if (params.isPopup !== undefined) {
          this.isPopup = params.isPopup;
      }
      if (params.isOnFocus !== undefined) {
          this.isOnFocus = params.isOnFocus;
      }
      if (params.isOnHover !== undefined) {
          this.isOnHover = params.isOnHover;
      }
      if (params.isOnClick !== undefined) {
          this.isOnClick = params.isOnClick;
      }
      if (params.fontSize === undefined) {
          this.i1.set(1);
      }
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
      if (params.buttonGestureModifier !== undefined) {
          this.buttonGestureModifier = params.buttonGestureModifier;
      }
  }

  updateStateVars(params) {
      this.i1.reset(params.fontSize);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.q1.purgeDependencyOnElmtId(rmElmtId);
      this.s1.purgeDependencyOnElmtId(rmElmtId);
      this.t1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
      this.g2.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
      this.q1.aboutToBeDeleted();
      this.s1.aboutToBeDeleted();
      this.t1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
      this.g2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }

  get isOnFocus() {
      return this.q1.get();
  }

  set isOnFocus(newValue) {
      this.q1.set(newValue);
  }

  get isOnHover() {
      return this.s1.get();
  }

  set isOnHover(newValue) {
      this.s1.set(newValue);
  }

  get isOnClick() {
      return this.t1.get();
  }

  set isOnClick(newValue) {
      this.t1.set(newValue);
  }

  get fontSize() {
      return this.i1.get();
  }

  set fontSize(newValue) {
      this.i1.set(newValue);
  }

  get buttonGestureModifier() {
      return this.g2.get();
  }

  set buttonGestureModifier(newValue) {
      this.g2.set(newValue);
  }

  textDialog() {
      if (this.item.value === o) {
          return {
              'id': -1,
              'type': 10003,
              params: ['sys.string.ohos_toolbar_more'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else {
          return this.item.label ? this.item.label : '';
      }
  }

  getFgColor() {
      return this.isOnClick
          ? {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_titlebar_icon_pressed'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          } : {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_titlebar_icon'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
  }

  getBgColor() {
      if (this.isOnClick) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_click_effect'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else if (this.isOnHover) {
          return {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_hover'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__'
          };
      } else {
          return Color.Transparent;
      }
  }

  toStringFormat(resource) {
      if (typeof resource === 'string') {
          return resource;
      } else if (typeof resource === 'undefined') {
          return '';
      } else {
          let i2 = '';
          try {
              i2 = getContext()?.resourceManager?.getStringSync(resource);
          } catch (err) {
              let code = err?.code;
              let message = err?.message;
              hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
          }
          return i2;
      }
  }

  getAccessibilityReadText() {
      if (this.item.value === o) {
          return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } else if (this.item.accessibilityText) {
          return this.toStringFormat(this.item.accessibilityText);
      } else if (this.item.label) {
          return this.toStringFormat(this.item.label);
      }
      return ' ';
  }

  onPlaceChildren(selfLayoutInfo, children, constraint) {
      children.forEach((child) => {
          child.layout({ x: 0, y: 0 });
      });
      this.fontSize = this.decideFontScale();
  }

  onFontSizeUpdated() {
      this.buttonGestureModifier.fontSize = this.fontSize;
  }

  aboutToAppear() {
      try {
          let h2 = this.getUIContext();
          this.isFollowingSystemFontScale = h2.isFollowingSystemFontScale();
          this.maxFontScale = h2.getMaxFontScale();
      } catch (g2) {
          let code = g2.code;
          let message = g2.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
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
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
          Button.accessibilityText(this.getAccessibilityReadText());
          Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
          Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
          Button.width(e1.imageHotZoneWidth);
          Button.height(e1.imageHotZoneWidth);
          Button.borderRadius(e1.buttonBorderRadius);
          Button.foregroundColor(this.getFgColor());
          Button.backgroundColor(this.getBgColor());
          Button.opacity(this.item.isEnabled ? 1 : e1.disabledImageOpacity);
          ViewStackProcessor.visualState('focused');
          Button.border({
              radius: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_corner_radius_clicked'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              },
              width: e1.focusBorderWidth,
              color: {
                  'id': -1,
                  'type': 10001,
                  params: ['sys.color.ohos_id_color_focused_outline'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              },
              style: BorderStyle.Solid
          });
          ViewStackProcessor.visualState('normal');
          Button.border({
              radius: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.ohos_id_corner_radius_clicked'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__'
              },
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
          Button.onHover((isOn) => {
              if (!this.item.isEnabled) {
                  return;
              }
              this.isOnHover = isOn;
          });
          Button.onKeyEvent((event) => {
              if (!this.item.isEnabled) {
                  return;
              }
              if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                  return;
              }
              if (event.type === KeyType.Down) {
                  this.isOnClick = true;
              }
              if (event.type === KeyType.Up) {
                  this.isOnClick = false;
              }
          });
          Button.onTouch((event) => {
              if (!this.item.isEnabled) {
                  return;
              }
              if (event.type === TouchType.Down) {
                  this.isOnClick = true;
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  this.isOnClick = false;
                  if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                      this.dialogController?.close();
                  }
              }
          });
          Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
          Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
      }, Button);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.item.symbolStyle) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create();
                      SymbolGlyph.fontColor([{
                          'id': -1,
                          'type': 10001,
                          params: ['sys.color.font_primary'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      }]);
                      SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                      SymbolGlyph.fontSize(c2.symbolSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.focusable(this.item?.isEnabled);
                      SymbolGlyph.key(e1.focusablePrefix + this.index);
                      SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  }, SymbolGlyph);
              });
          } else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (Util.u1(this.item.value)) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create(this.item.value);
                                  SymbolGlyph.fontColor([{
                                      'id': -1,
                                      'type': 10001,
                                      params: ['sys.color.font_primary'],
                                      'bundleName': '__harDefaultBundleName__',
                                      'moduleName': '__harDefaultModuleName__'
                                  }]);
                                  SymbolGlyph.fontSize(c2.symbolSize);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.item?.isEnabled);
                                  SymbolGlyph.key(e1.focusablePrefix + this.index);
                              }, SymbolGlyph);
                          });
                      } else {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.item.value);
                                  Image.width(e1.imageSize);
                                  Image.height(e1.imageSize);
                                  Image.focusable(this.item.isEnabled);
                                  Image.key(e1.focusablePrefix + this.index);
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

e1.imageSize = 24;
e1.imageHotZoneWidth = 48;
e1.buttonBorderRadius = 8;
e1.focusBorderWidth = 2;
e1.disabledImageOpacity = 0.4;
e1.focusablePrefix = 'Id-TabTitleBar-ImageMenuItem-';

class d2 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === 'function') {
          this.paramsGenerator_ = paramsLambda;
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
      this.v1 = this.createStorageLink('mainWindow', undefined, 'mainWindow');
      this.i1 = new ObservedPropertySimplePU(1, this, 'fontSize');
      this.w1 = new ObservedPropertySimplePU(1, this, 'maxLines');
      this.z1 = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
      this.cancel = () => {
      };
      this.confirm = () => {
      };
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
      if (params.tabTitleDialog !== undefined) {
          this.tabTitleDialog = params.tabTitleDialog;
      }
      if (params.callbackId !== undefined) {
          this.callbackId = params.callbackId;
      }
      if (params.tabTitleBarDialog !== undefined) {
          this.tabTitleBarDialog = params.tabTitleBarDialog;
      }
      if (params.mainWindowStage !== undefined) {
          this.mainWindowStage = params.mainWindowStage;
      }
      if (params.controller !== undefined) {
          this.controller = params.controller;
      }
      if (params.minFontSize !== undefined) {
          this.minFontSize = params.minFontSize;
      }
      if (params.maxFontSize !== undefined) {
          this.maxFontSize = params.maxFontSize;
      }
      if (params.screenWidth !== undefined) {
          this.screenWidth = params.screenWidth;
      }
      if (params.verticalScreenLines !== undefined) {
          this.verticalScreenLines = params.verticalScreenLines;
      }
      if (params.horizontalsScreenLines !== undefined) {
          this.horizontalsScreenLines = params.horizontalsScreenLines;
      }
      if (params.fontSize !== undefined) {
          this.fontSize = params.fontSize;
      }
      if (params.maxLines !== undefined) {
          this.maxLines = params.maxLines;
      }
      if (params.cancel !== undefined) {
          this.cancel = params.cancel;
      }
      if (params.confirm !== undefined) {
          this.confirm = params.confirm;
      }
  }

  updateStateVars(params) {
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.v1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
      this.w1.purgeDependencyOnElmtId(rmElmtId);
      this.z1.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
      this.v1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
      this.w1.aboutToBeDeleted();
      this.z1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }

  setController(ctr) {
      this.controller = ctr;
  }

  get mainWindow() {
      return this.v1.get();
  }

  set mainWindow(newValue) {
      this.v1.set(newValue);
  }

  get fontSize() {
      return this.i1.get();
  }

  set fontSize(newValue) {
      this.i1.set(newValue);
  }

  get maxLines() {
      return this.w1.get();
  }

  set maxLines(newValue) {
      this.w1.set(newValue);
  }

  get windowStandardHeight() {
      return this.z1.get();
  }

  set windowStandardHeight(newValue) {
      this.z1.set(newValue);
  }

  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.tabTitleBarDialog) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width(this.fontSize === this.maxFontSize ? b1 : c1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? b1 : c1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({
                          'id': -1,
                          'type': 10002,
                          params: ['sys.float.corner_radius_level10'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      });
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.tabTitleDialog.symbolStyle) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{
                                      'id': -1,
                                      'type': 10001,
                                      params: ['sys.color.font_primary'],
                                      'bundleName': '__harDefaultBundleName__',
                                      'moduleName': '__harDefaultModuleName__'
                                  }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolStyle);
                                  SymbolGlyph.fontSize(a1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                  SymbolGlyph.margin({
                                      top: {
                                          'id': -1,
                                          'type': 10002,
                                          params: ['sys.float.padding_level24'],
                                          'bundleName': '__harDefaultBundleName__',
                                          'moduleName': '__harDefaultModuleName__'
                                      },
                                      bottom: {
                                          'id': -1,
                                          'type': 10002,
                                          params: ['sys.float.padding_level8'],
                                          'bundleName': '__harDefaultBundleName__',
                                          'moduleName': '__harDefaultModuleName__'
                                      },
                                  });
                                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                              }, SymbolGlyph);
                          });
                      } else if (this.tabTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  If.create();
                                  if (Util.u1(this.tabTitleDialog.value)) {
                                      this.ifElseBranchUpdateFunction(0, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              SymbolGlyph.create(this.tabTitleDialog.value);
                                              SymbolGlyph.fontColor([{
                                                  'id': -1,
                                                  'type': 10001,
                                                  params: ['sys.color.font_primary'],
                                                  'bundleName': '__harDefaultBundleName__',
                                                  'moduleName': '__harDefaultModuleName__'
                                              }]);
                                              SymbolGlyph.fontSize(a1);
                                              SymbolGlyph.draggable(false);
                                              SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                              SymbolGlyph.margin({
                                                  top: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level24'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                                  bottom: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level8'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                              });
                                          }, SymbolGlyph);
                                      });
                                  } else {
                                      this.ifElseBranchUpdateFunction(1, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              Image.create(this.tabTitleDialog.value);
                                              Image.width(a1);
                                              Image.height(a1);
                                              Image.margin({
                                                  top: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level24'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                                  bottom: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level8'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                              });
                                              Image.fillColor({
                                                  'id': -1,
                                                  'type': 10001,
                                                  params: ['sys.color.icon_primary'],
                                                  'bundleName': '__harDefaultBundleName__',
                                                  'moduleName': '__harDefaultModuleName__'
                                              });
                                          }, Image);
                                      });
                                  }
                              }, If);
                              If.pop();
                          });
                      } else {
                          this.ifElseBranchUpdateFunction(2, () => {
                          });
                      }
                  }, If);
                  If.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width('100%');
                      Column.padding({
                          left: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.padding_level4'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          right: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.padding_level4'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                          bottom: {
                              'id': -1,
                              'type': 10002,
                              params: ['sys.float.padding_level12'],
                              'bundleName': '__harDefaultBundleName__',
                              'moduleName': '__harDefaultModuleName__'
                          },
                      });
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.tabTitleBarDialog);
                      Text.fontSize(u);
                      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                      Text.maxLines(this.maxLines);
                      Text.width('100%');
                      Text.textAlign(TextAlign.Center);
                      Text.fontColor({
                          'id': -1,
                          'type': 10001,
                          params: ['sys.color.font_primary'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      });
                  }, Text);
                  Text.pop();
                  Column.pop();
                  Column.pop();
              });
          } else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width(this.fontSize === this.maxFontSize ? b1 : c1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? b1 : c1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({
                          'id': -1,
                          'type': 10002,
                          params: ['sys.float.corner_radius_level10'],
                          'bundleName': '__harDefaultBundleName__',
                          'moduleName': '__harDefaultModuleName__'
                      });
                      Column.justifyContent(FlexAlign.Center);
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.tabTitleDialog.symbolStyle) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{
                                      'id': -1,
                                      'type': 10001,
                                      params: ['sys.color.font_primary'],
                                      'bundleName': '__harDefaultBundleName__',
                                      'moduleName': '__harDefaultModuleName__'
                                  }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.symbolStyle);
                                  SymbolGlyph.fontSize(a1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                              }, SymbolGlyph);
                          });
                      } else if (this.tabTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  If.create();
                                  if (Util.u1(this.tabTitleDialog.value)) {
                                      this.ifElseBranchUpdateFunction(0, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              SymbolGlyph.create(this.tabTitleDialog.value);
                                              SymbolGlyph.fontColor([{
                                                  'id': -1,
                                                  'type': 10001,
                                                  params: ['sys.color.font_primary'],
                                                  'bundleName': '__harDefaultBundleName__',
                                                  'moduleName': '__harDefaultModuleName__'
                                              }]);
                                              SymbolGlyph.fontSize(a1);
                                              SymbolGlyph.draggable(false);
                                              SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                              SymbolGlyph.margin({
                                                  top: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level24'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                                  bottom: {
                                                      'id': -1,
                                                      'type': 10002,
                                                      params: ['sys.float.padding_level8'],
                                                      'bundleName': '__harDefaultBundleName__',
                                                      'moduleName': '__harDefaultModuleName__'
                                                  },
                                              });
                                          }, SymbolGlyph);
                                      });
                                  } else {
                                      this.ifElseBranchUpdateFunction(1, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              Image.create(this.tabTitleDialog.value);
                                              Image.width(a1);
                                              Image.height(a1);
                                              Image.fillColor({
                                                  'id': -1,
                                                  'type': 10001,
                                                  params: ['sys.color.icon_primary'],
                                                  'bundleName': '__harDefaultBundleName__',
                                                  'moduleName': '__harDefaultModuleName__'
                                              });
                                          }, Image);
                                      });
                                  }
                              }, If);
                              If.pop();
                          });
                      } else {
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
      let context = this.getUIContext().getHostContext();
      this.mainWindowStage = context.windowStage.getMainWindowSync();
      let properties = this.mainWindowStage.getWindowProperties();
      let rect = properties.windowRect;
      if (px2vp(rect.height) > this.screenWidth) {
          this.maxLines = this.verticalScreenLines;
      } else {
          this.maxLines = this.horizontalsScreenLines;
      }
  }

  rerender() {
      this.updateDirtyElements();
  }
}

class Util {
  static u1(e2) {
      if (!Util.a2(e2)) {
          return false;
      }
      let resource = e2;
      return resource.type === t;
  }

  static a2(resource) {
      if (!resource) {
          return false;
      }
      if (typeof resource === 'string' || typeof resource === 'undefined') {
          return false;
      }
      return true;
  }
}

export default {
  TabTitleBar: TabTitleBar
};