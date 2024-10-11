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

export enum ArcButtonPosition {
  TOP_EDGE = 0,
  BOTTOM_EDGE = 1
}

export enum ArcButtonStyleMode {
  EMPHASIZED_LIGHT = 0,
  EMPHASIZED_DEEP = 1,
  NORMAL_LIGHT = 2,
  NORMAL_DEEP = 3,
  CUSTOM = 4
}

export enum ArcButtonStatus {
  NORMAL = 0,
  PRESSED = 1,
  DISABLED = 2
}

interface CommonArcButtonOptions {
  /**
   * 弧形按钮位置类型属性,默认为下弧形按钮
   */
  position?: ArcButtonPosition

  /**
   *强调、普通01、普通02、警告、自定义  默认是强调状态
   */
  styleMode?: ArcButtonStyleMode

  /**
   *初始态、按压、不可用形态,默认为初始态
   */
  status?: ArcButtonStatus

  /**
   *文字
   */
  label?: ResourceStr

  /**
   *背景模糊能力
   */
  backgroundBlurStyle?: BlurStyle

  /**
   *按钮背景色
   */
  backgroundColor?: ColorMetrics

  /**
   *按钮阴影色
   */
  shadowColor?: ColorMetrics

  /**
   *打开关闭弧形按钮阴影
   */
  shadowEnabled?: boolean

  /**
   *字体大小
   */
  fontSize?: LengthMetrics

  /**
   *字体颜色
   */
  fontColor?: ColorMetrics

  /**
   *字体按压颜色
   */
  pressedTextColor?: ColorMetrics

  /**
   *文字样式
   */
  fontStyle?: FontStyle

  /**
   *文字字体族
   */
  fontFamily?: string | Resource

  /**
   *文字到边框的距离
   */
  fontMargin?: LocalizedMargin

  /**
   * TouchEvent
   */
  onTouch?: Callback<TouchEvent>

  /**
   * ClickEvent
   */
  onClick?: Callback<ClickEvent>
}


class Constants {
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
  public static readonly NORMAL01_NORMAL_BTN_COLOR = '#182840'
  public static readonly NORMAL01_TEXT_COLOR = '#5EA1FF'
  public static readonly NORMAL01_PRESSED_BTN_COLOR = '#2F3D53'
  public static readonly NORMAL01_DISABLE_BTN_COLOR = '#132230'
  public static readonly NORMAL01_DISABLE_TEXT_COLOR = '#995ea1ff'
  public static readonly NORMAL02_NORMAL_BTN_COLOR = '#1D201C'
  public static readonly NORMAL02_TEXT_COLOR = '#5EA1FF'
  public static readonly NORMAL02_PRESSED_BTN_COLOR = '#3C3C3C'
  public static readonly NORMAL02_DISABLE_BTN_COLOR = '#1E211D'
  public static readonly NORMAL02_DISABLE_TEXT_COLOR = '#995ea1ff'
  public static readonly EMPHASIZEWARN_NORMAL_BTN_COLOR = '#BF2629'
  public static readonly EMPHASIZEWARN_TEXT_COLOR = '#FFFFFF'
  public static readonly EMPHASIZEWARN_PRESSED_BTN_COLOR = '#9E342F'
  public static readonly EMPHASIZEWARN_DISABLE_BTN_COLOR = '#3E0d0c'
  public static readonly EMPHASIZEWARN_DISABLE_TEXT_COLOR = '#99FFFFFF'
}

interface ArcButtonThemeInterface {
  /**
   * 弧形按钮高度
   */
  BUTTON_HEIGHT: number,
  /**
   * 辅助圆半径
   */
  ARC_CIRCLE_DIAMETER: number,

  /**
   * 表盘直径
   */
  DIAL_CIRCLE_DIAMETER: number,

  /**
   * 弧形按钮倒角圆半径
   */
  CHAMFER_CIRCLE_RADIUS: number,
}

