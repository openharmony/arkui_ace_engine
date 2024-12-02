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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const MeasureText = requireNapi('measure');
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
import { SymbolGlyphModifier } from "@ohos.arkui.modifier";
const d1 = { "id": -1, "type": 40000, params: ['sys.symbol.dot_grid_2x2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const f1 = '18.3fp';
const g1 = '64vp';
const h1 = '256vp';
const i1 = '216vp';
export class TabTitleBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.tabItems = [];
      this.menuItems = [];
      this.swiperContent = undefined;
      this.j2 = new ObservedPropertySimplePU(0, this, "tabWidth");
      this.l2 = new ObservedPropertySimplePU(0, this, "currentIndex");
      this.u1 = new ObservedPropertySimplePU(1, this, "fontSize");
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
      this.j2.purgeDependencyOnElmtId(rmElmtId);
      this.l2.purgeDependencyOnElmtId(rmElmtId);
      this.u1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.j2.aboutToBeDeleted();
      this.l2.aboutToBeDeleted();
      this.u1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get tabWidth() {
      return this.j2.get();
  }
  set tabWidth(newValue) {
      this.j2.set(newValue);
  }
  get currentIndex() {
      return this.l2.get();
  }
  set currentIndex(newValue) {
      this.l2.set(newValue);
  }
  get fontSize() {
      return this.u1.get();
  }
  set fontSize(newValue) {
      this.u1.set(newValue);
  }
  GradientMask(u2, x0, y0, x1, y1, parent = null) {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.blendMode(BlendMode.DST_OUT);
          Column.width(TabTitleBar.gradientMaskWidth);
          Column.height(TabTitleBar.totalHeight);
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Canvas.create(u2);
          Canvas.width(TabTitleBar.gradientMaskWidth);
          Canvas.height(TabTitleBar.totalHeight);
          Canvas.onReady(() => {
              let v2 = u2.createLinearGradient(x0, y0, x1, y1);
              v2.addColorStop(0.0, '#ffffffff');
              v2.addColorStop(1, '#00ffffff');
              u2.fillStyle = v2;
              u2.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight);
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
      this.tabItems.forEach((t2) => {
          this.imageWidths.push(0);
      });
      this.loadOffsets();
  }
  loadOffsets() {
      this.tabOffsets.length = 0;
      let r2 = 0;
      this.tabOffsets.push(r2);
      r2 += h2.marginFirst;
      this.tabItems.forEach((s2, index) => {
          if (s2.icon !== undefined || s2.symbolIcon !== undefined) {
              if (Math.abs(this.imageWidths[index]) > h2.imageHotZoneWidth) {
                  r2 += this.imageWidths[index];
              }
              else {
                  r2 += h2.imageHotZoneWidth;
              }
          }
          else {
              r2 += h2.paddingLeft;
              r2 += px2vp(MeasureText.measureText({
                  textContent: s2.title.toString(),
                  fontSize: 18,
                  fontWeight: FontWeight.Medium,
              }));
              r2 += h2.paddingRight;
          }
          this.tabOffsets.push(r2);
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
          Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
          Flex.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          Flex.onAreaChange((q2, newValue) => {
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
              const o2 = _item;
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
                                  let componentCall = new h2(this, {
                                      item: o2,
                                      index: index,
                                      maxIndex: this.tabItems.length - 1,
                                      currentIndex: this.currentIndex,
                                      onCustomClick: (itemIndex) => this.currentIndex = itemIndex,
                                      onImageComplete: (width) => {
                                          this.imageWidths[index] = width;
                                          this.loadOffsets();
                                      }
                                  }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 143, o1: 21 });
                                  ViewPU.create(componentCall);
                                  let paramsLambda = () => {
                                      return {
                                          item: o2,
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
                              }
                              else {
                                  this.updateStateVarsOfChildByElmtId(elmtId, {
                                      currentIndex: this.currentIndex
                                  });
                              }
                          }, { name: "TabContentItem" });
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
      this.GradientMask.bind(this)(this.leftContext2D, 0, TabTitleBar.totalHeight / 2, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2);
      Stack.pop();
      this.GradientMask.bind(this)(this.rightContext2D, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2);
      Stack.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems !== undefined && this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      __Common__.create();
                      __Common__.height(TabTitleBar.totalHeight);
                      __Common__.onAreaChange((n2, newValue) => {
                          this.menuSectionWidth = Number(newValue.width);
                      });
                  }, __Common__);
                  {
                      this.observeComponentCreation2((elmtId, isInitialRender) => {
                          if (isInitialRender) {
                              let componentCall = new j1(this, { menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 173, o1: 11 });
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                  return {
                                      menuItems: this.menuItems,
                                      index: 1 + TabTitleBar.instanceCount++
                                  };
                              };
                              componentCall.paramsGenerator_ = paramsLambda;
                          }
                          else {
                              this.updateStateVarsOfChildByElmtId(elmtId, {});
                          }
                      }, { name: "CollapsibleMenuSection" });
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
class j1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.menuItems = [];
      this.index = 0;
      this.item = {
          value: d1,
          n1: new SymbolGlyphModifier(d1),
          label: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
      this.longPressTime = 500;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.firstFocusableIndex = -1;
      this.v1 = new ObservedPropertySimplePU(false, this, "isPopupShown");
      this.w1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnFocus");
      this.z1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnHover");
      this.a2 = new ObservedPropertySimplePU(false, this, "isMoreIconOnClick");
      this.u1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new i2(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  tabTitleDialog: this.item,
                  tabTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize,
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 243, o1: 14 });
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
      this.setInitiallyProvidedValue(params);
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
      if (params.longPressTime !== undefined) {
          this.longPressTime = params.longPressTime;
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
          this.u1.set(1);
      }
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
  }
  updateStateVars(params) {
      this.u1.reset(params.fontSize);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.v1.purgeDependencyOnElmtId(rmElmtId);
      this.w1.purgeDependencyOnElmtId(rmElmtId);
      this.z1.purgeDependencyOnElmtId(rmElmtId);
      this.a2.purgeDependencyOnElmtId(rmElmtId);
      this.u1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.v1.aboutToBeDeleted();
      this.w1.aboutToBeDeleted();
      this.z1.aboutToBeDeleted();
      this.a2.aboutToBeDeleted();
      this.u1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get isPopupShown() {
      return this.v1.get();
  }
  set isPopupShown(newValue) {
      this.v1.set(newValue);
  }
  get isMoreIconOnFocus() {
      return this.w1.get();
  }
  set isMoreIconOnFocus(newValue) {
      this.w1.set(newValue);
  }
  get isMoreIconOnHover() {
      return this.z1.get();
  }
  set isMoreIconOnHover(newValue) {
      this.z1.set(newValue);
  }
  get isMoreIconOnClick() {
      return this.a2.get();
  }
  set isMoreIconOnClick(newValue) {
      this.a2.set(newValue);
  }
  get fontSize() {
      return this.u1.get();
  }
  set fontSize(newValue) {
      this.u1.set(newValue);
  }
  getMoreIconFgColor() {
      return this.isMoreIconOnClick
          ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
  getMoreIconBgColor() {
      if (this.isMoreIconOnClick) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else if (this.isMoreIconOnHover) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else {
          return Color.Transparent;
      }
  }
  aboutToAppear() {
      try {
          let m2 = this.getUIContext();
          this.isFollowingSystemFontScale = m2.isFollowingSystemFontScale();
          this.maxFontScale = m2.getMaxFontScale();
      }
      catch (l2) {
          let code = l2.code;
          let message = l2.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      }
      this.menuItems.forEach((item, index) => {
          if (item.isEnabled && this.firstFocusableIndex === -1 &&
              index > j1.maxCountOfVisibleItems - 2) {
              this.firstFocusableIndex = this.index * 1000 + index + 1;
          }
      });
  }
  decideFontScale() {
      let k2 = this.getUIContext();
      this.systemFontScale = k2.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
          return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
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
          if (this.menuItems.length <= j1.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new l1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 305, o1: 13 });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              item: item,
                                              index: this.index * 1000 + index + 1
                                          };
                                      };
                                      componentCall.paramsGenerator_ = paramsLambda;
                                  }
                                  else {
                                      this.updateStateVarsOfChildByElmtId(elmtId, {});
                                  }
                              }, { name: "ImageMenuItem" });
                          }
                      };
                      this.forEachUpdateFunction(elmtId, this.menuItems, forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new l1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 310, o1: 15 });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              item: item,
                                              index: this.index * 1000 + index + 1
                                          };
                                      };
                                      componentCall.paramsGenerator_ = paramsLambda;
                                  }
                                  else {
                                      this.updateStateVarsOfChildByElmtId(elmtId, {});
                                  }
                              }, { name: "ImageMenuItem" });
                          }
                      };
                      this.forEachUpdateFunction(elmtId, this.menuItems.slice(0, j1.maxCountOfVisibleItems - 1), forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.width(l1.imageHotZoneWidth);
                      Row.height(l1.imageHotZoneWidth);
                      Row.borderRadius(l1.buttonBorderRadius);
                      Row.foregroundColor(this.getMoreIconFgColor());
                      Row.backgroundColor(this.getMoreIconBgColor());
                      Row.justifyContent(FlexAlign.Center);
                      ViewStackProcessor.visualState("focused");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          width: l1.focusBorderWidth,
                          color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          style: BorderStyle.Solid
                      });
                      ViewStackProcessor.visualState("normal");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          width: 0
                      });
                      ViewStackProcessor.visualState();
                      Row.onFocus(() => this.isMoreIconOnFocus = true);
                      Row.onBlur(() => this.isMoreIconOnFocus = false);
                      Row.onHover((isOn) => this.isMoreIconOnHover = isOn);
                      Row.onKeyEvent((event) => {
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
                      Row.onTouch((event) => {
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
                      Row.onClick(() => this.isPopupShown = true);
                      Gesture.create(GesturePriority.Low);
                      LongPressGesture.create({ repeat: false, duration: this.longPressTime });
                      LongPressGesture.onAction((event) => {
                          this.fontSize = this.decideFontScale();
                          if (event) {
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
                          onStateChange: (e) => {
                              this.isPopupShown = e.isVisible;
                              if (!e.isVisible) {
                                  this.isMoreIconOnClick = false;
                              }
                          }
                      });
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create(d1);
                      SymbolGlyph.fontSize(h2.symbolSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                      SymbolGlyph.focusable(true);
                  }, SymbolGlyph);
                  Row.pop();
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
          Column.width(l1.imageHotZoneWidth + j1.focusPadding * j1.marginsNum);
          Column.margin({ top: j1.focusPadding, bottom: j1.focusPadding });
          Column.onAppear(() => {
              focusControl.requestFocus(l1.focusablePrefix + this.firstFocusableIndex);
          });
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          ForEach.create();
          const forEachItemGenFunction = (_item, index) => {
              const item = _item;
              {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      if (isInitialRender) {
                          let componentCall = new l1(this, { item: item, index: this.index * 1000 +
                                  j1.maxCountOfVisibleItems + index }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/TabTitleBar.ets", line: 402, o1: 11 });
                          ViewPU.create(componentCall);
                          let paramsLambda = () => {
                              return {
                                  item: item,
                                  index: this.index * 1000 +
                                      j1.maxCountOfVisibleItems + index
                              };
                          };
                          componentCall.paramsGenerator_ = paramsLambda;
                      }
                      else {
                          this.updateStateVarsOfChildByElmtId(elmtId, {});
                      }
                  }, { name: "ImageMenuItem" });
              }
          };
          this.forEachUpdateFunction(elmtId, this.menuItems.slice(j1.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction, undefined, true, false);
      }, ForEach);
      ForEach.pop();
      Column.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
j1.maxCountOfVisibleItems = 1;
j1.focusPadding = 4;
j1.marginsNum = 2;
class h2 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = { title: '' };
      this.index = 0;
      this.maxIndex = 0;
      this.onCustomClick = undefined;
      this.onImageComplete = undefined;
      this.l2 = new SynchedPropertySimpleOneWayPU(params.currentIndex, this, "currentIndex");
      this.b2 = new ObservedPropertySimplePU(false, this, "isOnFocus");
      this.c2 = new ObservedPropertySimplePU(false, this, "isOnHover");
      this.d2 = new ObservedPropertySimplePU(false, this, "isOnClick");
      this.j2 = new ObservedPropertySimplePU(0, this, "tabWidth");
      this.m2 = new ObservedPropertySimplePU(24, this, "imageWidth");
      this.n2 = new ObservedPropertySimplePU(24, this, "imageHeight");
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
      this.l2.reset(params.currentIndex);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.l2.purgeDependencyOnElmtId(rmElmtId);
      this.b2.purgeDependencyOnElmtId(rmElmtId);
      this.c2.purgeDependencyOnElmtId(rmElmtId);
      this.d2.purgeDependencyOnElmtId(rmElmtId);
      this.j2.purgeDependencyOnElmtId(rmElmtId);
      this.m2.purgeDependencyOnElmtId(rmElmtId);
      this.n2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.l2.aboutToBeDeleted();
      this.b2.aboutToBeDeleted();
      this.c2.aboutToBeDeleted();
      this.d2.aboutToBeDeleted();
      this.j2.aboutToBeDeleted();
      this.m2.aboutToBeDeleted();
      this.n2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get currentIndex() {
      return this.l2.get();
  }
  set currentIndex(newValue) {
      this.l2.set(newValue);
  }
  get isOnFocus() {
      return this.b2.get();
  }
  set isOnFocus(newValue) {
      this.b2.set(newValue);
  }
  get isOnHover() {
      return this.c2.get();
  }
  set isOnHover(newValue) {
      this.c2.set(newValue);
  }
  get isOnClick() {
      return this.d2.get();
  }
  set isOnClick(newValue) {
      this.d2.set(newValue);
  }
  get tabWidth() {
      return this.j2.get();
  }
  set tabWidth(newValue) {
      this.j2.set(newValue);
  }
  get imageWidth() {
      return this.m2.get();
  }
  set imageWidth(newValue) {
      this.m2.set(newValue);
  }
  get imageHeight() {
      return this.n2.get();
  }
  set imageHeight(newValue) {
      this.n2.set(newValue);
  }
  getBgColor() {
      if (this.isOnClick) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else if (this.isOnHover) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else {
          return Color.Transparent;
      }
  }
  getBorderAttr() {
      if (this.isOnFocus) {
          return {
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: h2.focusBorderWidth,
              color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              style: BorderStyle.Solid
          };
      }
      return { width: 0 };
  }
  getImageScaleFactor() {
      return this.index === this.currentIndex ? h2.imageMagnificationFactor : 1;
  }
  getImageLayoutWidth() {
      return h2.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth;
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Stack.create();
          Stack.margin({
              left: this.index === 0 ? h2.marginFirst : 0,
              right: this.index === this.maxIndex ? 12 : 0
          });
      }, Stack);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.height(TabTitleBar.totalHeight);
          Row.alignItems(VerticalAlign.Center);
          Row.justifyContent(FlexAlign.Center);
          Row.borderRadius(h2.buttonBorderRadius);
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
          if (this.item.icon === undefined && this.item.symbolIcon === undefined) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.item.title);
                      Context.animation({ duration: 300 });
                      Text.fontSize(this.index === this.currentIndex
                          ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline7'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline9'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.fontColor(this.index === this.currentIndex
                          ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text_off'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.fontWeight(FontWeight.Medium);
                      Text.focusable(true);
                      Context.animation(null);
                      Text.padding({
                          top: this.index === this.currentIndex ? 6 : 10,
                          left: h2.paddingLeft,
                          bottom: 2,
                          right: h2.paddingRight
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
                  }, Text);
                  Text.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Context.animation({ duration: 300 });
                      Row.width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
                          h2.paddingLeft + h2.paddingRight);
                      Row.constraintSize({
                          minWidth: h2.imageHotZoneWidth,
                          minHeight: h2.imageHotZoneWidth
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
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.item.symbolIcon) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  Context.animation({ duration: 300 });
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.item.symbolIcon);
                                  SymbolGlyph.fontSize(h2.symbolSize);
                                  SymbolGlyph.width(this.getImageLayoutWidth());
                                  SymbolGlyph.height(h2.imageSize);
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
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.item.icon);
                                  Context.animation({ duration: 300 });
                                  Image.alt(this.item.title);
                                  Image.width(this.getImageLayoutWidth());
                                  Image.height(h2.imageSize);
                                  Image.objectFit(ImageFit.Fill);
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
                                          h2.paddingLeft + h2.paddingRight);
                                  });
                                  Image.onError((event) => {
                                      if (!this.onImageComplete) {
                                          return;
                                      }
                                      this.onImageComplete(px2vp(event.componentWidth) +
                                          h2.paddingLeft + h2.paddingRight);
                                  });
                              }, Image);
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
                      Row.borderRadius(h2.buttonBorderRadius);
                      ViewStackProcessor.visualState("focused");
                      Row.border(this.getBorderAttr());
                      ViewStackProcessor.visualState("normal");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
