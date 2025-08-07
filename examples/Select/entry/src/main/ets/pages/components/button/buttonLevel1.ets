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
export function ButtonLevel1Builder(name: string, param: Object) {
  ButtonLevel1Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  label1?: string,
  label2?: string | Resource,
  type?: ButtonType,
  role?: ButtonRole,
  buttonStyle?: ButtonStyleMode,
  controlSize?: ControlSize,
  backgroundColor?: ResourceColor
}

@Entry
@Component
struct ButtonLevel1Example {
  pathStack: NavPathStack = new NavPathStack()
  @State label1?: string = 'Hello World'
  @State label2?: Resource | string = undefined
  @State type?: ButtonType = ButtonType.Capsule
  @State buttonStyle?: ButtonStyleMode = undefined
  @State controlSize?: ControlSize = undefined
  @State role?: ButtonRole = undefined
  @State backgroundColorStyle?: ResourceColor = undefined
  private index: number = 0
  private lastIndex: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  private sets: Array<setsObject> = [
    {
      label1: 'z',
      label2: $r('app.string.app_name'),
      type: ButtonType.ROUNDED_RECTANGLE,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: ControlSize.NORMAL,
      role: ButtonRole.NORMAL
    },
    {
      label1: 'z',
      label2: $r('app.string.app_name'),
      type: ButtonType.Circle,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: ControlSize.NORMAL,
      role: ButtonRole.NORMAL
    },
    {
      label1: 'ButtonTestButtonTestButtonT',
      label2: undefined,
      type: undefined,
      buttonStyle: ButtonStyleMode.NORMAL,
      controlSize: ControlSize.SMALL,
      role: ButtonRole.ERROR
    },
    {
      label1: 'z',
      label2: $r('app.string.app_name'),
      type: ButtonType.Circle,
      buttonStyle: undefined,
      controlSize: ControlSize.NORMAL,
      role: 0
    },
    {
      label1: 'z',
      label2: $r('app.string.app_name'),
      type: ButtonType.Circle,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: undefined,
      role: 1
    },
    {
      label1: '按\t钮测试%！ rrtt \r @#￥\n%……&*&*（））——+{}|、/\ButtonTestButtonTestButtonT',
      label2: $r('app.string.string_long'),
      type: ButtonType.Normal,
      buttonStyle: ButtonStyleMode.NORMAL,
      controlSize: ControlSize.NORMAL,
      role: 2
    },
    {
      label1: undefined,
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: ButtonStyleMode.TEXTUAL,
      controlSize: ControlSize.NORMAL,
      role: -100
    },
    {
      label1: undefined,
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: ButtonStyleMode.NORMAL,
      controlSize: ControlSize.NORMAL,
      role: undefined
    },
    {
      label1: 'Don\'t watch the clock; do what it does. Keep going.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: ControlSize.NORMAL,
      role: 100000
    },
    {
      label1: 'Education is not the filling of a pail, but the lighting of a fire.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: undefined,
      controlSize: ControlSize.NORMAL
    },
    {
      label1: 'Education is not the filling of a pail, but the lighting of a fire.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: undefined
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: undefined,
      controlSize: undefined
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: undefined,
      controlSize: undefined,
      backgroundColor: Color.Red
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: 3,
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      controlSize: undefined,
      backgroundColor: Color.Red
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: ButtonType.Capsule,
      buttonStyle: 1,
      controlSize: undefined,
      backgroundColor: '#DC143C'
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: 2,
      buttonStyle: ButtonStyleMode.TEXTUAL,
      controlSize: undefined,
      backgroundColor: $r('app.color.backgroundColor')
    },
    {
      label1: 'The expert in anything was once a beginner.',
      label2: $r('app.string.app_name'),
      type: 2,
      buttonStyle: 10000,
      controlSize: ControlSize.NORMAL, //controlSize不支持枚举异常值类型
    }
  ]

