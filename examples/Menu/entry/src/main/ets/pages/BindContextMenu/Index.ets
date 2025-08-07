import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct Index {
  scroller: Scroller = new Scroller()
  @State items : ListCategories[] = [
    {title:'labelInfoTest',utl:'pages/BindContextMenu/bindContextMenus/LabelInfoAnimation/labelInfoTest'},
    {title:'ContentTest',utl:'pages/BindContextMenu/bindContextMenus/ContentAnimation/Content'},
    {title:'UIConsistency',utl:'pages/BindContextMenu/UIConsistency'},
    {title:'bindMenu',utl:'pages/BindContextMenu/bindMenu'},
    {title:'bindContextMenuTest',utl:'pages/BindContextMenu/bindContextMenuTest'},
    {title:'AvoidMenu',utl:'pages/BindContextMenu/AvoidMenu'}
  ]

  build() {
    Scroll(this.scroller) {
      Column() {
        List({space:'10vp'}) {
          ForEach(this.items,(item : ListCategories) => {
            ListItem() {
              Text(item.title).fontSize(20).fontWeight(FontWeight.Bold).onClick(() => {
                router.pushUrl({url:item.utl})
              })
            }.width('80%').height('50vp').backgroundColor('#ff53ecd9').borderRadius(10)
          })
        }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
      }.width('100%').height('100%')
    }.height('100%')
  }
}