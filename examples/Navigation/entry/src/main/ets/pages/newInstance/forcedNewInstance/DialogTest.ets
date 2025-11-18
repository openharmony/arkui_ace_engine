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

import { MyButton, Tool } from '../Index'
import { Colors } from '@kit.ArkUI'
import { GeneralPageOne } from '../GeneralPages'

@Entry
@Component
struct forcedNewInstance {
  stack: NavPathStack = new NavPathStack()

  aboutToAppear(): void {
    this.getUIContext().getUIObserver().on('routerPageUpdate', (info) => {
      console.log('[router] observerInfo: ' + JSON.stringify(info))
    })
  }

  @Builder
  pageMap(name: string) {
    if (name.substring(0, 7) == 'pageOne') {
      PageOne()
    } else if (name.substring(0, 7) == 'pageTwo') {
      PageTwo()
    } else if (name == 'dialog') {
      Dialog()
    }
  }

  build() {
    Navigation(this.stack) {
      MyButton({
        text: 'push general',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'test' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })
      MyButton({
        text: 'push pageOne',
        onClickFunction: () => {
          this.stack.pushDestination({ name: 'pageOne' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })
    }.navDestination(this.pageMap)
  }
}

@Component
export struct PageOne {
  stack: NavPathStack = new NavPathStack()
  @State stackSize: number = -1
  name: string = 'NA_PAGE_ONE'

  build() {
    NavDestination() {
      Column() {
        Text('Current Index: ' + Tool.count)
          .fontSize(35)
          .fontWeight(FontWeight.Bold)
      }
      MyButton({
        text: 'push dialog',
        onClickFunction: () => {
          this.stack.pushPath({ name: 'dialog' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })

      MyButton({
        text: 'replace dialog',
        onClickFunction: () => {
          this.stack.replacePath({ name: 'dialog' }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })

      MyButton({
        text: 'push PageOne++',
        onClickFunction: () => {
          this.stack.pushPath({ name: 'pageOne' + Tool.count++ }, { launchMode: LaunchMode.NEW_INSTANCE})
        }
      })

    }.title('Page One')
    .onReady((ctx) => {
      this.stack = ctx.pathStack
      this.name = ctx.pathInfo.name
    })
    .onWillShow(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + this.name + ' onShown')
    })
    .onWillHide(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillHide')
    })
    .onHidden(() => {
      console.log('[new_instance][life] ' + this.name + ' onHidden')
    })
    .onWillAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillAppear')
    })
    .onAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onAppear')
    })
    .onWillDisappear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillDisappear')
    })
    .onDisAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onDisAppear')
    })
  }
}

@Component
export struct PageTwo {
  stack: NavPathStack = new NavPathStack()
  @State stackSize: number = -1
  color: Color = (Tool.count) % 2 == 0 ? Color.Pink : Color.Gray
  name: string = 'NA_PAGE_TWO'

  build() {
    NavDestination() {
      Column() {
        Text('Current Name: ' + this.name)
          .fontSize(35)
          .fontWeight(FontWeight.Bold)
      }

      Column() {
        Column() {
          Text('No New Instance')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
            .position({top: 7, left: 7})
        }.margin(10)
        MyButton({
          text: 'push pageOne',
          onClickFunction: () => {
            this.stack.pushDestination({ name: 'pageOne' })
          }
        })
        MyButton({
          text: 'push pageTwoDialog',
          onClickFunction: () => {
            this.stack.pushDestination({ name: 'pageTwoDialog' + Tool.count++ })
          }
        })

      }.backgroundColor('#598')
      .width('100%')
      .margin(15)

      Column() {
        Column() {
          Text('New Instance')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
            .position({top: 7, left: 7})
        }.margin(10)

        MyButton({
          text: 'clear + new one',
          onClickFunction: () => {
            this.stack.clear()
            this.stack.pushDestination({ name: 'pageOne' }, { launchMode: LaunchMode.NEW_INSTANCE})
          }
        })

        MyButton({
          text: 'clear + new two x3',
          onClickFunction: () => {
            this.stack.clear()
            this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
            this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
            this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
          }
        })
      }.backgroundColor('#aff')
      .width('100%')

    }
    .mode(NavDestinationMode.DIALOG)
    .title('Page Two').backgroundColor(this.color)
    .onReady((ctx: NavDestinationContext) => {
      this.stack = ctx.pathStack
      this.name = ctx.pathInfo.name
    })
    .onWillShow(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + this.name + ' onShown')
    })
    .onWillHide(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillHide')
    })
    .onHidden(() => {
      console.log('[new_instance][life] ' + this.name + ' onHidden')
    })
    .onWillAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillAppear')
    })
    .onAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onAppear')
    })
    .onWillDisappear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillDisappear')
    })
    .onDisAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onDisAppear')
    })
  }
}

@Component
struct Dialog {
  stack: NavPathStack = new NavPathStack()
  name: string = 'NA'
  build() {
    NavDestination() {
      Button().margin(20)
        .onClick(() => {
          this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
        })
    }
    .onReady((ctx: NavDestinationContext) => {
      this.stack = ctx.pathStack
      this.name = ctx.pathInfo.name
    })
    .backgroundColor(Color.Grey)
    .opacity(0.5)
    .mode(NavDestinationMode.DIALOG)
    .onWillShow(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + this.name + ' onShown')
    })
    .onWillHide(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillHide')
    })
    .onHidden(() => {
      console.log('[new_instance][life] ' + this.name + ' onHidden')
    })
    .onWillAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillAppear')
    })
    .onAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onAppear')
    })
    .onWillDisappear(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillDisappear')
    })
    .onDisAppear(() => {
      console.log('[new_instance][life] ' + this.name + ' onDisAppear')
    })
  }
}