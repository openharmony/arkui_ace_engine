import { LengthMetrics } from '@kit.ArkUI';
import { MyDataSource } from './BasicDataSource';
import { WaterFlowDataSource } from './WaterFlowDataSource';


// xxx.ets
class MyModifier implements AttributeModifier<LazyVGridLayoutAttribute> {
  public rowsGap: number = 5;
  public columnsGap: number = 5;
  public template: string = '1fr 1fr';

  applyNormalAttribute(instance: LazyVGridLayoutAttribute): void {
    instance
      .rowsGap(LengthMetrics.vp(this.rowsGap))
      .columnsGap(LengthMetrics.vp(this.columnsGap))
      .columnsTemplate(this.template)
  }
}

@Component
struct MyGrid {
  @Prop columnsGap: number = 0;
  @Prop rowsGap: number = 0;
  @Prop template: string = '1fr 2fr';
  arr: MyDataSource = new MyDataSource();

  aboutToAppear(): void {
    for (let i = 0; i < 50; i++) {
      this.arr.pushData(i.toString());
    }
  }

  build() {
    LazyVGridLayout() {
      LazyForEach(this.arr, (item: string) => {
        Text('Item' + item)
          .height(64)
          .borderColor(Color.Black)
          .width('100%')
          .borderWidth(1)
          .onAppear(() => {
            console.log('YYL:onAppear:' + item)
          })
          .onDisAppear(() => {
            console.log('YYL:onDisAppear:' + item)
          })
      })
    }
    .rowsGap(LengthMetrics.vp(this.rowsGap))
    .columnsGap(LengthMetrics.vp(this.columnsGap))
    .columnsTemplate(this.template)
  }
}

@Entry
@Component
struct ListItemExample {
  arr: MyDataSource = new MyDataSource();
  @State rowsGap: number = 0;
  @State columnsGap: number = 0;
  @State template: string = '1fr';
  @State modifier: MyModifier = new MyModifier();
  @State isClip: boolean = true;
  dataSource: WaterFlowDataSource = new WaterFlowDataSource(15);
  dataCount: number = this.dataSource.totalCount();
  @State section: WaterFlowSections = new WaterFlowSections();
  scroller: Scroller = new Scroller();
  @State h: number = 36;
  @State ani: boolean = false;
  @State num: number = 0;
  oneColumnSection: SectionOptions = {
    itemsCount: 9,
    crossCount: 3,
    columnsGap: '5vp',
    rowsGap: 10,
    margin: {
      top: 100,
      left: 5,
      bottom: 10,
      right: 5
    }

  }
  twoColumnSection: SectionOptions = {
    itemsCount: 4,
    crossCount: 2,
    columnsGap: 5,
    rowsGap: 5,
    margin: { bottom: 10 }
  }
  lastSection: SectionOptions = {
    itemsCount: 2,
    crossCount: 1,
    margin: { bottom: 20 }
  }
  gridSection: SectionOptions = {
    itemsCount: 1,
    crossCount: 1,
  }

  aboutToAppear() {
    // 初始化瀑布流分组信息
    let sectionOptions: SectionOptions[] = [];
    sectionOptions.push(this.gridSection);
    sectionOptions.push(this.oneColumnSection);
    sectionOptions.push(this.twoColumnSection);
    sectionOptions.push(this.lastSection);
    sectionOptions.push(this.gridSection);
    this.section.splice(0, 0, sectionOptions);
    for (let i = 0; i < 40; i++) {
      this.arr.pushData(i.toString());
    }
  }

