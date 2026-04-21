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

@Entry
@Component
struct Test22 {
  pathStack: NavPathStack = new NavPathStack();
  scroller: Scroller = new Scroller()
  build() {
    Navigation(this.pathStack){
      Scroll(this.scroller) {
        Column({space:'5vp'}) {
          Button('push pageSeven').onClick(() => {
            this.pathStack.pushPathByName('PageSevenWithToolBar', null)
          })

        }
      }
    }
    .width('100%')
    .height('100%')
    .title("Navigation")
    .navBarWidth(120)
    .minContentWidth(200)
    .navBarWidthRange([50,200])
  }
}