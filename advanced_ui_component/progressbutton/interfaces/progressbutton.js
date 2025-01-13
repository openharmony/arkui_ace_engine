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
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
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
  constructor(k1, l1, m1, n1 = -1, o1 = undefined, p1) {
    super(k1, m1, n1, p1);
    if (typeof o1 === 'function') {
      this.paramsGenerator_ = o1;
    }
    this.__progress = new SynchedPropertySimpleOneWayPU(l1.progress, this, 'progress');
    this.__textProgress = new ObservedPropertySimplePU(EMPTY_STRING, this, 'textProgress');
    this.__content = new SynchedPropertySimpleOneWayPU(l1.content, this, 'content');
    this.__isLoading = new ObservedPropertySimplePU(false, this, 'isLoading');
    this.progressButtonWidth = BUTTON_NORMARL_WIDTH;
    this.clickCallback = () => { };
    this.__enable = new SynchedPropertySimpleOneWayPU(l1.enable, this, 'enable');
    this.colorOptions = undefined;
    this.__progressColor = new ObservedPropertyObjectPU('#330A59F7', this, 'progressColor');
    this.__containerBorderColor = new ObservedPropertyObjectPU('#330A59F7', this, 'containerBorderColor');
    this.__containerBackgroundColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'containerBackgroundColor');
    this.__textHeight = new ObservedPropertyObjectPU(BUTTON_NORMARL_HEIGHT, this, 'textHeight');
    this.__buttonBorderRadius = new ObservedPropertySimplePU(BUTTON_BORDER_RADIUS, this, 'buttonBorderRadius');
    this.setInitiallyProvidedValue(l1);
    this.declareWatch('progress', this.getProgressContext);
    this.declareWatch('isLoading', this.getLoadingProgress);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(j1) {
    if (j1.textProgress !== undefined) {
      this.textProgress = j1.textProgress;
    }
    if (j1.content === undefined) {
      this.__content.set(EMPTY_STRING);
    }
    if (j1.isLoading !== undefined) {
      this.isLoading = j1.isLoading;
    }
    if (j1.progressButtonWidth !== undefined) {
      this.progressButtonWidth = j1.progressButtonWidth;
    }
    if (j1.clickCallback !== undefined) {
      this.clickCallback = j1.clickCallback;
    }
    if (j1.enable === undefined) {
      this.__enable.set(true);
    }
    if (j1.colorOptions !== undefined) {
      this.colorOptions = j1.colorOptions;
    }
    if (j1.progressColor !== undefined) {
      this.progressColor = j1.progressColor;
    }
    if (j1.containerBorderColor !== undefined) {
      this.containerBorderColor = j1.containerBorderColor;
    }
    if (j1.containerBackgroundColor !== undefined) {
      this.containerBackgroundColor = j1.containerBackgroundColor;
    }
    if (j1.textHeight !== undefined) {
      this.textHeight = j1.textHeight;
    }
    if (j1.buttonBorderRadius !== undefined) {
      this.buttonBorderRadius = j1.buttonBorderRadius;
    }
  }
  updateStateVars(i1) {
    this.__progress.reset(i1.progress);
    this.__content.reset(i1.content);
    this.__enable.reset(i1.enable);
  }
  purgeVariableDependenciesOnElmtId(h1) {
    this.__progress.purgeDependencyOnElmtId(h1);
    this.__textProgress.purgeDependencyOnElmtId(h1);
    this.__content.purgeDependencyOnElmtId(h1);
    this.__isLoading.purgeDependencyOnElmtId(h1);
    this.__enable.purgeDependencyOnElmtId(h1);
    this.__progressColor.purgeDependencyOnElmtId(h1);
    this.__containerBorderColor.purgeDependencyOnElmtId(h1);
    this.__containerBackgroundColor.purgeDependencyOnElmtId(h1);
    this.__textHeight.purgeDependencyOnElmtId(h1);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(h1);
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
  set progress(g1) {
    this.__progress.set(g1);
  }
  get textProgress() {
    return this.__textProgress.get();
  }
  set textProgress(f1) {
    this.__textProgress.set(f1);
  }
  get content() {
    return this.__content.get();
  }
  set content(e1) {
    this.__content.set(e1);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(d1) {
    this.__isLoading.set(d1);
  }
  get enable() {
    return this.__enable.get();
  }
  set enable(c1) {
    this.__enable.set(c1);
  }
  get progressColor() {
    return this.__progressColor.get();
  }
  set progressColor(b1) {
    this.__progressColor.set(b1);
  }
  get containerBorderColor() {
    return this.__containerBorderColor.get();
  }
  set containerBorderColor(a1) {
    this.__containerBorderColor.set(a1);
  }
  get containerBackgroundColor() {
    return this.__containerBackgroundColor.get();
  }
  set containerBackgroundColor(z) {
    this.__containerBackgroundColor.set(z);
  }
  get textHeight() {
    return this.__textHeight.get();
  }
  set textHeight(y) {
    this.__textHeight.set(y);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(x) {
    this.__buttonBorderRadius.set(x);
  }
  onWillApplyTheme(w) {
    this.progressColor = w.colors.compEmphasizeSecondary;
    this.containerBorderColor = w.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = w.colors.iconOnFourth;
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
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((t, u) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
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
      if (!u) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r, s) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r);
      Stack.create();
      if (!s) {
        Stack.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p, q) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p);
      Progress.create({ value: this.getButtonProgress(), total: MAX_PROGRESS,
        style: ProgressStyle.Capsule });
      Progress.height(ObservedObject.GetRawObject(this.textHeight));
      Progress.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Progress.borderRadius(this.buttonBorderRadius);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.clip(false);
      Progress.key(PROGRESS_BUTTON_PROGRESS_KEY);
      Progress.color(this.colorOptions?.progressColor ? this.colorOptions?.progressColor : this.progressColor);
      if (!q) {
        Progress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((n, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(n);
      Row.create();
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      if (!o) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((i, j) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i);
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.fontWeight(FontWeight.Medium);
      Text.key(PROGRESS_BUTTON_PRIMARY_FONT_KEY);
      Text.fontColor(this.colorOptions?.textColor);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ top: 4, left: 8, right: 8, bottom: 4 });
      Text.opacity(this.enable ? TEXT_ENABLE : TEXT_OPACITY);
      Text.onAreaChange((l, m) => {
        if (!m.height || m.height === this.textHeight) {
          return;
        }
        this.textHeight = m.height > BUTTON_NORMARL_HEIGHT ? m.height : BUTTON_NORMARL_HEIGHT;
        this.buttonBorderRadius = Number(this.textHeight) / 2;
      });
      if (!j) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    this.observeComponentCreation((g, h) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g);
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
      if (!h) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Stack.pop();
    Button.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}

export default { ProgressButton };