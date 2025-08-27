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

class Opt implements SelectOption {
  public value: string = ''
  constructor(val: string) {
    this.value = val
  }
}

@Component
export struct DimensionUtil {
  @Link length: SheetSize | Length
  @State lengthType: string = '%'
  @State lengthTypeSheetSizeVal: number = 0
  @State lengthTypeLengthType: string = 'vp'
  @State lengthTypeLengthVal: number = 100
  controller: TextInputController = new TextInputController()
  private units: string[] = ['vp', 'px', '%', 'fp', 'lpx']
  @State items: SelectOption[] = []

  @Prop min: number = 0
  @Prop max: number = 100
  @State step: number = 1

  aboutToAppear(): void {
    this.items = this.units.map((item: string) => {
      return new Opt(item)
    })
  }

  build() {
    Row() {
      TextPicker({ range: this.units, selected: 0 })
        .width(100)
        .height(60)
        .selectedTextStyle({ font: { size: 15 } })
        .disappearTextStyle({ font: { size: 15 } })
        .canLoop(true)
        .textStyle({ font: { size: 15 } })
        .defaultPickerItemHeight(20)
        .onChange((value: string | string[], index: number | number[]) => {
          this.lengthTypeLengthType = value as string
          if (this.lengthTypeLengthType == 'vp') {
            this.length = this.lengthTypeLengthVal
          } else {
            this.length = this.lengthTypeLengthVal + this.lengthTypeLengthType
          }
        })

      Slider({
        value: this.lengthTypeSheetSizeVal,
        min: this.min,
        max: this.max,
        step: this.step,
        style: SliderStyle.OutSet
      })
        .width('70%')
        .onChange((value: number, mode: SliderChangeMode) => {
          this.lengthTypeLengthVal = value
          this.length = this.lengthTypeLengthVal + this.lengthTypeLengthType
        })
    }
  }
}

@Component
export struct MyInput {
  @Prop title: string
  @Link value: string

  controller: TextInputController = new TextInputController()

  build() {
    Row() {
      Text(this.title + ' : ')
        .width(100)
        .textAlign(TextAlign.End)
        .padding({ right: 20 })
      TextInput({ text: this.value, controller: this.controller })
        .placeholderColor(Color.Grey)
        .placeholderFont({ size: 14, weight: 400 })
        .caretColor(Color.Blue)
        .width(100)
        .fontColor(Color.Black)
        .onChange((value: string) => {
          this.value = value
        })
        .id(this.title)
    }
  }
}

@Component
export struct ShadowSelect {
  @Link shadowType: string
  @Link shadowStyle: ShadowStyle
  @Link shadowOption: ShadowOptions | undefined | null

  @State shadowVal: string = ''

  @Styles Card() {
    .width('90%')
    .padding(10)
    .shadow({
      radius: 10,
      offsetX: 5,
      offsetY: 5
    })
  }

