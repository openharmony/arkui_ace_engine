import { vibrator } from '@kit.SensorServiceKit';
import { BusinessError } from '@kit.BasicServicesKit';

@Entry
@Component
struct TestDrag {
  @State items: number[] = [1, 2, 3, 4, 5];
  @State draggingIndex: number | undefined = undefined;
  scroller: Scroller = new Scroller();

  build() {
    Grid(this.scroller) {
      ForEach(this.items, (item: number, index) => {
        GridItem() {
          this.itemBuilder(item)
        }
        .visibility(this.draggingIndex == index ? Visibility.Hidden : Visibility.Visible)
      })
    }
    // 绑定同时触发的手势
    .parallelGesture(
      LongPressGesture({ repeat: false })
        .onAction((event: GestureEvent) => {
          if (event) {
            // 没按在任何item上，不做处理
            if (this.scroller.getItemIndex(event.fingerList[0].localX, event.fingerList[0].localY) < 0) {
              return;
            }
            // 长按振动
            try {
              vibrator.startVibration({
                type: 'preset',
                effectId: 'haptic.notice.success',
                count: 1,
              }, {
                usage: 'notification' // 根据实际选择类型归属不同的开关管控
              }, (error: BusinessError) => {
                if (error) {
                  console.error(`Failed to start vibration. Code: ${error.code}, message: ${error.message}`);
                  return;
                }
                console.info('Succeed in starting vibration');
              });
            } catch (err) {
              let e: BusinessError = err as BusinessError;
              console.error(`An unexpected error occurred. Code: ${e.code}, message: ${e.message}`);
            }
          }
        })
    )
    .columnsTemplate('1fr')
    .editMode(true)
    .supportAnimation(true)
    .width('100%')
    .height('100%')
    .onItemDragStart((_, index) => {
      this.draggingIndex = index;
      const point = this.items[index];
      return this.itemBuilder(point, true);
    })
    .onItemDrop((_, sourceIndex, insertIndex, isSuccess) => {
      if (isSuccess && insertIndex < this.items.length) {
        const point = this.items[sourceIndex];
        this.items[sourceIndex] = this.items[insertIndex];
        this.items[insertIndex] = point;
      }
      this.draggingIndex = undefined;
    })
  }

  @Builder
  itemBuilder(item: number, isDragging: boolean = false) {
    // 内层Row的shadow需要画在父组件范围，没有这一层节点则无处绘制
    Row() {
      Row() {
        Text('序号：' + item)
          .fontSize(16)
        Text('可长按拖拽')
          .fontSize(16)
      }
      .justifyContent(FlexAlign.SpaceBetween)
      // 通过margin给阴影留出绘制空间，不能使用padding
      .margin({ left: 16, right: 16 })
      .height(60)
      .width('90%')
      .backgroundColor(Color.White)
      .shadow(isDragging ? ShadowStyle.OUTER_DEFAULT_LG : undefined)
    }
  }
}
