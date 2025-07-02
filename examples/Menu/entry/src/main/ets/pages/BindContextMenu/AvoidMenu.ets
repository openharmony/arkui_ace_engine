import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct AvoidMenu {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'bottomPlacement_bottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/bottom'},
    {title:'bottomPlacement_bottomLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/bottomLeft'},
    {title:'bottomPlacement_bottomRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/bottomRight'},
    {title:'bottomPlacement_left',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/left'},
    {title:'bottomPlacement_leftBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/leftBottom'},
    {title:'bottomPlacement_leftTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/leftTop'},
    {title:'bottomPlacement_none',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/none'},
    {title:'bottomPlacement_right',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/right'},
    {title:'bottomPlacement_rightBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/rightBottom'},
    {title:'bottomPlacement_rightTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/rightTop'},
    {title:'bottomPlacement_top',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/top'},
    {title:'bottomPlacement_topLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/topLeft'},
    {title:'bottomPlacement_topRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/bottomPlacement/topRight'},
    {title:'leftPlacement_bottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/bottom'},
    {title:'leftPlacement_bottomLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/bottomLeft'},
    {title:'leftPlacement_bottomRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/bottomRight'},
    {title:'leftPlacement_left',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/left'},
    {title:'leftPlacement_leftBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/leftBottom'},
    {title:'leftPlacement_leftTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/leftTop'},
    {title:'leftPlacement_none',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/none'},
    {title:'leftPlacement_right',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/right'},
    {title:'leftPlacement_rightBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/rightBottom'},
    {title:'leftPlacement_rightTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/rightTop'},
    {title:'leftPlacement_top',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/top'},
    {title:'leftPlacement_topLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/topLeft'},
    {title:'leftPlacement_topRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/leftPlacement/topRight'},
    {title:'rightPlacement_bottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/bottom'},
    {title:'rightPlacement_bottomLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/bottomLeft'},
    {title:'rightPlacement_bottomRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/bottomRight'},
    {title:'rightPlacement_left',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/left'},
    {title:'rightPlacement_leftBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/leftBottom'},
    {title:'rightPlacement_leftTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/leftTop'},
    {title:'rightPlacement_none',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/none'},
    {title:'rightPlacement_right',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/right'},
    {title:'rightPlacement_rightBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/rightBottom'},
    {title:'rightPlacement_rightTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/rightTop'},
    {title:'rightPlacement_top',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/top'},
    {title:'rightPlacement_topLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/topLeft'},
    {title:'rightPlacement_topRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/rightPlacement/topRight'},
    {title:'topPlacement_bottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/bottom'},
    {title:'topPlacement_bottomLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/bottomLeft'},
    {title:'topPlacement_bottomRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/bottomRight'},
    {title:'topPlacement_left',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/left'},
    {title:'topPlacement_leftBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/leftBottom'},
    {title:'topPlacement_leftTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/leftTop'},
    {title:'topPlacement_none',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/none'},
    {title:'topPlacement_right',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/right'},
    {title:'topPlacement_rightBottom',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/rightBottom'},
    {title:'topPlacement_rightTop',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/rightTop'},
    {title:'topPlacement_top',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/top'},
    {title:'topPlacement_topLeft',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/topLeft'},
    {title:'topPlacement_topRight',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/topPlacement/topRight'},
    {title:'centerPlacement',utl:'pages/BindContextMenu/bindContextMenus/AvoidMenu/centerPlacement/bottomLeft'},
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