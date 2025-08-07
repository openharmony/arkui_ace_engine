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

import { AttributeUpdater } from '@ohos.arkui.modifier';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function ButtonLevel9Builder(name: string, param: Object) {
  ButtonLevel9Example()
}

ThemeControl.setDefaultTheme(undefined);

class MyButtonModifier extends AttributeUpdater<ButtonAttribute, ButtonInterface> {
  initializeModifier(instance: ButtonAttribute): void {
  }
}

@Entry
@Component
struct ButtonLevel9Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  private modifier: MyButtonModifier = new MyButtonModifier()
  private modifier2: MyButtonModifier = new MyButtonModifier()
  private modifier3: MyButtonModifier = new MyButtonModifier()
  private modifier4: MyButtonModifier = new MyButtonModifier()
  private modifier5: MyButtonModifier = new MyButtonModifier()
  private modifier6: MyButtonModifier = new MyButtonModifier()
  private modifier7: MyButtonModifier = new MyButtonModifier()
  private modifier8: MyButtonModifier = new MyButtonModifier()
  private modifier9: MyButtonModifier = new MyButtonModifier()
  private modifier10: MyButtonModifier = new MyButtonModifier()
  private modifier11: MyButtonModifier = new MyButtonModifier()
  private modifier12: MyButtonModifier = new MyButtonModifier()
  private modifier13: MyButtonModifier = new MyButtonModifier()
  private modifier14: MyButtonModifier = new MyButtonModifier()
  private modifier15: MyButtonModifier = new MyButtonModifier()
  private modifier16: MyButtonModifier = new MyButtonModifier()
  @State type1: ButtonStyleMode = ButtonStyleMode.EMPHASIZED
  @State type2: ButtonType = ButtonType.Capsule
  @State str: ResourceStr | undefined = '绑定文本'
  @State caseBefore: ResourceStr = '前'
  @State case9: ResourceStr = '场景9'
  @State case10: ResourceStr = '场景10'
  @State case11: ResourceStr = '场景11'
  @State case12: ResourceStr = '场景12'
  @State case13: ResourceStr = '场景13'
  @State case14: ResourceStr = '场景14'
  @State case15: ResourceStr = '场景15'
  @State case16: ResourceStr = '场景16'
  @State value: number = 75

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 10 }) {
          Column({ space: 5 }) {
            Text('场景一，点击按钮清除文本内容,清除Option恢复重点按钮样式')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              type: ButtonType.Circle
            })
              .attributeModifier(this.modifier)
              .backgroundColor(Color.Green)
              .key('Button1')
              .onClick(() => {
                this.modifier.updateConstructorParams()
              })
          }

          Column() {
            Text('场景二，点击按钮清除文本内容,清除Option恢复重点按钮样式')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              type: ButtonType.Circle
            })
              .attributeModifier(this.modifier2)
              .backgroundColor(Color.Green)
              .key('Button2')
              .onClick(() => {
                this.modifier2.updateConstructorParams(undefined)
              })
          }

          Column() {
            Text('场景三，点击按钮切换文本内容')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前')
              .attributeModifier(this.modifier3)
              .backgroundColor(Color.Green)
              .key('Button3')
              .onClick(() => {
                this.modifier3.updateConstructorParams('后')
              })
          }

          Column() {
            Text('场景四，点击按钮文本不变,更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              type: ButtonType.Circle,
            })
              .attributeModifier(this.modifier4)
              .backgroundColor(Color.Green)
              .key('Button4')
              .onClick(() => {
                this.modifier4.updateConstructorParams({
                  role: ButtonRole.ERROR,
                })
              })
          }

          Column() {
            Text('场景五，点击按钮清除文本,更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', undefined)
              .attributeModifier(this.modifier5)
              .backgroundColor(Color.Green)
              .key('Button5')
              .onClick(() => {
                this.modifier5.updateConstructorParams(undefined, {
                  type: ButtonType.Circle,
                  stateEffect: true,
                  buttonStyle: ButtonStyleMode.NORMAL,
                  controlSize: ControlSize.SMALL,
                  role: ButtonRole.ERROR
                })
              })
          }

          Column() {
            Text('场景六，点击按钮更新文本,重置Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              role: ButtonRole.ERROR
            })
              .attributeModifier(this.modifier6)
              .backgroundColor(Color.Green)
              .key('Button6')
              .onClick(() => {
                this.modifier6.updateConstructorParams('后', undefined)
              })
          }

          Column() {
            Text('场景七，点击按钮更新文本,更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              type: ButtonType.Capsule,
              stateEffect: true,
              buttonStyle: ButtonStyleMode.EMPHASIZED,
              controlSize: ControlSize.SMALL,
              role: ButtonRole.ERROR
            })
              .attributeModifier(this.modifier7)
              .backgroundColor(Color.Green)
              .key('Button7')
              .onClick(() => {
                this.modifier7.updateConstructorParams('后', {
                  type: ButtonType.Circle,
                  stateEffect: true,
                  buttonStyle: ButtonStyleMode.NORMAL,
                  controlSize: ControlSize.SMALL,
                  role: ButtonRole.ERROR
                })
              })
          }

          Column() {
            Text('场景八，清除Label，清除Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button('前', {
              type: ButtonType.Circle,
              stateEffect: true,
              controlSize: ControlSize.SMALL,
              role: ButtonRole.ERROR,
              buttonStyle: ButtonStyleMode.NORMAL
            })
              .attributeModifier(this.modifier8)
              .backgroundColor(Color.Green)
              .key('Button8')
              .onClick(() => {
                this.modifier8.updateConstructorParams(undefined, undefined)
              })
          }

          Column() {
            Text('场景九，默认展示场景9字样，(带孩子节点，自身构造Label，Options不生效,下同)，不影响文本，清除Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button(this.caseBefore, {
              role: ButtonRole.ERROR
            }) {
              Text('场景9')
            }
            .backgroundColor(Color.Green)
            .attributeModifier(this.modifier9)
            .key('Button9')
            .onClick(() => {
              this.modifier9.updateConstructorParams()
            })
            .width(70)
          }

          Column() {
            Text('场景十，默认展示场景10字样，不影响文本，清除Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button({
              buttonStyle: ButtonStyleMode.NORMAL,
              role: ButtonRole.ERROR
            }) {
              Text(this.case10)
            }
            .attributeModifier(this.modifier10)
            .key('Button10')
            .onClick(() => {
              this.modifier10.updateConstructorParams(undefined)
            })
            .width(70)
          }

          Column() {
            Text('场景十一，默认展示场景11字样，点击无任何反应')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button(this.caseBefore) {
              Text(this.case11)
            }
            .attributeModifier(this.modifier11)
            .backgroundColor(Color.Green)
            .key('Button11')
            .onClick(() => {
              this.modifier11.updateConstructorParams('后')
            })
            .width(70)
          }

          Column() {
            Text('场景十二，默认展示场景12字样，不影响Label，更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button(this.caseBefore) {
              Text(this.case12)
            }
            .attributeModifier(this.modifier12)
            .backgroundColor(Color.Green)
            .key('Button12')
            .onClick(() => {
              this.modifier12.updateConstructorParams({
                type: ButtonType.Circle,
              })
            })
            .width(70)
          }

          Column() {
            Text('场景十三，默认展示场景13字样，不影响文本，更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button(this.case13) {
              Text(this.case13)
            }
            .attributeModifier(this.modifier13)
            .backgroundColor(Color.Green)
            .key('Button13')
            .onClick(() => {
              this.modifier13.updateConstructorParams(undefined, {
                type: ButtonType.Circle,
              })
            })
            .width(70)
          }

          Column() {
            Text('场景十四，默认展示场景14字样，不影响文本，清除Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button({
              type: ButtonType.Circle
            }) {
              Text(this.case14)
            }
            .attributeModifier(this.modifier14)
            .backgroundColor(Color.Green)
            .key('Button14')
            .onClick(() => {
              this.modifier14.updateConstructorParams('后', undefined)
            })
            .width(70)
          }

          Column() {
            Text('场景十五，默认展示场景15字样，不影响文本，更新Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button(this.case15) {
              Text(this.case15)
            }
            .attributeModifier(this.modifier15)
            .backgroundColor(Color.Green)
            .key('Button15')
            .onClick(() => {
              this.modifier15.updateConstructorParams('后', {
                type: ButtonType.Circle,
              })
            })
            .width(70)
          }

          Column() {
            Text('场景十六，默认展示场景16字样，点击不影响文本，清除Options')
              .fontSize(7)
              .fontColor(0xCCCCCC)
              .width('100%')
            Button({
              type: ButtonType.Circle
            }) {
              Text(this.case16)
            }
            .attributeModifier(this.modifier16)
            .backgroundColor(Color.Green)
            .key('Button16')
            .onClick(() => {
              this.modifier16.updateConstructorParams(undefined, undefined)
            })
            .width(70)
          }
        }
        .width('100%')
      }
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel9')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}