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
struct bindContextMenuWithResponse_NONE {
  @State responseType: ResponseType = ResponseType.LongPress
  @State message: string = 'bindContextMenuWithResponse'

  @Builder
  MenuBuilder(responseType: ResponseType) {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Divider().height(10)
      Text('Response Type: ' + responseType.toString())
        .fontSize(16)
        .width(200)
        .height(30)
        .textAlign(TextAlign.Center)
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
      Button('bindContextMenuWithResponse NONE')
        .margin(20)
        .bindContextMenuWithResponse(this.MenuBuilder, {
          systemMaterial: new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }),
          backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
          onAppear: () => {
            console.info('Context menu appeared')
          },
          onDisappear: () => {
            console.info('Context menu disappeared')
          }
        })

      Text('Right click or long press to show context menu')
        .fontSize(16)
        .margin(20)

      Row() {
        Radio({ value: 'LongPress', group: 'responseType' })
          .checked(this.responseType === ResponseType.LongPress)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.responseType = ResponseType.LongPress
            }
          })
        Text('LongPress')
          .fontSize(16)
          .margin({ left: 5 })

        Radio({ value: 'RightClick', group: 'responseType' })
          .checked(this.responseType === ResponseType.RightClick)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.responseType = ResponseType.RightClick
            }
          })
          .margin({ left: 20 })
        Text('RightClick')
          .fontSize(16)
          .margin({ left: 5 })
      }
      .margin(20)
    }
    .width('100%')
    .height('100%')
  }
}
