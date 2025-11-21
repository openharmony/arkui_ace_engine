/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

enum DragState {
  IDLE = 0,
  LONG_PRESS = 1,
  DRAGGING = 2,
  DROP = 3
}

@ObservedV2
class DragCtrl<T> {
  @Trace public groupIndex?: number;
  @Trace public itemIndex?: number;
  @Trace public item?: T;
  @Trace public dragState: DragState = DragState.IDLE;
  @Trace public rect: RectResult = {
    x: 0,
    y: 0,
    width: 0,
    height: 0
  };
  private posX0: number = 0;
  private posY0: number = 0;
  private scroller: ListScroller;
  private getData: (groupIndex: number, itemIndex: number) => T;
  private move: (fromGroupIndex: number, fromItemIndex: number, toGroupIndex: number, toItemIndex: number) => void;
  private viewHeight: number = 0;
  private scrolling: boolean = false;
  private context: UIContext;

  constructor(
    context: UIContext,
    scroller: ListScroller,
    getData: (groupIndex: number, itemIndex: number) => T,
    move: (fromGroupIndex: number, fromItemIndex: number, toGroupIndex: number, toItemIndex: number) => void
  ) {
    this.context = context;
    this.scroller = scroller;
    this.getData = getData;
    this.move = move;
  }

  setViewHeight(viewHeight: number): void {
    this.viewHeight = viewHeight;
  }

  swapTo(groupIndex: number, itemIndex: number): void {
    if (this.groupIndex === undefined || this.itemIndex === undefined) {
      return;
    }
    if (itemIndex !== this.itemIndex && groupIndex === this.groupIndex) {
      let fromIndex: number = this.itemIndex;
      this.context.animateTo({ duration: 300 }, () => {
        this.move(groupIndex, fromIndex, groupIndex, itemIndex);
      })
      this.itemIndex = itemIndex;
    }
    if (groupIndex !== this.groupIndex) {
      let fromIndex = this.itemIndex;
      let fromGroup = this.groupIndex;
      this.context.animateTo({ duration: 300 }, () => {
        this.move(fromGroup, fromIndex, groupIndex, itemIndex);
      })
      this.itemIndex = itemIndex;
      this.groupIndex = groupIndex;
    }
  }

  reset(): void {
    this.groupIndex = undefined;
    this.itemIndex = undefined;
    this.dragState = DragState.IDLE;
    this.item = undefined;
  }

  onLongPress(event: GestureEvent): void {
    let pos = event.fingerList[0];
    let info: VisibleListContentInfo = this.scroller.getVisibleListContentInfo(pos.localX, pos.localY);
    if (info.itemIndexInGroup !== undefined) {
      this.item = this.getData(info.index, info.itemIndexInGroup);
      this.groupIndex = info.index;
      this.itemIndex = info.itemIndexInGroup;
      this.dragState = DragState.LONG_PRESS;
      this.rect = this.scroller.getItemRectInGroup(info.index, info.itemIndexInGroup);
      this.posX0 = this.rect.x;
      this.posY0 = this.rect.y;
    }
  }

  onDragStart(event: GestureEvent): void {
    if (this.dragState === DragState.LONG_PRESS) {
      this.dragState = DragState.DRAGGING;
    }
  }

  onDragUpdate(event: GestureEvent): void {
    if (this.dragState !== DragState.DRAGGING) {
      return;
    }
    this.rect = {
      x: this.posX0 + event.offsetX,
      y: this.posY0 + event.offsetY,
      width: this.rect.width,
      height: this.rect.height
    };
    let pos = event.fingerList[0];
    let info = this.scroller.getVisibleListContentInfo(pos.localX, pos.localY);
    if (info.itemIndexInGroup !== undefined) {
      this.swapTo(info.index, info.itemIndexInGroup);
    }
    if (pos.localY < 56) {
      if (!this.scrolling) {
        this.scroller.scrollEdge(Edge.Top, { velocity: 500 });
        this.scrolling = true;
      }
    } else if (pos.localY > this.viewHeight - 56) {
      if (!this.scrolling) {
        this.scroller.scrollEdge(Edge.Bottom, { velocity: 500 });
        this.scrolling = true;
      }
    } else {
      this.scrolling = false;
    }
  }

