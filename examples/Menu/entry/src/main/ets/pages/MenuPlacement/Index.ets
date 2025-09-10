import router from '@ohos.router';

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct RotationIndex {
  @State message: string = 'test'

  private items : ListCategories[] = [
    { title: 'RightClick',url: 'pages/MenuPlacement/RightClick/Index' },
  ]

  build() {
    Column() {
      Text('bindContextMenu')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('80%').height(50).borderRadius(10).backgroundColor('#2ebd82')
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
          .onClick(() => {
            this.message = 'Page:' + item.url
            router.pushUrl({url:item.url})
          })
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('80%')
      Text(this.message).fontSize(20)
    }.width('100%').height('100%')
  }
}