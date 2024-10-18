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
import actionSheetOffsetTest from '../MyTest/ActionSheetOffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetOffsetSample {
  @State offset_dx: number | string = 2
  @State offset_dy: number | string = -20
  @State string: string = 'actionText'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetOffsetTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetOffsetTest1').onClick(() => {
        ActionSheet.show({
          title: 'title1',
          message: 'message1',
          offset: { dx: $r('app.string.actionSheet_offset_dx'), dy: $r('app.string.actionSheet_offset_dy') },
          sheets: [{
            title: 'sheetsTitle1', action: () => {
              this.string = 'actionText1'
            }
          },]
        })
      })
      Button('ActionSheetOffsetTest2').onClick(() => {
        ActionSheet.show({
          title: 'title2',
          message: 'message2',
          offset: { dx: this.offset_dx, dy: this.offset_dy },
          sheets: [{
            title: 'sheetsTitle2', action: () => {
              this.string = 'actionText2'
            }
          },]
        })
      })
      Button('ActionSheetOffset1').onClick(() => {
        this.offset_dx = "8px"
        this.offset_dy = "-80px"
      })
    }
  }
}