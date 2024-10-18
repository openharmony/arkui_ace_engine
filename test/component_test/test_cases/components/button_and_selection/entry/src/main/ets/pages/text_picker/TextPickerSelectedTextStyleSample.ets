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
import textPickerSelectedTextStyleTest from '../MyTest/TextPickerSelectedTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct TextPickerSelectedTextStyleSample {
  @State selectedTextColor: ResourceColor = 'rgb(142, 255, 101)'
  @State selectedTextStrok: number | string = 50
  @State selectedTextSty: FontStyle = FontStyle.Normal
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']

  aboutToAppear() {
    loadComponentTestEntry(textPickerSelectedTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          color: Color.Green
        }).height(200).width(190).id('textPickerSelectedTextStyle1')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          color: 0xa52a2a
        }).height(200).width(190).id('textPickerSelectedTextStyle2')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          color: this.selectedTextColor
        }).height(200).width(190).id('textPickerSelectedTextStyle3')
      }

      Column() {
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle4')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle5')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle6')
      }

      Column() {
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle7')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Bold
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle8')
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: FontWeight.Bolder,
            size: $r('app.string.size'),
            family: 'Arial'
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle9')
      }

      Column() {
        TextPicker({ range: this.apfruits }).selectedTextStyle({
          font: {
            weight: this.selectedTextStrok,
            size: this.selectedTextStrok,
            family: 'TESTFONT',
            style: this.selectedTextSty
          }
        }).height(200).width(190).id('textPickerSelectedTextStyle10')
        Button('TextPickerSelectedTextStyle1').onClick(() => {
          this.selectedTextColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('TextPickerSelectedTextStyle2').onClick(() => {
          this.selectedTextStrok = '200';
          this.selectedTextSty = FontStyle.Italic;
        })
      }
    }.width('100%')
  }
}