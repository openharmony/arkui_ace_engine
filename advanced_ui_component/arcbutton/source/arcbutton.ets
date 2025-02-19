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

import measure from '@ohos.measure';
import Curves from '@ohos.curves';
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';

export enum ArcButtonPosition {
  TOP_EDGE = 0,
  BOTTOM_EDGE = 1
}

export enum ArcButtonStyleMode {
  EMPHASIZED_LIGHT = 0,
  EMPHASIZED_DARK = 1,
  NORMAL_LIGHT = 2,
  NORMAL_DARK = 3,
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
  pressedFontColor?: ColorMetrics
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
  public static readonly MAX_FONT_SIZE = 19;
  /**
   * 最小文字大小
   */
  public static readonly MIN_FONT_SIZE = 13;
  /**
   * 阴影半径
   */
  public static readonly SHADOW_BLUR = 4;
  /**
   * Y偏移
   */
  public static readonly SHADOW_OFFSET_Y = 3;
  /**
   * 按钮与边框距离
   */
  public static readonly DISTANCE_FROM_BORDER = 1;
  /**
   * 文本间距
   */
  public static readonly TEXT_HORIZONTAL_MARGIN = 24;
  public static readonly TEXT_MARGIN_TOP = 10;
  public static readonly TEXT_MARGIN_BOTTOM = 16;
  public static readonly EMPHASIZED_NORMAL_BTN_COLOR = $r('sys.color.comp_background_emphasize');
  public static readonly EMPHASIZED_TEXT_COLOR = '#FFFFFF';
  public static readonly EMPHASIZED_PRESSED_BTN_COLOR = '#357FFF';
  public static readonly EMPHASIZED_DISABLE_BTN_COLOR = '#1F71FF';
  public static readonly EMPHASIZED_DISABLE_TEXT_COLOR = '#FFFFFF';
  public static readonly NORMAL_LIGHT_NORMAL_BTN_COLOR = '#17273F';
  public static readonly NORMAL_LIGHT_TEXT_COLOR = '#5EA1FF';
  public static readonly NORMAL_LIGHT_PRESSED_BTN_COLOR = '#2E3D52';
  public static readonly NORMAL_LIGHT_DISABLE_BTN_COLOR = '#17273F';
  public static readonly NORMAL_LIGHT_DISABLE_TEXT_COLOR = '#995ea1ff';
  public static readonly NORMAL_DARK_NORMAL_BTN_COLOR = '#252525';
  public static readonly NORMAL_DARK_TEXT_COLOR = '#5EA1FF';
  public static readonly NORMAL_DARK_PRESSED_BTN_COLOR = '#3B3B3B';
  public static readonly NORMAL_DARK_DISABLE_BTN_COLOR = '#262626';
  public static readonly NORMAL_DARK_DISABLE_TEXT_COLOR = '#995ea1ff';
  public static readonly EMPHASIZEWARN_NORMAL_BTN_COLOR = '#BF2629';
  public static readonly EMPHASIZEWARN_TEXT_COLOR = '#FFFFFF';
  public static readonly EMPHASIZEWARN_PRESSED_BTN_COLOR = '#C53C3E';
  public static readonly EMPHASIZEWARN_DISABLE_BTN_COLOR = '#4C0f10';
  public static readonly EMPHASIZEWARN_DISABLE_TEXT_COLOR = '#99FFFFFF';
  public static readonly DEFAULT_TRANSPARENCY = 0.4;
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

@ObservedV2
export class ArcButtonOptions {
  @Trace public position: ArcButtonPosition;
  @Trace public styleMode: ArcButtonStyleMode;
  @Trace public status: ArcButtonStatus;
  @Trace public label: ResourceStr;
  @Trace public backgroundBlurStyle: BlurStyle;
  @Trace public backgroundColor: ColorMetrics;
  @Trace public shadowColor: ColorMetrics;
  @Trace public shadowEnabled: boolean;
  @Trace public fontSize: LengthMetrics;
  @Trace public fontColor: ColorMetrics;
  @Trace public pressedFontColor: ColorMetrics;
  @Trace public fontStyle: FontStyle;
  @Trace public fontFamily: string | Resource;
  @Trace public fontMargin: LocalizedMargin;
  @Trace public onTouch?: Callback<TouchEvent>;
  @Trace public onClick?: Callback<ClickEvent>;

