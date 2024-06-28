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
import measure from '@ohos.measure'
import Curves from '@ohos.curves'
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';

export enum ArcButtonTypeMode {
  TOP_EDGE,
  BOTTOM_EDGE
}

export enum ArcButtonStyleMode {
  EMPHASIZED,
  NORMAL_LIGHT,
  NORMAL_DEEP,
  EMPHASIZED_WARNING
}

export enum ArcButtonStatus {
  NORMAL,
  PRESSED,
  UNAVAILABLE
}

export enum ArkButtonClickEffectStyle {
  NONE,
  LIGHT,
  MIDDLE,
  HEAVY
}

export interface ArcButtonMargin {
  left: number
  top: number
  right: number
  bottom: number
}

interface CommonArcButtonOptions {
  /**
   * 上下弧形按钮类型属性,默认为下弧形按钮
   */
  type?: ArcButtonTypeMode;

  /**
   *圆弧半径
   */
  width?: number;

  /**
   *弧形按钮上圆弧的最高点到下圆弧最低点的距离
   */
  height?: number;

  /**
   *强调、普通01、普通02、警告  默认是强调状态
   */
  styleMode?: ArcButtonStyleMode;

  /**
   *初始态、按压、不可用形态,默认为初始态
   */
  status?: ArcButtonStatus;

  /**
   *文字
   */
  resourceText?: ResourceStr;

  /**
   *按钮回弹效果动效
   */
  touchEffect?: ArkButtonClickEffectStyle;

  /**
   *按钮背景色
   */
  backgroundColor?: string | Color;

  /**
   *按钮背景色
   */
  shadowColor?: string;

  /**
   *打开关闭弧形按钮阴影
   */
  shadowEnabled?: boolean;

  /**
   *字体大小
   */
  textSize?: LengthMetrics;

  /**
   *字体颜色
   */
  textColor?: Color | string;

  /**
   *字体按压颜色
   */
  pressedTextColor?: Color | string;

  /**
   *文字样式
   */
  textStyle?: FontStyle;

  /**
   *文字字体族
   */
  textFamily?: string | Resource;

  /**
   *文字到边框的距离
   */
  textMargin?: ArcButtonMargin;
}

@ObservedV2
export class ArcButtonOptions {
  @Trace public  type: ArcButtonTypeMode;
  @Trace public  width: number;
  @Trace public height: number;
  @Trace public styleMode: ArcButtonStyleMode;
  @Trace public status: ArcButtonStatus;
  @Trace public resourceText: ResourceStr;
  @Trace public touchEffect: ArkButtonClickEffectStyle;
  @Trace public backgroundColor: string | Color;
  @Trace public shadowColor: string;
  @Trace public shadowEnabled: boolean;
  @Trace public textSize: LengthMetrics;
  @Trace public textColor: Color | string;
  @Trace public pressedTextColor: Color | string;
  @Trace public textStyle: FontStyle;
  @Trace public textFamily: string | Resource;
  @Trace public textMargin: ArcButtonMargin;
  public touchCallback?: Callback<TouchEvent>
  public onClickEvent?: Callback<ClickEvent>

  constructor(options: CommonArcButtonOptions) {
    this.type = options.type ?? ArcButtonTypeMode.BOTTOM_EDGE
    this.width = options.width ?? Constants.UPPER_ARC_CIRCLE_R
    this.height = options.height ?? (Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R +
    Constants.UPPER_ARC_CIRCLE_R - Constants.UPPER_ARC_CIRCLE_CENTER_Y)
    this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED
    this.status = options.status ?? ArcButtonStatus.NORMAL
    this.resourceText = options.resourceText ?? ''
    this.touchEffect = options.touchEffect ?? ArkButtonClickEffectStyle.NONE
    this.backgroundColor = options.backgroundColor ?? Color.Black
    this.shadowColor = options.shadowColor ?? '#000000'
    this.shadowEnabled = options.shadowEnabled ?? false
    this.textSize = options.textSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE, LengthUnit.FP)
    this.textColor = options.textColor ?? Color.White
    this.pressedTextColor = options.pressedTextColor ?? Color.White
    this.textStyle = options.textStyle ?? FontStyle.Normal
    this.textFamily = options.textFamily ?? ''
    this.textMargin = options.textMargin ?? {
      left: Constants.TEXT_HORIZONTAL_MARGIN,
      top: Constants.TEXT_MARGIN_TOP,
      right: Constants.TEXT_HORIZONTAL_MARGIN,
      bottom: Constants.TEXT_MARGIN_BOTTOM
    }
  }
}

