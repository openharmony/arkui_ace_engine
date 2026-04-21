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
struct SelectSystemMaterialSample21 {
  @State selectOption: SelectOption[] = [
    { value: '首页', icon: $r('app.media.startIcon') },
    { value: '发现', icon: $r('app.media.startIcon') },
    { value: '消息', icon: $r('app.media.startIcon') },
    { value: '我的', icon: $r('app.media.startIcon') }
  ]
  @State selected: number = 0

  build() {
    Column({ space: 20 }) {
      Text('Select新材质示例21: 带icon的选项')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })

      Select(this.selectOption)
        .selected(this.selected)
        .value('请选择')
        .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .menuSystemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
        .onSelect((index: number) => {
          this.selected = index
          console.info('SelectSystemMaterialSample21: selected ' + this.selectOption[index].value)
        })

      Text('说明: 选项带有icon属性，使用半透明材质')
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
