/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (g1, h1, i1, j1) {
  var k1 = arguments.length, l1 = k1 < 3 ? h1 : j1 === null ? j1 = Object.getOwnPropertyDescriptor(h1, i1) : j1, m1;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    l1 = Reflect.decorate(g1, h1, i1, j1);
  else
    for (var n1 = g1.length - 1; n1 >= 0; n1--)
      if (m1 = g1[n1])
        l1 = (k1 < 3 ? m1(l1) : k1 > 3 ? m1(h1, i1, l1) : m1(h1, i1)) || l1;
  return k1 > 3 && l1 && Object.defineProperty(h1, i1, l1), l1;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
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
export class ProgressButtonV2 extends ViewV2 {
  constructor(y, z, a1, b1 = -1, c1, d1) {
    super(y, b1, d1);
    this.initParam("progress", (z && "progress" in z) ? z.progress : undefined);
    this.textProgress = EMPTY_STRING;
    this.initParam("content", (z && "content" in z) ? z.content : EMPTY_STRING);
    this.isLoading = false;
    this.initParam("progressButtonWidth", (z && "progressButtonWidth" in z) ? z.progressButtonWidth : LengthMetrics.vp(BUTTON_NORMARL_WIDTH));
    this.initParam("onClicked", (z && "onClicked" in z) ? z.onClicked : () => { });
    this.initParam("enable", (z && "enable" in z) ? z.enable : true);
    this.initParam("colorOptions", (z && "colorOptions" in z) ? z.colorOptions : undefined);
    this.progressColor = '#330A59F7';
    this.containerBorderColor = '#330A59F7';
    this.containerBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.textHeight = BUTTON_NORMARL_HEIGHT;
    this.buttonBorderRadius = BUTTON_BORDER_RADIUS;
    this.finalizeConstruction();
  }
  onWillApplyTheme(x) {
    this.progressColor = x.colors.compEmphasizeSecondary;
    this.containerBorderColor = x.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = x.colors.iconOnFourth;
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
    this.observeComponentCreation2((u, v) => {
      Button.createWithChild();
      Button.borderRadius(this.buttonBorderRadius);
      Button.clip(false);
      Button.hoverEffect(HoverEffect.None);
      Button.key(PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY);
      Button.backgroundColor(this.colorOptions?.backgroundColor?.color
        ? this.colorOptions?.backgroundColor?.color
        : this.containerBackgroundColor);
      Button.padding({ top: 0, bottom: 0 });
      Button.width(this.toLengthString(this.progressButtonWidth));
      Button.constraintSize({ minWidth: BUTTON_NORMARL_WIDTH });
      Button.stateEffect(this.enable);
      Button.onClick(() => {
        if (!this.enable) {
          return;
        }
        if (this.progress < MAX_PROGRESS) {
          this.isLoading = !this.isLoading;
        }
        this.onClicked && this.onClicked();
      });
    }, Button);
    this.observeComponentCreation2((s, t) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((q, r) => {
      Progress.create({ value: this.getButtonProgress(), total: MAX_PROGRESS,
        style: ProgressStyle.Capsule });
      Progress.height(this.textHeight);
      Progress.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Progress.borderRadius(this.buttonBorderRadius);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.clip(false);
      Progress.enabled(this.enable);
      Progress.key(PROGRESS_BUTTON_PROGRESS_KEY);
      Progress.color(this.colorOptions?.progressColor?.color ? this.colorOptions?.progressColor?.color : this.progressColor);
    }, Progress);
    this.observeComponentCreation2((o, p) => {
      Row.create();
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
    }, Row);
    this.observeComponentCreation2((j, k) => {
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.key(PROGRESS_BUTTON_PRIMARY_FONT_KEY);
      Text.fontColor(this.colorOptions?.textColor?.color);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({ top: 4, left: 8, right: 8, bottom: 4 });
      Text.opacity(this.enable ? TEXT_ENABLE : TEXT_OPACITY);
      Text.onAreaChange((m, n) => {
        if (!n.height || n.height === this.textHeight) {
          return;
        }
        this.textHeight = n.height > BUTTON_NORMARL_HEIGHT ? n.height : BUTTON_NORMARL_HEIGHT;
        this.buttonBorderRadius = Number(this.textHeight) / 2;
      });
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((h, i) => {
      Row.create();
      Row.key(PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY);
      Row.backgroundColor(Color.Transparent);
      Row.border({
        width: 1,
        color: this.colorOptions?.borderColor?.color ? this.colorOptions?.borderColor?.color : this.containerBorderColor
      });
      Row.height(this.textHeight);
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Row.borderRadius(this.buttonBorderRadius);
      Row.width('100%');
    }, Row);
    Row.pop();
    Stack.pop();
    Button.pop();
  }
  toLengthString(b) {
    if (b === void (0)) {
      return '';
    }
    const c = b.value;
    let d = '';
    switch (b.unit) {
      case LengthUnit.PX:
        d = `${c}px`;
        break;
      case LengthUnit.FP:
        d = `${c}fp`;
        break;
      case LengthUnit.LPX:
        d = `${c}lpx`;
        break;
      case LengthUnit.PERCENT:
        d = `${c * 100}%`;
        break;
      case LengthUnit.VP:
        d = `${c}vp`;
        break;
      default:
        d = `${c}vp`;
        break;
    }
    return d;
  }
  updateStateVars(a) {
    if (a === undefined) {
      return;
    }
    if ("progress" in a) {
      this.updateParam("progress", a.progress);
    }
    if ("content" in a) {
      this.updateParam("content", a.content);
    }
    if ("progressButtonWidth" in a) {
      this.updateParam("progressButtonWidth", a.progressButtonWidth);
    }
    if ("onClicked" in a) {
      this.updateParam("onClicked", a.onClicked);
    }
    if ("enable" in a) {
      this.updateParam("enable", a.enable);
    }
    if ("colorOptions" in a) {
      this.updateParam("colorOptions", a.colorOptions);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ProgressButtonV2.prototype, "progress", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "textProgress", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "content", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "isLoading", void 0);
__decorate([
  Param,
  Once
], ProgressButtonV2.prototype, "progressButtonWidth", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "onClicked", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "enable", void 0);
__decorate([
    Param
], ProgressButtonV2.prototype, "colorOptions", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "progressColor", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "containerBorderColor", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "containerBackgroundColor", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "textHeight", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "buttonBorderRadius", void 0);
__decorate([
  Monitor('progress')
], ProgressButtonV2.prototype, "getProgressContext", null);
__decorate([
  Monitor('isLoading')
], ProgressButtonV2.prototype, "getLoadingProgress", null);
let ProgressButtonV2Color = class ProgressButtonV2Color {
    constructor(e) {
        this.progressColor = e.progressColor;
        this.borderColor = e.borderColor;
        this.textColor = e.textColor;
        this.backgroundColor = e.backgroundColor;
    }
};
__decorate([
    Trace
], ProgressButtonV2Color.prototype, "progressColor", void 0);
__decorate([
    Trace
], ProgressButtonV2Color.prototype, "borderColor", void 0);
__decorate([
    Trace
], ProgressButtonV2Color.prototype, "textColor", void 0);
__decorate([
    Trace
], ProgressButtonV2Color.prototype, "backgroundColor", void 0);
ProgressButtonV2Color = __decorate([
    ObservedV2
], ProgressButtonV2Color);

export default { ProgressButtonV2,ProgressButtonV2Color };