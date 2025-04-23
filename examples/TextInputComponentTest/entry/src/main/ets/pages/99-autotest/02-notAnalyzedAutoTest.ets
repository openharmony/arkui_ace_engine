import router from '@ohos.router';

export interface PageParam {
  title: string;
  url: string;
  key: string;
}

const testList: PageParam[] = [
  { title: '1', url: '1', key: '1' },
]

@Entry
@Component
struct NotAdapterAutoTest {
  @State message: string = '未分析能否适配'

  build() {
    Column() {
      Text(this.message)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Scroll() {
        List({ space: 5 }) {
          ForEach(testList, (item: PageParam) => {
            ListItem() {
              Button(item.title)
                .width('100%')
                .fontSize(20)
                .key(item.key)
                .clip(false)
                .onClick(() => {
                  router.pushUrl({
                    url: item.url
                  }, router.RouterMode.Single)
                })
            }
          }, (item: PageParam) => item.title)
        }
      }
    }
    .height('100%')
  }
}