@Entry
@Component
struct GridWidthOneItem {
  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '1000000px', '16777216px', undefined, null, -1800000000, 1000000
  ];
  scroller: Scroller = new Scroller;

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      Grid(this.scroller) {
        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(5000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Yellow)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Button()
        }
      }
      .friction(0.1)
      .height('80%')
      .rowsTemplate('1fr')
      .rowsGap(10)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
    }
  }
}

