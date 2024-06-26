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
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const measure = requireNapi('measure');
const Curves = globalThis.requireNativeModule("ohos.curves");
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
export var ArcButtonTypeMode;
(function (ArcButtonTypeMode) {
    ArcButtonTypeMode[ArcButtonTypeMode["TOP_EDGE"] = 0] = "TOP_EDGE";
    ArcButtonTypeMode[ArcButtonTypeMode["BOTTOM_EDGE"] = 1] = "BOTTOM_EDGE";
})(ArcButtonTypeMode || (ArcButtonTypeMode = {}));
export var ArcButtonStyleMode;
(function (ArcButtonStyleMode) {
    ArcButtonStyleMode[ArcButtonStyleMode["EMPHASIZED"] = 0] = "EMPHASIZED";
    ArcButtonStyleMode[ArcButtonStyleMode["NORMAL_LIGHT"] = 1] = "NORMAL_LIGHT";
    ArcButtonStyleMode[ArcButtonStyleMode["NORMAL_DEEP"] = 2] = "NORMAL_DEEP";
    ArcButtonStyleMode[ArcButtonStyleMode["EMPHASIZED_WARNING"] = 3] = "EMPHASIZED_WARNING";
})(ArcButtonStyleMode || (ArcButtonStyleMode = {}));
var ArcButtonStatus;
(function (ArcButtonStatus) {
    ArcButtonStatus[ArcButtonStatus["NORMAL"] = 0] = "NORMAL";
    ArcButtonStatus[ArcButtonStatus["PRESSED"] = 1] = "PRESSED";
    ArcButtonStatus[ArcButtonStatus["UNAVAILABLE"] = 2] = "UNAVAILABLE";
})(ArcButtonStatus || (ArcButtonStatus = {}));
export var ArkButtonClickEffectStyle;
(function (ArkButtonClickEffectStyle) {
    ArkButtonClickEffectStyle[ArkButtonClickEffectStyle["NONE"] = 0] = "NONE";
    ArkButtonClickEffectStyle[ArkButtonClickEffectStyle["LIGHT"] = 1] = "LIGHT";
    ArkButtonClickEffectStyle[ArkButtonClickEffectStyle["MIDDLE"] = 2] = "MIDDLE";
    ArkButtonClickEffectStyle[ArkButtonClickEffectStyle["HEAVY"] = 3] = "HEAVY";
})(ArkButtonClickEffectStyle || (ArkButtonClickEffectStyle = {}));
let ArcButtonOptions = class ArcButtonOptions {
    constructor(options) {
        this.type = options.type ?? ArcButtonTypeMode.BOTTOM_EDGE;
        this.width = options.width ?? Constants.UPPER_ARC_CIRCLE_R;
        this.height = options.height ?? (Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R +
            Constants.UPPER_ARC_CIRCLE_R - Constants.UPPER_ARC_CIRCLE_CENTER_Y);
        this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED;
        this.status = options.status ?? ArcButtonStatus.NORMAL;
        this.resourceText = options.resourceText ?? '';
        this.touchEffect = options.touchEffect ?? ArkButtonClickEffectStyle.NONE;
        this.backgroundColor = options.backgroundColor ?? Color.Black;
        this.shadowColor = options.shadowColor ?? '#000000';
        this.shadowEnabled = options.shadowEnabled ?? false;
        this.textSize = options.textSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE, LengthUnit.FP);
        this.textColor = options.textColor ?? Color.White;
        this.pressedTextColor = options.pressedTextColor ?? Color.White;
        this.textStyle = options.textStyle ?? FontStyle.Normal;
        this.textFamily = options.textFamily ?? '';
        this.textMargin = options.textMargin ?? {
            left: Constants.TEXT_HORIZONTAL_MARGIN,
            top: Constants.TEXT_MARGIN_TOP,
            right: Constants.TEXT_HORIZONTAL_MARGIN,
            bottom: Constants.TEXT_MARGIN_BOTTOM
        };
    }
};
__decorate([
    Trace
], ArcButtonOptions.prototype, "type", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "width", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "height", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "styleMode", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "status", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "resourceText", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "touchEffect", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "backgroundColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "shadowColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "shadowEnabled", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "textSize", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "textColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "pressedTextColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "textStyle", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "textFamily", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "textMargin", void 0);
ArcButtonOptions = __decorate([
    ObservedV2
], ArcButtonOptions);
export { ArcButtonOptions };
export class ArcButton extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("options", (params && "options" in params) ? params.options : undefined);
        this.btnColor = Color.Black;
        this.btnNormalColor = Color.Black;
        this.btnPressColor = Color.Black;
        this.btnDisableColor = Color.Black;
        this.textNormalColor = Color.White;
        this.textDisableColor = Color.White;
        this.btnWidth = 0;
        this.btnHeight = 0;
        this.scaleX = 1;
        this.scaleY = 1;
        this.translateY = 0;
        this.isUp = false;
        this.textWidth = 0;
        this.textHeight = 0;
        this.textColor = Color.White;
        this.isExceed = false;
        this.settings = new RenderingContextSettings(true);
        this.context = new CanvasRenderingContext2D(this.settings);
        this.isReady = false;
        this.curves = {};
        this.scaleValue = 1;
        this.path2D = new Path2D();
        this.circularCrossPointUtil = new CircularCrossPointUtil();
        this.upperArcCircleR = 0;
        this.upperArcCircleY = 0;
        this.finalizeConstruction();
    }
    optionsChange() {
        this.judgeTextWidth();
        this.btnColor = this.options.backgroundColor;
        this.textColor = this.options.textColor;
        this.changeStatus();
    }
    changeStatus() {
        switch (this.options.styleMode) {
            case ArcButtonStyleMode.EMPHASIZED:
                this.btnNormalColor = Constants.EMPHASIZED_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.EMPHASIZED_TEXT_COLOR;
                this.btnPressColor = Constants.EMPHASIZED_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.EMPHASIZED_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.EMPHASIZED_DISABLE_TEXT_COLOR;
                break;
            case ArcButtonStyleMode.NORMAL_LIGHT:
                this.btnNormalColor = Constants.NORMAL01_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.NORMAL01_TEXT_COLOR;
                this.btnPressColor = Constants.NORMAL01_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.NORMAL01_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.NORMAL01_DISABLE_TEXT_COLOR;
                break;
            case ArcButtonStyleMode.NORMAL_DEEP:
                this.btnNormalColor = Constants.NORMAL02_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.NORMAL02_TEXT_COLOR;
                this.btnPressColor = Constants.NORMAL02_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.NORMAL02_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.NORMAL02_DISABLE_TEXT_COLOR;
                break;
            case ArcButtonStyleMode.EMPHASIZED_WARNING:
                this.btnNormalColor = Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.EMPHASIZEWARN_TEXT_COLOR;
                this.btnPressColor = Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR;
                break;
            default:
                break;
        }
        if (this.options.status === ArcButtonStatus.UNAVAILABLE) {
            this.btnColor = this.btnDisableColor;
            this.textColor = this.textDisableColor;
        }
        else {
            this.btnColor = this.btnNormalColor;
            this.textColor = this.textNormalColor;
        }
    }
    /**
     * 初始化数据
     */
    initValues() {
        this.isUp = this.options.type == ArcButtonTypeMode.TOP_EDGE;
        this.btnColor = this.options.backgroundColor;
        this.textColor = this.options.textColor;
        switch (this.options.touchEffect) {
            case ArkButtonClickEffectStyle.LIGHT:
                this.curves = Curves.interpolatingSpring(10, 1, 410, 38);
                this.scaleValue = 0.9;
                break;
            case ArkButtonClickEffectStyle.MIDDLE:
                this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
                this.scaleValue = 0.95;
                break;
            case ArkButtonClickEffectStyle.HEAVY:
                this.curves = Curves.interpolatingSpring(0, 1, 240, 28);
                this.scaleValue = 0.95;
                break;
            default:
                break;
        }
        this.changeStatus();
    }
    /**
     * 判断是否超出文本框宽度
     */
    judgeTextWidth() {
        let measureTextWidth = measure.measureText({
            textContent: this.options.resourceText,
            fontSize: this.options.textSize.value
        });
        this.isExceed = measureTextWidth > vp2px(this.textWidth);
    }
    aboutToAppear() {
        this.initValues();
        this.upperArcCircleR = this.options.width;
        this.upperArcCircleY = Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R + this.upperArcCircleR -
            this.options.height;
        this.circularCrossPointUtil.initData(this.upperArcCircleR, this.upperArcCircleY);
        this.circularCrossPointUtil.calculate().then((data) => {
            if (data == null) {
                return;
            }
            this.btnWidth = data.width + Constants.SHADOW_BLUR * 2;
            if (this.isUp) {
                this.btnHeight = data.height + Constants.SHADOW_BLUR + Constants.SHADOW_OFFSET_Y;
            }
            else {
                this.btnHeight = data.height + Constants.DISTANCE_FROM_BORDER * 2;
            }
            this.textWidth = data.width - this.options.textMargin.left - this.options.textMargin.right;
            this.judgeTextWidth();
            this.textHeight = data.height - this.options.textMargin.top - this.options.textMargin.bottom;
            let leftTopPoint = data.leftTopPoint;
            let rightTopPoint = data.rightTopPoint;
            let leftBottomPoint = data.leftBottomPoint;
            let rightBottomPoint = data.rightBottomPoint;
            let canvasLeftTopPoint = data.canvasLeftTop;
            canvasLeftTopPoint.x -= Constants.SHADOW_BLUR;
            canvasLeftTopPoint.y -= Constants.DISTANCE_FROM_BORDER;
            let pathStr = `M ${vp2px(leftTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftTopPoint.y - canvasLeftTopPoint.y)}
        A ${vp2px(Constants.UPPER_ARC_CIRCLE_R)} ${vp2px(Constants.UPPER_ARC_CIRCLE_R)},
        0, 0, 0, ${vp2px(rightTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightTopPoint.y - canvasLeftTopPoint.y)} ` +
                `M ${vp2px(rightTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightTopPoint.y - canvasLeftTopPoint.y)}
          A ${vp2px(Constants.CHAMFER_CIRCLE_R)} ${vp2px(Constants.CHAMFER_CIRCLE_R)}, 0, 0, 0,
          ${vp2px(rightBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightBottomPoint.y - canvasLeftTopPoint.y)} ` +
                `M ${vp2px(rightBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightBottomPoint.y - canvasLeftTopPoint.y)}
          A ${vp2px(Constants.LOWER_ARC_CIRCLE_R)} ${vp2px(Constants.LOWER_ARC_CIRCLE_R)},
          0, 0, 0, ${vp2px(leftBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftBottomPoint.y - canvasLeftTopPoint.y)} ` +
                `M ${vp2px(leftBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftBottomPoint.y - canvasLeftTopPoint.y)}
          A ${vp2px(Constants.CHAMFER_CIRCLE_R)} ${vp2px(Constants.CHAMFER_CIRCLE_R)}, 0, 0, 0,
          ${vp2px(leftTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftTopPoint.y - canvasLeftTopPoint.y)} ` +
                `M ${vp2px(leftTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftTopPoint.y - canvasLeftTopPoint.y)}
          L ${vp2px(rightTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightTopPoint.y - canvasLeftTopPoint.y)}
          L ${vp2px(rightBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(rightBottomPoint.y - canvasLeftTopPoint.y)}
          L ${vp2px(leftBottomPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftBottomPoint.y - canvasLeftTopPoint.y)}
          L ${vp2px(leftTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftTopPoint.y - canvasLeftTopPoint.y)}`;
            this.path2D = new Path2D(pathStr);
            this.doDraw();
        });
    }
    doDraw() {
        if (!this.isReady || this.path2D === undefined) {
            return;
        }
        let start = new Date().getTime();
        if (this.options.shadowEnabled) {
            this.context.shadowBlur = Constants.SHADOW_BLUR;
            this.context.shadowOffsetY = -Constants.SHADOW_OFFSET_Y;
            this.context.shadowColor = this.options.shadowColor;
        }
        this.context.beginPath();
        this.context.fillStyle = this.btnColor;
        this.context.fill(this.path2D);
    }
    buildLog() {
        return true;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Top });
            Context.animation(null);
            Stack.width(this.btnWidth);
            Stack.height(this.btnHeight);
            Stack.enabled(this.options.status !== ArcButtonStatus.UNAVAILABLE);
            Stack.opacity(this.options.status === ArcButtonStatus.UNAVAILABLE ? 0.4 : 1);
            Stack.scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.btnHeight });
            Stack.translate({ y: this.translateY });
            Stack.onTouch((event) => {
                let x = event.touches[0].windowX;
                let y = event.touches[0].windowY;
                switch (event.type) {
                    case TouchType.Down:
                        let isInPath = this.circularCrossPointUtil.isPointInPath(x, y, this.isUp);
                        if (!isInPath) {
                            return;
                        }
                        this.scaleX = this.scaleValue;
                        this.scaleY = this.scaleValue;
                        this.btnColor = this.btnPressColor;
                        break;
                    case TouchType.Up:
                        this.scaleX = 1;
                        this.scaleY = 1;
                        this.btnColor = this.btnNormalColor;
                        break;
                    default:
                        break;
                }
            });
            Stack.onClick((event) => {
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buildLog()) {
                this.ifElseBranchUpdateFunction(0, () => {
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Canvas.create(this.context);
            Canvas.onReady(() => {
                this.isReady = true;
                this.doDraw();
            });
            Canvas.width(this.btnWidth);
            Canvas.height(this.btnHeight);
            Canvas.rotate({
                angle: this.isUp ? 0 : 180
            });
        }, Canvas);
        Canvas.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isExceed) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.options.resourceText);
                        Text.width(this.textWidth);
                        Text.height(this.textHeight);
                        Text.fontColor(this.textColor);
                        Text.fontSize(this.options.textSize.value);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontStyle(this.options.textStyle);
                        Text.fontFamily(this.options.textFamily);
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.MARQUEE });
                        Text.margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top });
                    }, Text);
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.options.resourceText);
                        Text.width(this.textWidth);
                        Text.height(this.textHeight);
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor(this.textColor);
                        Text.maxFontSize(this.options.textSize.value);
                        Text.minFontSize(new LengthMetrics(Constants.MIN_FONT_SIZE, LengthUnit.FP).value);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontStyle(this.options.textStyle);
                        Text.fontFamily(this.options.textFamily);
                        Text.maxLines(1);
                        Text.margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top });
                    }, Text);
                    Text.pop();
                });
            }
        }, If);
        If.pop();
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
], ArcButton.prototype, "options", void 0);
__decorate([
    Local
], ArcButton.prototype, "btnColor", void 0);
__decorate([
    Local
], ArcButton.prototype, "btnWidth", void 0);
__decorate([
    Local
], ArcButton.prototype, "btnHeight", void 0);
__decorate([
    Local
], ArcButton.prototype, "scaleX", void 0);
__decorate([
    Local
], ArcButton.prototype, "scaleY", void 0);
__decorate([
    Local
], ArcButton.prototype, "translateY", void 0);
__decorate([
    Local
], ArcButton.prototype, "textWidth", void 0);
__decorate([
    Local
], ArcButton.prototype, "textHeight", void 0);
__decorate([
    Local
], ArcButton.prototype, "textColor", void 0);
__decorate([
    Local
], ArcButton.prototype, "isExceed", void 0);
__decorate([
    Monitor('options')
], ArcButton.prototype, "optionsChange", null);
__decorate([
    Monitor('btnColor')
], ArcButton.prototype, "doDraw", null);
class CircularCrossPointUtil {
    constructor() {
        this.mirrorUpperArcCircleY = 0;
        this.upperArcCircleY = 0;
        this.upperArcCircleR = 0;
    }
    initData(upperArcCircleR, upperArcCircleY) {
        this.upperArcCircleR = upperArcCircleR;
        this.upperArcCircleY = upperArcCircleY;
        let distance = this.calculateDistance(Constants.LOWER_ARC_CIRCLE_CENTER_X, Constants.LOWER_ARC_CIRCLE_CENTER_Y, Constants.UPPER_ARC_CIRCLE_CENTER_X, this.upperArcCircleY);
        this.mirrorUpperArcCircleY = distance - Constants.LOWER_ARC_CIRCLE_CENTER_Y;
    }
    async calculate() {
        let lowerArcCircleR = Constants.LOWER_ARC_CIRCLE_R;
        let lowerArcCircleCenterX = Constants.LOWER_ARC_CIRCLE_CENTER_X;
        let lowerArcCircleCenterY = Constants.LOWER_ARC_CIRCLE_CENTER_Y;
        let upperArcCircleCenterX = Constants.UPPER_ARC_CIRCLE_CENTER_X;
        let chamferCircleR = Constants.CHAMFER_CIRCLE_R;
        let upperArcCircle = new Circle(this.upperArcCircleR, lowerArcCircleCenterX, lowerArcCircleCenterY); //大圆
        let lowerArcCircle = new Circle(lowerArcCircleR, upperArcCircleCenterX, this.upperArcCircleY); //小圆
        let external_intersections = this.findCircleIntersections(upperArcCircle, lowerArcCircle);
        if (external_intersections.length > 1) {
            let intersection1 = external_intersections[0];
            let intersection2 = external_intersections[1];
            let inside_intersections = this.findCircleIntersections(new Circle(this.upperArcCircleR - chamferCircleR, lowerArcCircleCenterX, lowerArcCircleCenterY), new Circle(lowerArcCircleR - chamferCircleR, upperArcCircleCenterX, this.upperArcCircleY));
            if (inside_intersections.length > 1) {
                intersection1 = inside_intersections[0];
                intersection2 = inside_intersections[1];
                if (intersection1.x > intersection2.x) {
                    let mid = intersection1;
                    intersection1 = intersection2;
                    intersection2 = mid;
                }
                let tp1 = this.calculateIntersection(new Point(lowerArcCircleCenterX, lowerArcCircleCenterY), this.upperArcCircleR, new Point(intersection1.x, intersection1.y));
                let tp2 = this.calculateIntersection(new Point(lowerArcCircleCenterX, lowerArcCircleCenterY), this.upperArcCircleR, new Point(intersection2.x, intersection2.y));
                let tp3 = this.calculateIntersection(new Point(upperArcCircleCenterX, this.upperArcCircleY), lowerArcCircleR, new Point(intersection2.x, intersection2.y));
                let tp4 = this.calculateIntersection(new Point(upperArcCircleCenterX, this.upperArcCircleY), lowerArcCircleR, new Point(intersection1.x, intersection1.y));
                let width = this.calculateDistance(intersection1.x, intersection1.y, intersection2.x, intersection2.y)
                    + chamferCircleR * 2;
                let height = (this.upperArcCircleR + lowerArcCircleR) - this.calculateDistance(lowerArcCircleCenterX, lowerArcCircleCenterY, upperArcCircleCenterX, this.upperArcCircleY);
                let canvasLeftTop = new Point(intersection1.x - chamferCircleR, this.upperArcCircleY - lowerArcCircleR);
                return new AllPoints(width, height, tp1, tp2, tp4, tp3, canvasLeftTop);
            }
        }
        return null;
    }
    /**
     * 判断点是否在上弧圆内
     * @param x 触摸点X
     * @param y 触摸点Y
     * @returns 是否在上弧圆内
     */
    isPointInPath(x, y, isUp) {
        let distance = this.calculateDistance(x, y, Constants.UPPER_ARC_CIRCLE_CENTER_X, isUp ? this.mirrorUpperArcCircleY
            : this.upperArcCircleY);
        return distance <= this.upperArcCircleR;
    }
    /**
     * 计算两点间距离
     * @param point1 点1
     * @param point2 点2
     * @returns 距离
     */
    calculateDistance(x1, y1, x2, y2) {
        return Math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2);
    }
    calculateIntersection(circleCenter, circleRadius, point) {
        let h = circleCenter.x;
        let k = circleCenter.y;
        let x = point.x;
        let y = point.y;
        let m = 0;
        if (x != h) {
            m = (y - k) / (x - h);
        }
        else {
            m = -1;
        }
        let b = 0;
        if (m != -1) {
            b = y - m * x;
        }
        let resultPoint = [];
        if (m != -1) {
            let A = Math.pow(m, 2) + 1;
            let B = 2 * (m * b - m * k - h);
            let C = k ** 2 - circleRadius ** 2 + h ** 2 - 2 * b * k + b ** 2;
            let x1 = (-B + (B ** 2 - 4 * A * C) ** 0.5) / (2 * A);
            let x2 = (-B - (B ** 2 - 4 * A * C) ** 0.5) / (2 * A);
            let y1 = m * x1 + b;
            let y2 = m * x2 + b;
            resultPoint = [new Point(x1, y1), new Point(x2, y2)];
        }
        else {
            let x1 = h;
            let y1 = k + (circleRadius ** 2 - (x1 - h) ** 2) ** 0.5;
            let y2 = k - (circleRadius ** 2 - (x1 - h) ** 2) ** 0.5;
            resultPoint = [new Point(x1, y1), new Point(x1, y2)];
        }
        let d1 = this.calculateDistance(resultPoint[0].x, resultPoint[0].y, point.x, point.y);
        let d2 = this.calculateDistance(resultPoint[1].x, resultPoint[1].y, point.x, point.y);
        if (d1 < d2) {
            return resultPoint[0];
        }
        else {
            return resultPoint[1];
        }
    }
    /**
     * 查找两圆的交点
     * @param C1 第一个圆
     * @param c2 第二个圆
     * @returns 两圆相交的点的数组
     */
    findCircleIntersections(firstCircus, secondCircus) {
        let firstCircusR = firstCircus.radius;
        let firstCircusCenterX = firstCircus.x;
        let firstCircusCenterY = firstCircus.y;
        let secondCircusR = secondCircus.radius;
        let secondCircusCenterX = secondCircus.x;
        let secondCircusCenterY = secondCircus.y;
        // 计算两个圆心之间的距离
        let distance = Math.sqrt((firstCircusCenterX - secondCircusCenterX) ** 2 + (firstCircusCenterY -
            secondCircusCenterY) ** 2);
        // 检查异常情况
        if (distance > firstCircusR + secondCircusR) {
            //两个圆分离，不相交
            return [];
        }
        else if (distance < Math.abs(firstCircusR - secondCircusR)) {
            //一个圆包含在另一个圆内，不相交
            return [];
        }
        else if (distance === 0 && firstCircusR === secondCircusR) {
            //两个圆完全重合，具有无穷多交点
            return [];
        }
        // 计算交点
        let a = (firstCircusR ** 2 - secondCircusR ** 2 + distance ** 2) / (2 * distance);
        let h = Math.sqrt(firstCircusR ** 2 - a ** 2);
        // 中间变量
        let x2 = firstCircusCenterX + a * (secondCircusCenterX - firstCircusCenterX) / distance;
        let y2 = firstCircusCenterY + a * (secondCircusCenterY - firstCircusCenterY) / distance;
        // 交点
        let intersection1 = new Point(x2 + h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 -
            h * (secondCircusCenterX - firstCircusCenterX) / distance);
        let intersection2 = new Point(x2 - h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 +
            h * (secondCircusCenterX - firstCircusCenterX) / distance);
        return [intersection1, intersection2];
    }
}
class Circle {
    constructor(radius, x, y) {
        this.radius = radius;
        this.x = x;
        this.y = y;
    }
}
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}
class AllPoints {
    constructor(width, height, leftTopPoint, rightTopPoint, leftBottomPoint, rightBottomPoint, canvasLeftTop) {
        this.width = width;
        this.height = height;
        this.leftTopPoint = leftTopPoint;
        this.rightTopPoint = rightTopPoint;
        this.leftBottomPoint = leftBottomPoint;
        this.rightBottomPoint = rightBottomPoint;
        this.canvasLeftTop = canvasLeftTop;
    }
}
class Constants {
}
/**
 * 上弧圆圆心X坐标
 */
