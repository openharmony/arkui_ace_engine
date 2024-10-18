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
import selectSelectedOptionFontColorTest from '../MyTest/SelectSelectedOptionFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectSelectedOptionFontColorSample {
  @State selectedOpBgCol: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(selectSelectedOptionFontColorTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionFontColor(Color.Green)
        .id('selectSelectedOptionFontColor1')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionFontColor(0xffa500)
        .id('selectSelectedOptionFontColor2')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionFontColor(this.selectedOpBgCol)
        .id('selectSelectedOptionFontColor3')

      Button('SelectSelectedOptionFontColor').onClick(() => {
        this.selectedOpBgCol = $r('sys.color.ohos_fa_palette1')
      })
    }.width('100%')
  }
}