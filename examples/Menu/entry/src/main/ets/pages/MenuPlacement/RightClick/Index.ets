import router from '@ohos.router';

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct PinchIndex {
  @State message: string = 'test'

  private items : ListCategories[] = [
    {title:'Right_100vp', url:'pages/MenuPlacement/RightClick/RightWidth'},
    {title:'Right_48vp', url:'pages/MenuPlacement/RightClick/RightWidth1'},
    {title:'Right_64vp', url:'pages/MenuPlacement/RightClick/RightWidth2'},
    {title:'Right_noWidth', url:'pages/MenuPlacement/RightClick/RightWidth3'},
    {title:'Top_100vp', url:'pages/MenuPlacement/RightClick/TopWidth'},
    {title:'Top_48vp', url:'pages/MenuPlacement/RightClick/TopWidth1'},
    {title:'Top_64vp', url:'pages/MenuPlacement/RightClick/TopWidth2'},
    {title:'Top_noWidth', url:'pages/MenuPlacement/RightClick/TopWidth3'},
    {title:'Bottom_100vp', url:'pages/MenuPlacement/RightClick/BottomWidth'},
    {title:'Bottom_48vp', url:'pages/MenuPlacement/RightClick/BottomWidth1'},
    {title:'Bottom_64vp', url:'pages/MenuPlacement/RightClick/BottomWidth2'},
    {title:'Bottom_noWidth', url:'pages/MenuPlacement/RightClick/BottomWidth3'},
    {title:'TopLeft_100vp', url:'pages/MenuPlacement/RightClick/TopLeftWidth'},
    {title:'TopLeft_48vp', url:'pages/MenuPlacement/RightClick/TopLeftWidth1'},
    {title:'TopLeft_64vp', url:'pages/MenuPlacement/RightClick/TopLeftWidth2'},
    {title:'TopLeft_noWidth', url:'pages/MenuPlacement/RightClick/TopLeftWidth3'},
    {title:'TopRight_100vp', url:'pages/MenuPlacement/RightClick/TopRightWidth'},
    {title:'TopRight_48vp', url:'pages/MenuPlacement/RightClick/TopRightWidth1'},
    {title:'TopRight_64vp', url:'pages/MenuPlacement/RightClick/TopRightWidth2'},
    {title:'TopRight_noWidth', url:'pages/MenuPlacement/RightClick/TopRightWidth3'},
    {title:'BottomLeft_100vp', url:'pages/MenuPlacement/RightClick/BottomLeftWidth'},
    {title:'BottomLeft_48vp', url:'pages/MenuPlacement/RightClick/BottomLeftWidth1'},
    {title:'BottomLeft_64vp', url:'pages/MenuPlacement/RightClick/BottomLeftWidth2'},
    {title:'BottomLeft_noWidth', url:'pages/MenuPlacement/RightClick/BottomLeftWidth3'},
    {title:'BottomRight_100vp', url:'pages/MenuPlacement/RightClick/BottomRightWidth'},
    {title:'BottomRight_48vp', url:'pages/MenuPlacement/RightClick/BottomRightWidth1'},
    {title:'BottomRight_64vp', url:'pages/MenuPlacement/RightClick/BottomRightWidth2'},
    {title:'BottomRight_noWidth', url:'pages/MenuPlacement/RightClick/BottomRightWidth3'},
    {title:'RightTop_100vp', url:'pages/MenuPlacement/RightClick/RightTopWidth'},
    {title:'RightTop_48vp', url:'pages/MenuPlacement/RightClick/RightTopWidth1'},
    {title:'RightTop_64vp', url:'pages/MenuPlacement/RightClick/RightTopWidth2'},
    {title:'RightTop_noWidth', url:'pages/MenuPlacement/RightClick/RightTopWidth3'},
    {title:'RightBottom_100vp', url:'pages/MenuPlacement/RightClick/RightBottomWidth'},
    {title:'RightBottom_48vp', url:'pages/MenuPlacement/RightClick/RightBottomWidth1'},
    {title:'RightBottom_64vp', url:'pages/MenuPlacement/RightClick/RightBottomWidth2'},
    {title:'RightBottom_noWidth', url:'pages/MenuPlacement/RightClick/RightBottomWidth3'},
    {title:'NoPlace_100vp', url:'pages/MenuPlacement/RightClick/noPlacement'},
    {title:'NoPlace_48vp', url:'pages/MenuPlacement/RightClick/noPlacement1'},
    {title:'NoPlace_64vp', url:'pages/MenuPlacement/RightClick/noPlacement2'},
    {title:'NoPlace_noWidth', url:'pages/MenuPlacement/RightClick/noPlacement3'},
    {title:'width20%_height50%', url:'pages/MenuPlacement/RightClick/menuWidth'},
    {title:'width30%_height70%', url:'pages/MenuPlacement/RightClick/menuWidth1'},
    {title:'width30%', url:'pages/MenuPlacement/RightClick/menuWidth2'},
  ]

  build() {
    Column() {
      Text('鼠标右击，弹出菜单').fontSize(22)
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