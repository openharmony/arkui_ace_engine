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

const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const i = { "id": -1, "type": 40000, params: ['sys.symbol.arrow_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const j = { "id": -1, "type": 40000, params: ['sys.symbol.dot_grid_2x2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const m = '18.3fp';
const o = '64vp';
const t = '256vp';
const u = '216vp';
const a1 = '24vp';
class ComposeTitleBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = undefined;
      this.title = '';
      this.subtitle = '';
      this.menuItems = [];
      this.e1 = new ObservedPropertySimplePU(0, this, "titleMaxWidth");
      this.f1 = new ObservedPropertySimplePU(false, this, "backActive");
      this.g1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.title !== undefined) {
          this.title = params.title;
      }
      if (params.subtitle !== undefined) {
          this.subtitle = params.subtitle;
      }
      if (params.menuItems !== undefined) {
          this.menuItems = params.menuItems;
      }
      if (params.titleMaxWidth !== undefined) {
          this.titleMaxWidth = params.titleMaxWidth;
      }
      if (params.backActive !== undefined) {
          this.backActive = params.backActive;
      }
      if (params.fontSize !== undefined) {
          this.fontSize = params.fontSize;
      }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.e1.purgeDependencyOnElmtId(rmElmtId);
      this.f1.purgeDependencyOnElmtId(rmElmtId);
      this.g1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.e1.aboutToBeDeleted();
      this.f1.aboutToBeDeleted();
      this.g1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get titleMaxWidth() {
      return this.e1.get();
  }
  set titleMaxWidth(newValue) {
      this.e1.set(newValue);
  }
  get backActive() {
      return this.f1.get();
  }
  set backActive(newValue) {
      this.f1.set(newValue);
  }
  get fontSize() {
      return this.g1.get();
  }
  set fontSize(newValue) {
      this.g1.set(newValue);
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Flex.create({
              justifyContent: FlexAlign.SpaceBetween,
              alignItems: ItemAlign.Stretch
          });
          Flex.width('100%');
          Flex.height(ComposeTitleBar.totalHeight);
          Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
          Flex.onAreaChange((k1, newValue) => {
              let l1 = Number(newValue.width);
              if (this.menuItems !== undefined) {
                  let m1 = this.menuItems.length;
                  if (m1 >= b1.maxCountOfVisibleItems) {
                      l1 = l1 - c1.imageHotZoneWidth * b1.maxCountOfVisibleItems;
                  }
                  else if (m1 > 0) {
                      l1 = l1 - c1.imageHotZoneWidth * m1;
                  }
              }
              this.titleMaxWidth = l1;
              this.titleMaxWidth -= ComposeTitleBar.leftPadding;
              this.titleMaxWidth -= c1.imageHotZoneWidth;
              if (this.item !== undefined) {
                  this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                      ComposeTitleBar.portraitImageSize +
                      ComposeTitleBar.portraitImageRightPadding;
              }
              this.titleMaxWidth -= ComposeTitleBar.rightPadding;
          });
      }, Flex);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.margin({ left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Navigator.create();
          Navigator.active(this.backActive);
      }, Navigator);
      Navigator.pop();
      {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
              if (isInitialRender) {
                  let componentCall = new c1(this, { symbolItem: {
                          value: i,
                          symbolStyle: new SymbolGlyphModifier(i).fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]),
                          isEnabled: true,
                          action: () => this.backActive = true,
                      }, index: -1,
                      isLeftBackFlag: true,
                      isSymbol: true }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 56, h1: 9 });
                  ViewPU.create(componentCall);
                  let paramsLambda = () => {
                      return {
                          symbolItem: {
                              value: i,
                              symbolStyle: new SymbolGlyphModifier(i).fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]),
                              isEnabled: true,
                              action: () => this.backActive = true,
                          },
                          index: -1,
                          isLeftBackFlag: true,
                          isSymbol: true
                      };
                  };
                  componentCall.paramsGenerator_ = paramsLambda;
              }
              else {
                  this.updateStateVarsOfChildByElmtId(elmtId, {});
              }
          }, { name: "ImageMenuItem" });
      }
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.item !== undefined) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Image.create(this.item.value);
                      Image.width(ComposeTitleBar.portraitImageSize);
                      Image.height(ComposeTitleBar.portraitImageSize);
                      Image.margin({
                          left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                      });
                      Image.focusable(false);
                      Image.borderRadius((c1.buttonBorderRadius));
                  }, Image);
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.justifyContent(FlexAlign.Start);
          Column.alignItems(HorizontalAlign.Start);
          Column.constraintSize({ maxWidth: this.titleMaxWidth });
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.title !== undefined) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.justifyContent(FlexAlign.Start);
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.title);
                      Text.fontWeight(FontWeight.Medium);
                      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                      Text.constraintSize({ maxWidth: this.titleMaxWidth });
                  }, Text);
                  Text.pop();
                  Row.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.subtitle !== undefined) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.justifyContent(FlexAlign.Start);
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.subtitle);
                      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_over_line'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.maxLines(1);
                      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                      Text.constraintSize({ maxWidth: this.titleMaxWidth });
                  }, Text);
                  Text.pop();
                  Row.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      Column.pop();
      Row.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems !== undefined && this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.menuItems[0].symbolStyle !== undefined) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              {
                                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                                      if (isInitialRender) {
                                          let componentCall = new b1(this, {
                                              symbolMenuItems: this.menuItems,
                                              index: 1 + ComposeTitleBar.instanceCount++
                                          }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 112, h1: 11 });
                                          ViewPU.create(componentCall);
                                          let paramsLambda = () => {
                                              return {
                                                  symbolMenuItems: this.menuItems,
                                                  index: 1 + ComposeTitleBar.instanceCount++
                                              };
                                          };
                                          componentCall.paramsGenerator_ = paramsLambda;
                                      }
                                      else {
                                          this.updateStateVarsOfChildByElmtId(elmtId, {});
                                      }
                                  }, { name: "CollapsibleMenuSection" });
                              }
                          });
                      }
                      else {
                          this.ifElseBranchUpdateFunction(1, () => {
                              {
                                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                                      if (isInitialRender) {
                                          let componentCall = new b1(this, {
                                              menuItems: this.menuItems,
                                              index: 1 + ComposeTitleBar.instanceCount++
                                          }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 116, h1: 11 });
                                          ViewPU.create(componentCall);
                                          let paramsLambda = () => {
                                              return {
                                                  menuItems: this.menuItems,
                                                  index: 1 + ComposeTitleBar.instanceCount++
                                              };
                                          };
                                          componentCall.paramsGenerator_ = paramsLambda;
                                      }
                                      else {
                                          this.updateStateVarsOfChildByElmtId(elmtId, {});
                                      }
                                  }, { name: "CollapsibleMenuSection" });
                              }
                          });
                      }
                  }, If);
                  If.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      Flex.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class b1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.menuItems = [];
      this.symbolMenuItems = [];
      this.item = {
          value: j,
          label: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
      this.index = 0;
      this.longPressTime = 500;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.firstFocusableIndex = -1;
      this.i1 = new ObservedPropertySimplePU(false, this, "isPopupShown");
      this.j1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnFocus");
      this.l1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnHover");
      this.m1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnClick");
      this.g1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.n1 = new ObservedPropertySimplePU(-1, this, "publicMoreCounter");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new d1(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  itemComposeTitleDialog: this.item,
                  composeTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 179, h1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
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
      if (params.symbolMenuItems !== undefined) {
          this.symbolMenuItems = params.symbolMenuItems;
      }
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.index !== undefined) {
          this.index = params.index;
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
      if (params.fontSize !== undefined) {
          this.fontSize = params.fontSize;
      }
      if (params.publicMoreCounter !== undefined) {
          this.publicMoreCounter = params.publicMoreCounter;
      }
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.i1.purgeDependencyOnElmtId(rmElmtId);
      this.j1.purgeDependencyOnElmtId(rmElmtId);
      this.l1.purgeDependencyOnElmtId(rmElmtId);
      this.m1.purgeDependencyOnElmtId(rmElmtId);
      this.g1.purgeDependencyOnElmtId(rmElmtId);
      this.n1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.i1.aboutToBeDeleted();
      this.j1.aboutToBeDeleted();
      this.l1.aboutToBeDeleted();
      this.m1.aboutToBeDeleted();
      this.g1.aboutToBeDeleted();
      this.n1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get isPopupShown() {
      return this.i1.get();
  }
  set isPopupShown(newValue) {
      this.i1.set(newValue);
  }
  get isMoreIconOnFocus() {
      return this.j1.get();
  }
  set isMoreIconOnFocus(newValue) {
      this.j1.set(newValue);
  }
  get isMoreIconOnHover() {
      return this.l1.get();
  }
  set isMoreIconOnHover(newValue) {
      this.l1.set(newValue);
  }
  get isMoreIconOnClick() {
      return this.m1.get();
  }
  set isMoreIconOnClick(newValue) {
      this.m1.set(newValue);
  }
  get fontSize() {
      return this.g1.get();
  }
  set fontSize(newValue) {
      this.g1.set(newValue);
  }
  get publicMoreCounter() {
      return this.n1.get();
  }
  set publicMoreCounter(newValue) {
      this.n1.set(newValue);
  }
  getMoreIconFgColor() {
      return this.isMoreIconOnClick ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
          let j1 = this.getUIContext();
          this.isFollowingSystemFontScale = j1.isFollowingSystemFontScale();
          this.maxFontScale = j1.getMaxFontScale();
      }
      catch (err) {
          let code = err.code;
          let message = err.message;
          hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}');
      }
      if (this.menuItems) {
          this.menuItems.forEach((item, index) => {
              if (item.isEnabled && this.firstFocusableIndex == -1 &&
                  index > b1.maxCountOfVisibleItems - 2) {
                  this.firstFocusableIndex = this.index * 1000 + index + 1;
              }
          });
      }
  }
  decideFontScale() {
      try {
          let i1 = this.getUIContext();
          this.systemFontScale = i1.getHostContext()?.config?.fontSizeScale ?? 1;
          if (!this.isFollowingSystemFontScale) {
              return 1;
          }
          return Math.min(this.systemFontScale, this.maxFontScale);
      }
      catch (h1) {
          let code = h1.code;
          let message = h1.message;
          hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}');
          return 1;
      }
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Column.create();
          Column.height('100%');
          Column.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          Column.justifyContent(FlexAlign.Center);
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems != undefined && this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.menuItems.length <= b1.maxCountOfVisibleItems) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  ForEach.create();
                                  const forEachItemGenFunction = (_item, index) => {
                                      const item = _item;
                                      {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              if (isInitialRender) {
                                                  let componentCall = new c1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 251, h1: 15 });
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
                                                  let componentCall = new c1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 256, h1: 17 });
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
                                  this.forEachUpdateFunction(elmtId, this.menuItems.slice(0, b1.maxCountOfVisibleItems - 1), forEachItemGenFunction, undefined, true, false);
                              }, ForEach);
                              ForEach.pop();
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Row.create();
                                  Row.width(c1.imageHotZoneWidth);
                                  Row.height(c1.imageHotZoneWidth);
                                  Row.borderRadius(c1.buttonBorderRadius);
                                  Row.foregroundColor(this.getMoreIconFgColor());
                                  Row.backgroundColor(this.getMoreIconBgColor());
                                  Row.justifyContent(FlexAlign.Center);
                                  ViewStackProcessor.visualState("focused");
                                  Row.border({
                                      radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      width: c1.focusBorderWidth,
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
                                      if (!this.item?.isEnabled) {
                                          return;
                                      }
                                      if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                                          event.keyCode !== KeyCode.KEYCODE_SPACE) {
                                          return;
                                      }
                                      if (event.type == KeyType.Down) {
                                          this.isMoreIconOnClick = true;
                                      }
                                      if (event.type == KeyType.Up) {
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
                                  Row.onClick(() => {
                                      this.isPopupShown = true;
                                      this.publicMoreCounter += 1;
                                  });
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
                                  SymbolGlyph.create(j);
                                  SymbolGlyph.width(c1.imageSize);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.height(c1.imageSize);
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.focusable(true);
                                  SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter);
                              }, SymbolGlyph);
                              Row.pop();
                          });
                      }
                  }, If);
                  If.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.symbolMenuItems.length <= b1.maxCountOfVisibleItems) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  ForEach.create();
                                  const forEachItemGenFunction = (_item, index) => {
                                      const item = _item;
                                      {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              if (isInitialRender) {
                                                  let componentCall = new c1(this, { symbolItem: item, isSymbol: true, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 354, h1: 15 });
                                                  ViewPU.create(componentCall);
                                                  let paramsLambda = () => {
                                                      return {
                                                          symbolItem: item,
                                                          isSymbol: true,
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
                                  this.forEachUpdateFunction(elmtId, this.symbolMenuItems, forEachItemGenFunction, undefined, true, false);
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
                                                  let componentCall = new c1(this, { symbolItem: item, isSymbol: true, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 359, h1: 17 });
                                                  ViewPU.create(componentCall);
                                                  let paramsLambda = () => {
                                                      return {
                                                          symbolItem: item,
                                                          isSymbol: true,
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
                                  this.forEachUpdateFunction(elmtId, this.symbolMenuItems.slice(0, b1.maxCountOfVisibleItems - 1), forEachItemGenFunction, undefined, true, false);
                              }, ForEach);
                              ForEach.pop();
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Row.create();
                                  Row.width(c1.imageHotZoneWidth);
                                  Row.height(c1.imageHotZoneWidth);
                                  Row.borderRadius(c1.buttonBorderRadius);
                                  Row.foregroundColor(this.getMoreIconFgColor());
                                  Row.backgroundColor(this.getMoreIconBgColor());
                                  Row.justifyContent(FlexAlign.Center);
                                  ViewStackProcessor.visualState("focused");
                                  Row.border({
                                      radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      width: c1.focusBorderWidth,
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
                                      if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                                          event.keyCode !== KeyCode.KEYCODE_SPACE) {
                                          return;
                                      }
                                      if (event.type == KeyType.Down) {
                                          this.isMoreIconOnClick = true;
                                      }
                                      if (event.type == KeyType.Up) {
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
                                  Row.onClick(() => {
                                      this.isPopupShown = true;
                                      this.publicMoreCounter += 1;
                                  });
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
                                  SymbolGlyph.create(j);
                                  SymbolGlyph.width(c1.imageSize);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.height(c1.imageSize);
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.focusable(true);
                                  SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter);
                              }, SymbolGlyph);
                              Row.pop();
                          });
                      }
                  }, If);
                  If.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
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
          Column.width(c1.imageHotZoneWidth +
              b1.focusPadding * b1.marginsNum);
          Column.margin({ top: b1.focusPadding, bottom: b1.focusPadding });
          Column.onAppear(() => {
              focusControl.requestFocus(c1.focusablePrefix +
                  this.firstFocusableIndex);
          });
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new c1(this, { symbolItem: item, isSymbol: true, index: this.index * 1000 +
                                              b1.maxCountOfVisibleItems + index, isPopup: true }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 464, h1: 13 });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              symbolItem: item,
                                              isSymbol: true,
                                              index: this.index * 1000 +
                                                  b1.maxCountOfVisibleItems + index,
                                              isPopup: true
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
                      this.forEachUpdateFunction(elmtId, this.symbolMenuItems.slice(b1.maxCountOfVisibleItems - 1, this.symbolMenuItems.length), forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.menuItems != undefined && this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new c1(this, { item: item, isSymbol: true, index: this.index * 1000 +
                                              b1.maxCountOfVisibleItems + index, isPopup: true }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 473, h1: 13 });
                                      ViewPU.create(componentCall);
                                      let paramsLambda = () => {
                                          return {
                                              item: item,
                                              isSymbol: true,
                                              index: this.index * 1000 +
                                                  b1.maxCountOfVisibleItems + index,
                                              isPopup: true
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
                      this.forEachUpdateFunction(elmtId, this.menuItems.slice(b1.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
          }
      }, If);
      If.pop();
      Column.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
b1.maxCountOfVisibleItems = 3;
b1.focusPadding = 4;
b1.marginsNum = 2;
class c1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.isLeftBackFlag = false;
      this.item = {};
      this.symbolItem = {};
      this.index = 0;
      this.longPressTime = 500;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.isPopup = false;
      this.isSymbol = false;
      this.o1 = new ObservedPropertySimplePU(false, this, "isOnFocus");
      this.q1 = new ObservedPropertySimplePU(false, this, "isOnHover");
      this.s1 = new ObservedPropertySimplePU(false, this, "isOnClick");
      this.t1 = new ObservedPropertySimplePU(-1, this, "publicBackCounter");
      this.g1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new d1(this, {
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
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 520, h1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
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
      if (params.isLeftBackFlag !== undefined) {
          this.isLeftBackFlag = params.isLeftBackFlag;
      }
      if (params.item !== undefined) {
          this.item = params.item;
      }
      if (params.symbolItem !== undefined) {
          this.symbolItem = params.symbolItem;
      }
      if (params.index !== undefined) {
          this.index = params.index;
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
      if (params.isPopup !== undefined) {
          this.isPopup = params.isPopup;
      }
      if (params.isSymbol !== undefined) {
          this.isSymbol = params.isSymbol;
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
      if (params.publicBackCounter !== undefined) {
          this.publicBackCounter = params.publicBackCounter;
      }
      if (params.fontSize === undefined) {
          this.g1.set(1);
      }
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
  }
  updateStateVars(params) {
      this.g1.reset(params.fontSize);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.o1.purgeDependencyOnElmtId(rmElmtId);
      this.q1.purgeDependencyOnElmtId(rmElmtId);
      this.s1.purgeDependencyOnElmtId(rmElmtId);
      this.t1.purgeDependencyOnElmtId(rmElmtId);
      this.g1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.o1.aboutToBeDeleted();
      this.q1.aboutToBeDeleted();
      this.s1.aboutToBeDeleted();
      this.t1.aboutToBeDeleted();
      this.g1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get isOnFocus() {
      return this.o1.get();
  }
  set isOnFocus(newValue) {
      this.o1.set(newValue);
  }
  get isOnHover() {
      return this.q1.get();
  }
  set isOnHover(newValue) {
      this.q1.set(newValue);
  }
  get isOnClick() {
      return this.s1.get();
  }
  set isOnClick(newValue) {
      this.s1.set(newValue);
  }
  get publicBackCounter() {
      return this.t1.get();
  }
  set publicBackCounter(newValue) {
      this.t1.set(newValue);
  }
  get fontSize() {
      return this.g1.get();
  }
  set fontSize(newValue) {
      this.g1.set(newValue);
  }
  textDialog() {
      if (this.isSymbol) {
          if (this.symbolItem.value === i) {
              return { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
          }
          else if (this.symbolItem.value === j) {
              return { "id": -1, "type": 10003, params: ['sys.string.icon_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
          }
          else {
              return this.item.label ? this.item.label : '';
          }
      }
      else {
          return this.item.label ? this.item.label : '';
      }
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
  aboutToAppear() {
      try {
          let g1 = this.getUIContext();
          this.isFollowingSystemFontScale = g1.isFollowingSystemFontScale();
          this.maxFontScale = g1.getMaxFontScale();
      }
      catch (err) {
          let code = err.code;
          let message = err.message;
          hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}');
      }
  }
  decideFontScale() {
      try {
          let f1 = this.getUIContext();
          this.systemFontScale = f1.getHostContext()?.config?.fontSizeScale ?? 1;
          if (!this.isFollowingSystemFontScale) {
              return 1;
          }
          return Math.min(this.systemFontScale, this.maxFontScale);
      }
      catch (e1) {
          let code = e1.code;
          let message = e1.message;
          hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}');
          return 1;
      }
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.width(c1.imageHotZoneWidth);
          Row.height(c1.imageHotZoneWidth);
          Row.borderRadius(c1.buttonBorderRadius);
          Row.foregroundColor(this.getFgColor());
          Row.backgroundColor(this.getBgColor());
          Row.justifyContent(FlexAlign.Center);
          Row.opacity(this.item?.isEnabled ? 1 : c1.disabledImageOpacity);
          ViewStackProcessor.visualState("focused");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: c1.focusBorderWidth,
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
              if (!this.item?.isEnabled) {
                  return;
              }
              this.isOnFocus = true;
          });
          Row.onBlur(() => this.isOnFocus = false);
          Row.onHover((isOn) => {
              if (!this.item?.isEnabled) {
                  return;
              }
              this.isOnHover = isOn;
          });
          Row.onKeyEvent((event) => {
              if (!this.item?.isEnabled) {
                  return;
              }
              if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                  event.keyCode !== KeyCode.KEYCODE_SPACE) {
                  return;
              }
              if (event.type == KeyType.Down) {
                  this.isOnClick = true;
              }
              if (event.type == KeyType.Up) {
                  this.isOnClick = false;
              }
          });
          Row.onTouch((event) => {
              if (!this.item?.isEnabled) {
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
          Row.onClick(() => {
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
          Gesture.create(GesturePriority.Low);
          LongPressGesture.create({ repeat: false, duration: this.longPressTime });
          LongPressGesture.onAction((event) => {
              this.fontSize = this.decideFontScale();
              if (event) {
                  if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                      this.dialogController?.open();
                  }
              }
          });
          LongPressGesture.pop();
          Gesture.pop();
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.isSymbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create();
                      SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                      SymbolGlyph.attributeModifier.bind(this)(this.symbolItem.symbolStyle);
                      SymbolGlyph.fontSize(a1);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.focusable(this.symbolItem?.isEnabled);
                      SymbolGlyph.key(c1.focusablePrefix + this.index);
                      SymbolGlyph.symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicBackCounter);
                  }, SymbolGlyph);
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Image.create(this.item?.value);
                      Image.matchTextDirection(this.item?.value === i ? true : false);
                      Image.width(c1.imageSize);
                      Image.draggable(false);
                      Image.height(c1.imageSize);
                      Image.focusable(this.item?.isEnabled);
                      Image.key(c1.focusablePrefix + this.index);
                      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  }, Image);
              });
          }
      }, If);
      If.pop();
      Row.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
