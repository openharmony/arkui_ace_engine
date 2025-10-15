@Entry
@Component
struct ScrollWidthTwoItem {
  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '9999500px', '1100000px', '16776716px', undefined, null, -1800000000, 1000000
  ];
  scroller: Scroller = new Scroller;

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++;
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      Scroll(this.scroller) {
        Row() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Yellow)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Orange)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Green)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Gray)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Green)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Red)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Brown)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Black)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Blue)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Grey)

          Column() {
            Button()
          }
        }
      }
      .height(400)
      .scrollable(ScrollDirection.FREE)
      .minZoomScale(1)
      .maxZoomScale(2)
      .enableBouncesZoom(true)
    }
  }
}