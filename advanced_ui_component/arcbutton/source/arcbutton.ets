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
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';

export enum ArcButtonTypeMode {
  TOP_EDGE = 0,
  BOTTOM_EDGE = 1
}

export enum ArcButtonStyleMode {
  EMPHASIZED_LIGHT = 0,
  EMPHASIZED_DEEP = 1,
  NORMAL_LIGHT = 2,
  NORMAL_DEEP = 3
}

export enum ArcButtonStatus {
  NORMAL = 0,
  PRESSED = 1,
  DISABLED = 2
}

export enum ArkButtonClickEffectStyle {
  NONE = 0,
  LIGHT = 1,
  MIDDLE = 2,
  HEAVY = 3
}

interface CommonArcButtonOptions {
  /**
   * 上下弧形按钮类型属性,默认为下弧形按钮
   */
  type?: ArcButtonTypeMode;

  /**
   *圆弧半径
   */
  width?: LengthMetrics;

  /**
   *弧形按钮上圆弧的最高点到下圆弧最低点的距离
   */
  height?: LengthMetrics;

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
  backgroundColor?: ColorMetrics;

  /**
   *按钮阴影色
   */
  shadowColor?: ColorMetrics;

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
  textColor?: ColorMetrics;

  /**
   *字体按压颜色
   */
  pressedTextColor?: ColorMetrics;

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
  textMargin?: LocalizedMargin;
}

@ObservedV2
export class ArcButtonOptions {
  @Trace public type: ArcButtonTypeMode;
  @Trace public width: LengthMetrics;
  @Trace public height: LengthMetrics;
  @Trace public styleMode: ArcButtonStyleMode;
  @Trace public status: ArcButtonStatus;
  @Trace public resourceText: ResourceStr;
  @Trace public touchEffect: ArkButtonClickEffectStyle;
  @Trace public backgroundColor: ColorMetrics;
  @Trace public shadowColor: ColorMetrics;
  @Trace public shadowEnabled: boolean;
  @Trace public textSize: LengthMetrics;
  @Trace public textColor: ColorMetrics;
  @Trace public pressedTextColor: ColorMetrics;
  @Trace public textStyle: FontStyle;
  @Trace public textFamily: string | Resource;
  @Trace public textMargin: LocalizedMargin;
  public touchCallback?: Callback<TouchEvent>
  public onClickEvent?: Callback<ClickEvent>

  constructor(options: CommonArcButtonOptions) {
    this.type = options.type ?? ArcButtonTypeMode.BOTTOM_EDGE
    this.width = options.width ?? new LengthMetrics(Constants.UPPER_ARC_CIRCLE_R, LengthUnit.VP)
    this.height = options.height ?? new LengthMetrics((Constants.LOWER_ARC_CIRCLE_CENTER_Y +
    Constants.LOWER_ARC_CIRCLE_R + Constants.UPPER_ARC_CIRCLE_R - Constants.UPPER_ARC_CIRCLE_CENTER_Y), LengthUnit.VP)
    this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT
    this.status = options.status ?? ArcButtonStatus.NORMAL
    this.resourceText = options.resourceText ?? ''
    this.touchEffect = options.touchEffect ?? ArkButtonClickEffectStyle.NONE
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.Black)
    this.shadowColor = options.shadowColor ?? ColorMetrics.resourceColor('#000000')
    this.shadowEnabled = options.shadowEnabled ?? false
    this.textSize = options.textSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE, LengthUnit.FP)
    this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White)
    this.pressedTextColor = options.pressedTextColor ?? ColorMetrics.resourceColor(Color.White)
    this.textStyle = options.textStyle ?? FontStyle.Normal
    this.textFamily = options.textFamily ?? ''
    this.textMargin = options.textMargin ?? {
      start: new LengthMetrics(Constants.TEXT_HORIZONTAL_MARGIN, LengthUnit.VP),
      top: new LengthMetrics(Constants.TEXT_MARGIN_TOP, LengthUnit.VP),
      end: new LengthMetrics(Constants.TEXT_HORIZONTAL_MARGIN, LengthUnit.VP),
      bottom: new LengthMetrics(Constants.TEXT_MARGIN_BOTTOM, LengthUnit.VP)
    }
  }
}

