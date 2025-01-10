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

var __decorate = (this && this.__decorate) || function (k1, l1, m1, n1) {
  var o1 = arguments.length, p1 = o1 < 3 ? l1 : n1 === null ? n1 = Object.getOwnPropertyDescriptor(l1, m1) : n1, q1;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    p1 = Reflect.decorate(k1, l1, m1, n1);
  else
    for (var r1 = k1.length - 1; r1 >= 0; r1--)
      if (q1 = k1[r1])
        p1 = (o1 < 3 ? q1(p1) : o1 > 3 ? q1(l1, m1, p1) : q1(l1, m1)) || p1;
  return o1 > 3 && p1 && Object.defineProperty(l1, m1, p1), p1;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const arkuiNode = requireNapi('arkui.node');
const LengthMetrics = arkuiNode.LengthMetrics;
const LengthUnit = arkuiNode.LengthUnit;
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
  constructor(c1, d1, e1, f1 = -1, g1, h1) {
    super(c1, f1, h1);
    this.initParam("progress", (d1 && "progress" in d1) ? d1.progress : undefined);
    this.initParam("content", (d1 && "content" in d1) ? d1.content : EMPTY_STRING);
    this.initParam("progressButtonWidth", (d1 && "progressButtonWidth" in d1) ? d1.progressButtonWidth : LengthMetrics.vp(BUTTON_NORMARL_WIDTH));
    this.initParam("onClicked", (d1 && "onClicked" in d1) ? d1.onClicked : () => {
    });
    this.initParam("isEnabled", (d1 && "isEnabled" in d1) ? d1.isEnabled : true);
    this.initParam("colorOptions", (d1 && "colorOptions" in d1) ? d1.colorOptions : undefined);
    this.textProgress = EMPTY_STRING;
    this.isLoading = false;
    this.progressColor = '#330A59F7';
    this.containerBorderColor = '#330A59F7';
    this.containerBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_foreground_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.textHeight = BUTTON_NORMARL_HEIGHT;
    this.buttonBorderRadius = BUTTON_BORDER_RADIUS;
    this.finalizeConstruction();
  }
  onWillApplyTheme(b1) {
    this.progressColor = b1.colors.compEmphasizeSecondary;
    this.containerBorderColor = b1.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = b1.colors.iconOnFourth;
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
      this.textProgress = `${Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS)}%`;
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
        this.textProgress = `${Math.floor(this.progress / MAX_PROGRESS * MAX_PROGRESS)}%`;
      }
    }
  }
  initialRender() {
    this.observeComponentCreation2((y, z) => {
      Button.createWithChild();
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.button_container_border_radius_small'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.clip(false);
      Button.hoverEffect(HoverEffect.None);
      Button.key(PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY);
      Button.backgroundColor(this.colorOptions?.backgroundColor?.color
        ? this.colorOptions?.backgroundColor?.color
        : this.containerBackgroundColor);
      Button.padding({ top: 0, bottom: 0 });
      Button.width(this.toLengthString(this.progressButtonWidth));
      Button.constraintSize({ minWidth: BUTTON_NORMARL_WIDTH });
      Button.stateEffect(this.isEnabled);
      Button.onClick(() => {
        if (!this.isEnabled) {
          return;
        }
        if (this.progress < MAX_PROGRESS) {
          this.isLoading = !this.isLoading;
        }
        this.onClicked?.();
      });
    }, Button);
    this.observeComponentCreation2((w, x) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((u, v) => {
      Progress.create({
        value: this.getButtonProgress(), total: MAX_PROGRESS,
        style: ProgressStyle.Capsule
      });
      Progress.height(this.textHeight);
      Progress.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Progress.borderRadius(this.buttonBorderRadius);
      Progress.width('100%');
      Progress.hoverEffect(HoverEffect.None);
      Progress.style({ borderRadius: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.button_container_border_radius_small'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
      Progress.padding({ top: 0.6, left: 0.6, right: 0.6, bottom: 0.6 });
      Progress.clip(false);
      Progress.enabled(this.isEnabled);
      Progress.key(PROGRESS_BUTTON_PROGRESS_KEY);
      Progress.color(this.colorOptions?.progressColor?.color ? this.colorOptions?.progressColor?.color : this.progressColor);
    }, Progress);
    this.observeComponentCreation2((s, t) => {
      Row.create();
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
    }, Row);
    this.observeComponentCreation2((n, o) => {
      Text.create(this.isLoading ? this.textProgress : this.content);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.key(PROGRESS_BUTTON_PRIMARY_FONT_KEY);
      Text.fontColor(this.colorOptions?.textColor?.color);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.padding({
        top: 4,
        left: 8,
        right: 8,
        bottom: 4
      });
      Text.opacity(this.isEnabled ? TEXT_ENABLE : TEXT_OPACITY);
      Text.onSizeChange((q, r) => {
        if (!r.height || r.height === this.textHeight) {
          return;
        }
        this.textHeight = r.height > BUTTON_NORMARL_HEIGHT ? r.height : BUTTON_NORMARL_HEIGHT;
        this.buttonBorderRadius = Number(this.textHeight) / 2;
      });
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((l, m) => {
      Row.create();
      Row.key(PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY);
      Row.backgroundColor(Color.Transparent);
      Row.border({
        width: 1,
        color: this.colorOptions?.borderColor?.color ?
          this.colorOptions?.borderColor?.color : this.containerBorderColor
      });
      Row.height(this.textHeight);
      Row.constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT });
      Row.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.button_container_border_radius_small'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.width('100%');
    }, Row);
    Row.pop();
    Stack.pop();
    Button.pop();
  }
  toLengthString(c) {
    if (c === void (0)) {
      return '';
    }
    const d = c.value;
    switch (c.unit) {
      case LengthUnit.PX:
        return `${d}px`;
      case LengthUnit.FP:
        return `${d}fp`;
      case LengthUnit.LPX:
        return `${d}lpx`;
      case LengthUnit.PERCENT:
        return `${d * 100}%`;
      case LengthUnit.VP:
        return `${d}vp`;
      default:
        return `${d}vp`;
    }
  }
  updateStateVars(b) {
    if (b === undefined) {
      return;
    }
    if ("progress" in b) {
      this.updateParam("progress", b.progress);
    }
    if ("content" in b) {
      this.updateParam("content", b.content);
    }
    if ("progressButtonWidth" in b) {
      this.updateParam("progressButtonWidth", b.progressButtonWidth);
    }
    if ("onClicked" in b) {
      this.updateParam("onClicked", b.onClicked);
    }
    if ("isEnabled" in b) {
      this.updateParam("isEnabled", b.isEnabled);
    }
    if ("colorOptions" in b) {
      this.updateParam("colorOptions", b.colorOptions);
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
  Param
], ProgressButtonV2.prototype, "content", void 0);
__decorate([
  Param,
  Once
], ProgressButtonV2.prototype, "progressButtonWidth", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "onClicked", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "isEnabled", void 0);
__decorate([
  Param
], ProgressButtonV2.prototype, "colorOptions", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "textProgress", void 0);
__decorate([
  Local
], ProgressButtonV2.prototype, "isLoading", void 0);
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
  constructor(a) {
    this.progressColor = a.progressColor;
    this.borderColor = a.borderColor;
    this.textColor = a.textColor;
    this.backgroundColor = a.backgroundColor;
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