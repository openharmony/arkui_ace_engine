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
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const m = { "id": -1, "type": 40000, params: ['sys.symbol.arrow_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const o = { "id": -1, "type": 40000, params: ['sys.symbol.dot_grid_2x2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const t = 40000;
const u = '18.3fp';
const a1 = '64vp';
const b1 = '256vp';
const c1 = '216vp';
export class SelectTitleBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.g1 = new SynchedPropertySimpleOneWayPU(params.selected, this, "selected");
      this.options = [];
      this.menuItems = [];
      this.subtitle = '';
      this.badgeValue = 0;
      this.hidesBackButton = false;
      this.onSelected = () => { };
      this.h1 = new ObservedPropertySimplePU(0, this, "selectMaxWidth");
      this.i1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
      if (params.selected === undefined) {
          this.g1.set(0);
      }
      if (params.options !== undefined) {
          this.options = params.options;
      }
      if (params.menuItems !== undefined) {
          this.menuItems = params.menuItems;
      }
      if (params.subtitle !== undefined) {
          this.subtitle = params.subtitle;
      }
      if (params.badgeValue !== undefined) {
          this.badgeValue = params.badgeValue;
      }
      if (params.hidesBackButton !== undefined) {
          this.hidesBackButton = params.hidesBackButton;
      }
      if (params.onSelected !== undefined) {
          this.onSelected = params.onSelected;
      }
      if (params.selectMaxWidth !== undefined) {
          this.selectMaxWidth = params.selectMaxWidth;
      }
      if (params.fontSize !== undefined) {
          this.fontSize = params.fontSize;
      }
  }
  updateStateVars(params) {
      this.g1.reset(params.selected);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.g1.purgeDependencyOnElmtId(rmElmtId);
      this.h1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.g1.aboutToBeDeleted();
      this.h1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get selected() {
      return this.g1.get();
  }
  set selected(newValue) {
      this.g1.set(newValue);
  }
  get selectMaxWidth() {
      return this.h1.get();
  }
  set selectMaxWidth(newValue) {
      this.h1.set(newValue);
  }
  get fontSize() {
      return this.i1.get();
  }
  set fontSize(newValue) {
      this.i1.set(newValue);
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Flex.create({
              justifyContent: FlexAlign.SpaceBetween,
              alignItems: ItemAlign.Stretch
          });
          Flex.width('100%');
          Flex.height(SelectTitleBar.totalHeight);
          Flex.backgroundColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
          Flex.onAreaChange((n1, newValue) => {
              let o1 = Number(newValue.width);
              if (!this.hidesBackButton) {
                  o1 -= e1.imageHotZoneWidth;
                  o1 += SelectTitleBar.leftPadding;
                  o1 -= SelectTitleBar.leftPaddingWithBack;
              }
              if (this.menuItems !== undefined) {
                  let p1 = this.menuItems.length;
                  if (p1 >= d1.maxCountOfVisibleItems) {
                      o1 -= e1.imageHotZoneWidth * d1.maxCountOfVisibleItems;
                  }
                  else if (p1 > 0) {
                      o1 -= e1.imageHotZoneWidth * p1;
                  }
              }
              if (this.badgeValue) {
                  this.selectMaxWidth = o1 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                      SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
              }
              else {
                  this.selectMaxWidth = o1 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
              }
          });
      }, Flex);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.margin({ left: this.hidesBackButton ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.ohos_id_default_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
      }, Row);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (!this.hidesBackButton) {
              this.ifElseBranchUpdateFunction(0, () => {
                  {
                      this.observeComponentCreation2((elmtId, isInitialRender) => {
                          if (isInitialRender) {
                              let componentCall = new e1(this, { item: {
                                      value: '',
                                      symbolStyle: new SymbolGlyphModifier(m),
                                      isEnabled: true,
                                      label: { "id": -1, "type": 10003, params: ['sys.string.icon_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      action: () => this.getUIContext()?.getRouter()?.back()
                                  }, index: -1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 73, j1: 11 });
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                  return {
                                      item: {
                                          value: '',
                                          symbolStyle: new SymbolGlyphModifier(m),
                                          isEnabled: true,
                                          label: { "id": -1, "type": 10003, params: ['sys.string.icon_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                          action: () => this.getUIContext()?.getRouter()?.back()
                                      },
                                      index: -1
                                  };
                              };
                              componentCall.paramsGenerator_ = paramsLambda;
                          }
                          else {
                              this.updateStateVarsOfChildByElmtId(elmtId, {});
                          }
                      }, { name: "ImageMenuItem" });
                  }
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
          Column.constraintSize({ maxWidth: this.selectMaxWidth });
      }, Column);
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.badgeValue) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Badge.create({
                          count: this.badgeValue,
                          position: BadgePosition.Right,
                          style: {
                              badgeColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                              borderColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                              borderWidth: 0
                          }
                      });
                  }, Badge);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.justifyContent(FlexAlign.Start);
                      Row.margin({ right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Select.create(this.options);
                      Select.selected(this.selected);
                      Select.value(this.selected >= 0 && this.selected < this.options.length ?
                          this.options[this.selected].value : '');
                      Select.font({ size: this.hidesBackButton && !this.subtitle
                              ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline7'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                      Select.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Select.backgroundColor(Color.Transparent);
                      Select.onSelect(this.onSelected);
                      Select.constraintSize({ maxWidth: this.selectMaxWidth });
                      Select.offset({ x: -4 });
                  }, Select);
                  Select.pop();
                  Row.pop();
                  Badge.pop();
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.justifyContent(FlexAlign.Start);
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Select.create(this.options);
                      Select.selected(this.selected);
                      Select.value(this.selected >= 0 && this.selected < this.options.length ?
                          this.options[this.selected].value : '');
                      Select.font({ size: this.hidesBackButton && !this.subtitle
                              ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline7'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_headline8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                      Select.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Select.backgroundColor(Color.Transparent);
                      Select.onSelect(this.onSelected);
                      Select.constraintSize({ maxWidth: this.selectMaxWidth });
                      Select.offset({ x: -4 });
                  }, Select);
                  Select.pop();
                  Row.pop();
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
                      Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
                  }, Row);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Text.create(this.subtitle);
                      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_over_line'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Text.maxLines(1);
                      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                      Text.constraintSize({ maxWidth: this.selectMaxWidth });
                      Text.offset({ y: -4 });
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
                  {
                      this.observeComponentCreation2((elmtId, isInitialRender) => {
                          if (isInitialRender) {
                              let componentCall = new d1(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 149, j1: 9 });
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                  return {
                                      menuItems: this.menuItems,
                                      index: 1 + SelectTitleBar.instanceCount++
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
SelectTitleBar.badgeSize = 16;
SelectTitleBar.totalHeight = 56;
SelectTitleBar.leftPadding = 24;
SelectTitleBar.leftPaddingWithBack = 12;
SelectTitleBar.rightPadding = 24;
SelectTitleBar.badgePadding = 16;
SelectTitleBar.subtitleLeftPadding = 4;
SelectTitleBar.instanceCount = 0;
class d1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.menuItems = [];
      this.item = {
          symbolStyle: new SymbolGlyphModifier(o),
          label: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
      this.index = 0;
      this.longPressTime = 500;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.firstFocusableIndex = -1;
      this.l1 = new ObservedPropertySimplePU(false, this, "isPopupShown");
      this.m1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnFocus");
      this.n1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnHover");
      this.o1 = new ObservedPropertySimplePU(false, this, "isMoreIconOnClick");
      this.i1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new f1(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  selectTitleDialog: this.item,
                  selectTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize,
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 207, j1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
                  return {
                      cancel: () => {
                      },
                      confirm: () => {
                      },
                      selectTitleDialog: this.item,
                      selectTitleBarDialog: this.item.label ? this.item.label : '',
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
      if (params.dialogController !== undefined) {
          this.dialogController = params.dialogController;
      }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.l1.purgeDependencyOnElmtId(rmElmtId);
      this.m1.purgeDependencyOnElmtId(rmElmtId);
      this.n1.purgeDependencyOnElmtId(rmElmtId);
      this.o1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.l1.aboutToBeDeleted();
      this.m1.aboutToBeDeleted();
      this.n1.aboutToBeDeleted();
      this.o1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
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
          let m1 = this.getUIContext();
          this.isFollowingSystemFontScale = m1.isFollowingSystemFontScale();
          this.maxFontScale = m1.getMaxFontScale();
      }
      catch (l1) {
          let code = l1.code;
          let message = l1.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      }
      this.menuItems.forEach((item, index) => {
          if (item.isEnabled && this.firstFocusableIndex === -1 &&
              index > d1.maxCountOfVisibleItems - 2) {
              this.firstFocusableIndex = this.index * 1000 + index + 1;
          }
      });
  }
  decideFontScale() {
      let k1 = this.getUIContext();
      this.systemFontScale = k1.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
          return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
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
          if (this.menuItems.length <= d1.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new e1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 269, j1: 13 });
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
                                      let componentCall = new e1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 274, j1: 15 });
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
                      this.forEachUpdateFunction(elmtId, this.menuItems.slice(0, d1.maxCountOfVisibleItems - 1), forEachItemGenFunction, undefined, true, false);
                  }, ForEach);
                  ForEach.pop();
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Row.create();
                      Row.width(e1.imageHotZoneWidth);
                      Row.height(e1.imageHotZoneWidth);
                      Row.borderRadius(e1.buttonBorderRadius);
                      Row.foregroundColor(this.getMoreIconFgColor());
                      Row.backgroundColor(this.getMoreIconBgColor());
                      Row.justifyContent(FlexAlign.Center);
                      ViewStackProcessor.visualState("focused");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          width: e1.focusBorderWidth,
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
                      SymbolGlyph.create(o);
                      SymbolGlyph.fontSize(e1.imageSize);
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
                          let componentCall = new e1(this, { item: item, index: this.index * 1000 +
                                  d1.maxCountOfVisibleItems + index, isPopup: true }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 367, j1: 11 });
                          ViewPU.create(componentCall);
                          let paramsLambda = () => {
                              return {
                                  item: item,
                                  index: this.index * 1000 +
                                      d1.maxCountOfVisibleItems + index,
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
          this.forEachUpdateFunction(elmtId, this.menuItems.slice(d1.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction, undefined, true, false);
      }, ForEach);
      ForEach.pop();
      Column.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
d1.maxCountOfVisibleItems = 3;
d1.focusPadding = 4;
d1.marginsNum = 2;
class e1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.item = {};
      this.index = 0;
      this.longPressTime = 500;
      this.minFontSize = 1.75;
      this.isFollowingSystemFontScale = false;
      this.maxFontScale = 1;
      this.systemFontScale = 1;
      this.isPopup = false;
      this.q1 = new ObservedPropertySimplePU(false, this, "isOnFocus");
      this.s1 = new ObservedPropertySimplePU(false, this, "isOnHover");
      this.t1 = new ObservedPropertySimplePU(false, this, "isOnClick");
      this.i1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new f1(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  selectTitleDialog: this.item,
                  selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                  fontSize: this.fontSize,
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 403, j1: 14 });
              jsDialog.setController(this.dialogController);
              ViewPU.create(jsDialog);
              let paramsLambda = () => {
                  return {
                      cancel: () => {
                      },
                      confirm: () => {
                      },
                      selectTitleDialog: this.item,
                      selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
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
  }
  updateStateVars(params) {
      this.i1.reset(params.fontSize);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.q1.purgeDependencyOnElmtId(rmElmtId);
      this.s1.purgeDependencyOnElmtId(rmElmtId);
      this.t1.purgeDependencyOnElmtId(rmElmtId);
      this.i1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.q1.aboutToBeDeleted();
      this.s1.aboutToBeDeleted();
      this.t1.aboutToBeDeleted();
      this.i1.aboutToBeDeleted();
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
  textDialog() {
      if (this.item.value === o) {
          return { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else if (this.item.value === m) {
          return { "id": -1, "type": 10003, params: ['sys.string.icon_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
          let j1 = this.getUIContext();
          this.isFollowingSystemFontScale = j1.isFollowingSystemFontScale();
          this.maxFontScale = j1.getMaxFontScale();
      }
      catch (i1) {
          let code = i1.code;
          let message = i1.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      }
  }
  decideFontScale() {
      let h1 = this.getUIContext();
      this.systemFontScale = h1.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
          return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
  }
  initialRender() {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
          Row.create();
          Row.width(e1.imageHotZoneWidth);
          Row.height(e1.imageHotZoneWidth);
          Row.borderRadius(e1.buttonBorderRadius);
          Row.foregroundColor(this.getFgColor());
          Row.backgroundColor(this.getBgColor());
          Row.justifyContent(FlexAlign.Center);
          Row.opacity(this.item.isEnabled ? 1 : e1.disabledImageOpacity);
          Row.enabled(this.item.isEnabled);
          ViewStackProcessor.visualState("focused");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: e1.focusBorderWidth,
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
                  if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                      this.dialogController?.close();
                  }
              }
          });
          Row.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
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
          if (this.item.symbolStyle) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create();
                      SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                      SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                      SymbolGlyph.fontSize(e1.imageSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.focusable(this.item?.isEnabled);
                      SymbolGlyph.key(e1.focusablePrefix + this.index);
                      SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  }, SymbolGlyph);
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (Util.u1(this.item.value)) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create(this.item.value);
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.fontSize(e1.imageSize);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.item?.isEnabled);
                                  SymbolGlyph.key(e1.focusablePrefix + this.index);
                              }, SymbolGlyph);
                          });
                      }
                      else {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.item.value);
                                  Image.draggable(false);
                                  Image.width(e1.imageSize);
                                  Image.height(e1.imageSize);
                                  Image.focusable(this.item.isEnabled);
                                  Image.key(e1.focusablePrefix + this.index);
                                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
  }
  rerender() {
      this.updateDirtyElements();
  }
}
e1.imageSize = '24vp';
e1.imageHotZoneWidth = 48;
e1.buttonBorderRadius = 8;
e1.focusBorderWidth = 2;
e1.disabledImageOpacity = 0.4;
e1.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
class f1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.selectTitleDialog = {};
      this.callbackId = undefined;
      this.selectTitleBarDialog = '';
      this.mainWindowStage = undefined;
      this.controller = undefined;
      this.minFontSize = 1.75;
      this.maxFontSize = 3.2;
      this.screenWidth = 640;
      this.verticalScreenLines = 6;
      this.horizontalsScreenLines = 1;
      this.v1 = this.createStorageLink('mainWindow', undefined, "mainWindow");
      this.i1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.w1 = new ObservedPropertySimplePU(1, this, "maxLines");
      this.z1 = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
      this.cancel = () => {
      };
      this.confirm = () => {
      };
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
      if (params.selectTitleDialog !== undefined) {
          this.selectTitleDialog = params.selectTitleDialog;
      }
      if (params.callbackId !== undefined) {
          this.callbackId = params.callbackId;
      }
      if (params.selectTitleBarDialog !== undefined) {
          this.selectTitleBarDialog = params.selectTitleBarDialog;
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
          if (this.selectTitleBarDialog) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Column.create();
                      Column.width(this.fontSize === this.maxFontSize ? b1 : c1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? b1 : c1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.selectTitleDialog.symbolStyle) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolStyle);
                                  SymbolGlyph.fontSize(a1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                              }, SymbolGlyph);
                          });
                      }
                      else if (this.selectTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  If.create();
                                  if (Util.u1(this.selectTitleDialog.value)) {
                                      this.ifElseBranchUpdateFunction(0, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              SymbolGlyph.create(this.selectTitleDialog.value);
                                              SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                              SymbolGlyph.fontSize(a1);
                                              SymbolGlyph.draggable(false);
                                              SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                              SymbolGlyph.margin({
                                                  top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                                  bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                              });
                                          }, SymbolGlyph);
                                      });
                                  }
                                  else {
                                      this.ifElseBranchUpdateFunction(1, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              Image.create(this.selectTitleDialog.value);
                                              Image.width(a1);
                                              Image.height(a1);
                                              Image.margin({
                                                  top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                                  bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                              });
                                              Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
                      Text.create(this.selectTitleBarDialog);
                      Text.fontSize(u);
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
                      Column.width(this.fontSize === this.maxFontSize ? b1 : c1);
                      Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? b1 : c1 });
                      Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                      Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                      Column.justifyContent(FlexAlign.Center);
                  }, Column);
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (this.selectTitleDialog.symbolStyle) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolStyle);
                                  SymbolGlyph.fontSize(a1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                              }, SymbolGlyph);
                          });
                      }
                      else if (this.selectTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  If.create();
                                  if (Util.u1(this.selectTitleDialog.value)) {
                                      this.ifElseBranchUpdateFunction(0, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              SymbolGlyph.create(this.selectTitleDialog.value);
                                              SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                              SymbolGlyph.fontSize(a1);
                                              SymbolGlyph.draggable(false);
                                              SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                              SymbolGlyph.margin({
                                                  top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                                  bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                              });
                                          }, SymbolGlyph);
                                      });
                                  }
                                  else {
                                      this.ifElseBranchUpdateFunction(1, () => {
                                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                                              Image.create(this.selectTitleDialog.value);
                                              Image.width(a1);
                                              Image.height(a1);
                                              Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
class Util {
  static u1(g1) {
      if (!Util.a2(g1)) {
          return false;
      }
      let resource = g1;
      return resource.type == t;
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
  SelectTitleBar: SelectTitleBar,
};