  constructor(options: CommonArcButtonOptions) {
    this.position = options.position ?? ArcButtonPosition.BOTTOM_EDGE;
    this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT;
    this.status = options.status ?? ArcButtonStatus.NORMAL;
    this.label = options.label ?? '';
    this.backgroundBlurStyle = options.backgroundBlurStyle ?? BlurStyle.NONE;
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.Black);
    this.shadowColor = options.shadowColor ?? ColorMetrics.resourceColor('#000000');
    this.shadowEnabled = options.shadowEnabled ?? false;
    this.fontSize = options.fontSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE);
    this.fontColor = options.fontColor ?? ColorMetrics.resourceColor(Color.White);
    this.pressedFontColor = options.pressedFontColor ?? ColorMetrics.resourceColor(Color.White);
    this.fontStyle = options.fontStyle ?? FontStyle.Normal;
    this.fontFamily = options.fontFamily ?? '';
    this.fontMargin = options.fontMargin ?? {
      start: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
      top: LengthMetrics.vp(Constants.TEXT_MARGIN_TOP),
      end: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
      bottom: LengthMetrics.vp(Constants.TEXT_MARGIN_BOTTOM)
    }
    this.onTouch = options.onTouch ?? (() => {
    })
    this.onClick = options.onClick ?? (() => {
    })
  }
}

