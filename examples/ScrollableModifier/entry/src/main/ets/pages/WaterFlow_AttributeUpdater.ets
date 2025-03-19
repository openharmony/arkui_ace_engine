import { AttributeUpdater, WaterFlowModifier } from '@ohos.arkui.modifier'
import { WaterFlowDataSource } from './WaterFlowDataSource'

class MyWaterUpdater extends AttributeUpdater<WaterFlowModifier> {

  initializeModifier(instance: WaterFlowModifier): void {
    instance
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        console.info('waterFlow scrollFrameBegin offset: ' + offset + ' state: ' + state.toString())
        return { offsetRemain: offset }
      })
      .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource)=>{
        console.log('waterFlow onWillScroll scrollOffset: ' + scrollOffset + ' scrollState: ' + scrollState +
          ' scrollSource: ' + scrollState)
      })
      .onDidScroll((scrollOffset: number, scrollState: ScrollState)=>{
        console.log('waterFlow onDidScroll ' + scrollOffset + ' ' + scrollState)
      })
      .onReachStart(()=>{
        console.log('waterFlow onReachStart')
      })
      .onReachEnd(()=>{
        console.log('waterFlow onReachEnd')
      })
      .onScrollStart(()=>{
        console.log('waterFlow onScrollStart')
      })
      .onScrollStop(()=>{
        console.log('waterFlow onScrollStop')
      })
      .onScrollIndex((first: number, last: number) => {
        console.log('waterFlow onScrollIndex ' + first + ' ' + last)
      })
  }
}

@Entry
@Component
struct WaterFlowDemo_Updater {
  @State minSize: number = 80
  @State maxSize: number = 180
  @State fontSize: number = 24
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  scroller: Scroller = new Scroller()
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()
  private itemWidthArray: number[] = []
  private itemHeightArray: number[] = []
  @State gridUpdater: MyWaterUpdater = new MyWaterUpdater()

  // 计算FlowItem宽/高
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize)
    return (ret > this.minSize ? ret : this.minSize)
  }

  // 设置FlowItem的宽/高数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemWidthArray.push(this.getSize())
      this.itemHeightArray.push(this.getSize())
    }
  }

  aboutToAppear() {
    this.setItemSizeArray()
  }

  @Builder
  itemFoot() {
    Column() {
      Text(`Footer`)
        .fontSize(10)
        .backgroundColor(Color.Red)
        .width(50)
        .height(50)
        .align(Alignment.Center)
        .margin({ top: 2 })
    }
  }

  build() {
    Column({ space: 2 }) {
      WaterFlow() {
        LazyForEach(this.dataSource, (item: number) => {
          FlowItem() {
            Column() {
              Text('N' + item).fontSize(12).height('16')
              // 存在对应的jpg文件才会显示图片
              Image('res/waterFlowTest(' + item % 5 + ').jpg')
                .objectFit(ImageFit.Fill)
                .width('100%')
                .layoutWeight(1)
            }
          }
          .width('100%')
          .height(this.itemHeightArray[item % 100])
          .backgroundColor(this.colors[item % 5])
        }, (item: string) => item)
      }
      .attributeModifier(this.gridUpdater)
      .columnsTemplate('1fr 1fr')
      .columnsGap(10)
      .rowsGap(5)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100%')
    }
  }
}