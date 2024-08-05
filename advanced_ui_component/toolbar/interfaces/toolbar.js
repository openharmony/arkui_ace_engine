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

const LengthMetrics = requireNapi('arkui.node').LengthMetrics;

const REFLECT_MAX_COUNT = 3;
const IMAGE_SIZE_WIDTH_HEIGHT = 24;
const TEXT_MIN_SIZE = 9;
const DISABLE_OPACITY = 0.4;
const TEXT_MAX_LINES = 2;
const TOOLBAR_LIST_LENGTH = 5;
const TOOLBAR_LIST_NORMORL = 4;
const ITEM_DISABLE_STATE = 2;
const ITEM_DISABLE_ACTIVATE = 3;

let __decorate = this && this.__decorate || function (e, t, o, r) {
  let s;
  let i = arguments.length;
  let a = i < REFLECT_MAX_COUNT ? t : null === r ? r = Object.getOwnPropertyDescriptor(t, o) : r;
  if ('object' === typeof Reflect && 'function' === typeof Reflect.decorate) {
    a = Reflect.decorate(e, t, o, r);
  } else {
    for (let n = e.length - 1; n >= 0; n--) {
      (s = e[n]) && (a = (i < REFLECT_MAX_COUNT ? s(a) : i > REFLECT_MAX_COUNT ? s(t, o, a) : s(t, o)) || a);
    }
  }
  return i > REFLECT_MAX_COUNT && a && Object.defineProperty(t, o, a), a;
};
export let ItemState;
(function (j3) {
  j3[j3['ENABLE'] = 1] = 'ENABLE';
  j3[j3['DISABLE'] = 2] = 'DISABLE';
  j3[j3['ACTIVATE'] = 3] = 'ACTIVATE';
})(ItemState || (ItemState = {}));

const PUBLIC_MORE = { id: -1, type: 20000, params: ['sys.media.ohos_ic_public_more'], bundleName: '', moduleName: '' };

let ToolBarOption = class ToolBarOption {
  constructor() {
    this.content = '';
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
  }
};

ToolBarOption = __decorate([
  Observed
], ToolBarOption);
export { ToolBarOption };
let ToolBarOptions = class ToolBarOptions extends Array {
};
ToolBarOptions = __decorate([
  Observed
], ToolBarOptions);
export { ToolBarOptions };

