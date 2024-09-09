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
import gridItemSelectedTest from '../MyTest/GridItemSelectedTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridItemSelectedSample {
  @State select: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(gridItemSelectedTest)
  }

  @Styles
  normalStyles(): void{
    .backgroundColor("#E5E5E1")
  }

  @Styles
  selectStyles(): void{
    .backgroundColor("#ED6F21")
  }

  build() {
    Column({ space: 5 }) {
      Grid() {
        GridItem() {
          Text('4')
            .fontSize(16)
            .width('50%')
            .height('50%')
            .textAlign(TextAlign.Center)
        }
        .selectable(true)
        .selected(this.select)
        .id('gridItemSelected')
        .onClick(() => {
          this.select = !this.select
        })
        .stateStyles({
          normal: this.normalStyles,
          selected: this.selectStyles,
        })
      }.multiSelectable(true)
      .height(100)

      Button('GridItemSelected')
        .onClick(() => {
          this.select = !this.select
        })
    }.width('100%')
  }
}