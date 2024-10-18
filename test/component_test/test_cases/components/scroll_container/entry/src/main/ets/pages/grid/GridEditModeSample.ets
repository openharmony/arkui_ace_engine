/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
// 测试代码路径
import gridEditModeTest from '../MyTest/GridEditModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridEditModeSample {
  @State editMode: boolean = true
  @State numbers: string[] = []

  @Builder
  pixelMapBuilder() {
    Column() {
    }
  }

  aboutToAppear(): void {
    loadComponentTestEntry(gridEditModeTest)
    for (let i = 1; i <= 15; i++) {
      this.numbers.push(i + '')
    }
  }

  changeIndex(index1: number, index2: number) {
    let temp: string;
    temp = this.numbers[index1];
    this.numbers[index1] = this.numbers[index2];
    this.numbers[index2] = temp;
  }

  build() {
    Column({ space: 5 }) {
      Grid() {
        ForEach(this.numbers, (day: string) => {
          GridItem() {
            Text('gridEditModeTest' + day)
              .backgroundColor(0xF9CF93)
          }
        })
      }
      .id('gridEditMode')
      .columnsTemplate('1fr 1fr 1fr')
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      .editMode(this.editMode)
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        return this.pixelMapBuilder()
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        this.changeIndex(itemIndex, insertIndex)
      })

      Button('GridEditMode')
        .onClick(() => {
          this.editMode = !this.editMode
        })
    }.width('100%').margin({ top: 5 })
  }
}