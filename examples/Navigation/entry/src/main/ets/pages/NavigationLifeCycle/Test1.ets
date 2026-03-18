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
import { hilog_log, SR_NO_MAP } from '../utils/Index';

@Entry
@Component
struct NavigationApiTest {
  @State pageInfos: NavPathStack = new NavPathStack();

  onPageShow() {
    console.info('testTag pageA onPageShow');
  }

  onPageHide() {
    console.info('testTag pageA onPageHide');
  }

  onBackPress() {
    console.info('testTag pageA onBackPress');
    return false
  }

  aboutToAppear() {
    console.info('testTag pageA aboutToAppear');
  }

  aboutToDisappear() {
    console.info('testTag pageA aboutToDisappear');
  }

  @Builder
  pageOneTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('A').backgroundColor(Color.Pink)
    .onBackPressed(() => {
      return false
    })
    .onWillAppear(()=>{
      console.log("testTag A onWillAppear")
    })
    .onAppear(()=>{
      console.log("testTag A onAppear")
    })
    .onWillShow(()=>{
      console.log("testTag A onWillShow")
    })
    .onShown(()=>{
      console.log("testTag A onShown")
    })
    .onWillHide(()=>{
      console.log("testTag A onWillHide")
    })
    .onHidden(()=>{
      console.log("testTag A onHidden")
    })
    .onWillDisappear(()=>{
      console.log("testTag A onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("testTag A onDisAppear")
    })
  }

  @Builder
  pageTwoTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('B').backgroundColor(Color.Yellow)
    .onBackPressed(() => {
      return false
    })
    .onWillAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onWillAppear")
    })
    .onAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onAppear")
    })
    .onWillShow(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onWillShow")
    })
    .onShown(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onShown")
    })
    .onWillHide(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onWillHide")
    })
    .onHidden(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onHidden")
    })
    .onWillDisappear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onWillDisappear")
    })
    .onDisAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag B onDisAppear")
    })
  }


  @Builder
  pageThreeTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('C')
    .onBackPressed(() => {
      return false
    })
    .onWillAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onWillAppear")
    })
    .onAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onAppear")
    })
    .onWillShow(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onWillShow")
    })
    .onShown(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onShown")
    })
    .onWillHide(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onWillHide")
    })
    .onHidden(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onHidden")
    })
    .onWillDisappear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onWillDisappear")
    })
    .onDisAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag C onDisAppear")
    })
  }


  @Builder
  PageMap(name: string) {
    if (name === 'A') {
      this.pageOneTmp()
    } else if (name === 'B') {
      this.pageTwoTmp()
    } else if (name === 'C') {
      this.pageThreeTmp()
    }
  }



  build() {
    Column({space:5}){
      Button('push A')
        .onClick(() => {
          this.pageInfos.pushPath({ name: 'A' })
        })

      Button('push B')
        .onClick(() => {
          this.pageInfos.pushPath({ name: 'B' })
        })

      Button('push C')
        .onClick(() => {
          this.pageInfos.pushPath({ name: 'C' })
        })

      Button('pop')
        .onClick(() => {
          this.pageInfos.pop()
        })

      Button('clear')
        .onClick(() => {
          this.pageInfos.clear()
        })

      Button(`跳转到B，调用didshow，跳出弹窗，pushPath到C`, { stateEffect: true, type: ButtonType.Capsule })
        .key('didShowToB')
        .width('80%')
        .height(40)
        .onClick(() => {
          this.pageInfos.setInterception({
            willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
              console.log(`will show`)
            },
            didShow:(from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
              if (typeof to === "string") {
                console.log("target page is navigation home");
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
        .key('willShowToB')
        .width('80%')
        .height(40)
        .onClick(() => {
          this.pageInfos.setInterception({
            willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar", operation: NavigationOperation, animated: boolean) => {
              if (typeof to === "string") {
                console.log("target page is navigation home");
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

      Navigation(this.pageInfos) {
        Column({space:10}) {
        }
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation')
      .navDestination(this.PageMap)

    }

  }
}
