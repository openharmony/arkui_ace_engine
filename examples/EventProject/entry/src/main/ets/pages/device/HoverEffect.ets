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

// [Start mouse_hover_effect]
@Entry
@Component
export struct HoverEffectSample {
  @State buttonText: string = '';
  @State columnText: string = '';
  @State hoverText: string = 'Not Hover';
  @State color: Color = Color.Gray;

  build() {
    NavDestination() {
      Column({ space: 12 }) {

        Column({ space: 10 }) {
          Button('Auto')
            .width(170).height(70)
          Button('Scale')
            .width(170).height(70)
            .hoverEffect(HoverEffect.Scale)
          Button('Highlight')
            .width(170).height(70)
            .hoverEffect(HoverEffect.Highlight)
          Button('None')
            .width(170).height(70)
            .hoverEffect(HoverEffect.None)
        }.width('100%').height('100%').justifyContent(FlexAlign.Center)

      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.HoverEffectSample_title')替换为实际资源文件，在本示例中该资源文件的value值为"悬浮状态"
    .title($r('app.string.HoverEffectSample_title'))
  }
}
// [End mouse_hover_effect]