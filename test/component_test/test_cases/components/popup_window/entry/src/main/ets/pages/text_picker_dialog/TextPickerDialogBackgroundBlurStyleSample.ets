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
import textPickerDialogBackgroundBlurStyleTest from '../MyTest/TextPickerDialogBackgroundBlurStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextPickerDialogBackgroundBlurStyleSample {
  @State textDialogBackgroundBlurStyleIndex: number = -1
  private select: number | number[] = 0
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4', 'banana5']
  private textDialogBackgroundBlurStyleType: BlurStyle[] =
    [BlurStyle.Thin, BlurStyle.Regular, BlurStyle.Thick, BlurStyle.BACKGROUND_THIN, BlurStyle.BACKGROUND_REGULAR,
      BlurStyle.BACKGROUND_THICK, BlurStyle.BACKGROUND_ULTRA_THICK, BlurStyle.NONE, BlurStyle.COMPONENT_ULTRA_THIN,
      BlurStyle.COMPONENT_THIN, BlurStyle.COMPONENT_REGULAR,
      BlurStyle.COMPONENT_THICK, BlurStyle.COMPONENT_ULTRA_THICK]

  aboutToAppear(): void {
    loadComponentTestEntry(textPickerDialogBackgroundBlurStyleTest)
  }

  build() {
    Row() {
      Column() {
        Button("TextPickerDialogBackgroundBlurStyle")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              backgroundBlurStyle: this.textDialogBackgroundBlurStyleType[this.textDialogBackgroundBlurStyleIndex]
            })
          })
        Button('ClickToggleBackgroundBlueStyle')
          .onClick(() => {
            this.textDialogBackgroundBlurStyleIndex++
            this.textDialogBackgroundBlurStyleIndex %= 13
          })
      }.width('100%')
    }.height('100%')
  }
}