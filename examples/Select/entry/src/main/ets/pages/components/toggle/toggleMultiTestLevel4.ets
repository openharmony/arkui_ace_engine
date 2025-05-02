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

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ToggleMultiTestLevel4Builder(name: string, param: Object) {
  toggleMultiTestLevel4()
}

interface objSample {
  isOn?: boolean | undefined,
  enabled?: boolean | undefined,
  type?: ToggleType | undefined
}

class MySwitchStyle implements ContentModifier<ToggleConfiguration> {
  public selectedColor: Color = Color.White
  public lamp: string = 'string';

  constructor(selectedColor: Color, lamp: string) {
    this.selectedColor = selectedColor
    this.lamp = lamp;
  }

  applyContent(): WrappedBuilder<[ToggleConfiguration]> {
    return wrapBuilder(buildSwitch)
  }
}

class MySwitchStyle1 implements ContentModifier<ToggleConfiguration> {
  public selectedColor: Color = Color.White
  public lamp: string = 'string';

  constructor(selectedColor: Color, lamp: string) {
    this.selectedColor = selectedColor
    this.lamp = lamp;
  }

  applyContent(): WrappedBuilder<[ToggleConfiguration]> {
    return wrapBuilder(buildSwitch1)
  }
}

@Builder
function buildSwitch(config: ToggleConfiguration) {
  Column({ space: 10 }) {
    Circle({ width: 150, height: 150 })
      .fill(config.isOn ? (config.contentModifier as MySwitchStyle).selectedColor : Color.Blue)
    Row({ space: 4 }) {
      Button('蓝' + JSON.stringify((config.contentModifier as MySwitchStyle).lamp))
        .onClick(() => {
          config.triggerChange(false);
        })
        .key('Button1')
      Button('黄' + JSON.stringify((config.contentModifier as MySwitchStyle).lamp))
        .onClick(() => {
          config.triggerChange(true);
        })
        .key('Button2')
    }
  }
}

@Builder
function buildSwitch1(config: ToggleConfiguration) {
}

@Entry
@Component
struct toggleMultiTestLevel4 {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0;
  @State isOn: boolean | undefined = undefined;
  private testCase: Array<objSample> = [
    {
      isOn: true,
      enabled: true,
      type: ToggleType.Switch
    },
    {
      isOn: false,
      enabled: true,
      type: ToggleType.Switch
    },
    {
      isOn: undefined,
      enabled: true,
      type: ToggleType.Switch
    },
    {
      isOn: true,
      enabled: false,
      type: ToggleType.Switch
    },
    {
      isOn: undefined,
      enabled: undefined,
      type: ToggleType.Switch
    },
    {
      isOn: true,
      enabled: undefined,
      type: ToggleType.Switch
    },
    {
      isOn: true,
      enabled: true,
      type: ToggleType.Checkbox
    },
    {
      isOn: false,
      enabled: true,
      type: ToggleType.Checkbox
    },
    {
      isOn: undefined,
      enabled: true,
      type: ToggleType.Checkbox
    },
    {
      isOn: true,
      enabled: false,
      type: ToggleType.Checkbox
    },
    {
      isOn: undefined,
      enabled: undefined,
      type: ToggleType.Checkbox
    },
    {
      isOn: true,
      enabled: undefined,
      type: ToggleType.Checkbox
    },
    {
      isOn: true,
      enabled: true,
      type: ToggleType.Button
    },
    {
      isOn: false,
      enabled: true,
      type: ToggleType.Button
    },
    {
      isOn: undefined,
      enabled: true,
      type: ToggleType.Button
    },
    {
      isOn: true,
      enabled: false,
      type: ToggleType.Button
    },
    {
      isOn: undefined,
      enabled: undefined,
      type: ToggleType.Button
    },
    {
      isOn: true,
      enabled: undefined,
      type: ToggleType.Button
    },
  ]

  aboutToAppear(): void {
    this.isOn = this.testCase[this.index].isOn
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Row({ space: 4 }) {
          Text('${this.index + 1}' + '/')
            .fontSize(9)
            .fontColor(0xCCCCCC)
          Text('${this.testCase.length}')
            .key('paramSets_key')
            .fontSize(9)
            .fontColor(0xCCCCCC)
          MyComponent({
            title: 'Test ++', func: () => {

              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
              this.isOn = this.testCase[this.index].isOn
            }
          })

          MyComponent({
            title: 'Test --', func: () => {

              this.index--
              if (this.index <= -1) {
                this.index = this.testCase.length - 1
              }
              this.isOn = this.testCase[this.index].isOn
            }
          })
        }

        Toggle({ type: this.testCase[this.index].type, isOn: this.isOn })
          .enabled(this.testCase[this.index].enabled)
          .backgroundColor(Color.Red)
          .contentModifier(new MySwitchStyle(Color.Yellow, '灯'))
          .onChange((isOn: boolean) => {
            console.info('ToggleLog is:' + isOn)
            this.isOn = isOn
          })
        Toggle({ type: this.testCase[this.index].type, isOn: this.isOn })
          .enabled(this.testCase[this.index].enabled)
          .backgroundColor(Color.Red)
          .height(20)
          .width(30)
          .contentModifier(new MySwitchStyle1(Color.Yellow, '灯'))
          .onChange((isOn: boolean) => {
            console.info('ToggleLog is:' + isOn)
          })

        Toggle({ type: this.testCase[this.index].type, isOn: this.isOn })
          .enabled(this.testCase[this.index].enabled)
          .backgroundColor(Color.Green)
          .height(20)
          .width(30)
          .contentModifier(undefined)
          .key('undefined')

      }.width('100%')
    }
    .title('ToggleMultiTestLevel4')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}