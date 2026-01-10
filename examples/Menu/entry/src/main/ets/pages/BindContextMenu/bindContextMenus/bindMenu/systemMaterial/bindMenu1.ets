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
struct bindMenu {
  @State longPress: string = 'longPress'
  @State rightClick: string = 'rightClick'

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Divider().height(10)
      Text('Item: ' + this.longPress)
        .fontSize(20)
        .width(200)
        .height(20)
        .textAlign(TextAlign.Center)
      Text('Item: ' + this.rightClick)
        .fontSize(20)
        .width(200)
        .height(20)
        .textAlign(TextAlign.Center)
    }
  }

  build() {
    Column() {
      Button('bindMenu普通菜单不设置新材质')
        .bindMenu([
          {
            value: 'Menu1',
            action: () => {
              console.info('handle Menu1 select')
            }
          },
          {
            value: 'Menu2',
            action: () => {
              console.info('handle Menu2 select')
            }
          }
        ])
    }
  }
}