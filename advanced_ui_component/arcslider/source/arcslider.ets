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

import animator, { AnimatorResult } from '@ohos.animator';
import { common2D, drawing } from '@kit.ArkGraphics2D';
import { vibrator } from '@kit.SensorServiceKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { ColorMetrics } from '@ohos.arkui.node';
import hilog from '@ohos.hilog'

const ANGULAR_TO_RADIAN = Math.PI / 180;
const RADIAN_TO_ANGULAR = 180 / Math.PI;
const PI_RADIAN = 180;
const TWO_PI_RADIAN = 360;
const ANGLE_OVER_MIN = 10;
const LENGTH_OVER_MIN = 0.15;
const APPROXIMATE_NUMBER = Math.pow(10, -7);
const TOTAL_LENGTH = 233;

const VALUE_DEFAULT = 0;
const MIN_DEFAULT = 0;
const MAX_DEFAULT = 100;
const X_DEFAULT = 116.5;
const Y_DEFAULT = 116.5;
const RADIUS_DEFAULT = 116.5;
const PADDING_DEFAULT = 5.5;
const START_ANGLE_DEFAULT = 15;
const END_ANGLE_DEFAULT = 45;
const ACTIVE_START_ANGLE_DEFAULT = -60;
const ACTIVE_END_ANGLE_DEFAULT = 60;
const REVERSE_DEFAULT = true;
const TRACK_THICKNESS_DEFAULT = 5;
const ACTIVE_TRACK_THICKNESS_DEFAULT = 24;
const TRACK_COLOR_DEFAULT = '#33FFFFFF';
const TRACK_BLUR_DEFAULT = 20;
const SELECTED_COLOR_DEFAULT = '#FF5EA1FF';
const BLUR_COLOR_DEFAULT = '#00ffffff';

const MIN_STATUS = 'min';
const MAX_STATUS = 'max';
const NORMAL_STATUS = 'normal';
const VIBRATOR_TYPE_TWO = 'watchhaptic.crown.strength2';
const VIBRATOR_TYPE_SIX = 'watchhaptic.crown.strength6';
const CROWN_EVENT_FLAG = 30;
const CROWN_CONTROL_RATIO = 2.10;
const CROWN_SENSITIVITY_LOW = 0.5;
const CROWN_SENSITIVITY_MEDIUM = 1;
const CROWN_SENSITIVITY_HIGH = 2;
const INVALID_TIMEOUT_ID = -1;
const RESTORE_TIMEOUT = 3000;

export interface ArcSliderValueOptionsConstructorOptions {
  value?: number;
  min?: number;
  max?: number;
}

@ObservedV2
export class ArcSliderValueOptions {
  @Trace value?: number = VALUE_DEFAULT;
  @Trace min?: number = MIN_DEFAULT;
  @Trace max?: number = MAX_DEFAULT;

  constructor(options?: ArcSliderValueOptionsConstructorOptions) {
    if (options) {
      if (options.value !== undefined && options.value !== null) {
        this.value = options.value;
      }
      if (options.min !== undefined && options.min !== null) {
        this.min = options.min;
      }
      if (options.max !== undefined && options.max !== null) {
        this.max = options.max;
      }
    }
  }
}

export interface ArcSliderLayoutOptionsConstructorOptions {
  x?: number;
  y?: number;
  radius?: number;
  padding?: number;
  startAngle?: number;
  endAngle?: number;
  activeStartAngle?: number;
  activeEndAngle?: number;
  reverse?: boolean;
}

@ObservedV2
export class ArcSliderLayoutOptions {
  @Trace x?: number = X_DEFAULT;
  @Trace y?: number = Y_DEFAULT;
  @Trace radius?: number = RADIUS_DEFAULT;
  @Trace padding?: number = PADDING_DEFAULT;
  @Trace startAngle?: number = START_ANGLE_DEFAULT;
  @Trace endAngle?: number = END_ANGLE_DEFAULT;
  @Trace activeStartAngle?: number = ACTIVE_START_ANGLE_DEFAULT;
  @Trace activeEndAngle?: number = ACTIVE_END_ANGLE_DEFAULT;
  @Trace reverse?: boolean = REVERSE_DEFAULT;

  constructor(options?: ArcSliderLayoutOptionsConstructorOptions) {
    if (options) {
      if (options.x !== undefined && options.x !== null) {
        this.x = options.x;
      }
      if (options.y !== undefined && options.y !== null) {
        this.y = options.y;
      }
      if (options.radius !== undefined && options.radius !== null) {
        this.radius = options.radius;
      }
      if (options.padding !== undefined && options.padding !== null) {
        this.padding = options.padding;
      }
      if (options.startAngle !== undefined && options.startAngle !== null) {
        this.startAngle = options.startAngle;
      }
      if (options.endAngle !== undefined && options.endAngle !== null) {
        this.endAngle = options.endAngle;
      }
      if (options.activeStartAngle !== undefined && options.activeStartAngle !== null) {
        this.activeStartAngle = options.activeStartAngle;
      }
      if (options.activeEndAngle !== undefined && options.activeEndAngle !== null) {
        this.activeEndAngle = options.activeEndAngle;
      }
      if (options.reverse !== undefined && options.reverse !== null) {
        this.reverse = options.reverse;
      }
    }
  }
}

export interface ArcSliderStyleOptionsConstructorOptions {
  trackThickness?: number;
  activeTrackThickness?: number;
  trackColor?: string;
  selectedColor?: string;
  trackBlur?: number;
}

@ObservedV2
export class ArcSliderStyleOptions {
  @Trace trackThickness?: number = TRACK_THICKNESS_DEFAULT;
  @Trace activeTrackThickness?: number = ACTIVE_TRACK_THICKNESS_DEFAULT;
  @Trace trackColor?: string = TRACK_COLOR_DEFAULT;
  @Trace selectedColor?: string = SELECTED_COLOR_DEFAULT;
  @Trace trackBlur?: number = TRACK_BLUR_DEFAULT;