h2.imageSize = 24;
h2.symbolSize = '24vp';
h2.imageHotZoneWidth = 48;
h2.imageMagnificationFactor = 1.4;
h2.buttonBorderRadius = 8;
h2.focusBorderWidth = 2;
h2.paddingLeft = 8;
h2.paddingRight = 8;
h2.marginFirst = 16;
class l1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = { value: '' };
      this.index = 0;
      this.b2 = new ObservedPropertySimplePU(false, this, "isOnFocus");
      this.c2 = new ObservedPropertySimplePU(false, this, "isOnHover");
      this.d2 = new ObservedPropertySimplePU(false, this, "isOnClick");
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
      if (params.isOnFocus !== undefined) {
          this.isOnFocus = params.isOnFocus;
      }
      if (params.isOnHover !== undefined) {
          this.isOnHover = params.isOnHover;
      }
      if (params.isOnClick !== undefined) {
          this.isOnClick = params.isOnClick;
      }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.b2.purgeDependencyOnElmtId(rmElmtId);
      this.c2.purgeDependencyOnElmtId(rmElmtId);
      this.d2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.b2.aboutToBeDeleted();
      this.c2.aboutToBeDeleted();
      this.d2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get isOnFocus() {
      return this.b2.get();
  }
  set isOnFocus(newValue) {
      this.b2.set(newValue);
  }
  get isOnHover() {
      return this.c2.get();
  }
  set isOnHover(newValue) {
      this.c2.set(newValue);
  }
  get isOnClick() {
      return this.d2.get();
  }
  set isOnClick(newValue) {
      this.d2.set(newValue);
  }
  getFgColor() {
      return this.isOnClick
          ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
  getBgColor() {
      if (this.isOnClick) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else if (this.isOnHover) {
          return { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else {
          return Color.Transparent;
      }
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.width(l1.imageHotZoneWidth);
          Row.height(l1.imageHotZoneWidth);
          Row.borderRadius(l1.buttonBorderRadius);
          Row.foregroundColor(this.getFgColor());
          Row.backgroundColor(this.getBgColor());
          Row.justifyContent(FlexAlign.Center);
          Row.opacity(this.item.isEnabled ? 1 : l1.disabledImageOpacity);
          ViewStackProcessor.visualState("focused");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: l1.focusBorderWidth,
              color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              style: BorderStyle.Solid
          });
          ViewStackProcessor.visualState("normal");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
          Row.onHover((isOn) => {
              if (!this.item.isEnabled) {
                  return;
              }
              this.isOnHover = isOn;
          });
          Row.onKeyEvent((event) => {
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
          Row.onTouch((event) => {
              if (!this.item.isEnabled) {
                  return;
              }
              if (event.type === TouchType.Down) {
                  this.isOnClick = true;
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  this.isOnClick = false;
              }
          });
          Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.item.n1) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create();
                      SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                      SymbolGlyph.attributeModifier.bind(this)(this.item.n1);
                      SymbolGlyph.fontSize(h2.symbolSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.focusable(this.item?.isEnabled);
                      SymbolGlyph.key(l1.focusablePrefix + this.index);
                  }, SymbolGlyph);
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Image.create(this.item.value);
          Image.width(l1.imageSize);
          Image.height(l1.imageSize);
          Image.focusable(this.item.isEnabled);
          Image.key(l1.focusablePrefix + this.index);
          Image.draggable(false);
      }, Image);
      Row.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
