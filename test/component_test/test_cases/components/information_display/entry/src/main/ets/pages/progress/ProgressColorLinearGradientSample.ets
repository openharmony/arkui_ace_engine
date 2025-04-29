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
import progressColorLinearGradientTest from '../MyTest/ProgressColorLinearGradientTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressColorLinearGradientSample {
  @State value: number = 50
  public colorShadow: LinearGradient = new LinearGradient([{ color: "#FFFF00AA", offset: 0.1 },
    { color: "#ff254ff7", offset: 0.5 }])
  public Shadow: LinearGradient = new LinearGradient([{
    color: $r("app.color.progress_linear_gradient_color1"),
    offset: 0.1
  },
    { color: $r("app.color.progress_linear_gradient_color2"), offset: 0.5 }])
  @State progressColorShadow: LinearGradient = this.colorShadow
  @State progressShadow: LinearGradient = this.Shadow

  aboutToAppear(): void {
    loadComponentTestEntry(progressColorLinearGradientTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: this.value, total: 100, type: ProgressType.Linear })
        .color(this.progressColorShadow)
        .id('progressColorLinearGradient1')
      Button('ProgressColorLinearGradient1')
        .onClick(() => {
          this.colorShadow = new LinearGradient([{ color: 0x0000ff, offset: '10px' },
            { color: 0xffffff, offset: '15px' }])
        })
      Progress({ value: this.value, total: 100, type: ProgressType.Linear })
        .color(this.progressShadow)
        .id('progressColorLinearGradient2')
    }
  }
}