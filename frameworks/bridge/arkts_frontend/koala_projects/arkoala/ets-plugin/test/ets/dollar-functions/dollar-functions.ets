@Entry
@Component
struct Index {
  @State myState2: string = "Hello"

  build() {
    Column() {
      Image($rawfile('startIcon.png'))
      Image($r('app.media.icon'))
      Text($myState2)
    }
    .height('100%')
    .width('100%')
  }
}