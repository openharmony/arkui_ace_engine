import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct RotationIndex {
  @State message: string = 'test'

  private items : ListCategories[] = [
    { title: 'bindMenu', utl: 'pages/Dock/bindMenu' },
    { title: 'bindMenuBuilder', utl: 'pages/Dock/bindMenuBuilder' },
    { title: 'bindMenuBuilder noMenu', utl: 'pages/Dock/bindMenuBuiNoMenu' },
    { title: 'bindContextMenu', utl: 'pages/Dock/bindContextMenu' },
    { title: 'bindMenuSub', utl: 'pages/Dock/bindMenuSub' },
    { title: 'bindContextMenuSub', utl: 'pages/Dock/bindContextMenuSub' },
    { title: '横屏、竖屏空间均不足_bindMenu', utl: 'pages/Dock/bindMenuOut' },
    { title: '横屏、竖屏空间均不足_bindMenuBuilder', utl: 'pages/Dock/bindMenuBuilderOut' },
    { title: '横屏不足，竖屏充足_bindMenu', utl: 'pages/Dock/bindMenuHeight' },
    { title: '横屏不足，竖屏充足_bindMenuBuilder', utl: 'pages/Dock/bindMenuBuilderHei' },
    { title: '横屏不足，竖屏充足_bindContextMenu', utl: 'pages/Dock/bindContextMenuHei' },
    { title: '菜单高度80%_bindMenu', utl: 'pages/Dock/bindMenu1' },
    { title: '菜单高度80%_bindMenuBuilder', utl: 'pages/Dock/bindMenuBuilder1' },
    { title: '菜单高度80%_bindContextMenu', utl: 'pages/Dock/bindContextMenu1' },
    { title: 'menu内入参list组件', utl: 'pages/Dock/menuList' },
  ]

  build() {
    Column() {
      Text('PC上菜单高度满足UX效果')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('80%').height(50).borderRadius(10).backgroundColor('#2ebd82')
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
          .onClick(() => {
            this.message = 'Page:' + item.utl
            router.pushUrl({url:item.utl})
          })
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('80%')
      Text(this.message).fontSize(20)
    }.width('100%').height('100%')
  }
}