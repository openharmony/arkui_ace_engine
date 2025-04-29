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

class MyButtonStyle implements ContentModifier<ButtonConfiguration> {
  public x: number = 0;
  public y: number = 0;
  public selectedColor: Color = Color.Black;

  constructor(x: number, y: number, colorType: Color) {
    this.x = x;
    this.y = y;
    this.selectedColor = colorType;
  }

  applyContent(): WrappedBuilder<[ButtonConfiguration]> {
    return wrapBuilder(buildButton1);
  }
}

@Builder
export function ButtonCustomBuilder(name: string, param: Object) {
  ButtonCustomExample()
}

@Builder
function buildButton1(config: ButtonConfiguration) {
  Column({ space: 30 }) {
    Text(config.enabled ? 'enabled true' : 'enabled false')
    Text('圆圈状态' + (config.pressed ? '（ 按压 ）' : '（ 非按压 ）'))
    Text('点击位置x坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).x : '0'))
    Text('点击位置y坐标：' + (config.enabled ? (config.contentModifier as MyButtonStyle).y : '0'))
    Circle({ width: 50, height: 50 })
      .fill(config.pressed ? (config.contentModifier as MyButtonStyle).selectedColor : Color.Black)
      .gesture(
        TapGesture({ count: 1 }).onAction((event: GestureEvent) => {
          config.triggerClick(event.fingerList[0].localX, event.fingerList[0].localY)
        })).opacity(config.enabled ? 1 : 0.1)
  }
}

@Entry
@Component
struct ButtonCustomExample {
  pathStack: NavPathStack = new NavPathStack()
  @State buttonEnabled: boolean = true;
  @State positionX: number = 0;
  @State positionY: number = 0;
  @State state: boolean[] = [true, false];
  @State index: number = 0;

  build() {
    NavDestination() {
      Column() {
        Button('OK')
          .contentModifier(new MyButtonStyle(this.positionX, this.positionY, Color.Red))
          .onClick((event) => {
            console.info('change' + JSON.stringify(event));
            this.positionX = event.displayX;
            this.positionY = event.displayY;
          }).enabled(this.buttonEnabled)
        Row() {
          Toggle({ type: ToggleType.Switch, isOn: true }).onChange((value: boolean) => {
            if (value) {
              this.buttonEnabled = true;
            } else {
              this.buttonEnabled = false;
            }
          })
            .margin({ left: -80 })
        }
      }
      .height('100%')
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .title('ButtonCustom')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}