@ComponentV2
export struct ArcButton {
  @Require @Param options: ArcButtonOptions;
  @Local private canvasWidth: number = 0;
  @Local private canvasHeight: number = 0;
  @Local private scaleX: number = 1;
  @Local private scaleY: number = 1;
  @Local private btnColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black);
  @Local private textWidth: number = 0;
  @Local private textHeight: number = 0;
  @Local private fontColor: ColorMetrics = ColorMetrics.resourceColor(Color.White);
  @Local private isExceed: boolean = false;
  @Local private pathString: string = '';
  @Local private fontSize: string = ''
  private btnNormalColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black);
  private btnPressColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black);
  private btnDisableColor: ColorMetrics = ColorMetrics.resourceColor(Color.Black);
  private textNormalColor: ColorMetrics = ColorMetrics.resourceColor(Color.White);
  private textDisableColor: ColorMetrics = ColorMetrics.resourceColor(Color.White);
  private isUp: boolean = false;
  private curves: ICurve = Curves.interpolatingSpring(10, 1, 350, 35);
  private scaleValue: number = 1;
  private textPressColor: ColorMetrics = ColorMetrics.resourceColor(Color.White);
  private arcButtonTheme: ArcButtonThemeInterface = {
    BUTTON_HEIGHT: this.getArcButtonThemeVpValue($r('sys.float.arc_button_height')),
    ARC_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue($r('sys.float.arc_button_auxiliary_circle_diameter')),
    DIAL_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue($r('sys.float.arc_button_dial_circle_diameter')),
    CHAMFER_CIRCLE_RADIUS: this.getArcButtonThemeVpValue($r('sys.float.arc_button_chamfer_radius'))
  }
  private dataProcessUtil: DataProcessUtil = new DataProcessUtil(this.arcButtonTheme);

  @Monitor('options.label', 'options.type', 'options.fontSize', 'options.styleMode', 'options.status',
  'options.backgroundColor', 'options.fontColor')
  optionsChange() {
    this.fontSize = this.cover(this.options.fontSize)
    this.judgeTextWidth()
    this.changeStatus()
  }

  changeStatus() {
    switch (this.options.styleMode) {
      case ArcButtonStyleMode.EMPHASIZED_LIGHT:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_NORMAL_BTN_COLOR);
        this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR);
        this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_PRESSED_BTN_COLOR);
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
        this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_TEXT_COLOR);
        this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR);
        break;

      case ArcButtonStyleMode.NORMAL_LIGHT:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR);
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_PRESSED_BTN_COLOR);
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_BTN_COLOR);
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_TEXT_COLOR);
        this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
        break;

      case ArcButtonStyleMode.NORMAL_DARK:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_NORMAL_BTN_COLOR);
        this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
        this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_PRESSED_BTN_COLOR);
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_BTN_COLOR);
        this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_TEXT_COLOR);
        this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
        break;

      case ArcButtonStyleMode.EMPHASIZED_DARK:
        this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR);
        this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
        this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR);
        this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR);
        this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR);
        this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
        break;

      default:
        this.btnNormalColor = this.options.backgroundColor;
        this.textNormalColor = this.options.fontColor;
        this.btnPressColor = this.options.backgroundColor;
        this.textPressColor = this.options.pressedFontColor;
        break;
    }
    if (this.options.status === ArcButtonStatus.DISABLED) {
      this.btnColor = this.btnDisableColor;
      this.fontColor = this.textDisableColor;
    } else {
      this.btnColor = this.btnNormalColor;
      this.fontColor = this.textNormalColor;
    }
  }

  /**
   * 初始化数据
   */
  private initValues() {
    this.isUp = this.options.position == ArcButtonPosition.TOP_EDGE;
    this.btnColor = this.options.backgroundColor;
    this.fontColor = this.options.fontColor;
    this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
    this.scaleValue = 0.95;
    this.changeStatus();
  }

  private getArcButtonThemeVpValue(res: Resource): number {
    if (!res) {
      return 0
    }
    let metrics = LengthMetrics.resource(res)
    let value = metrics.value
    switch (metrics.unit) {
      case LengthUnit.PX:
        return px2vp(value)

      case LengthUnit.LPX:
        return px2vp(lpx2px(value))

      case LengthUnit.FP:
        return px2vp(fp2px(value))
    }
    return value
  }

  /**
   * 判断是否超出文本框宽度
   */
  private judgeTextWidth() {
    const measureTextWidth = measure.measureText({
      textContent: this.options.label,
      fontStyle: this.options.fontStyle,
      fontFamily: this.options.fontFamily,
      fontWeight: FontWeight.Medium,
      maxLines: 1,
      fontSize: `${Constants.MIN_FONT_SIZE}fp`
    })
    this.isExceed = measureTextWidth > this.getUIContext().vp2px(this.textWidth);
  }

  aboutToAppear() {
    if (this.arcButtonTheme.BUTTON_HEIGHT === 0) {
      console.error("arcbutton can't obtain sys float value.")
      return
    }
    this.initValues();
    this.dataProcessUtil.initData();
    const pathData = this.dataProcessUtil.calculate();
    this.generatePath(pathData);
  }

  private calculateActualPosition(pos: ArcButtonPoint, canvasTopPos: ArcButtonPoint): ArcButtonPoint {
    const x = this.getUIContext().vp2px(pos.x - canvasTopPos.x);
    const y = this.getUIContext().vp2px(pos.y - canvasTopPos.y);
    return new ArcButtonPoint(x, y);
  }

  private generatePath(data: AllPoints | null) {
    if (data === null) {
      return
    }
    this.canvasWidth = data.btnWidth + Constants.SHADOW_BLUR * 2;
    this.canvasHeight = data.btnHeight + Constants.DISTANCE_FROM_BORDER * 2;

    const margin = this.options.fontMargin;
    const start = margin?.start?.value ?? 0;
    const end = margin?.end?.value ?? 0;
    const top = margin?.top?.value ?? 0;
    const bottom = margin?.bottom?.value ?? 0;
    this.textWidth = data.btnWidth - start - end;
    this.textHeight = data.btnHeight - top - bottom;
    this.judgeTextWidth();
    const canvasLeftTopPoint = data.canvasLeftTop;
    canvasLeftTopPoint.x -= Constants.SHADOW_BLUR;
    canvasLeftTopPoint.y -= Constants.DISTANCE_FROM_BORDER;

    const leftTopPoint = this.calculateActualPosition(data.leftTopPoint, canvasLeftTopPoint);
    const upperArcCircleR: number = this.getUIContext().vp2px(this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2);

    const rightTopPoint = this.calculateActualPosition(data.rightTopPoint, canvasLeftTopPoint);
    const chamferCircleR: number = this.getUIContext().vp2px(this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS);

    const rightBottomPoint = this.calculateActualPosition(data.rightBottomPoint, canvasLeftTopPoint);
    const lowerArcCircleR: number = this.getUIContext().vp2px(this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2);

    const leftBottomPoint = this.calculateActualPosition(data.leftBottomPoint, canvasLeftTopPoint);

    const pathStr = `M ${leftTopPoint.x} ${leftTopPoint.y} A ${upperArcCircleR} ${upperArcCircleR}, 0, 0, 0,
       ${rightTopPoint.x} ${rightTopPoint.y}` +
      `Q ${rightTopPoint.x - chamferCircleR * 1.2} ${rightTopPoint.y +
        chamferCircleR * 0.6} ${rightBottomPoint.x} ${rightBottomPoint.y}` +
      `A ${lowerArcCircleR} ${lowerArcCircleR}, 0, 0, 0, ${leftBottomPoint.x}
       ${leftBottomPoint.y}` +
      `Q ${leftTopPoint.x + chamferCircleR * 1.2} ${leftTopPoint.y +
        chamferCircleR * 0.6} ${leftTopPoint.x} ${leftTopPoint.y}`

    this.pathString = pathStr
  }

  @Builder
  TextBuilderIsExceed() {
    Text(this.options.label)
      .width(this.textWidth)
      .height(this.textHeight)
      .fontColor(this.fontColor.color)
      .fontSize(this.fontSize)
      .maxLines(1)
      .textAlign(TextAlign.Center)
      .fontWeight(FontWeight.Medium)
      .fontStyle(this.options.fontStyle)
      .fontFamily(this.options.fontFamily)
      .backgroundColor(Color.Transparent)
      .textOverflow({ overflow: TextOverflow.MARQUEE })
      .margin({
        start: this.options.fontMargin.start,
        top: this.isUp ? this.options.fontMargin.bottom : this.options.fontMargin.top,
        end: this.options.fontMargin.end,
        bottom: this.options.fontMargin.bottom
      })
  }

  @Builder
  TextBuilderNormal() {
    Text(this.options.label)
      .width(this.textWidth)
      .height(this.textHeight)
      .textAlign(TextAlign.Center)
      .fontColor(this.fontColor.color)
      .maxFontSize(`${Constants.MAX_FONT_SIZE}fp`)
      .minFontSize(`${Constants.MIN_FONT_SIZE}fp`)
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

  private cover(params: LengthMetrics): string {
    switch (params.unit) {
      case LengthUnit.VP:
        return `${params.value}vp`;
      case LengthUnit.PX:
        return `${params.value}px`;
      case LengthUnit.FP:
        return `${params.value}fp`;
      case LengthUnit.LPX:
        return `${params.value}lpx`;
      case LengthUnit.PERCENT:
        return `${params.value}%`;
    }
  }

  private getShadow(): ShadowOptions | undefined {
    if (!this.options.shadowEnabled) {
      return undefined;
    }
    return {
      radius: Constants.SHADOW_BLUR,
      color: this.options.shadowColor.color,
      offsetY: Constants.SHADOW_OFFSET_Y
    }
  }

  build() {
    Stack({ alignContent: Alignment.Center }) {
      Button({ type: ButtonType.Normal, stateEffect: true })
        .width('100%')
        .height('100%')
        .rotate({ angle: !this.isUp ? 0 : 180 })
        .clipShape(new Path({ commands: this.pathString }))
        .backgroundColor(this.btnColor.color)
        .backgroundBlurStyle(this.options.backgroundBlurStyle)
        .shadow(this.getShadow())
      if (this.isExceed) {
        this.TextBuilderIsExceed()
      } else {
        this.TextBuilderNormal()
      }
    }
    .enabled(this.options.status !== ArcButtonStatus.DISABLED)
    .opacity((this.options.styleMode === ArcButtonStyleMode.EMPHASIZED_LIGHT &&
      this.options.status === ArcButtonStatus.DISABLED) ? Constants.DEFAULT_TRANSPARENCY : 1)
    .animation({ curve: this.curves })
    .width(this.canvasWidth)
    .height(this.canvasHeight)
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
    const x = event.touches[0].windowX;
    const y = event.touches[0].windowY;
    if (this.options.onTouch) {
      this.options.onTouch(event);
    }
    switch (event.type) {
      case TouchType.Down:
        this.scaleX = this.scaleValue;
        this.scaleY = this.scaleValue;
        this.btnColor = this.btnPressColor;
        this.fontColor = this.textPressColor;
        break;
      case TouchType.Up:
        this.scaleX = 1;
        this.scaleY = 1;
        this.btnColor = this.btnNormalColor;
        this.fontColor = this.textNormalColor;
        break;
      default:
        break;
    }
  }
}

