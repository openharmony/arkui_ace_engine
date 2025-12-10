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

import { promptAction } from "@kit.ArkUI"

@ComponentV2
export struct HomeTitle {
  @Param titleName: string = '__NA__'

  build() {
    Column() {
      Row() {
        Row() {
          Text(this.titleName)
            .fontFamily("HarmonyHeiTi")
            .fontColor("#000000")
            .fontSize(20)
            .fontWeight(700)
        }
        .height('100%')
        .width('50%')
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.Start)

        Row() {
          TitleMenu({ name: 'menu one' })
            .margin({ right: 8 })
          TitleMenu({ name: 'x_icon' })
        }
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.End)
        .height('100%')
        .width('50%')
      }
      .height(56)
      .width(618)
    }
    .height(64)
    .width('100%')
    .padding({ left: 16, right: 16, top: 8 })
  }
}

@ComponentV2
struct TitleMenu {
  @Param name: string = '__NA__';

  build() {
    Image('')
      .width(40)
      .height(40)
      .borderRadius(20)
      .backgroundColor('rgba(0,0,0,0.05)')
      .onClick(() => {
        promptAction.openToast({ message: `${this.name} clicked` })
          .then(() => {})
          .catch(() => {})
      })
  }
}