  constructor(options?: ArcSliderStyleOptionsConstructorOptions) {
    if (options) {
      if (options.trackThickness !== undefined && options.trackThickness !== null) {
        this.trackThickness = options.trackThickness;
      }
      if (options.activeTrackThickness !== undefined && options.activeTrackThickness !== null) {
        this.activeTrackThickness = options.activeTrackThickness;
      }
      if (options.trackColor !== undefined && options.trackColor !== null) {
        this.trackColor = options.trackColor;
      }
      if (options.selectedColor !== undefined && options.selectedColor !== null) {
        this.selectedColor = options.selectedColor;
      }
      if (options.trackBlur !== undefined && options.trackBlur !== null) {
        this.trackBlur = options.trackBlur;
      }
    }
  }
}

export interface ArcSliderOptionsConstructorOptions {
  valueOptions?: ArcSliderValueOptions;
  layoutOptions?: ArcSliderLayoutOptions;
  styleOptions?: ArcSliderStyleOptions;
  digitalCrownSensitivity?: CrownSensitivity;
  onTouch?: Callback<TouchEvent>;
  onChange?: Callback<number>;
}

@ObservedV2
export class ArcSliderOptions {
  @Trace valueOptions?: ArcSliderValueOptions = new ArcSliderValueOptions();
  @Trace layoutOptions?: ArcSliderLayoutOptions = new ArcSliderLayoutOptions();
  @Trace styleOptions?: ArcSliderStyleOptions = new ArcSliderStyleOptions();
  @Trace digitalCrownSensitivity?: CrownSensitivity = CrownSensitivity.MEDIUM;
  @Trace onTouch?: Callback<TouchEvent> = (event: TouchEvent) => {
  };
  @Trace onChange?: Callback<number> = (value: number) => {
  };

  constructor(options?: ArcSliderOptionsConstructorOptions) {
    if (options) {
      if (options.valueOptions !== undefined && options.valueOptions !== null) {
        this.valueOptions = options.valueOptions;
      }
      if (options.layoutOptions !== undefined && options.layoutOptions !== null) {
        this.layoutOptions = options.layoutOptions;
      }
      if (options.styleOptions !== undefined && options.styleOptions !== null) {
        this.styleOptions = options.styleOptions;
      }
      if (options.digitalCrownSensitivity !== undefined && options.digitalCrownSensitivity !== null) {
        this.digitalCrownSensitivity = options.digitalCrownSensitivity;
      }
      if (options.onTouch !== undefined && options.onTouch !== null) {
        this.onTouch = options.onTouch;
      }
      if (options.onChange !== undefined && options.onChange !== null) {
        this.onChange = options.onChange;
      }
    }
  }
}

class DrawParameters {
  lineWidth: number = 0;
  normalRadius: number = 0;
  start: number = 0;
  end: number = 0;
  trackStart: number = 0;
  selectArc: number = 0;
  trackColor: ColorMetrics = ColorMetrics.resourceColor(TRACK_COLOR_DEFAULT);
  selectedColor: ColorMetrics = ColorMetrics.resourceColor(SELECTED_COLOR_DEFAULT);
  reverse: boolean = REVERSE_DEFAULT;
  x: number = X_DEFAULT;
  y: number = Y_DEFAULT;
  blur: number = TRACK_BLUR_DEFAULT;
  uiContext: UIContext | undefined = undefined;

  constructor() {}
}

function checkApprox(num1: number, num2: number): boolean {
  return Math.abs(num1 - num2) < APPROXIMATE_NUMBER;
}

class MyFullDrawModifier extends DrawModifier {
  parameters: DrawParameters = new DrawParameters();

  constructor(parameters: DrawParameters) {
    super();
    this.parameters = parameters;
  }

  parseColorString(color: ColorMetrics): common2D.Color {
    return {alpha: color.alpha, red: color.red, green: color.green, blue: color.blue};
  }

  drawTrack(context: DrawContext) {
    if (this.parameters.uiContext === undefined) {
      hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
      return;
    }
    const canvas = context.canvas;
    const pen = new drawing.Pen();
    pen.setAntiAlias(true);
    pen.setColor(this.parseColorString(this.parameters.trackColor));
    pen.setStrokeWidth(this.parameters.uiContext.vp2px(this.parameters.lineWidth));
    pen.setCapStyle(drawing.CapStyle.ROUND_CAP);
    canvas.attachPen(pen);
    let path = new drawing.Path();
    if (this.parameters.reverse) {
      if (this.parameters.start < this.parameters.end) {
        path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
          this.parameters.end * RADIAN_TO_ANGULAR,
          TWO_PI_RADIAN + (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR);
      } else {
        path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
          this.parameters.end * RADIAN_TO_ANGULAR,
          (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR);
      }
    } else {
      if (this.parameters.start < this.parameters.end) {
        path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
          this.parameters.end * RADIAN_TO_ANGULAR,
          (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR);
      } else {
        path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
          this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
          this.parameters.trackStart * RADIAN_TO_ANGULAR,
          TWO_PI_RADIAN + (this.parameters.end - this.parameters.trackStart) * RADIAN_TO_ANGULAR);
      }
    }
    canvas.drawPath(path);
    canvas.detachPen();
  }

  drawSelect(context: DrawContext) {
    if (this.parameters.uiContext === undefined) {
      hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
      return;
    }
    if (!checkApprox(this.parameters.start, this.parameters.selectArc)) {
      const canvas = context.canvas;
      const pen = new drawing.Pen();
      pen.setAntiAlias(true);
      pen.setColor(this.parseColorString(this.parameters.selectedColor));
      pen.setStrokeWidth(this.parameters.uiContext.vp2px(this.parameters.lineWidth));
      pen.setCapStyle(drawing.CapStyle.ROUND_CAP);
      canvas.attachPen(pen);
      let path = new drawing.Path();
      if (this.parameters.reverse) {
        if (this.parameters.start < this.parameters.end) {
          path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
            this.parameters.selectArc * RADIAN_TO_ANGULAR,
            (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR);
        } else {
          path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
            this.parameters.selectArc * RADIAN_TO_ANGULAR,
            (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR);
        }
      } else {
        if (this.parameters.start < this.parameters.end) {
          path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
            this.parameters.selectArc * RADIAN_TO_ANGULAR,
            (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR);
        } else {
          path.arcTo(this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius),
            this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius),
            this.parameters.start * RADIAN_TO_ANGULAR,
            (this.parameters.selectArc - this.parameters.start) * RADIAN_TO_ANGULAR);
        }
      }
      canvas.drawPath(path);
      canvas.detachPen();
    }
  }

  drawContent(context: DrawContext): void {
    this.drawTrack(context);
  }

  drawFront(context: DrawContext): void {
    this.drawSelect(context);
  }
}

