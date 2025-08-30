@Entry
@Component
export struct DragPageDemo {
  @State dragListData1: DragListItemObj[] = [
    new DragListItemObj($r('app.media.startIcon'), '名字1', 1),
    new DragListItemObj($r('app.media.startIcon'), '名字2', 2),
    new DragListItemObj($r('app.media.startIcon'), '名字3', 3),
    new DragListItemObj($r('app.media.startIcon'), '名字4', 4),
    new DragListItemObj($r('app.media.startIcon'), '名字5', 5)
  ];
  @State dragListData2: DragListItemObj[] = [
    new DragListItemObj($r('app.media.startIcon'), '名字6', 6),
    new DragListItemObj($r('app.media.startIcon'), '名字7', 7),
    new DragListItemObj($r('app.media.startIcon'), '名字8', 8),
    new DragListItemObj($r('app.media.startIcon'), '名字9', 9),
    new DragListItemObj($r('app.media.startIcon'), '名字10', 10)
  ];
  @State temp: DragListItemObj | undefined = undefined;
  @State h: number = 254;
  @State h2: number = 254;

  build() {
    Scroll() {
      Column() {

        DragList({
          dragListData: this.dragListData1,
          temp: this.temp,
          name: 'main',
          h: this.h,
          h2: this.h2
        })
          .height(this.h)
        Blank().height(50)
        DragList({
          dragListData: this.dragListData2,
          temp: this.temp,
          name: 'more',
          h: this.h,
          h2: this.h2
        })
          .height(this.h2)
      }
      .backgroundColor(0x01000013)
      .width('90%')
    }
    .width('100%')
    .height('100%')

    .backgroundColor(Color.Black)
  }
}

@Component
struct DragList {
  @Link dragListData: DragListItemObj[];
  @Link temp: DragListItemObj;
  @BuilderParam name: string;
  @Link h: number;
  @Link h2: number;

  changeIndex(index1: number, index2: number) {
    let tmp = this.dragListData.splice(index1, 1);
    this.dragListData.splice(index2, 0, tmp[0]);
  }

  build() {
    Column() {
      Grid() {
        ForEach(this.dragListData, (item: DragListItemObj, index: number) => {
          GridItem() {
            Column() {
              DragListItem({ dragListItemObj: item })
                .margin({
                  top: 12,
                  bottom: 12
                })

              if (index !== this.dragListData.length - 1) {
                Divider()
                  .width('80%')
                  .height(1)
              }
            }
          }
        })
      }
      .columnsTemplate('1fr')
      .editMode(true)
      .supportAnimation(true)
      .onItemDragStart((event, itemIndex) => {
        console.log('struct drag start %s, %s is select', this.name, this.dragListData[itemIndex]);
        this.temp = this.dragListData[itemIndex];
        return this.draggingShow();
      })
      .onItemDrop((_, itemIndex: number, insertIndex: number,
        isSuccess: boolean) => {
        console.log('drag drop ' + 'index' + itemIndex.toString() + 'xxx' + insertIndex.toString());
        if (!isSuccess) {
          return;
        }
        if (itemIndex == -1) {
          this.dragListData.splice(insertIndex, 0, this.temp);
          if (this.name == 'more') {
            this.h2 += 20;

          } else {
            this.h += 20;
          }
          return;
        }
        if (insertIndex == -1) {
          this.dragListData.splice(itemIndex, 1);
          if (this.name == 'more') {
            this.h2 -= 20;
          } else {
            this.h -= 20;
          }
          return;
        }
        if (insertIndex >= this.dragListData.length) {
          return;
        }
        this.changeIndex(itemIndex, insertIndex);
      })
    }
    .backgroundColor(Color.White)
    .borderRadius(16);
  }

  @Builder
  draggingShow() {
    DragListItem({
      dragListItemObj: this.temp,
      dragging: true
    })
  }
}

@Component
export struct DragListItem {
  @BuilderParam dragListItemObj: DragListItemObj;
  dragging: boolean = false;
  @State symbolSize: number = 20;
  @State titleFontSize: number = 16;

  aboutToAppear(): void {
    if (this.dragging) {
      this.symbolSize = 24;
      this.titleFontSize = 20;
    }
  }

  build() {
    Row() {
      Row() {
        // 删除减号
        SymbolGlyph($r('sys.symbol.minus_circle_fill'))
          .fontColor([Color.Red])
          .width(this.symbolSize)
          .height(this.symbolSize)
          .margin({ left: 12 })
          .onClick(() => {
            // TODO: 删除逻辑
          })
          .draggable(false)
          .visibility(this.dragging ? Visibility.None : Visibility.Visible)
        // 图标
        Image(this.dragListItemObj.icon)
          .width(this.symbolSize)
          .height(this.symbolSize)
          .margin({ left: 20 })
          .focusable(false)
          .draggable(false)
        // 名字
        Text(this.dragListItemObj.title)
          .maxLines(1)
          .fontSize(this.symbolSize)
          .margin({ left: 10 })
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .ellipsisMode(EllipsisMode.END)
          .layoutWeight(1)
          .textAlign(TextAlign.Start)
          .focusable(false)
          .draggable(false)
      }
      .layoutWeight(1)

      // 三条线
      SymbolGlyph($r('app.media.startIcon'))
        .fontColor([Color.Black])
        .width(this.symbolSize)
        .height(this.symbolSize)
        .margin({ right: 12 })
    }
    .width('100%')
    .height(50)
  }
}

export class DragListItemObj {
  public icon: Resource | ResourceStr;
  public title: string;
  public index: number;
  public desc?: string;
  public type?: number;

  constructor(icon: Resource | ResourceStr, title: string, index: number, desc?: string, type?: number) {
    this.icon = icon;
    this.title = title;
    this.index = index;
    this.desc = desc ?? '';
    this.type = type ?? 0;
  }
}