export enum QrCodeState {
  QRCODE_NORMAL,
  QRCODE_EXPIRE,
  QRCODE_LOADING
}

enum ConfigData {
  FIVE_HUNDRED = 500,
  DEFAULT_OPACITY = 0.4,
  DEFAULT_TIMES = 200
}

enum ConfigDataString {
  TIPS = '二维码已失效，请刷新',
  ANIMATION_CURVE= '0.33,0,0.67,1',
  ONE_HUNDRED_TWENTY_FIVE_VP = '125vp',
  ONE_HUNDRED_ONE_VP = '101vp',
  TWENTY_EIGHT_VP = '28vp',
  THIRTY_FOUR_VP = '34vp',
  ELEVEN_FP = '11fp',
  SIX_VP = '6vp',
}

interface CommonQrcodeOptions {
  edgeLength?: ResourceStr //边框长度
  color?: ResourceColor //二维码颜色
  backgroundColor?: ResourceColor //背景颜色
  textColor?: ResourceColor //字体颜色
  textContent?: string //失效提示文本内容
  borderRadius?: ResourceStr //圆角
  opacity?: number //不透明度
  animationCurve?: Curve | string | ICurve //淡入曲线参数
  animationTime?: number

  qrCodeLength?: ResourceStr //二维码的边长
  expireImageLength?: ResourceStr //失效图标边长
  textSize?: ResourceStr //提示文本字体大小
  textWeight?: number | FontWeight | string //文本字重
  space?: ResourceStr //图标与文本间隔
  imageLoadLength?: ResourceStr //加载图标边长

}


export class QrcodeOptions  {
  edgeLength?: ResourceStr //边框长度
  color?: ResourceColor //二维码颜色
  backgroundColor?: ResourceColor //背景颜色
  textColor?: ResourceColor //字体颜色
  textContent?: string //失效提示文本内容
  borderRadius?: ResourceStr //圆角
  opacity?: number //不透明度
  animationCurve?: Curve | string | ICurve //淡入曲线参数
  animationTime?: number

  qrCodeLength?: ResourceStr //二维码的边长
  expireImageLength?: ResourceStr //失效图标边长
  textSize?: ResourceStr //提示文本字体大小
  textWeight?: number | FontWeight | string //文本字重
  space?: ResourceStr //图标与文本间隔
  imageLoadLength?: ResourceStr //加载图标边长

  optionsChange?: () => void

  constructor(options: CommonQrcodeOptions) {
    this.edgeLength = options.edgeLength ?? ConfigDataString.ONE_HUNDRED_TWENTY_FIVE_VP
    this.color = options.color ?? Color.Black
    this.backgroundColor = options.backgroundColor ?? Color.White
    this.textColor = options.textColor ?? Color.White
    this.textContent = options.textContent ?? ConfigDataString.TIPS

    this.borderRadius = options.borderRadius ?? $r('sys.float.ohos_id_corner_radius_default_s')
    this.opacity = options.opacity ?? ConfigData.DEFAULT_OPACITY
    this.animationCurve = options.animationCurve ?? ConfigDataString.ANIMATION_CURVE
    this.animationTime = options.animationTime ?? ConfigData.DEFAULT_TIMES
    this.qrCodeLength = options.qrCodeLength ?? ConfigDataString.ONE_HUNDRED_ONE_VP
    this.expireImageLength = options.expireImageLength ?? ConfigDataString.TWENTY_EIGHT_VP
    this.textSize = options.textSize ?? ConfigDataString.ELEVEN_FP
    this.textWeight = options.textWeight ?? FontWeight.Medium
    this.space = options.space ?? ConfigDataString.SIX_VP
    this.imageLoadLength = options.imageLoadLength ?? ConfigDataString.THIRTY_FOUR_VP
  }

}

@Component
export struct QrCode {
  @Link @Watch('optionsChange') options: QrcodeOptions
  @Link value: string
  @Link state: QrCodeState

  //监听组件状态变化
  optionsChange() {
    console.info('optionsChange end')
  }

  aboutToAppear() {
    if (this.options === void 0) {
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
            .color(this.options.color)
            .backgroundColor(Color.Transparent)
            .width(this.options.qrCodeLength)
            .height(this.options.qrCodeLength)
        }
        .height(this.options.edgeLength)
        .width(this.options.edgeLength)
        .backgroundColor(this.options.backgroundColor)
        .borderRadius(this.options.borderRadius)
        .opacity(this.state != QrCodeState.QRCODE_NORMAL ? this.options.opacity : 1)
        .animation({
          duration: this.options.animationTime,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
        .justifyContent(FlexAlign.Center)



        Column() {
          Image($r('app.media.Refresh'))
            .height(this.options.expireImageLength)
            .width(this.options.expireImageLength)
            .visibility(this.state == QrCodeState.QRCODE_EXPIRE ? Visibility.Visible : Visibility.None)

          if (this.state == QrCodeState.QRCODE_LOADING) {
            LoadingProgress()
              .color(Color.White)
              .height(this.options.imageLoadLength)
              .width(this.options.imageLoadLength)
              .visibility(this.state == QrCodeState.QRCODE_LOADING ? Visibility.Visible : Visibility.None)
              .animation({
                duration: this.options.animationTime,
                curve: this.options.animationCurve,
                playMode: PlayMode.Normal
              })
          }

          Text(this.options.textContent)
            .margin({ top: this.options.space })
            .fontColor(this.options.textColor)
            .fontSize(this.options.textSize)
            .fontWeight(this.options.textWeight)
            .textAlign(TextAlign.Center)
            .width(this.options.qrCodeLength)
            .visibility(this.state == QrCodeState.QRCODE_EXPIRE ? Visibility.Visible : Visibility.None)

        }
        .visibility(this.state == QrCodeState.QRCODE_NORMAL ? Visibility.None : Visibility.Visible)
        .animation({
          duration: this.options.animationTime,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
      }
    }
    .onClick(() => {
      if (this.state != QrCodeState.QRCODE_LOADING) {
        return this.state = QrCodeState.QRCODE_LOADING
      } else {
        return this.state
      }
    })
  }
}