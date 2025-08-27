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

import { CustomDialogExample } from '../../../../common/CustomDialogController'


@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}


@Entry
@Component
struct CustomDialogTestLevel0_2 {
  scroller: Scroller = new Scroller()
  //
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      textValue: $textValue,
      inputValue: $inputValue
    }),

    onWillAppear: () => {
      console.info('customDialog onWillAppear')
    },
    onDidAppear: () => {
      console.info('customDialog onDidAppear')
    },
    onWillDisappear: () => {
      console.info('customDialog onWillDisappear')
    },
    onDidDisappear: () => {
      console.info('customDialog onDidDisappear')
    },
  })

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证CustomDialog的生命周期回调属性`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text('生命周期回调返回日志')
            .paramTextStyle()
          Text(`子窗CustomDialog: 生命周期回调`)
            .componentTextStyle()
            .onClick(() => {
              this.dialogController = new CustomDialogController({
                showInSubWindow: true,

                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
                onWillAppear: () => {
                  console.info('customDialog onWillAppear')
                },
                onDidAppear: () => {
                  console.info('customDialog onDidAppear')
                },
                onWillDisappear: () => {
                  console.info('customDialog onWillDisappear')
                },
                onDidDisappear: () => {
                  console.info('customDialog onDidDisappear')
                },
              })
              this.dialogController?.open()
            })
          Text(`非子窗CustomDialog: 生命周期回调`)
            .componentTextStyle()
            .onClick(() => {
              this.dialogController = new CustomDialogController({
                showInSubWindow: false,

                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
                onWillAppear: () => {
                  console.info('customDialog onWillAppear')
                },
                onDidAppear: () => {
                  console.info('customDialog onDidAppear')
                },
                onWillDisappear: () => {
                  console.info('customDialog onWillDisappear')
                },
                onDidDisappear: () => {
                  console.info('customDialog onDidDisappear')
                },
              })
              this.dialogController?.open()
            })

          Text(`生命周期回调组合测试弹窗动效`)
            .paramTextStyle()
          Text(`CustomDialog: 生命周期*弹窗动效`)
            .componentTextStyle()
            .onClick(() => {
              this.dialogController = new CustomDialogController({
                openAnimation: { duration: 2000 },
                closeAnimation: { duration: 2000 },
                showInSubWindow: false,
                cancel: () => {
                  setTimeout(() => {
                    console.info('customDialog disappear transition loading')
                  }, 1000)
                },

                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
                onWillAppear: () => {
                  console.info('customDialog onWillAppear')
                },
                onDidAppear: () => {
                  console.info('customDialog onDidAppear')
                },
                onWillDisappear: () => {
                  console.info('customDialog onWillDisappear')
                },
                onDidDisappear: () => {
                  console.info('customDialog onDidDisappear')
                },
              })
              this.dialogController?.open()
              setTimeout(() => {
                console.info('customDialog appear transition loading')
              }, 1000)
            })
        }
        .columnStyle()

      }
      .width('100%')
    }
    .scrollBar(BarState.Off)
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%')
    .height('100%')
  }
}