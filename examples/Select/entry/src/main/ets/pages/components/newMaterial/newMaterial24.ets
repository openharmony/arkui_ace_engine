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
struct SelectSystemMaterialSample24 {
  @State selectOption: SelectOption[] = [
    { value: '选项一' },
    { value: '选项二' },
    { value: '选项三' },
    { value: '选项四' },
    { value: '选项五' }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例24: 在ScrollView中使用Select')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Scroll() {
        Column({ space: 20 }) {
          Select(this.selectOption)
            .selected(this.selected)
            .value('请选择')
            .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
            .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
            .onSelect((index: number) => {
              this.selected = index
            })

          Text('这是一个很长的文本内容，用于测试ScrollView中的Select组件')
            .fontSize(14)
            .width('100%')

          Text('更多内容...')
            .fontSize(14)
            .width('100%')
        }
        .width('100%')
        .padding(20)
      }
      .width('100%')
      .height('60%')

      Text('说明: Select组件可以在ScrollView中使用')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