const arcButtonTheme: ArcButtonThemeInterface = {
  BUTTON_HEIGHT: LengthMetrics.resource($r('sys.float.arc_button_height')).value,
  ARC_CIRCLE_DIAMETER: LengthMetrics.resource($r('sys.float.arc_button_auxiliary_circle_diameter')).value,
  DIAL_CIRCLE_DIAMETER: LengthMetrics.resource($r('sys.float.arc_button_dial_circle_diameter')).value,
  CHAMFER_CIRCLE_RADIUS: LengthMetrics.resource($r('sys.float.arc_button_chamfer_radius')).value
}

@ObservedV2
export class ArcButtonOptions {
  @Trace public position: ArcButtonPosition
  @Trace public styleMode: ArcButtonStyleMode
  @Trace public status: ArcButtonStatus
  @Trace public label: ResourceStr
  @Trace public backgroundBlurStyle: BlurStyle
  @Trace public backgroundColor: ColorMetrics
  @Trace public shadowColor: ColorMetrics
  @Trace public shadowEnabled: boolean
  @Trace public fontSize: LengthMetrics
  @Trace public fontColor: ColorMetrics
  @Trace public pressedTextColor: ColorMetrics
  @Trace public fontStyle: FontStyle
  @Trace public fontFamily: string | Resource
  @Trace public fontMargin: LocalizedMargin
  @Trace public onTouch?: Callback<TouchEvent>
  @Trace public onClick?: Callback<ClickEvent>