Constants.UPPER_ARC_CIRCLE_CENTER_X = 116.5;
/**
 * 上弧圆圆心Y坐标
 */
Constants.UPPER_ARC_CIRCLE_CENTER_Y = 514;
/**
 * 上弧圆半径
 */
Constants.UPPER_ARC_CIRCLE_R = 330;
/**
 * 下弧圆圆心X坐标
 */
Constants.LOWER_ARC_CIRCLE_CENTER_X = 116.5;
/**
 * 下弧圆圆心Y坐标
 */
Constants.LOWER_ARC_CIRCLE_CENTER_Y = 116.5;
/**
 * 下弧圆半径
 */
Constants.LOWER_ARC_CIRCLE_R = 115.5;
/**
 * 倒角圆半径
 */
Constants.CHAMFER_CIRCLE_R = 8;
/**
 * 最大文字大小
 */
Constants.MAX_FONT_SIZE = 19;
/**
 * 最小文字大小
 */
Constants.MIN_FONT_SIZE = 13;
/**
 * 阴影半径
 */
Constants.SHADOW_BLUR = 4;
/**
 * Y偏移
 */
Constants.SHADOW_OFFSET_Y = 3;
/**
 * 按钮与边框距离
 */
Constants.DISTANCE_FROM_BORDER = 1;
/**
 * 文本间距
 */
