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
import selectOptionWidthTest from '../MyTest/SelectOptionWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SelectOptionWidthSample {
  @State optionNum: Dimension = '100lpx'
  @State optionWidthTest: OptionWidthMode = OptionWidthMode.FIT_CONTENT

  aboutToAppear(): void {
    loadComponentTestEntry(selectOptionWidthTest)
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionWidth('100px')
        .id('selectOptionWidth1')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionWidth('100vp')
        .id('selectOptionWidth2')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionWidth('100fp')
        .id('selectOptionWidth3')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionWidth(this.optionNum)
        .id('selectOptionWidth4')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .optionWidth(this.optionWidthTest)
        .id('selectOptionWidth5')

      Button('SelectOptionWidth').onClick(() => {
        this.optionNum = $r('app.string.option_num')
        this.optionWidthTest = OptionWidthMode.FIT_TRIGGER;
      })
    }.width('100%')
  }
}