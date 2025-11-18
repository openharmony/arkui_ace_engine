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
struct Test1 {
  private stack: NavPathStack = new NavPathStack();
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'hello',
    },
    {
      value: 'hello',
    },
    {
      value: $r('app.media.startIcon'),
    },
    {
      value:  $r('app.float.menuValFloat'),
    },
    {
      value: $r('app.string.menuValString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    }
  ]

  @Builder
  PageBuilder(name: string) {
    pageOne()
  }

  build() {
    Navigation(this.stack) {
      Column() {
        Button('push pageOne').onClick(() => {
          this.stack.pushPath({name: 'pageOne'})
        })
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .menus(this.menuItems)
    .navDestination(this.PageBuilder)
  }
}

@Component
struct pageOne {
  @State pageTitle: string | Resource = 'This is NavDestination title'
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'hello',
    },
    {
      value: 'hello',
    },
    {
      value: $r('app.media.startIcon'),
    },
    {
      value:  $r('app.float.menuValFloat'),
    },
    {
      value: $r('app.string.menuValString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    },
    {
      value: $r('app.string.menuValLongString'),
    }
  ]
  build() {
    NavDestination() {
      Column() {
        Text('This is NavDestination content')
      }
    }
    .width('100%')
    .height('100%')
    .title(this.pageTitle)
    .menus(this.menuItems)
  }
}