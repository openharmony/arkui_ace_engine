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
@Builder
export function PopupDismissBuilder(name: string, param: Object) {
  PopupExample03()
}

@Entry
@Component
struct PopupExample03 {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup1: boolean = false
  @State message: string = ''

  @Builder popupBuilder() {
    Row({ space: 2 }) {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
        .margin({ left: -5 })
      Text('Custom Popup')
        .fontSize(10)
    }
    .width(100)
    .height(50)
    .padding(5)
  }

  build() {
    NavDestination() {
      Column({ space: 100 }) {
        Text('测试气泡onWillDimiss')
          .textAlign(TextAlign.Center)
          .fontSize(20)

        Text('onWillDimiss reason: ' + this.message)
          .textAlign(TextAlign.Center)
        Button('PopupOption')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1
          })
          .bindPopup(this.handlePopup1!!, {
            builder: this.popupBuilder(),
            showInSubWindow: false,
            onWillDismiss: (e) => {
              if (e.reason == DismissReason.PRESS_BACK) {
                this.message = 'PRESS_BACK'
              } else if (e.reason == DismissReason.TOUCH_OUTSIDE) {
                this.message = 'TOUCH_OUTSIDE'
              } else {
                this.message = ''
              }
              e.dismiss()
            }
          })
      }
      .width('100%')
    }
    .title('PopupDismissTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}