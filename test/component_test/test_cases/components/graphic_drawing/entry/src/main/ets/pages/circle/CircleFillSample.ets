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
import circleFillTest from '../MyTest/CircleFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CircleFillSample {
  @State private fillColorValue1: ResourceColor = 0xff0000
  @State private fillColorValue2: ResourceColor = $r('sys.color.ohos_id_color_text_hyperlink')

  aboutToAppear(): void {
    loadComponentTestEntry(circleFillTest)
  }

  build() {
    Column({ space: 10 }) {
      Circle({ width: 150, height: 150 })
        .fill(this.fillColorValue1)
        .id('circleFill1')
      Button('CircleFill1')
        .onClick(() => {
          this.fillColorValue1 = '#FFF07DDF'
        })
      Circle({ width: 150, height: 150 })
        .fill(this.fillColorValue2)
        .id('circleFill2')
      Button('CircleFill2')
        .onClick(() => {
          this.fillColorValue2 = Color.Blue
        })
    }.width('100%')
  }
}