  constructor(options: CommonArcButtonOptions) {
    this.position = options.position ?? ArcButtonPosition.BOTTOM_EDGE
    this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT
    this.status = options.status ?? ArcButtonStatus.NORMAL
    this.label = options.label ?? ''
    this.backgroundBlurStyle = options.backgroundBlurStyle ?? BlurStyle.NONE
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.Black)
    this.shadowColor = options.shadowColor ?? ColorMetrics.resourceColor('#000000')
    this.shadowEnabled = options.shadowEnabled ?? false
    this.fontSize = options.fontSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE)
    this.fontColor = options.fontColor ?? ColorMetrics.resourceColor(Color.White)
    this.pressedTextColor = options.pressedTextColor ?? ColorMetrics.resourceColor(Color.White)
    this.fontStyle = options.fontStyle ?? FontStyle.Normal
    this.fontFamily = options.fontFamily ?? ''
    this.fontMargin = options.fontMargin ?? {
      start: new LengthMetrics(Constants.TEXT_HORIZONTAL_MARGIN, LengthUnit.VP),
      top: new LengthMetrics(Constants.TEXT_MARGIN_TOP, LengthUnit.VP),
      end: new LengthMetrics(Constants.TEXT_HORIZONTAL_MARGIN, LengthUnit.VP),
      bottom: new LengthMetrics(Constants.TEXT_MARGIN_BOTTOM, LengthUnit.VP)
    }
    this.onTouch = options.onTouch ?? (() => {
    })
    this.onClick = options.onClick ?? (() => {
    })
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
  @Local private canvasWidth: number = 0
  @Local private canvasHeight: number = 0
  @Local private scaleX: number = 1
  @Local private scaleY: number = 1
  private isUp: boolean = false
  @Local private textWidth: number = 0
  @Local private textHeight: number = 0
  @Local private fontColor: ColorMetrics = ColorMetrics.resourceColor(Color.White)
  @Local private isExceed: boolean = false
  private curves: ICurve = {} as ICurve
  private scaleValue: number = 1
  private dataProcessUtil: DataProcessUtil = new DataProcessUtil()
  private textPressColor: ColorMetrics = ColorMetrics.resourceColor(Color.White)
  @Local private pathString: string = ''

  @Monitor('options.label', 'options.type', 'options.fontSize', 'options.styleMode', 'options.status',
  'options.backgroundColor', 'options.fontColor')
  optionsChange() {
    this.judgeTextWidth()
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
        this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR)
        break

      case ArcButtonStyleMode.NORMAL_LIGHT:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL01_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL01_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL01_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL01_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL01_DISABLE_TEXT_COLOR)
        this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL01_TEXT_COLOR)
        break

      case ArcButtonStyleMode.NORMAL_DEEP:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL02_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL02_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL02_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL02_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL02_DISABLE_TEXT_COLOR)
        this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL02_TEXT_COLOR)
        break

      case ArcButtonStyleMode.EMPHASIZED_DEEP:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR)
        this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR)
        this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR)
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR)
        this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR)
        this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR)
        break

      default:
        this.btnNormalColor = this.options.backgroundColor
        this.textNormalColor = this.options.fontColor
        this.btnPressColor = this.options.backgroundColor
        this.textPressColor = this.options.pressedTextColor
        break
    }
    if (this.options.status === ArcButtonStatus.DISABLED) {
      this.btnColor = this.btnDisableColor
      this.fontColor = this.textDisableColor
    } else {
      this.btnColor = this.btnNormalColor
      this.fontColor = this.textNormalColor
    }
  }

  /**
   * 初始化数据
   */
  private initValues() {
    this.isUp = this.options.position == ArcButtonPosition.TOP_EDGE
    this.btnColor = this.options.backgroundColor
    this.fontColor = this.options.fontColor
    this.curves = Curves.interpolatingSpring(10, 1, 350, 35)
    this.scaleValue = 0.95
    this.changeStatus()
  }

  /**
   * 判断是否超出文本框宽度
   */
  private judgeTextWidth() {
    const measureTextWidth = measure.measureText({
      textContent: this.options.label,
      fontSize: this.options.fontSize.value
    })
    this.isExceed = measureTextWidth > vp2px(this.textWidth)
  }

  aboutToAppear() {
    this.initValues()
    this.dataProcessUtil.initData()
    const pathData = this.dataProcessUtil.calculate()
    this.generatePath(pathData)
  }

  private generatePath(data: AllPoints | null) {
    if (data == null) {
      return
    }
    this.canvasWidth = data.btnWidth + Constants.SHADOW_BLUR * 2
    this.canvasHeight = data.btnHeight + Constants.DISTANCE_FROM_BORDER * 2

    const margin = this.options.fontMargin
    const start = margin?.start?.value ?? 0
    const end = margin?.end?.value ?? 0
    const top = margin?.top?.value ?? 0
    const bottom = margin?.bottom?.value ?? 0
    this.textWidth = data.btnWidth - start - end
    this.textHeight = data.btnHeight - top - bottom
    this.judgeTextWidth()
    const leftTopPoint = data.leftTopPoint
    const rightTopPoint = data.rightTopPoint
    const leftBottomPoint = data.leftBottomPoint
    const rightBottomPoint = data.rightBottomPoint
    const canvasLeftTopPoint = data.canvasLeftTop
    canvasLeftTopPoint.x -= Constants.SHADOW_BLUR
    canvasLeftTopPoint.y -= Constants.DISTANCE_FROM_BORDER

    const mLeftTopPointX: number = this.buttonVp2px(leftTopPoint.x, canvasLeftTopPoint.x)
    const mLeftTopPointY: number = this.buttonVp2px(leftTopPoint.y, canvasLeftTopPoint.y)
    const upperArcCircleR: number = this.getUIContext().vp2px(arcButtonTheme.ARC_CIRCLE_DIAMETER / 2)
    const rightTopPointX: number = this.buttonVp2px(rightTopPoint.x, canvasLeftTopPoint.x)
    const rightTopPointY: number = this.buttonVp2px(rightTopPoint.y, canvasLeftTopPoint.y)
    const chamferCircleR: number = this.getUIContext().vp2px(arcButtonTheme.CHAMFER_CIRCLE_RADIUS)
    const rightBottomPointX: number = this.buttonVp2px(rightBottomPoint.x, canvasLeftTopPoint.x)
    const rightBottomPointY: number = this.buttonVp2px(rightBottomPoint.y, canvasLeftTopPoint.y)
    const lowerArcCircleR: number = this.getUIContext().vp2px(arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2)
    const leftBottomPointX: number = this.buttonVp2px(leftBottomPoint.x, canvasLeftTopPoint.x)
    const leftBottomPointY: number = this.buttonVp2px(leftBottomPoint.y, canvasLeftTopPoint.y)

    const pathStr = `M ${mLeftTopPointX} ${mLeftTopPointY} A ${upperArcCircleR} ${upperArcCircleR}, 0, 0, 0,
       ${rightTopPointX} ${rightTopPointY}` +
      `M ${rightTopPointX} ${rightTopPointY} A ${chamferCircleR} ${chamferCircleR}, 0, 0, 0, ${rightBottomPointX}
       ${rightBottomPointY}` +
      `M ${rightBottomPointX} ${rightBottomPointY} A ${lowerArcCircleR} ${lowerArcCircleR}, 0, 0, 0, ${leftBottomPointX}
       ${leftBottomPointY}` +
      `M ${leftBottomPointX} ${leftBottomPointY} A ${chamferCircleR} ${chamferCircleR}, 0, 0, 0, ${mLeftTopPointX}
       ${mLeftTopPointY}` +
      `M ${mLeftTopPointX} ${mLeftTopPointY} L ${rightTopPointX} ${rightTopPointY} L ${rightBottomPointX}
       ${rightBottomPointY} L ${leftBottomPointX} ${leftBottomPointY} L ${mLeftTopPointX} ${mLeftTopPointY}`
    this.pathString = pathStr
  }

  buttonVp2px(valueX: number, valueY: number) {
    const num = valueX - valueY
    return this.getUIContext().vp2px(num)
  }

  private buildLog(): boolean {
    return true
  }

  @Builder
  textBuilderIsExceed() {
    Text(this.options.label)
      .width(this.textWidth)
      .height(this.textHeight)
      .fontColor(this.fontColor.color)
      .fontSize(this.options.fontSize.value)
      .fontWeight(FontWeight.Medium)
      .fontStyle(this.options.fontStyle)
      .fontFamily(this.options.fontFamily)
      .backgroundColor(Color.Transparent)
      .maxLines(1)
      .textOverflow({ overflow: TextOverflow.MARQUEE })
      .margin({
        start: this.options.fontMargin.start,
        top: this.isUp ? this.options.fontMargin.bottom : this.options.fontMargin.top,
        end: this.options.fontMargin.end,
        bottom: this.options.fontMargin.bottom
      })
  }

  @Builder
  textBuilderNormal() {
    Text(this.options.label)
      .width(this.textWidth)
      .height(this.textHeight)
      .textAlign(TextAlign.Center)
      .fontColor(this.fontColor.color)
      .backgroundColor(Color.Transparent)
      .maxFontSize(this.options.fontSize.value)
      .minFontSize(new LengthMetrics(Constants.MIN_FONT_SIZE).value)
      .fontWeight(FontWeight.Medium)
      .fontStyle(this.options.fontStyle)
      .fontFamily(this.options.fontFamily)
      .maxLines(1)
      .margin({
        start: this.options.fontMargin.start,
        top: this.isUp ? this.options.fontMargin.bottom : this.options.fontMargin.top,
        end: this.options.fontMargin.end,
        bottom: this.options.fontMargin.bottom
      })
  }

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Button({ type: ButtonType.Normal, stateEffect: true })
        .width('100%')
        .height('100%')
        .rotate({ angle: !this.isUp ? 0 : 180 })
        .opacity(this.options.status === ArcButtonStatus.DISABLED ? 0.4 : 1)
        .clipShape(new Path({ commands: this.pathString }))
        .backgroundColor(this.btnColor.color)
        .backgroundBlurStyle(this.options.backgroundBlurStyle)
        .shadow({
          radius: this.options.shadowEnabled ? Constants.SHADOW_BLUR : 0,
          color: this.options.shadowColor.color,
          offsetY: this.options.shadowEnabled ? Constants.SHADOW_OFFSET_Y : 0
        })

      if (this.isExceed) {
        this.textBuilderIsExceed()
      } else {
        this.textBuilderNormal()
      }
    }
    .width(this.canvasWidth)
    .height(this.canvasHeight)
    .enabled(this.options.status !== ArcButtonStatus.DISABLED)
    .animation({ curve: this.curves })
    .scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.canvasHeight })
    .onTouch((event: TouchEvent) => {
      this.dealTouchEvent(event)
    })
    .onClick((event: ClickEvent) => {
      if (this.options.onClick) {
        this.options.onClick(event)
      }
    })
  }

  private dealTouchEvent(event: TouchEvent) {
    const x = event.touches[0].windowX
    const y = event.touches[0].windowY
    const isInPath = this.dataProcessUtil.isPointInPath(x, y)
    if (!isInPath) {
      return
    }
    if (this.options.onTouch) {
      this.options.onTouch(event)
    }
    switch (event.type) {
      case TouchType.Down:
        this.scaleX = this.scaleValue
        this.scaleY = this.scaleValue
        this.btnColor = this.btnPressColor
        this.fontColor = this.textPressColor
        break
      case TouchType.Up:
        this.scaleX = 1
        this.scaleY = 1
        this.btnColor = this.btnNormalColor
        this.fontColor = this.textNormalColor
        break
      default:
        break
    }
  }
}

