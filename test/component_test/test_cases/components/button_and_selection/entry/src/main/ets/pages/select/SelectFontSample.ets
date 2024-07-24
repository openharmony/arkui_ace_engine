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
import selectFontTest from '../MyTest/SelectFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct SelectFontSample {
  @State text: string = "Title"
  @State fontStrok: number | string = 100
  @State fontStrokNum: number | string = 20
  @State fontStyle: FontStyle = FontStyle.Normal

  aboutToAppear() {
    loadComponentTestEntry(selectFontTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      Select([{ value: 'select1' }]).value(this.text).font({ weight: FontWeight.Lighter }).id('selectFont1')
      Select([{ value: 'select1' }]).value(this.text).font({ weight: FontWeight.Normal }).id('selectFont2')
      Select([{ value: 'select1' }]).value(this.text).font({ weight: FontWeight.Regular, size: 0 }).id('selectFont3')
      Select([{ value: 'select1' }]).value(this.text).font({ weight: FontWeight.Medium, size: -1 }).id('selectFont4')
      Select([{ value: 'select1' }])
        .value(this.text)
        .font({ weight: FontWeight.Bold, size: $r('app.string.size') })
        .id('selectFont5')
      Select([{ value: 'select1' }]).value(this.text).font({
        weight: FontWeight.Bolder, size: 10,
        family: 'Arial'
      }).id('selectFont6')
      Select([{ value: 'select1' }]).value(this.text).font({
        weight: this.fontStrok,
        size: this.fontStrokNum,
        family: 'TESTFONT',
        style: this.fontStyle
      }).id('selectFont7')

      Button('SelectFont').onClick(() => {
        this.fontStrok = '200';
        this.fontStrokNum = '40';
        this.fontStyle = FontStyle.Italic;
      })
    }.width('100%')
  }
}