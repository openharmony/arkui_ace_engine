/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { hilog } from '@kit.PerformanceAnalysisKit';
const DOMAIN = 0x0001;
const TAG = 'Sample_gesturebinding';
// [Start regular_binding]
// xxx.ets
@Entry
@Component
struct RegularBinding {
  build() {
    Column() {
      Text('Gesture').fontSize(28)
      // 采用gesture手势绑定方法绑定TapGesture
        .gesture(
          TapGesture()
            .onAction(() => {
              console.info('TapGesture is onAction');
            }))
    }
    .height(200)
    .width(250)
  }
}
//  [End regular_binding]