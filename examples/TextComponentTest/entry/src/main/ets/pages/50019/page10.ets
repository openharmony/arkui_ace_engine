/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
import router from '@ohos.router'

@Entry
@Component
struct SubWindowTextInput {
  @State stackA: NavPathStack = new NavPathStack();
  @State stackB: NavPathStack = new NavPathStack();
  private curWindow: window.Window | null = null;
  @State x: number = 50;
  @State y: number = 200;
  controller: TextInputController = new TextInputController()
  @State inputValue: string = ""
  @State isSupportAvoidance: boolean = true
  @State marginTop: number = 0
  @State cusHeight: number = 300
  @State focusable1: boolean = true

  // 自定义键盘组件
  @Builder CustomKeyboardBuilder() {
    Column() {
      Button('close Window')
        .width('100%')
        .onClick(() => {
          this.closeWindow();
        })
      Row() {
        Button('x')
          .width('50%')
          .onClick(() => {
            this.controller.stopEditing()
          })

        Button('focusable:' + this.focusable1)
          .width('50%')
          .onClick(() => {
            this.focusable1 = !this.focusable1
          })
      }.width('100%').margin({ top: 10 })
      Row() {
        Button('height+,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight += 10
          })

        Button('height-,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight -= 10
          })
      }.width('100%').margin({ top: 10 })
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, '*', 0, '#'], (item:number|string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }


  onPageShow(): void {
    window.findWindow('testWindow')?.setSubWindowModal(false)
      .then(() => {
        console.info('Succeeded in setting subwindow modal');
      }).catch((err: BusinessError) => {
      console.error('Failed to set subwindow modal. Cause:' +  JSON.stringify(err));
    })
  }

  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindow');
      if (!this.curWindow) {
        console.log(`testTag failed to findWindow`);
        return;
      }

      this.curWindow.destroyWindow().then(() => {
        console.log(`testTag success to destroy curWindow`);
      }).catch((err: BusinessError) => {
        console.log(`failed to destroy curWindow`)
      })
    } catch (e) {
      console.log(`testTag catch exception when find Window: ${JSON.stringify(e)}`)
    }
  }

  build() {
    Column({space:10}) {
      Text().height('63%')
      TextInput({ controller: this.controller, text: this.inputValue })
        .defaultFocus(true)
        .focusable(this.focusable1)
        .customKeyboard(this.CustomKeyboardBuilder(),{ supportAvoidance: this.isSupportAvoidance })
          // .margin({ top: this.marginTop })
        .border({ width: 1 })


    }
    .backgroundColor(Color.Pink)
    .width('100%')
    .height('100%')
    .borderWidth(1)
  }
}