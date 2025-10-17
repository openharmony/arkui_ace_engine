@Entry
@Component
struct GridTwoItem {
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
      Grid(this.scroller) {
        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Yellow)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Orange)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Pink)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Green)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Blue)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Black)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Brown)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Gray)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Red)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Grey)
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Button()
        }
      }
      .friction(0.1)
      .width('100%')
      .height('80%')
      .columnsTemplate('10fr')
      .columnsGap(10)
      .rowsGap(20)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
    }
  }
}