  build() {
    Column() {
      Scroll() {
        Flex({ wrap: FlexWrap.Wrap }) {
          Button('1列').onClick(() => {
            this.template = '1fr'
            this.modifier.template = '1fr'
          })
          Button('2列').onClick(() => {
            this.template = '1fr 1fr'
            this.modifier.template = '1fr 1fr'
          })
          Button('3列').onClick(() => {
            this.template = '1fr 1fr 1fr'
            this.modifier.template = '1fr 1fr 1fr'
          })
          Button('2列不等宽').onClick(() => {
            this.template = '2fr 3fr'
            this.modifier.template = '2fr 3fr'
          })
          Button('行Gap+').onClick(() => {
            this.rowsGap = this.rowsGap + 2
            this.modifier.rowsGap = this.rowsGap
          })
          Text(this.rowsGap.toString())
          Button('行Gap-').onClick(() => {
            if (this.rowsGap > -2) {
              this.rowsGap = this.rowsGap - 2
              this.modifier.rowsGap = this.rowsGap
            }
          })
          Button('列Gap+').onClick(() => {
            this.columnsGap = this.columnsGap + 2
            this.modifier.columnsGap = this.columnsGap
          })
          Text(this.columnsGap.toString())
          Button('列Gap-').onClick(() => {
            if (this.columnsGap > -2) {
              this.columnsGap = this.columnsGap - 2
              this.modifier.columnsGap = this.columnsGap
            }
          })
          Button('clip').onClick(() => {
            this.isClip = !this.isClip
          })
          Button('跳转动画' + this.ani).onClick(() => {
            this.ani = !this.ani;
          })
          Button('scrolltoindex 10').onClick(() => {
            this.scroller.scrollToIndex(10, this.ani)
          })
          Button('scrolltoindex 0').onClick(() => {
            this.scroller.scrollToIndex(0, this.ani)
          })
          Button('scrolltoindex 15').onClick(() => {
            this.scroller.scrollToIndex(16, this.ani)
          })
          Button('删除第一个').onClick(() => {
            this.arr.shiftData();
          })
          Button('删除最后个').onClick(() => {
            this.arr.popData();
          })
          Button('头插1个').onClick(() => {
            this.arr.unshiftData(this.arr.firstPrevData());
          })
          Button('追加1个').onClick(() => {
            this.arr.pushData(this.arr.lastNextData());
          })
          Button('删除全部').onClick(() => {
            this.arr.clearData();
          })
          Button('追加100').onClick(() => {
            this.arr.appendData(100);
          })
          Button('1个Item').onClick(() => {
            this.arr.clearData();
            this.arr.appendData(1);
          })
          Button('text高度+10').onClick(() => {
            this.h += 10
          })
          Button('text高度-10').onClick(() => {
            this.h -= 10
          })
          Button('默认').onClick((event: ClickEvent) => {
            this.num = 0
          })
          Button('滑窗').onClick((event: ClickEvent) => {
            this.num = 1
          })
        }
      }.height('200')

      Stack() {
        WaterFlow({ scroller: this.scroller, sections: this.section, layoutMode: this.num }) {

          FlowItem() {
            LazyVGridLayout() {
              LazyForEach(this.arr, (item: string) => {
                Text('Item' + item)
                  .height(this.h)
                  .onAppear(() => {
                    console.log('YYL:onAppear:' + item)
                  })
                  .onDisAppear(() => {
                    console.log('YYL:onDisAppear:' + item)
                  })
                  .borderColor(Color.Black)
                  .width('100%')
                  .borderWidth(1)
              })
            }
            .backgroundColor(Color.Brown)
            .attributeModifier(this.modifier)
          }

          LazyForEach(this.dataSource, (item: number) => {
            FlowItem() {
              Text('abc')
            }.backgroundColor(Color.Gray)
            .height(100)
            .width('100%')
          }, (item: string) => item + Math.random())

          FlowItem() {
            LazyVGridLayout() {
              LazyForEach(this.arr, (item: string) => {
                Text('Item' + item)
                  .height(this.h)
                  .onAppear(() => {
                    console.log('YYL:onAppear:' + item)
                  })
                  .onDisAppear(() => {
                    console.log('YYL:onDisAppear:' + item)
                  })
                  .borderColor(Color.Black)
                  .width('100%')
                  .borderWidth(1)
              })
            }
            .backgroundColor(Color.Green)
            .attributeModifier(this.modifier)
          }
        }
        .rowsGap(20)
        .width('90%')
        .height(this.isClip ? '100%' : '40%')
        .clip(this.isClip)
        .scrollBar(BarState.On)
        .edgeEffect(EdgeEffect.Spring)
        .backgroundColor(Color.Pink)
      }
      .clip(true)
      .layoutWeight(1)
    }.width('100%').height('100%')
  }
}