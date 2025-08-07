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
export function CheckboxLevel4Builder(name: string, param: Object) {
  CheckboxLevel4Example()
}

ThemeControl.setDefaultTheme(undefined);

interface objSample {
  name?: string | undefined,
  select?: boolean | undefined
}

class MyCheckboxStyle implements ContentModifier<CheckBoxConfiguration> {
  public selectedColor: Color = Color.White

  constructor(selectedColor: Color) {
    this.selectedColor = selectedColor;
  }

  applyContent(): WrappedBuilder<[CheckBoxConfiguration]> {
    return wrapBuilder(buildCheckbox)
  }
}

class MyCheckboxStyle1 implements ContentModifier<CheckBoxConfiguration> {
  public selectedColor: Color = Color.White

  constructor(selectedColor: Color) {
    this.selectedColor = selectedColor;
  }

  applyContent(): WrappedBuilder<[CheckBoxConfiguration]> {
    return wrapBuilder(buildCheckbox1)
  }
}

@Builder
function buildCheckbox(config: CheckBoxConfiguration) {
  Column({ space: 10 }) {
    Text(config.name + (config.selected ? '（ 选中 ）' : '（ 非选中 ）'))
      .width('90%').height(150).key('text11')
    Text(config.enabled ? 'enabled true' : 'enabled false')
    Shape() {
      Path()
        .width(100)
        .height(100)
        .commands('M100 0 L0 100 L50 200 L150 200 L200 100 Z')
        .fillOpacity(0)
        .strokeWidth(3)
        .onClick(() => {
          if (config.selected) {
            config.triggerChange(false)
          } else {
            config.triggerChange(true)
          }
        })
        .opacity(config.enabled ? 1 : 0.1)
      Path()
        .width(10)
        .height(10)
        .commands('M50 0 L100 100 L0 100 Z')
        .visibility(config.selected ? Visibility.Visible : Visibility.Hidden)
        .fill(config.selected ? (config.contentModifier as MyCheckboxStyle).selectedColor : Color.Black)
        .stroke((config.contentModifier as MyCheckboxStyle).selectedColor)
        .margin({ left: 11, top: 10 })
        .opacity(config.enabled ? 1 : 0.1)
    }
    .width(300)
    .height(200)
    .viewPort({
      x: 0,
      y: 0,
      width: 310,
      height: 310
    })
    .strokeLineJoin(LineJoinStyle.Miter)
    .strokeMiterLimit(5)
  }.width('100%').height('60%')
}

@Builder
function buildCheckbox1(config: CheckBoxConfiguration) {
}

@Entry
@Component
struct CheckboxLevel4Example {
  pathStack: NavPathStack = new NavPathStack()
  @State checkboxEnabled: boolean = true;
  @State index: number = 0;
  @State select1: boolean | undefined = undefined;
  private testCase: Array<objSample> = [
    {
      name: 'checkBoxOne',
      select: true
    },
    {
      name: 'checkBoxTwo',
      select: true
    },
    {
      name: 'checkBoxThree',
      select: false
    },
    {
      name: 'Success is not final, failure is not fatal: it is the courage to continue that counts.\nSuccess is not final, failure is not fatal: it is the courage to continue that counts.',
      select: true
    },
    {
      name: '',
      select: true
    },
    {
      name: 'The expert in anything was once a beginner.',
      select: false
    },
    {
      name: undefined,
      select: undefined
    },
    {
      name: 'The expert in anything was once a beginner.',
      select: false
    },
    {
      name: 'The expert in anything was once a beginner.',
      select: true
    },
    {
      name: 'Success is not final, failure is not fatal: it is the courage to continue that counts.\nSuccess is not final, failure is not fatal: it is the courage to continue that counts.',
      select: false
    },
    {
      name: '',
      select: false
    },
    {
      name: 'Don\'t watch the clock; do what it does. Keep going.',
      select: undefined
    },
    {
      name: 'Don\'t watch the clock; do what it does. Keep going.',
      select: undefined
    },
    {
      name: 'The expert in anything was once a beginner.',
      select: undefined
    },
    {
      name: 'Education is not the filling of a pail, but the lighting of a fire.\nEducation is not the filling of a pail, but the lighting of a fire.',
      select: true
    },
    {
      name: '',
      select: undefined
    },
  ]

  aboutToAppear(): void {
    this.select1 = this.testCase[this.index].select
  }

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Column({ space: 8 }) {
          Row({ space: 4 }) {
            Text(`${this.index + 1}` + `/`)
              .fontSize(9)
              .fontColor(0xCCCCCC)
            Text(`${this.testCase.length}`)
              .key('paramSets_key')
              .fontSize(9)
              .fontColor(0xCCCCCC)

            MyComponent({
              title: 'Test ++', func: () => {
                this.index++
                if (this.index == this.testCase.length) {
                  this.index = 0
                }
                this.select1 = this.testCase[this.index].select
              }
            })

            MyComponent({
              title: 'Test --', func: () => {
                this.index--
                if (this.index <= -1) {
                  this.index = this.testCase.length - 1
                }
                this.select1 = this.testCase[this.index].select
              }
            })
          }

          Row() {
            Toggle({ type: ToggleType.Switch, isOn: true })
              .onChange((value: boolean) => {
                if (value) {
                  this.checkboxEnabled = true
                } else {
                  this.checkboxEnabled = false
                }
              })
              .key('toggle1')
          }
        }

        Checkbox({ name: this.testCase[this.index].name, group: 'checkboxGroup' })
          .select(this.select1)
          .contentModifier(new MyCheckboxStyle(Color.Red))
          .onChange((value: boolean) => {
            console.info('Checkbox change is' + value)
            this.select1 = value
          })
          .enabled(this.checkboxEnabled)
          .height('60%')

        Checkbox({ name: this.testCase[this.index].name, group: 'checkboxGroup' })
          .select(this.select1)
          .contentModifier(new MyCheckboxStyle1(Color.Red))
          .onChange((value: boolean) => {
            console.info('Checkbox change is' + value)
          })
          .enabled(this.checkboxEnabled)
        Checkbox({ name: 'box1', group: 'checkboxGroup1' })
          .contentModifier(undefined)
          .onChange((value: boolean) => {
            console.info('Checkbox change is' + value)
          })
          .width(60)
          .responseRegion({
            x: 0,
            y: 0,
            width: '50%',
            height: '100%'
          })
          .key('Checkbox0001')
      }
    }
    .title('CheckboxLevel4')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}