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
  @State mode2:NavigationMode =NavigationMode.Auto

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
  @Builder

  build() {
    Column(){
      Navigation(this.pageInfos) {
        Column() {
        }
      }.title('主页面').navDestination(this.PageMap).mode(this.mode).height('30%')
      Row(){
        Button('单栏').onClick(() => {
          this.mode = NavigationMode.Stack
        })
        Button('双栏').onClick(() => {
          this.mode = NavigationMode.Split
        })
      }
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
          Button(`push B`, { stateEffect: true, type: ButtonType.Capsule })
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

          Button(`跳转到B，调用didshow，跳出弹窗，pushPath到C`, { stateEffect: true, type: ButtonType.Capsule })
            .key("didshow")
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                 console.log(`===NavigationReInterception===  will show`)
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("===NavigationReInterception=== target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    AlertDialog.show(
                      {
                        title: '弹窗',
                        message: 'text',
                        autoCancel: true,
                        alignment: DialogAlignment.Bottom,
                        offset: { dx: 0, dy: -20 },
                        gridCount: 3,
                        confirm: {
                          value: '确认',
                          action: () => {
                            target.pathStack.pushPath({ name:'C' })
                            console.info('Button-clicking callback')
                          }
                        }
                      }
                    )

                  }
                  console.log(`did show`)
                }
              });

              this.pageInfos.pushPath({name:'B'})
            })

          Button(`跳转到B，调用willShow，跳出弹窗，pushPath到C`, { stateEffect: true, type: ButtonType.Capsule })
            .key("willShow")
            .width('80%')
            .height(40)
            .margin(10)
            .onClick(() => {
              this.pageInfos.setInterception({
                willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  if (typeof to === "string") {
                    console.log("===NavigationReInterception=== target page is navigation home");
                    return;
                  }
                  let target: NavDestinationContext = to as NavDestinationContext;
                  if (target.pathInfo.name === 'B') {
                    target.pathStack.pop();
                    AlertDialog.show(
                      {
                        title: '弹窗',
                        message: 'text',
                        autoCancel: true,
                        alignment: DialogAlignment.Bottom,
                        offset: { dx: 0, dy: -20 },
                        gridCount: 3,
                        confirm: {
                          value: '确认',
                          action: () => {
                            target.pathStack.pushPath({ name:'C' })
                            console.info('===NavigationReInterception=== Button-clicking callback')
                          }
                        },
                      }
                    )

                  }
                  console.log(`will show`)
                },
                didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
                  console.log(`did show`)
                }
              });
              this.pageInfos.pushPath({name:'B'})
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
    .onAppear(() => {
      console.log(`===NavigationReInterception=== testTag pageOne onAppear`)
    })
    .onDisAppear(() => {
      console.log(`===NavigationReInterception=== testTag pageOne onDisAppear`)
    })
    .onShown(() => {
      console.log(`===NavigationReInterception=== testTag pageOne onShown`)
    })
    .onHidden(() => {
      console.log(`===NavigationReInterception=== testTag pageOne onHidden`)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}