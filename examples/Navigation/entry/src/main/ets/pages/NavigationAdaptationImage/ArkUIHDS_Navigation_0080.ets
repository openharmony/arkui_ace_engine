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

import { PageOneTmp } from './PageOne'
import { pageTwoTmp } from './PageTwo'
import { Pages } from './PageTwo'
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';

@Entry
@Component
export struct Navigation80 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @State navBarPosition:NavBarPosition = NavBarPosition.Start
  @State icon1: SymbolGlyphModifier= new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus'))
  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp({ names: name, values: this.pageInfos } as Pages)
    }
  }
  @Builder NavigationTitle() {
    Row() {
      Column() {
        Text('自定义标题')
          .fontColor('red')
          .fontSize(30)
          .lineHeight(41)
          .fontWeight(700)
        Text('自定义副标题')
          .fontColor('red')
          .fontSize(14)
          .lineHeight(19)
          .opacity(0.4)
          .margin({ top: 2, bottom: 20 })
      }
    }
  }
  build() {
    Column() {
      Navigation(this.pageInfos) {
        Column({space: 10}) {
          Button('navBarPosition.start')
            .onClick(() => {
              this.navBarPosition = NavBarPosition.Start
            })
          Button('navBarPosition.end')
            .onClick(() => {
              this.navBarPosition = NavBarPosition.End
            })
        }
      }
      .title({ builder: this.NavigationTitle, height: 82 })
      .navDestination(this.PageMap)
      .menus([
        {
          icon: 'resources/base/media/startIcon.png',
          value: 'item1',
        },
        {
          value: 'item2',
          icon: 'resources/base/media/startIcon.png',
        }
      ])
      .toolbarConfiguration([
        {
          value: 'first',
          icon: $r('app.media.startIcon')
        },
        {
          value: 'second',
          icon: $r('app.media.startIcon')
        },
        {
          value: 'third',
          icon: $r('app.media.startIcon')
        },
        {
          value: '44444',
          icon: $r('app.media.startIcon')
        },
        {
          value: '55555',
          icon: $r('app.media.startIcon')
        },
        {
          value: '66666',
          icon: $r('app.media.startIcon')
        },
        {
          value: '77777',
          icon: $r('app.media.startIcon')
        }
      ])
      .backButtonIcon(this.icon1)
      .hideTitleBar(false)
      .hideToolBar(false)
      .navBarPosition(this.navBarPosition)
      .onTitleModeChange((titleModel: NavigationTitleMode) => {
        console.info('titleMode' + titleModel)
      })
    }
  }
}
