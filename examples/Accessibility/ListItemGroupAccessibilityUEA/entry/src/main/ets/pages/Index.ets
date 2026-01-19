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

import { router } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  @State message: string = 'UEA';
  @State oneButtonColor: string = '#FFC0CB'

  build() {
    Column({ space: 20 }) {
      Text(this.message)
        .id('HelloWorld')
        .fontSize(50)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
      Button("EmptyUEA")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/EmptyUEA'
          })
        })
        .backgroundColor(this.oneButtonColor)
        .width(250)
        .height(70)
        .fontSize(16)
        .fontColor(Color.Black)
      Button("PhotoPickerUEA")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/PhotoPickerUEA'
          })
        })
        .backgroundColor(this.oneButtonColor)
        .width(250)
        .height(70)
        .fontSize(16)
        .fontColor(Color.Black)
      Button("OnfocusUEA")
        .onClick(() => {
          router.pushUrl({
            url: 'pages/OnfocusUEA'
          })
        })
        .backgroundColor(this.oneButtonColor)
        .width(250)
        .height(70)
        .fontSize(16)
        .fontColor(Color.Black)
      //fontColor(Color.Black)
    }

    .height('100%')
    .width('100%')
  }
}