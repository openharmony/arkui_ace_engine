import router from '@ohos.router';

interface ListCategories {
  title: string,
  url: string
}

@Entry
@Component
struct Index {
  @State message: string = 'Search'
  private items: ListCategories[] = [
    { title: '普通模式', url: 'pages/normal/normalIndex' },
    { title: '沙箱上下文模式', url: 'pages/sandbox/plugins' },
    { title: '普通+沙箱上下文模式', url: 'pages/mixed/plugins' },
  ]

  build() {
    Column() {
      List({ space: '10vp' }) {
        ForEach(this.items, (item: ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).onClick(() => {
              router.pushUrl({ url: item.url });
            })
          }.width('90%').height('80vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('100%')
    }.width('100%').height('100%')
  }
}