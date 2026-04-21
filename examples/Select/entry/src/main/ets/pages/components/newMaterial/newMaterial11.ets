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
struct SelectSystemMaterialSample11 {
  @State selectOption: SelectOption[] = [
    { value: '红色' },
    { value: '绿色' },
    { value: '蓝色' },
    { value: '黄色' }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例11: 不同材质组合对比')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Text('Select 1: 两个参数都为SEMI_TRANSPARENT')
        .fontSize(16)
        .margin({ top: 10 })
      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择颜色')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect((index: number) => {
          this.selected = index
        })

      Text('Select 2: 两个参数都为NONE')
        .fontSize(16)
        .margin({ top: 10 })
      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择颜色')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
        .onSelect((index: number) => {
          this.selected = index
        })

      Text('Select 3: systemMaterial为SEMI_TRANSPARENT, menuSystemMaterial为NONE')
        .fontSize(16)
        .margin({ top: 10 })
      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择颜色')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
        .onSelect((index: number) => {
          this.selected = index
        })

      Text('Select 4: systemMaterial为NONE, menuSystemMaterial为SEMI_TRANSPARENT')
        .fontSize(16)
        .margin({ top: 10 })
      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择颜色')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect((index: number) => {
          this.selected = index
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
