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

@Entry
@Component
export struct Navigation60 {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp({ names: name, values: this.pageInfos } as Pages)
    }
  }

  build() {
    Column() {
      Navigation(this.pageInfos) {
        Navigation() {
          Button('PushPath', { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(20)
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageOne' })
            })
        }
        .title('内层Navigation')
        .subTitle("subtitle")
        .menus([
          {
            icon: 'resources/base/media/startIcon.png',
            value: 'item1',
          },
          {
            value: 'item2',
            icon: 'resources/base/media/foreground.png',
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
        .hideTitleBar(false)
        .hideToolBar(false)
        .onTitleModeChange((titleModel: NavigationTitleMode) => {
          console.info('titleMode' + titleModel)
        })

        Column() {
        }
      }
      .title('外层Navigation')
      .navDestination(this.PageMap)
      .subTitle("subtitle")
      .menus([
        {
          icon: 'resources/base/media/startIcon.png',
          value: 'item1',
        },
        {
          value: 'item2',
          icon: 'resources/base/media/startIcon.png',
        },
        {
          value: 'item3',
          icon: 'resources/base/media/startIcon.png'

        },
        {
          value: 'item4',
          icon: 'resources/base/media/startIcon.png'
        },
        {
          value: 'item5',
          icon: 'resources/base/media/startIcon.png'
        },
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
      .hideTitleBar(false)
      .hideToolBar(false)
      .onTitleModeChange((titleModel: NavigationTitleMode) => {
        console.info('titleMode' + titleModel)
      })
    }
  }
}
