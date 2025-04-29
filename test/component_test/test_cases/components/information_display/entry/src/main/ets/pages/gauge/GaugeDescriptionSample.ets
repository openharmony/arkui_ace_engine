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
import gaugeDescriptionTest from '../MyTest/GaugeDescriptionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeDescriptionSample {
  @Builder
  descriptionBuilder() {
    Text('GaugeDescription')
      .maxFontSize('30sp')
      .minFontSize("10.0vp")
      .fontColor("#fffa2a2d")
      .fontWeight(FontWeight.Medium)
      .width('100%')
      .height("100%")
      .textAlign(TextAlign.Center)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeDescriptionTest)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .description(this.descriptionBuilder)
        .id('gaugeDescription')
    }
  }
}