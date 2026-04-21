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
import { BTmp } from './B'
import { CTmp } from './C'

class a{
  num = 1
}
@Entry
@Component
struct NavigationExample {
  pageInfos: NavPathStack = new NavPathStack()
  @State disableAnimation: boolean = false;
  @StorageLink('mode') mode: NavigationMode = NavigationMode.Stack
  @State text1:string = ''
  @State text2:string = ''

  @Builder
  PageMap(name: string) {
    if (name === 'A') {
      ATmp()
    }
    if (name === 'B') {
      BTmp()
    }
    else if (name === 'C') {
      CTmp()
    }
  }

  build() {
    Column(){
      Navigation(this.pageInfos) {
        Column() {
        }
      }.title('主页面').navDestination(this.PageMap).mode(this.mode).height(350)
      Scroll(){
        Column(){
          Text('返回信息:' + this.text1)
          Text('获取栈中所有NavDestination页面的名称:' + this.text2)
          Button(`push A`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'A'})
            })
          Button(`getAllPathName`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
            })
          Button(`pushPath/pop`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPath({ name: 'C' })
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'C') {
                    target.pathStack.pop();
                  }
                }
              });
            })
          Button(`popToName/pushDestination`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.popToName('A')
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'A') {
                    target.pathStack.pop();
                    target.pathStack.pushDestination({ name: 'C' })
                  }
                }
              });
            })
          Button(`pushPathByName/pushDestinationByName`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pushPathByName('C',null)
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'C') {
                    target.pathStack.pop();
                    target.pathStack.pushDestinationByName('A',null)
                  }
                }
              });
            })
          Button(`popToName/pop`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.popToName('A')
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'A') {
                    target.pathStack.pop();
                  }
                }
              });
            })

          Button(`willshow使用pop到A页面，didshow使用pop跳到Inavbar页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'A') {
                    target.pathStack.pop();
                  }
                }
              });
            })

          Button(`willshow使用pushPaht跳到C页面，didshow使用moveToTopB页面移动到栈顶`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPath({name:'C'});
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'C') {
                    target.pathStack.moveToTop('A');
                  }
                }
              });
            })

          Button(`willshow使用pushPaht跳到C页面，didshow使用clear清空页面栈`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPath({name:'C'});
                  }
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'C') {
                    target.pathStack.clear();
                  }
                }
              });
            })

        }
      }.height(450)
    }
  }
}

// PageOne.ets
class TmpClass{
  count:number=10
}

@Component
export struct ATmp {
  pageInfos: NavPathStack = new NavPathStack();
  @State isChange: boolean = false;
  @State text2: string = '';

  build() {
    NavDestination() {
      Scroll(){
        Column() {

        }.width('100%').height('100%')
      }
    }.title('A页面')
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}