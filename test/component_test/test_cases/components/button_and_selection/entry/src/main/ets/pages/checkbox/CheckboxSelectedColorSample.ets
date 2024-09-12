/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

// 测试代码路径
import checkboxSelectedColorTest from '../MyTest/CheckboxSelectedColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CheckboxSelectedColorSample {
  @State selectedColorTest: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(checkboxSelectedColorTest)
  }

  build() {
    Column() {
      Checkbox({ name: 'checkbox1' }).selectedColor(Color.Black).id('checkboxSelectedColor1')
      Checkbox({ name: 'checkbox2' }).selectedColor(0xa52a2a).id('checkboxSelectedColor2')
      Checkbox({ name: 'checkbox3' }).selectedColor(this.selectedColorTest).id('checkboxSelectedColor3')

      Button('CheckboxSelectedColor').onClick(() => {
        this.selectedColorTest = $r('sys.color.ohos_fa_palette1')
      })
    }
  }
}