@Component
export struct ArcSlider {
  options: ArcSliderOptions = new ArcSliderOptions();
  parameters: DrawParameters = new DrawParameters();
  private fullModifier: MyFullDrawModifier = new MyFullDrawModifier(this.parameters);
  private touchAnimator: AnimatorResult | undefined = undefined;
  private restoreAnimator: AnimatorResult | undefined = undefined;
  private clickSelectedAnimator: AnimatorResult | undefined = undefined;
  private maxRestoreAnimator: AnimatorResult | undefined = undefined;
  private minRestoreAnimator: AnimatorResult | undefined = undefined;
  private delta: number = 0;
  private crownDeltaAngle: number = 0;
  private lineWidth: number = 0;
  private lineWidthCurrent: number = 0;
  private normalRadius: number = 0;
  private touchY: number = 0;
  private endCurrent: number = 0;
  private meter: number = 0;
  private start: number = 0;
  private end: number = 0;
  private trackStart: number = 0;
  private trackStartCurrent: number = 0;
  private selectArc: number = 0;
  private selectArcCurrent: number = 0;
  private selectRatioNow: number = 0;
  private isEnlarged: boolean = false;
  private isTouchAnimatorFinished: boolean = false;
  private isClickAnimatorFinished: boolean = false;
  private clickValue: number = 0;
  private sliderValue: number = 0;
  private startAngle: number = -START_ANGLE_DEFAULT;
  private endAngle: number = -END_ANGLE_DEFAULT;
  private activeStartAngle: number = -ACTIVE_START_ANGLE_DEFAULT;
  private activeEndAngle: number = -ACTIVE_END_ANGLE_DEFAULT;
  private selectedMaxOrMin: string = NORMAL_STATUS;
  private totalWidth: number = TOTAL_LENGTH;
  private totalHeight: number = TOTAL_LENGTH;
  private isFocus: boolean = false;
  private needVibrate: boolean = true;
  private crownEventCounter: number = 0;
  @State clipPath: string = '';
  @State sweepFlag: boolean = false;
  @State largeArcFlag: boolean = false;

  aboutToAppear() {
    this.updateArcSlider();
  }

  private checkParam() {
    if (this.options.valueOptions!.max! <= this.options.valueOptions!.min!) {
      this.options.valueOptions!.max! = MAX_DEFAULT;
      this.options.valueOptions!.min! = MIN_DEFAULT;
    }
    if (this.options.valueOptions!.value! >= this.options.valueOptions!.max!) {
      this.options.valueOptions!.value! = this.options.valueOptions!.max!;
    }
    if (this.options.valueOptions!.value! <= this.options.valueOptions!.min!) {
      this.options.valueOptions!.value! = this.options.valueOptions!.min!;
    }
    if (this.options.layoutOptions!.startAngle! >= PI_RADIAN) {
      this.options.layoutOptions!.startAngle! = PI_RADIAN;
    }
    if (this.options.layoutOptions!.startAngle! <= -PI_RADIAN) {
      this.options.layoutOptions!.startAngle! = -PI_RADIAN;
    }
    if (this.options.layoutOptions!.endAngle! >= PI_RADIAN) {
      this.options.layoutOptions!.endAngle! = PI_RADIAN;
    }
    if (this.options.layoutOptions!.endAngle! <= -PI_RADIAN) {
      this.options.layoutOptions!.endAngle! = -PI_RADIAN;
    }
    if (this.options.layoutOptions!.activeStartAngle! >= PI_RADIAN) {
      this.options.layoutOptions!.activeStartAngle! = PI_RADIAN;
    }
    if (this.options.layoutOptions!.activeStartAngle! <= -PI_RADIAN) {
      this.options.layoutOptions!.activeStartAngle! = -PI_RADIAN;
    }
    if (this.options.layoutOptions!.activeEndAngle! >= PI_RADIAN) {
      this.options.layoutOptions!.activeEndAngle! = PI_RADIAN;
    }
    if (this.options.layoutOptions!.activeEndAngle! <= -PI_RADIAN) {
      this.options.layoutOptions!.activeEndAngle! = -PI_RADIAN;
    }
    this.startAngle = -this.options.layoutOptions!.startAngle!;
    this.endAngle = -this.options.layoutOptions!.endAngle!;
    this.activeStartAngle = -this.options.layoutOptions!.activeStartAngle!;
    this.activeEndAngle = -this.options.layoutOptions!.activeEndAngle!;
    if (this.options.layoutOptions!.padding! < 0) {
      this.options.layoutOptions!.padding! = PADDING_DEFAULT;
    }
    if (this.options.layoutOptions!.radius! < 0) {
      this.options.layoutOptions!.radius! = RADIUS_DEFAULT;
    }
    if (this.options.styleOptions!.trackThickness! <= 0) {
      this.options.styleOptions!.trackThickness! = TRACK_THICKNESS_DEFAULT;
    }
    if (this.options.styleOptions!.activeTrackThickness! <= 0) {
      this.options.styleOptions!.activeTrackThickness! = ACTIVE_TRACK_THICKNESS_DEFAULT;
    }
    if (this.options.styleOptions!.trackBlur! < 0) {
      this.options.styleOptions!.trackBlur! = TRACK_BLUR_DEFAULT;
    }
  }

  private updateModifier() {
    this.fullModifier.parameters.lineWidth = this.lineWidth;
    this.fullModifier.parameters.normalRadius = this.normalRadius;
    this.fullModifier.parameters.start = this.start;
    this.fullModifier.parameters.end = this.end;
    this.fullModifier.parameters.trackStart = this.trackStart;
    this.fullModifier.parameters.selectArc = this.selectArc;
    this.fullModifier.parameters.trackColor = ColorMetrics.resourceColor(this.options.styleOptions!.trackColor!);
    this.fullModifier.parameters.selectedColor = ColorMetrics.resourceColor(this.options.styleOptions!.selectedColor!);
    this.fullModifier.parameters.reverse = this.options.layoutOptions!.reverse!;
    this.fullModifier.parameters.x = this.options.layoutOptions!.x!;
    this.fullModifier.parameters.y = this.options.layoutOptions!.y!;
    this.fullModifier.parameters.blur = this.options.styleOptions!.trackBlur!;
    this.fullModifier.parameters.uiContext = this.getUIContext();
  }

