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

@Builder
export function PageSixWithToolBarBuilder(name: string, param: Object) {
  PageSixWithToolBar()
}

@Component
export struct  PageSixWithToolBar {
  @State toolbar1: Array<ToolbarItem>= [
    {
      value:'toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1Item1Item1',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    },
    {
      value:'Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.startIcon"),
      action: () => {
        console.log("hello")
      }
    }
  ]

  build() {
    NavDestination(                                                                                                  ){
      Column({ space: '5vp' }) {
      }
    }
    .width('100%')
    .height('100%')
    .title('This is navDestination')
    .toolbarConfiguration(this.toolbar1)
  }
}