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
import { Entry, Component, NavDestination, Column, Text } from '@ohos.arkui.component';

// [Start accessibility_group_start02]
@Entry
@Component
export struct AccessibilityGroupCase02 {
  build(): void {
    // [StartExclude accessibility_group_start02]
    NavDestination() {
      // [EndExclude accessibility_group_start02]
      Column() {
        Text('2026年')
        Text('1月27日')
        Text('星期二')
      }
      .accessibilityGroup(true)
      // [StartExclude accessibility_group_start02]
    }
    // [EndExclude accessibility_group_start02]
  }
}
// [End accessibility_group_start02]