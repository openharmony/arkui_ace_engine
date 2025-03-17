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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}

const animator = requireNapi('animator');
const drawing = requireNapi('graphics.drawing');
const vibrator = requireNapi('vibrator');
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const hilog = requireNapi('hilog');
const display = requireNapi('display');
const PathShape = requireNapi('arkui.shape').PathShape;

const ANGLE_TO_RADIAN = Math.PI / 180; // Common or specific numerical values
const RADIAN_TO_ANGLE = 180 / Math.PI;
const PI_ANGLE = 180;
const TWO_PI_RADIAN = 2 * Math.PI;
const APPROXIMATE_NUMBER = Math.pow(10, -7);
const ANGLE_OVER_MIN = 10 * ANGLE_TO_RADIAN;
const LENGTH_OVER_MIN = 0.15;
const INVALID_TIMEOUT_ID = -1;
const RESTORE_TIMEOUT = 3000;
const PROGRESS_DEFAULT = 0; // Default value
const MIN_DEFAULT = 0;
const MAX_DEFAULT = 100;
const PADDING_DEFAULT = 5.5;
const START_ANGLE_DEFAULT = 15;
const END_ANGLE_DEFAULT = 45;
const ACTIVE_START_ANGLE_DEFAULT = -60;
const ACTIVE_END_ANGLE_DEFAULT = 60;
const REVERSE_DEFAULT = true;
const TRACK_THICKNESS_DEFAULT = 5;
const ACTIVE_TRACK_THICKNESS_DEFAULT = 24;
const TRACK_THICKNESS_MAX = 16;
const ACTIVE_TRACK_THICKNESS_MAX = 36;
const TRACK_BLUR_DEFAULT = 20;
const TRACK_COLOR_DEFAULT = '#33FFFFFF';
const SELECTED_COLOR_DEFAULT = '#FF5EA1FF';
const BLUR_COLOR_DEFAULT = $r('sys.color.ohos_id_color_subtab_bg');
const TOUCH_ANIMATION_DURATION = 200;
const LIMIT_RESTORE_ANIMATION_DURATION = 333;
const RESTORE_ANIMATION_DURATION = 167;
const DIAMETER_DEFAULT = 233;
const VIBRATOR_TYPE_TWO = 'watchhaptic.feedback.crown.strength2'; // About crown
const VIBRATOR_TYPE_IMPACT = 'watchhaptic.feedback.crown.impact';
const CROWN_EVENT_FLAG = 30;
const CROWN_CONTROL_RATIO = 2.10;
const CROWN_SENSITIVITY_LOW = 0.5;
const CROWN_SENSITIVITY_MEDIUM = 1;
const CROWN_SENSITIVITY_HIGH = 2;

export var AnimatorStatus;
(function (AnimatorStatus) {
    AnimatorStatus[AnimatorStatus["MIN"] = 0] = "MIN";
    AnimatorStatus[AnimatorStatus["MAX"] = 1] = "MAX";
    AnimatorStatus[AnimatorStatus["NORMAL"] = 2] = "NORMAL";
})(AnimatorStatus || (AnimatorStatus = {}));

export var ClipPathArc;
(function (ClipPathArc) {
    ClipPathArc[ClipPathArc["ARC1"] = 0] = "ARC1";
    ClipPathArc[ClipPathArc["ARC2"] = 1] = "ARC2";
    ClipPathArc[ClipPathArc["ARC3"] = 2] = "ARC3";
    ClipPathArc[ClipPathArc["ARC4"] = 3] = "ARC4";
})(ClipPathArc || (ClipPathArc = {}));

export var ArcSliderPosition;
(function (ArcSliderPosition) {
    ArcSliderPosition[ArcSliderPosition["LEFT"] = 0] = "LEFT";
    ArcSliderPosition[ArcSliderPosition["RIGHT"] = 1] = "RIGHT";
})(ArcSliderPosition || (ArcSliderPosition = {}));
let ArcSliderValueOptions = class ArcSliderValueOptions {
    constructor(options) {
        this.progress = options?.progress ?? PROGRESS_DEFAULT;
        this.min = options?.min ?? MIN_DEFAULT;
        this.max = options?.max ?? MAX_DEFAULT;
    }
};
__decorate([
    Trace
], ArcSliderValueOptions.prototype, "progress", void 0);
__decorate([
    Trace
], ArcSliderValueOptions.prototype, "min", void 0);
__decorate([
    Trace
], ArcSliderValueOptions.prototype, "max", void 0);
ArcSliderValueOptions = __decorate([
    ObservedV2
], ArcSliderValueOptions);

export { ArcSliderValueOptions };
let ArcSliderLayoutOptions = class ArcSliderLayoutOptions {
    constructor(options) {
        this.reverse = options?.reverse ?? REVERSE_DEFAULT;
        this.position = options?.position ?? ArcSliderPosition.RIGHT;
    }
};
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "reverse", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "position", void 0);
ArcSliderLayoutOptions = __decorate([
    ObservedV2
], ArcSliderLayoutOptions);

export { ArcSliderLayoutOptions };
let ArcSliderStyleOptions = class ArcSliderStyleOptions {
    constructor(options) {
        this.trackThickness = options?.trackThickness ?? TRACK_THICKNESS_DEFAULT;
        this.activeTrackThickness = options?.activeTrackThickness ?? ACTIVE_TRACK_THICKNESS_DEFAULT;
        this.trackColor = options?.trackColor ?? TRACK_COLOR_DEFAULT;
        this.selectedColor = options?.selectedColor ?? SELECTED_COLOR_DEFAULT;
        this.trackBlur = options?.trackBlur ?? TRACK_BLUR_DEFAULT;
    }
};
__decorate([
    Trace
], ArcSliderStyleOptions.prototype, "trackThickness", void 0);
__decorate([
    Trace
], ArcSliderStyleOptions.prototype, "activeTrackThickness", void 0);
__decorate([
    Trace
], ArcSliderStyleOptions.prototype, "trackColor", void 0);
__decorate([
    Trace
], ArcSliderStyleOptions.prototype, "selectedColor", void 0);
__decorate([
    Trace
], ArcSliderStyleOptions.prototype, "trackBlur", void 0);
ArcSliderStyleOptions = __decorate([
    ObservedV2
], ArcSliderStyleOptions);

