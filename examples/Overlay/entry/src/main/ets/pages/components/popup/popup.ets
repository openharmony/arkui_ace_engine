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
export function PopupBuilder(name: string, param: Object) {
  PopupExample()
}

@Entry
@Component
struct PopupExample {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup: boolean = false
  @State customPopup: boolean = false

  // popup构造器定义弹框内容
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
      Column({ space: 5 }) {
        Text('bindPopup')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        // PopupOptions 类型设置弹框内容
        Button('PopupOptions')
          .onClick(() => {
            this.handlePopup = !this.handlePopup
          })
          .bindPopup(this.handlePopup, {
            message: 'This is a popup with PopupOptions',
            placementOnTop: true,
            showInSubWindow:false,
            // 设置气泡避让软键盘
            keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,
            primaryButton: {
              value: 'confirm',
              action: () => {
                this.handlePopup = !this.handlePopup
                console.info('confirm Button click')
              }
            },
            // 第二个按钮
            secondaryButton: {
              value: 'cancel',
              action: () => {
                this.handlePopup = !this.handlePopup
                console.info('cancel Button click')
              }
            },
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.handlePopup = false
              }
            }
          })
          .margin(20)

        Text('bindPopup + 自定义内容builder')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        // CustomPopupOptions 类型设置弹框内容
        Button('CustomPopupOptions')
          .onClick(() => {
            this.customPopup = !this.customPopup
          })
          .bindPopup(this.customPopup, {
            builder: this.popupBuilder,
            placement: Placement.Top,
            mask: {color:'#33000000'},
            popupColor: Color.Yellow,
            enableArrow: true,
            // 设置气泡避让软键盘
            keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,
            showInSubWindow: false,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.customPopup = false
              }
            }
          })
      }.width('100%').margin({ top: 5 })
    }
    .title('Popup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}