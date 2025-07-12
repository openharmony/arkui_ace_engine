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

import { MyComponent } from '../base/MyComponent';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function RadioLevel4Builder(name: string, param: Object) {
  RadioLevel4Example()
}

ThemeControl.setDefaultTheme(undefined);

interface objSample {
  value?: string | undefined,
  checked?: boolean | undefined
}

class MyRadioStyle implements ContentModifier<RadioConfiguration> {
  public type: number = 0
  public checkedColor: Color = Color.Black

  constructor(numberType: number, colorType: Color) {
    this.type = numberType
    this.checkedColor = colorType
  }

  applyContent(): WrappedBuilder<[RadioConfiguration]> {
    return wrapBuilder(buildRadio)
  }
}

class EmptyRadioStyle implements ContentModifier<RadioConfiguration> {
  public type: number = 0
  public checkedColor: Color = Color.Black

  constructor(numberType: number, colorType: Color) {
    this.type = numberType
    this.checkedColor = colorType
  }

  applyContent(): WrappedBuilder<[RadioConfiguration]> {
    return wrapBuilder(emptybuildRadio)
  }
}

@Builder
function buildRadio(config: RadioConfiguration) {
  Column({ space: 30 }) {
    Row() {
      Text(config.value + (config.checked ? '（ true ）' : '（ false ）'))
    }

    Row({ space: 30 }) {
      Circle({ width: 50, height: 50 })
        .stroke(Color.Black)
        .fill(config.checked ? (config.contentModifier as MyRadioStyle).checkedColor : Color.White)
      Button(config.checked ? 'on' : 'off')
        .width(100)
        .type(config.checked ? (config.contentModifier as MyRadioStyle).type : ButtonType.Normal)
        .backgroundColor(0xAABBCC)
        .onClick(() => {
          if (config.checked) {
            config.triggerChange(false)
          } else {
            config.triggerChange(true)
          }
        })
    }
  }
}

@Builder
function emptybuildRadio(config: RadioConfiguration) {
}

@Entry
@Component
struct RadioLevel4Example {
  pathStack: NavPathStack = new NavPathStack()
  @State Enabled1: boolean = true;
  @State index: number = 0;
  @State checked1: boolean | undefined = undefined;
  @State checked2: boolean | undefined = undefined;
  private testCase: Array<objSample> = [
    {
      value: 'The expert in anything was once a beginner.',
      checked: true
    },
    {
      value: 'Don\'t watch the clock; do what it does. Keep going.',
      checked: true
    },
    {
      value: 'Don\'t watch the clock; do what it does. Keep going.',
      checked: true
    },
    {
      value: 'Success is not final, failure is not fatal: it is the courage to continue that counts.',
      checked: false
    },
    {
      value: '',
      checked: true
    },
    {
      value: 'Don\'t watch the clock; do what it does. Keep going.',
      checked: true
    },
    {
      value: 'Don\'t watch the clock; do what it does. Keep going.',
      checked: false
    },
    {
      value: undefined,
      checked: undefined
    },
    {
      value: 'Don\'t watch the clock; do what it does. Keep going.',
      checked: false
    },
    {
      value: 'Education is not the filling of a pail, but the lighting of a fire.',
      checked: false
    },
    {
      value: 'Education is not the filling of a pail, but the lighting of a fire.',
      checked: false
    },
    {
      value: 'Success is not final, failure is not fatal: it is the courage to continue that counts.',
      checked: false
    },
    {
      value: '',
      checked: false
    },
    {
      value: 'Education is not the filling of a pail, but the lighting of a fire.',
      checked: undefined
    },
    {
      value: 'Education is not the filling of a pail, but the lighting of a fire.',
      checked: undefined
    },
    {
      value: 'Success is not final, failure is not fatal: it is the courage to continue that counts.',
      checked: undefined
    },
    {
      value: 'Success is not final, failure is not fatal: it is the courage to continue that counts.',
      checked: true
    },
    {
      value: '',
      checked: undefined
    },
    {
      value: 'Radio2',
      checked: undefined
    },
  ]

  aboutToAppear(): void {
    this.checked1 = this.testCase[this.index].checked
    this.checked2 = this.testCase[this.index].checked
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Row({ space: 4 }) {
          Text(`${this.index + 1}` + `/`)
            .fontSize(9)
            .fontColor(0xCCCCCC)
          Text(`${this.testCase.length}`)
            .key('paramSets_key1')
            .fontSize(9)
            .fontColor(0xCCCCCC)

          MyComponent({
            title: 'Test ++', func: () => {
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
              this.checked1 = this.testCase[this.index].checked
              this.checked2 = this.testCase[this.index].checked
            }
          })

          MyComponent({
            title: 'Test --', func: () => {
              this.index--
              if (this.index <= -1) {
                this.index = this.testCase.length - 1
              }
              this.checked1 = this.testCase[this.index].checked
              this.checked2 = this.testCase[this.index].checked
            }
          })
        }

        Row() {
          Toggle({ type: ToggleType.Switch, isOn: true })
            .onChange((value: boolean) => {
              if (value) {
                this.Enabled1 = true
              } else {
                this.Enabled1 = false
              }
            })
            .key('toggle1')
        }

        Row() {
          Radio({ value: this.testCase[this.index].value, group: 'radioGroup' })
            .contentModifier(new EmptyRadioStyle(1, Color.Red))// .checked(this.checked1)
            .width(200)
            .height(100)
            .enabled(this.Enabled1)
            .backgroundColor(Color.Yellow)
            .onChange((isChecked: boolean) => {
              console.info('RadioChange1 is: ' + isChecked)
            })
          Radio({ value: this.testCase[this.index].value, group: 'radioGroup1' })
            .contentModifier(undefined)
            .key('undefined')
        }

        Row() {
          Radio({ value: this.testCase[this.index].value, group: 'radioGroup' })
            .checked($$this.checked1)
            .width(300)
            .height(150)
            .contentModifier(new MyRadioStyle(1, Color.Red))
            .enabled(this.Enabled1)
            .backgroundColor(Color.Red)
            .onChange((isChecked: boolean) => {
              console.info('RadioChange1 is: ' + isChecked)
            })
        }

        Row() {
          Radio({ value: 'Radio2', group: 'radioGroup1' })
            .checked(this.checked2)
            .width(300)
            .height(150)
            .contentModifier(new MyRadioStyle(2, Color.Green))
            .enabled(this.Enabled1)
            .backgroundColor(Color.Orange)
            .onChange((isChecked: boolean) => {
              console.info('RadioChange2 is: ' + isChecked)
              this.checked2 = isChecked
            })
        }
      }
    }
    .title('RadioLevel4')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}