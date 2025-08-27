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
export function ButtonLevel5Builder(name: string, param: Object) {
  ButtonLevel5Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  borderRadius1?: Length | BorderRadiuses,
  borderRadius2?: Length | BorderRadiuses,
  borderRadius3?: Length | BorderRadiuses,
  borderRadius4?: Length | BorderRadiuses,
  color?: ResourceColor
}

@Entry
@Component
struct ButtonLevel5Example {
  pathStack: NavPathStack = new NavPathStack()
  @State borderRadius1?: Length | BorderRadiuses =
    undefined //DTS2023010913825 BorderRadiuses设置无效;  规格：不支持BorderRadiuses类型入参
  @State borderRadius2?: Length | BorderRadiuses = 10
  @State borderRadius3?: Length | BorderRadiuses = undefined
  @State borderRadius4?: Length | BorderRadiuses = undefined
  @State color?: ResourceColor = undefined // 重新设置成undefined后无效
  private index: number = 0
  private lastIndex: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  private sets: Array<setsObject> = [
    {
      borderRadius1: {
        bottomLeft: 20,
        topLeft: 20,
        topRight: 20,
        bottomRight: 20
      },
      borderRadius2: 30,
      borderRadius3: '30',
      borderRadius4: $r('app.float.float_30'),
      color: Color.Pink
    },
    {
      borderRadius1: {
        bottomLeft: $r('app.float.float_50'),
        topLeft: $r('app.float.float_50'),
        topRight: $r('app.float.float_50'),
        bottomRight: $r('app.float.float_50')
      },
      borderRadius2: 70,
      borderRadius3: 'zzz',
      borderRadius4: $r('app.integer.integer_30'),
      color: undefined
    },
    {
      borderRadius1: {
        bottomLeft: -20,
        topLeft: -20,
        topRight: 'aa',
        bottomRight: 'aa'
      },
      borderRadius2: undefined,
      borderRadius3: '30px',
      borderRadius4: undefined,
      color: Color.Green
    },
    {
      borderRadius1: {
        bottomLeft: '20',
        topLeft: '20',
        topRight: 40,
        bottomRight: 20
      },
      borderRadius2: undefined,
      borderRadius3: undefined,
      borderRadius4: $r('app.float.float_100'),
      color: Color.Pink
    },
    {
      borderRadius1: undefined,
      borderRadius2: -30,
      borderRadius3: '-30',
      borderRadius4: $r('app.float.float_n30'),
      color: Color.Blue
    }
  ]

  private setParam(): void {
    // 1. 参数赋值
    this.borderRadius1 = this.sets[this.index].borderRadius1
    this.borderRadius2 = this.sets[this.index].borderRadius2
    this.borderRadius3 = this.sets[this.index].borderRadius3
    this.borderRadius4 = this.sets[this.index].borderRadius4
    this.color = this.sets[this.index].color
    // 2. 参数打印
    this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
      '\nborderRadius1: ' + this.borderRadius1 + '\nborderRadius2: ' + this.borderRadius2 + '\nborderRadius3: ' +
    this.borderRadius3 + '\nborderRadius4: ' + this.borderRadius4 + '\ncolor: ' + this.color
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
                '\nborderRadius1: ' + this.borderRadius1 + '\nborderRadius2: ' + this.borderRadius2 +
                '\nborderRadius3: ' +
              this.borderRadius3 + '\nborderRadius4: ' + this.borderRadius4 + '\ncolor: ' + this.color
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

          if (this.show) {
            Text(this.info)
              .fontSize(9)
              .width('60%')
          }
          Divider()
            .strokeWidth('1px')
          Text('Button圆角设置测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
          Row({ space: 10 }) {
            Button('btn1', { type: ButtonType.Capsule })
              .borderRadius(10)
              .borderWidth(1)
              .backgroundColor(this.color)
              .layoutWeight(1)
            Button('btn2', { type: ButtonType.ROUNDED_RECTANGLE })
              .border({ width: 2, color: Color.Red, radius: 3 })
              .borderWidth(1)
              .backgroundColor(this.color)
              .layoutWeight(1)
            Button('border', { type: ButtonType.Normal })
              .border({ radius: 20 })
            Button('BorderRadiuses', { type: ButtonType.Normal })
              .borderRadius(this.borderRadius1)
              .borderWidth(1)
              .backgroundColor(Color.Pink) // 规格：BorderRadiuses不支持
          }

          Row({ space: 10 }) {
            Button('2', { type: ButtonType.Circle })
              .borderWidth(1)
              .width(100)
              .height(50) // 预期为固定直径为50的圆
            Button('3', { type: ButtonType.Circle })
              .borderWidth(1)
              .borderRadius(this.borderRadius2)
              .backgroundColor(Color.Pink)
            Button('4', { type: ButtonType.Circle })
              .borderWidth(1)
              .borderRadius(this.borderRadius2)
              .width(50) // 预期为固定直径为50的圆
            Button('5', { type: ButtonType.Circle })
              .borderWidth(1)
              .borderRadius(this.borderRadius2)
              .width(50)
              .height(100)
              .align(Alignment.TopStart) // 预期为固定直径为50的圆
          }

          Button('Resource', { type: ButtonType.Normal })
            .borderRadius(this.borderRadius4)
            .borderWidth(1)
            .height(100)
          Button('string', { type: ButtonType.Normal })
            .border({ width: 1, radius: 50 })
            .borderRadius(this.borderRadius3)
            .backgroundColor(this.color)
            .height(100) // string类型设置ok,但不能动态修改
          Button('number2', { type: ButtonType.Normal })
            .borderRadius(this.borderRadius2)
            .borderWidth(1)
            .backgroundColor(this.color)
            .height(100)
        }
        .width('100%')
        .padding(10)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}