export { ArcSliderStyleOptions };
let ArcSliderOptions = class ArcSliderOptions {
    constructor(options) {
        this.valueOptions = options?.valueOptions ?? new ArcSliderValueOptions();
        this.layoutOptions = options?.layoutOptions ?? new ArcSliderLayoutOptions();
        this.styleOptions = options?.styleOptions ?? new ArcSliderStyleOptions();
        this.digitalCrownSensitivity = options?.digitalCrownSensitivity ?? CrownSensitivity.MEDIUM;
        this.onTouch = options?.onTouch ?? ((event) => {
        });
        this.onChange = options?.onChange ?? ((progress) => {
        });
    }
};
__decorate([
    Trace
], ArcSliderOptions.prototype, "valueOptions", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "layoutOptions", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "styleOptions", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "digitalCrownSensitivity", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "onTouch", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "onChange", void 0);
ArcSliderOptions = __decorate([
    ObservedV2
], ArcSliderOptions);

export { ArcSliderOptions };

export class DrawParameters {
    constructor() {
        this.lineWidth = 0;
        this.radius = 0;
        this.trackEndAngle = 0;
        this.trackStartAngle = 0;
        this.selectedStartAngle = 0;
        this.selectedEndAngle = 0;
        this.trackColor = ColorMetrics.resourceColor(TRACK_COLOR_DEFAULT);
        this.selectedColor = ColorMetrics.resourceColor(SELECTED_COLOR_DEFAULT);
        this.x = 0;
        this.y = 0;
        this.blur = TRACK_BLUR_DEFAULT;
        this.uiContext = undefined;
    }
}

export function nearEqual(num1, num2) {
    return Math.abs(num1 - num2) < APPROXIMATE_NUMBER;
}

export class MyFullDrawModifier extends DrawModifier {
    constructor(parameters) {
        super();
        this.parameters = new DrawParameters();
        this.parameters = parameters;
    }

    parseColorString(color) {
        return { alpha: color.alpha, red: color.red, green: color.green, blue: color.blue };
    }

    drawTrack(context) {
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
        const path = new drawing.Path();
        const leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.radius);
        const leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.radius);
        const rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.radius);
        const rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.radius);
        let startAngle;
        let sweepAngle;
        startAngle = this.parameters.trackEndAngle * RADIAN_TO_ANGLE;
        sweepAngle = (this.parameters.trackStartAngle - this.parameters.trackEndAngle) * RADIAN_TO_ANGLE;
        path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngle, sweepAngle);
        canvas.drawPath(path);
        canvas.detachPen();
    }

    drawSelection(context) {
        if (this.parameters.uiContext === undefined) {
            hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
            return;
        }
        if (nearEqual(this.parameters.selectedStartAngle, this.parameters.selectedEndAngle)) {
            return;
        }
        const canvas = context.canvas;
        const pen = new drawing.Pen();
        pen.setAntiAlias(true);
        pen.setColor(this.parseColorString(this.parameters.selectedColor));
        pen.setStrokeWidth(this.parameters.uiContext.vp2px(this.parameters.lineWidth));
        pen.setCapStyle(drawing.CapStyle.ROUND_CAP);
        canvas.attachPen(pen);
        let path = new drawing.Path();
        const leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.radius);
        const leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.radius);
        const rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.radius);
        const rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.radius);
        let startAngle;
        let sweepAngle;
        startAngle = this.parameters.selectedEndAngle * RADIAN_TO_ANGLE;
        sweepAngle = (this.parameters.selectedStartAngle - this.parameters.selectedEndAngle) * RADIAN_TO_ANGLE;
        path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngle, sweepAngle);
        canvas.drawPath(path);
        canvas.detachPen();
    }

    drawContent(context) {
        this.drawTrack(context);
    }

    drawFront(context) {
        this.drawSelection(context);
    }
}