@ComponentV2
export struct ArcButton {
  @Require @Param options: ArcButtonOptions
  @Local btnColor: string | Color = Color.Black
  private btnNormalColor: string | Color = Color.Black
  private btnPressColor: string | Color = Color.Black
  private btnDisableColor: string | Color = Color.Black
  private textNormalColor: Color | string = Color.White
  private textDisableColor: Color | string = Color.White
  @Local btnWidth: number = 0
  @Local btnHeight: number = 0
  @Local scaleX: number = 1
  @Local scaleY: number = 1
  @Local translateY: number = 0
  private isUp: boolean = false
  @Local textWidth: number = 0
  @Local textHeight: number = 0
  @Local textColor: Color | string = Color.White
  @Local isExceed: boolean = false
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private isReady: boolean = false
  private curves: ICurve = {} as ICurve
  private scaleValue: number = 1
  private path2D: Path2D = new Path2D()
  private circularCrossPointUtil: CircularCrossPointUtil = new CircularCrossPointUtil()
  private upperArcCircleR: number = 0
  private upperArcCircleY: number = 0

  @Monitor('options')
  optionsChange() {
    this.judgeTextWidth()
    this.btnColor = this.options.backgroundColor
    this.textColor = this.options.textColor
    this.changeStatus()
  }

  changeStatus() {
    switch (this.options.styleMode) {
      case ArcButtonStyleMode.EMPHASIZED:
        this.btnNormalColor = Constants.EMPHASIZED_NORMAL_BTN_COLOR
        this.textNormalColor = Constants.EMPHASIZED_TEXT_COLOR
        this.btnPressColor = Constants.EMPHASIZED_PRESSED_BTN_COLOR
        this.btnDisableColor = Constants.EMPHASIZED_DISABLE_BTN_COLOR
        this.textDisableColor = Constants.EMPHASIZED_DISABLE_TEXT_COLOR
        break

      case ArcButtonStyleMode.NORMAL_LIGHT:
        this.btnNormalColor = Constants.NORMAL01_NORMAL_BTN_COLOR
        this.textNormalColor = Constants.NORMAL01_TEXT_COLOR
        this.btnPressColor = Constants.NORMAL01_PRESSED_BTN_COLOR
        this.btnDisableColor = Constants.NORMAL01_DISABLE_BTN_COLOR
        this.textDisableColor = Constants.NORMAL01_DISABLE_TEXT_COLOR
        break

      case ArcButtonStyleMode.NORMAL_DEEP:
        this.btnNormalColor = Constants.NORMAL02_NORMAL_BTN_COLOR
        this.textNormalColor = Constants.NORMAL02_TEXT_COLOR
        this.btnPressColor = Constants.NORMAL02_PRESSED_BTN_COLOR
        this.btnDisableColor = Constants.NORMAL02_DISABLE_BTN_COLOR
        this.textDisableColor = Constants.NORMAL02_DISABLE_TEXT_COLOR
        break

      case ArcButtonStyleMode.EMPHASIZED_WARNING:
        this.btnNormalColor = Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR
        this.textNormalColor = Constants.EMPHASIZEWARN_TEXT_COLOR
        this.btnPressColor = Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR
        this.btnDisableColor = Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR
        this.textDisableColor = Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR
        break

      default:
        break
    }
    if (this.options.status === ArcButtonStatus.UNAVAILABLE) {
      this.btnColor = this.btnDisableColor
      this.textColor = this.textDisableColor
    } else {
      this.btnColor = this.btnNormalColor
      this.textColor = this.textNormalColor
    }
  }

  /**
   * 初始化数据
   */
  private initValues() {
    this.isUp = this.options.type == ArcButtonTypeMode.TOP_EDGE
    this.btnColor = this.options.backgroundColor
    this.textColor = this.options.textColor
    switch (this.options.touchEffect) {
      case ArkButtonClickEffectStyle.LIGHT:
        this.curves = Curves.interpolatingSpring(10, 1, 410, 38)
        this.scaleValue = 0.9
        break

      case ArkButtonClickEffectStyle.MIDDLE:
        this.curves = Curves.interpolatingSpring(10, 1, 350, 35)
        this.scaleValue = 0.95
        break

      case ArkButtonClickEffectStyle.HEAVY:
        this.curves = Curves.interpolatingSpring(0, 1, 240, 28)
        this.scaleValue = 0.95
        break

      default:
        break
    }
    this.changeStatus()
  }

