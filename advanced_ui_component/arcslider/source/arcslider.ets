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

const ANGULAR_TO_RADIAN = Math.PI / 180;
const PI_RADIAN = 180;
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

const MIN_STATUS = 'min';
const MAX_STATUS = 'max';
const NORMAL_STATUS = 'normal';

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
  onTouch?: Callback<TouchEvent>;
  onChange?: Callback<number>;
}

@ObservedV2
export class ArcSliderOptions {
  @Trace valueOptions?: ArcSliderValueOptions = new ArcSliderValueOptions();
  @Trace layoutOptions?: ArcSliderLayoutOptions = new ArcSliderLayoutOptions();
  @Trace styleOptions?: ArcSliderStyleOptions = new ArcSliderStyleOptions();
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
      if (options.onTouch !== undefined && options.onTouch !== null) {
        this.onTouch = options.onTouch;
      }
      if (options.onChange !== undefined && options.onChange !== null) {
        this.onChange = options.onChange;
      }
    }
  }
}

@Component
export struct ArcSlider {
  options: ArcSliderOptions = new ArcSliderOptions();
  private settings: RenderingContextSettings = new RenderingContextSettings(true);
  private trackContext: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);
  private sliderContext: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);
  private touchAnimator: AnimatorResult | undefined = undefined;
  private restoreAnimator: AnimatorResult | undefined = undefined;
  private clickSelectedAnimator: AnimatorResult | undefined = undefined;
  private maxRestoreAnimator: AnimatorResult | undefined = undefined;
  private minRestoreAnimator: AnimatorResult | undefined = undefined;
  private delta: number = 0;
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

  private updateArcSlider(): number {
    this.checkParam();
    this.setReverse();
    if (this.isEnlarged == false) {
      this.setNormal();
    } else {
      this.setSelected();
    }
    this.drawTrack();
    this.drawSelect();
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
        this.selectArc = -selectRatio * (2 * Math.PI + this.start - this.end) + this.start;
      } else {
        this.selectArc = selectRatio * (this.end - this.start) + this.start;
      }
    } else {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = selectRatio * (this.end - this.start) + this.start;
      } else {
        this.selectArc = selectRatio * (2 * Math.PI + this.start - this.end) + this.start;
      }
    }
    this.normalRadius = this.options.layoutOptions!.radius! - (this.lineWidth / 2) -
      this.options.layoutOptions!.padding!;
  }

  setSelected() {
    let selectRatio = (this.options.valueOptions!.value! - this.options.valueOptions!.min!) /
      (this.options.valueOptions!.max! - this.options.valueOptions!.min!);
    if (this.end > this.start) {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = -selectRatio * (2 * Math.PI + this.start - this.end) + this.start;
      } else {
        this.selectArc = selectRatio * (this.end - this.start) + this.start;
      }
    } else {
      if (this.options.layoutOptions!.reverse!) {
        this.selectArc = selectRatio * (this.end - this.start) + this.start;
      } else {
        this.selectArc = -selectRatio * (2 * Math.PI + this.start - this.end) + this.start;
      }
    }
    this.normalRadius = this.options.layoutOptions!.radius! - (this.lineWidth / 2);
  }

  drawTrack() {
    this.trackContext.clearRect(0, 0, this.totalWidth, this.totalHeight);
    this.trackContext.save();
    this.trackContext.filter = 'blur(' + vp2px(this.options.styleOptions!.trackBlur!) + 'px)';
    this.trackContext.strokeStyle = this.options.styleOptions!.trackColor!;
    this.trackContext.lineWidth = this.lineWidth;
    this.trackContext.beginPath();
    this.trackContext.arc(this.options.layoutOptions!.x!, this.options.layoutOptions!.y!,
      this.normalRadius, this.trackStart, this.end, this.options.layoutOptions!.reverse!);
    this.trackContext.stroke();
    this.trackContext.restore();
  }

  drawSelect() {
    if (!this.checkApprox(this.start, this.selectArc)) {
      this.sliderContext.clearRect(0, 0, this.totalWidth, this.totalHeight);
      this.sliderContext.save();
      this.sliderContext.lineWidth = this.lineWidth;
      this.sliderContext.strokeStyle = this.options.styleOptions!.selectedColor!;
      this.sliderContext.beginPath();
      this.sliderContext.arc(this.options.layoutOptions!.x!, this.options.layoutOptions!.y!, this.normalRadius,
        this.start, this.selectArc, this.options.layoutOptions!.reverse!);
      this.sliderContext.stroke();
      this.sliderContext.restore();
    } else {
      this.sliderContext.clearRect(0, 0, this.totalWidth, this.totalHeight);
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
      this.drawTrack();
      this.drawSelect();
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
      this.drawTrack();
      this.drawSelect();
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
      this.drawTrack();
      this.drawSelect();
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
      this.drawTrack();
      this.drawSelect();
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
      this.drawSelect();
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
    this.drawTrack();
    this.drawSelect();
    this.touchY = moveY;
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

    this.drawTrack();
    this.drawSelect();
    this.touchY = moveY;
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
    this.drawTrack();
    this.drawSelect();
    this.touchY = moveY;
  }

  isHotRegion(touchX: number, touchY: number): boolean {
    let radius = Math.sqrt(Math.pow(touchX - this.options.layoutOptions!.x!, 2) +
    Math.pow(touchY - this.options.layoutOptions!.y!, 2));
    if ((radius < this.options.layoutOptions!.radius! - this.options.styleOptions!.activeTrackThickness!) ||
      (radius > this.options.layoutOptions!.radius!)) {
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
          return false;
        } else {
          return true;
        }
      } else {
        if (this.start > this.end) {
          return true;
        } else {
          return false;
        }
      }
    } else {
      if (angle < this.start / ANGULAR_TO_RADIAN || angle > this.end / ANGULAR_TO_RADIAN) {
        if (this.start > this.end) {
          return true;
        } else {
          return false;
        }
      } else {
        if (this.start > this.end) {
          return false;
        } else {
          return true;
        }
      }
    }
  }

  checkApprox(num1: number, num2: number): boolean {
    return Math.abs(num1 - num2) < APPROXIMATE_NUMBER;
  }

  build() {
    Column() {
      Stack() {
        Canvas(this.trackContext)
          .width(this.updateArcSlider())
          .height(this.totalHeight)
          .onReady(() => {
            this.trackContext.lineCap = 'round';
            this.setNormal();
            this.drawTrack();
            this.drawSelect();
          })
          .hitTestBehavior(HitTestMode.Transparent)

        Canvas(this.sliderContext)
          .width(this.totalWidth)
          .height(this.totalHeight)
          .onReady(() => {
            this.sliderContext.lineCap = 'round';
            this.setNormal();
            this.drawTrack();
            this.drawSelect();
          })
          .onTouch((event?: TouchEvent) => {
            if (event) {
              if (event.type === TouchType.Down && this.isEnlarged === false) {
                this.touchY = event.touches[0].y;
                clearTimeout(this.meter);
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                  this.options.onTouch?.(event);
                  this.isEnlarged = true;
                  this.startTouchAnimator();
                }
              } else if (event.type === TouchType.Down && this.isEnlarged) {
                this.touchY = event.touches[0].y;
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                  this.options.onTouch?.(event);
                  clearTimeout(this.meter);
                  if (this.isTouchAnimatorFinished) {
                    this.sliderValue = this.options.valueOptions!.value!;
                    this.calcClickValue(event.touches[0].x, event.touches[0].y);
                    this.startClickAnimator();
                  }
                  if (this.isClickAnimatorFinished) {
                    clearTimeout(this.meter);
                    this.touchY = event.touches[0].y;
                    this.calcValue(event.touches[0].y);
                    this.setSelected();
                    this.drawTrack();
                    this.drawSelect();
                  }
                }
              } else if (this.isEnlarged && event.type === TouchType.Up) {
                this.options.onChange?.(this.options.valueOptions!.value!);
                this.options.onTouch?.(event);
                clearTimeout(this.meter);
                this.meter = setTimeout(() => {
                  if (this.isEnlarged) {
                    this.isTouchAnimatorFinished = false;
                    this.isClickAnimatorFinished = false;
                    this.isEnlarged = false;
                    this.startRestoreAnimator();
                  }
                }, 3000)
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
                  }
                }
              } else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                (event.type === TouchType.Move)) {
                this.options.onTouch?.(event);
                clearTimeout(this.meter);
                if (this.options.layoutOptions!.reverse!) {
                  if (((this.selectArc < this.endCurrent) || (this.checkApprox(this.selectArc, this.endCurrent))) &&
                    (this.delta >= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.selectArc < this.endCurrent) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.trackStart >= this.start) && (this.checkApprox(this.options.valueOptions!.value!,
                    this.options.valueOptions!.min!)) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                  } else if ((this.trackStart > this.start) && (this.delta >= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                  } else {
                    this.calcValue(event.touches[0].y);
                    this.selectedMaxOrMin = NORMAL_STATUS;
                  }
                } else {
                  if (((this.selectArc > this.endCurrent) || (this.checkApprox(this.selectArc, this.endCurrent))) &&
                    (this.delta <= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.selectArc > this.endCurrent) && (this.delta >= 0)) {
                    this.selectedMaxOrMin = MAX_STATUS;
                    this.calcMaxValue(event.touches[0].y);
                  } else if ((this.checkApprox(this.options.valueOptions!.value!, this.options.valueOptions!.min!)) &&
                    (this.delta >= 0) && ((this.trackStart <= this.start) ||
                    (this.checkApprox(this.selectArc, this.endCurrent)))) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                  } else if ((this.trackStart < this.start) && (this.delta <= 0)) {
                    this.selectedMaxOrMin = MIN_STATUS;
                    this.calcMinValue(event.touches[0].y);
                  } else {
                    this.calcValue(event.touches[0].y);
                    this.selectedMaxOrMin = NORMAL_STATUS;
                  }
                }
              }
            }
          })
          .hitTestBehavior(HitTestMode.Transparent)
      }.width(this.totalWidth)
      .height(this.totalHeight)
      .hitTestBehavior(HitTestMode.Transparent)
    }
  }
}