class DataProcessUtil {
  private dial: ArcButtonCircle = new ArcButtonCircle(0, 0, 0)
  private arc: ArcButtonCircle = new ArcButtonCircle(0, 0, 0)
  private height: number = 0
  private width: number = 0

  initData() {
    const dialRadius = arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2
    this.dial = new ArcButtonCircle(dialRadius, dialRadius, dialRadius)

    const arcRadius = arcButtonTheme.ARC_CIRCLE_DIAMETER / 2
    this.height = arcButtonTheme.BUTTON_HEIGHT
    const arcX = this.dial.center.x
    const arcY = this.dial.center.y + dialRadius + arcRadius - this.height
    this.arc = new ArcButtonCircle(arcRadius, arcX, arcY)
  }

  calculate(): AllPoints {
    const chamferCircleR = arcButtonTheme.CHAMFER_CIRCLE_RADIUS
    const innerDial = new ArcButtonCircle(this.dial.radius - chamferCircleR, this.dial.center.x, this.dial.center.y)
    const innerArc = new ArcButtonCircle(this.arc.radius - chamferCircleR, this.arc.center.x, this.arc.center.y)
    const intersections = this.findCircleIntersections(innerArc, innerDial)
    const tp1 = this.calculateIntersection(this.arc.center, this.arc.radius, intersections[0])
    const tp2 = this.calculateIntersection(this.arc.center, this.arc.radius, intersections[1])
    const tp3 = this.calculateIntersection(this.dial.center, this.dial.radius, intersections[1])
    const tp4 = this.calculateIntersection(this.dial.center, this.dial.radius, intersections[0])

    this.width = this.calculateDistance(intersections[0], intersections[1]) + chamferCircleR * 2
    const canvasLeftTop = new ArcButtonPoint(intersections[0].x - chamferCircleR, this.dial.center.y +
    this.dial.radius - this.height)

    return new AllPoints(this.width, this.height, tp2, tp1, tp3, tp4, canvasLeftTop)
  }

