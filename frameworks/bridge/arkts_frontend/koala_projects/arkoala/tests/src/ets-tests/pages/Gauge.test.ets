/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct GaugeTest {
  build() {
      Gauge({ value: 7, min: 3, max: 8 })
      .startAngle(1)
      .endAngle(99)
      .strokeWidth("5px")
      .indicator({icon: "path/to/icon", space: 7})
      .trackShadow({radius: 77, offsetX: 88, offsetY: 99})
      .colors([
                [new LinearGradient([{color: "0x111111", offset: 1}, {color: "0x222222", offset: 2}]), 7],
                [new LinearGradient([{color: "0x333333", offset: 3}, {color: "0x555555", offset: 5}]), 8]
              ])

      Gauge({ value: 7, min: 3, max: 8 })
      .colors([
                ["0x777777", 7],
                ["0x999999", 9]
              ])

      Gauge({ value: 7, min: 3, max: 8 })
      .colors(new LinearGradient([{color: "0x111111", offset: 3}, {color: "0x222222", offset: 5}]))

      Gauge({ value: 7, min: 3, max: 8 })
      .colors("0x111111")
  }
}
