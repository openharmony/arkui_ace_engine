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
!function(e) {
  e[e.ENABLE = 1] = 'ENABLE';
  e[e.DISABLE = 2] = 'DISABLE';
  e[e.ACTIVATE = 3] = 'ACTIVATE';
}(ItemState || (ItemState = {}));
const PUBLIC_MORE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAA' +
  'IGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IAr' +
  's4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzAAAOxAAADsQBlSsOGwAAAYFJREFUeNrt3CFLQ1EUB/CpCwYRo8' +
  'G4j2IwCNrUYjH4AfwcfgBBwWZRMNgtFqPdILJgEhGDweAZvDjmJnfv3I3fD/5l3DfOfWdv23vhdDoAAAAAAAAwzxa' +
  'm9L5rkePIdmSjee05chu5iHxXej5ar3saDdiJXDabGaYfOYg8VHbyU+peKryJvch1ZHnEmtXIYeQ+8lrJyU+re7Hg' +
  'JtYj52Ou7Uau/thwW1LrLtmAk8jKBOsH37FHFTQgte6SDdht6ZjSUusu2YBeS8eUllr3YvLmuzP6971bYwP6/zjmpY' +
  'KTmVp3yQbctXRMaal1l2zAaeRngvUfkbMKGpBad8kbsffIZ2RrzPX7kacKGpBad+k74cfmE7I54ur6au4obyr6UU2r' +
  'e1oP43rNDc6wh1qDS/6t0n83s1o3AAAAAAAAAAAAAEAysyKS6zYrIrlusyKS6zYrwqyIdGZFJDMrIplZETPIrIh5qdu' +
  'sCLMi0pkVkcysiAqYFVEJsyIAAAAAAAAAKOYXUlF8EUcdfbsAAAAASUVORK5CYII=';
let ToolBarOption = class {
  constructor() {
    this.state = 1;
  }
};
ToolBarOption = __decorate([Observed], ToolBarOption);

export { ToolBarOption };
let ToolBarOptions = class extends Array {
};
ToolBarOptions = __decorate([Observed], ToolBarOptions);

export { ToolBarOptions };

export class ToolBar extends ViewPU {
  constructor(e, t, o, r = -1) {
    super(e, o, r);
    this.__toolBarList = new SynchedPropertyNesedObjectPU(t.toolBarList, this, 'toolBarList');
    this.controller = void 0;
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(t.activateIndex, this, 'activateIndex');
    this.__menuContent = new ObservedPropertyObjectPU([], this, 'menuContent');
    this.toolBarItemBackground = [];
    this.__itemBackground = new ObservedPropertyObjectPU({
      id: -1,
      type: 10001,
      params: ['sys.color.ohos_id_color_toolbar_bg'],
      bundleName: '',
      moduleName: ''
    }, this, 'itemBackground');
    this.setInitiallyProvidedValue(t);
  }

  setInitiallyProvidedValue(e) {
    this.__toolBarList.set(e.toolBarList);
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.activateIndex ? this.__activateIndex.set(e.activateIndex) : this.__activateIndex.set(-1);
    void 0 !== e.menuContent && (this.menuContent = e.menuContent);
    void 0 !== e.toolBarItemBackground && (this.toolBarItemBackground = e.toolBarItemBackground);
    void 0 !== e.itemBackground && (this.itemBackground = e.itemBackground);
  }

