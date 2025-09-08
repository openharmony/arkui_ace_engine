import { common, ConfigurationConstant } from '@kit.AbilityKit';

@Entry
@Component
struct NestedScroll1 {
  @State listPosition: number = 0; // 0代表滚动到List顶部，1代表中间值，2代表滚动到List底部。
  private arr: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20];
  private scrollerForScroll: Scroller = new Scroller();
  private scrollerForList: Scroller = new Scroller();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State changeIndex: number = 0;
  @State changeList: (number | Resource | undefined | null)[] = [
    99, 11, 0.9, 99, undefined,
    99, null, 11, 0.1, 99, -99
  ];
  scroller: Scroller = new Scroller();

  build() {
    Stack({ alignContent: Alignment.TopStart }) {

      Scroll(this.scroller) {
        Column() {
          ForEach(this.arr, (item: number) => {
            Text(item.toString())
              .width('90%')
              .height(150)
              .backgroundColor(0xFFFFFF)
              .borderRadius(15)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .margin({ top: 10 })
          }, (item: string) => item)
        }.width('100%')
      }
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollBar(BarState.On) // 滚动条常驻显示
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(10) // 滚动条宽度
      .friction(this.changeList[this.changeIndex])
      .edgeEffect(EdgeEffect.None)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        console.info(xOffset + ' ' + yOffset);
      })
      .onScrollEdge((side: Edge) => {
        console.info('To the edge');
      })
      .onScrollStop(() => {
        console.info('Scroll Stop');
      })

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
    }.width('100%').height('100%').backgroundColor(0xDCDCDC)
  }
}
