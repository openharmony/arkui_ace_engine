/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

@ObservedV2
class ListDragData {
  @Trace public title: string = '';
  @Trace public data: string[] = [];

  constructor(title: string, data: string[]) {
    this.title = title;
    this.data = data;
  }
}

class ListDragDraggingData {
  public data?: string;
}

@ComponentV2
struct ListDragPanel {
  @Require @Param data: string[];
  @Require @Param draggingData: ListDragDraggingData;

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
        .width('100%')
        .height('10%')
        .margin(10)
        .backgroundColor(Color.White)
        .borderRadius(4)
        .aspectRatio(1)
      }, (item: string) => item)
    }
    .width('50%')
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
      console.info('Item drag enter at position:', event.x, event.y);
    })
    .onItemDragMove((itemDragInfo: ItemDragInfo, itemIndex: number, insertIndex: number) => {
      if (this.lastInsertIndex != insertIndex){
        console.info('whk', itemDragInfo.x, itemDragInfo.y);
        this.lastInsertIndex = insertIndex;
      }
    })
    .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
      if (!isSuccess) {
        this.draggingData.data = undefined;
        return;
      }
      if (insertIndex >= 0) {
        this.data.splice(insertIndex, 0, this.draggingData.data!);
      }
      console.info('reportComponentChangeEvent  ' + event.x + ' drag insertIndex at position:', event.y);
      this.draggingData.data = undefined;
    })
    .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
      this.viewWidth = newValue.width as number;
    })
  }
}

@Entry
@ComponentV2
struct dragListIndex {
  @Local data: ListDragData[] = [
    new ListDragData('A', ['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8']),
    new ListDragData('B', ['B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7', 'B8']),
  ]
  @Local draggingData: ListDragDraggingData = new ListDragDraggingData();

  build() {
    Stack() {
      Row() {
        ListDragPanel({ data: this.data[0].data, draggingData: this.draggingData })
        ListDragPanel({ data: this.data[1].data, draggingData: this.draggingData })
      }
    }
    .backgroundColor('#FFDCDCDC')
  }
}