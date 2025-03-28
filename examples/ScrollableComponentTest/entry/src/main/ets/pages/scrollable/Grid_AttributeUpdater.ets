import { LengthMetrics } from '@ohos.arkui.node'
import { ColorMetrics } from '@ohos.arkui.node'
import { AttributeUpdater, GridModifier } from '@ohos.arkui.modifier'

@Builder function  pixelMapBuilder() { //拖拽过程样式
  Column() {
    Text()
      .fontSize(16)
      .backgroundColor(0xF9CF93)
      .width(80)
      .height(80)
      .textAlign(TextAlign.Center)
  }
}

class MyGridUpdater extends AttributeUpdater<GridAttribute> {
  constructor(aaa:GridExample_Updater) {
    super()
    this.this_ = aaa
  }

  changeIndex(index1: number, index2: number) { //交换数组位置
    let temp: string;
    temp = this.this_.numbers[index1];
    this.this_.numbers[index1] = this.this_.numbers[index2];
    this.this_.numbers[index2] = temp;
  }
  private this_:GridExample_Updater
   initializeModifier(instance: GridModifier): void {
    instance
      .onScrollFrameBegin((offset: number, state: ScrollState)=>{
        console.log('GridBridge::onScrollFrameBegin offset: ' + offset + ' state: ' + state)
        return null
      })
      .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource)=>{
        console.log('GridBridge::onWillScroll scrollOffset: ' + scrollOffset + ' scrollState: ' + scrollState +
          ' scrollSource: ' + scrollState)
        return null
      })
      .onDidScroll((scrollOffset: number, scrollState: ScrollState)=>{
        console.log('GridBridge::onDidScroll ' + scrollOffset + ' ' + scrollState)
      })
      .onReachEnd(()=>{
        console.log('Grid onReachEnd')
      })
      .onScrollStart(()=>{
        console.log('Grid onScrollStart')
      })
      .onScrollStop(()=>{
        console.log('Grid onScrollStop')
      })
      .onScrollIndex((first: number, last: number) => {
        console.log('Grid onScrollIndex ' + first + ' ' + last)
      })
      .onScrollBarUpdate((index: number, offset: number) => {
        console.info('Grid onScrollBarUpdate,index : ' + index.toString() + ',offset' + offset.toString())
        return { totalOffset: (index / 5) * (80 + 10) - offset, totalLength: 80 * 5 + 10 * 4 }
      })
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
        console.info('DragStart x = ' + event.x + ' y = ' + event.y);
        return pixelMapBuilder.bind(this.this_)
      
      })
      .onItemDragEnter((event: ItemDragInfo) => { //第一次拖拽此事件绑定的组件时，触发回调。
        console.info('DragEnter x = ' + event.x + ' y = ' + event.y);
      })
      .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => {
        console.info('DragMove x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex + ' insertIndex = ' +
          insertIndex);
      })
      .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => {
        console.info('DragLeave x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex);
      })
      //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => { 
        // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
        if (!isSuccess) {
          return
        }
        //itemIndex拖拽起始位置，insertIndex拖拽插入位置
        console.info('ItemDrop ' + itemIndex + ' ', insertIndex + ' ' + isSuccess)
        this.changeIndex(itemIndex, insertIndex)
      })
  }
  public isReset: boolean = false

  applyNormalAttribute(instance: GridAttribute): void {
    instance.onScrollFrameBegin((offset: number, state: ScrollState)=>{
      console.log('GridBridge::onScrollFrameBegin offset: ' + offset + ' state: ' + state)
      return null
    })
    .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource)=>{
      console.log('GridBridge::onWillScroll scrollOffset: ' + scrollOffset + ' scrollState: ' + scrollState +
        ' scrollSource: ' + scrollState)
      return null
    })
    .onDidScroll((scrollOffset: number, scrollState: ScrollState)=>{
      console.log('GridBridge::onDidScroll ' + scrollOffset + ' ' + scrollState)
    })
    .onReachEnd(()=>{
      console.log('Grid onReachEnd')
    })
    .onScrollStart(()=>{
      console.log('Grid onScrollStart')
    })
    .onScrollStop(()=>{
      console.log('Grid onScrollStop')
    })
    .onScrollIndex((first: number, last: number) => {
      console.log('Grid onScrollIndex ' + first + ' ' + last)
    })
    .onScrollBarUpdate((index: number, offset: number) => {
      console.info('Grid onScrollBarUpdate,index : ' + index.toString() + ',offset' + offset.toString())
      return { totalOffset: (index / 5) * (80 + 10) - offset, totalLength: 80 * 5 + 10 * 4 }
    })
    .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
      console.info('DragStart x = ' + event.x + ' y = ' + event.y);
      return pixelMapBuilder.bind(this.this_)

    })
    .onItemDragEnter((event: ItemDragInfo) => { //第一次拖拽此事件绑定的组件时，触发回调。
      console.info('DragEnter x = ' + event.x + ' y = ' + event.y);
    })
    .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => {
      console.info('DragMove x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex + ' insertIndex = ' +
        insertIndex);
    })
    .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => {
      console.info('DragLeave x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex);
    })
    //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
    .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
      // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
      if (!isSuccess) {
        return
      }
      //itemIndex拖拽起始位置，insertIndex拖拽插入位置。
      console.info('ItemDrop ' + itemIndex + ' ', insertIndex + ' ' + isSuccess)
      this.changeIndex(itemIndex, insertIndex)
    })
  }
}




