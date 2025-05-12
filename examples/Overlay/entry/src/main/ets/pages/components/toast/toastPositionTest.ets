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

import { promptAction } from '@kit.ArkUI'
import { BusinessError } from '@kit.BasicServicesKit';

@Builder
export function ToastPositionBuilder(name: string, param: Object) {
  ToastExample01()
}

@Extend(Button) function myButtonStyle() {
  .fontSize(10)
  .padding(5)
  .margin(2)
  .borderRadius(5)
}

@Extend(TextPicker) function myTextPicker() {
  .width(70)
  .height(50)
  .selectedTextStyle({font: {size: 12}})
  .canLoop(false)
  .textStyle({font: {size: 12}})
  .borderWidth(2)
}

@Entry
@Component
struct ToastExample01 {
  pathStack: NavPathStack = new NavPathStack()

  @State alignment: Alignment | undefined = Alignment.TopStart
  alignmentKeys: string[] = ['undefined'].concat(...Object.keys(Alignment).slice(9))
  alignments: (Alignment | undefined)[] = [
    undefined,
    Alignment.TopStart,
    Alignment.Top,
    Alignment.TopEnd,
    Alignment.Start,
    Alignment.Center,
    Alignment.End,
    Alignment.BottomStart,
    Alignment.Bottom,
    Alignment.BottomEnd
  ]

  @State alignIdx: number = 0
  @State showMode: promptAction.ToastShowMode = promptAction.ToastShowMode.DEFAULT
  @State toastBackgroundColor: Color | undefined = undefined
  @State toastTextColor: Color | undefined = undefined

  aboutToAppear(): void {
    console.log('toast: ', JSON.stringify(this.alignmentKeys))
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Row() {
            Text('TextColor: ')
            TextPicker({
              range: [
                'undefined',
                'Green',
                'Yellow',
                'White',
                'Orange'
              ],
              selected: 0
            })
              .myTextPicker()
              .onChange((value: string | string[]) => {
                switch (value) {
                  case 'Green':
                    this.toastTextColor = Color.Green
                    break
                  case 'Yellow':
                    this.toastTextColor = Color.Yellow
                    break
                  case 'White':
                    this.toastTextColor = Color.White
                    break
                  case 'Orange':
                    this.toastTextColor = Color.Orange
                    break
                  case 'undefined':
                    this.toastTextColor = undefined
                    break
                }
              })
          }
          Row() {
            Text('backgroundColor: ')
            TextPicker({
              range: [
                'undefined',
                'Red',
                'Blue',
                'Pink',
                'Black',
              ],
              selected: 0
            })
              .myTextPicker()
              .onChange((value: string | string[]) => {
                switch (value) {
                  case 'Red':
                    this.toastBackgroundColor = Color.Red
                    break
                  case 'Blue':
                    this.toastBackgroundColor = Color.Blue
                    break
                  case 'Pink':
                    this.toastBackgroundColor = Color.Pink
                    break
                  case 'Black':
                    this.toastBackgroundColor = Color.Black
                    break
                  case 'undefined':
                    this.toastBackgroundColor = undefined
                    break
                }
              })
          }
          Row() {
            Text('showMode: ')
            Button('default')
              .myButtonStyle()
              .backgroundColor(this.showMode == promptAction.ToastShowMode.DEFAULT ? Color.Brown : undefined)
              .onClick(()=>{
                this.showMode = promptAction.ToastShowMode.DEFAULT
              })
            Button('top_most')
              .myButtonStyle()
              .backgroundColor(this.showMode == promptAction.ToastShowMode.TOP_MOST ? Color.Brown : undefined)
              .onClick(()=>{
                this.showMode = promptAction.ToastShowMode.TOP_MOST
              })
          }
          .margin(5)

          Row() {
            Text(`对齐方式：${this.alignmentKeys[this.alignIdx]}`)
            Button('++1')
              .myButtonStyle()
              .onClick(()=>{
                this.alignIdx = (this.alignIdx + 1) % this.alignments.length
              })
            Button('--1')
              .myButtonStyle()
              .onClick(()=>{
                this.alignIdx = (this.alignIdx - 1) % this.alignments.length
              })
          }

          Button('showToast')
            .onClick(()=>{
              try {
                promptAction.showToast({
                  message: 'Hello World',
                  duration: 2000,
                  showMode: this.showMode,
                  alignment: this.alignments[this.alignIdx],
                  backgroundColor: this.toastBackgroundColor,
                  textColor: this.toastTextColor,
                  backgroundBlurStyle: BlurStyle.NONE
                });
              } catch (error) {
                let message = (error as BusinessError).message
                let code = (error as BusinessError).code
                console.error(`showToast args error code is ${code}, message is ${message}`);
              };
            })
        }
        .width('100%')
        .margin({top: 5})
      }
      .height('100%')
      .border({width: 1, color: Color.Red})
    }
    .title('toastPositionTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}