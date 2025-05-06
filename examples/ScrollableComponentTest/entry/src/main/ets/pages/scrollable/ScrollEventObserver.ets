import { WaterFlowDataSource } from './WaterFlowDataSource';
import uiObserver from '@ohos.arkui.observer';

@Entry
@Component
struct ScrollEventObserverDemo {
  minSize: number = 80;
  maxSize: number = 180;
  fontSize: number = 24;
  colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  scroller: Scroller = new Scroller();
  dataSource: WaterFlowDataSource = new WaterFlowDataSource();
  private itemWidthArray: number[] = [];
  private itemHeightArray: number[] = [];
  scrollId: string = 'waterflow';
  @State scrollUniqueId: number = -1;
  @State scrollEvent: uiObserver.ScrollEventType = uiObserver.ScrollEventType.SCROLL_STOP;
  @State scrollOffset: number = 0;

  // 计算FlowItem宽/高
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem的宽/高数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemWidthArray.push(this.getSize());
      this.itemHeightArray.push(this.getSize());
    }
  }

  aboutToAppear() {
    this.setItemSizeArray();
  }

  onDidBuild(): void {
    // 通过UIContext获取对应的Observer
    let observer = this.getUIContext().getUIObserver();
    // 按id注册关心的滚动组件的滚动事件
    observer.on('scrollEvent', { id: this.scrollId }, (info: uiObserver.ScrollEventInfo) => {
      this.scrollId = info.id;
      this.scrollUniqueId = info.uniqueId;
      this.scrollEvent = info.scrollEvent;
      this.scrollOffset = info.offset;
      console.info(`scroll event, id: ${info.id}, uniqueId: ${info.uniqueId}, eventType: ${info.scrollEvent}, offset: ${info.offset}`);
    })
  }

  build() {
    Column({ space: 2 }) {
      Row({ space: 5 }) {
        Text(this.scrollId)
        Text(this.scrollUniqueId.toString())
        Text(this.scrollEvent.toString())
        Text(this.scrollOffset.toString())
      }

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
      .id(this.scrollId)
      .columnsTemplate('1fr 1fr')
      .columnsGap(10)
      .rowsGap(5)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100%')
      .onReachStart(() => {
        console.info('waterFlow reach start');
      })
      .onScrollStart(() => {
        console.info('waterFlow scroll start');
      })
      .onScrollStop(() => {
        console.info('waterFlow scroll stop');
      })
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        console.info('waterFlow scrollFrameBegin offset: ' + offset + ' state: ' + state.toString());
        return { offsetRemain: offset };
      })
    }
  }
}