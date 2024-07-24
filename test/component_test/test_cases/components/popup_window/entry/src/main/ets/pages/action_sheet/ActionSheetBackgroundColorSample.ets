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
import actionSheetBackgroundColorTest from '../MyTest/ActionSheetBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetBackgroundColorSample {
  @State backgroundColor1: ResourceColor = Color.Gray
  @State backgroundColor2: ResourceColor = "#FFBC3535"
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetBackgroundColorTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetBackgroundColorTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: 'message1',
            backgroundColor: this.backgroundColor1,
            sheets: [{
              title: 'sheetsTitle1', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
        })
      Button('ActionSheetBackgroundColorTest2')
        .onClick(() => {
          ActionSheet.show({
            title: 'title2',
            message: 'message2',
            backgroundColor: this.backgroundColor2,
            sheets: [{
              title: 'sheetsTitle2', action: () => {
                this.string = 'actionText2'
              }
            },]
          })
        })
      Button('ActionSheetBackgroundColor1').onClick(() => {
        this.backgroundColor1 = $r("app.color.action_sheet_color")
        this.backgroundColor2 = 0x00dd77
      })
    }
  }
}