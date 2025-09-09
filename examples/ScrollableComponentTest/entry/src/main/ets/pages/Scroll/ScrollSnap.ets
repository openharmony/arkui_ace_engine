import { LengthMetrics, ScrollModifier } from '@kit.ArkUI';
import { common, ConfigurationConstant } from '@kit.AbilityKit';

@Entry
@Component
struct NestedScroll1 {
  @State listPosition: number = 0; // 0代表滚动到List顶部，1代表中间值，2代表滚动到List底部。
  private arr: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18];
  private scrollerForScroll: Scroller = new Scroller();
  private scrollerForList: Scroller = new Scroller();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State changeIndex: number = 0;
  @State changeList: (number | Resource | undefined | null)[] = [
    200, 330, undefined, 200, null,
    200, 60, 200, -900
  ];
  scroller: Scroller = new Scroller;

  build() {
    Scroll(this.scroller) {

      Column() {
        Column() {
          Button('切换数值')
            .onClick(() => {
              this.changeIndex++;
              if (this.changeIndex > this.changeList.length - 1) {
                this.changeIndex = 0;
              }
            })
          Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
        }

        ForEach(this.arr, (item: number) => {
          Text(item.toString())
            .width('90%')
            .height(200)
            .backgroundColor(0xFFFFFF)
            .borderWidth(1)
            .borderColor(Color.Black)
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
        }, (item: string) => item)
      }.width('100%').backgroundColor(0xDCDCDC)
    }
    .backgroundColor(Color.Yellow)
    .height('100%')
    .edgeEffect(EdgeEffect.Spring)
    .scrollSnap({
      snapAlign: ScrollSnapAlign.START,
      snapPagination: this.changeList[this.changeIndex],
      enableSnapToStart: true,
      enableSnapToEnd: true
    })
  }
}
