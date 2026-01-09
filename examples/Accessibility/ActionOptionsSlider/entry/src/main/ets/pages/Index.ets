import router from '@ohos.router'

interface routerInfo {
  url: string;
  info: string;
}

let routerData: routerInfo[] = [
  {url: "pages/slider001", info: "默认值测试"},
  {url: "pages/slider002", info: "正常值测试"},
  {url: "pages/slider003", info: "异常值测试"},
  {url: "pages/slider004", info: "modifier测试"},
  {url: "pages/slider005", info: "动态切换"},
]
@Entry
@Preview
@Component
struct Index {
  listScroller: Scroller = new Scroller()
  build() {
    Column({ space: 10 }) {
      List({space: 10, scroller: this.listScroller}) {
        ForEach(routerData, (item: routerInfo) => {
          ListItem() {
            Text(item.info)
              .width("100%")
              .height("50vp")
              .fontSize("20vp")
              .backgroundColor(0x6666FF)
              .borderRadius(10)
              .textAlign(TextAlign.Center)
              .onClick(() => {
                router.pushUrl({
                  url: item.url
                })
              })
          }
        })
      }.width("90%")

      .scrollBar(BarState.Off)
      .friction(0.6)
      .divider({ strokeWidth: 2, color: 0xFFFFFF, startMargin: 20, endMargin: 20 }) // 每行之间的分界线
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
    }.width('100%').height('100%').backgroundColor(0xE0FFFF).padding({ top: 5 })
  }
}

