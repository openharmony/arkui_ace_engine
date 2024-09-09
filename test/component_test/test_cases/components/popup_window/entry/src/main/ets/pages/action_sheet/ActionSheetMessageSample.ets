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
import actionSheetMessageTest from '../MyTest/ActionSheetMessageTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetMessageSample {
  @State message: string | Resource = 'message1'
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetMessageTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetMessageTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: this.message,
            sheets: [{
              title: ' sheetsTitle1', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
        })

      Button('ActionSheetMessage1')
        .onClick(() => {
          this.message = $r('app.string.actionSheet_message')
        })
    }
  }
}