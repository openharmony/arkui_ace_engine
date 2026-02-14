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

class GridDataSource {
  private dataArray: string[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(dataArray: string[]) {
    this.dataArray = dataArray;
  }

  totalCount(): number {
    return this.dataArray.length;
  }

  getData(index: number): string {
    return this.dataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
 {
      if (this.listeners.indexOf(listener) < 0) {
        this.listeners.push(listener);
      }
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
struct GridEditModeOptions {
  numbers: GridDataSource = new GridDataSource(['1', '2', '3', '4', '5', '6', '7', '8', '9']);
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
    for (i = 0; i < 9; i++) {
      this.isSelected.push(false);
    }
  }

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('menu item menu item 1')
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

      Text('Grid editModeOptions Demo')
        .fontSize(20)
        .margin({ top: 10 })

      Text('Long press on GridItem to show menu and gather selected items')
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ top: 5 })

      Grid() {
        LazyForEach(this.numbers, (day: string, index: number) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CFCF)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
          }
          .selected(this.isSelected[index])
          .stateStyles({
            normal: this.normalStyles,
            selected: this.selectStyles
          })
          .bindContextMenu(this.MenuBuilder, ResponseType.LongPress,
            { preview: MenuPreviewMode.IMAGE, hapticFeedbackMode: HapticFeedbackMode.ENABLED })
          .onClick(() => {
            this.isSelected[index] = !this.isSelected[index];
            console.info(`item:${index}, this.isSelected[item]:${this.isSelected[index]}`)
            if (this.isSelected[index]) {
              ++this.selectedCount;
            } else {
              --this.selectedCount;
            }
          })
        }, (day: string) => day)
      }
      .editModeOptions({
        enableGatherSelectedItemsAnimation: true, onGetPreviewBadge: () => {
          return this.selectedCount;
        }
      })
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
    }.width('100%').margin({ top: 5 })
  }
}
