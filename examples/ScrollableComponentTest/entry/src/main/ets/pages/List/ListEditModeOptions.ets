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

import router from '@ohos.router';

class ListDataSource {
  private dataArray: number[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(dataArray: number[]) {
    this.dataArray = dataArray;
  }

  totalCount(): number {
    return this.dataArray.length;
  }

  getData(index: number): number {
    return this.dataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }
}

@Entry
@Component
struct ListEditModeOptions {
  private arr: ListDataSource = new ListDataSource([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
  @State isSelected: boolean[] = [];
  selectedCount: number = 0;

  @Styles
  normalStyles(): void {
    .opacity(1.0)
  }

  @Styles
  selectStyles(): void {
    .opacity(0.4)
  }

  onPageShow(): void {
    let i: number = 0;
    for (i = 0; i < 10; i++) {
      this.isSelected.push(false);
    }
  }

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('menu item 1')
        .fontSize(18)
        .width(120)
        .height(50)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('menu item 2')
        .fontSize(18)
        .width(120)
        .height(50)
        .textAlign(TextAlign.Center)
    }.width(100)
  }

  build() {
    Column({ space: 5 }) {
      Button('Back')
        .width(100)
        .height(40)
        .margin({ top: 10 })
        .onClick(() => {
          router.back();
        })

      Text('List editModeOptions Demo')
        .fontSize(20)
        .margin({ top: 10 })

      Text('Long press on ListItem to show menu and gather selected items')
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ top: 5 })

      List({ space: 10 }) {
        LazyForEach(this.arr, (item: number) => {
          ListItem() {
            Text(item.toString())
              .fontSize(16)
              .backgroundColor(Color.White)
              .width('100%')
              .height(50)
              .textAlign(TextAlign.Center)
          }
          .selected(this.isSelected[item])
          .stateStyles({
            normal: this.normalStyles,
            selected: this.selectStyles
          })
          .bindContextMenu(this.MenuBuilder, ResponseType.LongPress,
            { preview: MenuPreviewMode.IMAGE, hapticFeedbackMode: HapticFeedbackMode.ENABLED })
          .onClick(() => {
            this.isSelected[item] = !this.isSelected[item];
            console.info(`item:${item}, this.isSelected[item]:${this.isSelected[item]}`)
            if (this.isSelected[item]) {
              ++this.selectedCount;
            } else {
              --this.selectedCount;
            }
          })
        }, (item: number) => item.toString())
      }
      .editModeOptions({
        enableGatherSelectedItemsAnimation: true, onGetPreviewBadge: () => {
          return this.selectedCount;
        }
      })
      .width('90%')
      .height(300)
      .scrollBar(BarState.Off)
    }.width('100%').margin({ top: 5 }).backgroundColor('#FFDCDCDC')
  }
}
