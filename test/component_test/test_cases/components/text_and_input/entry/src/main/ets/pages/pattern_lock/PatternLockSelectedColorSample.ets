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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import patternLockSelectedColorTest from '../MyTest/PatternLockSelectedColorTest'

@Entry
@Component
struct PatternLockSelectedColorSample {
  @State selectedColorType: ResourceColor = 0xff0000

  aboutToAppear(): void {
    loadComponentTestEntry(patternLockSelectedColorTest)
  }

  build() {
    Column() {
      PatternLock()
        .selectedColor(Color.Grey)
        .height(50)
        .id('patternLockSelectedColor1')
      PatternLock()
        .selectedColor(this.selectedColorType)
        .height(50)
        .id('patternLockSelectedColor2')
      Button('PatternLockSelectedColor1')
        .onClick(() => {
          this.selectedColorType = '#008000'
        })
      Button('PatternLockSelectedColor2')
        .onClick(() => {
          this.selectedColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}