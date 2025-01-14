/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
  constructor(c1, d1, e1, f1 = -1, g1 = undefined, h1) {
    super(c1, e1, f1, h1);
    if (typeof g1 === 'function') {
      this.paramsGenerator_ = g1;
    }
    this.__progress = new SynchedPropertySimpleOneWayPU(d1.progress, this, 'progress');
    this.__textProgress = new ObservedPropertySimplePU(EMPTY_STRING, this, 'textProgress');
    this.__content = new SynchedPropertySimpleOneWayPU(d1.content, this, 'content');
    this.__isLoading = new ObservedPropertySimplePU(false, this, 'isLoading');
    this.progressButtonWidth = BUTTON_NORMARL_WIDTH;
    this.clickCallback = () => { };
    this.__enable = new SynchedPropertySimpleOneWayPU(d1.enable, this, 'enable');
    this.colorOptions = undefined;
    this.__progressColor = new ObservedPropertyObjectPU('#330A59F7', this, 'progressColor');
    this.__containerBorderColor = new ObservedPropertyObjectPU('#330A59F7', this, 'containerBorderColor');
    this.__containerBackgroundColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'containerBackgroundColor');
    this.__textHeight = new ObservedPropertyObjectPU(BUTTON_NORMARL_HEIGHT, this, 'textHeight');
    this.__buttonBorderRadius = new ObservedPropertySimplePU(BUTTON_BORDER_RADIUS, this, 'buttonBorderRadius');
    this.setInitiallyProvidedValue(d1);
    this.declareWatch('progress', this.getProgressContext);
    this.declareWatch('isLoading', this.getLoadingProgress);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(b1) {
    if (b1.textProgress !== undefined) {
      this.textProgress = b1.textProgress;
    }
    if (b1.content === undefined) {
      this.__content.set(EMPTY_STRING);
    }
    if (b1.isLoading !== undefined) {
      this.isLoading = b1.isLoading;
    }
    if (b1.progressButtonWidth !== undefined) {
      this.progressButtonWidth = b1.progressButtonWidth;
    }
    if (b1.clickCallback !== undefined) {
      this.clickCallback = b1.clickCallback;
    }
    if (b1.enable === undefined) {
      this.__enable.set(true);
    }
    if (b1.colorOptions !== undefined) {
      this.colorOptions = b1.colorOptions;
    }
    if (b1.progressColor !== undefined) {
      this.progressColor = b1.progressColor;
    }
    if (b1.containerBorderColor !== undefined) {
      this.containerBorderColor = b1.containerBorderColor;
    }
    if (b1.containerBackgroundColor !== undefined) {
      this.containerBackgroundColor = b1.containerBackgroundColor;
    }
    if (b1.textHeight !== undefined) {
      this.textHeight = b1.textHeight;
    }
    if (b1.buttonBorderRadius !== undefined) {
      this.buttonBorderRadius = b1.buttonBorderRadius;
    }
  }
  updateStateVars(a1) {
    this.__progress.reset(a1.progress);
    this.__content.reset(a1.content);
    this.__enable.reset(a1.enable);
  }
  purgeVariableDependenciesOnElmtId(z) {
    this.__progress.purgeDependencyOnElmtId(z);
    this.__textProgress.purgeDependencyOnElmtId(z);
    this.__content.purgeDependencyOnElmtId(z);
    this.__isLoading.purgeDependencyOnElmtId(z);
    this.__enable.purgeDependencyOnElmtId(z);
    this.__progressColor.purgeDependencyOnElmtId(z);
    this.__containerBorderColor.purgeDependencyOnElmtId(z);
    this.__containerBackgroundColor.purgeDependencyOnElmtId(z);
    this.__textHeight.purgeDependencyOnElmtId(z);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(z);
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
    this.__textHeight.aboutToBeDeleted();
    this.__buttonBorderRadius.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get progress() {
    return this.__progress.get();
  }
  set progress(y) {
    this.__progress.set(y);
  }
  get textProgress() {
    return this.__textProgress.get();
  }
  set textProgress(x) {
    this.__textProgress.set(x);
  }
  get content() {
    return this.__content.get();
  }
  set content(w) {
    this.__content.set(w);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(v) {
    this.__isLoading.set(v);
  }
  get enable() {
    return this.__enable.get();
  }
  set enable(u) {
    this.__enable.set(u);
  }
  get progressColor() {
    return this.__progressColor.get();
  }
  set progressColor(t) {
    this.__progressColor.set(t);
  }
  get containerBorderColor() {
    return this.__containerBorderColor.get();
  }
  set containerBorderColor(s) {
    this.__containerBorderColor.set(s);
  }
  get containerBackgroundColor() {
    return this.__containerBackgroundColor.get();
  }
  set containerBackgroundColor(r) {
    this.__containerBackgroundColor.set(r);
  }
  get textHeight() {
    return this.__textHeight.get();
  }
  set textHeight(q) {
    this.__textHeight.set(q);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(p) {
    this.__buttonBorderRadius.set(p);
  }
  onWillApplyTheme(o) {
    this.progressColor = o.colors.compEmphasizeSecondary;
    this.containerBorderColor = o.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = o.colors.iconOnFourth;
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
      this.textProgress = Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS).toString() + '%';
    }
  }
  getLoadingProgress() {
    if (this.isLoading) {
      if (this.progress < 0) {
        this.textProgress = MIN_PERCENTAGE;
      }
      else if (this.progress >= MAX_PROGRESS) {
        this.textProgress = MAX_PERCENTAGE;
      }
      else {
        this.textProgress = Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS).toString() + '%';
      }
    }
  }
  initialRender() {
    this.observeComponentCreation2((m, n) => {
      Button.createWithChild();
      Button.borderRadius(this.buttonBorderRadius);
      Button.clip(false);
      Button.hoverEffect(HoverEffect.None);
      Button.key(PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY);
      Button.backgroundColor(this.colorOptions?.backgroundColor
        ? this.colorOptions?.backgroundColor
        : this.containerBackgroundColor);
      Button.constraintSize({ minWidth: 44 });
      Button.padding({ top: 0, bottom: 0 });
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
    this.observeComponentCreation2((k, l) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((i, j) => {
      Progress.create({ value: this.getButtonProgress(), total: MAX_PROGRESS,
        style: ProgressStyle.Capsule });
      Progress.height(ObservedObject.GetRawObject(this.textHeight));
      Progress.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Progress.borderRadius(this.buttonBorderRadius);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.padding({ top: 0.6, left: 0.6, right: 0.6, bottom: 0.6 });
      Progress.clip(false);
      Progress.key(PROGRESS_BUTTON_PROGRESS_KEY);
      Progress.color(this.colorOptions?.progressColor ? this.colorOptions?.progressColor : this.progressColor);
    }, Progress);
    this.observeComponentCreation2((g, h) => {
      Row.create();
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
    }, Row);
    this.observeComponentCreation2((c, d) => {
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.fontWeight(FontWeight.Medium);
      Text.key(PROGRESS_BUTTON_PRIMARY_FONT_KEY);
      Text.fontColor(this.colorOptions?.textColor);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ top: 4, left: 8, right: 8, bottom: 4 });
      Text.opacity(this.enable ? TEXT_ENABLE : TEXT_OPACITY);
      Text.onAreaChange((e, f) => {
        if (!f.height || f.height === this.textHeight) {
          return;
        }
        this.textHeight = f.height > BUTTON_NORMARL_HEIGHT ? f.height : BUTTON_NORMARL_HEIGHT;
        this.buttonBorderRadius = Number(this.textHeight) / 2;
      });
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((a, b) => {
      Row.create();
      Row.key(PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY);
      Row.backgroundColor(Color.Transparent);
      Row.border({
        width: 1,
        color: this.colorOptions?.borderColor ? this.colorOptions?.borderColor : this.containerBorderColor
      });
      Row.height(ObservedObject.GetRawObject(this.textHeight));
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Row.borderRadius(this.buttonBorderRadius);
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