export class ArcSlider extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("options", (params && "options" in params) ? params.options : new ArcSliderOptions());
        this.lineWidth = 0;
        this.radius = 0;
        this.trackStartAngle = 0;
        this.trackEndAngle = 0;
        this.selectedStartAngle = 0;
        this.selectedEndAngle = 0;
        this.selectRatioNow = 0;
        this.isEnlarged = false;
        this.clipPath = '';
        this.isReverse = false;
        this.isLargeArc = false;
        this.isFocus = false;
        this.parameters = "parameters" in params ? params.parameters : new DrawParameters();
        this.fullModifier = "fullModifier" in params ? params.fullModifier : new MyFullDrawModifier(this.parameters);
        this.touchAnimator = "touchAnimator" in params ? params.touchAnimator : undefined;
        this.restoreAnimator = "restoreAnimator" in params ? params.restoreAnimator : undefined;
        this.maxRestoreAnimator = "maxRestoreAnimator" in params ? params.maxRestoreAnimator : undefined;
        this.minRestoreAnimator = "minRestoreAnimator" in params ? params.minRestoreAnimator : undefined;
        this.delta = "delta" in params ? params.delta : 0;
        this.crownDeltaAngle = "crownDeltaAngle" in params ? params.crownDeltaAngle : 0;
        this.lineWidthBegin = "lineWidthBegin" in params ? params.lineWidthBegin : 0;
        this.touchY = "touchY" in params ? params.touchY : 0;
        this.meter = "meter" in params ? params.meter : 0;
        this.trackStartAngleBegin = "trackStartAngleBegin" in params ? params.trackStartAngleBegin : 0;
        this.selectedEndAngleBegin = "selectedEndAngleBegin" in params ? params.selectedEndAngleBegin : 0;
        this.isTouchAnimatorFinished = "isTouchAnimatorFinished" in params ? params.isTouchAnimatorFinished : false;
        this.clickValue = "clickValue" in params ? params.clickValue : 0;
        this.normalStartAngle = "normalStartAngle" in params ? params.normalStartAngle : 0;
        this.normalEndAngle = "normalEndAngle" in params ? params.normalEndAngle : 0;
        this.activeStartAngle = "activeStartAngle" in params ? params.activeStartAngle : 0;
        this.activeEndAngle = "activeEndAngle" in params ? params.activeEndAngle : 0;
        this.selectedMaxOrMin = "selectedMaxOrMin" in params ? params.selectedMaxOrMin : AnimatorStatus.NORMAL;
        this.needVibrate = "needVibrate" in params ? params.needVibrate : true;
        this.crownEventCounter = "crownEventCounter" in params ? params.crownEventCounter : 0;
        this.diameter = "diameter" in params ? params.diameter : 0;
        this.isAntiClock = "isAntiClock" in params ? params.isAntiClock : true;
        this.normalRadius = "normalRadius" in params ? params.normalRadius : 0;
        this.finalizeConstruction();
    }

    onChange(monitor) {
        monitor.dirty.forEach((path) => {
            const isAntiClockChanged = monitor.value('isAntiClock')?.now !== monitor.value('isAntiClock')?.before;
            const isReverseChanged = monitor.value('options.layoutOptions.reverse')?.now !==
                monitor.value('options.layoutOptions.reverse')?.before;
            const isThicknessChanged = monitor.value('options.styleOptions.activeTrackThickness')?.now !==
                monitor.value('options.styleOptions.activeTrackThickness')?.before;
            if (isAntiClockChanged || isReverseChanged) {
                this.selectedStartAngle = this.activeStartAngle;
                this.trackEndAngle = this.activeEndAngle;
                this.trackStartAngle = this.activeStartAngle;
            }
            if (isThicknessChanged) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness;
            }
            this.updateArcSlider();
        });
    }

    aboutToAppear() {
        this.updateArcSlider();
        this.resetDrawing();
        this.setTouchAnimator();
        this.setMaxRestoreAnimator();
        this.setMinRestoreAnimator();
        this.setRestoreAnimator();
        this.setDiameter();
    }

    aboutToDisappear() {
        clearTimeout(this.meter);
        this.touchAnimator = undefined;
        this.restoreAnimator = undefined;
        this.maxRestoreAnimator = undefined;
        this.minRestoreAnimator = undefined;
    }

    setTouchAnimator() {
        this.touchAnimator = animator.create({
            duration: TOUCH_ANIMATION_DURATION,
            easing: 'friction',
            delay: 0,
            fill: 'forwards',
            direction: 'normal',
            iterations: 1,
            begin: 0,
            end: 1
        });
        this.touchAnimator.onFrame = (fraction) => {
            this.lineWidth = this.calcAnimatorChange(this.options.styleOptions.trackThickness, this.options.styleOptions.activeTrackThickness, fraction);
            this.selectedStartAngle = this.calcAnimatorChange(this.normalStartAngle, this.activeStartAngle, fraction);
            this.trackStartAngle = this.selectedStartAngle;
            this.trackEndAngle = this.calcAnimatorChange(this.normalEndAngle, this.activeEndAngle, fraction);
            this.resetDrawing();
        };
        this.touchAnimator.onFinish = () => {
            this.isTouchAnimatorFinished = true;
        };
    }

    startTouchAnimator() {
        if (this.touchAnimator) {
            this.touchAnimator.play();
        }
    }

    setMaxRestoreAnimator() {
        this.maxRestoreAnimator = animator.create({
            duration: LIMIT_RESTORE_ANIMATION_DURATION,
            easing: 'sharp',
            delay: 0,
            fill: 'forwards',
            direction: 'normal',
            iterations: 1,
            begin: 0,
            end: 1
        });
        this.maxRestoreAnimator.onFrame = (fraction) => {
            this.lineWidth = this.calcAnimatorChange(this.lineWidthBegin, this.options.styleOptions.activeTrackThickness, fraction);
            this.selectedEndAngle = this.calcAnimatorChange(this.selectedEndAngleBegin, this.activeEndAngle, fraction);
            this.trackEndAngle = this.selectedEndAngle;
            this.resetDrawing();
        };
        this.maxRestoreAnimator.onFinish = () => {
            this.selectedMaxOrMin = AnimatorStatus.NORMAL;
        };
    }

    startMaxRestoreAnimator() {
        if (this.maxRestoreAnimator) {
            this.maxRestoreAnimator.play();
        }
    }

    setMinRestoreAnimator() {
        this.minRestoreAnimator = animator.create({
            duration: LIMIT_RESTORE_ANIMATION_DURATION,
            easing: 'sharp',
            delay: 0,
            fill: 'forwards',
            direction: 'normal',
            iterations: 1,
            begin: 0,
            end: 1
        });
        this.minRestoreAnimator.onFrame = (fraction) => {
            this.lineWidth = this.calcAnimatorChange(this.lineWidthBegin, this.options.styleOptions.activeTrackThickness, fraction);
            this.trackStartAngle = this.calcAnimatorChange(this.trackStartAngleBegin, this.activeStartAngle, fraction);
            this.resetDrawing();
        };
        this.minRestoreAnimator.onFinish = () => {
            this.selectedMaxOrMin = AnimatorStatus.NORMAL;
        };
    }

    startMinRestoreAnimator() {
        if (this.minRestoreAnimator) {
            this.minRestoreAnimator.play();
        }
    }

    setRestoreAnimator() {
        this.restoreAnimator = animator.create({
            duration: RESTORE_ANIMATION_DURATION,
            easing: 'friction',
            delay: 0,
            fill: 'forwards',
            direction: 'normal',
            iterations: 1,
            begin: 0,
            end: 1
        });
        this.restoreAnimator.onFrame = (fraction) => {
            this.lineWidth = this.calcAnimatorChange(this.options.styleOptions.activeTrackThickness, this.options.styleOptions.trackThickness, fraction);
            this.selectedStartAngle = this.calcAnimatorChange(this.activeStartAngle, this.normalStartAngle, fraction) *
                ANGLE_TO_RADIAN;
            this.trackStartAngle = this.selectedStartAngle;
            this.trackEndAngle = this.calcAnimatorChange(this.activeEndAngle, this.normalEndAngle, fraction) *
                ANGLE_TO_RADIAN;
            this.resetDrawing();
        };
    }

    startRestoreAnimator() {
        if (this.restoreAnimator) {
            this.restoreAnimator.play();
        }
    }

    updateArcSlider() {
        this.checkParam();
        this.setLayoutState(this.options.layoutOptions.reverse, this.options.layoutOptions.position);
        this.resetDrawing();
    }

    setLimitValues(attr, defaultValue, min, max) {
        if (attr < min) {
            attr = defaultValue;
        }
        if (max != undefined && attr > max) {
            attr = defaultValue;
        }
        return attr;
    }

    checkParam() {
        if (this.options.valueOptions.max === this.options.valueOptions.min ||
            this.options.valueOptions.max < this.options.valueOptions.min) {
            this.options.valueOptions.max = MAX_DEFAULT;
            this.options.valueOptions.min = MIN_DEFAULT;
            this.options.valueOptions.progress = PROGRESS_DEFAULT;
        }
        this.options.valueOptions.progress = Math.min(this.options.valueOptions.max, this.options.valueOptions.progress);
        this.options.valueOptions.progress = Math.max(this.options.valueOptions.min, this.options.valueOptions.progress);
        this.options.styleOptions.trackBlur = this.setLimitValues(this.options.styleOptions.trackBlur, TRACK_BLUR_DEFAULT, 0);
        this.options.styleOptions.trackThickness = this.setLimitValues(this.options.styleOptions.trackThickness, TRACK_THICKNESS_DEFAULT, TRACK_THICKNESS_DEFAULT, TRACK_THICKNESS_MAX);
        this.options.styleOptions.activeTrackThickness = this.setLimitValues(this.options.styleOptions.activeTrackThickness, ACTIVE_TRACK_THICKNESS_DEFAULT, ACTIVE_TRACK_THICKNESS_DEFAULT, ACTIVE_TRACK_THICKNESS_MAX);
    }

    updateModifier() {
        this.parameters.lineWidth = this.lineWidth;
        this.parameters.radius = this.radius;
        this.parameters.selectedStartAngle = this.selectedStartAngle;
        this.parameters.trackEndAngle = this.trackEndAngle;
        this.parameters.trackStartAngle = this.trackStartAngle;
        this.parameters.selectedEndAngle = this.selectedEndAngle;
        try {
            this.parameters.trackColor = ColorMetrics.resourceColor(this.options.styleOptions.trackColor);
        }
        catch (err) {
            let error = err;
            console.error(`Failed to set track color, code = ${error.code}, message =${error.message}`);
            this.parameters.trackColor = ColorMetrics.resourceColor(TRACK_COLOR_DEFAULT);
        }
        try {
            this.parameters.selectedColor = ColorMetrics.resourceColor(this.options.styleOptions.selectedColor);
        }
        catch (err) {
            let error = err;
            console.error(`Failed to set selected color, code = ${error.code}, message =${error.message}`);
            this.parameters.selectedColor = ColorMetrics.resourceColor(SELECTED_COLOR_DEFAULT);
        }
        this.parameters.blur = this.options.styleOptions.trackBlur;
    }

    setDiameter() {
        let width;
        try {
            width = display.getDefaultDisplaySync().width;
        }
        catch (err) {
            let error = err;
            console.error(`Failed to get default display width, code = ${error.code}, message =${error.message}`);
            width = 0;
        }
        this.parameters.uiContext = this.getUIContext();
        if (this.parameters.uiContext) {
            if (width !== 0) {
                this.diameter = this.parameters.uiContext.px2vp(width);
            }
            else {
                this.diameter = DIAMETER_DEFAULT;
            }
        }
        this.normalRadius = this.diameter / 2;
        this.parameters.x = this.normalRadius;
        this.parameters.y = this.normalRadius;
    }

    resetDrawing() {
        this.setLayoutOptions();
        this.updateModifier();
        this.fullModifier.invalidate();
        this.calcBlur();
    }

    setLayoutState(reverse, position) {
        const normalStartAngleRight = -START_ANGLE_DEFAULT * ANGLE_TO_RADIAN;
        const normalEndAngleRight = -END_ANGLE_DEFAULT * ANGLE_TO_RADIAN;
        const activeStartAngleRight = -ACTIVE_START_ANGLE_DEFAULT * ANGLE_TO_RADIAN;
        const activeEndAngleRight = -ACTIVE_END_ANGLE_DEFAULT * ANGLE_TO_RADIAN;
        const normalStartAngleLeft = -Math.PI - normalStartAngleRight;
        const normalEndAngleLeft = -Math.PI - normalEndAngleRight;
        const activeStartAngleLeft = -Math.PI - activeStartAngleRight;
        const activeEndAngleLeft = -Math.PI - activeEndAngleRight;
        if (reverse && position === ArcSliderPosition.RIGHT) {
            this.isAntiClock = true;
            this.normalStartAngle = normalStartAngleRight;
            this.normalEndAngle = normalEndAngleRight;
            this.activeStartAngle = activeStartAngleRight;
            this.activeEndAngle = activeEndAngleRight;
        }
        else if (!reverse && position === ArcSliderPosition.RIGHT) {
            this.isAntiClock = false;
            this.normalStartAngle = normalEndAngleRight;
            this.normalEndAngle = normalStartAngleRight;
            this.activeStartAngle = activeEndAngleRight;
            this.activeEndAngle = activeStartAngleRight;
        }
        else if (reverse && position === ArcSliderPosition.LEFT) {
            this.isAntiClock = false;
            this.normalStartAngle = normalStartAngleLeft;
            this.normalEndAngle = normalEndAngleLeft;
            this.activeStartAngle = activeStartAngleLeft;
            this.activeEndAngle = activeEndAngleLeft;
        }
        else if (!reverse && position === ArcSliderPosition.LEFT) {
            this.isAntiClock = true;
            this.normalStartAngle = normalEndAngleLeft;
            this.normalEndAngle = normalStartAngleLeft;
            this.activeStartAngle = activeEndAngleLeft;
            this.activeEndAngle = activeStartAngleLeft;
        }
    }

    setLayoutOptions() {
        this.radius = this.normalRadius - (this.lineWidth / 2);
        // Without setting the angle and width in the enlarged state, the animation will be affected
        if (!this.isEnlarged) {
            this.selectedStartAngle = this.normalStartAngle;
            this.trackEndAngle = this.normalEndAngle;
            this.trackStartAngle = this.normalStartAngle;
            this.radius = this.radius - PADDING_DEFAULT;
            this.lineWidth = this.options.styleOptions.trackThickness;
        }
        const selectedRatio = (this.options.valueOptions.progress - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        const deltaRadian = this.trackEndAngle - this.selectedStartAngle;
        const selectedAngle = selectedRatio * Math.abs(deltaRadian);
        if (this.trackEndAngle > this.selectedStartAngle) {
            this.selectedEndAngle = this.selectedStartAngle + selectedAngle;
        }
        else {
            this.selectedEndAngle = this.selectedStartAngle - selectedAngle;
        }
        this.calcBlur();
    }

    calcPathXY(isRLarge) {
        if (this.parameters.uiContext) {
            const halfLineWidth = this.parameters.lineWidth / 2;
            let distance = this.parameters.radius;
            let angle = 0;
            if (isRLarge === ClipPathArc.ARC1) {
                distance += halfLineWidth;
                angle = this.parameters.trackStartAngle;
            }
            else if (isRLarge === ClipPathArc.ARC2) {
                distance += halfLineWidth;
                angle = this.parameters.trackEndAngle;
            }
            else if (isRLarge === ClipPathArc.ARC3) {
                distance -= halfLineWidth;
                angle = this.parameters.trackEndAngle;
            }
            else if (isRLarge === ClipPathArc.ARC4) {
                distance -= halfLineWidth;
                angle = this.parameters.trackStartAngle;
            }
            return `${(this.parameters.uiContext.vp2px(this.parameters.x + distance * Math.cos(angle)))} ` +
                `${(this.parameters.uiContext.vp2px(this.parameters.y + (distance) * Math.sin(angle)))}`;
        }
        return 0;
    }

    calcPathR(isRLarge) {
        if (this.parameters.uiContext) {
            const halfLineWidth = this.parameters.lineWidth / 2;
            let pathR = this.parameters.uiContext.vp2px(halfLineWidth);
            if (isRLarge === ClipPathArc.ARC2) {
                pathR += this.parameters.uiContext.vp2px(this.parameters.radius);
            }
            else if (isRLarge === ClipPathArc.ARC4) {
                pathR = this.parameters.uiContext.vp2px(this.parameters.radius) - pathR;
            }
            return `${pathR} ${pathR}`;
        }
        return 0;
    }

    setClipPath() {
        let littleArc = this.calcPathR(ClipPathArc.ARC1);
        const sourcePoint = `M${this.calcPathXY(ClipPathArc.ARC4)}`;
        const arc1 = ` A${littleArc} 0 1 ` + `${Number(this.isReverse)} ${this.calcPathXY(ClipPathArc.ARC1)}`;
        const arc2 = ` A${this.calcPathR(ClipPathArc.ARC2)} 0 ${Number(this.isLargeArc)} ${Number(this.isReverse)} ` +
            `${this.calcPathXY(ClipPathArc.ARC2)}`;
        const arc3 = ` A${littleArc} 0 1 ` + `${Number(this.isReverse)} ${this.calcPathXY(ClipPathArc.ARC3)}`;
        const arc4 = ` A${this.calcPathR(ClipPathArc.ARC4)} 0 ${Number(this.isLargeArc)} ${Number(!this.isReverse)} ` +
            `${this.calcPathXY(ClipPathArc.ARC4)}`;
        this.clipPath = sourcePoint + arc1 + arc2 + arc3 + arc4;
    }

    calcBlur() {
        this.isLargeArc = false;
        if (this.isAntiClock) {
            this.isReverse = false;
        }
        else {
            this.isReverse = true;
        }
        this.setClipPath();
    }

    calcAnimatorChange(start, end, fraction) {
        return (fraction * (end - start) + start);
    }

    calcClickValue(clickX, clickY) {
        if (clickY - this.normalRadius > this.radius) {
            clickY = this.radius + this.normalRadius;
        }
        else if (this.normalRadius - clickY > this.radius) {
            clickY = this.normalRadius - this.radius;
        }
        const sin = Math.abs(clickY - this.normalRadius) / this.radius;
        let radian = Math.asin(sin);
        const isXPositive = clickX > this.normalRadius;
        const isYPositive = clickY > this.normalRadius;
        if (!isXPositive && isYPositive) {
            radian = -Math.PI - radian;
        }
        else if (!isXPositive && !isYPositive) {
            radian = radian - Math.PI;
        }
        else if (isXPositive && !isYPositive) {
            radian = -radian;
        }
        this.selectedEndAngle = radian;
        const delta = (this.selectedStartAngle - this.selectedEndAngle) / ANGLE_TO_RADIAN;
        if (!this.isAntiClock) {
            this.selectRatioNow = -delta / (ACTIVE_END_ANGLE_DEFAULT - ACTIVE_START_ANGLE_DEFAULT);
        }
        else {
            this.selectRatioNow = delta / (ACTIVE_END_ANGLE_DEFAULT - ACTIVE_START_ANGLE_DEFAULT);
        }
        this.selectRatioNow = Math.min(1, this.selectRatioNow);
        this.selectRatioNow = Math.max(0, this.selectRatioNow);
        this.clickValue = this.selectRatioNow * (this.options.valueOptions.max - this.options.valueOptions.min) +
        this.options.valueOptions.min;
        this.options.valueOptions.progress = this.clickValue;
        this.setLayoutOptions();
        this.updateModifier();
        this.fullModifier.invalidate();
    }

    calcValue(moveY) {
        this.delta = this.touchY - moveY;
        const total = this.radius * Math.sqrt(3);
        let valueNow = (this.options.valueOptions.progress - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        if (this.options.layoutOptions.reverse) {
            valueNow += this.delta / total;
        }
        else {
            valueNow -= this.delta / total;
        }
        valueNow = Math.min(1, valueNow);
        valueNow = Math.max(0, valueNow);
        this.options.valueOptions.progress = valueNow * (this.options.valueOptions.max - this.options.valueOptions.min) +
        this.options.valueOptions.min;
        this.setLayoutOptions();
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
    }

    calcCrownTotal(activeStartAngle, activeEndAngle) {
        if (activeEndAngle > activeStartAngle) {
            if (this.options.layoutOptions.reverse) {
                return (TWO_PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle));
            }
            return Math.abs(activeEndAngle - activeStartAngle);
        }
        else {
            if (this.options.layoutOptions.reverse) {
                return Math.abs(activeEndAngle - activeStartAngle);
            }
            return (TWO_PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle));
        }
    }

    calcCrownValue(deltaCrownAngle) {
        const totalAngle = this.calcCrownTotal(this.activeStartAngle, this.activeEndAngle);
        const totalValue = this.options.valueOptions.max - this.options.valueOptions.min;
        let valueNow = (this.options.valueOptions.progress - this.options.valueOptions.min) / totalValue;
        valueNow += deltaCrownAngle / totalAngle;
        valueNow = Math.min(1, valueNow);
        valueNow = Math.max(0, valueNow);
        this.options.valueOptions.progress = valueNow * totalValue + this.options.valueOptions.min;
        const isMaxOrMin = this.options.valueOptions.progress === this.options.valueOptions.max ||
            this.options.valueOptions.progress === this.options.valueOptions.min;
        if (isMaxOrMin) {
            if (this.needVibrate) {
                this.needVibrate = false;
                try {
                    this.startVibration(VIBRATOR_TYPE_IMPACT);
                }
                catch (error) {
                    const e = error;
                    hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                    Code: ${e.code}, message: ${e.message}`);
                }
            }
        }
        else {
            this.needVibrate = true;
        }
        this.setLayoutOptions();
        this.updateModifier();
        this.fullModifier.invalidate();
    }

    calcMaxValueDeltaIsPositive(delta) {
        const isLineWidthFitted = this.lineWidth >= this.options.styleOptions.activeTrackThickness *
            (1 - LENGTH_OVER_MIN);
        if (this.isAntiClock) {
            const isEndAngleFitted = this.selectedEndAngle >= (this.activeEndAngle - ANGLE_OVER_MIN);
            if (isEndAngleFitted && isLineWidthFitted) {
                this.selectedEndAngle -= (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) / (LENGTH_OVER_MIN * this.lineWidth +
                Math.abs(this.delta));
                this.trackEndAngle = this.selectedEndAngle;
            }
            if (this.selectedEndAngle <= (this.activeEndAngle - ANGLE_OVER_MIN)) {
                this.selectedEndAngle = this.activeEndAngle - ANGLE_OVER_MIN;
            }
        }
        else {
            const isEndAngleFitted = this.selectedEndAngle <= (this.activeEndAngle + ANGLE_OVER_MIN);
            if (isEndAngleFitted && isLineWidthFitted) {
                this.selectedEndAngle += (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) / (LENGTH_OVER_MIN * this.lineWidth +
                Math.abs(this.delta));
                this.trackEndAngle = this.selectedEndAngle;
            }
            if (this.selectedEndAngle >= (this.activeEndAngle + ANGLE_OVER_MIN)) {
                this.selectedEndAngle = this.activeEndAngle + ANGLE_OVER_MIN;
            }
        }
        this.trackEndAngle = this.selectedEndAngle;
        if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
            this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
        }
    }

    calcMaxValueDeltaIsNegative(delta) {
        const isLineWidthFitted = this.lineWidth <= this.options.styleOptions.activeTrackThickness;
        const isEndAngleFitted = this.selectedEndAngle <= this.activeEndAngle;
        if (this.isAntiClock) {
            if (isEndAngleFitted || isLineWidthFitted) {
                this.selectedEndAngle -= (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
            }
            if (this.selectedEndAngle >= this.activeEndAngle) {
                this.selectedEndAngle = this.activeEndAngle;
                this.trackEndAngle = this.selectedEndAngle;
            }
        }
        else {
            if ((!isEndAngleFitted) || isLineWidthFitted) {
                this.selectedEndAngle += (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
            }
            if (this.selectedEndAngle <= this.activeEndAngle) {
                this.selectedEndAngle = this.activeEndAngle;
                this.trackEndAngle = this.selectedEndAngle;
            }
        }
        this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) / (LENGTH_OVER_MIN * this.lineWidth +
        Math.abs(this.delta));
        this.trackEndAngle = this.selectedEndAngle;
        if (this.lineWidth >= this.options.styleOptions.activeTrackThickness) {
            this.lineWidth = this.options.styleOptions.activeTrackThickness;
        }
    }

    calcMaxValue(moveY) {
        this.delta = this.touchY - moveY;
        let delta = this.delta;
        if (!this.options.layoutOptions.reverse) {
            delta = -this.delta;
        }
        if (delta >= 0) {
            this.calcMaxValueDeltaIsPositive(delta);
        }
        else {
            this.calcMaxValueDeltaIsNegative(delta);
        }
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
        this.calcBlur();
    }

    calcMinValueDeltaIsNegative(delta) {
        const isLineWidthFitted = this.lineWidth >= this.options.styleOptions.activeTrackThickness *
            (1 - LENGTH_OVER_MIN);
        if (this.isAntiClock) {
            const isStartAngleFitted = this.trackStartAngle <= this.selectedStartAngle + ANGLE_OVER_MIN;
            if (isStartAngleFitted && isLineWidthFitted) {
                this.trackStartAngle -= (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius +
                Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if (this.trackStartAngle >= this.selectedStartAngle + ANGLE_OVER_MIN) {
                this.trackStartAngle = this.selectedStartAngle + ANGLE_OVER_MIN;
            }
        }
        else {
            const isStartAngleFitted = this.trackStartAngle >= this.selectedStartAngle - ANGLE_OVER_MIN;
            if (isStartAngleFitted && isLineWidthFitted) {
                this.trackStartAngle += (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius +
                Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if (this.trackStartAngle <= this.selectedStartAngle - ANGLE_OVER_MIN) {
                this.trackStartAngle = this.selectedStartAngle - ANGLE_OVER_MIN;
            }
        }
        if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
            this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
        }
    }

    calcMinValueDeltaIsPositive(delta) {
        const isLineWidthFitted = this.lineWidth <= this.options.styleOptions.activeTrackThickness;
        const isStartAngleFitted = this.trackStartAngle > this.selectedStartAngle;
        if (this.isAntiClock) {
            if (isStartAngleFitted || isLineWidthFitted) {
                this.trackStartAngle -= (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
                this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) / (LENGTH_OVER_MIN * this.lineWidth +
                Math.abs(this.delta));
            }
            if (this.trackStartAngle < this.selectedStartAngle) {
                this.trackStartAngle = this.selectedStartAngle;
            }
        }
        else {
            if (!isStartAngleFitted || isLineWidthFitted) {
                this.trackStartAngle += (ANGLE_OVER_MIN) * delta / (ANGLE_OVER_MIN * this.radius + Math.abs(this.delta));
                this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) / (LENGTH_OVER_MIN * this.lineWidth +
                Math.abs(this.delta));
            }
            if (this.trackStartAngle > this.selectedStartAngle) {
                this.trackStartAngle = this.selectedStartAngle;
            }
        }
        if (this.lineWidth >= this.options.styleOptions.activeTrackThickness) {
            this.lineWidth = this.options.styleOptions.activeTrackThickness;
        }
    }

    calcMinValue(moveY) {
        this.delta = this.touchY - moveY;
        let delta = this.delta;
        if (!this.options.layoutOptions.reverse) {
            delta = -this.delta;
        }
        if (delta <= 0) {
            this.calcMinValueDeltaIsNegative(delta);
        }
        else {
            this.calcMinValueDeltaIsPositive(delta);
        }
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
        this.calcBlur();
    }

    isHotRegion(touchX, touchY) {
        const radius = Math.sqrt(Math.pow(touchX - this.normalRadius, 2) + Math.pow(touchY - this.normalRadius, 2));
        let isRadiusNoFitted = (radius < this.normalRadius - this.options.styleOptions.activeTrackThickness) ||
            (radius > this.normalRadius);
        if (isRadiusNoFitted) {
            return false;
        }
        const sin = Math.abs(touchY - this.normalRadius) / radius;
        const radian = Math.asin(sin);
        let angle = radian / ANGLE_TO_RADIAN;
        const isXPositive = touchX > this.normalRadius;
        const isYPositive = touchY > this.normalRadius;
        if (!isXPositive && isYPositive) {
            angle = -PI_ANGLE - angle;
        }
        else if (!isXPositive && !isYPositive) {
            angle = angle - PI_ANGLE;
        }
        else if (isXPositive && !isYPositive) {
            angle = -angle;
        }
        let angleToRadian = angle * ANGLE_TO_RADIAN;
        const isAntiClockAngleFitted = angleToRadian <= this.selectedStartAngle &&
            angleToRadian >= this.trackEndAngle;
        const isClockAngleFitted = angleToRadian >= this.selectedStartAngle && angleToRadian <= this.trackEndAngle;
        if (this.isAntiClock && isAntiClockAngleFitted || !this.isAntiClock && isClockAngleFitted) {
            return true;
        }
        return false;
    }

    calcDisplayControlRatio(crownSensitivity) {
        if (crownSensitivity === CrownSensitivity.LOW) {
            return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_LOW;
        }
        else if (crownSensitivity === CrownSensitivity.MEDIUM) {
            return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_MEDIUM;
        }
        else if (crownSensitivity === CrownSensitivity.HIGH) {
            return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_HIGH;
        }
        return CROWN_CONTROL_RATIO * CROWN_SENSITIVITY_MEDIUM;
    }

    clearTimeout() {
        if (this.meter !== INVALID_TIMEOUT_ID) {
            clearTimeout(this.meter);
            this.meter = INVALID_TIMEOUT_ID;
        }
    }

    onTouchEvent(event) {
        const isTouchTypeUp = this.isEnlarged && event.type === TouchType.Up;
        const isTouchTypeMove = this.isEnlarged && this.isTouchAnimatorFinished && event.type === TouchType.Move;
        if (event.type === TouchType.Down) {
            this.isFocus = false;
            if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                this.isFocus = true;
            }
            this.onTouchDown(event);
        }
        else if (isTouchTypeUp) {
            this.clearTimeout();
            if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                this.options.onTouch?.(event);
            }
            this.meter = setTimeout(() => {
                if (this.isEnlarged) {
                    this.isTouchAnimatorFinished = false;
                    this.isEnlarged = false;
                    this.startRestoreAnimator();
                    this.calcBlur();
                }
            }, RESTORE_TIMEOUT);
            this.isMaxOrMinAnimator();
        }
        else if (isTouchTypeMove && this.isFocus) {
            this.options.onTouch?.(event);
            this.onTouchMove(event.touches[0].y);
            this.options.onChange?.(this.options.valueOptions.progress);
            this.clearTimeout();
        }
    }

    onTouchDown(event) {
        if (!this.isEnlarged) {
            this.touchY = event.touches[0].y;
            this.clearTimeout();
            if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                this.options.onTouch?.(event);
                this.isEnlarged = true;
                this.startTouchAnimator();
                this.calcBlur();
            }
        }
        else {
            this.touchY = event.touches[0].y;
            if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                this.options.onTouch?.(event);
                this.clearTimeout();
                if (this.isTouchAnimatorFinished) {
                    this.calcClickValue(event.touches[0].x, event.touches[0].y);
                }
                this.touchY = event.touches[0].y;
                this.calcValue(event.touches[0].y);
                this.options.onChange?.(this.options.valueOptions.progress);
                this.setLayoutOptions();
                this.updateModifier();
                this.fullModifier.invalidate();
            }
        }
    }

    isMaxOrMinAnimator() {
        let selectedEndAngle = this.selectedEndAngle;
        let trackStartAngle = this.trackStartAngle;
        let activeEndAngle = this.activeEndAngle;
        let activeStartAngle = this.activeStartAngle;
        if (!this.isAntiClock) {
            selectedEndAngle = -this.selectedEndAngle;
            trackStartAngle = -this.trackStartAngle;
            activeEndAngle = -this.activeEndAngle;
            activeStartAngle = -this.activeStartAngle;
        }
        const canMaxRestoreAnimatorStart = this.selectedMaxOrMin === AnimatorStatus.MAX &&
            selectedEndAngle < activeEndAngle;
        const canMinRestoreAnimatorStart = this.selectedMaxOrMin === AnimatorStatus.MIN &&
            trackStartAngle > activeStartAngle;
        if (canMaxRestoreAnimatorStart) {
            this.lineWidthBegin = this.lineWidth;
            this.selectedEndAngleBegin = this.selectedEndAngle;
            this.startMaxRestoreAnimator();
        }
        if (canMinRestoreAnimatorStart) {
            this.lineWidthBegin = this.lineWidth;
            this.trackStartAngleBegin = this.trackStartAngle;
            this.startMinRestoreAnimator();
            this.calcBlur();
        }
    }

    onTouchMove(touchY) {
        let maxAngel;
        let minAngel;
        let delta = this.delta;
        maxAngel = this.selectedEndAngle;
        minAngel = this.trackStartAngle;
        if (!this.options.layoutOptions.reverse) {
            delta = -this.delta;
        }
        const isMaxFitted = !(delta < 0 && nearEqual(maxAngel, this.activeEndAngle));
        const isMinFitted = !(delta > 0 && nearEqual(this.trackStartAngle, this.activeStartAngle)) &&
        nearEqual(this.options.valueOptions.progress, this.options.valueOptions.min);
        const isMaxNearEqual = nearEqual(maxAngel, this.activeEndAngle);
        const isMinNearEqual = nearEqual(minAngel, this.activeStartAngle);
        if (this.isAntiClock) {
            const isCalcMax = (maxAngel < this.activeEndAngle || isMaxNearEqual) && isMaxFitted;
            const isCalcMin = (minAngel >= this.activeStartAngle || isMinNearEqual) && isMinFitted;
            if (isCalcMax) {
                this.selectedMaxOrMin = AnimatorStatus.MAX;
                this.calcMaxValue(touchY);
            }
            else if (isCalcMin) {
                this.selectedMaxOrMin = AnimatorStatus.MIN;
                this.calcMinValue(touchY);
            }
            else {
                this.calcValue(touchY);
                this.selectedMaxOrMin = AnimatorStatus.NORMAL;
            }
        }
        else {
            const isCalcMax = (maxAngel > this.activeEndAngle || isMaxNearEqual) && isMaxFitted;
            const isCalcMin = (minAngel <= this.activeStartAngle || isMinNearEqual) && isMinFitted;
            if (isCalcMax) {
                this.selectedMaxOrMin = AnimatorStatus.MAX;
                this.calcMaxValue(touchY);
            }
            else if (isCalcMin) {
                this.selectedMaxOrMin = AnimatorStatus.MIN;
                this.calcMinValue(touchY);
            }
            else {
                this.calcValue(touchY);
                this.selectedMaxOrMin = AnimatorStatus.NORMAL;
            }
        }
    }

    onDigitalCrownEvent(event) {
        if (event && this.isFocus) {
            this.crownEventCounter += 1;
            if (this.crownEventCounter % CROWN_EVENT_FLAG === 0) {
                try {
                    this.startVibration(VIBRATOR_TYPE_TWO);
                }
                catch (error) {
                    const e = error;
                    hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                      Code: ${e.code}, message: ${e.message}`);
                }
                this.crownEventCounter = 0;
            }
        }
        this.crownAction(event);
    }

    startVibration(vibratorType) {
        const ret = vibrator.isSupportEffectSync(vibratorType);
        if (ret) {
            vibrator.startVibration({
                type: 'preset',
                effectId: vibratorType,
                count: 1,
            }, {
                usage: 'unknown'
            }, (error) => {
                if (error) {
                    hilog.error(0x3900, 'ArcSlider', `Failed to start vibration.
                            Code: ${error.code}, message: ${error.message}`);
                    this.crownEventCounter = 0;
                    return;
                }
                hilog.info(0x3900, 'ArcSlider', 'Succeed in starting vibration');
            });
        }
        else {
            hilog.error(0x3900, 'ArcSlider', vibratorType + ` is not supported`);
        }
    }

    crownAction(event) {
        if (event.action === CrownAction.BEGIN && !this.isEnlarged) {
            this.clearTimeout();
            this.isEnlarged = true;
            this.startTouchAnimator();
            this.calcBlur();
            this.crownDeltaAngle = this.getUIContext().px2vp(-event.degree *
            this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.radius;
            this.calcCrownValue(this.crownDeltaAngle);
        }
        else if (event.action === CrownAction.BEGIN && this.isEnlarged) {
            this.clearTimeout();
            this.crownDeltaAngle = this.getUIContext().px2vp(-event.degree *
            this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.radius;
            this.calcCrownValue(this.crownDeltaAngle);
        }
        else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) && (event.action === CrownAction.UPDATE)) {
            this.clearTimeout();
            this.crownDeltaAngle = this.getUIContext().px2vp(-event.degree *
            this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.radius;
            this.calcCrownValue(this.crownDeltaAngle);
        }
        else if (this.isEnlarged && event.action === CrownAction.END) {
            this.clearTimeout();
            this.meter = setTimeout(() => {
                if (this.isEnlarged) {
                    this.isTouchAnimatorFinished = false;
                    this.isEnlarged = false;
                    this.startRestoreAnimator();
                    this.calcBlur();
                }
            }, RESTORE_TIMEOUT);
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.clipShape(new PathShape().commands(this.clipPath));
            Stack.onTouchIntercept((event) => {
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                    return HitTestMode.Default;
                }
                return HitTestMode.Transparent;
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Circle.create({ width: this.diameter, height: this.diameter });
            Circle.width(this.diameter);
            Circle.height(this.diameter);
            Circle.fill(BLUR_COLOR_DEFAULT);
            Circle.backdropBlur(this.options.styleOptions.trackBlur);
        }, Circle);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel();
            Button.stateEffect(false);
            Button.backgroundColor(BLUR_COLOR_DEFAULT);
            Button.drawModifier(this.fullModifier);
            Button.width(this.diameter);
            Button.height(this.diameter);
            Button.onTouch((event) => {
                if (event) {
                    this.onTouchEvent(event);
                }
            });
            Button.onTouchIntercept((event) => {
                if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                    return HitTestMode.Block;
                }
                return HitTestMode.Transparent;
            });
            Button.focusable(true);
            Button.focusOnTouch(true);
            Button.onDigitalCrown((event) => {
                this.onDigitalCrownEvent(event);
                this.options.onChange?.(this.options.valueOptions.progress);
            });
        }, Button);
        Button.pop();
        Stack.pop();
    }

    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("options" in params) {
            this.updateParam("options", params.options);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ArcSlider.prototype, "options", void 0);
