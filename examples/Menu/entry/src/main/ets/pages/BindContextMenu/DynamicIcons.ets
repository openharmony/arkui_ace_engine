import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct DynamicIcons {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'DynamicIcons_dynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/DynamicIcons/dynamicIcon'},
    {title:'DynamicIcons_endDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/DynamicIcons/endDynamicIcon'},
    {title:'DynamicIcons_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/DynamicIcons/startDynamicIcon'},
    {title:'endDynamicIcon_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/endDynamicIcon/endDynamicIcon'},
    {title:'IconTextAlign_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/IconTextAlign/dynamicIcon'},
    {title:'IconTextAlign_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/IconTextAlign/endDynamicIcon'},
    {title:'IconTextAlign_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/IconTextAlign/startDynamicIcon'},
    {title:'SettingIcons_startDynamicIcon',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuDynamicIcons/SettingIcons/startDynamicIcon'},
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