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
import selectOptionBgColorTest from '../MyTest/SelectOptionBgColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectOptionBgColorSample {
  @State optionBgCol: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(selectOptionBgColorTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' },]).optionBgColor(Color.Green).id('selectOptionBgColor1')
      Select([{ value: 'select1' },
        { value: 'select2' },]).optionBgColor(0xa52a2a).id('selectOptionBgColor2')
      Select([{ value: 'select1' },
        { value: 'select2' },]).optionBgColor(this.optionBgCol).id('selectOptionBgColor3')

      Button('SelectOptionBgColor').onClick(() => {
        this.optionBgCol = $r('sys.color.ohos_fa_palette1')
      })
    }.width('100%')
  }
}