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
import listItemSelectedTest from '../MyTest/ListItemSelectedTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListItemSelectedSample {
  @State selectedType: boolean = false

  @Styles
  selectStyles(): void {
    .backgroundColor(0x008000)
    .borderWidth(2)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(listItemSelectedTest)
  }

  build() {
    Column() {
      List() {
        ListItem() {
          Text("list item selected1")
            .width('100%')
            .height(100)
        }
        .stateStyles({ selected: this.selectStyles })
        .selectable(true)
        .selected(this.selectedType)
        .backgroundColor(Color.Pink)
        .id('listItemSelected1')
      }

      List() {
        ListItem() {
          Text("list item selected2")
            .width('100%')
            .height(100)
        }
        .selectable(true)
        .selected(this.selectedType)
        .backgroundColor(Color.Pink)
        .id('listItemSelected2')
      }.multiSelectable(true)

      Button("ListItemSelected").onClick(() => {
        this.selectedType = !this.selectedType
      })
    }
  }
}