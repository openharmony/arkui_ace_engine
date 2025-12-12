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

@ObservedV2
class PageData {
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
struct DraggableGrid {
  @Require @Param swiperCtrl: SwiperController;
  @Require @Param data: string[];
  @Require @Param draggingData: DraggingData;
  @Builder
  ItemBuilder(data: string, size: SizeOptions) {
    Stack() {
      Text(data)
    }
    .backgroundColor(Color.White)
    .borderRadius(4)
    .size(size)
  }
  viewWidth: number = 0;
  entryHotZoneTm?: number;

  scroller: Scroller = new Scroller();
  build() {
    Grid(this.scroller) {
      Repeat<string>(this.data)
        .each((item: RepeatItem<string>) => {
          GridItem() {
            Text(item.item)
          }
          .backgroundColor(Color.White)
          .borderRadius(4)
          .width('100%')
          .aspectRatio(1)
        })
        .key((item: string) => item)
    }.columnsTemplate('1fr 1fr 1fr')
    .rowsGap(10)
    .columnsGap(10)
    .padding(10)
    .editMode(true)
    .supportAnimation(true)
    .onItemDragStart((event: ItemDragInfo, itemIndex: number)=>{
      let rect = this.scroller.getItemRect(itemIndex);
      let size: SizeOptions = {
        width: rect.width,
        height: rect.height
      };
      this.draggingData.data = this.data[itemIndex];
      return this.ItemBuilder(this.data[itemIndex], size);
    })
    .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number)=>{
      if (event.x < 32) {
        if (this.entryHotZoneTm === undefined) {
          this.entryHotZoneTm = new Date().getTime();
        } else {
          let current = new Date().getTime();
          if (current - this.entryHotZoneTm > 800) {
            this.entryHotZoneTm = undefined;
            this.swiperCtrl.showPrevious();
          }
        }
      } else if (event.x > this.viewWidth - 32) {
        if (this.entryHotZoneTm === undefined) {
          this.entryHotZoneTm = new Date().getTime();
        } else {
          let current = new Date().getTime();
          if (current - this.entryHotZoneTm > 800) {
            this.entryHotZoneTm = undefined;
            this.swiperCtrl.showNext();
          }
        }
      } else {
        this.entryHotZoneTm = undefined;
      }
    })
    .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean)=>{
      if (!isSuccess) {
        this.draggingData.data = undefined;
        return;
      }
      if (itemIndex >= 0 && insertIndex >= 0) {
        let tmp = this.data.splice(itemIndex, 1);
        this.data.splice(insertIndex, 0, tmp[0]);
      } else if (itemIndex >= 0) {
        this.data.splice(itemIndex, 1);
      } else if (insertIndex >= 0) {
        this.data.splice(insertIndex, 0, this.draggingData.data!);
      }
      this.draggingData.data = undefined;
    })
    .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions)=>{
      this.viewWidth = newValue.width as number;
    })
  }
}

@Entry
@ComponentV2
struct Index {
  swiperCtrl: SwiperController = new SwiperController()
  @Local data: PageData[] = [
    new PageData('A', ['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8']),
    new PageData('B', ['B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7', 'B8']),
    new PageData('C', ['C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8']),
    new PageData('D', ['D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'D8']),
    new PageData('E', ['E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7', 'E8']),
  ]
  @Local draggingData: DraggingData = new DraggingData()
  build() {
    Stack() {
      Swiper(this.swiperCtrl) {
        Repeat<PageData>(this.data)
          .each((item: RepeatItem<PageData>) => {
            DraggableGrid({data: item.item.data, swiperCtrl: this.swiperCtrl, draggingData: this.draggingData})
          })
          .key((item: PageData) => item.title)
      }
      .height('100%')
      .width('100%')
    }.backgroundColor('#dcdcdc')
  }
}