Constants.TEXT_HORIZONTAL_MARGIN = 24;
Constants.TEXT_MARGIN_TOP = 10;
Constants.TEXT_MARGIN_BOTTOM = 16;
Constants.EMPHASIZED_NORMAL_BTN_COLOR = '#1F71FF';
Constants.EMPHASIZED_TEXT_COLOR = '#FFFFFF';
Constants.EMPHASIZED_PRESSED_BTN_COLOR = '#2B6EC2';
Constants.EMPHASIZED_DISABLE_BTN_COLOR = '#991F71FF';
Constants.EMPHASIZED_DISABLE_TEXT_COLOR = '#99FFFFFF';
Constants.NORMAL01_NORMAL_BTN_COLOR = '#132230';
Constants.NORMAL01_TEXT_COLOR = '#5EA1FF';
Constants.NORMAL01_PRESSED_BTN_COLOR = '#25353E';
Constants.NORMAL01_DISABLE_BTN_COLOR = '#132230';
Constants.NORMAL01_DISABLE_TEXT_COLOR = '#995ea1ff';
Constants.NORMAL02_NORMAL_BTN_COLOR = '#1D201C';
Constants.NORMAL02_TEXT_COLOR = '#5EA1FF';
Constants.NORMAL02_PRESSED_BTN_COLOR = '#30342D';
Constants.NORMAL02_DISABLE_BTN_COLOR = '#1E211D';
Constants.NORMAL02_DISABLE_TEXT_COLOR = '#995ea1ff';
Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR = '#BF2629';
Constants.EMPHASIZEWARN_TEXT_COLOR = '#FFFFFF';
Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR = '#9E342F';
Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR = '#3E0d0c';
Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR = '#99FFFFFF';
//# sourceMappingURL=ArcButton.js.map
export default { ArcButton, ArcButtonOptions, TypeMode, ArcButtonStyleMode, ArcButtonStatus, ClickEffectStatus }