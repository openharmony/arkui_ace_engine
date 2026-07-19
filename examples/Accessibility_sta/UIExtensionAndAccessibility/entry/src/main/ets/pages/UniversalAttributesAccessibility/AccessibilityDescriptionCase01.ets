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
import { Entry, Component, NavDestination, Button, Color, ClickEvent } from '@ohos.arkui.component';

// [Start accessibility_description_start01]
@Entry
@Component
export struct AccessibilityDescriptionCase01 {
  build(): void {
    // [StartExclude accessibility_description_start01]
    NavDestination() {
      // [EndExclude accessibility_description_start01]
      Button("全屏")
        .width(96)
        .height(40)
        .background(Color.Blue)
        .onClick((event: ClickEvent) => {
          // 全屏逻辑
        })
      // [StartExclude accessibility_description_start01]
    }
    // [EndExclude accessibility_description_start01]
  }
}
// [End accessibility_description_start01]