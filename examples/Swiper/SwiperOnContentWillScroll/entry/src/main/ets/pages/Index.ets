import router from '@ohos.router';

@Entry
@Component
struct Index {
  build() {
    Column() {
      Button("非嵌套场景")
        .onClick(() => {
          router.pushUrl({
            url: "pages/SwiperNormal"
          })
        })
        .margin(10)
    }
    .height('100%')
    .width('100%')
  }
}