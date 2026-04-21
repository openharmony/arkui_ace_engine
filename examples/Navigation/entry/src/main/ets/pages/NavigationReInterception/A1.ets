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
          Text('返回信息:' + this.text1)
        }
      }.title('A页面').navDestination(this.PageMap).mode(this.mode).height(350)
      Scroll(){
        Column(){
          Button(`从A push 到B`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
            })
          Button(`getAllPathName`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
            })
          Button(`从A跳转到B，调用didshow，push到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPath({ name: 'C' })
                  }
                }
              });
            })


          Button(`从A跳转到B，调用didshow，pushPathByName到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPathByName('C',null)
                  }
                }
              });
            })

          Button(`从A跳转到B，调用didshow，pushPathByName到C(携带onPop)`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushPathByName('C',a,(popInfo:PopInfo) => {
                      console.info(popInfo.info.name)
                    })
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，pushDestination到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushDestination({name: 'C' })
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，pushDestinationByName到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushDestinationByName('C',null)
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，pushDestinationByName到C(携带onPop)`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {

                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    target.pathStack.pushDestinationByName('C',a,(popInfo:PopInfo) => {
                      console.info(popInfo.info.name)
                    })
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，replacePath到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {

                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.replacePath({name:'C'})
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，replacePathByName到C`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.replacePathByName('C',null)
                  }
                }
              });
            })
          Button(`从A跳转到B，调用didshow，使用removeByIndexes删除B`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.removeByIndexes([0])
                }
              });
            })
          Button(`从A跳转到B，调用didshow，使用removeByName删除B`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.removeByName('B')
                }
              });
            })
          Button(`从A跳转到B，调用didshow，pop掉B页面`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.pop()
                }
              });
            })

          Button(`pushPathByName到B(携带onPop)，调用willshow，popB`, { stateEffect: true, type: ButtonType.Capsule })
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPathByName('B',a,(popInfo:PopInfo) => {
                this.text1 = JSON.stringify(popInfo)
                console.info(popInfo.info.name)
              })
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  let result = a
                  this.pageInfos.pop(result);
                }
              });
            })

          Button('A页面push到B页面，调用willshow，clear所有页面，使用getAllPathName')
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.pushPath({name:'B'})
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  this.pageInfos.clear()
                  this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
                }
              });
            })
          Text('获取栈中所有NavDestination页面的名称:' + this.text2)
          Button('getAllPathName').onClick(() =>{
            this.text2 = JSON.stringify(this.pageInfos.getAllPathName())
          })
        }
      }.height(450)
    }
  }
}