l1.imageSize = 24;
l1.imageHotZoneWidth = 48;
l1.buttonBorderRadius = 8;
l1.focusBorderWidth = 2;
l1.disabledImageOpacity = 0.4;
l1.focusablePrefix = "Id-TabTitleBar-ImageMenuItem-";
class i2 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
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
      this.e2 = this.createStorageLink('mainWindow', undefined, "mainWindow");
      this.u1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.f2 = new ObservedPropertySimplePU(1, this, "maxLines");
      this.g2 = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
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
      this.e2.purgeDependencyOnElmtId(rmElmtId);
      this.u1.purgeDependencyOnElmtId(rmElmtId);
      this.f2.purgeDependencyOnElmtId(rmElmtId);
      this.g2.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.e2.aboutToBeDeleted();
      this.u1.aboutToBeDeleted();
      this.f2.aboutToBeDeleted();
      this.g2.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  setController(ctr) {
      this.controller = ctr;
  }
  get mainWindow() {
      return this.e2.get();
  }
  set mainWindow(newValue) {
      this.e2.set(newValue);
  }
  get fontSize() {
      return this.u1.get();
  }
  set fontSize(newValue) {
      this.u1.set(newValue);
  }
  get maxLines() {
      return this.f2.get();
  }
  set maxLines(newValue) {
      this.f2.set(newValue);
  }
  get windowStandardHeight() {
      return this.g2.get();
  }
  set windowStandardHeight(newValue) {
      this.g2.set(newValue);
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.tabTitleBarDialog) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width(this.fontSize === this.maxFontSize ? h1 : i1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? h1 : i1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.tabTitleDialog.n1) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.n1);
                                  SymbolGlyph.fontSize(g1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                              }, SymbolGlyph);
                          });
                      }
                      else if (this.tabTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.tabTitleDialog.value);
                                  Image.width(g1);
                                  Image.height(g1);
                                  Image.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                              }, Image);
                          });
                      }
                      else {
                          this.ifElseBranchUpdateFunction(2, () => {
                          });
                      }
                  }, If);
                  If.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width('100%');
                      Column.padding({
                          left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                      });
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.tabTitleBarDialog);
                      Text.fontSize(f1);
                      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                      Text.maxLines(this.maxLines);
                      Text.width('100%');
                      Text.textAlign(TextAlign.Center);
                      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  }, Text);
                  Text.pop();
                  Column.pop();
                  Column.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width(this.fontSize === this.maxFontSize ? h1 : i1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? h1 : i1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Column.justifyContent(FlexAlign.Center);
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.tabTitleDialog.n1) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.tabTitleDialog.n1);
                                  SymbolGlyph.fontSize(g1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.tabTitleDialog?.isEnabled);
                              }, SymbolGlyph);
                          });
                      }
                      else {
                          this.ifElseBranchUpdateFunction(1, () => {
                          });
                      }
                  }, If);
                  If.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Image.create(this.tabTitleDialog.value);
                      Image.width(g1);
                      Image.height(g1);
                      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  }, Image);
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
      }
      else {
          this.maxLines = this.horizontalsScreenLines;
      }
  }
  rerender() {
      this.updateDirtyElements();
  }
}
export default {
TabTitleBar: TabTitleBar,
IconResource: IconResource,
};
