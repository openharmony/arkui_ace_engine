import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct bindContextMenuTest {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'baiduLongPress',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/baiduLongPress'},
    {title:'baiduRightClick',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/baiduRightClick'},
    {title:'menuLongPress',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/menuLongPress'},
    {title:'menuRightClick',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/menuRightClick'},
    {title:'secondInterfaceLongPress',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/secondInterfaceLongPress'},
    {title:'secondInterfaceRightClick',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/secondInterfaceRightClick'},
    {title:'builderLongPress',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/builderLongPress'},
    {title:'builderRightClick',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenuTest/builderRightClick'},
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