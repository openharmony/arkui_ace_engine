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

import { Entry, Component, NavDestination, Column, Row, List, ListItem, Stack, Text, FocusDrawLevel, FontWeight, $r } from '@ohos.arkui.component';

@Entry
@Component
export struct AccessibilityFocusDrawLevel {
  build(): void {
    NavDestination() {
      Row() {
        List() {
          ListItem() {
            Column() {
              Stack() {
                Column() {
                  Text($r('app.string.UniversalAttributesAccessibility_text5'))
                  Text($r('app.string.UniversalAttributesAccessibility_text5'))
                    .accessibilityFocusDrawLevel(FocusDrawLevel.TOP)
                }

                Column() {
                  Text($r('app.string.UniversalAttributesAccessibility_text6'))
                  Text($r('app.string.UniversalAttributesAccessibility_text6'))
                }
              }

              Column() {
                Text($r('app.string.UniversalAttributesAccessibility_text9'))
                  .fontSize(50)
                  .fontWeight(FontWeight.Bold)
                Text('UIExtensionComponent placeholder (not available in static mode)')
                  .fontSize(14)
                  .fontColor('#999999')
              }
              .width('100%')
              .height('100%')
              .accessibilityText($r('app.string.UniversalAttributesAccessibility_text7'))
              .accessibilityDescription($r('app.string.UniversalAttributesAccessibility_text8'))

              Column() {
                Text($r('app.string.UniversalAttributesAccessibility_text10'))
                  .fontSize(50)
                  .fontWeight(FontWeight.Bold)
              }
            }
          }
        }.accessibilityScrollTriggerable(false)
      }
      .height('100%')
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.UniversalAttributesAccessibility_title3'))
  }
}
