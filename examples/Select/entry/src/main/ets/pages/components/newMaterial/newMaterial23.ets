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
struct SelectSystemMaterialSample23 {
  @State selectOption1: SelectOption[] = [
    { value: '选项A' },
    { value: '选项B' }
  ]
  @State selectOption2: SelectOption[] = [
    { value: '选项C' },
    { value: '选项D' }
  ]
  @State selectOption3: SelectOption[] = [
    { value: '选项E' },
    { value: '选项F' }
  ]
  @State selected1: number = 0
  @State selected2: number = 0
  @State selected3: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例23: 垂直排列多个Select')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Select(this.selectOption1)
        .selected(this.selected1)
        .value('请选择第一项')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect(() => {
        })

      Select(this.selectOption2)
        .selected(this.selected2)
        .value('请选择第二项')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect(() => {
        })

      Select(this.selectOption3)
        .selected(this.selected3)
        .value('请选择第三项')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect(() => {
        })

      Text('说明: 垂直排列多个Select组件')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
