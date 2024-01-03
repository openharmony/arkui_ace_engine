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

const EMPTY_STRING = '';
const MAX_PROGRESS = 100;
const MAX_PERCENTAGE = '100%';
const MIN_PERCENTAGE = '0%';
const TEXT_OPACITY = 0.4;
const BUTTON_NORMARL_WIDTH = 44;
const BUTTON_NORMARL_HEIGHT = 28;
const BUTTON_BORDER_RADIUS = 14;
const BUTTON_BORDER_WIDTH = 0.5;

export class ProgressButton extends ViewPU {
  constructor(e, t, s, r = -1) {
    super(e, s, r);
    this.__progress = new SynchedPropertySimpleOneWayPU(t.progress, this, 'progress');
    this.__textProgress = new ObservedPropertySimplePU('', this, 'textProgress');
    this.__content = new SynchedPropertySimpleOneWayPU(t.content, this, 'content');
    this.__isLoading = new ObservedPropertySimplePU(!1, this, 'isLoading');
    this.__enable = new SynchedPropertySimpleOneWayPU(t.enable, this, 'enable');
    this.progressButtonWidth = 44;
    this.clickCallback = null;
    this.setInitiallyProvidedValue(t);
    this.declareWatch('progress', this.getProgressContext);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.textProgress && (this.textProgress = e.textProgress);
    void 0 !== e.content ? this.__content.set(e.content) : this.__content.set('');
    void 0 !== e.isLoading && (this.isLoading = e.isLoading);
    void 0 !== e.enable ? this.__enable.set(e.enable) : this.__enable.set(!0);
    void 0 !== e.progressButtonWidth && (this.progressButtonWidth = e.progressButtonWidth);
    void 0 !== e.clickCallback && (this.clickCallback = e.clickCallback);
  }

  updateStateVars(e) {
    this.__progress.reset(e.progress);
    this.__content.reset(e.content);
    this.__enable.reset(e.enable);
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__progress.purgeDependencyOnElmtId(e);
    this.__textProgress.purgeDependencyOnElmtId(e);
    this.__content.purgeDependencyOnElmtId(e);
    this.__isLoading.purgeDependencyOnElmtId(e);
    this.__enable.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__progress.aboutToBeDeleted();
    this.__textProgress.aboutToBeDeleted();
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    this.__enable.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get progress() {
    return this.__progress.get();
  }

  set progress(e) {
    this.__progress.set(e);
  }

  get textProgress() {
    return this.__textProgress.get();
  }

  set textProgress(e) {
    this.__textProgress.set(e);
  }

  get content() {
    return this.__content.get();
  }

  set content(e) {
    this.__content.set(e);
  }

  get isLoading() {
    return this.__isLoading.get();
  }

  set isLoading(e) {
    this.__isLoading.set(e);
  }

  get enable() {
    return this.__enable.get();
  }

  set enable(e) {
    this.__enable.set(e);
  }

  getButtonProgress() {
    return this.progress < 0 ? 0 : this.progress > MAX_PROGRESS ? MAX_PROGRESS : this.progress;
  }

  getProgressContext() {
    if (this.progress < 0) {
      this.isLoading = !1;
      this.textProgress = '0%';
    } else if (this.progress >= MAX_PROGRESS) {
      this.isLoading = !1;
      this.textProgress = '100%';
    } else {
      this.isLoading = !0;
      this.textProgress = Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS).toString() + '%';
    }
  }

  initialRender() {
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Button.createWithChild();
      Button.borderRadius(BUTTON_BORDER_RADIUS);
      Button.clip(!1);
      Button.hoverEffect(HoverEffect.None);
      Button.backgroundColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_foreground_contrary'],
        bundleName: '',
        moduleName: ''
      });
      Button.constraintSize({ minWidth: 44 });
      Button.width(this.progressButtonWidth < BUTTON_NORMARL_WIDTH ? BUTTON_NORMARL_WIDTH : this.progressButtonWidth);
      Button.stateEffect(this.enable);
      Button.onClick((() => {
        if (this.enable) {
          this.progress < MAX_PROGRESS && (this.isLoading = !this.isLoading);
          this.clickCallback && this.clickCallback();
        }
      }));
      t || Button.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Stack.create();
      t || Stack.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Progress.create({ value: this.getButtonProgress(), total: MAX_PROGRESS, style: ProgressStyle.Capsule });
      Progress.height(BUTTON_NORMARL_HEIGHT);
      Progress.borderRadius(BUTTON_BORDER_RADIUS);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.clip(!1);
      Progress.enabled(this.enable);
      Progress.color('#330A59F7');
      t || Progress.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_button3'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ left: 8, right: 8 });
      Text.opacity(this.enable ? 1 : TEXT_OPACITY);
      t || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, t) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.backgroundColor(Color.Transparent);
      Row.border({ width: 1, color: '#330A59F7'});
      Row.height(28);
      Row.borderRadius(14);
      Row.width('100%');
      t || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Row.pop();
    Stack.pop();
    Button.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}
export default { ProgressButton };