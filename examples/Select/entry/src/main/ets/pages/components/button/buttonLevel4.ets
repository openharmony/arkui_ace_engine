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
export function ButtonLevel4Builder(name: string, param: Object) {
  ButtonLevel4Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  label1: string,
  type?: ButtonType,
  width1?: Length,
  height1?: Length,
  padding1?: Padding | Length,

}

@Entry
@Component
struct ButtonLevel4Example {
  pathStack: NavPathStack = new NavPathStack()
  @State label1: string = 'hello'
  @State label2: string = ''
  @State type?: ButtonType = undefined
  @State width1?: Length = undefined
  @State height1?: Length = undefined
  @State padding1?: Padding | Length = undefined
  private index: number = 0
  private lastIndex: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  private sets: Array<setsObject> = [
    {
      // 预期左右预留button默认的padding，上比下大10
      label1: '这是一条普通信息',
      type: ButtonType.Capsule,
      width1: '50',
      height1: '80',
      padding1: { top: 10 }
    },
    {
      // 预期文字左右无padding，上下居中
      label1: '这是一条长信息这是一条长信息这是一条长信息',
      type: ButtonType.Normal,
      width1: '80',
      height1: '100',
      padding1: {
        top: 0,
        bottom: '0',
        left: 0,
        right: 0
      }
    },
    {
      // 预期左右居中，上比下大30-父容器宽*10%=-7.5(以屏幕宽为375vp为例)
      label1: '这是一条普通信息',
      type: ButtonType.Normal,
      width1: '80',
      height1: '100',
      padding1: {
        top: 30,
        bottom: '10%',
        left: 0,
        right: 0
      }
    },
    {
      // 预期以宽高小者作为半径
      label1: '短信息',
      type: ButtonType.Circle,
      width1: '80',
      height1: '50',
      padding1: {
        top: 10,
        bottom: 20,
        left: 20,
        right: 10
      }
    },
    {
      // 预期上比下多20，左比右多10，在剩余空间内居中，显示不下则显示为点点点
      label1: '这是一条普通信息',
      type: ButtonType.Capsule,
      width1: '80',
      height1: '50',
      padding1: {
        top: '20',
        bottom: undefined,
        left: 10,
        right: undefined
      }
    },
    {
      label1: '这是一条普通信息',
      type: ButtonType.Capsule,
      width1: '80',
      height1: '10',
      padding1: undefined
    },
    {
      // 预期上比下多20，左比右多10，在剩余空间内居中，显示不下则显示为点点点
      label1: '这是一条普通信息',
      type: ButtonType.ROUNDED_RECTANGLE,
      width1: '80',
      height1: '50',
      padding1: {
        top: '20',
        bottom: undefined,
        left: 10,
        right: undefined
      }
    },
    {
      label1: '这是一条普通信息',
      type: ButtonType.ROUNDED_RECTANGLE,
      width1: '80',
      height1: '10',
      padding1: undefined
    },
  ]

  private setParam(): void {
    // 1. 参数赋值
    this.label1 = this.sets[this.index].label1
    this.type = this.sets[this.index].type
    this.width1 = this.sets[this.index].width1
    this.height1 = this.sets[this.index].height1
    this.padding1 = this.sets[this.index].padding1
    // 2. 参数打印
    this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
      '\nlabel1: ' + this.label1 + '\nButtonType: ' + this.type + '\nwidth1: ' + this.width1 + '\nheight1: ' +
    this.height1 + '\npadding1: ' + this.padding1
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
              this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.lastIndex + 1) +
                '\nlabel1: ' + this.label1 + '\nButtonType: ' + this.type + '\nwidth1: ' + this.width1 + '\nheight1: ' +
              this.height1 + '\npadding1: ' + this.padding1
            })

          Row({ space: 2 }) {
            Text(`${this.sets.length}`)
              .key('button11')
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

          Divider()
            .strokeWidth('1px')
          Text('Button 不指定宽高或指定单边长度以及考虑异常值，验证动态改变文本内容后自适应逻辑')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Button(`组件与通用属性结合考虑异常值${this.label1}`, { type: this.type })
            .fontSize(-1)
            .fontStyle(undefined)
            .fontWeight(-100)
            .width(-1)
            .height(-1)
            .borderWidth(-1)
            .borderColor('color')
            .borderStyle(undefined)
            .borderRadius(-10)
            .size({ width: -100, height: undefined })
            .padding(-1)
            .margin(-1)
            .border(undefined)
            .borderImage(undefined)
          Button(`不设宽高${this.label1}`, { type: this.type })
            .fontSize(15)
            .fontStyle(FontStyle.Normal)
            .fontWeight('lighter')
            .fontFamily(null)
          Button(`固定宽${this.label1}`, { type: this.type })
            .width('30%')
            .fontColor('aa')
            .fontSize(10)
            .fontStyle(FontStyle.Normal)
            .fontWeight('bolder')
          Button(`固定高${this.label1}`, { type: this.type })
            .height('20%')
            .fontColor('#008000')
            .fontSize('20')
            .fontStyle(FontStyle.Italic)
            .fontWeight(undefined)
            .fontFamily(undefined)
          // 最后一个button固定宽高，用于参照
          Button(`固定宽高${this.label1}`, { type: this.type })// circle类型时...缩略在原型按钮内不是居中
            .width('30%')
            .height('20%')
            .fontSize(20)

          Divider()
            .strokeWidth('1px')

          Text('Button 固定内容后，验证动态改变button大小后自适应逻辑')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Button(`固定内容：The expert in anything was once a beginner.`, { type: this.type })
            .width(this.width1)
            .height(this.height1)
            .padding(this.padding1)
          Button(`size设置` + this.label2, { type: this.type })
            .key('ButtonSize')
            .size({
              width: 200,
              height: 40
            })
            .responseRegion({
              x: 0,
              y: 0,
              width: '60%',
              height: '100%'
            })
            .onClick(() => {
              this.label2 = this.label2 + 'a'
            })
          Divider()
            .strokeWidth('1px')
          if (this.show) {
            Text(this.info)
              .fontSize(9)
              .width('60%')
          }
        }
        .width('100%')
        .padding(10)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel4')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}