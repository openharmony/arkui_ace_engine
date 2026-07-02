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

// [Start dynamic_response_mouse_hover]
@Entry
@Component
export struct Hover {
  @State hoverText: string = 'Not Hover';
  @State color: Color = Color.Gray;

  build() {
    NavDestination() {
      Column({ space: 12 }) {

        Column() {
          Button(this.hoverText)
            .width(200).height(100)
            .backgroundColor(this.color)
            .onHover((isHover?: boolean) => { // 使用onHover接口监听鼠标是否悬浮在Button组件上
              if (isHover) {
                this.hoverText = 'Hovered!';
                this.color = Color.Green;
              } else {
                this.hoverText = 'Not Hover';
                this.color = Color.Gray;
              }
            })
        }.width('100%').height('100%').justifyContent(FlexAlign.Center)

      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.Device_OnHover_title')替换为实际资源文件，在本示例中该资源文件的value值为"悬浮事件"
    .title($r('app.string.Device_OnHover_title'))
  }
}
// [End dynamic_response_mouse_hover]