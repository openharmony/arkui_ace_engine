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

import { SymbolGlyphModifier } from '@kit.ArkUI'

@Builder
export function PageEightWithToolBarBuilder(name: string, param: Object) {
  PageEightWithToolBar()
}

@Component
export struct  PageEightWithToolBar {
  @State toolItemStatus: ToolbarItemStatus = ToolbarItemStatus.NORMAL
  @State toolbar1: Array<ToolbarItem>= [
    {
      value:'toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1toolItem1Item1Item1',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
      status:ToolbarItemStatus.NORMAL
    },
    {
      value:'toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2toolItem2',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
      status:ToolbarItemStatus.DISABLED
    },
    {
      value:'toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3toolItem3',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
      status:ToolbarItemStatus.ACTIVE
    },
    {
      value:'toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4toolItem4',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
    },
    {
      value:'toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5toolItem5',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
    },
    {
      value:'toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6toolItem6',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
    },
    {
      value:'Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7Item7',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')),
      activeSymbolIcon:new SymbolGlyphModifier($r('sys.symbol.ohos_circle')),
    }
  ]

  build() {
    NavDestination(                                                                                                  ){
      Column({ space: '5vp' }) {
        Button("status: NORMAL")
          .onClick(() => {
            this.toolItemStatus = ToolbarItemStatus.NORMAL
          })
        Button("status: DISABLED")
          .onClick(() => {
            this.toolItemStatus = ToolbarItemStatus.DISABLED
          })
        Button("status: ACTIVE")
          .onClick(() => {
            this.toolItemStatus = ToolbarItemStatus.ACTIVE
          })
      }
    }
    .width('100%')
    .height('100%')
    .title('This is navDestination')
    .toolbarConfiguration(this.toolbar1)
  }
}