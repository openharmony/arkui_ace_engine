import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct Font {
  scroller: Scroller = new Scroller()
  @State message: string = 'Search'
  @State items : ListCategories[] = [
    {title:'MenuFont_FontColor_01',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontColor/contentFontColor_01'},
    {title:'MenuFont_FontColor_02',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontColor/contentFontColor_02'},
    {title:'MenuFont_FontColor_03',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontColor/contentFontColor_03'},
    {title:'MenuFont_FontColor_04',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontColor/contentFontColor_04'},
    {title:'MenuFont_ContentFontSize_10',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/contentFontSize_10'},
    {title:'MenuFont_ContentFontSize_20',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/contentFontSize_20'},
    {title:'MenuFont_ContentFontSize_30',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/contentFontSize_30'},
    {title:'MenuFont_LabelFontSize_10',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/labelFontSize_10'},
    {title:'MenuFont_LabelFontSize_20',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/labelFontSize_20'},
    {title:'MenuFont_LabelFontSize_30',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontSize/labelFontSize_30'},
    {title:'MenuFont_ContentFontWeight_Bold',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Bold'},
    {title:'MenuFont_ContentFontWeight_Bolder',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Bolder'},
    {title:'MenuFont_ContentFontWeight_Lighter',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Lighter'},
    {title:'MenuFont_ContentFontWeight_Medium',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Medium'},
    {title:'MenuFont_ContentFontWeight_Normal',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Normal'},
    {title:'MenuFont_ContentFontWeight_Regular',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/contentFontWeight_Regular'},
    {title:'MenuFont_LabelFontWeight_Bold',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Bold'},
    {title:'MenuFont_LabelFontWeight_Bolder',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Bolder'},
    {title:'MenuFont_LabelFontWeight_Lighter',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Lighter'},
    {title:'MenuFont_LabelFontWeight_Medium',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Medium'},
    {title:'MenuFont_LabelFontWeight_Normal',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Normal'},
    {title:'MenuFont_LabelFontWeight_Regular',utl:'pages/BindContextMenu/bindContextMenus/UIConsistency/MenuFont/FontWeight/labelFontWeight_Regular'},
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