  updateStateVars(e) {
    this.__toolBarList.set(e.toolBarList);
    this.__activateIndex.reset(e.activateIndex);
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__toolBarList.purgeDependencyOnElmtId(e);
    this.__activateIndex.purgeDependencyOnElmtId(e);
    this.__menuContent.purgeDependencyOnElmtId(e);
    this.__itemBackground.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__itemBackground.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get toolBarList() {
    return this.__toolBarList.get();
  }

  get activateIndex() {
    return this.__activateIndex.get();
  }

  set activateIndex(e) {
    this.__activateIndex.set(e);
  }

  get menuContent() {
    return this.__menuContent.get();
  }

  set menuContent(e) {
    this.__menuContent.set(e);
  }

  get itemBackground() {
    return this.__itemBackground.get();
  }

  set itemBackground(e) {
    this.__itemBackground.set(e);
  }

  MoreTabBuilder(e, t = null) {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.bindMenu(ObservedObject.GetRawObject(this.menuContent), { offset: { x: 5, y: -10 } });
      Column.padding({ left: 4, right: 4 });
      Column.borderRadius({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        bundleName: '',
        moduleName: ''
      });
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE_WIDTH_HEIGHT);
      Image.height(IMAGE_SIZE_WIDTH_HEIGHT);
      Image.fillColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_icon'],
        bundleName: '',
        moduleName: ''
      });
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      t || Image.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create({
        id: -1,
        type: 10003,
        params: ['app.string.id_string_more'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_text'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      t || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Column.pop();
  }

  TabBuilder(e, t = null) {
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.focusable(!(ITEM_DISABLE_STATE === this.toolBarList[e].state));
      Column.focusOnTouch(!(ITEM_DISABLE_STATE === this.toolBarList[e].state));
      Column.padding({ left: 4, right: 4 });
      Column.borderRadius({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_corner_radius_clicked'],
        bundleName: '',
        moduleName: ''
      });
      Column.backgroundColor(ObservedObject.GetRawObject(this.itemBackground));
      Column.onClick((() => {
        ITEM_DISABLE_ACTIVATE === this.toolBarList[e].state && (this.activateIndex === e ? this.activateIndex = -1 : this.activateIndex = e);
        ITEM_DISABLE_STATE !== this.toolBarList[e].state && this.toolBarList[e].action && this.toolBarList[e].action();
      }));
      Column.onHover((t => {
        this.toolBarItemBackground[e] = t ? ITEM_DISABLE_STATE === this.toolBarList[e].state ? {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          bundleName: '',
          moduleName: ''
        } : {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_hover'],
          bundleName: '',
          moduleName: ''
        } : {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          bundleName: '',
          moduleName: ''
        };
        this.itemBackground = this.toolBarItemBackground[e];
      }));
      ViewStackProcessor.visualState('pressed');
      Column.backgroundColor(ITEM_DISABLE_STATE === this.toolBarList[e].state ? this.toolBarItemBackground[e] : {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_click_effect'],
        bundleName: '',
        moduleName: ''
      });
      ViewStackProcessor.visualState('normal');
      Column.backgroundColor(this.toolBarItemBackground[e]);
      ViewStackProcessor.visualState();
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Image.create(this.toolBarList[e].icon);
      Image.width(IMAGE_SIZE_WIDTH_HEIGHT);
      Image.height(IMAGE_SIZE_WIDTH_HEIGHT);
      Image.fillColor(this.activateIndex === e && ITEM_DISABLE_STATE !== this.toolBarList[e].state ? {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary_activated'],
        bundleName: '',
        moduleName: ''
      } : {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_primary'],
        bundleName: '',
        moduleName: ''
      });
      Image.opacity(ITEM_DISABLE_STATE === this.toolBarList[e].state ? DISABLE_OPACITY : 1);
      Image.margin({ top: 8, bottom: 2 });
      Image.objectFit(ImageFit.Contain);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((t, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Text.create(this.toolBarList[e].content);
      Text.fontColor(this.activateIndex === e && ITEM_DISABLE_STATE !== this.toolBarList[e].state ? {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_text_actived'],
        bundleName: '',
        moduleName: ''
      } : {
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_text'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '',
        moduleName: ''
      });
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_caption'],
        bundleName: '',
        moduleName: ''
      });
      Text.minFontSize(TEXT_MIN_SIZE);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(TEXT_MAX_LINES);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.opacity(ITEM_DISABLE_STATE === this.toolBarList[e].state ? DISABLE_OPACITY : 1);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Column.pop();
  }

  refreshData() {
    this.menuContent = [];
    for (let e = 0; e < this.toolBarList.length; e++) {
      if (e >= TOOLBAR_LIST_NORMORL && this.toolBarList.length > TOOLBAR_LIST_LENGTH) {
        this.menuContent[e - TOOLBAR_LIST_NORMORL] = {
          value: this.toolBarList[e].content,
          action: this.toolBarList[e].action
        };
      } else {
        this.toolBarItemBackground[e] = {
          id: -1,
          type: 10001,
          params: ['sys.color.ohos_id_color_toolbar_bg'],
          bundleName: '',
          moduleName: ''
        };
        this.menuContent = [];
      }
    }
    return !0;
  }

  aboutToAppear() {
    this.refreshData();
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      t || Divider.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.width('100%');
      t || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Tabs.create({ barPosition: BarPosition.End, controller: this.controller });
      Tabs.vertical(!1);
      Tabs.constraintSize({ minHeight: 56, maxHeight: 56 });
      Tabs.barMode(BarMode.Fixed);
      Tabs.onChange((e => {
      }));
      Tabs.width('100%');
      Tabs.padding({ left: this.toolBarList.length < 5 ? 20: 0, right: this.toolBarList.length < 5 ? 20: 0})
      Tabs.backgroundColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_toolbar_bg'],
        bundleName: '',
        moduleName: ''
      });
      t || Tabs.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.toolBarList, ((e, t) => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          this.toolBarList.length <= TOOLBAR_LIST_LENGTH ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              TabContent.create();
              TabContent.tabBar({
                builder: () => {
                  this.TabBuilder.call(this, t);
                }
              });
              TabContent.enabled(!(ITEM_DISABLE_STATE === this.toolBarList[t].state));
              TabContent.focusOnTouch(!(ITEM_DISABLE_STATE === this.toolBarList[t].state));
              r || TabContent.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            TabContent.pop();
          })) : t < TOOLBAR_LIST_NORMORL && this.ifElseBranchUpdateFunction(1, (() => {
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              TabContent.create();
              TabContent.tabBar({
                builder: () => {
                  this.TabBuilder.call(this, t);
                }
              });
              TabContent.enabled(!(ITEM_DISABLE_STATE === this.toolBarList[t].state));
              TabContent.focusOnTouch(!(ITEM_DISABLE_STATE === this.toolBarList[t].state));
              r || TabContent.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            TabContent.pop();
          }));
          r || If.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        If.pop();
      }), void 0, !0, !1);
      t || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    ForEach.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.refreshData() && this.toolBarList.length > TOOLBAR_LIST_LENGTH ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          TabContent.create();
          TabContent.tabBar({
            builder: () => {
              this.MoreTabBuilder.call(this, TOOLBAR_LIST_NORMORL);
            }
          });
          t || TabContent.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        TabContent.pop();
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
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