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

import { Entry, Component, Builder, NavDestination, Column, Text, FontWeight, Row, Image, Button, ClickEvent, $r } from '@ohos.arkui.component';

// [Start accessibility_text_start]
@Entry
@Component
export struct AccessibilityText {
  @Builder
  customAccessibilityNode(): void {
    Column() {
      Text(`virtual node`)
    }
    .width(10)
      .height(10)
  }

  build(): void {
    // [StartExclude accessibility_text_start]
    NavDestination() {
      // [EndExclude accessibility_text_start]
      Row() {
        // [StartExclude accessibility_text_start]
        // [Start accessibility_group_start]
        Column() {
          Text('HelloWorld').fontSize(50).fontWeight(FontWeight.Bold)
        }
        .accessibilityGroup(true)

        // [End accessibility_group_start]
        // [Start accessibility_level_start]
        Column() {
          Text('HelloWorld').fontSize(50).fontWeight(FontWeight.Bold)
        }
        .accessibilityGroup(true)
          .accessibilityLevel('yes')

        // [End accessibility_level_start]
        // [Start accessibility_text_group_start]
        Column() {
          // 需确保resource/base/media目录下图标存在，可用其他图标替换演示。
          Image($r('app.media.play')) // 仅图标，无默认文本
          .width(60)
          .height(60)
          .accessibilityText($r('app.string.UniversalAttributesAccessibility_text12'))
          .onClick((event: ClickEvent) => {
              // 播放音频、视频的核心逻辑
          })
        }

        // [End accessibility_text_group_start]
        // [Start accessibility_description_start]
        Column() {
          Button()
          .width(120)
          .height(40)
          .accessibilityLevel('yes')
          .accessibilityText($r('app.string.UniversalAttributesAccessibility_text12'))
          .accessibilityDescription($r('app.string.UniversalAttributesAccessibility_text13'))
          .onClick((event: ClickEvent) => {
              // 播放音频、视频的核心逻辑
          })
        }

        // [End accessibility_description_start]
        // [Start accessibility_checked_start]
        Column() {
          Text('HelloWorld').fontSize(50).fontWeight(FontWeight.Bold)
        }
        .accessibilityGroup(true)
          .accessibilityLevel('yes')
          .accessibilityText('分组')
          .accessibilityDescription('Column组件可以被选中，播报的内容是"分组"')
          .accessibilityChecked(true)

        // [End accessibility_checked_start]
        // [Start accessibility_selected_start]
        Column() {
          Text('HelloWorld').fontSize(50).fontWeight(FontWeight.Bold)
        }
        .accessibilityGroup(true)
          .accessibilityLevel('yes')
          // 请将$r('app.string.UniversalAttributesAccessibility_text7')替换为实际资源文件，在本示例中该资源文件的value值为"分组"
          .accessibilityText('分组')
          .accessibilityDescription('Column组件可以被选中，播报的内容是"分组"')
          .accessibilitySelected(undefined)

        // [End accessibility_selected_start]
        // [EndExclude accessibility_text_start]
        Column() {
          Text('文本1')
            .fontSize(50)
            .fontWeight(FontWeight.Bold)
          Text('文本2')
            .fontSize(50)
            .fontWeight(FontWeight.Bold)
        }
        .width('100%')
          .accessibilityGroup(true)
          .accessibilityLevel('yes')
          .accessibilityText('分组')
          .accessibilityDescription('Column组件可以被选中，播报的内容是"分组"')
          .accessibilityVirtualNode(this.customAccessibilityNode)
          .accessibilityChecked(true)
          .accessibilitySelected(undefined)
      }
      .height('100%')
      //[StartExclude accessibility_text_start]
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.UniversalAttributesAccessibility_title1')替换为实际资源文件，在本示例中该资源文件的value值为"使用无障碍属性 1"
    .title($r('app.string.UniversalAttributesAccessibility_title1'))
    //[EndExclude accessibility_text_start]
  }
}
// [End accessibility_text_start]
