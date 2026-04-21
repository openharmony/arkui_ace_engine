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
// Index.ets
import { PageOneTmp } from './PageOne'
import { pageTwoTmp } from './PageTwo'
import {PageThreeTmp} from './PageThree'

@Entry
@Component
struct NavigationExample {
  pageInfos: NavPathStack = new NavPathStack()
  @State disableAnimation: boolean = false;
  @StorageLink('mode') mode: NavigationMode = NavigationMode.Auto

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp()
    } else if (name === "pageThree") {
      PageThreeTmp()
    }
  }

  aboutToAppear(): void {
    this.registerInterception();
  }

  registerInterception() {
    this.pageInfos.setInterception({
      willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar",
                 operation: NavigationOperation, animated: boolean) => {
        let fromName: string = "";
        if (typeof from === "string") {
          fromName = from.toString();
        } else {
          fromName = from?.pathInfo?.name;
        }
        let toName: string = "";
        if (typeof to === "string") {
          toName = to.toString();
        } else {
          toName = to?.pathInfo?.name;
        }
        console.log(`===NavigationReInterception=== will show from page name: ${fromName}, toName is ${toName}, operation: ${operation}, animated: ${animated}`)
      },
      didShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar",
                operation: NavigationOperation, isAnimated: boolean) => {
        let fromName: string = "";
        if (typeof from === "string") {
          fromName = from.toString();
        } else {
          fromName = from?.pathInfo?.name;
        }
        let toName: string = "";
        if (typeof to === "string") {
          toName = to.toString();
        } else {
          toName = to?.pathInfo?.name;
        }
        console.log(`===NavigationReInterception=== did show from page name: ${fromName}, toName is ${toName}, operation: ${operation}, animated: ${isAnimated}`)
      },
      modeChange: (mode: NavigationMode) => {
        console.log(`===NavigationReInterception=== current navigation mode is ${mode}`);
      }
    })
  }

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pushPageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' }) //将name指定的NavDestination页面信息入栈
          })
        Button(`page Five`, { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPathByName('pageFive', null);
          })

        Button(`suspend pageOne`, { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.setInterception({
              willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext| "navBar", operation: NavigationOperation, animated: boolean)=>{
                console.log(" ==== trigger will show =====");
                while (true) {
                  console.log("==== suspend =====");
                }
              }
            });
            this.pageInfos.pushPath({name: 'pageOne'})
          })

        Button(`use animation:${this.disableAnimation}`, { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.disableAnimation = !this.disableAnimation;
            this.pageInfos.disableAnimation(this.disableAnimation)
          })
      }
    }.title('NavIndex').navDestination(this.PageMap).mode(this.mode)
  }
}