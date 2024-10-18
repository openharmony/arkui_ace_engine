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

//测试代码路径
import GridRowItemAlignTest from '../MyTest/GridRowItemAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridRowItemAlignSample {
  @State alignItemsStatus: ItemAlign = ItemAlign.Center

  aboutToAppear(): void {
    loadComponentTestEntry(GridRowItemAlignTest)
  }

  build() {
    Column() {
      GridRow() {
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("20%")
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("40%")
      }
      .id('gridRowItemAlign1')
      .alignItems(this.alignItemsStatus)
      .backgroundColor(Color.Red)
      .height("15%")
      .width("100%")

      GridRow() {
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("20%")
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("40%")
      }
      .id('gridRowItemAlign2')
      .alignItems(ItemAlign.Baseline)
      .backgroundColor(Color.Red)
      .height("15%")
      .width("100%")

      GridRow() {
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("20%")
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("40%")
      }
      .id('gridRowItemAlign3')
      .alignItems(ItemAlign.Auto)
      .backgroundColor(Color.Red)
      .height("15%")
      .width("100%")

      GridRow() {
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("20%")
        GridCol().borderColor(Color.Orange).borderWidth(2).width("20%").height("40%")
      }
      .id('gridRowItemAlign4')
      .alignItems(ItemAlign.End)
      .backgroundColor(Color.Red)
      .height("15%")
      .width("100%")

      Button('GridRowItemAlign1')
        .onClick(() => {
          this.alignItemsStatus = ItemAlign.Start
        })

      Button('GridRowItemAlign2')
        .onClick(() => {
          this.alignItemsStatus = ItemAlign.Stretch
        })
    }
  }
}