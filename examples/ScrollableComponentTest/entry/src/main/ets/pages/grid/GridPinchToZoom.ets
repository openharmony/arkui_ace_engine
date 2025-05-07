import { WaterFlowDataSource } from '../scrollable/WaterFlowDataSource';

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
struct GridPinchDemo {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  @State columns: number = 2 // 默认列数
  @State itemScale: number = 1 // Pinch手势期间Item缩放比例
  @State gestureEnd: boolean = false // Pinch手势是否结束
  private pinchTime: number = 0 // 上次Pinch事件时间
  dataCount: number = 100
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()

  aboutToAppear() {
    // 读取上次的最终列数
    let lastCount: number | undefined = AppStorage.get('columnsCount')
    if (typeof lastCount != 'undefined') {
      this.columns = lastCount;
    }
  }

  build() {
    Column({ space: 2 }) {
      Row() {
        Text('双指缩放改变列数')
          .height('5%')
          .margin({ top: 10, left: 20 })
      }

      Grid() {
        LazyForEach(this.dataSource, (item: number) => {
          GridItem() {
            ReusableItem({ item: item })
          }
          .width('100%')
          .height(150)
          .backgroundColor(this.colors[item % 5])
          // Pinch手势期间修改itemScale产生缩放动画
          .scale({ x: this.itemScale, y: this.itemScale })
          .animation({
            duration: this.gestureEnd ? 350 : 500,
            curve: this.gestureEnd ? Curve.Friction : Curve.Smooth,
          })
        }, (item: string) => item)
      }
      .columnsTemplate('1fr '.repeat(this.columns))
      .columnsGap(10)
      .rowsGap(5)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100%')
      .layoutWeight(1)
      // 改变列数时隐式动画
      .animation({
        duration: 300,
        curve: Curve.Smooth
      })
      .priorityGesture(
        PinchGesture()
          .onActionStart((event: GestureEvent) => {
            this.gestureEnd = false
            this.pinchTime = event.timestamp
          })
          .onActionUpdate((event: GestureEvent) => {
            // 10ms以上再处理刷新
            if (event.timestamp - this.pinchTime < 10000000) {
              return;
            }
            this.pinchTime = event.timestamp
            if (event.scale > 1) {
              this.itemScale = 1.04
            } else {
              this.itemScale = 0.95
            }
          })
          .onActionEnd((event: GestureEvent) => {
            console.info('end scale:' + event.scale)
            this.gestureEnd = true
            this.itemScale = 1
            // 手指分开，减少列数以放大Item
            if (event.scale > 2) {
              this.columns--
            } else if (event.scale < 0.6) {
              this.columns++
            }
            // 可以根据设备屏幕宽度设定最大和最小列数，此处以最小1列最大4列为例
            this.columns = Math.min(4, Math.max(1, this.columns));
            AppStorage.setOrCreate<number>('columnsCount', this.columns)
          })
      )
    }
  }
}