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
import actionSheetSheetsTest from '../MyTest/ActionSheetSheetsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetSheetsSample {
  @State title: string | Resource = ' sheetsTitle1'
  @State icon: string | Resource = '../../../resources/base/media/icon.png'
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetSheetsTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetSheetsTest1').onClick(() => {
        ActionSheet.show({
          title: 'title1',
          message: 'message1',
          sheets: [{
            title: this.title, icon: this.icon, action: () => {
              this.string = 'actionText1'
            }
          },]
        })
      })
      Button('ActionSheetSheets1').onClick(() => {
        this.title = $r('app.string.actionSheet_title')
        this.icon = $r('app.media.startIcon')
      })
    }
  }
}