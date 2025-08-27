@ComponentV2({freezeWhenInactive: true})
export struct V2ChildComponent {
  @Param @Require message: string
  @Param @Require img: Resource
  @Param @Require bgcolor:Color

  @Monitor( 'bgcolor')
  onMessageChange(monitor: IMonitor) {
    monitor.dirty.forEach((path: string) => {
      console.log(`${path} changed from ${monitor.value(path)?.before} to ${monitor.value(path)?.now} for ${this.message}`)
    })
  }

  build() {
    Row({space: 8}) {
      Text(`[a]: ${this.message}`)
        .fontSize(25)
        .backgroundColor(this.bgcolor)
      Image(this.img)
        .width(40)
        .height(40)
    }
    .alignItems(VerticalAlign.Top)
    .justifyContent(FlexAlign.Start)
  }
}
@ObservedV2
export class Data1396 {
  @Trace public message: string = '';
  @Trace public img: Resource = $r('app.media.icon')
  @Trace public bgColor:Color = Color.Blue

  constructor(message: string, img: Resource, bgColor:Color) {
    this.message = message
    this.img = img
    this.bgColor = bgColor
  }
}
@ComponentV2
export struct ListRepeatChildComponent {
  @Param @Require simpleList: Array<Data1396>
  @Param @Require img:Resource
  @Param @Require bgcolor:Color
  build() {
    WaterFlow() {
      Repeat<Data1396>(this.simpleList)
        .each((obj: RepeatItem<Data1396>) => {
        })
        .key((item: Data1396, index: number) => {
          return item.message;
        })
        .virtualScroll({ totalCount: this.simpleList.length })
        .templateId(() => 'a')
        .template('a', (ri) => {
          FlowItem() {
            V2ChildComponent({
              message: ri.item.message,
              img: this.img,
              bgcolor: this.bgcolor
            })
          }
        }, { cachedCount: 2 })
    }
    .layoutWeight(1)
    .cachedCount(1)
    .width('100%')
    .height('90%')
  }
}

@Entry
@ComponentV2
export struct ListPage {
  @Local simpleList: Array<Data1396> = [];
  private counter: number = 0;
  @Local isHidden: boolean = false
  @Local img:Resource = $r('app.media.icon')
  @Local bgcolor:Color = Color.Blue
  aboutToAppear(): void {
    for (let i = 0; i < 21; i++) {
      this.simpleList.push(new Data1396(`item_${i}`, $r('app.media.icon'), Color.Blue));
      this.counter++;
    }
  }

  build() {
    Scroll() {
      Column({ space: 10 }) {
        ListRepeatChildComponent({simpleList: this.simpleList, img:this.img, bgcolor:this.bgcolor})
            .visibility(this.isHidden ? Visibility.Hidden : Visibility.Visible)
      }
    }
  }
}