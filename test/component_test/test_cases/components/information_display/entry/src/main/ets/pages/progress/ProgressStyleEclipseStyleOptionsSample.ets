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
import progressStyleEclipseStyleOptionsTest from '../MyTest/ProgressStyleEclipseStyleOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressStyleEclipseStyleOptionsSample {
  @State style: EclipseStyleOptions = { enableSmoothEffect: true }

  aboutToAppear(): void {
    loadComponentTestEntry(progressStyleEclipseStyleOptionsTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 80, total: 100, type: ProgressType.Eclipse })
        .height(100)
        .width(200)
        .color(Color.Orange)
        .value(60)
        .width(100)
        .style(this.style)
        .id('progressStyleEclipseStyleOptions')
      Button('ProgressStyleEclipseStyleOptions')
        .onClick(() => {
          this.style = { enableSmoothEffect: false }
        })
    }
  }
}