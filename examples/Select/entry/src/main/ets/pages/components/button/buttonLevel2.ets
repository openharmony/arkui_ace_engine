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

import { ChildComponent } from '../base/ChildComponent';
import { MyComponent } from '../base/MyComponent';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function ButtonLevel2Builder(name: string, param: Object) {
  ButtonLevel2Example()
}

ThemeControl.setDefaultTheme(undefined);

interface setsObject {
  type?: ButtonType,
  visit?: Visibility
}

@Entry
@Component
struct ButtonLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  @State myType1: ButtonType = ButtonType.Capsule
  @State visible?: Visibility = undefined
  @State buttonClip?: boolean = undefined
  @State title: string = 'test'
  private index: number = 0
  private lastIndex: number = -1
  @State info?: string = undefined
  @State show: boolean = false
  private sets: Array<setsObject> = [
    {
      type: ButtonType.ROUNDED_RECTANGLE,
      visit: Visibility.Hidden
    },
    {
      type: ButtonType.ROUNDED_RECTANGLE,
      visit: Visibility.None
    },
    {
      type: ButtonType.ROUNDED_RECTANGLE,
      visit: Visibility.Visible
    },
    {
      type: ButtonType.Capsule,
      visit: Visibility.Hidden
    },
    {
      type: ButtonType.Capsule,
      visit: Visibility.Visible
    },
    {
      type: ButtonType.Capsule,
      visit: Visibility.None
    },
    {
      type: ButtonType.Circle,
      visit: Visibility.Visible
    },
    {
      type: ButtonType.Circle,
      visit: Visibility.None
    },
    {
      type: ButtonType.Circle,
      visit: Visibility.Hidden
    },
    {
      type: ButtonType.Normal,
      visit: Visibility.Visible
    },
    {
      type: ButtonType.Normal,
      visit: Visibility.None
    },
    {
      type: ButtonType.Normal,
      visit: Visibility.Hidden
    },
    {
      type: undefined,
      visit: undefined
    },
  ]
  private setParam(): void {
    // 1. 参数赋值
    this.myType1 = this.sets[this.index].type!
    this.visible = this.sets[this.index].visit
    // 2. 参数打印
    this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.index + 1) +
      '\nButtonType: ' + ButtonType[this.myType1] + '\nVisibility: ' + this.visible
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('切换测试参数,显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%').onClick(() => {
            this.show = !this.show
            this.buttonClip = this.show
            this.info = 'Total: ' + this.sets.length + ', CaseNumber: ' + (this.lastIndex + 1) +
              '\nButtonType: ' + ButtonType[this.myType1] + '\nVisibility: ' + this.visible
          })

          Row({ space: 2 }) {
            Text(`${this.sets.length}`).key('button01')
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
            Text(this.info).fontSize(9).width('60%')
          }
          Divider().strokeWidth('1px')
          Text('Button容器测试')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')

          Button({ type: ButtonType.Normal }) {
            ChildComponent({
              title: $title, func: () => {
                this.title = this.title + 'A'
              }
            })
          }
          .key('button_2')
          .backgroundColor(Color.Orange)
          .height(100)
          .aspectRatio(1)
          .align(Alignment.BottomStart)
          .onClick(() => {
            this.title = this.title + 'B'
          })

          Button({ type: this.myType1 }) {
            Row() {
              Image($r('app.media.app_icon')).width('20%').visibility(this.visible).aspectRatio(1).margin(12)
              Text('Success is not final, failure is not fatal: it is the courage to continue that counts.')// button容器高没有自适应
                .fontSize(20).layoutWeight(1) // layoutWeight导致崩溃,已修复
            }
          }
          .backgroundColor(Color.Pink)
          .borderWidth(2)

          Button({ type: this.myType1 }) {
            Row() {
              Image($r('app.media.app_icon')).width('20%').visibility(this.visible).aspectRatio(1).margin(12)
              Text('Success is not final, failure is not fatal: it is the courage to continue that counts.')
                .fontSize(20) //.layoutWeight(1)
            }.width(120)
          }
          .backgroundColor(Color.Pink)
          .borderWidth(2)
          .width(100)
          .aspectRatio(0.5)
          .clip(this.buttonClip)
        }.margin(5)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}