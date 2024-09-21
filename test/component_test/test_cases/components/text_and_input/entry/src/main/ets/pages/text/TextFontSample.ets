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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textFontTest from '../MyTest/TextFontTest'
import font from '@ohos.font';

@Entry
@Component
struct TextFontSample {
  @State index: number = 0
  @State familyValues: FontWeight[] =
    [FontWeight.Normal, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder, FontWeight.Regular]

  aboutToAppear() {
    font.registerFont({
      familyName: 'fontRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(textFontTest)
  }

  build() {
    Column() {
      Text('text')
        .font({
          size: 10,
          weight: 10,
          family: 'Arial',
          style: FontStyle.Normal
        })
        .id('textFont1')
      Text('text')
        .font({
          size: '20px',
          weight: "20",
          family: 'fontRawFile',
          style: FontStyle.Italic
        })
        .id('textFont2')
      Text('text')
        .font({ size: $r('app.string.text'), weight: FontWeight.Lighter })
        .id('textFont3')
      Text('text')
        .font({ weight: this.familyValues[this.index] })
        .id('textFont4')
      Button('TextFont')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}