  /**
   * 判断点是否在上弧圆内
   * @param x 触摸点X
   * @param y 触摸点Y
   * @returns 是否在上弧圆内
   */
  isPointInPath(x: number, y: number): boolean {
    const pointTouch = new ArcButtonPoint(x, y)
    const distance = this.calculateDistance(pointTouch, this.arc.center)
    return distance <= this.arc.radius
  }

  /**
   * 计算两点间距离
   * @param point1 点1
   * @param point2 点2
   * @returns 距离
   */
  calculateDistance(point1: ArcButtonPoint, point2: ArcButtonPoint): number {
    return Math.sqrt((point2.x - point1.x) ** 2 + (point2.y - point1.y) ** 2)
  }

  calculateIntersection(circleCenter: ArcButtonPoint, circleRadius: number, point: ArcButtonPoint): ArcButtonPoint {
    const h = circleCenter.x
    const k = circleCenter.y
    const x = point.x
    const y = point.y

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
      const A = Math.pow(m, 2) + 1
      const B = 2 * (m * b - m * k - h)
      const C = k ** 2 - circleRadius ** 2 + h ** 2 - 2 * b * k + b ** 2

      const x1 = (-B + (B ** 2 - 4 * A * C) ** 0.5) / (2 * A)
      const x2 = (-B - (B ** 2 - 4 * A * C) ** 0.5) / (2 * A)
      const y1: number = m * x1 + b
      const y2: number = m * x2 + b

      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x2, y2)]
    } else {
      const x1 = h
      const y1 = k + (circleRadius ** 2 - (x1 - h) ** 2) ** 0.5
      const y2 = k - (circleRadius ** 2 - (x1 - h) ** 2) ** 0.5
      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x1, y2)]
    }

    const d1 = this.calculateDistance(resultPoint[0], point)
    const d2 = this.calculateDistance(resultPoint[1], point)
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
    const firstCircusR = firstCircus.radius
    const firstCircusCenterX = firstCircus.center.x
    const firstCircusCenterY = firstCircus.center.y

    const secondCircusR = secondCircus.radius
    const secondCircusCenterX = secondCircus.center.x
    const secondCircusCenterY = secondCircus.center.y

    // 计算两个圆心之间的距离
    const distance = Math.sqrt((firstCircusCenterX - secondCircusCenterX) ** 2 + (firstCircusCenterY -
      secondCircusCenterY) ** 2)

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
    const a = (firstCircusR ** 2 - secondCircusR ** 2 + distance ** 2) / (2 * distance)
    const h = Math.sqrt(firstCircusR ** 2 - a ** 2)

    // 中间变量
    const x2 = firstCircusCenterX + a * (secondCircusCenterX - firstCircusCenterX) / distance
    const y2 = firstCircusCenterY + a * (secondCircusCenterY - firstCircusCenterY) / distance

    // 交点
    let intersection1 = new ArcButtonPoint(x2 + h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 -
      h * (secondCircusCenterX - firstCircusCenterX) / distance)
    let intersection2 = new ArcButtonPoint(x2 - h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 +
      h * (secondCircusCenterX - firstCircusCenterX) / distance)

    if (intersection1.x > intersection2.x) {
      const mid = intersection1
      intersection1 = intersection2
      intersection2 = mid
    }

    return [intersection1, intersection2]
  }
}

class ArcButtonCircle {
  public radius: number
  public center: ArcButtonPoint

  constructor(radius: number, x: number, y: number) {
    this.radius = radius
    this.center = new ArcButtonPoint(x, y)
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
  public btnWidth: number
  public btnHeight: number
  public leftTopPoint: ArcButtonPoint
  public rightTopPoint: ArcButtonPoint
  public leftBottomPoint: ArcButtonPoint
  public rightBottomPoint: ArcButtonPoint
  public canvasLeftTop: ArcButtonPoint

  constructor(btnWidth: number,
              btnHeight: number,
              leftTopPoint: ArcButtonPoint,
              rightTopPoint: ArcButtonPoint,
              leftBottomPoint: ArcButtonPoint,
              rightBottomPoint: ArcButtonPoint,
              canvasLeftTop: ArcButtonPoint) {
    this.btnWidth = btnWidth
    this.btnHeight = btnHeight
    this.leftTopPoint = leftTopPoint
    this.rightTopPoint = rightTopPoint
    this.leftBottomPoint = leftBottomPoint
    this.rightBottomPoint = rightBottomPoint
    this.canvasLeftTop = canvasLeftTop
  }
}
