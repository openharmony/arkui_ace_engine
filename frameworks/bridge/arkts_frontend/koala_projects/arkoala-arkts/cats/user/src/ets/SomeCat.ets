import router from '@ohos.router'
import { getRouterParams } from './Index'

// function catUrl(counter: number): string {
//   return `https://cataas.com/cat?counter=${counter}`
//   // return `http://localhost:8080/cats?counter=${counter}`
// }

@Entry
@Component
struct SomeCat {
  @State message: string = getRouterParams("Meow").message
  // @State loading: boolean = false
  @State error: string = ""

  counter:number = 0

  aboutToAppear() {
    this.counter = Math.random()
    // this.loading = true
    this.error = ""
  }

  build() {
    Stack() {
      // if (this.loading) {
      //   LoadingProgress()
      //     .color(Color.Blue)
      //     .width('20%')
      //     .height('20%')
      //     .align(Alignment.Center)
      // }
      if (this.error. length > 0) {
         Text("Error: " + this.error)
            .fontColor('#ff0000')
            .fontSize(30)
      }
      // Image(catUrl(this.counter))
      Image("/resources/koala.png")
        // .onFinish(() => {
        //   this.loading = false
        // })
        .objectFit(ImageFit.Cover)
        .onError((e: ImageError) => {
          // this.loading = false
          this.error = this.error.length > 0 ? this.error : (e?.message ?? "Unknown")
          console.log("Image onError", e?.message)
        })
        .onClick((event: ClickEvent) => {
          console.log("%%%%%%% Cat click back %%%%%%%%")
          router.back()
        })
        .height('100%')
        .width('100%')
      Text(this.message)
        .fontColor(Color.White)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .offset({y: 300} as Position)
        .borderWidth(3)
        .borderColor('#404040')
        .backgroundColor('#202020')
        .padding(7)
        .borderRadius(5)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xcedada)
    .alignContent(Alignment.Center)
  }

  pageTransition() {
    PageTransitionEnter({ duration: 1000, curve : Curve.EaseIn })
      .opacity(1)
      .slide(SlideEffect.Right)
      .onEnter((type: RouteType, progress: number) => {
        console.log("Cat on enter: ", progress)
      })

    PageTransitionExit({ duration: 1000, curve : Curve.EaseOut })
      .slide(SlideEffect.Right)
      // .scale({x: 0.5, y: 0.5} as ScaleOptions)
      .opacity(0)
      .onExit((type: RouteType, progress: number) => {
        console.log("Cat on exit: ", progress)
      })
  }
}