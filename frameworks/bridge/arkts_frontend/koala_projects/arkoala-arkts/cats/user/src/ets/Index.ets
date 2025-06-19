import router from '@ohos.router'

type T = [ ResourceColor, number ]

@Entry
@Component
struct Index {
  build() {
    Column() {
      Question({
        question: "Help!",
        answer: "Don't panic!",
        color: 0xf13428
      })
      Question({
        question: "I'm tired...",
        answer: "Have some rest!",
        color: 0x7bf128
      })
      Question({
        question: "Support me!",
        answer: "We are proud of you!",
        color: 0x28a6f1
      })
        // Button("Click me")
        //   .onClick(() => {
        //     console.log("On click")
        //   })
        //     // .onHover((isHover) => this.isActive = isHover ?? false)
        //     // .radialGradient({ center: ["50%", "50%"], radius: "20%", colors: [[this.color, 0.0], ['#909090', 0.25], [this.color, 0.5]], repeating: true })
        //   .fontColor(Color.Black)
        //   .fontWeight(FontWeight.Bold)
        //   .fontSize(30)
        //   .width(250)
        //   .height(250)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xcedada)
    .justifyContent(FlexAlign.SpaceEvenly)
  }

  pageTransition() {
    PageTransitionEnter({ duration: 1000, curve : Curve.EaseIn })
      .opacity(1)
      .slide(SlideEffect.Left)
    PageTransitionExit({ duration: 1000, curve : Curve.EaseOut })
      .slide(SlideEffect.Left)
    //  .scale({x: 0.5, y: 0.5} as ScaleOptions)
      .opacity(0)
    // .onEnter((type: RouteType, progress: number) => {
    //   console.log("Progress", progress)
    // })
  }
}

@Component
struct Question {
  @Prop question: string
  @Prop color: number
  @Prop answer: string
  @State isActive: boolean = false

  build() {
    let radial:T[] = [[this.color, 0.0], ['#909090', 0.25], [this.color, 0.5]]

    Button(this.question)
      .onClick((event: ClickEvent) => {
        router.pushUrl({
          url: "SomeCat",
          params: new RouterParams(this.answer)
        })
      })
      .onHover((isHover:boolean, event: HoverEvent) => {
        this.isActive = isHover
      })
      .radialGradient({ center: ["50%", "50%"],
                        radius: "25%",
                        colors: Array.from<T>(radial),
                        repeating: true 
                      } as Type_CommonMethod_radialGradient_value)
      .fontColor(Color.Black)
      .fontWeight(this.isActive ? FontWeight.Bold : FontWeight.Normal)
      .fontSize(this.isActive ? 30 : 24)
      .width(this.isActive ? 250 : 210)
      .height(this.isActive ? 250 : 210)
      // .animation({
      //     duration: 2000,
      //     curve: Curve.EaseOut,
      //     playMode: PlayMode.Normal
      // })
  }
}

export class RouterParams {
  readonly message: string

  constructor(message: string) {
    this.message = message
  }
}

export function getRouterParams(defaultMessage: string): RouterParams {
  const params = router.getParams()
  return params ? params as RouterParams : new RouterParams(defaultMessage)
}

