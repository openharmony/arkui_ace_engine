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
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct SheetTransitionExample {
  @State isShowBottom: boolean = false
  @State isShowSide: boolean = false
  @State isShowSide2: boolean = false
  @State sheetHeight: number = 300;
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];

  @Builder
  sideBuilder() {
    Column() {
      ForEach(this.arr, (item: number) => {
        Row() {
          Text(item.toString())
            .width('80%')
            .height(60)
            .backgroundColor('#3366CC')
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .margin({ top: 5 })
        }
      }, (item: number) => item.toString())
      TextInput()
        .margin({ top: 5 })
    }
    .width('100%')
    .height('auto')
  }

  build() {
    Column({space:3}) {
      Text($r('app.string.SideSheet4'))
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')

      Button('bindSheet-Side-withMask')
        .onClick(() => {
          this.isShowSide = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowSide, this.sideBuilder(), {
          title: { title: 'SideSheetWithMask', subtitle: 'no scrolling across boundaries effect,width=300vp' },
          backgroundColor: Color.Grey,
          onWillAppear: () => {
            console.log('BindSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('BindSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('BindSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('BindSheet onDisappear.')
          },
          preferType: SheetType.SIDE,
          width: 300,
          showClose: true,
          blurStyle: BlurStyle.Regular,
          maskColor: Color.Brown,
          effectEdge : EffectEdge.START & EffectEdge.END,
          onWillDismiss: ((dismissSheetAction: DismissSheetAction) => {
            console.log('BindSheet DismissReason:' + dismissSheetAction.reason)
            if (dismissSheetAction.reason == DismissReason.PRESS_BACK) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.PRESS_BACK')
            } else if(dismissSheetAction.reason == DismissReason.CLOSE_BUTTON) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.CLOSE_BUTTON')
            } else if(dismissSheetAction.reason == DismissReason.TOUCH_OUTSIDE) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.TOUCH_OUTSIDE')
            } else if(dismissSheetAction.reason == DismissReason.SLIDE) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.SLIDE')
            }
            dismissSheetAction.dismiss()
          }),
          onWillSpringBackWhenDismiss: ((springBackAction: SpringBackAction) => {
            console.log('BindSheet onWillSpringBackWhenDismiss')
          }),
          onHeightDidChange: (height: number)=>{
            console.log('BindSheet height change:' + height)
          },
          onWidthDidChange: (width: number)=>{
            console.log('BindSheet width change:' + width)
          },
        })


      Button('bindSheet-Side-NotwithMask')
        .onClick(() => {
          this.isShowSide2 = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowSide2, this.sideBuilder(), {
          title: { title: 'SideSheetNotWithMask', subtitle: 'no scrolling across boundaries effect,width=300vp' },
          backgroundColor: Color.Grey,
          onWillAppear: () => {
            console.log('BindSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('BindSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('BindSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('BindSheet onDisappear.')
          },
          preferType: SheetType.SIDE,
          width: 300,
          showClose: true,
          blurStyle: BlurStyle.Regular,
          maskColor: Color.Brown,
          enableOutsideInteractive: true,
          effectEdge : EffectEdge.START & EffectEdge.END,
          borderWidth: {start: LengthMetrics.vp(2)},
          onWillDismiss: ((dismissSheetAction: DismissSheetAction) => {
            console.log('BindSheet DismissReason:' + dismissSheetAction.reason)
            if (dismissSheetAction.reason == DismissReason.PRESS_BACK) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.PRESS_BACK')
            } else if(dismissSheetAction.reason == DismissReason.CLOSE_BUTTON) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.CLOSE_BUTTON')
            } else if(dismissSheetAction.reason == DismissReason.TOUCH_OUTSIDE) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.TOUCH_OUTSIDE')
            } else if(dismissSheetAction.reason == DismissReason.SLIDE) {
              console.log('BindSheet DismissSheetAction.reason == DismissReason.SLIDE')
            }
            dismissSheetAction.dismiss()
          }),
          onWillSpringBackWhenDismiss: ((springBackAction: SpringBackAction) => {
            console.log('BindSheet onWillSpringBackWhenDismiss')
          }),
          onHeightDidChange: (height: number)=>{
            console.log('BindSheet height change:' + height)
          },
          onWidthDidChange: (width: number)=>{
            console.log('BindSheet width change:' + width)
          },
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}