c1.imageSize = 24;
c1.imageHotZoneWidth = 48;
c1.buttonBorderRadius = 8;
c1.focusBorderWidth = 2;
c1.disabledImageOpacity = 0.4;
c1.focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-";
class d1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
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
      this.u1 = this.createStorageLink('mainWindow', undefined, "mainWindow");
      this.g1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.v1 = new ObservedPropertySimplePU(1, this, "maxLines");
      this.w1 = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
      this.cancel = () => {
      };
      this.confirm = () => {
      };
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
      if (params.itemComposeTitleDialog !== undefined) {
          this.itemComposeTitleDialog = params.itemComposeTitleDialog;
      }
      if (params.itemComposeTitleSymbolDialog !== undefined) {
          this.itemComposeTitleSymbolDialog = params.itemComposeTitleSymbolDialog;
      }
      if (params.isSymbol !== undefined) {
          this.isSymbol = params.isSymbol;
      }
      if (params.callbackId !== undefined) {
          this.callbackId = params.callbackId;
      }
      if (params.composeTitleBarDialog !== undefined) {
          this.composeTitleBarDialog = params.composeTitleBarDialog;
      }
      if (params.composeTitleBarSymbolDialog !== undefined) {
          this.composeTitleBarSymbolDialog = params.composeTitleBarSymbolDialog;
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
      this.u1.purgeDependencyOnElmtId(rmElmtId);
      this.g1.purgeDependencyOnElmtId(rmElmtId);
      this.v1.purgeDependencyOnElmtId(rmElmtId);
      this.w1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.u1.aboutToBeDeleted();
      this.g1.aboutToBeDeleted();
      this.v1.aboutToBeDeleted();
      this.w1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  setController(ctr) {
      this.controller = ctr;
  }
  get mainWindow() {
      return this.u1.get();
  }
  set mainWindow(newValue) {
      this.u1.set(newValue);
  }
  get fontSize() {
      return this.g1.get();
  }
  set fontSize(newValue) {
      this.g1.set(newValue);
  }
  get maxLines() {
      return this.v1.get();
  }
  set maxLines(newValue) {
      this.v1.set(newValue);
  }
  get windowStandardHeight() {
      return this.w1.get();
  }
  set windowStandardHeight(newValue) {
      this.w1.set(newValue);
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.isSymbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.composeTitleBarSymbolDialog) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Column.create();
                                  Column.width(this.fontSize === this.maxFontSize ? t : u);
                                  Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? t : u });
                                  Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                  Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                  Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleSymbolDialog.symbolStyle);
                                  SymbolGlyph.fontSize(o);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                                  });
                              }, SymbolGlyph);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Column.create();
                                  Column.width('100%');
                                  Column.padding({
                                      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                                  });
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Text.create(this.composeTitleBarSymbolDialog);
                                  Text.fontSize(m);
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
                                  Column.width(this.fontSize === this.maxFontSize ? t : u);
                                  Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? t : u });
                                  Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                  Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                  Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                  Column.justifyContent(FlexAlign.Center);
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleSymbolDialog.symbolStyle);
                                  SymbolGlyph.fontSize(o);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                                  });
                              }, SymbolGlyph);
                              Column.pop();
                          });
                      }
                  }, If);
                  If.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.composeTitleBarDialog) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Column.create();
                                  Column.width(this.fontSize === this.maxFontSize ? t : u);
                                  Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? t : u });
                                  Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                  Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                  Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.itemComposeTitleDialog.value);
                                  Image.width(o);
                                  Image.height(o);
                                  Image.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                                  });
                              }, Image);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Column.create();
                                  Column.width('100%');
                                  Column.padding({
                                      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                                  });
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Text.create(this.composeTitleBarSymbolDialog);
                                  Text.fontSize(m);
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
                                  Column.width(this.fontSize === this.maxFontSize ? t : u);
                                  Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? t : u });
                                  Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                                  Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                                  Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                  Column.justifyContent(FlexAlign.Center);
                              }, Column);
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.itemComposeTitleDialog.value);
                                  Image.width(o);
                                  Image.height(o);
                                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                              }, Image);
                              Column.pop();
                          });
                      }
                  }, If);
                  If.pop();
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
export { ComposeTitleBar };
