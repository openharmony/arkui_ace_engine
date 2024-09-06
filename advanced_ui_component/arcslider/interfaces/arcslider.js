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
let ArcSliderValueOptions = class ArcSliderValueOptions {
    constructor(options) {
        this.value = VALUE_DEFAULT;
        this.min = MIN_DEFAULT;
        this.max = MAX_DEFAULT;
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
};
__decorate([
    Trace
], ArcSliderValueOptions.prototype, "value", void 0);
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
        this.x = X_DEFAULT;
        this.y = Y_DEFAULT;
        this.radius = RADIUS_DEFAULT;
        this.padding = PADDING_DEFAULT;
        this.startAngle = START_ANGLE_DEFAULT;
        this.endAngle = END_ANGLE_DEFAULT;
        this.activeStartAngle = ACTIVE_START_ANGLE_DEFAULT;
        this.activeEndAngle = ACTIVE_END_ANGLE_DEFAULT;
        this.reverse = REVERSE_DEFAULT;
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
};
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "x", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "y", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "radius", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "padding", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "startAngle", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "endAngle", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "activeStartAngle", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "activeEndAngle", void 0);
__decorate([
    Trace
], ArcSliderLayoutOptions.prototype, "reverse", void 0);
ArcSliderLayoutOptions = __decorate([
    ObservedV2
], ArcSliderLayoutOptions);

