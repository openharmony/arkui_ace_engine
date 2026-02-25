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

import uiMaterial from "@ohos.arkui.uiMaterial"

@Entry
@Component
struct bindContextMenu_isShown_content_without_material {
  @State isShow: boolean = false
  @State message: string = 'bindContextMenu_isShown_content'

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Divider().height(10)
      Text('Menu Item 1')
        .fontSize(20)
        .width(200)
        .height(30)
        .textAlign(TextAlign.Center)
      Text('Menu Item 2')
        .fontSize(20)
        .width(200)
        .height(30)
        .textAlign(TextAlign.Center)
    }
  }

  build() {
    Column() {
      Button('bindContextMenu isShown+content without material')
        .margin(20)
        .bindContextMenu(this.isShow, this.MenuBuilder, {
          aboutToDisappear: () => {
            this.isShow = false
          }
        })

      Text('Current isShow state: ' + this.isShow)
        .fontSize(16)
        .margin(10)

      Button('Show Context Menu')
        .margin(10)
        .onClick(() => {
          this.isShow = true
        })
    }
    .width('100%')
    .height('100%')
  }
}
