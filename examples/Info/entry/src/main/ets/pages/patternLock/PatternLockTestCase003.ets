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
struct patternLock {
  @State rating: number = 0;
  @State fillColor: string = '#FF000000';
  @State name: string = 'PatternLock';
  @State stepTips: string = '操作步骤：在九宫格中画出自己想设置的密码，设置两次' + '\n' + '预期结果：设置密码成功';
  @State view: boolean = false;
  @State passwords: Number[] = [];
  @State message: string = '请输入密码';
  private patternLockController: PatternLockController = new PatternLockController();

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
        Text(this.message)
          .textAlign(TextAlign.Center)
          .margin(20)
          .fontSize(20)
          .margin({ top: 24 })

        PatternLock(this.patternLockController)
          .sideLength(300)
          .circleRadius(9)
          .pathStrokeWidth(18)
          .activeColor('#B0C4DE')
          .selectedColor('#228B22')
          .pathColor('#90EE90')
          .backgroundColor('#F5F5F5')
          .autoReset(true)
          .onPatternComplete((input: Array<number>) => {
            // 输入的密码长度小于5时，提示重新输入
            if (input === null || input === undefined || input.length < 5) {
              this.message = '输入的密码长度需要大于5, 请重新输入。'
              return
            }
            // 判断密码长度是否大于0
            if (this.passwords.length > 0) {
              // 判断两次输入的密码是否相同，相同则提示密码设置成功，否则提示重新输入
              if (this.passwords.toString() === input.toString()) {
                this.passwords = input
                let regex: RegExp = new RegExp(',', 'g');
                this.message = '设置密码成功: ' + this.passwords.toString().replace(regex, ' ')
                this.view = true;
              } else {
                this.message = '两次密码不一致，请重新输入。'
              }
            } else {
              // 提示第二次输入密码
              this.passwords = input
              this.message = '请再一次输入密码进行确认。'
            }
          })

        Button('重置密码锁')
          .margin(30)
          .onClick(() => {
            // 重置密码锁
            this.patternLockController.reset()
            this.passwords = []
            this.message = '请输入密码'
          })
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