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

@Entry
@Component
struct Index {
  stack: NavPathStack = new NavPathStack()

  @Builder
  pageMap(name: string) {
    if (name) {
     PageOne()
    }
  }

  aboutToAppear(): void {
    this.stack.pushPath({ name: 'pageOne' })
  }

  build() {
    Navigation(this.stack) {

    }.navDestination(this.pageMap)
    .hideNavBar(true)
  }
}

@Component
struct PageOne {
  stack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Button('push pageOne x2').margin(20)
        .onClick(() => {
          this.stack.pushPath({ name: 'pageOne' })
          this.stack.pushPath({ name: 'pageOne' })
        })
    }.onReady((ctx) => {
      this.stack = ctx.pathStack
    })
    .title('page one')
  }
}