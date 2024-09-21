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
import textPickerDisappearTextStyleTest from '../MyTest/TextPickerDisappearTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct TextPickerDisappearTextStyleSample {
  @State disappearTextColor: ResourceColor = 'rgb(142, 255, 101)'
  @State disappearTextStrok: number | string = 50
  @State disappearTextSty: FontStyle = FontStyle.Normal
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']

  aboutToAppear() {
    loadComponentTestEntry(textPickerDisappearTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          color: Color.Green
        }).height(200).width(190).id('textPickerDisappearTextStyle1')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          color: 0xa52a2a
        }).height(200).width(190).id('textPickerDisappearTextStyle2')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          color: this.disappearTextColor
        }).height(200).width(190).id('textPickerDisappearTextStyle3')
      }

      Column() {
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle4')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle5')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle6')
      }

      Column() {
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle7')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Bold
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle8')
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: FontWeight.Bolder,
            size: $r('app.string.size'),
            family: 'Arial'
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle9')
      }

      Column() {
        TextPicker({ range: this.apfruits }).disappearTextStyle({
          font: {
            weight: this.disappearTextStrok,
            size: this.disappearTextStrok,
            family: 'TESTFONT',
            style: this.disappearTextSty
          }
        }).height(200).width(190).id('textPickerDisappearTextStyle10')
        Button('TextPickerDisappearTextStyle1').onClick(() => {
          this.disappearTextColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('TextPickerDisappearTextStyle2').onClick(() => {
          this.disappearTextStrok = '200';
          this.disappearTextSty = FontStyle.Italic;
        })
      }
    }.width('100%')
  }
}