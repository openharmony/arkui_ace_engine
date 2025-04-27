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
export function PopupStyleBuilder(name: string, param: Object) {
  PopupExample02()
}

@Entry
@Component
struct PopupExample02 {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup1: boolean = false
  @State handlePopup2: boolean = false
  @State handlePopup3: boolean = false

  build() {
    NavDestination() {
      Column({ space: 100 }) {
        Text('测试气泡部分样式属性是否正常')
          .textAlign(TextAlign.Center)
          .fontSize(20)

        Button('验证targetSpace为0')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1
          })
          .bindPopup(this.handlePopup1!!, {
            message: 'this is a popup',
            messageOptions: {
              textColor: Color.Red,
              font: {
                size: '14vp',
                style: FontStyle.Italic,
                weight: FontWeight.Bolder
              }
            },
            autoCancel: false,
            mask: false,
            placement: Placement.Bottom,
            enableArrow: false,
            targetSpace: 0,
          })

        Button('验证气泡箭头宽度32，高度16，圆角20')
          .onClick(() => {
            this.handlePopup2 = !this.handlePopup2
          })
          .bindPopup(this.handlePopup2!!, {
            message: '验证气泡箭头宽度32，高度16，圆角20',
            autoCancel: false,
            mask: false,
            arrowHeight: 16, // 设置气泡箭头高度
            arrowWidth: 32, // 设置气泡箭头宽度
            radius: 20, // 设置气泡的圆角
            shadow: ShadowStyle.OUTER_DEFAULT_XS, // 设置气泡的阴影
          })

        Button('验证气泡arrowPointPosition')
          .onClick(() => {
            this.handlePopup3 = !this.handlePopup3
          })
          .bindPopup(this.handlePopup3!!, {
            message: '验证气泡arrowPointPosition',
            autoCancel: false,
            mask: false,
            arrowPointPosition: ArrowPointPosition.START,
            backgroundBlurStyle: BlurStyle.NONE,
            popupColor: Color.Red
          })
      }
      .width('100%')
    }
    .title('PopupStyleBuilder')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}