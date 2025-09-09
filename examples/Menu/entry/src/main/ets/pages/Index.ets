import router from '@ohos.router';

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct RotationIndex {

  private items : ListCategories[] = [
    {title: 'Menu示例代码',url: 'pages/Examples/Index' },
    {title: 'Menu生命周期',url:'pages/LifeCycle/Index'},
    {title: 'Menu拖拽相关测试',url:'pages/Drag/Index'},
    {title: 'bindContextMenu菜单UX规格',url:'pages/BindContextMenu/Index'},
    {title: 'PreviewAnimation',url:'pages/PreviewAnimation/Index'},
    {title: 'Dock',url:'pages/Dock/Index'},
    {title: 'MenuUX',url:'pages/MenuUX/Index'},
    {title: 'MenuPlacement',url:'pages/MenuPlacement/Index'},
  ]

  build() {
    Column() {
      Text('Menu测试用例')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
          .onClick(() => {
            router.pushUrl({url:item.url})
          })
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('80%')
    }.width('100%').height('100%')
  }
}