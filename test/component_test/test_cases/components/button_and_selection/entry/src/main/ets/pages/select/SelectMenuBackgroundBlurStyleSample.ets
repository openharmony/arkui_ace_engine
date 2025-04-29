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
import selectMenuBackgroundBlurStyleTest from '../MyTest/SelectMenuBackgroundBlurStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectMenuBackgroundBlurStyleSample {
  @State text: string = "Title"
  @State blurBackThin: BlurStyle = BlurStyle.BACKGROUND_THIN
  @State blurComponentThin: BlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
  @State blurComponentThick: BlurStyle = BlurStyle.COMPONENT_THICK

  aboutToAppear(): void {
    loadComponentTestEntry(selectMenuBackgroundBlurStyleTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.Thin)
        .id('selectMenuBackgroundBlurStyle1')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.Regular)
        .id('selectMenuBackgroundBlurStyle2')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.Thick)
        .id('selectMenuBackgroundBlurStyle3')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(this.blurBackThin)
        .id('selectMenuBackgroundBlurStyle4')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.BACKGROUND_THICK)
        .id('selectMenuBackgroundBlurStyle5')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.BACKGROUND_ULTRA_THICK)
        .id('selectMenuBackgroundBlurStyle6')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.NONE)
        .id('selectMenuBackgroundBlurStyle7')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(this.blurComponentThin)
        .id('selectMenuBackgroundBlurStyle8')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(BlurStyle.COMPONENT_REGULAR)
        .id('selectMenuBackgroundBlurStyle9')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .value(this.text)
        .menuBackgroundBlurStyle(this.blurComponentThick)
        .id('selectMenuBackgroundBlurStyle10')

      Button('SelectMenuBackgroundBlurStyle').onClick(() => {
        this.blurBackThin = BlurStyle.BACKGROUND_REGULAR
        this.blurComponentThin = BlurStyle.COMPONENT_THIN
        this.blurComponentThick = BlurStyle.COMPONENT_ULTRA_THICK
      })
    }.width('100%')
  }
}