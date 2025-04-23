import router from '@ohos.router';

interface Categories {
  title:string,
  url:string
}

@Entry
@Component
struct Index {
  private items: Categories[] = [
    { title: "示例1：弹出普通菜单", url: "pages/MenuItemDemo" },
    { title: "示例2：弹出自定义菜单", url: "pages/MenuBuilder" },
    { title: "示例3：长按弹出菜单", url: "pages/MenuLongPress" },
    { title: "示例4：右键弹出指向型菜单", url: "pages/MenuRightClick" },
    { title: "示例5：长按弹出菜单的截图预览样式", url: "pages/MenuImagePreview" },
    { title: "示例6：长按弹出菜单的自定义预览样式", url: "pages/MenuBuilderPreview" },
    { title: "示例7：设置状态变量弹出菜单", url: "pages/ContextMenuIsShown" },
    { title: "示例8：设置菜单和预览的动效", url: "pages/ContextMenuTransition" },
    { title: "示例9：设置symbol类型图标", url: "pages/MenuSymbolIcon" },
    { title: "示例10：设置一镜到底动效", url: "pages/MenuHoverScale" },
  ]

  build() {
    Column() {
      Text('菜单控制示例代码').fontSize(22)
      List({ space: '10vp' }) {
        ForEach(this.items, (item: Categories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
          }
          .width('90%')
          .height('40vp')
          .backgroundColor('#ff53ecd9')
          .borderRadius(10)
          .onClick(() => {
            router.pushUrl({ url: item.url })
          })
        })
      }.alignListItem(ListItemAlign.Center).margin(({ top: '10vp' })).width('100%').height('70%')
    }.width('100%').height('100%')
  }
}