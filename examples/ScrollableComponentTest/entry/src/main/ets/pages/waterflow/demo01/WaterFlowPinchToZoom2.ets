import { WaterFlowDataSource } from './WaterFlowDataSource';
import { image } from '@kit.ImageKit';

@Reusable
@Component
struct ReusableItem {
  @State item: number = 0

  // 从复用缓存中加入到组件树之前调用，可在此处更新组件的状态变量以展示正确的内容
  aboutToReuse(params: Record<string, number>) {
    this.item = params.item;
    console.info('Reuse item:' + this.item)
  }

  aboutToAppear() {
    console.info('item:' + this.item)
  }

  build() {
    Column() {
      Text('N' + this.item).fontSize(12).height('16')
      Image('res/waterFlow(' + this.item % 5 + ').JPG')
        .objectFit(ImageFit.Fill)
        .width('100%')
        .layoutWeight(1)
    }
  }
}

@Entry
@Component
struct WaterFlowDemo {
  @State minSize: number = 80
  @State maxSize: number = 180
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  @State columns: number = 4 // 默认列数
  @State itemScale: number = 1 // Pinch手势期间Item缩放比例
  @State imageScale: number = 1 // Pinch手势期间Item缩放比例
  @State itemOpacity: number = 1
  @State gestureEnd: boolean = false // Pinch手势是否结束
  private pinchTime: number = 0 // 上次Pinch事件时间
  dataCount: number = 100
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()
  private itemWidthArray: number[] = []
  private itemHeightArray: number[] = []
  @State pixmap: image.PixelMap | undefined = undefined
  private columnChanged: boolean = false
  private oldColumn: number = this.columns

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
    // 读取上次的最终列数
    let lastCount = AppStorage.get<number>('columnsCount')
    if (typeof lastCount != 'undefined') {
      this.columns = lastCount
    }
    this.setItemSizeArray()
  }

  changeColumns(scale: number) {
    this.oldColumn = this.columns
    if (scale > (this.columns / (this.columns - 0.5))) {
      this.columns--
      this.columnChanged = true
    } else if (scale < 1 && this.columns < 4) {
      this.columns++
      this.columnChanged = true
    }
    // 可以根据设备屏幕宽度设定最大和最小列数，此处以最小1列最大4列为例
    this.columns = Math.min(4, Math.max(1, this.columns));
  }

  build() {
    Column({ space: 2 }) {
      Row() {
        Text('双指缩放改变列数')
          .height('5%')
          .margin({ top: 10, left: 20 })
      }

      Stack() {
        // 叠加图片组件
        Image(this.pixmap).width('100%').height('100%')
          .scale({
            x: this.imageScale,
            y: this.imageScale,
            centerX: 0,
            centerY: 0
          })

        WaterFlow() {
          LazyForEach(this.dataSource, (item: number) => {
            FlowItem() {
              ReusableItem({ item: item })
            }
            .width('100%')
            .aspectRatio(this.itemHeightArray[item % 100] / this.itemWidthArray[item % 100])
            .backgroundColor(this.colors[item % 5])
          }, (item: string) => item)
        }
        .id('waterflow')
        .columnsTemplate('1fr '.repeat(this.columns))
        .backgroundColor(0xFAEEE0)
        .width('100%')
        .height('100%')
        .layoutWeight(1)
        .opacity(this.itemOpacity)
        .scale({
          x: this.itemScale,
          y: this.itemScale,
          centerX: 0,
          centerY: 0
        })
        .priorityGesture(
          PinchGesture()
            .onActionStart((event: GestureEvent) => {
              this.gestureEnd = false
              this.pinchTime = event.timestamp
              this.columnChanged = false
              // 图片组件显示缩放前截图
              this.getUIContext().getComponentSnapshot().get('waterflow', (error: Error, pixmap: image.PixelMap) => {
                if (error) {
                  console.log('error: ' + JSON.stringify(error))
                  return;
                }
                this.pixmap = pixmap
              })
            })
            .onActionUpdate((event: GestureEvent) => {
              // 10ms以上再处理刷新
              if (event.timestamp - this.pinchTime < 10000000) {
                return;
              }
              this.pinchTime = event.timestamp

              let maxScale = this.oldColumn / (this.oldColumn - 1)
              this.itemScale = event.scale > maxScale ? maxScale : event.scale
              this.imageScale = event.scale > maxScale ? maxScale : event.scale
              this.itemOpacity = (this.itemScale > 1) ? (this.itemScale - 1) : (1 - this.itemScale)
              this.itemOpacity *= 3
              if (!this.columnChanged) {
                // WaterFlow按切换后列数布局
                this.changeColumns(event.scale)
              }
              // 控制缩放比例，不要留白或过大
              if (this.columnChanged) {
                this.itemScale = this.imageScale * this.columns / this.oldColumn
                if (event.scale < 1) {
                  this.itemScale = this.itemScale > 1 ? this.itemScale : 1
                } else {
                  this.itemScale = this.itemScale < 1 ? this.itemScale : 1
                }
              }
            })
            .onActionEnd((event: GestureEvent) => {
              this.gestureEnd = true
              // 离手回到正常布局
              animateTo({ duration: 300 }, () => {
                this.itemScale = 1
                this.itemOpacity = 1
              })
              AppStorage.setOrCreate<number>('columnsCount', this.columns)
            })
        )
      }.width('100%')
      .height('100%')
    }
  }
}