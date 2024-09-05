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
import actionSheetIsModalTest from '../MyTest/ActionSheetIsModalTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetIsModalSample {
  @State isModal: boolean = true
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetIsModalTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetIsModalTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: 'message1',
            isModal: this.isModal,
            sheets: [{
              title: 'sheetsTitle11', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
        })
      Button('ActionSheetIsModal1').onClick(() => {
        this.isModal = !this.isModal
      })
    }
  }
}