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

@Builder
export function SelectOnSelectBuilder(name: string, param: Object) {
  OnSelectExample()
}

@Component
struct OnSelectExample {
  pathStack: NavPathStack = new NavPathStack()
  @State connectType1: number = 0
  @State connectType2: number = 0
  @State connectType3: number = 0
  @State selectOption1: SelectOption[] = []
  @State selectOption2: SelectOption[] = [{ value: '' }]
  @State selectOption3: SelectOption[] = []
  @State selectValue: string = ''

  aboutToAppear(): void {
    this.selectOption1 =
      [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]

    setTimeout(() => {
      this.selectOption2 =
        [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]

      this.selectOption3 =
        [{ value: 'TCP' }, { value: 'UDP' }, { value: 'Bluetooth' }, { value: 'USB' }, { value: 'MQTT' }]
    }, 2000)
  }

  build() {
    NavDestination() {
      Column({ space: 20 }) {
        Text('正常显示，选项在显示前赋值')
          .width('100%')
        Select(this.selectOption1)
          .selected(this.connectType1)
          .value(this.selectOption1[this.connectType1].value)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number, text?: string | undefined) => {
            this.connectType1 = index
          })
          .width('100%')

        Text('正常显示，选项在显示前赋值[{ value: \'\' }]，后在aboutToAppear中延迟2秒赋值')
          .width('100%')
          .fontColor(Color.Orange)
        Select(this.selectOption2)
          .selected(this.connectType2)
          .value(this.selectOption2[this.connectType2].value)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number, text?: string | undefined) => {
            this.connectType2 = index
          })
          .width('100%')

        Text('选项在显示前赋值[]，后在aboutToAppear中延迟2秒赋值')
          .width('100%')
          .fontColor(Color.Red)
        Select(this.selectOption3)
          .selected(this.connectType3)
          .value(this.selectValue)
          .font({ size: 16 })
          .fontColor($r('sys.color.font_primary'))
          .selectedOptionFont({ size: 16 })
          .optionFont({ size: 16 })
          .optionWidth(OptionWidthMode.FIT_TRIGGER)
          .optionHeight(300)
          .borderRadius(10)
          .onSelect((index: number, text?: string | undefined) => {
            this.connectType3 = index
            if (text != undefined) {
              this.selectValue = text
            }
          })
          .width('100%')
      }
      .padding(20)
      .height('100%')
      .width('100%')
    }
    .title('SelectOnSelect')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { OnSelectExample };