class DataProcessUtil {
  private dial: ArcButtonCircle = new ArcButtonCircle(0, 0, 0);
  private arc: ArcButtonCircle = new ArcButtonCircle(0, 0, 0);
  private height: number = 0;
  private width: number = 0;
  private arcButtonTheme: ArcButtonThemeInterface | undefined = undefined

  constructor(theme: ArcButtonThemeInterface) {
    this.arcButtonTheme = theme
  }

  initData() {
    const dialRadius = this.arcButtonTheme!.DIAL_CIRCLE_DIAMETER / 2;
    this.dial = new ArcButtonCircle(dialRadius, dialRadius, dialRadius);

    const arcRadius = this.arcButtonTheme!.ARC_CIRCLE_DIAMETER / 2;
    this.height = this.arcButtonTheme!.BUTTON_HEIGHT;
    const arcX = this.dial.center.x;
    const arcY = this.dial.center.y + dialRadius + arcRadius - this.height;
    this.arc = new ArcButtonCircle(arcRadius, arcX, arcY);
  }

  calculate(): AllPoints {
    const chamferCircleR = this.arcButtonTheme!.CHAMFER_CIRCLE_RADIUS;
    const innerDial = new ArcButtonCircle(this.dial.radius - chamferCircleR, this.dial.center.x, this.dial.center.y);
    const innerArc = new ArcButtonCircle(this.arc.radius - chamferCircleR, this.arc.center.x, this.arc.center.y);
    const intersections = this.findCircleIntersections(innerArc, innerDial);
    const tp1 = this.calculateIntersection(this.arc.center, this.arc.radius, intersections[0]);
    const tp2 = this.calculateIntersection(this.arc.center, this.arc.radius, intersections[1]);
    const tp3 = this.calculateIntersection(this.dial.center, this.dial.radius, intersections[1]);
    const tp4 = this.calculateIntersection(this.dial.center, this.dial.radius, intersections[0]);

    this.width = this.calculateDistance(intersections[0], intersections[1]) + chamferCircleR * 2;
    const canvasLeftTop = new ArcButtonPoint(intersections[0].x - chamferCircleR, this.dial.center.y +
    this.dial.radius - this.height);

    return new AllPoints(this.width, this.height, tp2, tp1, tp3, tp4, canvasLeftTop);
  }