@Entry
@Component
export  struct  GridExample_Updater {
  @State numbers: string[] = []
  scroller: Scroller = new Scroller()
  scroller2: Scroller = new Scroller()
  @State text: string = 'drag'
  @State gridUpdater: MyGridUpdater = new MyGridUpdater(this)


  aboutToAppear() {
    for (let i = 1;i <= 15; i++) {
      this.numbers.push(i + '')
    }
  }

  @Builder pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text(this.text)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  changeIndex(index1: number, index2: number) { //交换数组位置
    let temp: string;
    temp = this.numbers[index1];
    this.numbers[index1] = this.numbers[index2];
    this.numbers[index2] = temp;
  }

  build() {
    Column({ space: 5 }) {
      Button('change flip')
        .onClick((event: ClickEvent) => {
          this.gridUpdater.isReset = !this.gridUpdater.isReset
        })
      Button('TEST')
        .onClick((event: ClickEvent) => {
          this.gridUpdater.attribute?.onScrollFrameBegin((offset: number, state: ScrollState)=>{
              console.log('GridBridge::onScrollFrameBegin offset: ' + offset + ' state: ' + state)
              return null
            })
            .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource)=>{
              console.log('GridBridge::onWillScroll scrollOffset: ' + scrollOffset + ' scrollState: ' + scrollState  + ' scrollSource: ' + scrollState)
              return null
            })
            .onDidScroll((scrollOffset: number, scrollState: ScrollState)=>{
              console.log('GridBridge::onDidScroll ' + scrollOffset + ' ' + scrollState)
            })
            .onReachStart(() => {
              console.log('Grid onReachStart')
            })
            .onReachEnd(() => {
              console.log('Grid onReachEnd')
            })
            .onScrollStart(() => {
              console.log('Grid onScrollStart')
            })
            .onScrollStop(() => {
              console.log('Grid onScrollStop')
            })
            .onScrollIndex((first: number, last: number) => {
              console.log('Grid onScrollIndex ' + first + ' ' + last)
            })
            .onScrollBarUpdate((index: number, offset: number) => {
              console.info('Grid onScrollBarUpdate,index : ' + index.toString() + ',offset' + offset.toString())
              return { totalOffset: (index / 5) * (80 + 10) - offset, totalLength: 80 * 5 + 10 * 4 }
            })
            .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
              this.text = this.numbers[itemIndex]
              console.info('DragStart x = ' + event.x + ' y = ' + event.y);
              return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
            })
            .onItemDragEnter((event: ItemDragInfo) => { //第一次拖拽此事件绑定的组件时，触发回调。
              console.info('DragEnter x = ' + event.x + ' y = ' + event.y);
            })
            .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => {
              console.info('DragMove x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex + ' insertIndex = ' + insertIndex);
            })
            .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => {
              console.info('DragLeave x = ' + event.x + ' y = ' + event.y + ' itemIndex = ' + itemIndex);
            })
            .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number,
              isSuccess: boolean) => { //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
              // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
              if (!isSuccess) {
                return
              }
              console.info('ItemDrop ' + itemIndex + ' ', insertIndex + ' ' + isSuccess) //itemIndex拖拽起始位置，insertIndex拖拽插入位置
              this.changeIndex(itemIndex, insertIndex)
            })
        })
      Grid(this.scroller) {

        ForEach(this.numbers, (day: string) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width(80)
              .height(80)
              .textAlign(TextAlign.Center)
          }
        })
      }
      .onReachStart(()=>{
        console.log('Grid onReachStart')
      })
      .attributeModifier(this.gridUpdater)
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
      .editMode(true) //设置Grid是否进入编辑模式，进入编辑模式可以拖拽Grid组件内部GridItem
      Grid(this.scroller2) {

        ForEach(this.numbers, (day: string) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width(80)
              .height(80)
              .textAlign(TextAlign.Center)
          }
        })
      }
      .onReachStart(()=>{
        console.log('Grid onReachStart')
      })
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
      .attributeModifier(this.gridUpdater)
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      .editMode(true) //设置Grid是否进入编辑模式，进入编辑模式可以拖拽Grid组件内部GridItem
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
        this.text = this.numbers[itemIndex]
        console.info('DragStart x = ' + event.x + ' y = ' + event.y);
        return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
      })
    }.width('100%').margin({ top: 5 })
  }
}
