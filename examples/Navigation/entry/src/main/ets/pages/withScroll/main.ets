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

@Entry
@Component
struct Index {
  scroller: Scroller = new Scroller()

  build() {
    Row() {
      Scroll(this.scroller) {
        Column() {
          Button('navigation1')
            .backgroundColor(Color.Blue)
            .fontColor(Color.White)
            .fontWeight(FontWeight.Bolder)
            .fontSize(15)
            .borderRadius(10)
            .width('70%')
            .height(35)
            .margin(7)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/withScroll/navigation1'
              })
            })
          Button('outside set scroll')
            .backgroundColor(Color.Blue)
            .fontColor(Color.White)
            .fontWeight(FontWeight.Bolder)
            .fontSize(15)
            .borderRadius(10)
            .width('70%')
            .height(35)
            .margin(7)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/withScroll/navigation2'
              })
            })
          Button('inside set scroll')
            .backgroundColor(Color.Blue)
            .fontColor(Color.White)
            .fontWeight(FontWeight.Bolder)
            .fontSize(15)
            .borderRadius(10)
            .width('70%')
            .height(35)
            .margin(7)
            .onClick(() => {
              router.pushUrl({
                url: 'pages/withScroll/navigation3'
              })
            })
        }
        .width('100%')
      }
    }
    .height('100%')
  }
}