  /**
   * 计算两点间距离
   * @param point1 点1
   * @param point2 点2
   * @returns 距离
   */
  calculateDistance(point1: ArcButtonPoint, point2: ArcButtonPoint): number {
    return Math.sqrt((point2.x - point1.x) ** 2 + (point2.y - point1.y) ** 2);
  }

  calculateIntersection(circleCenter: ArcButtonPoint, circleRadius: number, point: ArcButtonPoint): ArcButtonPoint {
    const h = circleCenter.x;
    const k = circleCenter.y;
    const x = point.x;
    const y = point.y;

    //计算直线斜率
    let m: number = 0;
    if (x !== h) {
      m = (y - k) / (x - h);
    } else {
      m = -1;
    }
    
    //计算截距
    let intercept: number = 0;
    if (m !== -1) {
      intercept = y - m * x;
    }

    //保存焦点位置
    let resultPoint: ArcButtonPoint[] = []

    //判断斜率
    if (m !== -1) {
      const a = Math.pow(m, 2) + 1;
      const b = 2 * (m * intercept - m * k - h);
      const c = k ** 2 - circleRadius ** 2 + h ** 2 - 2 * intercept * k + intercept ** 2;

      const x1 = (-b + (b ** 2 - 4 * a * c) ** 0.5) / (2 * a);
      const x2 = (-b - (b ** 2 - 4 * a * c) ** 0.5) / (2 * a);
      const y1: number = m * x1 + intercept;
      const y2: number = m * x2 + intercept;

      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x2, y2)];
    } else {
      const x1 = h;
      const y1 = k + circleRadius;
      const y2 = k - circleRadius;
      resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x1, y2)];
    }

    const d1 = this.calculateDistance(resultPoint[0], point);
    const d2 = this.calculateDistance(resultPoint[1], point);
    if (d1 < d2) {
      return resultPoint[0];
    } else {
      return resultPoint[1];
    }
  }

  /**
   * 查找两圆的交点
   * @param C1 第一个圆
   * @param c2 第二个圆
   * @returns 两圆相交的点的数组
   */
  findCircleIntersections(firstCircus: ArcButtonCircle, secondCircus: ArcButtonCircle): ArcButtonPoint[] {
    const firstCircusR = firstCircus.radius;
    const firstCircusCenterX = firstCircus.center.x;
    const firstCircusCenterY = firstCircus.center.y;

    const secondCircusR = secondCircus.radius;
    const secondCircusCenterX = secondCircus.center.x;
    const secondCircusCenterY = secondCircus.center.y;

    // 计算两个圆心之间的距离
    const distance = Math.sqrt((firstCircusCenterX - secondCircusCenterX) ** 2 + (firstCircusCenterY -
      secondCircusCenterY) ** 2);

    // 检查异常情况
    if (distance > firstCircusR + secondCircusR) {
      //两个圆分离，不相交
      return [];
    } else if (distance < Math.abs(firstCircusR - secondCircusR)) {
      //一个圆包含在另一个圆内，不相交
      return [];
    } else if (distance === 0 && firstCircusR === secondCircusR) {
      //两个圆完全重合，具有无穷多交点
      return [];
    }

    // 计算交点
    const a = (firstCircusR ** 2 - secondCircusR ** 2 + distance ** 2) / (2 * distance);
    const h = Math.sqrt(firstCircusR ** 2 - a ** 2);

    // 中间变量
    const x2 = firstCircusCenterX + a * (secondCircusCenterX - firstCircusCenterX) / distance;
    const y2 = firstCircusCenterY + a * (secondCircusCenterY - firstCircusCenterY) / distance;

    // 交点
    let intersection1 = new ArcButtonPoint(x2 + h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 -
      h * (secondCircusCenterX - firstCircusCenterX) / distance);
    let intersection2 = new ArcButtonPoint(x2 - h * (secondCircusCenterY - firstCircusCenterY) / distance, y2 +
      h * (secondCircusCenterX - firstCircusCenterX) / distance);

    if (intersection1.x > intersection2.x) {
      const mid = intersection1;
      intersection1 = intersection2;
      intersection2 = mid;
    }

    return [intersection1, intersection2];
  }
}

