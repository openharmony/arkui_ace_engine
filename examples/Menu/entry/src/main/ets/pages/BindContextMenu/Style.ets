import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct Style {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'MenuStyle_endIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuStyle/endIconMenu'},
    {title:'MenuStyle_icon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuStyle/iconMenu'},
    {title:'MenuStyle_normal',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuStyle/normalMenu'},
    {title:'MenuStyle_startIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuStyle/startIconMenu'},
    {title:'MenuStyle_titleIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuStyle/titleIconMenu'},
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