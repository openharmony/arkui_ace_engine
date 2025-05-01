import { ItemsPageView } from './ItemsPageView';

@Entry
@Component
struct ListGridDemo {
  @State curIndex: number = 0;
  @State tabItem:Array<string> =
    ['全部', '咨询', '医生', '经络', '膳食', '茶饮', '运动', '足浴']

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontSize(this.curIndex === index ? 20 : 16)
        .fontColor(Color.White)
        .fontWeight(this.curIndex === index ? FontWeight.Bold : FontWeight.Normal)
        .id(index.toString())
        .margin({ bottom: 10 })

      if (this.curIndex === index) {
        Text()
          .width(16)
          .borderRadius(5)
          .backgroundColor(Color.White)
          .height(5)
      }
    }
    .margin({ left: 10, right: 10 })
    .width(this.curIndex === index ? name.length * 20 : name.length * 16)
    .alignItems(HorizontalAlign.Center)
    .justifyContent(FlexAlign.Center)
    .height(56)
  }

  build() {
    Column(){
      Stack({ alignContent: Alignment.TopStart }) {
        Image('')
          .backgroundColor('#29a493')
          .width('100%').height((AppStorage.get('statusHeight')!))
        Column(){
          Tabs({ index: this.curIndex, }) {
            ForEach(this.tabItem, (item: string, index: number) => {
              TabContent() {
                Scroll() {
                  Column() {
                    ItemsPageView({ tabBarIndex: this.curIndex })
                  }
                }
              }
              .tabBar(this.tabBuilder(index, item))
            })
          }
          .onTabBarClick((index: number) => {
            this.curIndex = index;
          })
          .onChange((index: number) => {
            this.curIndex = index;
          })
          .layoutWeight(1)
          .barOverlap(false)
          .barMode(BarMode.Scrollable)
          .barHeight(56)
        }

      }
      .height('100%')
      .width('100%')
    }
  }
}
