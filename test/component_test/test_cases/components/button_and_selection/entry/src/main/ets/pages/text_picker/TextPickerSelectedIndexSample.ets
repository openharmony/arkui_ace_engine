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
import textPickerSelectedIndexTest from '../MyTest/TextPickerSelectedIndexTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextPickerSelectedIndexSample {
  @State selectedIndexText: number = 3
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private multi: string[][] = [this.apfruits, this.orfruits]

  aboutToAppear(): void {
    loadComponentTestEntry(textPickerSelectedIndexTest)
  }

  build() {
    Column() {
      TextPicker({ range: this.apfruits }).selectedIndex(2).id('textPickerSelectedIndex1');
      TextPicker({ range: this.multi }).selectedIndex([this.selectedIndexText, 0]).id('textPickerSelectedIndex2');

      Button('TextPickerSelectedIndex').onClick(() => {
        this.selectedIndexText = 2
      })
    }
  }
}