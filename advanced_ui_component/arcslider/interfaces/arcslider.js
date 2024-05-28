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

var __decorate = (this && this.__decorate) || function (t2, u2, v2, w2) {
    var x2 = arguments.length, y2 = x2 < 3 ? u2 : w2 === null ? w2 = Object.getOwnPropertyDescriptor(u2, v2) : w2, z2;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        y2 = Reflect.decorate(t2, u2, v2, w2);
    else
        for (var a3 = t2.length - 1; a3 >= 0; a3--)
            if (z2 = t2[a3])
                y2 = (x2 < 3 ? z2(y2) : x2 > 3 ? z2(u2, v2, y2) : z2(u2, v2)) || y2;
    return x2 > 3 && y2 && Object.defineProperty(u2, v2, y2), y2;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const animator = requireNapi('animator');

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
let ArcSliderValueOptions = class ArcSliderValueOptions {
    constructor(r2) {
        this.value = VALUE_DEFAULT;
        this.min = MIN_DEFAULT;
        this.max = MAX_DEFAULT;
        if (r2) {
            if (r2.value !== undefined && r2.value !== null) {
                this.value = r2.value;
            }
            if (r2.min !== undefined && r2.min !== null) {
                this.min = r2.min;
            }
            if (r2.max !== undefined && r2.max !== null) {
                this.max = r2.max;
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
    constructor(q2) {
        this.x = X_DEFAULT;
        this.y = Y_DEFAULT;
        this.radius = RADIUS_DEFAULT;
        this.padding = PADDING_DEFAULT;
        this.startAngle = START_ANGLE_DEFAULT;
        this.endAngle = END_ANGLE_DEFAULT;
        this.activeStartAngle = ACTIVE_START_ANGLE_DEFAULT;
        this.activeEndAngle = ACTIVE_END_ANGLE_DEFAULT;
        this.reverse = REVERSE_DEFAULT;
        if (q2) {
            if (q2.x !== undefined && q2.x !== null) {
                this.x = q2.x;
            }
            if (q2.y !== undefined && q2.y !== null) {
                this.y = q2.y;
            }
            if (q2.radius !== undefined && q2.radius !== null) {
                this.radius = q2.radius;
            }
            if (q2.padding !== undefined && q2.padding !== null) {
                this.padding = q2.padding;
            }
            if (q2.startAngle !== undefined && q2.startAngle !== null) {
                this.startAngle = q2.startAngle;
            }
            if (q2.endAngle !== undefined && q2.endAngle !== null) {
                this.endAngle = q2.endAngle;
            }
            if (q2.activeStartAngle !== undefined && q2.activeStartAngle !== null) {
                this.activeStartAngle = q2.activeStartAngle;
            }
            if (q2.activeEndAngle !== undefined && q2.activeEndAngle !== null) {
                this.activeEndAngle = q2.activeEndAngle;
            }
            if (q2.reverse !== undefined && q2.reverse !== null) {
                this.reverse = q2.reverse;
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
    constructor(p2) {
        this.trackThickness = TRACK_THICKNESS_DEFAULT;
        this.activeTrackThickness = ACTIVE_TRACK_THICKNESS_DEFAULT;
        this.trackColor = TRACK_COLOR_DEFAULT;
        this.selectedColor = SELECTED_COLOR_DEFAULT;
        this.trackBlur = TRACK_BLUR_DEFAULT;
        if (p2) {
            if (p2.trackThickness !== undefined && p2.trackThickness !== null) {
                this.trackThickness = p2.trackThickness;
            }
            if (p2.activeTrackThickness !== undefined && p2.activeTrackThickness !== null) {
                this.activeTrackThickness = p2.activeTrackThickness;
            }
            if (p2.trackColor !== undefined && p2.trackColor !== null) {
                this.trackColor = p2.trackColor;
            }
            if (p2.selectedColor !== undefined && p2.selectedColor !== null) {
                this.selectedColor = p2.selectedColor;
            }
            if (p2.trackBlur !== undefined && p2.trackBlur !== null) {
                this.trackBlur = p2.trackBlur;
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
    constructor(k2) {
        this.valueOptions = new ArcSliderValueOptions();
        this.layoutOptions = new ArcSliderLayoutOptions();
        this.styleOptions = new ArcSliderStyleOptions();
        this.onTouch = (o2) => {
        };
        this.onChange = (n2) => {
        };
        if (k2) {
            if (k2.valueOptions !== undefined && k2.valueOptions !== null) {
                this.valueOptions = k2.valueOptions;
            }
            if (k2.layoutOptions !== undefined && k2.layoutOptions !== null) {
                this.layoutOptions = k2.layoutOptions;
            }
            if (k2.styleOptions !== undefined && k2.styleOptions !== null) {
                this.styleOptions = k2.styleOptions;
            }
            if (k2.onTouch !== undefined && k2.onTouch !== null) {
                this.onTouch = k2.onTouch;
            }
            if (k2.onChange !== undefined && k2.onChange !== null) {
                this.onChange = k2.onChange;
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
], ArcSliderOptions.prototype, "onTouch", void 0);
__decorate([
    Trace
], ArcSliderOptions.prototype, "onChange", void 0);
ArcSliderOptions = __decorate([
    ObservedV2
], ArcSliderOptions);
export { ArcSliderOptions };
export class ArcSlider extends ViewPU {
    constructor(e2, f2, g2, h2 = -1, i2 = undefined, j2) {
        super(e2, g2, h2, j2);
        if (typeof i2 === "function") {
            this.paramsGenerator_ = i2;
        }
        this.options = new ArcSliderOptions();
        this.settings = new RenderingContextSettings(true);
        this.trackContext = new CanvasRenderingContext2D(this.settings);
        this.sliderContext = new CanvasRenderingContext2D(this.settings);
        this.touchAnimator = undefined;
        this.restoreAnimator = undefined;
        this.clickSelectedAnimator = undefined;
        this.maxRestoreAnimator = undefined;
        this.minRestoreAnimator = undefined;
        this.delta = 0;
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
        this.setInitiallyProvidedValue(f2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(d2) {
        if (d2.options !== undefined) {
            this.options = d2.options;
        }
        if (d2.settings !== undefined) {
            this.settings = d2.settings;
        }
        if (d2.trackContext !== undefined) {
            this.trackContext = d2.trackContext;
        }
        if (d2.sliderContext !== undefined) {
            this.sliderContext = d2.sliderContext;
        }
        if (d2.touchAnimator !== undefined) {
            this.touchAnimator = d2.touchAnimator;
        }
        if (d2.restoreAnimator !== undefined) {
            this.restoreAnimator = d2.restoreAnimator;
        }
        if (d2.clickSelectedAnimator !== undefined) {
            this.clickSelectedAnimator = d2.clickSelectedAnimator;
        }
        if (d2.maxRestoreAnimator !== undefined) {
            this.maxRestoreAnimator = d2.maxRestoreAnimator;
        }
        if (d2.minRestoreAnimator !== undefined) {
            this.minRestoreAnimator = d2.minRestoreAnimator;
        }
        if (d2.delta !== undefined) {
            this.delta = d2.delta;
        }
        if (d2.lineWidth !== undefined) {
            this.lineWidth = d2.lineWidth;
        }
        if (d2.lineWidthCurrent !== undefined) {
            this.lineWidthCurrent = d2.lineWidthCurrent;
        }
        if (d2.normalRadius !== undefined) {
            this.normalRadius = d2.normalRadius;
        }
        if (d2.touchY !== undefined) {
            this.touchY = d2.touchY;
        }
        if (d2.endCurrent !== undefined) {
            this.endCurrent = d2.endCurrent;
        }
        if (d2.meter !== undefined) {
            this.meter = d2.meter;
        }
        if (d2.start !== undefined) {
            this.start = d2.start;
        }
        if (d2.end !== undefined) {
            this.end = d2.end;
        }
        if (d2.trackStart !== undefined) {
            this.trackStart = d2.trackStart;
        }
        if (d2.trackStartCurrent !== undefined) {
            this.trackStartCurrent = d2.trackStartCurrent;
        }
        if (d2.selectArc !== undefined) {
            this.selectArc = d2.selectArc;
        }
        if (d2.selectArcCurrent !== undefined) {
            this.selectArcCurrent = d2.selectArcCurrent;
        }
        if (d2.selectRatioNow !== undefined) {
            this.selectRatioNow = d2.selectRatioNow;
        }
        if (d2.isEnlarged !== undefined) {
            this.isEnlarged = d2.isEnlarged;
        }
        if (d2.isTouchAnimatorFinished !== undefined) {
            this.isTouchAnimatorFinished = d2.isTouchAnimatorFinished;
        }
        if (d2.isClickAnimatorFinished !== undefined) {
            this.isClickAnimatorFinished = d2.isClickAnimatorFinished;
        }
        if (d2.clickValue !== undefined) {
            this.clickValue = d2.clickValue;
        }
        if (d2.sliderValue !== undefined) {
            this.sliderValue = d2.sliderValue;
        }
        if (d2.startAngle !== undefined) {
            this.startAngle = d2.startAngle;
        }
        if (d2.endAngle !== undefined) {
            this.endAngle = d2.endAngle;
        }
        if (d2.activeStartAngle !== undefined) {
            this.activeStartAngle = d2.activeStartAngle;
        }
        if (d2.activeEndAngle !== undefined) {
            this.activeEndAngle = d2.activeEndAngle;
        }
        if (d2.selectedMaxOrMin !== undefined) {
            this.selectedMaxOrMin = d2.selectedMaxOrMin;
        }
        if (d2.totalWidth !== undefined) {
            this.totalWidth = d2.totalWidth;
        }
        if (d2.totalHeight !== undefined) {
            this.totalHeight = d2.totalHeight;
        }
    }
    updateStateVars(c2) {
    }
    purgeVariableDependenciesOnElmtId(b2) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
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
    updateArcSlider() {
        this.checkParam();
        this.setReverse();
        if (this.isEnlarged == false) {
            this.setNormal();
        }
        else {
            this.setSelected();
        }
        this.drawTrack();
        this.drawSelect();
        return this.totalWidth;
    }
    setReverse() {
        if (!this.options.layoutOptions.reverse) {
            let x1 = this.startAngle;
            let y1 = this.endAngle;
            let z1 = this.activeStartAngle;
            let a2 = this.activeEndAngle;
            this.startAngle = y1;
            this.endAngle = x1;
            this.activeStartAngle = a2;
            this.activeEndAngle = z1;
        }
    }
    setNormal() {
        this.lineWidth = this.options.styleOptions.trackThickness;
        this.start = this.startAngle * ANGULAR_TO_RADIAN;
        this.end = this.endAngle * ANGULAR_TO_RADIAN;
        this.trackStart = this.startAngle * ANGULAR_TO_RADIAN;
        let w1 = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        if (this.end > this.start) {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = -w1 * (2 * Math.PI + this.start - this.end) + this.start;
            }
            else {
                this.selectArc = w1 * (this.end - this.start) + this.start;
            }
        }
        else {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = w1 * (this.end - this.start) + this.start;
            }
            else {
                this.selectArc = w1 * (2 * Math.PI + this.start - this.end) + this.start;
            }
        }
        this.normalRadius = this.options.layoutOptions.radius - (this.lineWidth / 2) -
            this.options.layoutOptions.padding;
    }
    setSelected() {
        let v1 = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        if (this.end > this.start) {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = -v1 * (2 * Math.PI + this.start - this.end) + this.start;
            }
            else {
                this.selectArc = v1 * (this.end - this.start) + this.start;
            }
        }
        else {
            if (this.options.layoutOptions.reverse) {
                this.selectArc = v1 * (this.end - this.start) + this.start;
            }
            else {
                this.selectArc = -v1 * (2 * Math.PI + this.start - this.end) + this.start;
            }
        }
        this.normalRadius = this.options.layoutOptions.radius - (this.lineWidth / 2);
    }
    drawTrack() {
        this.trackContext.clearRect(0, 0, this.totalWidth, this.totalHeight);
        this.trackContext.save();
        this.trackContext.filter = 'blur(' + vp2px(this.options.styleOptions.trackBlur) + 'px)';
        this.trackContext.strokeStyle = this.options.styleOptions.trackColor;
        this.trackContext.lineWidth = this.lineWidth;
        this.trackContext.beginPath();
        this.trackContext.arc(this.options.layoutOptions.x, this.options.layoutOptions.y, this.normalRadius, this.trackStart, this.end, this.options.layoutOptions.reverse);
        this.trackContext.stroke();
        this.trackContext.restore();
    }
    drawSelect() {
        if (!this.checkApprox(this.start, this.selectArc)) {
            this.sliderContext.clearRect(0, 0, this.totalWidth, this.totalHeight);
            this.sliderContext.save();
            this.sliderContext.lineWidth = this.lineWidth;
            this.sliderContext.strokeStyle = this.options.styleOptions.selectedColor;
            this.sliderContext.beginPath();
            this.sliderContext.arc(this.options.layoutOptions.x, this.options.layoutOptions.y, this.normalRadius, this.start, this.selectArc, this.options.layoutOptions.reverse);
            this.sliderContext.stroke();
            this.sliderContext.restore();
        }
        else {
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
        });
        this.touchAnimator.onFrame = (u1) => {
            this.lineWidth = u1 * (this.options.styleOptions.activeTrackThickness -
                this.options.styleOptions.trackThickness) + this.options.styleOptions.trackThickness;
            this.start = (u1 * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
            this.trackStart = (u1 * (this.activeStartAngle - this.startAngle) + this.startAngle) * ANGULAR_TO_RADIAN;
            this.end = (u1 * (this.activeEndAngle - this.endAngle) + this.endAngle) * ANGULAR_TO_RADIAN;
            this.setSelected();
            this.drawTrack();
            this.drawSelect();
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
        this.maxRestoreAnimator.onFrame = (r1) => {
            this.lineWidth = r1 * (this.options.styleOptions.activeTrackThickness - this.lineWidthCurrent) +
                this.lineWidthCurrent;
            this.selectArc = r1 * (this.endCurrent - this.selectArcCurrent) + this.selectArcCurrent;
            this.end = this.selectArc;
            this.drawTrack();
            this.drawSelect();
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
        this.minRestoreAnimator.onFrame = (p1) => {
            this.lineWidth = p1 * (this.options.styleOptions.activeTrackThickness - this.lineWidthCurrent) +
                this.lineWidthCurrent;
            this.trackStart = p1 * (this.activeStartAngle * ANGULAR_TO_RADIAN - this.trackStartCurrent) +
                this.trackStartCurrent;
            this.drawTrack();
            this.drawSelect();
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
        this.restoreAnimator.onFrame = (n1) => {
            this.lineWidth = n1 * (this.options.styleOptions.trackThickness -
                this.options.styleOptions.activeTrackThickness) + this.options.styleOptions.activeTrackThickness;
            this.start = (n1 * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) * ANGULAR_TO_RADIAN;
            this.trackStart = (n1 * (this.startAngle - this.activeStartAngle) + this.activeStartAngle) *
                ANGULAR_TO_RADIAN;
            this.end = (n1 * (this.endAngle - this.activeEndAngle) + this.activeEndAngle) * ANGULAR_TO_RADIAN;
            this.setNormal();
            this.drawTrack();
            this.drawSelect();
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
        this.clickSelectedAnimator.onFrame = (l1) => {
            this.options.valueOptions.value = l1;
            this.setSelected();
            this.drawSelect();
        };
        this.clickSelectedAnimator.onFinish = () => {
            this.isClickAnimatorFinished = true;
        };
        if (this.clickSelectedAnimator) {
            this.clickSelectedAnimator.play();
        }
    }
    calcClickValue(f1, g1) {
        if (g1 - this.options.layoutOptions.y > this.normalRadius) {
            g1 = this.normalRadius + this.options.layoutOptions.y;
        }
        else if (this.options.layoutOptions.y - g1 > this.normalRadius) {
            g1 = this.options.layoutOptions.y - this.normalRadius;
        }
        let h1 = Math.abs(g1 - this.options.layoutOptions.y) / this.normalRadius;
        let i1 = Math.asin(h1);
        if ((f1 < this.options.layoutOptions.x) && (g1 > this.options.layoutOptions.y)) {
            i1 = Math.PI - i1;
        }
        else if ((f1 < this.options.layoutOptions.x) && (g1 < this.options.layoutOptions.y)) {
            i1 = i1 - Math.PI;
        }
        else if ((f1 > this.options.layoutOptions.x) && (g1 < this.options.layoutOptions.y)) {
            i1 = -i1;
        }
        this.selectArc = i1;
        this.selectRatioNow = (this.selectArc - this.start) / (this.end - this.start);
        this.selectRatioNow = Math.min(1, this.selectRatioNow);
        this.selectRatioNow = Math.max(0, this.selectRatioNow);
        this.clickValue = this.selectRatioNow * (this.options.valueOptions.max - this.options.valueOptions.min) +
            this.options.valueOptions.min;
    }
    calcSin(e1) {
        if ((e1 >= Math.PI / 2) && (e1 <= Math.PI)) {
            return Math.sin(e1);
        }
        else if ((e1 <= Math.PI / 2) && (e1 >= -Math.PI / 2)) {
            return 2 - Math.sin(e1);
        }
        else if ((e1 >= -Math.PI) && (e1 <= -Math.PI / 2)) {
            return 4 + Math.sin(e1);
        }
        return 0;
    }
    calcValue(b1) {
        this.delta = this.touchY - b1;
        let c1 = this.normalRadius * (this.calcSin(this.activeEndAngle * ANGULAR_TO_RADIAN) -
            this.calcSin(this.activeStartAngle * ANGULAR_TO_RADIAN));
        let d1 = (this.options.valueOptions.value - this.options.valueOptions.min) /
            (this.options.valueOptions.max - this.options.valueOptions.min);
        d1 += this.delta / c1;
        d1 = Math.min(1, d1);
        d1 = Math.max(0, d1);
        this.options.valueOptions.value = d1 *
            (this.options.valueOptions.max - this.options.valueOptions.min) + this.options.valueOptions.min;
        this.setSelected();
        this.drawTrack();
        this.drawSelect();
        this.touchY = b1;
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
            if ((this.selectArc <= this.endCurrent) ||
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
            if ((this.selectArc <= (this.endCurrent + ANGLE_OVER_MIN * ANGULAR_TO_RADIAN)) &&
                (this.lineWidth >= this.options.styleOptions.activeTrackThickness * (1 - LENGTH_OVER_MIN))) {
                this.selectArc += (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN) * Math.abs(this.delta) /
                    (ANGLE_OVER_MIN * ANGULAR_TO_RADIAN * this.normalRadius + Math.abs(this.delta));
                this.lineWidth -= LENGTH_OVER_MIN * this.lineWidth * Math.abs(this.delta) /
                    (LENGTH_OVER_MIN * this.lineWidth + Math.abs(this.delta));
                this.end = this.selectArc;
            }
        }
    }
    calcMaxValue(a1) {
        this.delta = this.touchY - a1;
        if (this.delta >= 0) {
            this.calcMaxValueDeltaIsPositive();
        }
        else {
            this.calcMaxValueDeltaIsNegative();
        }
        this.drawTrack();
        this.drawSelect();
        this.touchY = a1;
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
    calcMinValue(z) {
        this.delta = this.touchY - z;
        if (this.delta <= 0) {
            this.calcMinValueDeltaIsNegative();
        }
        else {
            this.calcMinValueDeltaIsPositive();
        }
        this.drawTrack();
        this.drawSelect();
        this.touchY = z;
    }
    isHotRegion(t, u) {
        let v = Math.sqrt(Math.pow(t - this.options.layoutOptions.x, 2) +
            Math.pow(u - this.options.layoutOptions.y, 2));
        if ((v < this.options.layoutOptions.radius - this.options.styleOptions.activeTrackThickness) ||
            (v > this.options.layoutOptions.radius)) {
            return false;
        }
        let w = Math.abs(u - this.options.layoutOptions.y) / v;
        let x = Math.asin(w);
        let y = x / ANGULAR_TO_RADIAN;
        if ((t < this.options.layoutOptions.x) && (u > this.options.layoutOptions.y)) {
            y = PI_RADIAN - y;
        }
        else if ((t < this.options.layoutOptions.x) && (u < this.options.layoutOptions.y)) {
            y = y - PI_RADIAN;
        }
        else if ((t > this.options.layoutOptions.x) && (u < this.options.layoutOptions.y)) {
            y = -y;
        }
        if (this.options.layoutOptions.reverse) {
            if (y > this.start / ANGULAR_TO_RADIAN || y < this.end / ANGULAR_TO_RADIAN) {
                if (this.start > this.end) {
                    return false;
                }
                else {
                    return true;
                }
            }
            else {
                if (this.start > this.end) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else {
            if (y < this.start / ANGULAR_TO_RADIAN || y > this.end / ANGULAR_TO_RADIAN) {
                if (this.start > this.end) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                if (this.start > this.end) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
    }
    checkApprox(r, s) {
        return Math.abs(r - s) < APPROXIMATE_NUMBER;
    }
    initialRender() {
        this.observeComponentCreation2((p, q) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((n, o) => {
            Stack.create();
            Stack.width(this.totalWidth);
            Stack.height(this.totalHeight);
            Stack.hitTestBehavior(HitTestMode.Transparent);
        }, Stack);
        this.observeComponentCreation2((k, l) => {
            Canvas.create(this.trackContext);
            Canvas.width(this.updateArcSlider());
            Canvas.height(this.totalHeight);
            Canvas.onReady(() => {
                this.trackContext.lineCap = 'round';
                this.setNormal();
                this.drawTrack();
                this.drawSelect();
            });
            Canvas.hitTestBehavior(HitTestMode.Transparent);
        }, Canvas);
        Canvas.pop();
        this.observeComponentCreation2((e, f) => {
            Canvas.create(this.sliderContext);
            Canvas.width(this.totalWidth);
            Canvas.height(this.totalHeight);
            Canvas.onReady(() => {
                this.sliderContext.lineCap = 'round';
                this.setNormal();
                this.drawTrack();
                this.drawSelect();
            });
            Canvas.onTouch((i) => {
                if (i) {
                    if (i.type === TouchType.Down && this.isEnlarged === false) {
                        clearTimeout(this.meter);
                        if (this.isHotRegion(i.touches[0].x, i.touches[0].y)) {
                            this.options.onTouch?.(i);
                            this.isEnlarged = true;
                            this.startTouchAnimator();
                        }
                    }
                    else if (i.type === TouchType.Down && this.isEnlarged) {
                        this.touchY = i.touches[0].y;
                        if (this.isHotRegion(i.touches[0].x, i.touches[0].y)) {
                            this.options.onTouch?.(i);
                            clearTimeout(this.meter);
                            if (this.isTouchAnimatorFinished) {
                                this.sliderValue = this.options.valueOptions.value;
                                this.calcClickValue(i.touches[0].x, i.touches[0].y);
                                this.startClickAnimator();
                            }
                            if (this.isClickAnimatorFinished) {
                                clearTimeout(this.meter);
                                this.touchY = i.touches[0].y;
                                this.calcValue(i.touches[0].y);
                                this.setSelected();
                                this.drawTrack();
                                this.drawSelect();
                            }
                        }
                    }
                    else if (this.isEnlarged && i.type === TouchType.Up) {
                        this.options.onChange?.(this.options.valueOptions.value);
                        this.options.onTouch?.(i);
                        clearTimeout(this.meter);
                        this.meter = setTimeout(() => {
                            if (this.isEnlarged) {
                                this.isTouchAnimatorFinished = false;
                                this.isClickAnimatorFinished = false;
                                this.isEnlarged = false;
                                this.startRestoreAnimator();
                            }
                        }, 3000);
                        if (this.options.layoutOptions.reverse) {
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
                        }
                        else {
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
                    }
                    else if ((this.isEnlarged) && (this.isTouchAnimatorFinished) &&
                        (i.type === TouchType.Move)) {
                        this.options.onTouch?.(i);
                        clearTimeout(this.meter);
                        if (this.options.layoutOptions.reverse) {
                            if (((this.selectArc < this.endCurrent) || (this.checkApprox(this.selectArc, this.endCurrent))) &&
                                (this.delta >= 0)) {
                                this.selectedMaxOrMin = MAX_STATUS;
                                this.calcMaxValue(i.touches[0].y);
                            }
                            else if ((this.selectArc < this.endCurrent) && (this.delta <= 0)) {
                                this.selectedMaxOrMin = MAX_STATUS;
                                this.calcMaxValue(i.touches[0].y);
                            }
                            else if ((this.trackStart >= this.start) && (this.checkApprox(this.options.valueOptions.value, this.options.valueOptions.min)) && (this.delta <= 0)) {
                                this.selectedMaxOrMin = MIN_STATUS;
                                this.calcMinValue(i.touches[0].y);
                            }
                            else if ((this.trackStart > this.start) && (this.delta >= 0)) {
                                this.selectedMaxOrMin = MIN_STATUS;
                                this.calcMinValue(i.touches[0].y);
                            }
                            else {
                                this.calcValue(i.touches[0].y);
                                this.selectedMaxOrMin = NORMAL_STATUS;
                            }
                        }
                        else {
                            if (((this.selectArc > this.endCurrent) || (this.checkApprox(this.selectArc, this.endCurrent))) &&
                                (this.delta <= 0)) {
                                this.selectedMaxOrMin = MAX_STATUS;
                                this.calcMaxValue(i.touches[0].y);
                            }
                            else if ((this.selectArc > this.endCurrent) && (this.delta >= 0)) {
                                this.selectedMaxOrMin = MAX_STATUS;
                                this.calcMaxValue(i.touches[0].y);
                            }
                            else if ((this.checkApprox(this.options.valueOptions.value, this.options.valueOptions.min)) &&
                                (this.delta >= 0) && ((this.trackStart <= this.start) ||
                                (this.checkApprox(this.selectArc, this.endCurrent)))) {
                                this.selectedMaxOrMin = MIN_STATUS;
                                this.calcMinValue(i.touches[0].y);
                            }
                            else if ((this.trackStart < this.start) && (this.delta <= 0)) {
                                this.selectedMaxOrMin = MIN_STATUS;
                                this.calcMinValue(i.touches[0].y);
                            }
                            else {
                                this.calcValue(i.touches[0].y);
                                this.selectedMaxOrMin = NORMAL_STATUS;
                            }
                        }
                    }
                }
            });
            Canvas.hitTestBehavior(HitTestMode.Transparent);
        }, Canvas);
        Canvas.pop();
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
