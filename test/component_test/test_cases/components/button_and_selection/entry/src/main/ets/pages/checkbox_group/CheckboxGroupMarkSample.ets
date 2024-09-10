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
import checkboxGroupMarkTest from '../MyTest/CheckboxGroupMarkTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CheckboxGroupMarkSample {
  @State markColor: ResourceColor = 'rgb(142, 255, 101)'
  @State markStrok: number | Resource = 50

  aboutToAppear(): void {
    loadComponentTestEntry(checkboxGroupMarkTest)
  }

  build() {
    Flex() {
      Column() {
        CheckboxGroup({ group: 'checkboxGroup1' }).mark({
          strokeColor: Color.Black
        }).id('checkboxGroupMark1')
        CheckboxGroup({ group: 'checkboxGroup1' }).mark({
          strokeColor: 0xa52a2a
        }).id('checkboxGroupMark2')
        CheckboxGroup({ group: 'checkboxGroup1' }).mark({
          strokeColor: this.markColor
        }).id('checkboxGroupMark3')
      }

      Column() {
        CheckboxGroup({ group: 'checkboxGroup1' }).mark({
          size: '10px',
          strokeWidth: '10px'
        }).id('checkboxGroupMark4')
        CheckboxGroup({ group: 'checkboxGroup1' }).mark({
          size: this.markStrok,
          strokeWidth: this.markStrok
        }).id('checkboxGroupMark5')
        Button('CheckboxGroupMark1').onClick(() => {
          this.markColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('CheckboxGroupMark2').onClick(() => {
          this.markStrok = $r('app.string.mark_strok')
        })
      }
    }
  }
}