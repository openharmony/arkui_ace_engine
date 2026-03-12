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

import I18n from '@ohos.i18n';
import { BusinessError } from '@ohos.base'
@Builder
export function PageSevenWithToolBarBuilder(name: string, param: Object) {
  PageSevenWithToolBar()
}

@Component
export struct  PageSevenWithToolBar {
  @State toolItemStatus: ToolbarItemStatus = ToolbarItemStatus.NORMAL
  @State toolbar1: Array<ToolbarItem>= [
    {
      value:'toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1Item1Item1',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.360"),
      action: () => {
        console.log("hello")
      },
      status: ToolbarItemStatus.NORMAL
    },
    {
      value:'toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: ToolbarItemStatus.DISABLED
    },
    {
      value:'toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: ToolbarItemStatus.ACTIVE
    },
    {
      value:'toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: ToolbarItemStatus.ACTIVE
    },
    {
      value:'toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: this.toolItemStatus
    },
    {
      value:'toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: this.toolItemStatus
    },
    {
      value:'Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7',
      icon: $r("app.media.foreground"),
      activeIcon: $r("app.media.354"),
      action: () => {
        console.log("hello")
      },
      status: this.toolItemStatus
    }
  ]
  @State hideToolBar: boolean = false;
  @State hideTitleBar: boolean = false;
  @State safeAreaEdge: Array <LayoutSafeAreaEdge>	= [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
  @State language: string = I18n.System.getAppPreferredLanguage();

  build() {
    NavDestination(                                                                                                  ){
      Column({ space: '5vp' }) {

        Button("hideToolBar: true")
          .onClick(() => {
            this.hideToolBar = true
          })
        Button("hideToolBar: false")
          .onClick(() => {
            this.hideToolBar = false
          })

        Button("hideTitleBar: true")
          .onClick(() => {
            this.hideTitleBar = true
          })
        Button("hideTitleBar: false")
          .onClick(() => {
            this.hideTitleBar = false
          })


        Button("ignoreLayoutSafeArea edges: TOP")
          .onClick(() => {
            this.safeAreaEdge = [LayoutSafeAreaEdge.TOP]
          })
        Button("ignoreLayoutSafeArea edges: BOTTOM")
          .onClick(() => {
            this.safeAreaEdge = [LayoutSafeAreaEdge.BOTTOM]
          })
        Button("ignoreLayoutSafeArea edges: TOP和BOTTOM")
          .onClick(() => {
             this.safeAreaEdge = [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
          })

        Column() {


          Button("zh-Hans(汉语)").onClick(() => {
            console.log("getAppPreferredLanguage last " + I18n.System.getAppPreferredLanguage());
            try {
              I18n.System.setAppPreferredLanguage("zh-Hans");
              let val = I18n.System.getAppPreferredLanguage();
              this.language = val;
              console.log("getAppPreferredLanguage new " + val);
            } catch (error) {
              let err: BusinessError = error as BusinessError;
              console.error(`call System.setAppPreferredLanguage failed, error code: ${err.code}, message: ${err.message}.`);
            }
          })
          Button("ug(维吾尔语)").onClick(() => {
            console.log("getAppPreferredLanguage last " + I18n.System.getAppPreferredLanguage());
            try {
              I18n.System.setAppPreferredLanguage("ug");
              let val = I18n.System.getAppPreferredLanguage();
              this.language = val;
              console.log("getAppPreferredLanguage new " + val);
            } catch (error) {
              let err: BusinessError = error as BusinessError;
              console.error(`call System.setAppPreferredLanguage failed, error code: ${err.code}, message: ${err.message}.`);
            }
          })
        }
      }.backgroundColor(Color.Green).width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .title('This is navDestination')
    .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], this.safeAreaEdge)
    .toolbarConfiguration(this.toolbar1,{backgroundColor: '#80004AAF', backgroundBlurStyle:BlurStyle.BACKGROUND_THIN})
    .hideTitleBar(this.hideTitleBar)
    .hideToolBar(this.hideToolBar)
    .backgroundColor(Color.Pink)
  }
}