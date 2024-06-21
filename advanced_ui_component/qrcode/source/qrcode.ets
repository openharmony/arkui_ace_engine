import { LengthMetrics,ColorMetrics, LengthUnit } from '@ohos.arkui.node';
export enum QrcodeState {
  NORMAL,
  EXPIRED,
  LOADING
}

enum ConfigData {
  FIVE_HUNDRED = 500,
  DEFAULT_OPACITY = 0.4,
  DEFAULT_TIMES = 200
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


export class QrcodeOptions  {
  edgeLength?: LengthMetrics //边框长度
  color?: ColorMetrics //二维码颜色
  backgroundColor?: ColorMetrics //背景颜色
  textColor?: ColorMetrics //字体颜色
  textContent?: string //失效提示文本内容
  borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses //圆角
  opacity?: number | Resource//不透明度
  animationCurve?: Curve | string | ICurve //淡入曲线参数
  animationDuration?: number

  qrcodeSideLength?: LengthMetrics //二维码的边长
  expiredImageLength?: LengthMetrics //失效图标边长
  textSize?: ResourceStr //提示文本字体大小
  textWeight?: number | FontWeight | string //文本字重
  space?: ResourceStr //图标与文本间隔
  loadingImageLength?: LengthMetrics //加载图标边长

  optionsChange?: () => VoidCallback

  constructor(options: CommonQrcodeOptions) {
    this.edgeLength = options.edgeLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_TWENTY_FIVE_VP,LengthUnit.VP)
    this.color = options.color ?? ColorMetrics.resourceColor(Color.Black)
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.White)
    this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White)
    this.textContent = options.textContent ?? ConfigDataConstants.TIPS

    this.borderRadius = options.borderRadius ?? $r('sys.float.ohos_id_corner_radius_default_s')
    this.opacity = options.opacity ?? ConfigData.DEFAULT_OPACITY
    this.animationCurve = options.animationCurve ?? ConfigDataConstants.ANIMATION_CURVE
    this.animationDuration = options.animationDuration ?? ConfigData.DEFAULT_TIMES
    this.qrcodeSideLength = options.qrcodeSideLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_ONE_VP,LengthUnit.VP)
    this.expiredImageLength = options.expiredImageLength ?? new LengthMetrics(ConfigDataConstants.TWENTY_EIGHT_VP,LengthUnit.VP)
    this.textSize = options.textSize ?? ConfigDataConstants.ELEVEN_FP
    this.textWeight = options.textWeight ?? FontWeight.Medium
    this.space = options.space ?? ConfigDataConstants.SIX_VP
    this.loadingImageLength = options.loadingImageLength ?? new LengthMetrics(ConfigDataConstants.THIRTY_FOUR_VP,LengthUnit.VP)
  }

}

@Component
export struct Qrcode {
  @Link @Watch('optionsChange') options: QrcodeOptions
  @Link value: string
  @Link state: QrcodeState

  //监听组件状态变化
  optionsChange() {
    console.info('optionsChange end')
  }

  aboutToAppear() {
    if (this.options === undefined) {
      return
    } else {
      console.info('aboutToAppear:' + JSON.stringify(this.options))
      this.optionsChange()
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
      if (this.state != QrcodeState.LOADING) {
        return this.state = QrcodeState.LOADING
      } else {
        return this.state
      }
    })
  }
}