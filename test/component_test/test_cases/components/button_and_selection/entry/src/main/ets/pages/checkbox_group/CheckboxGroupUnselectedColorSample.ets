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
import checkboxGroupUnSelectedColorTest from '../MyTest/CheckboxGroupUnselectedColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CheckboxGroupUnSelectedColorSample {
  @State unSelectedCol: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(checkboxGroupUnSelectedColorTest)
  }

  build() {
    Column() {
      CheckboxGroup({ group: 'checkboxGroup1' }).unselectedColor(Color.Black).id('checkboxGroupUnSelectedColor1')
      CheckboxGroup({ group: 'checkboxGroup2' }).unselectedColor(0xa52a2a).id('checkboxGroupUnSelectedColor2')
      CheckboxGroup({ group: 'checkboxGroup3' }).unselectedColor(this.unSelectedCol).id('checkboxGroupUnSelectedColor3')

      Button('CheckboxGroupUnSelectedColor').onClick(() => {
        this.unSelectedCol = $r('sys.color.ohos_fa_palette1')
      })
    }.width('100%').padding(24)
  }
}