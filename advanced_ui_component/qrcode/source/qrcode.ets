import { LengthMetrics,ColorMetrics, LengthUnit } from '@ohos.arkui.node';

export enum QrcodeState {
  NORMAL,
  EXPIRED,
  LOADING
}

class ConfigDataConstants {
  static readonly TIPS = '二维码已失效，请刷新';
  static readonly ANIMATION_CURVE= '0.33,0,0.67,1';
  static readonly ONE_HUNDRED_TWENTY_FIVE_VP = 125;
  static readonly ONE_HUNDRED_ONE_VP = 101;
  static readonly TWENTY_EIGHT_VP = 28;
  static readonly THIRTY_FOUR_VP = 34;
  static readonly ELEVEN_FP = '11fp';
  static readonly SIX_VP = '6vp';
  static readonly FIVE_HUNDRED = 500;
  static readonly DEFAULT_OPACITY = 0.4;
  static readonly DEFAULT_TIMES = 200;
}

interface CommonQrcodeOptions {
  edgeLength?: LengthMetrics //边框长度
  color?: ColorMetrics //二维码颜色
  backgroundColor?: ColorMetrics //背景颜色
  textColor?: ColorMetrics //字体颜色
  textContent?: string //失效提示文本内容
  borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses //圆角
  opacity?: number | Resource //不透明度
  animationCurve?: Curve | string | ICurve //淡入曲线参数
  animationDuration?: number

  qrcodeSideLength?: LengthMetrics //二维码的边长
  expiredImageLength?: LengthMetrics //失效图标边长
  textSize?: ResourceStr //提示文本字体大小
  textWeight?: number | FontWeight | string //文本字重
  space?: ResourceStr //图标与文本间隔
  loadingImageLength?: LengthMetrics //加载图标边长

}

@ObservedV2
export class QrcodeOptions  {
  @Trace edgeLength?: LengthMetrics //边框长度
  @Trace color?: ColorMetrics //二维码颜色
  @Trace backgroundColor?: ColorMetrics //背景颜色
  @Trace textColor?: ColorMetrics //字体颜色
  @Trace textContent?: string //失效提示文本内容
  @Trace borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses //圆角
  @Trace opacity?: number | Resource//不透明度
  @Trace animationCurve?: Curve | string | ICurve //淡入曲线参数
  @Trace animationDuration?: number

  @Trace qrcodeSideLength?: LengthMetrics //二维码的边长
  @Trace expiredImageLength?: LengthMetrics //失效图标边长
  @Trace textSize?: ResourceStr //提示文本字体大小
  @Trace textWeight?: number | FontWeight | string //文本字重
  @Trace space?: ResourceStr //图标与文本间隔
  @Trace loadingImageLength?: LengthMetrics //加载图标边长

  constructor(options: CommonQrcodeOptions) {
    this.edgeLength = options.edgeLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_TWENTY_FIVE_VP,LengthUnit.VP)
    this.color = options.color ?? ColorMetrics.resourceColor(Color.Black)
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.White)
    this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White)
    this.textContent = options.textContent ?? ConfigDataConstants.TIPS

    this.borderRadius = options.borderRadius ?? $r('sys.float.ohos_id_corner_radius_default_s')
    this.opacity = options.opacity ?? ConfigDataConstants.DEFAULT_OPACITY
    this.animationCurve = options.animationCurve ?? ConfigDataConstants.ANIMATION_CURVE
    this.animationDuration = options.animationDuration ?? ConfigDataConstants.DEFAULT_TIMES
    this.qrcodeSideLength = options.qrcodeSideLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_ONE_VP,LengthUnit.VP)
    this.expiredImageLength = options.expiredImageLength ?? new LengthMetrics(ConfigDataConstants.TWENTY_EIGHT_VP,LengthUnit.VP)
    this.textSize = options.textSize ?? ConfigDataConstants.ELEVEN_FP
    this.textWeight = options.textWeight ?? FontWeight.Medium
    this.space = options.space ?? ConfigDataConstants.SIX_VP
    this.loadingImageLength = options.loadingImageLength ?? new LengthMetrics(ConfigDataConstants.THIRTY_FOUR_VP,LengthUnit.VP)
  }

}

@ComponentV2
export struct Qrcode {
  @Require @Param  options: QrcodeOptions
  @Consumer() value: string = ''
  @Consumer() state: QrcodeState = QrcodeState.NORMAL
  clickCallback: () => void = () => {}

  aboutToAppear() {
    if (this.options === undefined) {
      return
    } else {
      console.info('aboutToAppear:' + JSON.stringify(this.options))
    }
  }

  build() {
    Stack() {
      if (this.options !== void 0) {
        Column() {
          QRCode(this.value)
            .color(this.options.color?.color)
            .backgroundColor(Color.Transparent)
            .width(this.options.qrcodeSideLength?.value)
            .height(this.options.qrcodeSideLength?.value)
        }
        .height(this.options.edgeLength?.value)
        .width(this.options.edgeLength?.value)
        .backgroundColor(this.options.backgroundColor?.color)
        .borderRadius(this.options.borderRadius)
        .opacity(this.state != QrcodeState.NORMAL ? this.options.opacity : 1)
        .animation({
          duration: this.options.animationDuration,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
        .justifyContent(FlexAlign.Center)



        Column() {
          Image($r('sys.media.ohos_qrcode_refresh_icon'))
            .height(this.options.expiredImageLength?.value)
            .width(this.options.expiredImageLength?.value)
            .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)

          if (this.state == QrcodeState.LOADING) {
            LoadingProgress()
              .color(Color.White)
              .height(this.options.loadingImageLength?.value)
              .width(this.options.loadingImageLength?.value)
              .visibility(this.state == QrcodeState.LOADING ? Visibility.Visible : Visibility.None)
              .animation({
                duration: this.options.animationDuration,
                curve: this.options.animationCurve,
                playMode: PlayMode.Normal
              })
          }

          Text(this.options.textContent)
            .margin({ top: this.options.space })
            .fontColor(this.options.textColor?.color)
            .fontSize(this.options.textSize)
            .fontWeight(this.options.textWeight)
            .textAlign(TextAlign.Center)
            .width(this.options.qrcodeSideLength?.value)
            .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)

        }
        .visibility(this.state == QrcodeState.NORMAL ? Visibility.None : Visibility.Visible)
        .animation({
          duration: this.options.animationDuration,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
      }
    }
    .onClick(() => {
      this.clickCallback && this.clickCallback()
    })
  }
}