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

import router from '@ohos.router';
import promptAction from '@ohos.promptAction';

@Entry
@Component
struct gauge {
  @State rating: number = 0;
  @State address: string = '';
  @State fillColor: string = '#FF000000';
  @State name: string = 'Gauge';
  @State stepTips: string = '操作步骤：拖动下方滑动条' + '\n' + '预期结果：仪表盘的刻度发生改变';
  @State view: boolean = false;
  @State active: boolean = false;
  @State intervalNum: number = 0;
  @State start: boolean = false
  @State fromStart: boolean = true
  @State step: number = 50
  @State loop: number = 3
  @State mColor: Color = Color.Gray
  @State value: number = 0
  @State startAngle: number = 0
  @State endAngle: number = 360
  @State mWidth: number = 20

  @Builder
  PassBtn(text: Resource, isFullScreen: boolean) {
    if (this.view == false) {
      Button({ stateEffect: this.view }) {
        Image($r('app.media.ic_public_pass'))
          .width('20vp')
          .height('20vp')
      }
      .width('30%')
      .height('30vp')
      .backgroundColor(Color.Grey)
      .opacity(0.4)
      .onClick(() => {

      })
    } else {
      Button({ stateEffect: this.view }) {
        Image($r('app.media.ic_public_pass'))
          .width('20vp')
          .height('20vp')
      }.width('30%')
      .height('30vp')
      .backgroundColor(Color.Grey)
      .onClick(() => {
        router.back({
          url: 'pages/ArkUI/ArkUI_index',
          params: {
            result: 'true ', title: this.name,
          }
        })
        promptAction.showToast({
          message: '通过', duration: 1000
        });
      })
    }
  }

  @Builder
  FailBtn(text: Resource, isFullScreen: boolean) {
    Button() {
      Image($r('app.media.ic_public_fail'))
        .width('20vp')
        .height('20vp')
    }
    .width('30%')
    .height('30vp')
    .backgroundColor(Color.Grey)
    .onClick(() => {
      router.back({
        url: 'pages/ArkUI/ArkUI_index',
        params: {
          result: 'false', title: this.name,
        }
      })
      promptAction.showToast({
        message: '失败', duration: 1000
      });
    })
  }

  onPageShow() {
    this.intervalNum = setInterval(() => {
      if (this.value > 0) {
        this.view = true
      }
    }, 500)
  }

  onPageHide() {
    clearInterval(this.intervalNum)
  }

  aboutToDisappear() {
    clearInterval(this.intervalNum)
  }

  build() {
    Column() {
      Row() {
        Button() {
          Image($r('app.media.ic_public_back'))
            .width('20vp')
            .height('18vp')
            .margin({ left: '20vp' })
        }
        .backgroundColor(Color.Black)
        .size({ width: '40vp', height: '30vp' })
        .onClick(() => {
          router.back({
            url: 'pages/ArkUI/ArkUI_index',
            params: { result: 'None' }
          })
        })

        Text(this.name)
          .fontColor(Color.White)
          .fontSize('18fp')
          .margin({ left: '-20vp' })
        Text('hello')
          .fontColor(Color.White)
          .visibility(Visibility.Hidden)
      }
      .backgroundColor(Color.Black)
      .height('10%')
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Column() {
        Row() {
          Text('仪表盘')
            .align(Alignment.Start)
            .height('100%')
            .width('100%')
            .fontSize(16)
        }
        .height(20)
        .width('90%')
        .justifyContent(FlexAlign.Start)
        .margin({ top: 50 })

        Gauge({ value: this.value })
          .width(200)
          .height(200)
          .colors([[0x317AF7, 1], [0x5BA854, 1], [0xE08C3A, 1], [0x9C554B, 1]])
          .startAngle(this.startAngle)
          .endAngle(this.endAngle)
          .strokeWidth(this.mWidth)
          .margin({ top: 12 })

        Row() {
          Text('调整刻度')
            .align(Alignment.Start)
            .height('100%')
            .width('100%')
            .fontSize(16)
        }
        .height(20)
        .width('90%')
        .justifyContent(FlexAlign.Start)
        .margin({ top: 50 })

        Column() {
          Row({ space: 10 }) {
            Slider({
              value: this.value,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet,
            })
              .margin({ top: 12, bottom: 24 })
              .width('70%')
              .trackColor('#4DCB26')
              .selectedColor('#00A7FA')
              .trackThickness('8vp')
              .blockBorderColor('#07B9A2')
              .blockBorderWidth('1vp')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.value = value
                console.info('set onChange value ' + value);
              })
          }
        }
        .backgroundColor(Color.White)
        .borderRadius(24)
        .width('100%')
        .padding(15)
      }
      .height('80%')
      .width('100%')
      .backgroundColor(Color.White)

      Row() {
        this.PassBtn($r('app.string.btn_fullscreen'), true);
        Button() {
          Image($r('app.media.ic_public_help'))
            .width('20vp')
            .height('20vp')
        }
        .width('30%')
        .height('30vp')
        .backgroundColor(Color.Grey)
        .onClick(() => {
          AlertDialog.show(
            {
              title: '操作提示',
              message: this.stepTips,
              confirm: {
                value: 'OK',
                action: () => {
                }
              }
            }
          )
        })

        this.FailBtn($r('app.string.btn_fullscreen'), true);
      }
      .height('10%')
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .backgroundColor(Color.Black)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F1F3F5')
  }
}