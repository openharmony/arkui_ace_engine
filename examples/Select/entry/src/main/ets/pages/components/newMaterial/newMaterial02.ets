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
struct SelectSystemMaterialSample20 {
  @State selectOption: SelectOption[] = [
    { value: '春' },
    { value: '夏' },
    { value: '秋' },
    { value: '冬' }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例20: 季节选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择季节')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect((index: number) => {
          this.selected = index
          console.info('SelectSystemMaterialSample20: 选择了季节: ' + this.selectOption[index].value)
        })

      Text('已选择: ' + (this.selectOption[this.selected]?.value || '未选择'))
        .fontSize(18)
        .fontColor(Color.Green)

      Text('说明: 季节选择示例，使用半透明材质')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}