@ComponentV2
export struct ArcButton {
  @Require @Param options: ArcButtonOptions
  @Local private btnColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black)
  private btnNormalColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black)
  private btnPressColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black)
  private btnDisableColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black)
  private textNormalColor: ColorMetrics = ColorMetrics.resourceColor(Color.White)
  private textDisableColor: ColorMetrics = ColorMetrics.resourceColor(Color.White)
  @Local private btnWidth: number = 0
  @Local private btnHeight: number = 0
  @Local private scaleX: number = 1
  @Local private scaleY: number = 1
  @Local private translateY: number = 0
  private isUp: boolean = false
  @Local private textWidth: number = 0
  @Local private textHeight: number = 0
  @Local private textColor: ColorMetrics = ColorMetrics.resourceColor(Color.White)
  @Local private isExceed: boolean = false
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private isReady: boolean = false
  private curves: ICurve = {} as ICurve
  private scaleValue: number = 1
  private path2D: Path2D = new Path2D()
  private circularCrossPointUtil: CircularCrossPointUtil = new CircularCrossPointUtil()
  private upperArcCircleR: number = 0
  private upperArcCircleY: number = 0

  @Monitor('options.resourceText','options.textSize','options.styleMode','options.status',
  'options.backgroundColor','options.textColor')
  optionsChange() {
    this.judgeTextWidth()
    this.btnColor = this.options.backgroundColor
    this.textColor = this.options.textColor
    this.changeStatus()
  }

  changeStatus() {
    switch (this.options.styleMode) {
      case ArcButtonStyleMode.EMPHASIZED_LIGHT:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_TEXT_COLOR)
        break

      case ArcButtonStyleMode.NORMAL_LIGHT:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL01_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL01_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL01_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL01_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL01_DISABLE_TEXT_COLOR)
        break

      case ArcButtonStyleMode.NORMAL_DEEP:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL02_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL02_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL02_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL02_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL02_DISABLE_TEXT_COLOR)
        break

      case ArcButtonStyleMode.EMPHASIZED_DEEP:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR)
        break

      default:
        break
    }
    if (this.options.status === ArcButtonStatus.DISABLED) {
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
    this.upperArcCircleR = this.options.width.value
    this.upperArcCircleY = Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R + this.upperArcCircleR -
    this.options.height.value
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
      let margin = this.options.textMargin
      let start = margin?.start?.value ?? 0
      let end = margin?.end?.value ?? 0
      let top = margin?.top?.value ?? 0
      let bottom = margin?.bottom?.value ?? 0
      this.textWidth = data.width - start - end
      this.textHeight = data.height - top - bottom
      this.judgeTextWidth()
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
    if (this.options.shadowEnabled) {
      this.context.shadowBlur = Constants.SHADOW_BLUR
      this.context.shadowOffsetY = -Constants.SHADOW_OFFSET_Y
      this.context.shadowColor = this.options.shadowColor.color
    }
    this.context.beginPath()
    this.context.fillStyle = this.btnColor.color
    this.context.fill(this.path2D)
  }

  private buildLog(): boolean {
    return true;
  }

  @Builder
  textBuilderIsExceed() {
    Text(this.options.resourceText)
      .width(this.textWidth)
      .height(this.textHeight)
      .fontColor(this.textColor.color)
      .fontSize(this.options.textSize.value)
      .fontWeight(FontWeight.Medium)
      .fontStyle(this.options.textStyle)
      .fontFamily(this.options.textFamily)
      .maxLines(1)
      .textOverflow({ overflow: TextOverflow.MARQUEE })
      .margin({
        start: this.options.textMargin.start,
        top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top,
        end: this.options.textMargin.end,
        bottom: this.options.textMargin.bottom
      })
  }

  @Builder
  textBuilderNormal() {
    Text(this.options.resourceText)
      .width(this.textWidth)
      .height(this.textHeight)
      .textAlign(TextAlign.Center)
      .fontColor(this.textColor.color)
      .maxFontSize(this.options.textSize.value)
      .minFontSize(new LengthMetrics(Constants.MIN_FONT_SIZE, LengthUnit.FP).value)
      .fontWeight(FontWeight.Medium)
      .fontStyle(this.options.textStyle)
      .fontFamily(this.options.textFamily)
      .maxLines(1)
      .margin({
        start: this.options.textMargin.start,
        top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top,
        end: this.options.textMargin.end,
        bottom: this.options.textMargin.bottom
      })
  }

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      if (this.buildLog()) {
      }
      Canvas(this.context)
        .onReady(() => {
          this.isReady = true
          this.doDraw()
        })
        .width(this.btnWidth)
        .height(this.btnHeight)
        .rotate({ angle: this.isUp ? 0 : 180 })
      if (this.isExceed) {
        this.textBuilderIsExceed()
      } else {
        this.textBuilderNormal()
      }
    }
    .animation({ curve: this.curves })
    .width(this.btnWidth)
    .height(this.btnHeight)
    .enabled(this.options.status !== ArcButtonStatus.DISABLED)
    .opacity(this.options.status === ArcButtonStatus.DISABLED ? 0.4 : 1)
    .scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.btnHeight })
    .translate({ y: this.translateY })
    .onTouch((event: TouchEvent) => {
      if (this.options.touchCallback) {
        this.options.touchCallback(event)
      }
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
      if (this.options.onClickEvent) {
        this.options.onClickEvent(event)
      }
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
    let upperArcCircle = new ArcButtonCircle(this.upperArcCircleR, lowerArcCircleCenterX, lowerArcCircleCenterY) //大圆
    let lowerArcCircle = new ArcButtonCircle(lowerArcCircleR, upperArcCircleCenterX, this.upperArcCircleY) //小圆

    let externalIntersections = this.findCircleIntersections(upperArcCircle, lowerArcCircle)
    if (externalIntersections.length > 1) {
      let intersection1: ArcButtonPoint = externalIntersections[0]
      let intersection2: ArcButtonPoint = externalIntersections[1]

      let insideIntersections = this.findCircleIntersections(new ArcButtonCircle(this.upperArcCircleR - chamferCircleR,
        lowerArcCircleCenterX, lowerArcCircleCenterY), new ArcButtonCircle(lowerArcCircleR - chamferCircleR,
        upperArcCircleCenterX, this.upperArcCircleY))
      if (insideIntersections.length > 1) {
        intersection1 = insideIntersections[0]
        intersection2 = insideIntersections[1]

        if (intersection1.x > intersection2.x) {
          let mid = intersection1
          intersection1 = intersection2
          intersection2 = mid
        }

        let tp1 = this.calculateIntersection(new ArcButtonPoint(lowerArcCircleCenterX, lowerArcCircleCenterY),
          this.upperArcCircleR, new ArcButtonPoint(intersection1.x, intersection1.y))
        let tp2 = this.calculateIntersection(new ArcButtonPoint(lowerArcCircleCenterX, lowerArcCircleCenterY),
          this.upperArcCircleR, new ArcButtonPoint(intersection2.x, intersection2.y))
        let tp3 = this.calculateIntersection(new ArcButtonPoint(upperArcCircleCenterX, this.upperArcCircleY),
          lowerArcCircleR, new ArcButtonPoint(intersection2.x, intersection2.y))
        let tp4 = this.calculateIntersection(new ArcButtonPoint(upperArcCircleCenterX, this.upperArcCircleY),
          lowerArcCircleR, new ArcButtonPoint(intersection1.x, intersection1.y))

        let width = this.calculateDistance(intersection1.x, intersection1.y, intersection2.x, intersection2.y) +
          chamferCircleR * 2
        let height = (this.upperArcCircleR + lowerArcCircleR) - this.calculateDistance(lowerArcCircleCenterX,
          lowerArcCircleCenterY, upperArcCircleCenterX, this.upperArcCircleY)
        let canvasLeftTop = new ArcButtonPoint(intersection1.x - chamferCircleR, this.upperArcCircleY - lowerArcCircleR)
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
    let distance = this.calculateDistance(x, y, Constants.UPPER_ARC_CIRCLE_CENTER_X, isUp ?
    this.mirrorUpperArcCircleY : this.upperArcCircleY)
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

  calculateIntersection(circleCenter: ArcButtonPoint, circleRadius: number, point: ArcButtonPoint): ArcButtonPoint {

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

    let resultPoint: ArcButtonPoint[] = []
    if (m != -1) {
      let A = Math.pow(m, 2) + 1
      let B = 2 * (m * b - m * k - h)
      let C = k**2 - circleRadius**2 + h**2 - 2 * b * k + b**2

      let x1 = (-B + (B**2 - 4 * A * C)**0.5) / (2 * A)
      let x2 = (-B - (B**2 - 4 * A * C)**0.5) / (2 * A)
      let y1: number = m * x1 + b
      let y2: number = m * x2 + b

      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x2, y2)]
    } else {
      let x1 = h
      let y1 = k + (circleRadius**2 - (x1 - h)**2)**0.5
      let y2 = k - (circleRadius**2 - (x1 - h)**2)**0.5
      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x1, y2)]
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
  findCircleIntersections(firstCircus: ArcButtonCircle, secondCircus: ArcButtonCircle): ArcButtonPoint[] {
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
    let intersection1 = new ArcButtonPoint(x2 + h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 -
      h * (secondCircusCenterX - firstCircusCenterX) / distance)
    let intersection2 = new ArcButtonPoint(x2 - h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 +
      h * (secondCircusCenterX - firstCircusCenterX) / distance)
    return [intersection1, intersection2]
  }
}

class ArcButtonCircle {
  public radius: number
  public x: number
  public y: number

  constructor(radius: number, x: number, y: number) {
    this.radius = radius
    this.x = x
    this.y = y
  }
}

class ArcButtonPoint {
  public x: number
  public y: number

  constructor(x: number, y: number) {
    this.x = x
    this.y = y
  }
}

class AllPoints {
  public width: number
  public height: number
  public leftTopPoint: ArcButtonPoint
  public rightTopPoint: ArcButtonPoint
  public leftBottomPoint: ArcButtonPoint
  public rightBottomPoint: ArcButtonPoint
  public canvasLeftTop: ArcButtonPoint

  constructor(width: number,
              height: number,
              leftTopPoint: ArcButtonPoint,
              rightTopPoint: ArcButtonPoint,
              leftBottomPoint: ArcButtonPoint,
              rightBottomPoint: ArcButtonPoint,
              canvasLeftTop: ArcButtonPoint) {
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