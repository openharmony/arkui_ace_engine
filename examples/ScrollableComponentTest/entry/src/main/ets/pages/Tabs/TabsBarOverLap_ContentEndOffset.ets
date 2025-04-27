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
struct barBackgroundColorTest {
  private controller: TabsController = new TabsController()
  @State arr:number[] = []

  aboutToAppear(): void {
    for (let i = 0; i < 20; i++) {
      this.arr.push(i)
    }
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.End, index: 0, controller: this.controller }) {
        TabContent() {
          List() {
            ForEach(this.arr, (item:number)=> {
              ListItem() {
                Row() {
                  Image($r('app.media.startIcon')).size({width:64, height:64})
                  Text("item" + item.toString())
                  Blank()
                  Button("下载")
                }.width("100%").padding(12)
              }
            })
          }
          .contentEndOffset(56)
        }
        .tabBar(new BottomTabBarStyle($r('sys.media.ohos_app_icon'), "1"))
        TabContent()
        .tabBar(new BottomTabBarStyle($r('sys.media.ohos_app_icon'), "2"))
      }
      .barOverlap(true)
      .barBackgroundColor('#88888888')
    }
    .height('100%')
  }
}
