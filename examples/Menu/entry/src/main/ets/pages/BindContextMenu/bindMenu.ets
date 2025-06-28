import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct bindMenuTest {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'baidu',utl:'pages/BindContextMenu/bindContextMenus/bindMenu/baidu'},
    {title:'secondInterface',utl:'pages/BindContextMenu/bindContextMenus/bindMenu/secondInterface'},
    {title:'menu',utl:'pages/BindContextMenu/bindContextMenus/bindMenu/menu'},
    {title:'menuBuilder',utl:'pages/BindContextMenu/bindContextMenus/bindMenu/menuBuilder'},
  ]

  build() {
    Scroll(this.scroller) {
      Column() {
        List({space:'10vp'}) {
          ForEach(this.items,(item : ListCategories) => {
            ListItem() {
              Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).onClick(() => {
                router.pushUrl({url:item.utl})
              })
            }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
          })
        }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
      }.width('100%').height('100%')
    }.height('100%')
  }
}