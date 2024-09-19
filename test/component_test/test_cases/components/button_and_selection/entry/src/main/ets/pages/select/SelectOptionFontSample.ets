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
import selectOptionFontTest from '../MyTest/SelectOptionFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct SelectOptionFontSample {
  @State optionFontStrok: number | string = 100
  @State optionFontNum: number | string = 20
  @State optionFontStyle: FontStyle = FontStyle.Normal
  @State text: string = "Title"

  aboutToAppear() {
    loadComponentTestEntry(selectOptionFontTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Lighter })
        .id('selectOptionFont1')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Normal })
        .id('selectOptionFont2')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Regular })
        .id('selectOptionFont3')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Medium, size: 0 })
        .id('selectOptionFont4')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Bold, size: -1 })
        .id('selectOptionFont5')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({ weight: FontWeight.Bolder, size: $r('app.string.size'), family: 'Arial' })
        .id('selectOptionFont6')
      Select([{ value: 'select1' },
        { value: 'select2' },])
        .value(this.text)
        .optionFont({
          weight: this.optionFontStrok,
          size: this.optionFontNum,
          family: 'TESTFONT',
          style: this.optionFontStyle
        })
        .id('selectOptionFont7')

      Button('SelectOptionFont').onClick(() => {
        this.optionFontStrok = '200';
        this.optionFontNum = '40';
        this.optionFontStyle = FontStyle.Italic;
      })
    }.width('100%')
  }
}