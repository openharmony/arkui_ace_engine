/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct Index {
  @State hint: string = '';

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('SmartGestureController 验证')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)
        Column({ space: 12 }) {
          Button('Case1: 长页面Scroll + Button')
            .width('100%')
            .height(60)
            .fontSize(16)
            .onClick(() => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/Case1' });
            })

          Button('Case2: 长列表List')
            .width('100%')
            .height(60)
            .fontSize(16)
            .onClick(() => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/Case2' });
            })

          Button('Case3: 单页面 + 多组件')
            .width('100%')
            .height(60)
            .fontSize(16)
            .onClick(() => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/Case3' });
            })

          Button('Case4: Swiper + Button')
            .width('100%')
            .height(60)
            .fontSize(16)
            .onClick(() => {
              this.getUIContext().getRouter().pushUrl({ url: 'pages/Case4' });
            })

        }
        .width('100%')
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f3f5')
  }
}