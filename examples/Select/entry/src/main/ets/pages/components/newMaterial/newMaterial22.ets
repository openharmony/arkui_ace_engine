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
struct SelectSystemMaterialSample22 {
  @State selectOption: SelectOption[] = [
    { value: '选项一' },
    { value: '选项二' },
    { value: '选项三' }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例22: 与其他组件组合布局')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Text('请选择您的偏好:')
        .fontSize(16)

      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect((index: number) => {
          this.selected = index
        })

      Button('确认选择')
        .onClick(() => {
          console.info('SelectSystemMaterialSample22: 确认选择 ' + this.selectOption[this.selected].value)
        })

      Text('说明: Select与Text、Button组件组合使用')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
