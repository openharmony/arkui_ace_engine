import router from '@ohos.router';
@Entry
@Component
struct Index {

  build() {
    Scroll() {
      Row() {
        Column() {
          Button('右击')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/RightClick',
              })
            })
          Button('长按')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/LongPress',
              })
            })
          Button('aboutToAppear_BindMenu_编译失败_onAppear()')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToAppear/BindMenu',
              })
            })
          Button('aboutToDisappear_右击')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_RightClick',
              })
            })
          Button('aboutToDisappear_长按')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_LongPress',
              })
            })
            Button('aboutToDisappear_BindMenu_编译失败_onDisappear')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/LifeCycle/aboutToDisappear/Dis_BindMenu',
              })
            })


        }
        .width('100%')
      }
      .height('100%')
    }
  }
}