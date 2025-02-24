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
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
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
  constructor(h1, i1, j1, k1 = -1, l1 = undefined, m1) {
    super(h1, j1, k1, m1);
    if (typeof l1 === 'function') {
      this.paramsGenerator_ = l1;
    }
    this.__progress = new SynchedPropertySimpleOneWayPU(i1.progress, this, 'progress');
    this.__textProgress = new ObservedPropertySimplePU(EMPTY_STRING, this, 'textProgress');
    this.__content = new SynchedPropertySimpleOneWayPU(i1.content, this, 'content');
    this.__isLoading = new ObservedPropertySimplePU(false, this, 'isLoading');
    this.progressButtonWidth = BUTTON_NORMARL_WIDTH;
    this.clickCallback = () => { };
    this.__enable = new SynchedPropertySimpleOneWayPU(i1.enable, this, 'enable');
    this.__colorOptions = new SynchedPropertyObjectOneWayPU(i1.colorOptions, this, 'colorOptions');
    this.__progressButtonRadius = new SynchedPropertyObjectOneWayPU(i1.progressButtonRadius, this, 'progressButtonRadius');
    this.__progressColor = new ObservedPropertyObjectPU('#330A59F7', this, 'progressColor');
    this.__containerBorderColor = new ObservedPropertyObjectPU('#330A59F7', this, 'containerBorderColor');
    this.__containerBackgroundColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'containerBackgroundColor');
    this.__textHeight = new ObservedPropertyObjectPU(BUTTON_NORMARL_HEIGHT, this, 'textHeight');
    this.__buttonBorderRadius = new ObservedPropertySimplePU(BUTTON_BORDER_RADIUS, this, 'buttonBorderRadius');
    this.setInitiallyProvidedValue(i1);
    this.declareWatch('progress', this.getProgressContext);
    this.declareWatch('isLoading', this.getLoadingProgress);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(g1) {
    if (g1.textProgress !== undefined) {
      this.textProgress = g1.textProgress;
    }
    if (g1.content === undefined) {
      this.__content.set(EMPTY_STRING);
    }
    if (g1.isLoading !== undefined) {
      this.isLoading = g1.isLoading;
    }
    if (g1.progressButtonWidth !== undefined) {
      this.progressButtonWidth = g1.progressButtonWidth;
    }
    if (g1.clickCallback !== undefined) {
      this.clickCallback = g1.clickCallback;
    }
    if (g1.enable === undefined) {
      this.__enable.set(true);
    }
    if (g1.colorOptions === undefined) {
      this.__colorOptions.set(undefined);
    }
    if (g1.progressButtonRadius === undefined) {
      this.__progressButtonRadius.set(undefined);
    }
    if (g1.progressColor !== undefined) {
      this.progressColor = g1.progressColor;
    }
    if (g1.containerBorderColor !== undefined) {
      this.containerBorderColor = g1.containerBorderColor;
    }
    if (g1.containerBackgroundColor !== undefined) {
      this.containerBackgroundColor = g1.containerBackgroundColor;
    }
    if (g1.textHeight !== undefined) {
      this.textHeight = g1.textHeight;
    }
    if (g1.buttonBorderRadius !== undefined) {
      this.buttonBorderRadius = g1.buttonBorderRadius;
    }
  }
  updateStateVars(f1) {
    this.__progress.reset(f1.progress);
    this.__content.reset(f1.content);
    this.__enable.reset(f1.enable);
    this.__colorOptions.reset(f1.colorOptions);
    this.__progressButtonRadius.reset(f1.progressButtonRadius);
  }
  purgeVariableDependenciesOnElmtId(e1) {
    this.__progress.purgeDependencyOnElmtId(e1);
    this.__textProgress.purgeDependencyOnElmtId(e1);
    this.__content.purgeDependencyOnElmtId(e1);
    this.__isLoading.purgeDependencyOnElmtId(e1);
    this.__enable.purgeDependencyOnElmtId(e1);
    this.__colorOptions.purgeDependencyOnElmtId(e1);
    this.__progressButtonRadius.purgeDependencyOnElmtId(e1);
    this.__progressColor.purgeDependencyOnElmtId(e1);
    this.__containerBorderColor.purgeDependencyOnElmtId(e1);
    this.__containerBackgroundColor.purgeDependencyOnElmtId(e1);
    this.__textHeight.purgeDependencyOnElmtId(e1);
    this.__buttonBorderRadius.purgeDependencyOnElmtId(e1);
  }
  aboutToBeDeleted() {
    this.__progress.aboutToBeDeleted();
    this.__textProgress.aboutToBeDeleted();
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    this.__enable.aboutToBeDeleted();
    this.__colorOptions.aboutToBeDeleted();
    this.__progressButtonRadius.aboutToBeDeleted();
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
  set progress(d1) {
    this.__progress.set(d1);
  }
  get textProgress() {
    return this.__textProgress.get();
  }
  set textProgress(c1) {
    this.__textProgress.set(c1);
  }
  get content() {
    return this.__content.get();
  }
  set content(b1) {
    this.__content.set(b1);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(a1) {
    this.__isLoading.set(a1);
  }
  get enable() {
    return this.__enable.get();
  }
  set enable(z) {
    this.__enable.set(z);
  }
  get colorOptions() {
    return this.__colorOptions.get();
  }
  set colorOptions(y) {
    this.__colorOptions.set(y);
  }
  get progressButtonRadius() {
    return this.__progressButtonRadius.get();
  }
  set progressButtonRadius(x) {
    this.__progressButtonRadius.set(x);
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
  get textHeight() {
    return this.__textHeight.get();
  }
  set textHeight(t) {
    this.__textHeight.set(t);
  }
  get buttonBorderRadius() {
    return this.__buttonBorderRadius.get();
  }
  set buttonBorderRadius(s) {
    this.__buttonBorderRadius.set(s);
  }
  onWillApplyTheme(r) {
    this.progressColor = r.colors.compEmphasizeSecondary;
    this.containerBorderColor = r.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = r.colors.iconOnFourth;
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
  getProgressButtonRadius() {
    if (!this.progressButtonRadius || this.progressButtonRadius.unit === LengthUnit.PERCENT) {
      return LengthMetrics.vp(this.buttonBorderRadius);
    }
    else if (this.progressButtonRadius.value < 0) {
      return LengthMetrics.vp(0);
    }
    else {
      return this.progressButtonRadius;
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
  toLengthString(o) {
    if (o === void (0)) {
      return '';
    }
    const p = o.value;
    let q = '';
    switch (o.unit) {
      case LengthUnit.PX:
        q = `${p}px`;
        break;
      case LengthUnit.FP:
        q = `${p}fp`;
        break;
      case LengthUnit.LPX:
        q = `${p}lpx`;
        break;
      case LengthUnit.PERCENT:
        q = `${p * 100}%`;
        break;
      case LengthUnit.VP:
        q = `${p}vp`;
        break;
      default:
        q = `${p}vp`;
        break;
    }
    return q;
  }
  initialRender() {
    this.observeComponentCreation2((m, n) => {
      Button.createWithChild();
      Button.borderRadius(this.progressButtonRadius ? this.toLengthString(this.getProgressButtonRadius()) :
      this.buttonBorderRadius);
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
      Progress.style({
        borderColor: this.colorOptions?.borderColor ? this.colorOptions?.borderColor : this.containerBorderColor,
        borderRadius: this.getProgressButtonRadius()
      });
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
      Row.borderRadius(this.progressButtonRadius ? this.toLengthString(this.getProgressButtonRadius()) :
      this.buttonBorderRadius);
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