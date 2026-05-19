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
// [Start crown_event]
// xxx.ets
@Entry
@Component
struct Index {
  @State message: string = 'onDigitalCrown';

  build() {
    Column() {
      Row() {
        Stack() {
          // [Start text]
          Text(this.message)
            .fontSize(20)
            .fontColor(Color.White)
            .backgroundColor("#262626")
            .textAlign(TextAlign.Center)
            .focusable(true)
            .focusOnTouch(true)
            .defaultFocus(true)
            // [End text]
            .borderWidth(2)
            .width(223)
            .height(223)
            .borderRadius(110)
            // [Start onDigitalCrown]
            .onDigitalCrown((event: CrownEvent) => {
              // [StartExclude onDigitalCrown]
              // [Start stopPropagation]
              event.stopPropagation();
              this.message = "CrownEvent\n\n" + JSON.stringify(event);
              hilog.debug(0x0000, 'Tag',
                "action:%{public}d, angularVelocity:%{public}f, degree:%{public}f, timestamp:%{public}f",
                event.action, event.angularVelocity, event.degree, event.timestamp);
              // [End stopPropagation]
              // [EndExclude onDigitalCrown]
            })
          // [End onDigitalCrown]
        }.width("100%").height("100%")
      }.width("100%").height("100%")
    }
  }
}
// [End crown_event]