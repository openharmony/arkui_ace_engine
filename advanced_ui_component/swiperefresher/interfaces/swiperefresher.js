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

const LOADINGPROGRESS_SIZE = 24;
const DEFAULT_MARGIN = 16;
const ITEM_SPACE = 4;

export class SwipeRefresher extends ViewPU {
  constructor(e, t, o, s = -1) {
    super(e, o, s);
    this.__content = new SynchedPropertySimpleOneWayPU(t.content, this, "content");
    this.__isLoading = new SynchedPropertySimpleOneWayPU(t.isLoading, this, "isLoading");
    this.setInitiallyProvidedValue(t)
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.content ? this.__content.set(e.content) : this.__content.set(null);
    void 0 !== e.isLoading ? this.__isLoading.set(e.isLoading) : this.__isLoading.set(!1)
  }

  updateStateVars(e) {
    this.__content.reset(e.content);
    this.__isLoading.reset(e.isLoading)
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__content.purgeDependencyOnElmtId(e);
    this.__isLoading.purgeDependencyOnElmtId(e)
  }

  aboutToBeDeleted() {
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal()
  }

  get content() {
    return this.__content.get()
  }

  set content(e) {
    this.__content.set(e)
  }

  get isLoading() {
    return this.__isLoading.get()
  }

  set isLoading(e) {
    this.__isLoading.set(e)
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
      t || Flex.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.isLoading ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          LoadingProgress.create();
          LoadingProgress.height(24);
          LoadingProgress.width(24);
          LoadingProgress.margin({ right: 4 });
          t || LoadingProgress.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }))
      })) : If.branchId(1);
      t || If.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    If.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.content);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_text_secondary"],
        bundleName: "",
        moduleName: ""
      });
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_body2"],
        bundleName: "",
        moduleName: ""
      });
      Text.padding({ top: 16, bottom: 16 });
      t || Text.pop();
      ViewStackProcessor.StopGetAccessRecording()
    }));
    Text.pop();
    Flex.pop()
  }

  rerender() {
    this.updateDirtyElements()
  }
}