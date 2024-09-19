/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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
import selectOptionHeightTest from '../MyTest/SelectOptionHeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectOptionHeightSample {
  @State optionHeightTest: Dimension = '100lpx'

  aboutToAppear(): void {
    loadComponentTestEntry(selectOptionHeightTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionHeight('100px')
        .id('selectOptionHeight1')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionHeight('100vp')
        .id('selectOptionHeight2')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionHeight('100fp')
        .id('selectOptionHeight3')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionHeight(this.optionHeightTest)
        .id('selectOptionHeight4')

      Button('SelectOptionHeight').onClick(() => {
        this.optionHeightTest = $r('app.string.option_height');
      })

    }.width('100%')
  }
}