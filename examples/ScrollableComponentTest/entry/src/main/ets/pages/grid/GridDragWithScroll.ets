@Entry
@Component
struct GridDragWithScroll {
  @State numbers: string[] = [];
  scroller: Scroller = new Scroller();
  @State item: string = '';
  @State flag: boolean = true;

  @Builder
  pixelMapBuilder() {
    Column() {
      Text(this.item)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  aboutToAppear() {
    for (let i = 1; i <= 15; i++) {
      this.numbers.push(`grid1 Item${i}`);
    }
  }

  build() {
    Column({ space: 5 }) {
      Grid(this.scroller) {
        ForEach(this.numbers, (day: string, index) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width(80)
              .height(80)
              .textAlign(TextAlign.Center)
          }
        }, (day: string) => JSON.stringify(day))
      }
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      .editMode(true)
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        this.item = this.numbers[itemIndex];
        this.numbers.splice(itemIndex, 1);
        return this.pixelMapBuilder();
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number,
        isSuccess: boolean) => {
        let deleteArea = this.getUIContext().getComponentUtils().getRectangleById('deleteArea')
        if (vp2px(event.x) > deleteArea.screenOffset.x &&
          vp2px(event.x) < deleteArea.screenOffset.x + deleteArea.size.width &&
          vp2px(event.y) > deleteArea.screenOffset.y &&
          vp2px(event.y) < deleteArea.screenOffset.y + deleteArea.size.height) {
          return;
        }

        if (insertIndex >= 0) {
          this.numbers.splice(insertIndex, 0, this.item);
        } else {
          this.numbers.push(this.item);
        }
      })
      .onItemDragMove((event: ItemDragInfo) => {
        if (event.y > 300 && event.y < 320) {
          this.scroller.scrollTo({
            xOffset: this.scroller.currentOffset().xOffset,
            yOffset: this.scroller.currentOffset().yOffset += 2
          })
        }
      })
      .id('gridContent')

      Row() {

      }
      .width('100%')
      .backgroundColor(Color.Pink)
      .margin({ top: 100 })
      .height(100)
      .draggable(true)
      .allowDrop([])
      .onDragEnd(() => {
        console.log(`aaaa fasdfdasfa`)
      })
      .id('deleteArea')
    }
  }
}