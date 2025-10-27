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

@Entry
@Component
struct InterceptionTest {
  stack: NavPathStack = new NavPathStack()

  func() {
    console.log('test')
  }

  aboutToAppear(): void {
    this.stack.setInterception({
      willShow: (from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar',
        operation: NavigationOperation, animated: boolean) => {
        console.log('[new_instance][interception] in willShow, cur op: ' + JSON.stringify(operation))
      },
      didShow: (from: NavDestinationContext | 'navBar', to: NavDestinationContext | 'navBar',
        operation: NavigationOperation, animated: boolean) => {
        console.log('[new_instance][interception] in didShow, cur op: ' + JSON.stringify(operation))
      }
    })
    this.getUIContext().getUIObserver().on('routerPageUpdate', (info) => {
      console.log('[router] observerInfo: ' + JSON.stringify(info))
    })
  }

  @Builder
  pageMap(name: string) {
    if (name.substring(0, 7) == 'pageTwo') {
      PageTwo()
    }
  }

  build() {
    Navigation(this.stack) {

    }.navDestination(this.pageMap)
    .hideNavBar(true)
    .onAppear(() => {
      this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ }, { launchMode: LaunchMode.NEW_INSTANCE })
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
          text: 'push pageTwo',
          onClickFunction: () => {
            this.stack.pushDestination({ name: 'pageTwo' })
          }
        })
        MyButton({
          text: 'pop x3 + push two++ x3',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pop()
            this.stack.pop()
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
          }
        })
        MyButton({
          text: 'push pageTwo++',
          onClickFunction: () => {
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ })
          }
        })
        MyButton({
          text: 'clear and pushTwo',
          onClickFunction: () => {
            this.stack.clear()
            this.stack.pushDestination({ name: 'pageTwo' })
          }
        })
        MyButton({
          text: 'pop x2 + two',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pop()
            this.stack.pushPath({ name: 'pageTwo' })
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
          text: 'new_instance pageTwo++',
          onClickFunction: () => {
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count }, { launchMode: LaunchMode.NEW_INSTANCE})
          }
        })

        MyButton({
          text: 'pop + new_instance pageTwo',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pushDestination({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE})
          }
        })

        MyButton({
          text: 'pop + new_instance pageTwo++',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pushDestination({ name: 'pageTwo' + Tool.count++ }, { launchMode: LaunchMode.NEW_INSTANCE})
          }
        })

        MyButton({
          text: 'pop x2 + new Two x2',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pop()
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
          }
        })

        MyButton({
          text: 'pop x3 + new Two x3',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pop()
            this.stack.pop()
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE })
          }
        })

        MyButton({
          text: 'pop x3 + new Two x3 (no ani)',
          onClickFunction: () => {
            this.stack.pop()
            this.stack.pop()
            this.stack.pop()
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE, animated: false })
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE, animated: false })
            this.stack.pushPath({ name: 'pageTwo' }, { launchMode: LaunchMode.NEW_INSTANCE, animated: false })
          }
        })
      }.backgroundColor('#aff')
      .width('100%')

    }.title('Page Two').backgroundColor(this.color)
    .onReady((ctx: NavDestinationContext) => {
      this.stack = ctx.pathStack
      this.name = ctx.pathInfo.name
    })
    .onWillShow(() => {
      console.log('[new_instance][life] ' + this.name + ' onWillShow')
    })
    .onShown(() => {
      console.log('[new_instance][life] ' + this.name + ' onShown')
      this.stackSize = this.stack.size()
      console.log('[new_instance] ======== print index ========')
      this.stack.getAllPathName()
      console.log('[new_instance] ======== print index ========')
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