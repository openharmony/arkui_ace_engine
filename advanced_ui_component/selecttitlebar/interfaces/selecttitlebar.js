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
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const d1 = { "id": -1, "type": 40000, params: ['sys.symbol.dot_grid_2x2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const e1 = { "id": -1, "type": 40000, params: ['sys.symbol.arrow_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const f1 = '18.3fp';
const g1 = '64vp';
const h1 = '256vp';
const i1 = '216vp';
export class SelectTitleBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.s1 = new SynchedPropertySimpleOneWayPU(params.selected, this, "selected");
      this.options = [];
      this.menuItems = [];
      this.subtitle = '';
      this.badgeValue = 0;
      this.hidesBackButton = false;
      this.onSelected = () => { };
      this.t1 = new ObservedPropertySimplePU(0, this, "selectMaxWidth");
      this.u1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.setInitiallyProvidedValue(params);
      this.finalizeConstruction();
  }
  setInitiallyProvidedValue(params) {
      if (params.selected === undefined) {
          this.s1.set(0);
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
      this.s1.reset(params.selected);
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
      this.s1.purgeDependencyOnElmtId(rmElmtId);
      this.t1.purgeDependencyOnElmtId(rmElmtId);
      this.u1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.s1.aboutToBeDeleted();
      this.t1.aboutToBeDeleted();
      this.u1.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal();
  }
  get selected() {
      return this.s1.get();
  }
  set selected(newValue) {
      this.s1.set(newValue);
  }
  get selectMaxWidth() {
      return this.t1.get();
  }
  set selectMaxWidth(newValue) {
      this.t1.set(newValue);
  }
  get fontSize() {
      return this.u1.get();
  }
  set fontSize(newValue) {
      this.u1.set(newValue);
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
          Flex.onAreaChange((u1, newValue) => {
              let v1 = Number(newValue.width);
              if (!this.hidesBackButton) {
                  v1 -= l1.imageHotZoneWidth;
                  v1 += SelectTitleBar.leftPadding;
                  v1 -= SelectTitleBar.leftPaddingWithBack;
              }
              if (this.menuItems.length > 0) {
                  let w1 = this.menuItems.length;
                  if (w1 >= j1.maxCountOfVisibleItems) {
                      v1 -= l1.imageHotZoneWidth * j1.maxCountOfVisibleItems;
                  }
                  else if (w1 > 0) {
                      v1 -= l1.imageHotZoneWidth * w1;
                  }
              }
              if (this.badgeValue) {
                  this.selectMaxWidth = v1 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                      SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
              }
              else {
                  this.selectMaxWidth = v1 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
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
                              let componentCall = new l1(this, { item: {
                                      value: e1,
                                      n1: new SymbolGlyphModifier((e1)),
                                      isEnabled: true,
                                      action: () => this.getUIContext()?.getRouter()?.back()
                                  }, index: -1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 75, o1: 11 });
                              ViewPU.create(componentCall);
                              let paramsLambda = () => {
                                  return {
                                      item: {
                                          value: e1,
                                          n1: new SymbolGlyphModifier((e1)),
                                          isEnabled: true,
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
          if (this.menuItems.length > 0) {
              this.ifElseBranchUpdateFunction(0, () => {
                  {
                      this.observeComponentCreation2((elmtId, isInitialRender) => {
                          if (isInitialRender) {
                              let componentCall = new j1(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 150, o1: 9 });
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
class j1 extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
      super(parent, __localStorage, elmtId, extraInfo);
      if (typeof paramsLambda === "function") {
          this.paramsGenerator_ = paramsLambda;
      }
      this.menuItems = [];
      this.item = {
          value: d1,
          n1: new SymbolGlyphModifier(d1),
          label: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
      this.index = 0;
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
      this.u1 = new ObservedPropertySimplePU(1, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new m1(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  selectTitleDialog: this.item,
                  selectTitleBarDialog: this.item.label ? this.item.label : '',
                  fontSize: this.fontSize,
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 209, o1: 14 });
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
          let t1 = this.getUIContext();
          this.isFollowingSystemFontScale = t1.isFollowingSystemFontScale();
          this.maxFontScale = t1.getMaxFontScale();
      }
      catch (s1) {
          let code = s1.code;
          let message = s1.message;
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
      let q1 = this.getUIContext();
      this.systemFontScale = q1.getHostContext()?.config?.fontSizeScale ?? 1;
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
          if (this.menuItems.length <= j1.maxCountOfVisibleItems) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      ForEach.create();
                      const forEachItemGenFunction = (_item, index) => {
                          const item = _item;
                          {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  if (isInitialRender) {
                                      let componentCall = new l1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 271, o1: 13 });
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
                                      let componentCall = new l1(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 276, o1: 15 });
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
                      ViewStackProcessor.visualState("normal");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          width: 0
                      });
                      ViewStackProcessor.visualState("focused");
                      Row.border({
                          radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          width: l1.focusBorderWidth,
                          color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                          style: BorderStyle.Solid
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
                      SymbolGlyph.fontSize(l1.imageSize);
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
                                  j1.maxCountOfVisibleItems + index, isPopup: true }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 369, o1: 11 });
                          ViewPU.create(componentCall);
                          let paramsLambda = () => {
                              return {
                                  item: item,
                                  index: this.index * 1000 +
                                      j1.maxCountOfVisibleItems + index,
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
          this.forEachUpdateFunction(elmtId, this.menuItems.slice(j1.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction, undefined, true, false);
      }, ForEach);
      ForEach.pop();
      Column.pop();
  }
  rerender() {
      this.updateDirtyElements();
  }
}
j1.maxCountOfVisibleItems = 3;
j1.focusPadding = 4;
j1.marginsNum = 2;
class l1 extends ViewPU {
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
      this.b2 = new ObservedPropertySimplePU(false, this, "isOnFocus");
      this.c2 = new ObservedPropertySimplePU(false, this, "isOnHover");
      this.d2 = new ObservedPropertySimplePU(false, this, "isOnClick");
      this.u1 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, "fontSize");
      this.dialogController = new CustomDialogController({
          builder: () => {
              let jsDialog = new m1(this, {
                  cancel: () => {
                  },
                  confirm: () => {
                  },
                  selectTitleDialog: this.item,
                  selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                  fontSize: this.fontSize,
              }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/SelectTitleBar.ets", line: 405, o1: 14 });
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
      this.b2.purgeDependencyOnElmtId(rmElmtId);
      this.c2.purgeDependencyOnElmtId(rmElmtId);
      this.d2.purgeDependencyOnElmtId(rmElmtId);
      this.u1.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
      this.b2.aboutToBeDeleted();
      this.c2.aboutToBeDeleted();
      this.d2.aboutToBeDeleted();
      this.u1.aboutToBeDeleted();
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
  get fontSize() {
      return this.u1.get();
  }
  set fontSize(newValue) {
      this.u1.set(newValue);
  }
  textDialog() {
      if (this.item.value === d1) {
          return { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
      else if (this.item.value === e1) {
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
          let p1 = this.getUIContext();
          this.isFollowingSystemFontScale = p1.isFollowingSystemFontScale();
          this.maxFontScale = p1.getMaxFontScale();
      }
      catch (o1) {
          let code = o1.code;
          let message = o1.message;
          hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      }
  }
  decideFontScale() {
      let n1 = this.getUIContext();
      this.systemFontScale = n1.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
          return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
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
          Row.enabled(this.item.isEnabled);
          ViewStackProcessor.visualState("normal");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: 0
          });
          ViewStackProcessor.visualState("focused");
          Row.border({
              radius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: l1.focusBorderWidth,
              color: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              style: BorderStyle.Solid
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
          if (this.item.n1) {
              this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      SymbolGlyph.create();
                      SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                      SymbolGlyph.attributeModifier.bind(this)(this.item.n1);
                      SymbolGlyph.fontSize(l1.imageSize);
                      SymbolGlyph.draggable(false);
                      SymbolGlyph.focusable(this.item?.isEnabled);
                      SymbolGlyph.key(l1.focusablePrefix + this.index);
                  }, SymbolGlyph);
              });
          }
          else {
              this.ifElseBranchUpdateFunction(1, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                      Image.create(this.item.value);
                      Image.draggable(false);
                      Image.width(l1.imageSize);
                      Image.height(l1.imageSize);
                      Image.focusable(this.item.isEnabled);
                      Image.key(l1.focusablePrefix + this.index);
                      Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
l1.imageSize = '24vp';
l1.imageHotZoneWidth = 48;
l1.buttonBorderRadius = 8;
l1.focusBorderWidth = 2;
l1.disabledImageOpacity = 0.4;
l1.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
class m1 extends ViewPU {
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
          if (this.selectTitleBarDialog) {
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
                      if (this.selectTitleDialog.n1) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.n1);
                                  SymbolGlyph.fontSize(g1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.selectTitleDialog?.isEnabled);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                              }, SymbolGlyph);
                          });
                      }
                      else if (this.selectTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.selectTitleDialog.value);
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
                      Text.create(this.selectTitleBarDialog);
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
                      if (this.selectTitleDialog.n1) {
                          this.ifElseBranchUpdateFunction(0, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  SymbolGlyph.create();
                                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                  SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.n1);
                                  SymbolGlyph.fontSize(g1);
                                  SymbolGlyph.draggable(false);
                                  SymbolGlyph.focusable(this.selectTitleDialog?.isEnabled);
                                  SymbolGlyph.margin({
                                      top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                      bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                                  });
                              }, SymbolGlyph);
                          });
                      }
                      else if (this.selectTitleDialog.value) {
                          this.ifElseBranchUpdateFunction(1, () => {
                              this.observeComponentCreation2((elmtId, isInitialRender) => {
                                  Image.create(this.selectTitleDialog.value);
                                  Image.width(g1);
                                  Image.height(g1);
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
SelectTitleBar: SelectTitleBar,
IconResource: IconResource,
};
