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
  constructor(d3, e3, f3, g3 = -1, h3 = undefined, i3) {
    super(d3, f3, g3, i3);
    if (typeof h3 === 'function') {
      this.paramsGenerator_ = h3;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(e3.toolBarList, this, 'toolBarList');
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(e3.activateIndex, this, 'activateIndex');
    this.__moreText = new SynchedPropertySimpleOneWayPU(e3.moreText, this, 'moreText');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.toolBarItemBackground = [];
    this.__itemBackground = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      bundleName: '',
      moduleName: '',
    }, this, 'itemBackground');
    this.__iconPrimaryColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.icon_primary'],
      bundleName: '',
      moduleName: '',
    }, this, 'iconPrimaryColor');
    this.__iconActivePrimaryColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.icon_emphasize'],
      bundleName: '',
      moduleName: '',
    }, this, 'iconActivePrimaryColor');
    this.__fontPrimaryColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.font_primary'],
      bundleName: '',
      moduleName: '',
    }, this, 'fontPrimaryColor');
    this.__fontActivatedPrimaryColor = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.font_emphasize'],
      bundleName: '',
      moduleName: '',
    }, this, 'fontActivatedPrimaryColor');
    this.setInitiallyProvidedValue(e3);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(c3) {
    this.__toolBarList.set(c3.toolBarList);
    if (c3.controller !== undefined) {
      this.controller = c3.controller;
    }
    if (c3.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (c3.moreText === undefined) {
      this.__moreText.set('更多');
    }
    if (c3.menuContent !== undefined) {
      this.menuContent = c3.menuContent;
    }
    if (c3.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = c3.toolBarItemBackground;
    }
    if (c3.itemBackground !== undefined) {
      this.itemBackground = c3.itemBackground;
    }
    if (c3.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = c3.iconPrimaryColor;
    }
    if (c3.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = c3.iconActivePrimaryColor;
    }
    if (c3.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = c3.fontPrimaryColor;
    }
    if (c3.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = c3.fontActivatedPrimaryColor;
    }
  }

  updateStateVars(b3) {
    this.__toolBarList.set(b3.toolBarList);
    this.__activateIndex.reset(b3.activateIndex);
    this.__moreText.reset(b3.moreText);
  }

  purgeVariableDependenciesOnElmtId(a3) {
    this.__toolBarList.purgeDependencyOnElmtId(a3);
    this.__activateIndex.purgeDependencyOnElmtId(a3);
    this.__moreText.purgeDependencyOnElmtId(a3);
    this.__menuContent.purgeDependencyOnElmtId(a3);
    this.__itemBackground.purgeDependencyOnElmtId(a3);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(a3);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(a3);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(a3);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(a3);
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

  set activateIndex(z2) {
    this.__activateIndex.set(z2);
  }

  get moreText() {
    return this.__moreText.get();
  }

  set moreText(y2) {
    this.__moreText.set(y2);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(x2) {
    this.__menuContent.set(x2);
  }

  get itemBackground() {
    return this.__itemBackground.get();
  }

  set itemBackground(w2) {
    this.__itemBackground.set(w2);
  }

  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }

  set iconPrimaryColor(v2) {
    this.__iconPrimaryColor.set(v2);
  }

  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }

  set iconActivePrimaryColor(u2) {
    this.__iconActivePrimaryColor.set(u2);
  }

  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }

  set fontPrimaryColor(t2) {
    this.__fontPrimaryColor.set(t2);
  }

  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }

  set fontActivatedPrimaryColor(s2) {
    this.__fontActivatedPrimaryColor.set(s2);
  }

  onWillApplyTheme(r2) {
    this.iconPrimaryColor = r2.colors.iconPrimary;
    this.iconActivePrimaryColor = r2.colors.iconEmphasize;
    this.fontPrimaryColor = r2.colors.fontPrimary;
    this.fontActivatedPrimaryColor = r2.colors.fontEmphasize;
  }

  MoreTabBuilder(g2, h2 = null) {
    this.observeComponentCreation2((p2, q2) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.padding({ left: 4, right: 4 });
      Column.borderRadius({ id: -1, type: 10002, params: ['sys.float.ohos_id_corner_radius_clicked'],
        bundleName: '', moduleName: '' });
    }, Column);
    this.observeComponentCreation2((n2, o2) => {
      Image.create(PUBLIC_MORE);
      Image.width(24);
      Image.height(24);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      Image.bindMenu(ObservedObject.GetRawObject(this.menuContent), { offset: { x: 5, y: -10 } });
    }, Image);
    this.observeComponentCreation2((l2, m2) => {
      Text.create(this.moreText);
      Text.fontColor(ObservedObject.GetRawObject(this.fontPrimaryColor));
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Medium);
    }, Text);
    Text.pop();
    Column.pop();
  }

  TabBuilder(r1, s1 = null) {
    this.observeComponentCreation2((a2, b2) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.focusable(!(this.toolBarList[r1]?.state === 2));
      Column.focusOnTouch(!(this.toolBarList[r1]?.state === 2));
      Column.padding({ left: 4, right: 4 });
      Column.borderRadius({
        id: -1, type: 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        bundleName: '', moduleName: '' });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onClick(() => {
        let f2 = this.toolBarList[r1];
        if (f2.state === ItemState.ACTIVATE) {
          if (this.activateIndex === r1)
            this.activateIndex = -1;
          else {
            this.activateIndex = r1;
          }
        }
        if (!(f2.state === ItemState.DISABLE)) {
          f2.action && f2.action();
        }
      });
      Column.onHover((e2) => {
        if (e2) {
          this.toolBarItemBackground[r1] = (this.toolBarList[r1]?.state === ItemState.DISABLE) ?
            { id: -1, type: 10001,
              params: ['sys.color.ohos_id_color_toolbar_bg'],
              bundleName: '', moduleName: '' } :
            { id: -1, type: 10001, params: ['sys.color.ohos_id_color_hover'],
              bundleName: '', moduleName: '' };
        }
        else {
          this.toolBarItemBackground[r1] = { id: -1, type: 10001, params: ['sys.color.ohos_id_color_toolbar_bg'],
            bundleName: '', moduleName: '' };
        }
        this.itemBackground = this.toolBarItemBackground[r1];
      });
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor((this.toolBarList[r1]?.state === ItemState.DISABLE) ?
      this.toolBarItemBackground[r1] : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'],
          'bundleName': '', 'moduleName': '' });
      ViewStackProcessor.visualState("normal");
      Column.backgroundColor(this.toolBarItemBackground[r1]);
      ViewStackProcessor.visualState();
    }, Column);
    this.observeComponentCreation2((y1, z1) => {
      Image.create(this.toolBarList[r1]?.icon);
      Image.width(24);
      Image.height(24);
      Image.fillColor(this.activateIndex === r1 && !(this.toolBarList[r1]?.state === 2)
        ? this.iconActivePrimaryColor : this.iconPrimaryColor);
      Image.opacity((this.toolBarList[r1]?.state === 2) ? 0.4 : 1);
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
    }, Image);
    this.observeComponentCreation2((w1, x1) => {
      Text.create(this.toolBarList[r1]?.content);
      Text.fontColor(this.activateIndex === r1 && !(this.toolBarList[r1]?.state === 2)
        ? this.fontActivatedPrimaryColor : this.fontPrimaryColor);
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '', moduleName: '' });
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '', moduleName: '' });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.opacity((this.toolBarList[r1]?.state === 2) ? 0.4 : 1);
    }, Text);
    Text.pop();
    Column.pop();
  }

  refreshData() {
    this.menuContent = [];
    for (let q1 = 0; q1 < this.toolBarList.length; q1++) {
      if (q1 >= 4 && this.toolBarList.length > 5) {
        this.menuContent[q1 - 4] = {
          value: this.toolBarList[q1].content,
          action: this.toolBarList[q1].action,
        };
      }
      else {
        this.toolBarItemBackground[q1] = { id: -1, type: 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          bundleName: '', moduleName: '' };
        this.menuContent = [];
      }
    }
    return true;
  }

  aboutToAppear() {
    this.refreshData();
  }

  initialRender() {
    this.observeComponentCreation2((o1, p1) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((m1, n1) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
    }, Divider);
    this.observeComponentCreation2((k1, l1) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((g1, h1) => {
      Tabs.create({ barPosition: BarPosition.End, controller: this.controller });
      Tabs.vertical(false);
      Tabs.constraintSize({ minHeight: 56, maxHeight: 56 });
      Tabs.barMode(BarMode.Fixed);
      Tabs.onChange((j1) => {
      });
      Tabs.width('100%');
      Tabs.padding({ left: this.toolBarList.length < 5 ? 24 : 0, right: this.toolBarList.length < 5 ? 24 : 0 });
      Tabs.backgroundColor({
        id: -1, type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_bg'],
        bundleName: '', moduleName: '',
      });
    }, Tabs);
    this.observeComponentCreation2((n, o) => {
      ForEach.create();
      const p = (r, s) => {
        const t = r;
        this.observeComponentCreation2((v, w) => {
          If.create();
          if (this.toolBarList.length <= 5) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((e1, f1) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, s);
                } });
                TabContent.enabled(!(this.toolBarList[s]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[s]?.state === 2));
              }, TabContent);
              TabContent.pop();
            });
          }
          else if (s < 4) {
            this.ifElseBranchUpdateFunction(1, () => {
              this.observeComponentCreation2((a1, b1) => {
                TabContent.create();
                TabContent.tabBar({ builder: () => {
                  this.TabBuilder.call(this, s);
                } });
                TabContent.enabled(!(this.toolBarList[s]?.state === 2));
                TabContent.focusOnTouch(!(this.toolBarList[s]?.state === 2));
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
      this.forEachUpdateFunction(n, this.toolBarList, p, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((g, h) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > 5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((l, m) => {
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
export default { ToolBarOptions, ToolBar };