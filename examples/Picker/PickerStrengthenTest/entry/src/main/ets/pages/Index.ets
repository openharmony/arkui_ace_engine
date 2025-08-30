/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Entry
@Component
struct TextPickerExample {
  private select: number = 1
  private range: string[] =
    ['appleapple', 'orangeorange', 'banana', 'watermelon', 'grapegrape', 'strawberry', 'qqq', 'www', 'eee', 'rrr',
      'ttt', 'yyy', 'uuu', 'iii', 'ooo', 'ppp', 'aaa', 'sss', 'ddd', 'fff', 'ggg', 'hhh', 'jjj', 'kkk']
  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: 'AAA',
      children: [{ text: 'a1', children: [{ text: 'a11' }, { text: 'a12' }, { text: 'a13' }] },
        { text: 'a2', children: [{ text: 'a21' }, { text: 'a22' }, { text: 'a23' }] }]
    },
    {
      text: 'BBB',
      children: [{ text: 'b1', children: [{ text: 'b11' }, { text: 'b12' }, { text: 'b13' }] },
        { text: 'b2', children: [{ text: 'b21' }, { text: 'b22' }, { text: 'b23' }] }]
    },
    {
      text: 'CCC',
      children: [{ text: 'c1', children: [{ text: 'c11' }, { text: 'c12' }, { text: 'c13' }] },
        { text: 'c2', children: [{ text: 'c21' }, { text: 'c22' }, { text: 'c23' }] }]
    }
  ]
  @State minVal: number = 20
  @State maxVal: number = 25
  @State overflow: TextOverflow = TextOverflow.Clip
  @State isDisabled: boolean = false
  @State jsonStr: string = ''
  @State isEnabled: boolean = true
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private pefruits: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.apfruits, this.orfruits, this.pefruits]

  build() {
    Scroll() {
      Column() {
        Row() {
          Button('min-' + this.minVal)
            .onClick(() => {
              this.minVal -= 2
            })
          Button('min+' + this.minVal)
            .onClick(() => {
              this.minVal += 2
            })
          Button('max-' + this.maxVal)
            .onClick(() => {
              this.maxVal -= 2
            })
          Button('max+' + this.maxVal)
            .onClick(() => {
              this.maxVal += 2
            })
        }

        Row() {
          Button('Clip')
            .onClick(() => {
              this.overflow = TextOverflow.Clip
            })
          Button('Ellipsis')
            .onClick(() => {
              this.overflow = TextOverflow.Ellipsis
            })
          Button('MARQUEE')
            .onClick(() => {
              this.overflow = TextOverflow.MARQUEE
            })
          Button('None')
            .onClick(() => {
              this.overflow = TextOverflow.None
            })
        }

        Button('disableTextStyleAnimation' + this.isDisabled)
          .onClick(() => {
            this.isDisabled = !this.isDisabled
          })
        Button('getInspectorByKey')
          .onClick(() => {
            this.jsonStr = getInspectorByKey('ttt')
          })

        TextPicker({ range: this.range, selected: this.select })
          .width(300)
          .id('ttt')
          .disableTextStyleAnimation(this.isDisabled)
          .gradientHeight(90)
          .defaultTextStyle({
            minFontSize: this.minVal,
            maxFontSize: this.maxVal,
            overflow: this.overflow,
            color: Color.Orange,
            font: {
              size: this.maxVal,
              weight: FontWeight.Bold,
              family: 'serif',
              style: FontStyle.Italic
            }
          })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('Picker item onChange, value: ' + value + ', index: ' + index)
          })
          .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
            console.info('Picker item onDidEnterSelectedArea, value: ' + value + ', index: ' + index)
          })
        Text(this.jsonStr)
        TextPicker({ range: this.cascade })
          .enabled(this.isEnabled)
          .key('TextPickerTextStyle_Normal')
          .canLoop(false)
          .opacity(0.5)
          .disableTextStyleAnimation(true)
          .gradientHeight(90)
          .defaultTextStyle({ minFontSize: 32, maxFontSize: 35, overflow: TextOverflow.Ellipsis })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('TextPicker 多列联动:onChange ' + JSON.stringify(value) + ', ' + 'index: ' +
            JSON.stringify(index))
          })
          .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
            console.info('TextPicker 多列联动:onDidEnterSelectedArea ' + JSON.stringify(value) + ', ' + 'index: ' +
            JSON.stringify(index))
          })

        TextPicker({ range: this.multi }).selectedIndex([1, 2, 1])
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('multi:onChange ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
          })
          .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
            console.info('multi:onDidEnterSelectedArea ' + JSON.stringify(value) + ', ' + 'index: ' +
            JSON.stringify(index))
          })

        Button('TextPickerDialog')
          .margin(20)
          .onClick(() => {
            this.getUIContext().showTextPickerDialog({
              range: this.range,
              selected: this.select,
              // canLoop: false,
              disableTextStyleAnimation: this.isDisabled,
              defaultTextStyle: {
                minFontSize: this.minVal,
                maxFontSize: this.maxVal,
                overflow: TextOverflow.Ellipsis,
                color: Color.Orange,
                font: {
                  size: 18,
                  weight: FontWeight.Bold,
                  family: 'serif',
                  style: FontStyle.Italic
                }
              },
              disappearTextStyle: { color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } },
              textStyle: { color: Color.Black, font: { size: 20, weight: FontWeight.Normal } },
              selectedTextStyle: { color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } },
              onChange: (TextPickerResult) => {
                console.info('Picker item onChange' + JSON.stringify(TextPickerResult))
              },
              onEnterSelectedArea: (TextPickerResult) => {
                console.info('Picker item onDidEnterSelectedArea' + JSON.stringify(TextPickerResult))
              }
            })
          })

        Button('enable' + this.isEnabled)
          .onClick(() => {
            this.isEnabled = !this.isEnabled
          })
      }
    }
  }
}
