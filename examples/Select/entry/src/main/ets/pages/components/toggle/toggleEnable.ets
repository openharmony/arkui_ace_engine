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

@Builder
export function ToggleEnableBuilder(name: string, param: Object) {
  ToggleEnableExample()
}

@Entry
@Component
struct ToggleEnableExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('手柄在enable,false的情况下，有透明度')
          .margin({ top: 50, bottom: 50 })

        Toggle({ type: ToggleType.Switch })
          .enabled(false)

      }
      .width('100%')
      .padding(24)
      .height('100%')
      .backgroundColor(Color.Pink)
    }
    .title('ToggleEnable')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { ToggleEnableExample };