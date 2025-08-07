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

import vibrator from '@ohos.vibrator';

@Entry
@Component
struct Index {
  @State contentHeight: number = 300;
  @State isShow: boolean = false;
  @State items: string[] = [
    '#FF0000',
    '#FFFF00',
    '#00FF00',
    '#00FFFF',
    '#0000FF'
  ];

  @Builder
  DraggingItem(item: string) {
    Column() {
      Rect().fill(item).width(50).height(50)
    }.width(50).height(50)
  }

  @Builder
  GridPage() {
    Grid() {
      ForEach(this.items, (item: string) => {
        GridItem() {
          Rect().fill(item).width(50).height(50)
        }
      }, (item: string) => item)
    }
    .editMode(true)
    .supportAnimation(true)
    .overlay()
    .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { // 第一次拖拽此事件绑定的组件时，触发回调。
      console.log('SheetGridDemo: onItemDragStart');
      vibrator.startVibration({
        type: 'preset',
        effectId: 'haptic.common.success',
        count: 1
      }, {
        usage: 'physicalFeedback'
      });
      return this.DraggingItem(this.items[itemIndex]);
    })
    // 绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
    .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
      console.log('SheetGridDemo: onItemDrop, itemIndex: ${itemIndex}, insertIndex: ${insertIndex}');
    })
    .columnsTemplate('1fr 1fr 1fr 1fr')
    .width('100%')
    .height(500)
  }

  @Builder
  TestSheetContent() {
    Column({ space: 20 }) {
      Text('当前高度: ' + this.contentHeight)
      Text('在Sheet中拖拽：')
      Button('改变高度').onClick(() => {
        this.contentHeight = this.contentHeight === 300 ? 500 : 300;
      })
      this.GridPage()
    }
    .backgroundColor(Color.Pink)
    .height(this.contentHeight)
  }

  build() {
    Row() {
      Column({ space: 20 }) {
        Text('当前高度: ' + this.contentHeight)
        Text('不在Sheet中拖拽：')
        this.GridPage()

        Button('Show')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.isShow = true;
          })
          .bindSheet(this.isShow, this.TestSheetContent(), {
            height: SheetSize
              .FIT_CONTENT,
            onDisappear: () => {
              this.isShow = false;
            }
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}