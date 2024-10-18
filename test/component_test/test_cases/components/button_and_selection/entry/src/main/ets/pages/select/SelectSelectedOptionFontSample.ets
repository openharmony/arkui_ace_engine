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
import selectSelectedOptionFontTest from '../MyTest/SelectSelectedOptionFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct SelectSelectedOptionFontSample {
  @State selectedOpFontStrok: number | string = 100
  @State selectedOpFontNum: number | string = 20
  @State selectedOpFontStyle: FontStyle = FontStyle.Normal

  aboutToAppear() {
    loadComponentTestEntry(selectSelectedOptionFontTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({ weight: FontWeight.Lighter }).id('selectSelectedOptionFont1')
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({ weight: FontWeight.Normal }).id('selectSelectedOptionFont2')
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({ weight: FontWeight.Regular }).id('selectSelectedOptionFont3')
      Select([{ value: 'select1' },
        { value: 'select2' }])
        .selectedOptionFont({ weight: FontWeight.Medium, size: 0 })
        .id('selectSelectedOptionFont4')
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({ weight: FontWeight.Bold, size: -1 }).id('selectSelectedOptionFont5')
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({
        weight: FontWeight.Bolder,
        size: $r('app.string.size'), family: 'Arial'
      }).id('selectSelectedOptionFont6')
      Select([{ value: 'select1' },
        { value: 'select2' }]).selectedOptionFont({
        weight: this.selectedOpFontStrok,
        size: this.selectedOpFontNum,
        family: 'TESTFONT',
        style: this.selectedOpFontStyle
      }).id('selectSelectedOptionFont7')

      Button('SelectSelectedOptionFont').onClick(() => {
        this.selectedOpFontStrok = '200';
        this.selectedOpFontNum = '40';
        this.selectedOpFontStyle = FontStyle.Italic;
      })
    }.width('100%')
  }
}