__decorate([
    Local
], ArcSlider.prototype, "lineWidth", void 0);
__decorate([
    Local
], ArcSlider.prototype, "radius", void 0);
__decorate([
    Local
], ArcSlider.prototype, "trackStartAngle", void 0);
__decorate([
    Local
], ArcSlider.prototype, "trackEndAngle", void 0);
__decorate([
    Local
], ArcSlider.prototype, "selectedStartAngle", void 0);
__decorate([
    Local
], ArcSlider.prototype, "selectedEndAngle", void 0);
__decorate([
    Local
], ArcSlider.prototype, "selectRatioNow", void 0);
__decorate([
    Local
], ArcSlider.prototype, "isEnlarged", void 0);
__decorate([
    Local
], ArcSlider.prototype, "clipPath", void 0);
__decorate([
    Local
], ArcSlider.prototype, "isReverse", void 0);
__decorate([
    Local
], ArcSlider.prototype, "isLargeArc", void 0);
__decorate([
    Local
], ArcSlider.prototype, "isFocus", void 0);
__decorate([
    Monitor('trackStartAngle', 'trackEndAngle', 'selectedStartAngle', 'selectedEndAngle', 'options.valueOptions.min', 'options.valueOptions.max', 'options.valueOptions.progress', 'options.layoutOptions.reverse', 'options.layoutOptions.position', 'options.styleOptions.trackThickness', 'options.styleOptions.activeTrackThickness', 'options.styleOptions.trackColor', 'options.styleOptions.selectedColor', 'options.styleOptions.trackBlur', 'clipPath', 'isFocus', 'isAntiClock')
], ArcSlider.prototype, "onChange", null);


export default {
    ArcSlider,
    ArcSliderPosition,
    ArcSliderOptions,
    ArcSliderValueOptions,
    ArcSliderLayoutOptions,
    ArcSliderStyleOptions
};
