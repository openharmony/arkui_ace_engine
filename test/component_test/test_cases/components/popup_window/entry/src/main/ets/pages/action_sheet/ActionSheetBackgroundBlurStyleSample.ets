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
import actionSheetBackgroundBlurStyleTest from '../MyTest/ActionSheetBackgroundBlurStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetBackgroundBlurStyleSample {
  @State BlurStyle: BlurStyle[] =
    [BlurStyle.Thin, BlurStyle.Regular, BlurStyle.Thick, BlurStyle.BACKGROUND_THIN, BlurStyle.BACKGROUND_REGULAR,
      BlurStyle.BACKGROUND_THICK,
      BlurStyle.BACKGROUND_ULTRA_THICK, BlurStyle.NONE, BlurStyle.COMPONENT_ULTRA_THIN, BlurStyle.COMPONENT_THIN,
      BlurStyle.COMPONENT_REGULAR, BlurStyle.COMPONENT_THICK, BlurStyle.COMPONENT_ULTRA_THICK]
  @State string: string = 'actionText'
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetBackgroundBlurStyleTest)
  }

  build() {
    Column() {
      Text(this.string)
      Button('ActionSheetBackgroundBlurStyleTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: 'message1',
            backgroundBlurStyle: this.BlurStyle[this.index],
            sheets: [{
              title: 'sheetsTitle1', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
          this.index++
          this.index %= 13
        })
    }
  }
}