  private setParam(): void {
    // 1. 参数赋值
    this.label1 = this.sets[this.index].label1
    this.label2 = this.sets[this.index].label2
    this.type = this.sets[this.index].type
    this.buttonStyle = this.sets[this.index].buttonStyle
    this.controlSize = this.sets[this.index].controlSize
    this.role = this.sets[this.index].role
    this.backgroundColorStyle = this.sets[this.index].backgroundColor
    // 2. 参数打印
    this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
      '\nlabel1: ' + this.label1 + '\nlabel2: ' + this.label2 + '\ntype：' + this.type + '\nbuttonStyle：' +
    this.buttonStyle + '\ncontrolSize：' + this.controlSize + '\nrole：' + this.role
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('切换测试参数,显示参数=' + this.show)
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .onClick(() => {
              this.show = !this.show
              this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
                '\nlabel1: ' + this.label1 + '\nlabel2: ' + this.label2 + '\ntype：' + this.type + '\nbuttonStyle：' +
              this.buttonStyle + '\ncontrolSize：' + this.controlSize + '\nrole：' + this.role
            })

          Row({ space: 2 }) {
            Text(`${this.sets.length}`)
              .key('button00')
            MyComponent({
              title: 'Test++', func: () => {
                this.setParam()
                this.lastIndex = this.index
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
                this.setParam()
                this.lastIndex = this.index
              }
            })
          }

          if (this.show) {
            Text(this.info)
              .fontSize(9)
              .width('60%')
          }

          Divider().strokeWidth('1px')
          // 优先级测试，预期属性设置高于接口入参
          Text('Button值测试;Button type优先级测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Row({ space: 2 }) {
            Button({ type: ButtonType.Normal }) //预期为矩形无内容按钮
            Button('', { type: undefined }).borderRadius(10) //预期为圆角矩形无内容按钮
            Button('aaa', { type: ButtonType.Circle })
              .type(undefined)
              .borderRadius(10) //圆角矩形型
            Button('bbb', { type: undefined })
              .type(ButtonType.Normal) // 矩形
            Button('ccc', { type: undefined })
              .type(undefined)
              .borderRadius(10) //圆角矩形按钮型
            Button('ddd', { type: ButtonType.Capsule })
              .type(ButtonType.Circle) // 圆形
          }
          .margin(5)
          .padding(5)
          .backgroundColor(Color.Pink)

          Text('buttonStyle优先级测试;controlSize优先级测试;role优先级测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Row({ space: 2 }) {
            Button('eee', { buttonStyle: ButtonStyleMode.NORMAL })
              .buttonStyle(ButtonStyleMode.EMPHASIZED) //强调按钮（用于强调当前操作）
            Button('fff', { buttonStyle: ButtonStyleMode.TEXTUAL })
              .buttonStyle(ButtonStyleMode.EMPHASIZED) //强调按钮（用于强调当前操作）
            Button('ggg', { buttonStyle: ButtonStyleMode.NORMAL })
              .buttonStyle(ButtonStyleMode.TEXTUAL) //文本按钮（纯文本，无背景颜色）
            Button('hhh', { controlSize: ControlSize.SMALL }).controlSize(ControlSize.NORMAL) //正常尺寸按钮
            Button('iii', { controlSize: ControlSize.NORMAL }).controlSize(ControlSize.SMALL) //小尺寸按钮
            Button('jjj', { role: ButtonRole.NORMAL }).role(ButtonRole.ERROR) //警示按钮
            Button('kkk', { role: 1 }).role(0) //正常按钮
          }.margin(5).padding(5).backgroundColor(Color.Pink)

          Text('Button label和type以及buttonStyle，controlSize,role动态修改测试（组件宽高固定）')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 2 }) {
            Button(this.label1, {
              type: this.type,
              buttonStyle: this.buttonStyle,
              controlSize: this.controlSize,
              role: this.role
            })
              .width('20%')
              .borderWidth(1)
              .backgroundColor(this.backgroundColorStyle)
            Button(this.label1, {
              type: this.type,
              buttonStyle: this.buttonStyle,
              controlSize: this.controlSize,
              role: this.role
            })
              .width('20%')
              .aspectRatio(0.5)
              .borderWidth(1)
              .backgroundColor(this.backgroundColorStyle)
            Button(this.label2)
              .type(this.type)
              .buttonStyle(this.buttonStyle)
              .controlSize(this.controlSize)
              .role(this.role)
              .width('20%')
              .height(100)
              .borderWidth(1)
              .backgroundColor(this.backgroundColorStyle)
            Button(this.label2)
              .type(this.type)
              .buttonStyle(this.buttonStyle)
              .controlSize(this.controlSize)
              .role(this.role)
              .width('20%')
              .aspectRatio(2)
              .borderWidth(1)
              .backgroundColor(this.backgroundColorStyle) // 配合aspectRatio使用，type不能动态修改
          }
          .margin(5)
          .padding(5)
          .backgroundColor(Color.Pink)
        }
        .borderWidth(2)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}