@Entry
@Component
struct ListItemMoveWidth {
  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '9999500px', '1100000px', '16776716px', undefined, null, -1800000000, 1000000
  ];
  @State _Direction: Direction = Direction.Ltr;
  @State chain: boolean = false;
  @State direction_list: Axis = Axis.Vertical;
  @State alignListItem: ListItemAlign = ListItemAlign.Start;
  @State open_scroll: boolean = true;
  listScroller: Scroller = new Scroller();
  @State arr: string[] = [];
  @State press3: number = 0;
  @State drop3: number = 0;
  @State start3: number = 0;
  @State from3: number = 0;
  @State to3: number = 0;

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.arr.push(i.toString());
    }
  }

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
      List({ space: 10, scroller: this.listScroller }) {
        ForEach(this.arr, (item3: number, index3: number) => {
          ListItem() {
            Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
              Column() {
                Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
              }
              .borderRadius(1000)
              .borderColor(Color.Black)
              .width(this.changeList[this.changeIndex]) //TODO 疑问：子组件像素是否需要width也设置
              .backgroundColor(Color.Yellow)
              .height('80%')
            }
          }
        }, (item: string) => item)
          .onMove((from1: number, to1: number) => {
            let temp = this.arr.splice(from1, 1);
            this.arr.splice(to1, 0, temp[0]);
          },
            {
              onLongPress: (index: number) => {
                this.press3 = index;
              },
              onDrop: (index: number) => {
                this.drop3 = index;
              },
              onDragStart: (index: number) => {
                this.start3 = index;
              },
              onMoveThrough: (from: number, Through: number) => {
                this.from3 = from;
                this.to3 = Through;
              }
            }
          )
      }
      .chainAnimation(true)
      .edgeEffect(EdgeEffect.Spring)
      .listDirection(Axis.Horizontal)
      .height('80%')
      .width('100%')
      .borderRadius(10)
      .backgroundColor(0xDCDCDC)
      .height('80%')
    }
  }
}