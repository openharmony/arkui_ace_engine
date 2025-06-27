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
export function ButtonJudgmentBuilder(name: string, param: Object) {
  ButtonJudgmentExample()
}

@Entry
@Component
struct ButtonJudgmentExample {
  @State count: number = 0;
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column() {
        Text(`${this.count}`)
          .fontSize(30)
          .onClick(() => {
            this.count++;
          })
        if (this.count <= 0) {
          Button('count is negative').fontSize(30).height(50)
        } else if (this.count % 2 === 0) {
          Button('count is even').fontSize(30).height(50)
        } else {
          Button('count is odd').fontSize(30).height(50)
        }
      }.height('100%').width('100%').justifyContent(FlexAlign.Center)
    }
    .title('ButtonJudgment')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}