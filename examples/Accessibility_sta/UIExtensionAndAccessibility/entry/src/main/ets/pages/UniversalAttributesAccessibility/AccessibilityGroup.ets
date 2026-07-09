'use static';
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { Entry, Component, NavDestination, Column, ColumnOptions, Text, Button, $r } from '@ohos.arkui.component';

@Entry
@Component
export struct AccessibilityGroup {
  build(): void {
    NavDestination() {
      Column({ space: 10 } as ColumnOptions) {
        Text('123456')
          .focusable(true)
          .borderRadius(5)
          .accessibilityText($r('app.string.UniversalAttributesAccessibility_text1'))
          .accessibilityLevel('yes')
        Button().accessibilityLevel('yes').accessibilityText($r('app.string.UniversalAttributesAccessibility_text2'))
        Button($r('app.string.UniversalAttributesAccessibility_text3')).accessibilityLevel('yes')
        Button()
        Button('btn123').accessibilityText($r('app.string.UniversalAttributesAccessibility_text4')).accessibilityLevel('yes')
        Button('btn123').accessibilityLevel('yes')
      }
      .accessibilityGroup(true, { accessibilityPreferred: true })
      .borderWidth(5)
      .width('100%')
      .height('100%')
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.UniversalAttributesAccessibility_title2'))
  }
}
