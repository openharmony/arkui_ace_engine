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
import gridLayoutDirectionTest from '../MyTest/GridLayoutDirectionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridLayoutDirectionSample {
  numbers: string[] = []
  directionTypeArr: GridDirection[] = [
    GridDirection.Column, GridDirection.RowReverse, GridDirection.ColumnReverse]
  index: number = 0
  @State directionType: GridDirection = this.directionTypeArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(gridLayoutDirectionTest)
    for (let i = 1; i <= 30; i++) {
      this.numbers.push(i + '')
    }
  }

  build() {
    Scroll() {
      Column() {
        Grid() {
          ForEach(this.numbers, (day: string) => {
            GridItem() {
              Text('GridLayoutDirection' + day).fontSize(16).backgroundColor(0xF9CF93)
            }.width(80).height(80).borderWidth(2).borderColor(Color.Red)
          }, (day: string) => day)
        }
        .height(300)
        .columnsGap(10)
        .rowsGap(10)
        .layoutDirection(GridDirection.Row)
        .id('gridLayoutDirection1')

        Grid() {
          ForEach(this.numbers, (day: string) => {
            GridItem() {
              Text('GridLayoutDirection' + day).fontSize(16).backgroundColor(0xF9CF93)
            }.width(80).height(80).borderWidth(2).borderColor(Color.Red)
          }, (day: string) => day)
        }
        .height(300)
        .columnsGap(10)
        .rowsGap(10)
        .layoutDirection(this.directionType)
        .id('gridLayoutDirection2')

        Button('GridLayoutDirection')
          .onClick(() => {
            this.index++
            this.directionType = this.directionTypeArr[this.index % 3]
          })
      }
    }
  }
}