  onDrop(event: GestureEvent): void {
    if (this.dragState !== DragState.DRAGGING) {
      return;
    }
    let rect = this.scroller.getItemRectInGroup(this.groupIndex, this.itemIndex);
    this.context.animateTo({
      duration: 300,
      onFinish: () => {
        this.reset();
      }
    }, () => {
      this.rect = rect;
    });
  }
}

@ObservedV2
class GroupData {
  @Trace public title: string = '';
  @Trace public data: string[] = [];

  constructor(title: string, data: string[]) {
    this.title = title;
    this.data = data;
  }
}

@ComponentV2
struct SortableGroup {
  @Require @Param data: GroupData;
  @Require @Param draggingInfo: DragCtrl<string>;

  build() {
    ListItemGroup() {
      Repeat<string>(this.data.data)
        .each((item: RepeatItem<string>) => {
          ListItem() {
            Text(item.item)
          }
          .height(48)
          .width('100%')
          .borderRadius(8)
          .visibility(this.draggingInfo?.item === item.item ? Visibility.Hidden : Visibility.Visible)
          .transition(TransitionEffect.IDENTITY)
        })
        .key((item: string) => {
          return item;
        })
    }
    .margin({ left: 12, right: 12 })
    .padding(4)
    .borderRadius(16)
    .backgroundColor(Color.White)
    .divider({ strokeWidth: '1px', color: '#DCDCDC' })
  }
}

@Entry
@ComponentV2
struct Index {
  private scroller: ListScroller = new ListScroller();
  @Local groupedData: GroupData[] = [
    new GroupData('A', ['A1', 'A2', 'A3', 'A4']),
    new GroupData('B', ['B1', 'B2', 'B3', 'B4']),
    new GroupData('C', ['C1', 'C2', 'C3', 'C4']),
    new GroupData('D', ['D1', 'D2', 'D3', 'D4']),
    new GroupData('E', ['E1', 'E2', 'E3', 'E4']),
  ];
  @Local draggingInfo: DragCtrl<string> = new DragCtrl<string>(
    this.getUIContext(),
    this.scroller,
    (groupIndex: number, itemIndex: number): string => {
      return this.groupedData[groupIndex].data[itemIndex];
    },
    (fromGroupIndex: number, fromItemIndex: number, toGroupIndex: number, toItemIndex: number): void => {
      let tmp = this.groupedData[fromGroupIndex].data.splice(fromItemIndex, 1);
      this.groupedData[toGroupIndex].data.splice(toItemIndex, 0, tmp[0]);
    }
  );

  build() {
    Stack() {
      List({ space: 10, scroller: this.scroller }) {
        Repeat<GroupData>(this.groupedData)
          .each((data: RepeatItem<GroupData>) => {
            SortableGroup({ data: data.item, draggingInfo: this.draggingInfo });
          })
          .key((item: GroupData) => {
            return item.title;
          })
      }
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.draggingInfo.setViewHeight(newValue.height as number)
      })
      .gesture(
        GestureGroup(GestureMode.Sequence,
          LongPressGesture({ repeat: false })
            .onAction((event: GestureEvent) => {
              this.draggingInfo.onLongPress(event);
            }),
          PanGesture({ fingers: 1 })
            .onActionStart((event: GestureEvent) => {
              this.draggingInfo.onDragStart(event);
            })
            .onActionUpdate((event: GestureEvent) => {
              this.draggingInfo.onDragUpdate(event);
            })
            .onActionEnd((event: GestureEvent) => {
              this.draggingInfo.onDrop(event);
            })
        ).onCancel(() => {
          this.draggingInfo.reset();
        })
      )

      if (this.draggingInfo.dragState !== DragState.IDLE) {
        Stack() {
          Text(this.draggingInfo.item)
        }
        .size({ width: this.draggingInfo.rect.width, height: this.draggingInfo.rect.height })
        .position({ x: this.draggingInfo.rect.x, y: this.draggingInfo.rect.y })
        .borderRadius(8)
        .backgroundColor(Color.White)
        .shadow(ShadowStyle.OUTER_DEFAULT_SM)
      }
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#DCDCDC')
  }
}
