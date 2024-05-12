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

if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const EMPTY_STRING = '';
const MAX_PROGRESS = 100;
const MAX_PERCENTAGE = '100%';
const MIN_PERCENTAGE = '0%';
const TEXT_OPACITY = 0.4;
const BUTTON_NORMARL_WIDTH = 44;
const BUTTON_NORMARL_HEIGHT = 28;
const BUTTON_BORDER_RADIUS = 14;
const TEXT_ENABLE = 1.0;
const PROGRESS_BUTTON_PROGRESS_KEY = 'progress_button_progress_key';
const PROGRESS_BUTTON_PRIMARY_FONT_KEY = 'progress_button_primary_font_key';
const PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY = 'progress_button_container_background_color_key';
const PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY = 'progress_button_emphasize_secondary_button_key';
export class ProgressButton extends ViewPU {
  constructor(f1, g1, h1, i1 = -1, j1 = undefined, k1) {
    super(f1, h1, i1, k1);
    if (typeof j1 === "function") {
      this.paramsGenerator_ = j1;
    }
    this.__progress = new SynchedPropertySimpleOneWayPU(g1.progress, this, "progress");
    this.__textProgress = new ObservedPropertySimplePU(EMPTY_STRING, this, "textProgress");
    this.__content = new SynchedPropertySimpleOneWayPU(g1.content, this, "content");
    this.__isLoading = new ObservedPropertySimplePU(false, this, "isLoading");
    this.progressButtonWidth = BUTTON_NORMARL_WIDTH;
    this.clickCallback = () => { };
    this.__enable = new SynchedPropertySimpleOneWayPU(g1.enable, this, "enable");
    this.__progressColor = new ObservedPropertyObjectPU('#330A59F7', this, "progressColor");
    this.__containerBorderColor = new ObservedPropertyObjectPU('#330A59F7', this, "containerBorderColor");
    this.__containerBackgroundColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "containerBackgroundColor");
    this.setInitiallyProvidedValue(g1);
    this.declareWatch("progress", this.getProgressContext);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(e1) {
    if (e1.textProgress !== undefined) {
      this.textProgress = e1.textProgress;
    }
    if (e1.content === undefined) {
      this.__content.set(EMPTY_STRING);
    }
    if (e1.isLoading !== undefined) {
      this.isLoading = e1.isLoading;
    }
    if (e1.progressButtonWidth !== undefined) {
      this.progressButtonWidth = e1.progressButtonWidth;
    }
    if (e1.clickCallback !== undefined) {
      this.clickCallback = e1.clickCallback;
    }
    if (e1.enable === undefined) {
      this.__enable.set(true);
    }
    if (e1.progressColor !== undefined) {
      this.progressColor = e1.progressColor;
    }
    if (e1.containerBorderColor !== undefined) {
      this.containerBorderColor = e1.containerBorderColor;
    }
    if (e1.containerBackgroundColor !== undefined) {
      this.containerBackgroundColor = e1.containerBackgroundColor;
    }
  }
  updateStateVars(d1) {
    this.__progress.reset(d1.progress);
    this.__content.reset(d1.content);
    this.__enable.reset(d1.enable);
  }
  purgeVariableDependenciesOnElmtId(c1) {
    this.__progress.purgeDependencyOnElmtId(c1);
    this.__textProgress.purgeDependencyOnElmtId(c1);
    this.__content.purgeDependencyOnElmtId(c1);
    this.__isLoading.purgeDependencyOnElmtId(c1);
    this.__enable.purgeDependencyOnElmtId(c1);
    this.__progressColor.purgeDependencyOnElmtId(c1);
    this.__containerBorderColor.purgeDependencyOnElmtId(c1);
    this.__containerBackgroundColor.purgeDependencyOnElmtId(c1);
  }
  aboutToBeDeleted() {
    this.__progress.aboutToBeDeleted();
    this.__textProgress.aboutToBeDeleted();
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    this.__enable.aboutToBeDeleted();
    this.__progressColor.aboutToBeDeleted();
    this.__containerBorderColor.aboutToBeDeleted();
    this.__containerBackgroundColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get progress() {
    return this.__progress.get();
  }
  set progress(b1) {
    this.__progress.set(b1);
  }
  get textProgress() {
    return this.__textProgress.get();
  }
  set textProgress(a1) {
    this.__textProgress.set(a1);
  }
  get content() {
    return this.__content.get();
  }
  set content(z) {
    this.__content.set(z);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(y) {
    this.__isLoading.set(y);
  }
  get enable() {
    return this.__enable.get();
  }
  set enable(x) {
    this.__enable.set(x);
  }
  get progressColor() {
    return this.__progressColor.get();
  }
  set progressColor(w) {
    this.__progressColor.set(w);
  }
  get containerBorderColor() {
    return this.__containerBorderColor.get();
  }
  set containerBorderColor(v) {
    this.__containerBorderColor.set(v);
  }
  get containerBackgroundColor() {
    return this.__containerBackgroundColor.get();
  }
  set containerBackgroundColor(u) {
    this.__containerBackgroundColor.set(u);
  }
  onWillApplyTheme(t) {
    this.progressColor = t.colors.compEmphasizeSecondary;
    this.containerBorderColor = t.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = t.colors.iconOnFourth;
  }
  getButtonProgress() {
    if (this.progress < 0) {
      return 0;
    }
    else if (this.progress > MAX_PROGRESS) {
      return MAX_PROGRESS;
    }
    return this.progress;
  }
  getProgressContext() {
    if (this.progress < 0) {
      this.isLoading = false;
      this.textProgress = MIN_PERCENTAGE;
    }
    else if (this.progress >= MAX_PROGRESS) {
      this.isLoading = false;
      this.textProgress = MAX_PERCENTAGE;
    }
    else {
      this.isLoading = true;
      this.textProgress = Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS).toString() + "%";
    }
  }
  initialRender() {
    this.observeComponentCreation2((q, r) => {
      Button.createWithChild();
      Button.borderRadius(BUTTON_BORDER_RADIUS);
      Button.clip(false);
      Button.hoverEffect(HoverEffect.None);
      Button.key(PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY);
      Button.backgroundColor(ObservedObject.GetRawObject(this.containerBackgroundColor));
      Button.constraintSize({ minWidth: 44 });
      Button.width((!this.progressButtonWidth || this.progressButtonWidth < BUTTON_NORMARL_WIDTH) ?
        BUTTON_NORMARL_WIDTH : this.progressButtonWidth);
      Button.stateEffect(this.enable);
      Button.onClick(() => {
        if (!this.enable) {
          return;
        }
        if (this.progress < MAX_PROGRESS) {
          this.isLoading = !this.isLoading;
        }
        this.clickCallback && this.clickCallback();
      });
    }, Button);
    this.observeComponentCreation2((o, p) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((m, n) => {
      Progress.create({ value: this.getButtonProgress(), total: MAX_PROGRESS,
        style: ProgressStyle.Capsule });
      Progress.height(BUTTON_NORMARL_HEIGHT);
      Progress.borderRadius(BUTTON_BORDER_RADIUS);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.clip(false);
      Progress.enabled(this.enable);
      Progress.key(PROGRESS_BUTTON_PROGRESS_KEY);
      Progress.color(ObservedObject.GetRawObject(this.progressColor));
    }, Progress);
    this.observeComponentCreation2((k, l) => {
      Row.create();
    }, Row);
    this.observeComponentCreation2((i, j) => {
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.key(PROGRESS_BUTTON_PRIMARY_FONT_KEY);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ left: 8, right: 8 });
      Text.opacity(this.enable ? TEXT_ENABLE : TEXT_OPACITY);
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((g, h) => {
      Row.create();
      Row.key(PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY);
      Row.backgroundColor(Color.Transparent);
      Row.border({ width: 1, color: this.containerBorderColor });
      Row.height(BUTTON_NORMARL_HEIGHT);
      Row.borderRadius(BUTTON_BORDER_RADIUS);
      Row.width('100%');
    }, Row);
    Row.pop();
    Stack.pop();
    Button.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { ProgressButton };