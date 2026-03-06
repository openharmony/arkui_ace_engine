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
struct SelectSystemMaterialSample15 {
  @State selectOption1: SelectOption[] = [
    { value: '男' },
    { value: '女' }
  ]
  @State selectOption2: SelectOption[] = [
    { value: '18-25岁' },
    { value: '26-35岁' },
    { value: '36-45岁' },
    { value: '46岁以上' }
  ]
  @State selected1: number = 0
  @State selected2: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例15: 多个Select组合使用')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Row({ space: 20 }) {
        Text('性别:')
          .fontSize(16)
        Select(this.selectOption1)
          .selected(this.selected1)
          .value('请选择')
          .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .onSelect((index: number) => {
            this.selected1 = index
          })
      }

      Row({ space: 20 }) {
        Text('年龄:')
          .fontSize(16)
        Select(this.selectOption2)
          .selected(this.selected2)
          .value('请选择')
          .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
          .onSelect((index: number) => {
            this.selected2 = index
          })
      }

      Text('说明: 多个Select组件可以组合使用，都使用相同的材质设置')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