export class ToolBar extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
    super(parent, __localStorage, elmtId, extraInfo);
    if (typeof paramsLambda === 'function') {
      this.paramsGenerator_ = paramsLambda;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(params.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(params.activateIndex, this, 'activateIndex');
    this.__moreText = new SynchedPropertyObjectOneWayPU(params.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.toolBarItemBackground = [];
    this.__itemBackground = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      'bundleName': '',
      'moduleName': '',
    }, this, 'itemBackground');
    this.__iconPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_primary'],
      'bundleName': '',
      'moduleName': '',
    }, this, 'iconPrimaryColor');
    this.__iconActivePrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_emphasize'],
      'bundleName': '',
      'moduleName': '',
    }, this, 'iconActivePrimaryColor');
    this.__fontPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '',
      'moduleName': '',
    }, this, 'fontPrimaryColor');
    this.__fontActivatedPrimaryColor = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '',
      'moduleName': '',
    }, this, 'fontActivatedPrimaryColor');
    this.setInitiallyProvidedValue(params);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(params) {
    this.__toolBarList.set(params.toolBarList);
    if (params.controller !== undefined) {
      this.controller = params.controller;
    }
    if (params.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (params.moreText === undefined) {
      this.__moreText.set({
        'id': -1,
        'type': 10003,
        params: ['sys.string.ohos_toolbar_more'],
        'bundleName': '',
        'moduleName': '',
      });
    }
    if (params.menuContent !== undefined) {
      this.menuContent = params.menuContent;
    }
    if (params.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = params.toolBarItemBackground;
    }
    if (params.itemBackground !== undefined) {
      this.itemBackground = params.itemBackground;
    }
    if (params.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = params.iconPrimaryColor;
    }
    if (params.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = params.iconActivePrimaryColor;
    }
    if (params.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = params.fontPrimaryColor;
    }
    if (params.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = params.fontActivatedPrimaryColor;
    }
  }

  updateStateVars(params) {
    this.__toolBarList.set(params.toolBarList);
    this.__activateIndex.reset(params.activateIndex);
    this.__moreText.reset(params.moreText);
  }

  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__toolBarList.purgeDependencyOnElmtId(rmElmtId);
    this.__activateIndex.purgeDependencyOnElmtId(rmElmtId);
    this.__moreText.purgeDependencyOnElmtId(rmElmtId);
    this.__menuContent.purgeDependencyOnElmtId(rmElmtId);
    this.__itemBackground.purgeDependencyOnElmtId(rmElmtId);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(rmElmtId);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(rmElmtId);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(rmElmtId);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(rmElmtId);
  }

  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__moreText.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__itemBackground.aboutToBeDeleted();
    this.__iconPrimaryColor.aboutToBeDeleted();
    this.__iconActivePrimaryColor.aboutToBeDeleted();
    this.__fontPrimaryColor.aboutToBeDeleted();
    this.__fontActivatedPrimaryColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get toolBarList() {
    return this.__toolBarList.get();
  }

  get activateIndex() {
    return this.__activateIndex.get();
  }
  set activateIndex(newValue) {
    this.__activateIndex.set(newValue);
  }

  get moreText() {
    return this.__moreText.get();
  }

  set moreText(newValue) {
    this.__moreText.set(newValue);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(newValue) {
    this.__menuContent.set(newValue);
  }

  get itemBackground() {
    return this.__itemBackground.get();
  }

  set itemBackground(newValue) {
    this.__itemBackground.set(newValue);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(newValue) {
    this.__iconPrimaryColor.set(newValue);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }

  set iconActivePrimaryColor(newValue) {
    this.__iconActivePrimaryColor.set(newValue);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }

  set fontPrimaryColor(newValue) {
    this.__fontPrimaryColor.set(newValue);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }

  set fontActivatedPrimaryColor(newValue) {
    this.__fontActivatedPrimaryColor.set(newValue);
  }

  onWillApplyTheme(theme) {
    this.iconPrimaryColor = theme.colors.iconPrimary;
    this.iconActivePrimaryColor = theme.colors.iconEmphasize;
    this.fontPrimaryColor = theme.colors.fontPrimary;
    this.fontActivatedPrimaryColor = theme.colors.fontEmphasize;
  }

  MoreTabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.bindMenu(ObservedObject.GetRawObject(this.menuContent),
        { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Column.padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '' });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Image.create(PUBLIC_MORE);
      Image.width(24);
      Image.height(24);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.moreText);
      Text.fontColor(ObservedObject.GetRawObject(this.fontPrimaryColor));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '',
        'moduleName': '__harDefaultModuleName__' });
      Text.fontWeight(FontWeight.Medium);
    }, Text);
    Text.pop();
    Column.pop();
  }

  TabBuilder(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.focusable(!(this.toolBarList[index]?.state === 2));
      Column.focusOnTouch(!(this.toolBarList[index]?.state === 2));
      Column.padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) });
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        'bundleName': '',
        'moduleName': '__harDefaultModuleName__' });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onClick(() => {
        let toolbar = this.toolBarList[index];
        if (toolbar.state === ItemState.ACTIVATE) {
          if (this.activateIndex === index) {
            this.activateIndex = -1;
          }
          else {
            this.activateIndex = index;
          }
        }
        if (!(toolbar.state === ItemState.DISABLE)) {
          toolbar.action && toolbar.action();
        }
      });
      Column.onHover((isHover) => {
        if (isHover) {
          this.toolBarItemBackground[index] = (this.toolBarList[index]?.state === ItemState.DISABLE) ? {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_toolbar_bg'],
            'bundleName': '',
            'moduleName': '' } : { 'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '',
            'moduleName': '' };
        }
        else {
          this.toolBarItemBackground[index] = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_toolbar_bg'],
            'bundleName': '',
            'moduleName': '' };
        }
        this.itemBackground = this.toolBarItemBackground[index];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((this.toolBarList[index]?.state === ItemState.DISABLE) ?
      this.toolBarItemBackground[index] : {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '',
          'moduleName': '' });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[index]);
      ViewStackProcessor.visualState();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Image.create(this.toolBarList[index]?.icon);
      Image.width(24);
      Image.height(24);
      Image.fillColor(this.activateIndex === index && !(this.toolBarList[index]?.state === 2)
        ? this.iconActivePrimaryColor : this.iconPrimaryColor);
      Image.opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1);
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Text.create(this.toolBarList[index]?.content);
      Text.fontColor(this.activateIndex === index && !(this.toolBarList[index]?.state === 2)
        ? this.fontActivatedPrimaryColor : this.fontPrimaryColor);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '',
        'moduleName': '' });
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        'bundleName': '', 'moduleName': '' });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1);
    }, Text);
    Text.pop();
    Column.pop();
  }

  refreshData() {
    this.menuContent = [];
    for (let i = 0; i < this.toolBarList.length; i++) {
      if (i >= 4 && this.toolBarList.length > 5) {
        this.menuContent[i - 4] = {
          value: this.toolBarList[i].content,
          action: this.toolBarList[i].action,
          enabled: this.toolBarList[i].state !== ItemState.DISABLE,
        };
      }
      else {
        this.toolBarItemBackground[i] = {
          'id': -1,
          'type': 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          'bundleName': '',
          'moduleName': '' };
        this.menuContent = [];
      }
    }
    return true;
  }

  aboutToAppear() {
    this.refreshData();
  }

  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
    }, Divider);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Tabs.create({ barPosition: BarPosition.End, controller: this.controller });
      Tabs.vertical(false);
      Tabs.constraintSize({ minHeight: 56, maxHeight: 56 });
      Tabs.barMode(BarMode.Fixed);
      Tabs.onChange((index) => {
      });
      Tabs.width('100%');
      Tabs.padding({
        start: LengthMetrics.vp(this.toolBarList.length < 5 ? 24 : 0),
        end: LengthMetrics.vp(this.toolBarList.length < 5 ? 24 : 0)
      });
      Tabs.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_toolbar_bg'],
        'bundleName': '',
        'moduleName': '' });
    }, Tabs);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const item = _item;
        this.observeComponentCreation2((elmtId, isInitialRender) => {
          If.create();
          if (this.toolBarList.length <= 5) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, index);
                } });
                TabContent.enabled(!(this.toolBarList[index]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[index]?.state === 2));
              }, TabContent);
              TabContent.pop();
            });
          }
          else if (index < 4) {
            this.ifElseBranchUpdateFunction(1, () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, index);
                } });
                TabContent.enabled(!(this.toolBarList[index]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[index]?.state === 2));
              }, TabContent);
              TabContent.pop();
            });
          }
          else {
            this.ifElseBranchUpdateFunction(2, () => {
            });
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(elmtId, this.toolBarList, forEachItemGenFunction, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > 5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            TabContent.create();
            TabContent.tabBar({ builder: () => {
              this.MoreTabBuilder.call(this, 4);
            } });
          }, TabContent);
          TabContent.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Tabs.pop();
    Column.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
export default { ToolBarOptions, ToolBar, ItemState, ToolBarOption };