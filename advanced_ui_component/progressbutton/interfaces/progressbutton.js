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
const PROGRESS_BUTTON_CONTAINER_EMPHASIZE_SECONDARY_BACKGROUND_KEY = 'progress_button_container_emphasiza_secondary_background_key';
const PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY = 'progress_button_emphasize_secondary_button_key';
export class ProgressButton extends ViewPU {
  constructor(g1, h1, i1, j1 = -1, k1 = undefined, l1) {
    super(g1, i1, j1, l1);
    if (typeof k1 === "function") {
      this.paramsGenerator_ = k1;
    }
    this.__progress = new SynchedPropertySimpleOneWayPU(h1.progress, this, "progress");
    this.__textProgress = new ObservedPropertySimplePU(EMPTY_STRING, this, "textProgress");
    this.__content = new SynchedPropertySimpleOneWayPU(h1.content, this, "content");
    this.__isLoading = new ObservedPropertySimplePU(false, this, "isLoading");
    this.progressButtonWidth = BUTTON_NORMARL_WIDTH;
    this.clickCallback = () => { };
    this.__enable = new SynchedPropertySimpleOneWayPU(h1.enable, this, "enable");
    this.__progressColor = new ObservedPropertyObjectPU('#330A59F7', this, "progressColor");
    this.__textFontColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "textFontColor");
    this.__containerBorderColor = new ObservedPropertyObjectPU('#330A59F7', this, "containerBorderColor");
    this.__containerBackgroundColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ["sys.color.ohos_id_color_foreground_contrary"], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "containerBackgroundColor");
    this.setInitiallyProvidedValue(h1);
    this.declareWatch("progress", this.getProgressContext);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(f1) {
    if (f1.textProgress !== undefined) {
      this.textProgress = f1.textProgress;
    }
    if (f1.content === undefined) {
      this.__content.set(EMPTY_STRING);
    }
    if (f1.isLoading !== undefined) {
      this.isLoading = f1.isLoading;
    }
    if (f1.progressButtonWidth !== undefined) {
      this.progressButtonWidth = f1.progressButtonWidth;
    }
    if (f1.clickCallback !== undefined) {
      this.clickCallback = f1.clickCallback;
    }
    if (f1.enable === undefined) {
      this.__enable.set(true);
    }
    if (f1.progressColor !== undefined) {
      this.progressColor = f1.progressColor;
    }
    if (f1.textFontColor !== undefined) {
      this.textFontColor = f1.textFontColor;
    }
    if (f1.containerBorderColor !== undefined) {
      this.containerBorderColor = f1.containerBorderColor;
    }
    if (f1.containerBackgroundColor !== undefined) {
      this.containerBackgroundColor = f1.containerBackgroundColor;
    }
  }
  updateStateVars(e1) {
    this.__progress.reset(e1.progress);
    this.__content.reset(e1.content);
    this.__enable.reset(e1.enable);
  }
  purgeVariableDependenciesOnElmtId(d1) {
    this.__progress.purgeDependencyOnElmtId(d1);
    this.__textProgress.purgeDependencyOnElmtId(d1);
    this.__content.purgeDependencyOnElmtId(d1);
    this.__isLoading.purgeDependencyOnElmtId(d1);
    this.__enable.purgeDependencyOnElmtId(d1);
    this.__progressColor.purgeDependencyOnElmtId(d1);
    this.__textFontColor.purgeDependencyOnElmtId(d1);
    this.__containerBorderColor.purgeDependencyOnElmtId(d1);
    this.__containerBackgroundColor.purgeDependencyOnElmtId(d1);
  }
  aboutToBeDeleted() {
    this.__progress.aboutToBeDeleted();
    this.__textProgress.aboutToBeDeleted();
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    this.__enable.aboutToBeDeleted();
    this.__progressColor.aboutToBeDeleted();
    this.__textFontColor.aboutToBeDeleted();
    this.__containerBorderColor.aboutToBeDeleted();
    this.__containerBackgroundColor.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get progress() {
    return this.__progress.get();
  }
  set progress(c1) {
    this.__progress.set(c1);
  }
  get textProgress() {
    return this.__textProgress.get();
  }
  set textProgress(b1) {
    this.__textProgress.set(b1);
  }
  get content() {
    return this.__content.get();
  }
  set content(a1) {
    this.__content.set(a1);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(z) {
    this.__isLoading.set(z);
  }
  get enable() {
    return this.__enable.get();
  }
  set enable(y) {
    this.__enable.set(y);
  }
  get progressColor() {
    return this.__progressColor.get();
  }
  set progressColor(x) {
    this.__progressColor.set(x);
  }
  get textFontColor() {
    return this.__textFontColor.get();
  }
  set textFontColor(w) {
    this.__textFontColor.set(w);
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
    this.textFontColor = t.colors.fontPrimary;
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
      Text.fontColor(ObservedObject.GetRawObject(this.textFontColor));
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ left: 8, right: 8 });
      Text.opacity(this.enable ? TEXT_ENABLE : TEXT_OPACITY);
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((g, h) => {
      Row.create();
      Row.key(PROGRESS_BUTTON_CONTAINER_EMPHASIZE_SECONDARY_BACKGROUND_KEY);
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