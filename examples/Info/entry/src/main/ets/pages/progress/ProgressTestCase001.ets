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
struct progress {
  @State fillColor: string = '#FF000000';
  @State name: string = 'Progress';
  @State stepTips: string = '操作步骤：拖动滑块向右移动' + '\n' + '预期结果：进度条进度随着拖动距离增大而变大';
  @State view: boolean = false;
  @State accumulateTime: number = 0;
  @State progress: number = 0;
  @State progressNext: number = 0;
  @State intervalNum: number = 0;

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
      if (this.progressNext !== this.progress) {
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

      Scroll() {
        Column() {
          Text('线性样式')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column() {
            Column({ space: 15 }) {
              Progress({ value: this.progress, type: ProgressType.Linear })
                .width(200)
              Progress({ value: this.progress, total: 100, type: ProgressType.Linear })
                .color(Color.Grey)
                .width(200)
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)

          Text('圆形样式')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column() {
            Row({ space: 40 }) {
              Progress({ value: this.progress, type: ProgressType.Eclipse })
                .width(50)
              Progress({ value: this.progress, total: 100, type: ProgressType.Eclipse })
                .width(50)
                .color(Color.Grey)
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)

          Text('环形有刻度样式')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column({ space: 10 }) {
            Row({ space: 20 }) {
              Progress({ value: this.progress, type: ProgressType.ScaleRing })
                .width(50)
              Progress({ value: this.progress, total: 100, type: ProgressType.ScaleRing })
                .color(Color.Grey).width(50)
                .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
              Progress({ value: this.progress, total: 100, type: ProgressType.ScaleRing })
                .color(Color.Grey).width(50)
                .style({ strokeWidth: 20, scaleCount: 20, scaleWidth: 5 })
              Progress({ value: this.progress, total: 100, type: ProgressType.ScaleRing })
                .color(Color.Grey).width(50)
                .style({ strokeWidth: 20, scaleCount: 30, scaleWidth: 3 })
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)

          Text('环形无刻度样式')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column() {
            Row({ space: 40 }) {
              Progress({ value: this.progress, type: ProgressType.Ring })
                .width(50)
              Progress({ value: this.progress, total: 100, type: ProgressType.Ring })
                .color(Color.Grey).width(50)
                .style({ strokeWidth: 10, scaleCount: 30, scaleWidth: 20 })
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)

          Text('胶囊样式')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column() {
            Row({ space: 40 }) {
              Progress({ value: this.progress, type: ProgressType.Capsule })
                .width(100)
                .height(50)
              Progress({ value: this.progress, total: 100, type: ProgressType.Capsule })
                .color(Color.Grey)
                .width(100)
                .height(50)
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)
          .width('100%')

          Text('调整进度')
            .fontSize(18)
            .height(22)
            .alignSelf(ItemAlign.Start)
            .margin({ left: 12, top: 12 })
          Column() {
            Row({ space: 10 }) {
              Slider({
                value: this.progress,
                min: 0,
                max: 100,
                style: SliderStyle.OutSet,
              })
                .margin({ top: 24, bottom: 24 })
                .width('70%')
                .trackColor('#4DCB26')
                .selectedColor('#00A7FA')
                .trackThickness('8vp')
                .blockBorderColor('#07B9A2')
                .blockBorderWidth('1vp')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.progress = value
                  console.info('set brightness value ' + value);
                })
            }
          }
          .backgroundColor(Color.White)
          .borderRadius(24)
          .width('100%')
          .padding(15)
          .width('100%')
        }
      }
      .backgroundColor(Color.White)
      .height('80%')
      .width('100%')


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