export { ArcSliderLayoutOptions };
let ArcSliderStyleOptions = class ArcSliderStyleOptions {
    constructor(options) {
        this.trackThickness = TRACK_THICKNESS_DEFAULT;
        this.activeTrackThickness = ACTIVE_TRACK_THICKNESS_DEFAULT;
        this.trackColor = TRACK_COLOR_DEFAULT;
        this.selectedColor = SELECTED_COLOR_DEFAULT;
        this.trackBlur = TRACK_BLUR_DEFAULT;
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
        this.valueOptions = new ArcSliderValueOptions();
        this.layoutOptions = new ArcSliderLayoutOptions();
        this.styleOptions = new ArcSliderStyleOptions();
        this.digitalCrownSensitivity = CrownSensitivity.MEDIUM;
        this.onTouch = (event) => {
        };
        this.onChange = (value) => {
        };
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

class DrawParameters {
    constructor() {
        this.lineWidth = 0;
        this.normalRadius = 0;
        this.start = 0;
        this.end = 0;
        this.trackStart = 0;
        this.selectArc = 0;
        this.trackColor = ColorMetrics.resourceColor(TRACK_COLOR_DEFAULT);
        this.selectedColor = ColorMetrics.resourceColor(SELECTED_COLOR_DEFAULT);
        this.reverse = REVERSE_DEFAULT;
        this.x = X_DEFAULT;
        this.y = Y_DEFAULT;
        this.blur = TRACK_BLUR_DEFAULT;
        this.uiContext = undefined;
    }
}

function nearEquals(num1, num2) {
    return Math.abs(num1 - num2) < APPROXIMATE_NUMBER;
}

class MyFullDrawModifier extends DrawModifier {
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
        let path = new drawing.Path();
        let leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius);
        let leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius);
        let rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius);
        let rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius);
        let startAngular;
        let stopAngular;
        if (this.parameters.reverse) {
            if (this.parameters.start < this.parameters.end) {
                startAngular = this.parameters.end * RADIAN_TO_ANGULAR;
                stopAngular = TWO_PI_RADIAN + (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR;
            }
            else {
                startAngular = this.parameters.end * RADIAN_TO_ANGULAR;
                stopAngular = (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR;
            }
        }
        else {
            if (this.parameters.start < this.parameters.end) {
                startAngular = this.parameters.end * RADIAN_TO_ANGULAR;
                stopAngular = (this.parameters.trackStart - this.parameters.end) * RADIAN_TO_ANGULAR;
            }
            else {
                startAngular = this.parameters.trackStart * RADIAN_TO_ANGULAR;
                stopAngular = TWO_PI_RADIAN + (this.parameters.end - this.parameters.trackStart) * RADIAN_TO_ANGULAR;
            }
        }
        path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngular, stopAngular);
        canvas.drawPath(path);
        canvas.detachPen();
    }

    drawSelection(context) {
        if (this.parameters.uiContext === undefined) {
            hilog.error(0x3900, 'ArcSlider', `uiContext is undefined`);
            return;
        }
        if (nearEquals(this.parameters.start, this.parameters.selectArc)) {
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
        let leftTopX = this.parameters.uiContext.vp2px(this.parameters.x - this.parameters.normalRadius);
        let leftTopY = this.parameters.uiContext.vp2px(this.parameters.y - this.parameters.normalRadius);
        let rightBottomX = this.parameters.uiContext.vp2px(this.parameters.x + this.parameters.normalRadius);
        let rightBottomY = this.parameters.uiContext.vp2px(this.parameters.y + this.parameters.normalRadius);
        let startAngular;
        let stopAngular;
        if (this.parameters.reverse) {
            if (this.parameters.start < this.parameters.end) {
                if (this.parameters.selectArc > this.parameters.start) {
                    startAngular = (this.parameters.selectArc - 2 * Math.PI) * RADIAN_TO_ANGULAR;
                    stopAngular = (2 * Math.PI + this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR;
                }
                else {
                    startAngular = this.parameters.selectArc * RADIAN_TO_ANGULAR;
                    stopAngular = (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR;
                }
            }
            else {
                startAngular = this.parameters.selectArc * RADIAN_TO_ANGULAR;
                stopAngular = (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR;
            }
        }
        else {
            if (this.parameters.start < this.parameters.end) {
                startAngular = this.parameters.selectArc * RADIAN_TO_ANGULAR;
                stopAngular = (this.parameters.start - this.parameters.selectArc) * RADIAN_TO_ANGULAR;
            }
            else {
                if (this.parameters.selectArc < this.parameters.start) {
                    startAngular = (this.parameters.start - 2 * Math.PI) * RADIAN_TO_ANGULAR;
                    stopAngular = (2 * Math.PI + this.parameters.selectArc - this.parameters.start) * RADIAN_TO_ANGULAR;
                }
                else {
                    startAngular = this.parameters.start * RADIAN_TO_ANGULAR;
                    stopAngular = (this.parameters.selectArc - this.parameters.start) * RADIAN_TO_ANGULAR;
                }
            }
        }
        path.arcTo(leftTopX, leftTopY, rightBottomX, rightBottomY, startAngular, stopAngular);
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

export class ArcSlider extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.options = new ArcSliderOptions();
        this.parameters = new DrawParameters();
        this.fullModifier = new MyFullDrawModifier(this.parameters);
        this.touchAnimator = undefined;
        this.restoreAnimator = undefined;
        this.clickSelectedAnimator = undefined;
        this.maxRestoreAnimator = undefined;
        this.minRestoreAnimator = undefined;
        this.delta = 0;
        this.crownDeltaAngle = 0;
        this.lineWidth = 0;
        this.lineWidthCurrent = 0;
        this.normalRadius = 0;
        this.touchY = 0;
        this.endCurrent = 0;
        this.meter = 0;
        this.start = 0;
        this.end = 0;
        this.trackStart = 0;
        this.trackStartCurrent = 0;
        this.selectArc = 0;
        this.selectArcCurrent = 0;
        this.selectRatioNow = 0;
        this.isEnlarged = false;
        this.isTouchAnimatorFinished = false;
        this.isClickAnimatorFinished = false;
        this.clickValue = 0;
        this.sliderValue = 0;
        this.startAngle = -START_ANGLE_DEFAULT;
        this.endAngle = -END_ANGLE_DEFAULT;
        this.activeStartAngle = -ACTIVE_START_ANGLE_DEFAULT;
        this.activeEndAngle = -ACTIVE_END_ANGLE_DEFAULT;
        this.selectedMaxOrMin = NORMAL_STATUS;
        this.totalWidth = TOTAL_LENGTH;
        this.totalHeight = TOTAL_LENGTH;
        this.isFocus = false;
        this.needVibrate = true;
        this.crownEventCounter = 0;
        this.__clipPath = new ObservedPropertySimplePU('', this, "clipPath");
        this.__sweepFlag = new ObservedPropertySimplePU(false, this, "sweepFlag");
        this.__isArcLarge = new ObservedPropertySimplePU(false, this, "isArcLarge");
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.options !== undefined) {
            this.options = params.options;
        }
        if (params.parameters !== undefined) {
            this.parameters = params.parameters;
        }
        if (params.fullModifier !== undefined) {
            this.fullModifier = params.fullModifier;
        }
        if (params.touchAnimator !== undefined) {
            this.touchAnimator = params.touchAnimator;
        }
        if (params.restoreAnimator !== undefined) {
            this.restoreAnimator = params.restoreAnimator;
        }
        if (params.clickSelectedAnimator !== undefined) {
            this.clickSelectedAnimator = params.clickSelectedAnimator;
        }
        if (params.maxRestoreAnimator !== undefined) {
            this.maxRestoreAnimator = params.maxRestoreAnimator;
        }
        if (params.minRestoreAnimator !== undefined) {
            this.minRestoreAnimator = params.minRestoreAnimator;
        }
        if (params.delta !== undefined) {
            this.delta = params.delta;
        }
        if (params.crownDeltaAngle !== undefined) {
            this.crownDeltaAngle = params.crownDeltaAngle;
        }
        if (params.lineWidth !== undefined) {
            this.lineWidth = params.lineWidth;
        }
        if (params.lineWidthCurrent !== undefined) {
            this.lineWidthCurrent = params.lineWidthCurrent;
        }
        if (params.normalRadius !== undefined) {
            this.normalRadius = params.normalRadius;
        }
        if (params.touchY !== undefined) {
            this.touchY = params.touchY;
        }
        if (params.endCurrent !== undefined) {
            this.endCurrent = params.endCurrent;
        }
        if (params.meter !== undefined) {
            this.meter = params.meter;
        }
        if (params.start !== undefined) {
            this.start = params.start;
        }
        if (params.end !== undefined) {
            this.end = params.end;
        }
        if (params.trackStart !== undefined) {
            this.trackStart = params.trackStart;
        }
        if (params.trackStartCurrent !== undefined) {
            this.trackStartCurrent = params.trackStartCurrent;
        }
        if (params.selectArc !== undefined) {
            this.selectArc = params.selectArc;
        }
        if (params.selectArcCurrent !== undefined) {
            this.selectArcCurrent = params.selectArcCurrent;
        }
        if (params.selectRatioNow !== undefined) {
            this.selectRatioNow = params.selectRatioNow;
        }
        if (params.isEnlarged !== undefined) {
            this.isEnlarged = params.isEnlarged;
        }
        if (params.isTouchAnimatorFinished !== undefined) {
            this.isTouchAnimatorFinished = params.isTouchAnimatorFinished;
        }
        if (params.isClickAnimatorFinished !== undefined) {
            this.isClickAnimatorFinished = params.isClickAnimatorFinished;
        }
        if (params.clickValue !== undefined) {
            this.clickValue = params.clickValue;
        }
        if (params.sliderValue !== undefined) {
            this.sliderValue = params.sliderValue;
        }
        if (params.startAngle !== undefined) {
            this.startAngle = params.startAngle;
        }
        if (params.endAngle !== undefined) {
            this.endAngle = params.endAngle;
        }
        if (params.activeStartAngle !== undefined) {
            this.activeStartAngle = params.activeStartAngle;
        }
        if (params.activeEndAngle !== undefined) {
            this.activeEndAngle = params.activeEndAngle;
        }
        if (params.selectedMaxOrMin !== undefined) {
            this.selectedMaxOrMin = params.selectedMaxOrMin;
        }
        if (params.totalWidth !== undefined) {
            this.totalWidth = params.totalWidth;
        }
        if (params.totalHeight !== undefined) {
            this.totalHeight = params.totalHeight;
        }
        if (params.isFocus !== undefined) {
            this.isFocus = params.isFocus;
        }
        if (params.needVibrate !== undefined) {
            this.needVibrate = params.needVibrate;
        }
        if (params.crownEventCounter !== undefined) {
            this.crownEventCounter = params.crownEventCounter;
        }
        if (params.clipPath !== undefined) {
            this.clipPath = params.clipPath;
        }
        if (params.sweepFlag !== undefined) {
            this.sweepFlag = params.sweepFlag;
        }
        if (params.isArcLarge !== undefined) {
            this.isArcLarge = params.isArcLarge;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__clipPath.purgeDependencyOnElmtId(rmElmtId);
        this.__sweepFlag.purgeDependencyOnElmtId(rmElmtId);
        this.__isArcLarge.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__clipPath.aboutToBeDeleted();
        this.__sweepFlag.aboutToBeDeleted();
        this.__isArcLarge.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get clipPath() {
        return this.__clipPath.get();
    }

    set clipPath(newValue) {
        this.__clipPath.set(newValue);
    }

    get sweepFlag() {
        return this.__sweepFlag.get();
    }

    set sweepFlag(newValue) {
        this.__sweepFlag.set(newValue);
    }

    get isArcLarge() {
        return this.__isArcLarge.get();
    }

    set isArcLarge(newValue) {
        this.__isArcLarge.set(newValue);
    }

    aboutToAppear() {
        this.updateArcSlider();
    }

    checkParam() {
        if (this.options.valueOptions.max <= this.options.valueOptions.min) {
            this.options.valueOptions.max = MAX_DEFAULT;
            this.options.valueOptions.min = MIN_DEFAULT;
        }
        if (this.options.valueOptions.value >= this.options.valueOptions.max) {
            this.options.valueOptions.value = this.options.valueOptions.max;
        }
        if (this.options.valueOptions.value <= this.options.valueOptions.min) {
            this.options.valueOptions.value = this.options.valueOptions.min;
        }
        if (this.options.layoutOptions.startAngle >= PI_RADIAN) {
            this.options.layoutOptions.startAngle = PI_RADIAN;
        }
        if (this.options.layoutOptions.startAngle <= -PI_RADIAN) {
            this.options.layoutOptions.startAngle = -PI_RADIAN;
        }
        if (this.options.layoutOptions.endAngle >= PI_RADIAN) {
            this.options.layoutOptions.endAngle = PI_RADIAN;
        }
        if (this.options.layoutOptions.endAngle <= -PI_RADIAN) {
            this.options.layoutOptions.endAngle = -PI_RADIAN;
        }
        if (this.options.layoutOptions.activeStartAngle >= PI_RADIAN) {
            this.options.layoutOptions.activeStartAngle = PI_RADIAN;
        }
        if (this.options.layoutOptions.activeStartAngle <= -PI_RADIAN) {
            this.options.layoutOptions.activeStartAngle = -PI_RADIAN;
        }
        if (this.options.layoutOptions.activeEndAngle >= PI_RADIAN) {
            this.options.layoutOptions.activeEndAngle = PI_RADIAN;
        }
        if (this.options.layoutOptions.activeEndAngle <= -PI_RADIAN) {
            this.options.layoutOptions.activeEndAngle = -PI_RADIAN;
        }
        this.startAngle = -this.options.layoutOptions.startAngle;
        this.endAngle = -this.options.layoutOptions.endAngle;
        this.activeStartAngle = -this.options.layoutOptions.activeStartAngle;
        this.activeEndAngle = -this.options.layoutOptions.activeEndAngle;
        if (this.options.layoutOptions.padding < 0) {
            this.options.layoutOptions.padding = PADDING_DEFAULT;
        }
        if (this.options.layoutOptions.radius < 0) {
            this.options.layoutOptions.radius = RADIUS_DEFAULT;
        }
        if (this.options.styleOptions.trackThickness <= 0) {
            this.options.styleOptions.trackThickness = TRACK_THICKNESS_DEFAULT;
        }
        if (this.options.styleOptions.activeTrackThickness <= 0) {
            this.options.styleOptions.activeTrackThickness = ACTIVE_TRACK_THICKNESS_DEFAULT;
        }
        if (this.options.styleOptions.trackBlur < 0) {
            this.options.styleOptions.trackBlur = TRACK_BLUR_DEFAULT;
        }
    }

    updateModifier() {
        this.fullModifier.parameters.lineWidth = this.lineWidth;
        this.fullModifier.parameters.normalRadius = this.normalRadius;
        this.fullModifier.parameters.start = this.start;
        this.fullModifier.parameters.end = this.end;
        this.fullModifier.parameters.trackStart = this.trackStart;
        this.fullModifier.parameters.selectArc = this.selectArc;
        this.fullModifier.parameters.trackColor = ColorMetrics.resourceColor(this.options.styleOptions.trackColor);
        this.fullModifier.parameters.selectedColor = ColorMetrics.resourceColor(this.options.styleOptions.selectedColor);
        this.fullModifier.parameters.reverse = this.options.layoutOptions.reverse;
        this.fullModifier.parameters.x = this.options.layoutOptions.x;
        this.fullModifier.parameters.y = this.options.layoutOptions.y;
        this.fullModifier.parameters.blur = this.options.styleOptions.trackBlur;
        this.fullModifier.parameters.uiContext = this.getUIContext();
    }

    updateArcSlider() {
        this.checkParam();
        this.setReverse();
        if (this.isEnlarged == false) {
            this.setNormal();
        }
        else {
            this.setSelected();
        }
        this.updateModifier();
        this.fullModifier.invalidate();
        return this.totalWidth;
    }

    setReverse() {
        if (!this.options.layoutOptions.reverse) {
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
        this.lineWidth = this.options.styleOptions.trackThickness;
        this.start = this.startAngle * ANGULAR_TO_RADIAN;
        this.end = this.endAngle * ANGULAR_TO_RADIAN;
        this.trackStart = this.startAngle * ANGULAR_TO_RADIAN;
        let selectRatio = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        if (this.end > this.start) {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = this.start - selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                if (this.selectArc <= -Math.PI) {
                    this.selectArc += 2 * Math.PI;
                }
            }
            else {
                this.selectArc = this.start + selectRatio * Math.abs(this.end - this.start);
            }
        }
        else {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = this.start - selectRatio * Math.abs(this.end - this.start);
            }
            else {
                this.selectArc = this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                if (this.selectArc >= Math.PI) {
                    this.selectArc = -2 * Math.PI + this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                }
            }
        }
        this.normalRadius = this.options.layoutOptions.radius - (this.lineWidth / 2) -
        this.options.layoutOptions.padding;
        this.calBlur();
    }

    setSelected() {
        let selectRatio = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        if (this.end > this.start) {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = this.start - selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                if (this.selectArc <= -Math.PI) {
                    this.selectArc = 2 * Math.PI + this.start - selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                }
            }
            else {
                this.selectArc = this.start + selectRatio * Math.abs(this.end - this.start);
            }
        }
        else {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = this.start - selectRatio * Math.abs(this.end - this.start);
            }
            else {
                this.selectArc = this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                if (this.selectArc >= Math.PI) {
                    this.selectArc = -2 * Math.PI + this.start + selectRatio * (2 * Math.PI - Math.abs(this.end - this.start));
                }
            }
        }
        this.normalRadius = this.options.layoutOptions.radius - (this.lineWidth / 2);
        this.calBlur();
    }

    calBlurIsReverseTrue() {
        if (this.trackStart > this.end) {
            if (this.trackStart - this.end > Math.PI) {
                this.isArcLarge = true;
                this.sweepFlag = false;
            }
            else {
                this.isArcLarge = false;
                this.sweepFlag = false;
            }
        }
        else {
            if (2 * Math.PI + this.trackStart - this.end > Math.PI) {
                this.isArcLarge = true;
                this.sweepFlag = false;
            }
            else {
                this.isArcLarge = false;
                this.sweepFlag = false;
            }
        }
    }

    calBlurIsReverseFalse() {
        if (this.trackStart > this.end) {
            if (2 * Math.PI + this.end - this.trackStart > Math.PI) {
                this.isArcLarge = true;
                this.sweepFlag = true;
            }
            else {
                this.isArcLarge = false;
                this.sweepFlag = true;
            }
        }
        else {
            if (this.end - this.trackStart > Math.PI) {
                this.isArcLarge = true;
                this.sweepFlag = true;
            }
            else {
                this.isArcLarge = false;
                this.sweepFlag = true;
            }
        }
    }

    setClipPath() {
        if (this.parameters.uiContext) {
            this.clipPath = 'M' + String(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius -
                this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
                this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart))) + ' A' +
            String(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' 0' + ' 1' + ' ' +
            String(Number(this.sweepFlag)) + ' ' + String(this.parameters.uiContext.vp2px(this.parameters.x +
                (this.parameters.normalRadius + this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
                this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart))) + ' A' +
            String(this.parameters.uiContext.vp2px(this.parameters.normalRadius + this.parameters.lineWidth / 2)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.normalRadius + this.parameters.lineWidth / 2)) + ' 0 ' +
            String(Number(this.isArcLarge)) + ' ' + String(Number(this.sweepFlag)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius +
                this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius +
                this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
            String(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.lineWidth / 2)) + ' 0' + ' 1 ' +
            String(Number(this.sweepFlag)) + ' ' + String(this.parameters.uiContext.vp2px(this.parameters.x +
                (this.parameters.normalRadius - this.parameters.lineWidth / 2) * Math.cos(this.parameters.end))) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
                this.parameters.lineWidth / 2) * Math.sin(this.parameters.end))) + ' A' +
            String(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth / 2)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.normalRadius - this.parameters.lineWidth / 2)) + ' 180 ' +
            String(Number(this.isArcLarge)) + ' ' + String(Number(!this.sweepFlag)) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.x + (this.parameters.normalRadius -
                this.parameters.lineWidth / 2) * Math.cos(this.parameters.trackStart))) + ' ' +
            String(this.parameters.uiContext.vp2px(this.parameters.y + (this.parameters.normalRadius -
                this.parameters.lineWidth / 2) * Math.sin(this.parameters.trackStart)));
        }
    }

    calBlur() {
        if (this.parameters.reverse) {
            this.calBlurIsReverseTrue();
        }
        else {
            this.calBlurIsReverseFalse();
        }
        this.setClipPath();
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
        });
        this.touchAnimator.onFrame = (value) => {
            this.lineWidth = value * (this.options.styleOptions.activeTrackThickness -
            this.options.styleOptions.trackThickness) + this.options.styleOptions.trackThickness;
            this.start = (value * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
            this.trackStart = (value * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
            this.end = (value * (this.activeEndAngle - this.endAngle) + this.endAngle) * ANGULAR_TO_RADIAN;
            this.setSelected();
            this.updateModifier();
            this.fullModifier.invalidate();
            this.calBlur();
        };
        this.touchAnimator.onFinish = () => {
            this.isTouchAnimatorFinished = true;
            this.endCurrent = this.end;
        };
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
        });
        this.maxRestoreAnimator.onFrame = (value) => {
            this.lineWidth = value * (this.options.styleOptions.activeTrackThickness - this.lineWidthCurrent) +
            this.lineWidthCurrent;
            this.selectArc = value * (this.endCurrent - this.selectArcCurrent) + this.selectArcCurrent;
            this.end = this.selectArc;
            this.updateModifier();
            this.fullModifier.invalidate();
            this.calBlur();
        };
        this.maxRestoreAnimator.onFinish = () => {
            this.selectedMaxOrMin = 'normal';
        };
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
        });
        this.minRestoreAnimator.onFrame = (value) => {
            this.lineWidth = value * (this.options.styleOptions.activeTrackThickness - this.lineWidthCurrent) +
            this.lineWidthCurrent;
            this.trackStart = value * (this.activeStartAngle * ANGULAR_TO_RADIAN - this.trackStartCurrent) +
            this.trackStartCurrent;
            this.updateModifier();
            this.fullModifier.invalidate();
            this.calBlur();
        };
        this.minRestoreAnimator.onFinish = () => {
            this.selectedMaxOrMin = 'normal';
        };
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
        });
        this.restoreAnimator.onFrame = (value) => {
            this.lineWidth = value * (this.options.styleOptions.trackThickness -
            this.options.styleOptions.activeTrackThickness) + this.options.styleOptions.activeTrackThickness;
            this.start = (value * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) * ANGULAR_TO_RADIAN;
            this.trackStart = (value * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) *
                ANGULAR_TO_RADIAN;
            this.end = (value * (this.endAngle - this.activeEndAngle) + this.activeEndAngle) * ANGULAR_TO_RADIAN;
            this.setNormal();
            this.updateModifier();
            this.fullModifier.invalidate();
            this.calBlur();
        };
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
        });
        this.clickSelectedAnimator.onFrame = (value) => {
            this.options.valueOptions.value = value;
            this.setSelected();
            this.updateModifier();
            this.fullModifier.invalidate();
        };
        this.clickSelectedAnimator.onFinish = () => {
            this.isClickAnimatorFinished = true;
        };
        if (this.clickSelectedAnimator) {
            this.clickSelectedAnimator.play();
        }
    }

    calcClickValue(clickX, clickY) {
        if (clickY - this.options.layoutOptions.y > this.normalRadius) {
            clickY = this.normalRadius + this.options.layoutOptions.y;
        }
        else if (this.options.layoutOptions.y - clickY > this.normalRadius) {
            clickY = this.options.layoutOptions.y - this.normalRadius;
        }
        let sin = Math.abs(clickY - this.options.layoutOptions.y) / this.normalRadius;
        let radian = Math.asin(sin);
        if ((clickX < this.options.layoutOptions.x) && (clickY > this.options.layoutOptions.y)) {
            radian = Math.PI - radian;
        }
        else if ((clickX < this.options.layoutOptions.x) && (clickY < this.options.layoutOptions.y)) {
            radian = radian - Math.PI;
        }
        else if ((clickX > this.options.layoutOptions.x) && (clickY < this.options.layoutOptions.y)) {
            radian = -radian;
        }
        this.selectArc = radian;
        if ((this.parameters.reverse) && (this.end > this.start)) {
            if (this.selectArc < this.start) {
                this.selectRatioNow = (this.start - this.selectArc) / (2 * Math.PI + this.start - this.end);
            }
            else {
                this.selectRatioNow = (2 * Math.PI + this.start - this.selectArc) / (2 * Math.PI + this.start - this.end);
            }
        }
        else if ((!this.parameters.reverse) && (this.end < this.start)) {
            if (this.selectArc < this.start) {
                this.selectRatioNow = (2 * Math.PI + this.selectArc - this.start) / (2 * Math.PI - this.start + this.end);
            }
            else {
                this.selectRatioNow = (this.selectArc - this.start) / (2 * Math.PI - this.start + this.end);
            }
        }
        else {
            this.selectRatioNow = (this.selectArc - this.start) / (this.end - this.start);
        }
        this.selectRatioNow = Math.min(1, this.selectRatioNow);
        this.selectRatioNow = Math.max(0, this.selectRatioNow);
        this.clickValue = this.selectRatioNow * (this.options.valueOptions.max - this.options.valueOptions.min) +
        this.options.valueOptions.min;
    }

    calcSin(radian) {
        if ((radian >= Math.PI / 2) && (radian <= Math.PI)) {
            return Math.sin(radian);
        }
        else if ((radian <= Math.PI / 2) && (radian >= -Math.PI / 2)) {
            return 2 - Math.sin(radian);
        }
        else if ((radian >= -Math.PI) && (radian <= -Math.PI / 2)) {
            return 4 + Math.sin(radian);
        }
        return 0;
    }

    calcValue(moveY) {
        this.delta = this.touchY - moveY;
        let total = 0;
        if (this.parameters.reverse) {
            if (this.start > this.end) {
                total = this.normalRadius * (this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN) -
                this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN));
            }
            else {
                total = this.normalRadius * (this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN) + 4 -
                this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN));
            }
        }
        else {
            if (this.start > this.end) {
                total = this.normalRadius * (this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN) + 4 -
                this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN));
            }
            else {
                total = this.normalRadius * (this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN) -
                this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN));
            }
        }
        let valueNow = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        valueNow += this.delta / total;
        valueNow = Math.min(1, valueNow);
        valueNow = Math.max(0, valueNow);
        this.options.valueOptions.value = valueNow *
            (this.options.valueOptions.max - this.options.valueOptions.min) + this.options.valueOptions.min;
        this.setSelected();
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
    }

    calcCrownTotal(activeStartAngle, activeEndAngle) {
        if (activeEndAngle > activeStartAngle) {
            if (this.options.layoutOptions.reverse) {
                return (2 * PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle)) * ANGULAR_TO_RADIAN;
            }
            else {
                return Math.abs(activeEndAngle - activeStartAngle) * ANGULAR_TO_RADIAN;
            }
        }
        else {
            if (this.options.layoutOptions.reverse) {
                return Math.abs(activeEndAngle - activeStartAngle) * ANGULAR_TO_RADIAN;
            }
            else {
                return (2 * PI_RADIAN - Math.abs(activeEndAngle - activeStartAngle)) * ANGULAR_TO_RADIAN;
            }
        }
    }

    calcCrownValue(deltaCrownAngle) {
        let totalAngle = this.calcCrownTotal(this.activeStartAngle, this.activeEndAngle);
        let totalValue = this.options.valueOptions.max - this.options.valueOptions.min;
        let valueNow = (this.options.valueOptions.value - this.options.valueOptions.min) / totalValue;
        valueNow += deltaCrownAngle / totalAngle;
        valueNow = Math.min(1, valueNow);
        valueNow = Math.max(0, valueNow);
        this.options.valueOptions.value = valueNow * totalValue + this.options.valueOptions.min;
        if (this.options.valueOptions.value === this.options.valueOptions.max ||
            this.options.valueOptions.value === this.options.valueOptions.min) {
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
                        }, (error) => {
                            if (error) {
                                hilog.error(0x3900, 'ArcSlider', `Failed to start vibration.
                  Code: ${error.code}, message: ${error.message}`);
                                return;
                            }
                            hilog.info(0x3900, 'ArcSlider', 'Succeed in starting vibration');
                        });
                    }
                    else {
                        hilog.error(0x3900, 'ArcSlider', `watchhaptic.crown.strength6 is not supported`);
                    }
                }
                catch (error) {
                    let e = error;
                    hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                    Code: ${e.code}, message: ${e.message}`);
                }
            }
        }
        else {
            this.needVibrate = true;
        }
        this.setSelected();
        this.updateModifier();
        this.fullModifier.invalidate();
    }

    calcMaxValueDeltaIsPositive() {
        if (this.options.layoutOptions.reverse) {
            if ((this.selectArc >= (this.endCurrent - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN)) &&
                (this.lineWidth >= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN))) {
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
            if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
            }
        }
        else {
            if ((this.selectArc <= (this.endCurrent + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN)) &&
                (this.lineWidth >= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN))) {
                this.selectArc += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
                this.end = this.selectArc;
            }
            if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
            }
            if (((this.selectArc / ANGULAR_TO_RADIAN) >= (this.endCurrent / ANGULAR_TO_RADIAN + ANGLE_OVER_MIN))) {
                this.selectArc = this.endCurrent + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
                this.end = this.selectArc;
            }
        }
    }

    calcMaxValueDeltaIsNegative() {
        if (this.options.layoutOptions.reverse) {
            if ((this.selectArc <= this.endCurrent) ||
                (this.lineWidth <= this.options.styleOptions.activeTrackThickness)) {
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
            if (this.lineWidth >= this.options.styleOptions.activeTrackThickness) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness;
            }
        }
        else {
            if (((this.selectArc >= this.endCurrent) && (this.selectArc < this.start)) ||
                (this.lineWidth <= this.options.styleOptions.activeTrackThickness)) {
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
            if (this.lineWidth >= this.options.styleOptions.activeTrackThickness) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness;
            }
        }
    }

    calcMaxValue(moveY) {
        this.delta = this.touchY - moveY;
        if (this.delta >= 0) {
            this.calcMaxValueDeltaIsPositive();
        }
        else {
            this.calcMaxValueDeltaIsNegative();
        }
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
        this.calBlur();
    }

    calcMinValueDeltaIsNegative() {
        if (this.options.layoutOptions.reverse) {
            if ((this.trackStart < this.start + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) &&
                (this.lineWidth >= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN))) {
                this.trackStart += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if ((this.trackStart / ANGULAR_TO_RADIAN) >= this.start / ANGULAR_TO_RADIAN + ANGLE_OVER_MIN) {
                this.trackStart = this.start + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
            }
            if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
            }
        }
        else {
            if ((this.trackStart > this.start - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) &&
                (this.lineWidth >= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN))) {
                this.trackStart -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if ((this.trackStart / ANGULAR_TO_RADIAN) <= this.start / ANGULAR_TO_RADIAN - ANGLE_OVER_MIN) {
                this.trackStart = this.start - ANGLE_OVER_MIN * ANGULAR_TO_RADIAN;
            }
            if (this.lineWidth <= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN)) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN);
            }
        }
    }

    calcMinValueDeltaIsPositive() {
        if (this.options.layoutOptions.reverse) {
            if ((this.trackStart > this.start) || (this.lineWidth <= this.options.styleOptions.activeTrackThickness)) {
                this.trackStart -= (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if (this.lineWidth > this.options.styleOptions.activeTrackThickness) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness;
            }
            if (this.trackStart < this.start) {
                this.trackStart = this.start;
            }
        }
        else {
            if ((this.trackStart < this.start) || (this.lineWidth <= this.options.styleOptions.activeTrackThickness)) {
                this.trackStart += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth += LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
            }
            if (this.trackStart > this.start) {
                this.trackStart = this.start;
            }
            if (this.lineWidth >= this.options.styleOptions.activeTrackThickness) {
                this.lineWidth = this.options.styleOptions.activeTrackThickness;
            }
        }
    }

    calcMinValue(moveY) {
        this.delta = this.touchY - moveY;
        if (this.delta <= 0) {
            this.calcMinValueDeltaIsNegative();
        }
        else {
            this.calcMinValueDeltaIsPositive();
        }
        this.updateModifier();
        this.fullModifier.invalidate();
        this.touchY = moveY;
        this.calBlur();
    }

    isHotRegion(touchX, touchY) {
        let radius = Math.sqrt(Math.pow(touchX - this.options.layoutOptions.x, 2) +
        Math.pow(touchY - this.options.layoutOptions.y, 2));
        if ((radius < this.options.layoutOptions.radius - this.options.styleOptions.activeTrackThickness) ||
            (radius > this.options.layoutOptions.radius)) {
            this.isFocus = false;
            return false;
        }
        let sin = Math.abs(touchY - this.options.layoutOptions.y) / radius;
        let radian = Math.asin(sin);
        let angle = radian / ANGULAR_TO_RADIAN;
        if ((touchX < this.options.layoutOptions.x) && (touchY > this.options.layoutOptions.y)) {
            angle = PI_RADIAN - angle;
        }
        else if ((touchX < this.options.layoutOptions.x) && (touchY < this.options.layoutOptions.y)) {
            angle = angle - PI_RADIAN;
        }
        else if ((touchX > this.options.layoutOptions.x) && (touchY < this.options.layoutOptions.y)) {
            angle = -angle;
        }
        if (this.options.layoutOptions.reverse) {
            if (angle > this.start / ANGULAR_TO_RADIAN || angle < this.end / ANGULAR_TO_RADIAN) {
                if (this.start > this.end) {
                    this.isFocus = false;
                    return false;
                }
                else {
                    this.isFocus = true;
                    return true;
                }
            }
            else {
                if (this.start > this.end) {
                    this.isFocus = true;
                    return true;
                }
                else {
                    this.isFocus = false;
                    return false;
                }
            }
        }
        else {
            if (angle < this.start / ANGULAR_TO_RADIAN || angle > this.end / ANGULAR_TO_RADIAN) {
                if (this.start > this.end) {
                    this.isFocus = true;
                    return true;
                }
                else {
                    this.isFocus = false;
                    return false;
                }
            }
            else {
                if (this.start > this.end) {
                    this.isFocus = false;
                    return false;
                }
                else {
                    this.isFocus = true;
                    return true;
                }
            }
        }
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

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.hitTestBehavior(HitTestMode.Transparent);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.hitTestBehavior(HitTestMode.Transparent);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Circle.create({ width: TOTAL_LENGTH, height: TOTAL_LENGTH });
            Circle.width(this.updateArcSlider());
            Circle.fill(BLUR_COLOR_DEFAULT);
            Circle.clipShape(new Path({ commands: this.clipPath }));
            Circle.backdropBlur(TRACK_BLUR_DEFAULT);
            Circle.hitTestBehavior(HitTestMode.Transparent);
        }, Circle);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel();
            Button.backgroundColor(BLUR_COLOR_DEFAULT);
            Button.drawModifier(this.fullModifier);
            Button.width(this.updateArcSlider());
            Button.height(this.totalHeight);
            Button.onTouch((event) => {
                if (event) {
                    if (event.type === TouchType.Down && !this.isEnlarged) {
                        this.touchY = event.touches[0].y;
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                            this.options.onTouch?.(event);
                            this.isEnlarged = true;
                            this.startTouchAnimator();
                            this.calBlur();
                        }
                    }
                    else if (event.type === TouchType.Down && this.isEnlarged) {
                        this.touchY = event.touches[0].y;
                        if (this.isHotRegion(event.touches[0].x, event.touches[0].y)) {
                            this.options.onTouch?.(event);
                            if (this.meter !== INVALID_TIMEOUT_ID) {
                                clearTimeout(this.meter);
                                this.meter = INVALID_TIMEOUT_ID;
                            }
                            if (this.isTouchAnimatorFinished) {
                                this.sliderValue = this.options.valueOptions.value;
                                this.calcClickValue(event.touches[0].x, event.touches[0].y);
                                this.startClickAnimator();
                            }
                            if (this.isClickAnimatorFinished) {
                                if (this.meter !== INVALID_TIMEOUT_ID) {
                                    clearTimeout(this.meter);
                                    this.meter = INVALID_TIMEOUT_ID;
                                }
                                this.touchY = event.touches[0].y;
                                this.calcValue(event.touches[0].y);
                                this.setSelected();
                                this.updateModifier();
                                this.fullModifier.invalidate();
                            }
                        }
                    }
                    else if (this.isEnlarged && event.type === TouchType.Up) {
                        this.options.onChange?.(this.options.valueOptions.value);
                        this.options.onTouch?.(event);
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        this.meter = setTimeout(() => {
                            if (this.isEnlarged) {
                                this.isTouchAnimatorFinished = false;
                                this.isClickAnimatorFinished = false;
                                this.isEnlarged = false;
                                this.startRestoreAnimator();
                                this.calBlur();
                            }
                        }, RESTORE_TIMEOUT);
                        if (this.options.layoutOptions.reverse) {
                            if (this.selectedMaxOrMin === MAX_STATUS && (this.selectArc < this.endCurrent)) {
                                if (this.start > this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.selectArcCurrent = this.selectArc;
                                    this.startMaxRestoreAnimator();
                                }
                                else if ((this.start < this.end) && (this.selectArc > this.start)) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.selectArcCurrent = this.selectArc;
                                    this.startMaxRestoreAnimator();
                                }
                            }
                            if (this.selectedMaxOrMin === MIN_STATUS && this.trackStart > this.start) {
                                if (this.start > this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.trackStartCurrent = this.trackStart;
                                    this.startMinRestoreAnimator();
                                    this.calBlur();
                                }
                                else if (this.start < this.end && this.trackStart < this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.trackStartCurrent = this.trackStart;
                                    this.startMinRestoreAnimator();
                                }
                            }
                        }
                        else {
                            if (this.selectedMaxOrMin === MAX_STATUS && (this.selectArc > this.endCurrent)) {
                                if (this.start > this.end && this.selectArc < this.start) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.selectArcCurrent = this.selectArc;
                                    this.startMaxRestoreAnimator();
                                }
                                else if (this.start < this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.selectArcCurrent = this.selectArc;
                                    this.startMaxRestoreAnimator();
                                }
                            }
                            if (this.selectedMaxOrMin === MIN_STATUS && this.trackStart < this.start) {
                                if (this.start > this.end && this.trackStart > this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.trackStartCurrent = this.trackStart;
                                    this.startMinRestoreAnimator();
                                    this.calBlur();
                                }
                                else if (this.start < this.end) {
                                    this.lineWidthCurrent = this.lineWidth;
                                    this.trackStartCurrent = this.trackStart;
                                    this.startMinRestoreAnimator();
                                    this.calBlur();
                                }
                            }
                        }
                    }
                    else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                        (event.type === TouchType.Move)) {
                        this.options.onTouch?.(event);
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        if (this.options.layoutOptions.reverse) {
                            if (this.start > this.endCurrent) {
                                if (((this.selectArc < this.endCurrent) || (nearEquals(this.selectArc, this.endCurrent))) &&
                                    (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.selectArc < this.endCurrent) && (this.delta <= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.trackStart >= this.start) && (nearEquals(this.options.valueOptions.value, this.options.valueOptions.min)) && (this.delta <= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else if ((this.trackStart > this.start) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else {
                                    this.calcValue(event.touches[0].y);
                                    this.selectedMaxOrMin = NORMAL_STATUS;
                                }
                            }
                            else {
                                if ((this.selectArc > this.start) && ((this.selectArc < this.endCurrent)) && (this.delta <= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.selectArc > this.start) && ((this.selectArc <= this.endCurrent) ||
                                    (nearEquals(this.selectArc, this.endCurrent))) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.trackStart > this.start) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else if ((this.trackStart >= this.start) && (nearEquals(this.options.valueOptions.value, this.options.valueOptions.min)) && (this.delta <= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else {
                                    this.calcValue(event.touches[0].y);
                                    this.selectedMaxOrMin = NORMAL_STATUS;
                                }
                            }
                        }
                        else {
                            if (this.start > this.endCurrent) {
                                if ((((this.selectArc < this.start) && (this.selectArc > this.endCurrent))) && (this.delta <= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.selectArc < this.start) && ((this.selectArc > this.endCurrent) ||
                                    (nearEquals(this.selectArc, this.endCurrent))) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((nearEquals(this.options.valueOptions.value, this.options.valueOptions.min)) &&
                                    (this.delta <= 0) && ((this.trackStart <= this.start) ||
                                    (nearEquals(this.selectArc, this.endCurrent)))) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else if ((this.trackStart < this.start) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else {
                                    this.calcValue(event.touches[0].y);
                                    this.selectedMaxOrMin = NORMAL_STATUS;
                                }
                            }
                            else {
                                if (((this.selectArc >= this.endCurrent) || (nearEquals(this.selectArc, this.endCurrent))) &&
                                    (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((this.selectArc > this.endCurrent) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MAX_STATUS;
                                    this.calcMaxValue(event.touches[0].y);
                                }
                                else if ((nearEquals(this.options.valueOptions.value, this.options.valueOptions.min)) &&
                                    (this.delta <= 0) && ((this.trackStart <= this.start) ||
                                    (nearEquals(this.selectArc, this.endCurrent)))) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else if ((this.trackStart < this.start) && (this.delta >= 0)) {
                                    this.selectedMaxOrMin = MIN_STATUS;
                                    this.calcMinValue(event.touches[0].y);
                                    this.calBlur();
                                }
                                else {
                                    this.calcValue(event.touches[0].y);
                                    this.selectedMaxOrMin = NORMAL_STATUS;
                                }
                            }
                        }
                    }
                }
            });
            Button.focusable(true);
            Button.focusOnTouch(true);
            Button.onDigitalCrown((event) => {
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
                                hilog.error(0x3900, 'ArcSlider', `watchhaptic.crown.strength2 is not supported`);
                            }
                        }
                        catch (error) {
                            let e = error;
                            hilog.error(0x3900, 'ArcSlider', `An unexpected error occurred in starting vibration.
                      Code: ${e.code}, message: ${e.message}`);
                        }
                        this.crownEventCounter = 0;
                    }
                    if (event.action === CrownAction.BEGIN && !this.isEnlarged) {
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        this.isEnlarged = true;
                        this.startTouchAnimator();
                        this.calBlur();
                        this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                        this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.normalRadius;
                        this.calcCrownValue(this.crownDeltaAngle);
                    }
                    else if (event.action === CrownAction.BEGIN && this.isEnlarged) {
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                        this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.normalRadius;
                        this.calcCrownValue(this.crownDeltaAngle);
                    }
                    else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                        (event.action === CrownAction.UPDATE)) {
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        this.crownDeltaAngle = this.getUIContext().px2vp(event.degree *
                        this.calcDisplayControlRatio(this.options.digitalCrownSensitivity)) / this.normalRadius;
                        this.calcCrownValue(this.crownDeltaAngle);
                    }
                    else if (this.isEnlarged && event.action === CrownAction.END) {
                        if (this.meter !== INVALID_TIMEOUT_ID) {
                            clearTimeout(this.meter);
                            this.meter = INVALID_TIMEOUT_ID;
                        }
                        this.meter = setTimeout(() => {
                            if (this.isEnlarged) {
                                this.isTouchAnimatorFinished = false;
                                this.isClickAnimatorFinished = false;
                                this.isEnlarged = false;
                                this.startRestoreAnimator();
                                this.calBlur();
                            }
                        }, RESTORE_TIMEOUT);
                    }
                }
            });
            Button.hitTestBehavior(HitTestMode.Transparent);
        }, Button);
        Button.pop();
        Stack.pop();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    ArcSlider,
    ArcSliderOptions,
    ArcSliderValueOptions,
    ArcSliderLayoutOptions,
    ArcSliderStyleOptions
};
