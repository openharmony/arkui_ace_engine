class DemoGridItemInfo {
    public name: string;
    public icon: Resource;
  
    constructor(name: string, icon: Resource) {
      this.name = name;
      this.icon = icon;
    }
}
  
@Entry
@ComponentV2
struct DemoGrid {
    @Local itemList: Array<DemoGridItemInfo> = [];
    @Local isRefreshing: boolean = false;
    private layoutOptions: GridLayoutOptions = {
      regularSize: [1, 1],
      irregularIndexes: [10],
       onGetIrregularSizeByIndex: (index: number) => {
         return [2, 1]
       }
    }
    private gridScroller: Scroller = new Scroller();
    private num: number = 0;
    private flag: boolean = false;
    @Local repeatNum: number = 70;
  
    aboutToAppear(): void {
      for (let i = 0; i < 50; i++) {
        this.itemList.push(new DemoGridItemInfo('视频' + i,
          i % 3 == 0 ? $r('app.media.icon') :
            i % 3 == 1 ? $r('app.media.icon') : $r('app.media.icon')));
      }
    }
  
    build() {
      Column({ space: 10 }) {
        Text('Grid容器组件中包含Repeat组件')
          .fontSize(15)
          .fontColor(Color.Gray)
          Grid(this.gridScroller, this.layoutOptions) {
            Repeat<DemoGridItemInfo>(this.itemList)
            .each((obj: RepeatItem<DemoGridItemInfo>) => {
              if (obj.index === 10 ) {
                GridItem() {
                  Text('先前浏览至此，点击刷新')
                    .fontSize(20)
                }
                .height(30)
                .border({ width: 1 })
                .onClick(() => {
                  this.gridScroller.scrollToIndex(0);
                  this.isRefreshing = true;
                })
                .onAppear(() => {
                  console.info('AceTag', obj.item.name);
                })
              } else {
                GridItem() {
                  Column() {
                    Image(obj.item.icon)
                      .width('100%')
                      .height(80)
                      .objectFit(ImageFit.Cover)
                      .borderRadius({ topLeft: 16, topRight: 16 })
                    Text(obj.item.name)
                      .fontSize(15)
                      .height(20)
                  }
                }
                .height(100)
                .borderRadius(16)
                .backgroundColor(Color.White)
                .onAppear(() => {
                  console.info('AceTag', obj.item.name);
                })
              }
            })
            .key((item: DemoGridItemInfo) => item.name)
            .virtualScroll({ totalCount: 70 })
        }
        .onReachEnd(()=>{
          console.log('onReachEnd')
        })
        .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
           console.info('onDidScroll isAtEnd:' + this.gridScroller.isAtEnd())
        })
        .edgeEffect(EdgeEffect.Spring)
        .columnsTemplate('repeat(auto-fit, 150)')
        .cachedCount(4)
        .rowsGap(15)
        .columnsGap(10)
        .height('70%')
        .padding(10)
        .backgroundColor('#F1F3F5')
        Button('ScrollTo')
          .onClick(() => {
            this.itemList.splice(49, 1)
          })
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Center)
    }
}