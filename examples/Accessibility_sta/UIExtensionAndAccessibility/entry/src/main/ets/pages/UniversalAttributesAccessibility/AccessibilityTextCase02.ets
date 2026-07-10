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
import { Entry, Component, NavDestination, Column, Image, ClickEvent, $r } from '@ohos.arkui.component';

// [Start accessibility_text_start02]
@Entry
@Component
export struct AccessibilityTextCase02 {
  build(): void {
    // [StartExclude accessibility_text_start02]
    NavDestination() {
      // [EndExclude accessibility_text_start02]
      Column() {
        // 需确保resource/base/media目录下图标存在，可用其他图标替换演示。
        Image($r('app.media.play'))
          .width(60)
          .height(60)
          .onClick((event: ClickEvent) => {
            // 播放音频、视频的核心逻辑
          })
          .accessibilityText('播放')
      }
      .backgroundColor('#f1f2f3')
      // [StartExclude accessibility_text_start02]
    }
    // [EndExclude accessibility_text_start02]
  }
}
// [End accessibility_text_start02]