import router from '@ohos.router';

interface ListCategories {
  title: string,
  utl: string
}

@Entry
@Component
struct IndexSR20240201979716 {
  private items: ListCategories[] = [
    { title: 'Text', utl: 'pages/32-Dev-2/Text' },
    { title: 'TextInput', utl: 'pages/32-Dev-2/TextInput' },
    { title: 'TextArea', utl: 'pages/32-Dev-2/TextArea' },
    { title: 'Search', utl: 'pages/32-Dev-2/Search' },
    { title: 'ImageSpan', utl: 'pages/32-Dev-2/ImageSpan' },
  ]

  build() {
    Column() {
      List({ space: '10vp' }) {
        ForEach(this.items, (item: ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).onClick(() => {
              router.pushUrl({ url: item.utl })
            })
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('90%')
    }.width('100%').height('100%')
  }
}