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
import selectSelectedOptionBgColorTest from '../MyTest/SelectSelectedOptionBgColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectSelectedOptionBgColorSample {
  @State selectedOpFontCol: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(selectSelectedOptionBgColorTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionBgColor(Color.Green)
        .id('selectSelectedOptionBgColor1')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionBgColor(0xffa500)
        .id('selectSelectedOptionBgColor2')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionBgColor(this.selectedOpFontCol)
        .id('selectSelectedOptionBgColor3')

      Button('SelectSelectedOptionBgColor').onClick(() => {
        this.selectedOpFontCol = $r('sys.color.ohos_fa_palette1')
      })
    }.width('100%')
  }
}