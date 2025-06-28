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
export function ButtonLevel8Builder(name: string, param: Object) {
  ButtonLevel8Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  label?: string,
}

class MyButtonStyle implements ContentModifier<ButtonConfiguration> {
  public x: number = 0
  public y: number = 0
  public selectedColor: Color = Color.Black

  constructor(x: number, y: number, colorType: Color) {
    this.x = x
    this.y = y
    this.selectedColor = colorType
  }

  applyContent(): WrappedBuilder<[ButtonConfiguration]> {
    return wrapBuilder(buildButton)
  }
}

class MyButtonStyle1 implements ContentModifier<ButtonConfiguration> {
  public x: number = 0
  public y: number = 0
  public selectedColor: Color = Color.Black

  constructor(x: number, y: number, colorType: Color) {
    this.x = x
    this.y = y
    this.selectedColor = colorType
  }

  applyContent(): WrappedBuilder<[ButtonConfiguration]> {
    return wrapBuilder(buildButton1)
  }
}

@Builder
function buildButton(config: ButtonConfiguration) {
  Column({ space: 30 }) {
    Text(config.label)
    Text(config.enabled ? 'enabled true' : 'enabled false')
    Text('圆圈状态' + (config.pressed ? '（ 按压 ）' : '（ 非按压 ）'))
      .key('TextTest1')
    Text('点击位置x坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).x.toFixed(0) : '0'))
    Text('点击位置y坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).y.toFixed(0) : '0'))
    Circle({ width: 50, height: 50 })
      .fill(config.pressed ? (config.contentModifier as MyButtonStyle).selectedColor : Color.Black)
      .key('CircleTest1')
      .onClick((event: ClickEvent) => {
        config.triggerClick(event.displayX, event.displayY)
      })
      .opacity(config.enabled ? 1 : 0.1)
  }
}

@Builder
function buildButton1(config: ButtonConfiguration) {
  Column({ space: 30 }) {
    Text(config.label)
    Text(config.enabled ? 'enabled true' : 'enabled false')
    Text('圆圈状态' + (config.pressed ? '（ 按压 ）' : '（ 非按压 ）'))
      .key('TextTest1')
    Text('点击位置x坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).x.toFixed(0) : '0'))
    Text('点击位置y坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).y.toFixed(0) : '0'))
    Circle({ width: 50, height: 50 })
      .fill(config.pressed ? (config.contentModifier as MyButtonStyle).selectedColor : Color.Black)
      .key('CircleTest1')
      .onClick((event: ClickEvent) => {
        config.triggerClick(event.displayX, event.displayY)
      })
      .opacity(config.enabled ? 1 : 0.1)
  }
}

@Entry
@Component
struct ButtonLevel8Example {
  pathStack: NavPathStack = new NavPathStack()
  @State buttonEnabled: boolean = true;
  @State positionX: number = 0
  @State positionY: number = 0
  @State state: boolean[] = [true, false]
  @State index: number = 0
  private sets: Array<setsObject> = [
    {
      label: 'Recommendation'
    },
    {
      label: 'The expert in anything was once a beginner.'
    },
    {
      label: '按\t钮测试%！ rrtt \r @#￥\n%……&*&*（））——+{}|、/\ButtonTestButtonTestButtonT'
    },
    {
      label: undefined
    },
    {
      label: 'Education is not the filling of a pail, but the lighting of a fire.'
    },
    {
      label: ''
    },
    {
      label: 'Success is not final, failure is not fatal: it is the courage to continue that counts.'
    }
  ]

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Divider()
        Row({ space: 2 }) {
          Text(`${this.index + 1}` + '/')
          Text(`${this.sets.length}`)
            .key('buttonTest01')

          MyComponent({
            title: 'Test++', func: () => {
              // 控制循环
              this.index++
              if (this.index == this.sets.length) {
                this.index = 0
              }
            }
          })

          MyComponent({
            title: 'Test--', func: () => {
              // 控制循环
              this.index--
              if (this.index == -1) {
                this.index = this.sets.length - 1
              }
            }
          })
        }

        Button(this.sets[this.index].label)
          .contentModifier(new MyButtonStyle(this.positionX, this.positionY, Color.Red))
          .onClick((event) => {
            console.info('changeganggeniubi: ' + event.displayX.toFixed(0) + ',' + event.displayY.toFixed(0))
            this.positionX = event.displayX
            this.positionY = event.displayY
          })
          .enabled(this.buttonEnabled)

        Button(this.sets[this.index].label)
          .contentModifier(new MyButtonStyle1(this.positionX, this.positionY, Color.Red))

        Button('undefined ' + this.sets[this.index].label)
          .contentModifier(undefined)

        Row() {
          Toggle({ type: ToggleType.Switch, isOn: true })
            .key('ToggleTest1')
            .onChange((value: boolean) => {
              if (value) {
                this.buttonEnabled = true
              } else {
                this.buttonEnabled = false
              }
            })
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .title('ButtonLevel8')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}