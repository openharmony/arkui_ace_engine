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
import patternLockRegularColorTest from '../MyTest/PatternLockRegularColorTest'

@Entry
@Component
struct PatternLockRegularColorSample {
  @State regularColorType: ResourceColor = 0xff0000

  aboutToAppear(): void {
    loadComponentTestEntry(patternLockRegularColorTest)
  }

  build() {
    Column() {
      PatternLock()
        .regularColor(Color.Grey)
        .height(50)
        .id('patternLockRegularColor1')
      PatternLock()
        .regularColor(this.regularColorType)
        .height(50)
        .id('patternLockRegularColor2')
      Button('PatternLockRegularColor1')
        .onClick(() => {
          this.regularColorType = '#008000'
        })
      Button('PatternLockRegularColor2')
        .onClick(() => {
          this.regularColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}