  build() {
    Column() {
      Column() {
        Row() {
          Text('shadow : ')
            .fontColor(Color.Red)
          Text(this.shadowVal)
            .maxLines(20)
            .width('70%')
        }
        Column() {
          Row() {
            Text('shadow类型 : ')
            Select([
              { value: 'ShadowOptions'},
              { value: 'ShadowStyle' },
            ])
              .onSelect((index: number, value: string) => {
                this.shadowType = value
              })
          }

          if (this.shadowType == 'ShadowStyle') {
            Row() {
              Text('ShadowStyle')
              Select([
                { value: 'OUTER_DEFAULT_XS' },
                { value: 'OUTER_DEFAULT_SM' },
                { value: 'OUTER_DEFAULT_MD' },
                { value: 'OUTER_DEFAULT_LG' },
                { value: 'OUTER_FLOATING_SM' },
                { value: 'OUTER_FLOATING_MD' },
              ])
                .onSelect((index: number, value: string) => {
                  switch (value) {
                    case 'OUTER_DEFAULT_XS':
                      this.shadowStyle = ShadowStyle.OUTER_DEFAULT_XS
                      this.shadowVal = 'OUTER_DEFAULT_XS'
                      break
                    case 'OUTER_DEFAULT_SM':
                      this.shadowStyle = ShadowStyle.OUTER_DEFAULT_SM
                      this.shadowVal = 'OUTER_DEFAULT_SM'
                      break
                    case 'OUTER_DEFAULT_MD':
                      this.shadowStyle = ShadowStyle.OUTER_DEFAULT_MD
                      this.shadowVal = 'OUTER_DEFAULT_MD'
                      break
                    case 'OUTER_DEFAULT_LG':
                      this.shadowStyle = ShadowStyle.OUTER_DEFAULT_LG
                      this.shadowVal = 'OUTER_DEFAULT_LG'
                      break
                    case 'OUTER_FLOATING_SM':
                      this.shadowStyle = ShadowStyle.OUTER_FLOATING_SM
                      this.shadowVal = 'OUTER_FLOATING_SM'
                      break
                    case 'OUTER_FLOATING_MD':
                      this.shadowStyle = ShadowStyle.OUTER_FLOATING_MD
                      this.shadowVal = 'OUTER_FLOATING_MD'
                      break
                  }
                })
            }
          } else if (this.shadowType == 'ShadowOptions') {
            Row() {
              Text('ShadowOptions')
              Select([
                { value: '{ radius: 50, type: ShadowType.COLOR,' +
                  ' color: Color.Black, offsetX: 50, offsetY: 50, fill: true }' },
                { value: '{ radius: 50, type: ShadowType.BLUR,' +
                  ' color: \'#00FF00\', offsetX: 50, offsetY: 50, fill: false }' },
                { value: '{ radius: 50, type: ShadowType.COLOR,' +
                  ' color: ColoringStrategy.AVERAGE, offsetX: 50, offsetY: 50, fill: true }' },
                { value: '{ radius: 50, type: ShadowType.COLOR,' +
                  ' color: ColoringStrategy.INVERT, offsetX: 50, offsetY: 50, fill: true }' },
                { value: 'undefined' },
                { value: 'null' },
              ])
                .onSelect((index: number, value: string) => {
                  switch (value) {
                    case '{ radius: 50, type: ShadowType.COLOR,' +
                      ' color: Color.Black, offsetX: 50, offsetY: 50, fill: true }':
                      this.shadowOption = {
                        radius: 50,
                        type: ShadowType.COLOR,
                        color: Color.Black,
                        offsetX: 50,
                        offsetY: 50,
                        fill: true
                      }
                      this.shadowVal = '{ radius: 50, type: ShadowType.COLOR,' +
                        ' color: Color.Black, offsetX: 50, offsetY: 50, fill: true }'
                      break
                    case '{ radius: 50, type: ShadowType.BLUR,' +
                      ' color: \'#00FF00\', offsetX: 50, offsetY: 50, fill: false }':
                      this.shadowOption = {
                        radius: 50,
                        type: ShadowType.BLUR,
                        color: '#00FF00',
                        offsetX: 50,
                        offsetY: 50,
                        fill: false
                      }
                      this.shadowVal = '{ radius: 50, type: ShadowType.BLUR,' +
                        ' color: \'#00FF00\', offsetX: 50, offsetY: 50, fill: false }'
                      break
                    case '{ radius: 50, type: ShadowType.COLOR,' +
                      ' color: ColoringStrategy.AVERAGE, offsetX: 50, offsetY: 50, fill: true }':
                      this.shadowOption = {
                        radius: 50,
                        type: ShadowType.COLOR,
                        color: ColoringStrategy.AVERAGE,
                        offsetX: 50,
                        offsetY: 50,
                        fill: true
                      }
                      this.shadowVal = '{ radius: 50, type: ShadowType.COLOR,' +
                        ' color: ColoringStrategy.AVERAGE, offsetX: 50, offsetY: 50, fill: true }'
                      break
                    case '{ radius: 50, type: ShadowType.COLOR,' +
                      ' color: ColoringStrategy.INVERT, offsetX: 50, offsetY: 50, fill: true }':
                      this.shadowOption = {
                        radius: 50,
                        type: ShadowType.COLOR,
                        color: ColoringStrategy.INVERT,
                        offsetX: 50,
                        offsetY: 50,
                        fill: true
                      }
                      this.shadowVal = '{ radius: 50, type: ShadowType.COLOR,' +
                        ' color: ColoringStrategy.INVERT, offsetX: 50, offsetY: 50, fill: true }'
                      break
                    case 'undefined':
                      this.shadowOption = undefined
                      this.shadowVal = 'undefined'
                      break
                    case 'null':
                      this.shadowOption = null
                      this.shadowVal = 'null'
                      break
                  }
                })
            }
          }
        }
      }
    }
  }
}

@Component
export struct KeyboardAvoidModeSelect {
  @Link keyboardAvoidMode: number | undefined

  build() {
    Row() {
      Text('keyboardAvoidMode : ' + this.keyboardAvoidMode)
      TextPicker({
        range: [
          'Default',
          'None',
          'undefined'
        ],
        selected: 0
      })
        .width(100)
        .height(60)
        .selectedTextStyle({ font: { size: 15 } })
        .disappearTextStyle({ font: { size: 15 } })
        .canLoop(false)
        .textStyle({ font: { size: 15 } })
        .defaultPickerItemHeight(20)
        .onChange((value: string | string[], index: number | number[]) => {
          switch (value) {
            case 'Default':
              this.keyboardAvoidMode = KeyboardAvoidMode.DEFAULT
              break
            case 'None':
              this.keyboardAvoidMode = KeyboardAvoidMode.NONE
              break
            case 'undefined':
              this.keyboardAvoidMode = undefined
              break
            default:
              break
          }
        })
    }
  }
}