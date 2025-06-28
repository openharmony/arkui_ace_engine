import router from '@ohos.router'
@Entry
@Component
struct BaiduBindMenu {
  build() {
    Row(){
      Column() {
        Text('单击展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)

      }
      .bindMenu([
        {
          value: '跳转Baidu',
          action: () => {
            router.pushUrl({
              url: 'pages/baidu',
            })
            console.info('handle Menu select')
          }
        }

      ])

    }
    .width('100%')
    .height('100%')
  }
}