  private updateArcSlider(): number {
    this.checkParam();
    this.setReverse();
    if (this.isEnlarged == false) {
      this.setNormal();
    } else {
      this.setSelected();
    }
    this.updateModifier();
    this.fullModifier.invalidate();
    return this.totalWidth;
  }

  setReverse() {
    if (!this.options.layoutOptions!.reverse!) {
      let startAngleInitial = this.startAngle;
      let endAngleInitial = this.endAngle;
      let activeStartAngleInitial = this.activeStartAngle;
      let activeEndAngleInitial = this.activeEndAngle;
      this.startAngle = endAngleInitial;
      this.endAngle = startAngleInitial;
      this.activeStartAngle = activeEndAngleInitial;
      this.activeEndAngle = activeStartAngleInitial;
    }
  }

  setNormal() {
    this.lineWidth = this.options.styleOptions!.trackThickness!;
    this.start = this.startAngle * ANGULAR_TO_RADIAN;
    this.end = this.endAngle * ANGULAR_TO_RADIAN;
    this.trackStart = this.startAngle * ANGULAR_TO_RADIAN;
    let selectRatio = (this.options.valueOptions!.value! - this.options.valueOptions!.min!) /
      (this.options.valueOptions!.max! - this.options.valueOptions!.min!);
    if (this.end > this.start) {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = this.start - selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
      } else {
        this.selectArc = this.start + selectRatio * Math.abs(this.end - this.start);
      }
    } else {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = this.start - selectRatio * Math.abs(this.end - this.start);
      } else {
        this.selectArc = this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
      }
    }
    this.normalRadius = this.options.layoutOptions!.radius! - (this.lineWidth / 2) -
      this.options.layoutOptions!.padding!;
    this.calBlurNormal();
  }

  setSelected() {
    let selectRatio = (this.options.valueOptions!.value! - this.options.valueOptions!.min!) /
      (this.options.valueOptions!.max! - this.options.valueOptions!.min!);
    if (this.end > this.start) {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = this.start - selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
      } else {
        this.selectArc = this.start + selectRatio * Math.abs(this.end - this.start);
      }
    } else {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = this.start - selectRatio * Math.abs(this.end - this.start);
      } else {
        this.selectArc = this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
      }
    }
    this.normalRadius = this.options.layoutOptions!.radius! - (this.lineWidth / 2);
    this.calBlurSelected();
  }

  calBlurNormal() {
    if (this.parameters.reverse) {
      if (this.trackStart > this.end) {
        if (this.trackStart - this.end > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = false
        } else {
          this.largeArcFlag = false
          this.sweepFlag = false
        }
      } else {
        if (2 * Math.PI + this.trackStart - this.end > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = false
        } else {
          this.largeArcFlag = false
          this.sweepFlag = false
        }
      }
    } else {
      if (this.trackStart > this.end) {
        if (2 * Math.PI + this.end - this.trackStart > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = true
        } else {
          this.largeArcFlag = false
          this.sweepFlag = true
        }
      } else {
        if (this.end - this.trackStart > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = true
        } else {
          this.largeArcFlag = false
          this.sweepFlag = true
        }
      }
    }
    if (this.parameters.uiContext!) {
      this.clipPath = 'M' + JSON.stringify(1.5 * (this.parameters.x + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' + JSON.stringify(1.5 *
        (this.parameters.y + (this.parameters.normalRadius - this.parameters.lineWidth / 2) *
        Math.sin(this.parameters.trackStart))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' 0' + ' 1' + ' ' +
      JSON.stringify(Number(this.sweepFlag)) + ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius + this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius + this.parameters.lineWidth / 2)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius + this.parameters.lineWidth /
        2)) + ' 0' + ' ' + JSON.stringify(Number(this.largeArcFlag)) + ' ' + JSON.stringify(Number(this.sweepFlag)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius +
        this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' 0' + ' 1' + ' ' +
      JSON.stringify(Number(this.sweepFlag)) + ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius - this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth / 2)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth /
        2)) + ' 180' + ' ' + JSON.stringify(Number(this.largeArcFlag)) + ' ' + JSON.stringify(Number(!this.sweepFlag)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart)))
    }
  }

  calBlurSelected() {
    if (this.parameters.reverse) {
      if (this.trackStart > this.end) {
        if (this.trackStart - this.end > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = false
        } else {
          this.largeArcFlag = false
          this.sweepFlag = false
        }
      } else {
        if (2 * Math.PI + this.trackStart - this.end > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = false
        } else {
          this.largeArcFlag = false
          this.sweepFlag = false
        }
      }
    } else {
      if (this.trackStart > this.end) {
        if (2 * Math.PI + this.end - this.trackStart > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = true
        } else {
          this.largeArcFlag = false
          this.sweepFlag = true
        }
      } else {
        if (this.end - this.trackStart > Math.PI) {
          this.largeArcFlag = true
          this.sweepFlag = true
        } else {
          this.largeArcFlag = false
          this.sweepFlag = true
        }
      }
    }
    if (this.parameters.uiContext!) {
      this.clipPath = 'M' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius - this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth) / 2) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth) / 2) + ' 0' + ' 1' + ' ' +
      JSON.stringify(Number(this.sweepFlag)) + ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius + this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius + this.parameters.lineWidth / 2)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius +
        this.parameters.lineWidth / 2)) + ' 0' + ' ' + JSON.stringify(Number(this.largeArcFlag)) + ' ' +
      JSON.stringify(Number(this.sweepFlag)) + ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius + this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth) / 2) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.lineWidth) / 2) + ' 0' + ' 0' + ' ' +
      JSON.stringify(Number(this.sweepFlag)) + ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x +
        (this.parameters.normalRadius - this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth / 2)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth /
        2)) + ' 180' + ' ' + JSON.stringify(Number(this.largeArcFlag)) + ' ' + JSON.stringify(Number(!this.sweepFlag)) +
        ' ' + JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
      JSON.stringify(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
        this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart)))
    }
  }

  startTouchAnimator() {
    this.touchAnimator = animator.create({
      duration: 200,
      easing: 'friction',
      delay: 0,
      fill: 'forwards',
      direction: NORMAL_STATUS,
      iterations: 1,
      begin: 0,
      end: 1
    })
    this.touchAnimator.onFrame = (value: number) => {
      this.lineWidth = value * (this.options.styleOptions!.activeTrackThickness! -
        this.options.styleOptions!.trackThickness!) + this.options.styleOptions!.trackThickness!;
      this.start = (value * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
      this.trackStart = (value * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
      this.end = (value * (this.activeEndAngle - this.endAngle) + this.endAngle) * ANGULAR_TO_RADIAN;
      this.setSelected();
      this.updateModifier();
      this.fullModifier.invalidate();
      this.calBlurNormal();
    }
    this.touchAnimator.onFinish = () => {
      this.isTouchAnimatorFinished = true;
      this.endCurrent = this.end;
    }
    if (this.touchAnimator) {
      this.touchAnimator.play();
    }
  }

  startMaxRestoreAnimator() {
    this.maxRestoreAnimator = animator.create({
      duration: 333,
      easing: 'sharp',
      delay: 0,
      fill: 'forwards',
      direction: NORMAL_STATUS,
      iterations: 1,
      begin: 0,
      end: 1
    })
    this.maxRestoreAnimator.onFrame = (value: number) => {
      this.lineWidth = value * (this.options.styleOptions!.activeTrackThickness! - this.lineWidthCurrent) +
      this.lineWidthCurrent;
      this.selectArc = value * (this.endCurrent - this.selectArcCurrent) + this.selectArcCurrent;
      this.end = this.selectArc;
      this.updateModifier();
      this.fullModifier.invalidate();
      this.calBlurSelected();
    }
    if (this.maxRestoreAnimator) {
      this.maxRestoreAnimator.play();
    }
  }

  startMinRestoreAnimator() {
    this.minRestoreAnimator = animator.create({
      duration: 333,
      easing: 'sharp',
      delay: 0,
      fill: 'forwards',
      direction: NORMAL_STATUS,
      iterations: 1,
      begin: 0,
      end: 1
    })
    this.minRestoreAnimator.onFrame = (value: number) => {
      this.lineWidth = value * (this.options.styleOptions!.activeTrackThickness! - this.lineWidthCurrent) +
      this.lineWidthCurrent;
      this.trackStart = value * (this.activeStartAngle * ANGULAR_TO_RADIAN - this.trackStartCurrent) +
      this.trackStartCurrent;
      this.updateModifier();
      this.fullModifier.invalidate();
      this.calBlurSelected();
    }
    if (this.minRestoreAnimator) {
      this.minRestoreAnimator.play();
    }
  }

  startRestoreAnimator() {
    this.restoreAnimator = animator.create({
      duration: 167,
      easing: 'friction',
      delay: 0,
      fill: 'forwards',
      direction: NORMAL_STATUS,
      iterations: 1,
      begin: 0,
      end: 1
    })
    this.restoreAnimator.onFrame = (value: number) => {
      this.lineWidth = value * (this.options.styleOptions!.trackThickness! -
        this.options.styleOptions!.activeTrackThickness!) + this.options.styleOptions!.activeTrackThickness!;
      this.start = (value * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) * ANGULAR_TO_RADIAN;
      this.trackStart = (value * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) *
        ANGULAR_TO_RADIAN;
      this.end = (value * (this.endAngle - this.activeEndAngle) + this.activeEndAngle) * ANGULAR_TO_RADIAN;
      this.setNormal();
      this.updateModifier();
      this.fullModifier.invalidate();
      this.calBlurNormal();
    }
    if (this.restoreAnimator) {
      this.restoreAnimator.play();
    }
  }

  startClickAnimator() {
    this.clickSelectedAnimator = animator.create({
      duration: 0,
      easing: 'interpolating-spring(0,1,400,38)',
      delay: 0,
      fill: 'forwards',
      direction: NORMAL_STATUS,
      iterations: 1,
      begin: this.sliderValue,
      end: this.clickValue
    })
    this.clickSelectedAnimator.onFrame = (value: number) => {
      this.options.valueOptions!.value! = value;
      this.setSelected();
      this.updateModifier();
      this.fullModifier.invalidate();
    }
    this.clickSelectedAnimator.onFinish = () => {
      this.isClickAnimatorFinished = true;
    }
    if (this.clickSelectedAnimator) {
      this.clickSelectedAnimator.play();
    }
  }

  calcClickValue(clickX: number, clickY: number) {
    if (clickY - this.options.layoutOptions!.y! > this.normalRadius) {
      clickY = this.normalRadius + this.options.layoutOptions!.y!;
    } else if (this.options.layoutOptions!.y! - clickY > this.normalRadius) {
      clickY = this.options.layoutOptions!.y! - this.normalRadius;
    }
    let sin = Math.abs(clickY - this.options.layoutOptions!.y!) / this.normalRadius;
    let radian = Math.asin(sin);
    if ((clickX < this.options.layoutOptions!.x!) && (clickY > this.options.layoutOptions!.y!)) {
      radian = Math.PI - radian;
    } else if ((clickX < this.options.layoutOptions!.x!) && (clickY < this.options.layoutOptions!.y!)) {
      radian = radian - Math.PI;
    } else if ((clickX > this.options.layoutOptions!.x!) && (clickY < this.options.layoutOptions!.y!)) {
      radian = -radian;
    }
    this.selectArc = radian;
    this.selectRatioNow = (this.selectArc - this.start) / (this.end - this.start);
    this.selectRatioNow = Math.min(1, this.selectRatioNow);
    this.selectRatioNow = Math.max(0, this.selectRatioNow);
    this.clickValue = this.selectRatioNow * (this.options.valueOptions!.max! - this.options.valueOptions!.min!) +
      this.options.valueOptions!.min!;
  }

  calcSin(radian: number): number {
    if ((radian >= Math.PI / 2) && (radian <= Math.PI)) {
      return Math.sin(radian);
    } else if ((radian <= Math.PI / 2) && (radian >= -Math.PI / 2)) {
      return 2 - Math.sin(radian);
    } else if ((radian >= -Math.PI) && (radian <= -Math.PI / 2)) {
      return 4 + Math.sin(radian);
    }
    return 0
  }

  calcValue(moveY: number) {
    this.delta = this.touchY - moveY;
    let total = this.normalRadius * (this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN) -
    this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN));
    let valueNow = (this.options.valueOptions!.value! - this.options.valueOptions!.min!) /
      (this.options.valueOptions!.max! - this.options.valueOptions!.min!);
    valueNow += this.delta / total;
    valueNow = Math.min(1, valueNow);
    valueNow = Math.max(0, valueNow);
    this.options.valueOptions!.value! = valueNow *
      (this.options.valueOptions!.max! - this.options.valueOptions!.min!) + this.options.valueOptions!.min!;
    this.setSelected();
    this.updateModifier();
    this.fullModifier.invalidate();
    this.touchY = moveY;
  }

  calcCrownTotal(activeStartAngle: number, activeEndAngle: number): number {
    if (activeEndAngle > activeStartAngle) {
      if (this.options.layoutOptions!.reverse!) {
        return (2 * PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle)) * ANGULAR_TO_RADIAN;
      } else {
        return Math.abs(activeEndAngle - activeStartAngle) * ANGULAR_TO_RADIAN;
      }
    } else {
      if (this.options.layoutOptions!.reverse!) {
        return Math.abs(activeEndAngle - activeStartAngle) * ANGULAR_TO_RADIAN;
      } else {
        return (2 * PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle)) * ANGULAR_TO_RADIAN;
      }
    }
  }

  calcCrownValue(deltaCrownAngle: number) {
    let totalAngle = this.calcCrownTotal(this.activeStartAngle, this.activeEndAngle);
    let totalValue = this.options.valueOptions!.max! - this.options.valueOptions!.min!;
    let valueNow = (this.options.valueOptions!.value! - this.options.valueOptions!.min!) / totalValue;
    valueNow += deltaCrownAngle / totalAngle;
    valueNow = Math.min(1, valueNow);
    valueNow = Math.max(0, valueNow);
    this.options.valueOptions!.value = valueNow * totalValue + this.options.valueOptions!.min!;
    if (this.options.valueOptions!.value! === this.options.valueOptions!.max! ||
      this.options.valueOptions!.value! === this.options.valueOptions!.min!) {
      if (this.needVibrate) {
        this.needVibrate = false;
        try {
          let ret = vibrator.isSupportEffectSync(VIBRATOR_TYPE_SIX);
          if (ret) {
            vibrator.startVibration({
              type: 'preset',
              effectId: VIBRATOR_TYPE_SIX,
              count: 1,
            }, {
              usage: 'unknown'
            }, (error: BusinessError) => {
              if (error) {
                hilog.error(0x3900, 'ArcSlider', `Failed to start vibration.
                  Code: ${error.code}, message: ${error.message}`);
                return;
              }
              hilog.info(0x3900, 'ArcSlider', 'Succeed in starting vibration');
            });
          } else {
            hilog.error(0x3900, 'ArcSlider', `watchhaptic.crown.strength6 is not supported`);
          }
        } catch (error) {
          let e: BusinessError = error as BusinessError;
          hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                    Code: ${e.code}, message: ${e.message}`);
        }
      }
    } else {
      this.needVibrate = true;
    }
    this.setSelected();
    this.updateModifier();
    this.fullModifier.invalidate();
  }

  calcMaxValueDeltaIsPositive() {
    if (this.options.layoutOptions!.reverse!) {
      if ((this.selectArc >= (this.endCurrent - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN)) &&
        (this.lineWidth >= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN))) {
        this.selectArc -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
        this.end = this.selectArc;
      }
      if ((this.selectArc / ANGULAR_TO_RADIAN) <= (this.endCurrent / ANGULAR_TO_RADIAN - ANGLE_OVER_MIN)) {
        this.selectArc = this.endCurrent - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
        this.end = this.selectArc;
      }
      if (this.lineWidth <= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN)) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN);
      }
    } else {
      if ((this.selectArc <= this.endCurrent) ||
        (this.lineWidth <= this.options.styleOptions!.activeTrackThickness!)) {
        this.selectArc -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
        this.end = this.selectArc;
      }
      if (this.selectArc <= this.endCurrent) {
        this.selectArc = this.endCurrent;
        this.end = this.selectArc;
      }
      if (this.lineWidth >= this.options.styleOptions!.activeTrackThickness!) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness!;
      }
    }
  }

  calcMaxValueDeltaIsNegative() {
    if (this.options.layoutOptions!.reverse!) {
      if ((this.selectArc <= this.endCurrent) ||
        (this.lineWidth <= this.options.styleOptions!.activeTrackThickness!)) {
        this.selectArc += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
        this.end = this.selectArc;
      }
      if (this.selectArc >= this.endCurrent) {
        this.selectArc = this.endCurrent;
        this.end = this.selectArc;
      }
      if (this.lineWidth >= this.options.styleOptions!.activeTrackThickness!) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness!;
      }
    } else {
      if ((this.selectArc <= (this.endCurrent + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN)) &&
        (this.lineWidth >= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN))) {
        this.selectArc += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
        this.end = this.selectArc;
      }
    }
  }

  calcMaxValue(moveY: number) {
    this.delta = this.touchY - moveY;
    if (this.delta >= 0) {
      this.calcMaxValueDeltaIsPositive();
    } else {
      this.calcMaxValueDeltaIsNegative();
    }
    this.updateModifier();
    this.fullModifier.invalidate();
    this.touchY = moveY;
    this.calBlurSelected();
  }

  calcMinValueDeltaIsNegative() {
    if (this.options.layoutOptions!.reverse!) {
      if ((this.trackStart < this.start + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) &&
        (this.lineWidth >= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN))) {
        this.trackStart += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
      }
      if ((this.trackStart / ANGULAR_TO_RADIAN) >= this.start / ANGULAR_TO_RADIAN + ANGLE_OVER_MIN) {
        this.trackStart = this.start + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
      }
      if (this.lineWidth <= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN)) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN);
      }
    } else {
      if ((this.trackStart < this.start) || (this.lineWidth <= this.options.styleOptions!.activeTrackThickness!)) {
        this.trackStart += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
      }
      if (this.trackStart > this.start) {
        this.trackStart = this.start;
      }
      if (this.lineWidth >= this.options.styleOptions!.activeTrackThickness!) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness!;
      }
    }
  }

  calcMinValueDeltaIsPositive() {
    if (this.options.layoutOptions!.reverse!) {
      if ((this.trackStart > this.start) || (this.lineWidth <= this.options.styleOptions!.activeTrackThickness!)) {
        this.trackStart -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
      }
      if (this.lineWidth > this.options.styleOptions!.activeTrackThickness!) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness!;
      }
      if (this.trackStart < this.start) {
        this.trackStart = this.start;
      }
    } else {
      if ((this.trackStart > this.start - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) &&
        (this.lineWidth >= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN))) {
        this.trackStart -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
          (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
        this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
          (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
      }
      if ((this.trackStart / ANGULAR_TO_RADIAN) <= this.start / ANGULAR_TO_RADIAN - ANGLE_OVER_MIN) {
        this.trackStart = this.start - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
      }
      if (this.lineWidth <= this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN)) {
        this.lineWidth = this.options.styleOptions!.activeTrackThickness! * (1 - LENGTH_OVER_MIN);
      }
    }
  }

  calcMinValue(moveY: number) {
    this.delta = this.touchY - moveY;
    if (this.delta <= 0) {
      this.calcMinValueDeltaIsNegative();
    } else {
      this.calcMinValueDeltaIsPositive();
    }
    this.updateModifier();
    this.fullModifier.invalidate();
    this.touchY = moveY;
    this.calBlurNormal();
  }

  isHotRegion(touchX: number, touchY: number): boolean {
    let radius = Math.sqrt(Math.pow(touchX - this.options.layoutOptions!.x!, 2) +
    Math.pow(touchY - this.options.layoutOptions!.y!, 2));
    if ((radius < this.options.layoutOptions!.radius! - this.options.styleOptions!.activeTrackThickness!) ||
      (radius > this.options.layoutOptions!.radius!)) {
      this.isFocus = false;
      return false;
    }
    let sin = Math.abs(touchY - this.options.layoutOptions!.y!) / radius;
    let radian = Math.asin(sin);
    let angle = radian / ANGULAR_TO_RADIAN;
    if ((touchX < this.options.layoutOptions!.x!) && (touchY > this.options.layoutOptions!.y!)) {
      angle = PI_RADIAN - angle;
    } else if ((touchX < this.options.layoutOptions!.x!) && (touchY < this.options.layoutOptions!.y!)) {
      angle = angle - PI_RADIAN;
    } else if ((touchX > this.options.layoutOptions!.x!) && (touchY < this.options.layoutOptions!.y!)) {
      angle = -angle;
    }
    if (this.options.layoutOptions!.reverse!) {
      if (angle > this.start / ANGULAR_TO_RADIAN || angle < this.end / ANGULAR_TO_RADIAN) {
        if (this.start > this.end) {
          this.isFocus = false;
          return false;
        } else {
          this.isFocus = true;
          return true;
        }
      } else {
        if (this.start > this.end) {
          this.isFocus = true;
          return true;
        } else {
          this.isFocus = false;
          return false;
        }
      }
    } else {
      if (angle < this.start / ANGULAR_TO_RADIAN || angle > this.end / ANGULAR_TO_RADIAN) {
        if (this.start > this.end) {
          this.isFocus = true;
          return true;
        } else {
          this.isFocus = false;
          return false;
        }
      } else {
        if (this.start > this.end) {
          this.isFocus = false;
          return false;
        } else {
          this.isFocus = true;
          return true;
        }
      }
    }
  }

  calcDisplayControlRatio(crownSensitivity: CrownSensitivity): number {
    if (crownSensitivity === CrownSensitivity.LOW) {
      return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_LOW;
    } else if (crownSensitivity === CrownSensitivity.MEDIUM) {
      return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_MEDIUM;
    } else if (crownSensitivity === CrownSensitivity.HIGH) {
      return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_HIGH;
    }
    return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_MEDIUM;
  }

  build() {
    Column() {
      Stack() {
        Circle({ width: TOTAL_LENGTH, height: TOTAL_LENGTH })
          .width(this.updateArcSlider())
          .fill(BLUR_COLOR_DEFAULT)
          .clipShape(new Path({ commands: this.clipPath }))
          .backdropBlur(TRACK_BLUR_DEFAULT)
        Button()
          .backgroundColor(BLUR_COLOR_DEFAULT)
          .drawModifier(this.fullModifier)
          .width(this.updateArcSlider())
          .height(this.totalHeight)
          .onTouch((event?: TouchEvent) => {
            if (event) {
              if (event.type === TouchType.Down && !this.isEnlarged) {
                this.touchY = event.touches[0].y;
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                  this.options.onTouch?.(event);
                  this.isEnlarged = true;
                  this.startTouchAnimator();
                  this.calBlurSelected();
                }
              } else if (event.type === TouchType.Down && this.isEnlarged) {
                this.touchY = event.touches[0].y;
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                  this.options.onTouch?.(event);
                  if (this.meter !== INVALID_TIMEOUT_ID) {
                    clearTimeout(this.meter);
                    this.meter = INVALID_TIMEOUT_ID
                  }
                  if (this.isTouchAnimatorFinished) {
                    this.sliderValue = this.options.valueOptions!.value!;
                    this.calcClickValue(event.touches[0].x, event.touches[0].y);
                    this.startClickAnimator();
                  }
                  if (this.isClickAnimatorFinished) {
                    if (this.meter !== INVALID_TIMEOUT_ID) {
                      clearTimeout(this.meter);
                      this.meter = INVALID_TIMEOUT_ID
                    }
                    this.touchY = event.touches[0].y;
                    this.calcValue(event.touches[0].y);
                    this.setSelected();
                    this.updateModifier();
                    this.fullModifier.invalidate();
                  }
                }
              } else if (this.isEnlarged && event.type === TouchType.Up) {
                this.options.onChange?.(this.options.valueOptions!.value!);
                this.options.onTouch?.(event);
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                this.meter = setTimeout(() => {
                  if (this.isEnlarged) {
                    this.isTouchAnimatorFinished = false;
                    this.isClickAnimatorFinished = false;
                    this.isEnlarged = false;
                    this.startRestoreAnimator();
                    this.calBlurNormal();
                  }
                }, RESTORE_TIMEOUT)
                if (this.options.layoutOptions!.reverse!) {
                  if (this.selectedMaxOrMin === MAX_STATUS && this.selectArc < this.endCurrent) {
                    this.lineWidthCurrent = this.lineWidth;
                    this.selectArcCurrent = this.selectArc;
                    this.startMaxRestoreAnimator();
                  }
                  if (this.selectedMaxOrMin === MIN_STATUS && this.trackStart > this.start) {
                    this.lineWidthCurrent = this.lineWidth;
                    this.trackStartCurrent = this.trackStart;
                    this.startMinRestoreAnimator();
                    this.calBlurSelected();
                  }
                } else {
                  if (this.selectedMaxOrMin === MAX_STATUS && this.selectArc > this.endCurrent) {
                    this.lineWidthCurrent = this.lineWidth;
                    this.selectArcCurrent = this.selectArc;
                    this.startMaxRestoreAnimator();
                  }
                  if (this.selectedMaxOrMin === MIN_STATUS && this.trackStart < this.start) {
                    this.lineWidthCurrent = this.lineWidth;
                    this.trackStartCurrent = this.trackStart;
                    this.startMinRestoreAnimator();
                    this.calBlurSelected();
                  }
                }
              } else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                (event.type === TouchType.Move)) {
                this.options.onTouch?.(event);
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                if (this.options.layoutOptions!.reverse!) {
                  if (((this.selectArc < this.endCurrent) || (checkApprox(this.selectArc, this.endCurrent))) &&
                    (this.delta >= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.selectArc < this.endCurrent) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.trackStart >= this.start) && (checkApprox(this.options.valueOptions!.value!,
                    this.options.valueOptions!.min!)) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                    this.calBlurSelected();
                  } else if ((this.trackStart > this.start) && (this.delta >= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                    this.calBlurSelected();
                  } else {
                    this.calcValue(event.touches[0].y);
                    this.selectedMaxOrMin = NORMAL_STATUS;
                  }
                } else {
                  if (((this.selectArc > this.endCurrent) || (checkApprox(this.selectArc, this.endCurrent))) &&
                    (this.delta <= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.selectArc > this.endCurrent) && (this.delta >= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((checkApprox(this.options.valueOptions!.value!, this.options.valueOptions!.min!)) &&
                    (this.delta >= 0) && ((this.trackStart <= this.start) ||
                    (checkApprox(this.selectArc, this.endCurrent)))) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                    this.calBlurSelected();
                  } else if ((this.trackStart < this.start) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                    this.calBlurSelected();
                  } else {
                    this.calcValue(event.touches[0].y);
                    this.selectedMaxOrMin = NORMAL_STATUS;
                  }
                }
              }
            }
          })
          .focusable(true)
          .focusOnTouch(true)
          .onDigitalCrown((event: CrownEvent) => {
            if (event && this.isFocus) {
              this.crownEventCounter += 1;
              if (this.crownEventCounter % CROWN_EVENT_FLAG === 0) {
                try {
                  let ret = vibrator.isSupportEffectSync(VIBRATOR_TYPE_TWO);
                  if (ret) {
                    vibrator.startVibration({
                      type: 'preset',
                      effectId: VIBRATOR_TYPE_TWO,
                      count: 1,
                    }, {
                      usage: 'unknown'
                    }, (error: BusinessError) => {
                      if (error) {
                        hilog.error(0x3900, 'ArcSlider', `Failed to start vibration.
                            Code: ${error.code}, message: ${error.message}`);
                        this.crownEventCounter = 0;
                        return;
                      }
                      hilog.info(0x3900, 'ArcSlider', 'Succeed in starting vibration');
                    });
                  } else {
                    hilog.error(0x3900, 'ArcSlider', `watchhaptic.crown.strength2 is not supported`);
                  }
                } catch (error) {
                  let e: BusinessError = error as BusinessError;
                  hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                      Code: ${e.code}, message: ${e.message}`);
                }
                this.crownEventCounter = 0;
              }
              if (event.action === CrownAction.BEGIN && !this.isEnlarged) {
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                this.isEnlarged = true;
                this.startTouchAnimator();
                this.calBlurSelected();
                this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                this.calcDisplayControlRatio(this.options.digitalCrownSensitivity!)) / this.normalRadius;
                this.calcCrownValue(this.crownDeltaAngle);
              } else if (event.action === CrownAction.BEGIN && this.isEnlarged) {
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                this.calcDisplayControlRatio(this.options.digitalCrownSensitivity!)) / this.normalRadius;
                this.calcCrownValue(this.crownDeltaAngle);
              } else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                (event.action === CrownAction.UPDATE)) {
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                this.calcDisplayControlRatio(this.options.digitalCrownSensitivity!)) / this.normalRadius;
                this.calcCrownValue(this.crownDeltaAngle);
              } else if (this.isEnlarged && event.action === CrownAction.END) {
                if (this.meter !== INVALID_TIMEOUT_ID) {
                  clearTimeout(this.meter);
                  this.meter = INVALID_TIMEOUT_ID
                }
                this.meter = setTimeout(() => {
                  if (this.isEnlarged) {
                    this.isTouchAnimatorFinished = false;
                    this.isClickAnimatorFinished = false;
                    this.isEnlarged = false;
                    this.startRestoreAnimator();
                    this.calBlurNormal();
                  }
                }, RESTORE_TIMEOUT)
              }
            }
          })
      }
    }.hitTestBehavior(HitTestMode.Transparent)
  }
}