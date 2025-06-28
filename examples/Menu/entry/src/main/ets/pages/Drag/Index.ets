import router from '@ohos.router';
@Entry
@Component
struct Index {

  build() {
    Scroll() {
      Row() {
        Column() {
          Text('').fontSize(28).fontWeight(FontWeight.Bold)
          Button('Drag1')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag1',
              })
            })
          Button('Drag2')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag2',
              })
            })
          Button('Drag3')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag3',
              })
            })
          Button('Drag4')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag4',
              })
            })
          Button('Drag5')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag5',
              })
            })
          Button('Drag6')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag6',
              })
            })
          Button('Drag7')
            .margin(10)
            .height(60)
            .width(300)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Drag/Drag7',
              })
            })

        }
        .width('100%')
      }
      .height('100%')
    }
  }
}