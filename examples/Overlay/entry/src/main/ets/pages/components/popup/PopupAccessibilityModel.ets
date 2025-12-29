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
export function PopupAccessibilityModelBuilder(name: string, param: Object) {
  PopupAccessibilityModelExample()
}

@Entry
@Component
struct PopupAccessibilityModelExample {
  @State handlePopup: boolean = false;
  @State customPopup: boolean = false;
  @State message: string = 'Hello World';
  @State changeMessage: boolean = false;

  // Popup构造器定义弹框内容
  @Builder popupBuilder() {
    Row({ space: 2 }) {
      // $r('app.media.startIcon')需要替换为开发者所需的图像资源文件。
      Image($r("app.media.startIcon")).width(24).height(24).margin({ left: -5 })
      Text('Custom Popup').fontSize(10)
    }.width(300).height(250).padding(5)
  }

  build() {
    Flex({ direction: FlexDirection.Column }) {
      // PopupOptions 类型设置弹框内容
      Button('Popup not in Modal')
        .onClick(() => {
          this.handlePopup = !this.handlePopup;
        })
        .bindPopup(this.handlePopup, {
          message: 'This is a popup with PopupOptions',
          placement: Placement.Top,
          showInSubWindow:false,
          mask: false,
          keyboardAvoidMode: KeyboardAvoidMode.DEFAULT, // 设置气泡避让软键盘
          primaryButton: {
            value: 'confirm',
            action: () => {
              this.handlePopup = !this.handlePopup;
              console.info('confirm Button click');
            }
          },
          // 第二个按钮
          secondaryButton: {
            value: 'cancel',
            action: () => {
              this.handlePopup = !this.handlePopup;
              console.info('cancel Button click');
            }
          },
          onStateChange: (e) => {
            console.info(JSON.stringify(e.isVisible))
            if (!e.isVisible) {
              this.handlePopup = false;
            }
          }
        })
        .position({ x: 100, y: 150 })


      // CustomPopupOptions 类型设置弹框内容
      Button('Popup in Modal')
        .onClick(() => {
          this.customPopup = !this.customPopup;
        })
        .bindPopup(this.customPopup, {
          builder: this.popupBuilder,
          placement: Placement.Top,
          mask: {color:'#33000000'},
          popupColor: Color.Yellow,
          enableArrow: true,
          keyboardAvoidMode: KeyboardAvoidMode.DEFAULT, // 设置气泡避让软键盘
          showInSubWindow: false,
          onStateChange: (e) => {
            if (!e.isVisible) {
              this.customPopup = false;
            }
          }
        })
        .position({ x: 80, y: 300 })

      Text(this.message)
        .id('HelloWorld')
        .fontSize($r('app.float.page_text_font_size'))
        .margin(100)
        .fontWeight(FontWeight.Bold)
        .onClick(() => {
          this.changeMessage = !this.changeMessage;
          this.message = this.changeMessage ? 'Welcome' : 'Hello World';
        })
        .position({ x: 80, y: 450 })
    }.width('100%').padding({ top: 5 })
  }
}