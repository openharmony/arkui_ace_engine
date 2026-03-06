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
struct SelectSystemMaterialSample13 {
  @State selectOption: SelectOption[] = [
    { value: 'A' },
    { value: 'B' },
    { value: 'C' },
    { value: 'D' },
    { value: 'E' }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例13: 动态切换材质类型')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Button('切换材质类型')
        .onClick(() => {
          this.selected = (this.selected + 1) % 2
        })

      if (this.selected === 0) {
        Select(this.selectOption)
          .selected(0)
          .value('当前材质: SEMI_TRANSPARENT')
          .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .onSelect((index: number) => {
            console.info('SelectSystemMaterialSample13: selected index = ' + index)
          })
      } else {
        Select(this.selectOption)
          .selected(0)
          .value('当前材质: NONE')
          .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
          .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
          .onSelect((index: number) => {
            console.info('SelectSystemMaterialSample13: selected index = ' + index)
          })
      }

      Text('说明: 点击按钮可以在不同材质类型之间切换')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