  /**
   * 判断是否超出文本框宽度
   */
  private judgeTextWidth() {
    let measureTextWidth = measure.measureText({
      textContent: this.options.resourceText,
      fontSize: this.options.textSize.value
    })
    this.isExceed = measureTextWidth > vp2px(this.textWidth)
  }

  aboutToAppear() {
    this.initValues()
    this.upperArcCircleR = this.options.width
    this.upperArcCircleY = Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R + this.upperArcCircleR -
    this.options.height
    this.circularCrossPointUtil.initData(this.upperArcCircleR, this.upperArcCircleY)
    this.circularCrossPointUtil.calculate().then((data: AllPoints | null) => {
      if (data == null) {
        return
      }
      this.btnWidth = data.width + Constants.SHADOW_BLUR * 2
      if (this.isUp) {
        this.btnHeight = data.height + Constants.SHADOW_BLUR + Constants.SHADOW_OFFSET_Y
      } else {
        this.btnHeight = data.height + Constants.DISTANCE_FROM_BORDER * 2
      }
      this.textWidth = data.width - this.options.textMargin.left - this.options.textMargin.right
      this.judgeTextWidth()
      this.textHeight = data.height - this.options.textMargin.top - this.options.textMargin.bottom
      let leftTopPoint = data.leftTopPoint
      let rightTopPoint = data.rightTopPoint
      let leftBottomPoint = data.leftBottomPoint
      let rightBottomPoint = data.rightBottomPoint
      let canvasLeftTopPoint = data.canvasLeftTop
      canvasLeftTopPoint.x -= Constants.SHADOW_BLUR
      canvasLeftTopPoint.y -= Constants.DISTANCE_FROM_BORDER
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
          L ${vp2px(leftTopPoint.x - canvasLeftTopPoint.x)} ${vp2px(leftTopPoint.y - canvasLeftTopPoint.y)}`
      this.path2D = new Path2D(pathStr)
      this.doDraw()
    })
  }

  @Monitor('btnColor')
  doDraw() {
    if (!this.isReady || this.path2D === undefined) {
      return
    }
    let start = new Date().getTime()
    if (this.options.shadowEnabled) {
      this.context.shadowBlur = Constants.SHADOW_BLUR
      this.context.shadowOffsetY = -Constants.SHADOW_OFFSET_Y
      this.context.shadowColor = this.options.shadowColor
    }
    this.context.beginPath()
    this.context.fillStyle = this.btnColor
    this.context.fill(this.path2D)
  }

  private buildLog(): boolean {
    return true;
  }

  build() {
    Stack({ alignContent: Alignment.Top }) {
      if (this.buildLog()) {
      }
      Canvas(this.context)
        .onReady(() => {
          this.isReady = true
          this.doDraw()
        })
        .width(this.btnWidth)
        .height(this.btnHeight)
        .rotate({
          angle: this.isUp ? 0 : 180
        })

      if (this.isExceed) {
        Text(this.options.resourceText)
          .width(this.textWidth)
          .height(this.textHeight)
          .fontColor(this.textColor)
          .fontSize(this.options.textSize.value)
          .fontWeight(FontWeight.Medium)
          .fontStyle(this.options.textStyle)
          .fontFamily(this.options.textFamily)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.MARQUEE })
          .margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top })
      } else {
        Text(this.options.resourceText)
          .width(this.textWidth)
          .height(this.textHeight)
          .textAlign(TextAlign.Center)
          .fontColor(this.textColor)
          .maxFontSize(this.options.textSize.value)
          .minFontSize(new LengthMetrics(Constants.MIN_FONT_SIZE, LengthUnit.FP).value)
          .fontWeight(FontWeight.Medium)
          .fontStyle(this.options.textStyle)
          .fontFamily(this.options.textFamily)
          .maxLines(1)
          .margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top })
      }
    }
    .animation({ curve: this.curves })
    .width(this.btnWidth)
    .height(this.btnHeight)
    .enabled(this.options.status !== ArcButtonStatus.UNAVAILABLE)
    .opacity(this.options.status === ArcButtonStatus.UNAVAILABLE ? 0.4 : 1)
    .scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.btnHeight })
    .translate({ y: this.translateY })
    .onTouch((event: TouchEvent) => {
      let x = event.touches[0].windowX
      let y = event.touches[0].windowY
      switch (event.type) {
        case TouchType.Down:
          let isInPath = this.circularCrossPointUtil.isPointInPath(x, y, this.isUp)
          if (!isInPath) {
            return
          }
          this.scaleX = this.scaleValue
          this.scaleY = this.scaleValue
          this.btnColor = this.btnPressColor
          break

        case TouchType.Up:
          this.scaleX = 1
          this.scaleY = 1
          this.btnColor = this.btnNormalColor
          break

        default:
          break
      }
    })
    .onClick((event: ClickEvent) => {
    })
  }
}


class CircularCrossPointUtil {
  private mirrorUpperArcCircleY: number = 0
  private upperArcCircleY: number = 0
  private upperArcCircleR: number = 0

  initData(upperArcCircleR: number, upperArcCircleY: number) {
    this.upperArcCircleR = upperArcCircleR
    this.upperArcCircleY = upperArcCircleY
    let distance = this.calculateDistance(Constants.LOWER_ARC_CIRCLE_CENTER_X,
      Constants.LOWER_ARC_CIRCLE_CENTER_Y, Constants.UPPER_ARC_CIRCLE_CENTER_X, this.upperArcCircleY)
    this.mirrorUpperArcCircleY = distance - Constants.LOWER_ARC_CIRCLE_CENTER_Y
  }

  async calculate(): Promise<AllPoints | null> {

    let lowerArcCircleR = Constants.LOWER_ARC_CIRCLE_R
    let lowerArcCircleCenterX = Constants.LOWER_ARC_CIRCLE_CENTER_X
    let lowerArcCircleCenterY = Constants.LOWER_ARC_CIRCLE_CENTER_Y
    let upperArcCircleCenterX = Constants.UPPER_ARC_CIRCLE_CENTER_X

    let chamferCircleR = Constants.CHAMFER_CIRCLE_R
    let upperArcCircle = new Circle(this.upperArcCircleR, lowerArcCircleCenterX, lowerArcCircleCenterY) //大圆
    let lowerArcCircle = new Circle(lowerArcCircleR, upperArcCircleCenterX, this.upperArcCircleY) //小圆

    let external_intersections = this.findCircleIntersections(upperArcCircle, lowerArcCircle)
    if (external_intersections.length > 1) {
      let intersection1: Point = external_intersections[0]
      let intersection2: Point = external_intersections[1]

      let inside_intersections = this.findCircleIntersections(new Circle(this.upperArcCircleR - chamferCircleR,
        lowerArcCircleCenterX, lowerArcCircleCenterY), new Circle(lowerArcCircleR - chamferCircleR,
        upperArcCircleCenterX, this.upperArcCircleY))
      if (inside_intersections.length > 1) {
        intersection1 = inside_intersections[0]
        intersection2 = inside_intersections[1]

        if (intersection1.x > intersection2.x) {
          let mid = intersection1
          intersection1 = intersection2
          intersection2 = mid
        }

        let tp1 = this.calculateIntersection(new Point(lowerArcCircleCenterX, lowerArcCircleCenterY),
          this.upperArcCircleR, new Point(intersection1.x, intersection1.y))
        let tp2 = this.calculateIntersection(new Point(lowerArcCircleCenterX, lowerArcCircleCenterY),
          this.upperArcCircleR, new Point(intersection2.x, intersection2.y))
        let tp3 = this.calculateIntersection(new Point(upperArcCircleCenterX, this.upperArcCircleY),
          lowerArcCircleR, new Point(intersection2.x, intersection2.y))
        let tp4 = this.calculateIntersection(new Point(upperArcCircleCenterX, this.upperArcCircleY),
          lowerArcCircleR, new Point(intersection1.x, intersection1.y))

        let width = this.calculateDistance(intersection1.x, intersection1.y, intersection2.x, intersection2.y)
          + chamferCircleR * 2
        let height = (this.upperArcCircleR + lowerArcCircleR) - this.calculateDistance(lowerArcCircleCenterX,
          lowerArcCircleCenterY, upperArcCircleCenterX, this.upperArcCircleY)
        let canvasLeftTop = new Point(intersection1.x - chamferCircleR, this.upperArcCircleY - lowerArcCircleR)
        return new AllPoints(width, height, tp1, tp2, tp4, tp3, canvasLeftTop)
      }
    }
    return null
  }

  /**
   * 判断点是否在上弧圆内
   * @param x 触摸点X
   * @param y 触摸点Y
   * @returns 是否在上弧圆内
   */
  isPointInPath(x: number, y: number, isUp: boolean): boolean {
    let distance = this.calculateDistance(x, y, Constants.UPPER_ARC_CIRCLE_CENTER_X, isUp ? this.mirrorUpperArcCircleY
      : this.upperArcCircleY)
    return distance <= this.upperArcCircleR
  }

  /**
   * 计算两点间距离
   * @param point1 点1
   * @param point2 点2
   * @returns 距离
   */
  calculateDistance(x1: number, y1: number, x2: number, y2: number): number {
    return Math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
  }

  calculateIntersection(circleCenter: Point, circleRadius: number, point: Point): Point {

    let h = circleCenter.x
    let k = circleCenter.y
    let x = point.x
    let y = point.y

    let m: number = 0
    if (x != h) {
      m = (y - k) / (x - h)
    } else {
      m = -1
    }

    let b: number = 0
    if (m != -1) {
      b = y - m * x
    }

    let resultPoint: Point[] = []
    if (m != -1) {
      let A = Math.pow(m, 2) + 1
      let B = 2 * (m * b - m * k - h)
      let C = k**2 - circleRadius**2 + h**2 - 2 * b * k + b**2

      let x1 = (-B + (B**2 - 4 * A * C)**0.5) / (2 * A)
      let x2 = (-B - (B**2 - 4 * A * C)**0.5) / (2 * A)
      let y1: number = m * x1 + b
      let y2: number = m * x2 + b

      resultPoint = [new Point(x1, y1), new Point(x2, y2)]
    } else {
      let x1 = h
      let y1 = k + (circleRadius**2 - (x1 - h)**2)**0.5
      let y2 = k - (circleRadius**2 - (x1 - h)**2)**0.5
      resultPoint = [new Point(x1, y1), new Point(x1, y2)]
    }

    let d1 = this.calculateDistance(resultPoint[0].x, resultPoint[0].y, point.x, point.y)
    let d2 = this.calculateDistance(resultPoint[1].x, resultPoint[1].y, point.x, point.y)

    if (d1 < d2) {
      return resultPoint[0]
    } else {
      return resultPoint[1]
    }
  }

  /**
   * 查找两圆的交点
   * @param C1 第一个圆
   * @param c2 第二个圆
   * @returns 两圆相交的点的数组
   */
  findCircleIntersections(firstCircus: Circle, secondCircus: Circle): Point[] {
    let firstCircusR = firstCircus.radius
    let firstCircusCenterX = firstCircus.x
    let firstCircusCenterY = firstCircus.y

    let secondCircusR = secondCircus.radius
    let secondCircusCenterX = secondCircus.x
    let secondCircusCenterY = secondCircus.y

    // 计算两个圆心之间的距离
    let distance = Math.sqrt((firstCircusCenterX - secondCircusCenterX)**2 + (firstCircusCenterY -
      secondCircusCenterY)**2)

    // 检查异常情况
    if (distance > firstCircusR + secondCircusR) {
      //两个圆分离，不相交
      return []
    } else if (distance < Math.abs(firstCircusR - secondCircusR)) {
      //一个圆包含在另一个圆内，不相交
      return []
    } else if (distance === 0 && firstCircusR === secondCircusR) {
      //两个圆完全重合，具有无穷多交点
      return []
    }

    // 计算交点
    let a = (firstCircusR**2 - secondCircusR**2 + distance**2) / (2 * distance)
    let h = Math.sqrt(firstCircusR**2 - a**2)

    // 中间变量
    let x2 = firstCircusCenterX + a * (secondCircusCenterX - firstCircusCenterX) / distance
    let y2 = firstCircusCenterY + a * (secondCircusCenterY - firstCircusCenterY) / distance

    // 交点
    let intersection1 = new Point(x2 + h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 -
      h * (secondCircusCenterX - firstCircusCenterX) / distance)
    let intersection2 = new Point(x2 - h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 +
      h * (secondCircusCenterX - firstCircusCenterX) / distance)
    return [intersection1, intersection2]
  }
}

class Circle {
  radius: number
  x: number
  y: number

  constructor(radius: number, x: number, y: number) {
    this.radius = radius
    this.x = x
    this.y = y
  }
}

class Point {
  x: number
  y: number

  constructor(x: number, y: number) {
    this.x = x
    this.y = y
  }
}

class AllPoints {
  width: number
  height: number
  leftTopPoint: Point
  rightTopPoint: Point
  leftBottomPoint: Point
  rightBottomPoint: Point
  canvasLeftTop: Point

  constructor(width: number,
              height: number,
              leftTopPoint: Point,
              rightTopPoint: Point,
              leftBottomPoint: Point,
              rightBottomPoint: Point,
              canvasLeftTop: Point) {
    this.width = width
    this.height = height
    this.leftTopPoint = leftTopPoint
    this.rightTopPoint = rightTopPoint
    this.leftBottomPoint = leftBottomPoint
    this.rightBottomPoint = rightBottomPoint
    this.canvasLeftTop = canvasLeftTop
  }
}

class Constants {
  /**
   * 上弧圆圆心X坐标
   */
  public static readonly UPPER_ARC_CIRCLE_CENTER_X = 116.5;
  /**
   * 上弧圆圆心Y坐标
   */
  public static readonly UPPER_ARC_CIRCLE_CENTER_Y = 514;
  /**
   * 上弧圆半径
   */
  public static readonly UPPER_ARC_CIRCLE_R = 330;
  /**
   * 下弧圆圆心X坐标
   */
  public static readonly LOWER_ARC_CIRCLE_CENTER_X = 116.5;
  /**
   * 下弧圆圆心Y坐标
   */
  public static readonly LOWER_ARC_CIRCLE_CENTER_Y = 116.5;
  /**
   * 下弧圆半径
   */
  public static readonly LOWER_ARC_CIRCLE_R = 115.5;
  /**
   * 倒角圆半径
   */
  public static readonly CHAMFER_CIRCLE_R = 8;
  /**
   * 最大文字大小
   */
  public static readonly MAX_FONT_SIZE = 19
  /**
   * 最小文字大小
   */
  public static readonly MIN_FONT_SIZE = 13
  /**
   * 阴影半径
   */
  public static readonly SHADOW_BLUR = 4
  /**
   * Y偏移
   */
  public static readonly SHADOW_OFFSET_Y = 3
  /**
   * 按钮与边框距离
   */
  public static readonly DISTANCE_FROM_BORDER = 1
  /**
   * 文本间距
   */
  public static readonly TEXT_HORIZONTAL_MARGIN = 24
  public static readonly TEXT_MARGIN_TOP = 10
  public static readonly TEXT_MARGIN_BOTTOM = 16
  public static readonly EMPHASIZED_NORMAL_BTN_COLOR = '#1F71FF'
  public static readonly EMPHASIZED_TEXT_COLOR = '#FFFFFF'
  public static readonly EMPHASIZED_PRESSED_BTN_COLOR = '#2B6EC2'
  public static readonly EMPHASIZED_DISABLE_BTN_COLOR = '#991F71FF'
  public static readonly EMPHASIZED_DISABLE_TEXT_COLOR = '#99FFFFFF'
  public static readonly NORMAL01_NORMAL_BTN_COLOR = '#132230'
  public static readonly NORMAL01_TEXT_COLOR = '#5EA1FF'
  public static readonly NORMAL01_PRESSED_BTN_COLOR = '#25353E'
  public static readonly NORMAL01_DISABLE_BTN_COLOR = '#132230'
  public static readonly NORMAL01_DISABLE_TEXT_COLOR = '#995ea1ff'
  public static readonly NORMAL02_NORMAL_BTN_COLOR = '#1D201C'
  public static readonly NORMAL02_TEXT_COLOR = '#5EA1FF'
  public static readonly NORMAL02_PRESSED_BTN_COLOR = '#30342D'
  public static readonly NORMAL02_DISABLE_BTN_COLOR = '#1E211D'
  public static readonly NORMAL02_DISABLE_TEXT_COLOR = '#995ea1ff'
  public static readonly EMPHASIZEWARN_NORMAL_BTN_COLOR = '#BF2629'
  public static readonly EMPHASIZEWARN_TEXT_COLOR = '#FFFFFF'
  public static readonly EMPHASIZEWARN_PRESSED_BTN_COLOR = '#9E342F'
  public static readonly EMPHASIZEWARN_DISABLE_BTN_COLOR = '#3E0d0c'
  public static readonly EMPHASIZEWARN_DISABLE_TEXT_COLOR = '#99FFFFFF'
}