class ArcButtonCircle {
  public radius: number;
  public center: ArcButtonPoint;

  constructor(radius: number, x: number, y: number) {
    this.radius = radius;
    this.center = new ArcButtonPoint(x, y);
  }
}

class ArcButtonPoint {
  public x: number;
  public y: number;

  constructor(x: number, y: number) {
    this.x = x;
    this.y = y;
  }
}

class AllPoints {
  public btnWidth: number;
  public btnHeight: number;
  public leftTopPoint: ArcButtonPoint;
  public rightTopPoint: ArcButtonPoint;
  public leftBottomPoint: ArcButtonPoint;
  public rightBottomPoint: ArcButtonPoint;
  public canvasLeftTop: ArcButtonPoint;

  constructor(btnWidth: number,
    btnHeight: number,
    leftTopPoint: ArcButtonPoint,
    rightTopPoint: ArcButtonPoint,
    leftBottomPoint: ArcButtonPoint,
    rightBottomPoint: ArcButtonPoint,
    canvasLeftTop: ArcButtonPoint) {
    this.btnWidth = btnWidth;
    this.btnHeight = btnHeight;
    this.leftTopPoint = leftTopPoint;
    this.rightTopPoint = rightTopPoint;
    this.leftBottomPoint = leftBottomPoint;
    this.rightBottomPoint = rightBottomPoint;
    this.canvasLeftTop = canvasLeftTop;
  }
}
