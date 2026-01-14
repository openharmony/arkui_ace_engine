/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/*
 * Description: List在扩展安全区的情况下支持展开指定ListItem的swipeAction
 * Writer: dailihuan
 */

@ObservedV2
class ListData {
  @Trace public title: string = '';
  @Trace public data: string[] = [];

  constructor(title: string, data: string[]) {
    this.title = title;
    this.data = data;
  }
}

class DraggingData {
  public data?: string;
}

@ComponentV2
struct DraggableList {
  @Require @Param data: string[];
  @Require @Param draggingData: DraggingData;

  @Builder
  ItemBuilder(data: string, size: SizeOptions, event: ItemDragInfo): void {
    Stack() {
      Text(data)
    }
    .backgroundColor(Color.White)
    .borderRadius(4)
    .size(size)
  }

  viewWidth: number = 0;
  lastInsertIndex: number = 0;
  scroller: Scroller = new Scroller();

  build() {
    List({ scroller: this.scroller }) {
      ForEach(this.data, (item: string) => {
        ListItem() {
          Text(item)
        }
        .width("100%")
        .height("10%")
        .margin(10)
        .backgroundColor(Color.White)
        .borderRadius(4)
        .width('100%')
        .aspectRatio(1)
      }, (item: string) => item)
    }
    .width("50%")
    .layoutWeight(1)
    .padding(10)
    .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
      let rect = this.scroller.getItemRect(itemIndex);
      let size: SizeOptions = {
        width: rect.width,
        height: rect.height
      };
      this.lastInsertIndex = itemIndex;
      this.draggingData.data = this.data[itemIndex];
      this.data.splice(itemIndex, 1);

      return this.ItemBuilder(this.draggingData.data, size, event);
    })
    .onItemDragEnter((event: ItemDragInfo) => {
      console.info("Item drag enter at position:", event.x, event.y);
    })
    .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => {
      if (this.lastInsertIndex != insertIndex){
        console.info("insertIndex change from ", this.lastInsertIndex, "to", insertIndex);
        this.lastInsertIndex = insertIndex;
      }
    })
    .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => {
      console.info("Item " + itemIndex + " drag leave at position:", event.x, event.y);
    })
    .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
      if (!isSuccess) {
        this.draggingData.data = undefined;
        return;
      }
      if (insertIndex >= 0) {
        this.data.splice(insertIndex, 0, this.draggingData.data!);
      }
      this.draggingData.data = undefined;
    })
    .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
      this.viewWidth = newValue.width as number;
    })
  }
}

@Entry
@ComponentV2
struct Index {
  @Local data: ListData[] = [
    new ListData('A', ['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8']),
    new ListData('B', ['B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7', 'B8']),
  ];
  @Local draggingData: DraggingData = new DraggingData();

  build() {
    Stack() {
      Row() {
        DraggableList({ data: this.data[0].data, draggingData: this.draggingData })
        DraggableList({ data: this.data[1].data, draggingData: this.draggingData })
      }
    }
    .backgroundColor('#FFDCDCDC')
  }
}