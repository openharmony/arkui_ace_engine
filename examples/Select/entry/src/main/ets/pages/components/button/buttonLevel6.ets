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
export function ButtonLevel6Builder(name: string, param: Object) {
  ButtonLevel6Example()
}

ThemeControl.setDefaultTheme(undefined);

interface case_states_object {
  title?: string,
  state?: boolean
}

interface HoverEffectObject {
  title?: string,
  style?: HoverEffect
}

@CustomDialog
struct MyDialog {
  controller: CustomDialogController

  build() {
    Column() {
      Button('按钮', { type: ButtonType.Normal, stateEffect: true })
        .borderRadius(8)
        .backgroundColor(0x317aff)
        .key('button002')
        .width(90)
        .onClick(() => {
          console.log('ButtonDialogShowInSubWindow Open ButtonType.Normal')
        })
        .margin({ bottom: 10 })
      Button('关闭弹窗')
        .onClick(() => {
          this.controller.close()
        }).backgroundColor(0x317aff)
    }
  }
}

@Component
struct ComponentA {
  @Prop text: string

  build() {
    Row({ space: 5 }) {
      Stack() {
        Image($r('app.media.app_icon'))
          .width(70)
          .fitOriginalSize(true)
          .borderWidth(1) //borderWidth真机上效果异常，显示到按钮外边了
        Text('住宅小区')
          .backgroundColor(Color.White)
      }

      Text(this.text)
        .backgroundColor(Color.White)
    }
  }
}

@Entry
@Component
struct ButtonLevel6Example {
  pathStack: NavPathStack = new NavPathStack()
  private message: string = 'Hello World'
  @State text: string = 'button'
  @State state?: boolean = undefined
  @State style?: HoverEffect = undefined
  @State width1: number = 100
  @State width2: number = 100
  private caseStates: Array<case_states_object> = [
    { title: 'false', state: false },
    { title: 'true', state: true },
    { title: 'undefined', state: undefined }
  ]
  private hoverEffect1: Array<HoverEffectObject> = [
    { title: 'Scale', style: HoverEffect.Scale },
    { title: 'None', style: HoverEffect.None },
    { title: 'undefined', style: HoverEffect.Highlight }
  ]
  private dialog = new CustomDialogController({
    builder: MyDialog(),
    showInSubWindow: true,
    autoCancel: false,
    cancel: () => {

    },
    closeAnimation: {
      duration: 350,
      onFinish: () => {

      }
    },
    alignment: DialogAlignment.Center,
    customStyle: true,
    backgroundColor: '#22000000',
    maskColor: '#ff0',
    isModal: true,
  })

  @Styles
  pressedStyle() {
    .borderWidth(2)
    .borderColor(Color.Red)
    .backgroundColor(Color.Green)
  }

  @Styles
  normalStyles() {
    .borderWidth(1)
    .borderColor(Color.Black)
    .backgroundColor(Color.Blue)
  }

  @Builder
  myBuilder(value: string) {
    Column({ space: 2 }) {
      ComponentA({ text: value + '' + this.text })
      TextInput({ placeholder: 'input' }).width(100).caretColor(Color.White) // 长按移动光标不灵敏
    }
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('Button-stateEffect效果、交互归一\nButton容器组合场景')
            .fontSize(7)
            .fontColor(0xCCCCCC)
            .width('100%')
          Button(this.message, { type: ButtonType.Normal, stateEffect: this.state })
            .width(this.width2)
            .id('normal_button')
            .onClick(() => {
              this.width2 = this.width2 - 10
            })
          Button(this.message, { type: ButtonType.Circle, stateEffect: this.state })
            .width(this.width1)
            .id('circle_button')
            .hoverEffect(this.style)
            .onClick(() => {
              this.width1 = this.width1 - 10
            })
          Button(this.message, { type: ButtonType.Capsule, stateEffect: this.state })
            .width(100)
            .id('capsule_button')
            .stateStyles({ pressed: this.pressedStyle, normal: this.normalStyles })
          Button({ stateEffect: this.state }) { // 作为容器时，点击效果只是背景色变了一点
            Row() {
              Image($r('app.media.app_icon'))
                .width(100)
                .height(100)
                .margin(10)
              Text('Education is not the filling of a pail, but the lighting of a fire.')//老框架上不裁剪
                .fontSize(20)//.margin({top: 20, bottom: 20}) //新框架上Button容器高怎么自适应，当前不显示
                .width(200)
                .backgroundColor('rgba(255,165,0,0.3)')
            }
          }
          .backgroundColor(Color.Pink)
          .margin(20)
          .clip(true)
          .id('container_button1')

          Button({ stateEffect: this.state }) {
            ComponentA({ text: this.text })
          }

          Button({ stateEffect: this.state }) {
            Column({ space: 5 }) {
              MyComponent({ title: 'MyComponent' })
              Text('Text')
                .backgroundColor(Color.White)
            }
            .margin(5)
          }
          .stateStyles({ pressed: this.pressedStyle, normal: this.normalStyles })
          .id('container_button2')

          Divider().strokeWidth('1px')
          Text('验证button容器内的文本是否可以动态修改：')
            .fontSize(7)
            .fontColor(0xCCCCCC)
            .width('100%')
          MyComponent({
            title: 'TestPU', func: () => {
              this.text = 'testPU'
            }
          })
          Divider()
            .strokeWidth('1px')

          Text('观察stateEffect UX效果====1.切换stateEffect：')
            .fontSize(7)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            ForEach(this.caseStates, (item: case_states_object) => {
              MyComponent({
                title: item.title, func: () => {
                  this.state = item.state
                }
              })
            }, (item: case_states_object) => item.title)
          }

          Text('HoverEffect切换效果')
            .fontSize(7)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            ForEach(this.hoverEffect1, (item: HoverEffectObject) => {
              MyComponent({
                title: item.title, func: () => {
                  this.style = item.style
                }
              })
            }, (item: HoverEffectObject) => item.title)
          }

          Divider()
            .strokeWidth('2px')

          Text('子窗口弹窗Button组件onChange事件触发')
            .fontSize(7)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row() {
            Button('弹出弹窗，内置Button组件')
              .onClick(() => {
                this.dialog.open()
              })
              .backgroundColor(0x317aff)
              .key('button001')
          }
        }
        .width(300)
        .borderWidth(2)
        .padding(5)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel6')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
