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
import { CustomTransition } from '../utils/CustomNavigationUtils'
import { hilog_log, SR_NO_MAP } from '../utils/Index';

let durationOne: number = 1000
let durationTwo: number = 1000

@Entry
@Component
struct NavigationExample2 {
  @State timeout: number = 1000
  @State routerTo: string = ''
  @State routerFrom: string = ''
  @State proxyTo: string = ''
  @State proxyFrom: string = ''
  @State mode: NavigationMode = NavigationMode.Stack
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      pageOne()
    } else if (name === 'pageTwo') {
      pageTwo()
    }
  }

  build() {
    Column({space:5}) {
      Column({space:5}){
        Button('push pageOne')
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' })
          }).margin(5)

        Button('push pageTwo')
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageTwo' })
          }).margin(5)

        Button('pop')
          .onClick(() => {
            this.pageInfos.pop()
          }).margin(5)

        Button('clear')
          .onClick(() => {
            this.pageInfos.clear()
          }).margin(5)
      }


      Navigation(this.pageInfos) {
        Column({space:10}) {
        }
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation121212')
      .navDestination(this.PageMap)
      .customNavContentTransition((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => {
        if (from.mode === NavDestinationMode.DIALOG || to.mode === NavDestinationMode.DIALOG) {
          console.log("Dialog navDestination do system transition animation.")
          return undefined
        }
        this.routerTo = JSON.stringify(to) + ''
        this.routerFrom = JSON.stringify(from) + ''
        // 其他页面做自定义动画
        let customAnimation: NavigationAnimatedTransition
        customAnimation = {
          onTransitionEnd: (success) => {
            if (success) {
              console.log("custom transition success");
            } else {
              console.log("custom transition failed");
            }
          },
          // timeout: this.timeout,
          transition: (transitionContext) => {
            this.proxyTo = JSON.stringify(transitionContext.to) + ''
            this.proxyFrom = JSON.stringify(transitionContext.from) + ''
            let onFinish: () => void = () => {
              transitionContext.finishTransition()
            }
            // from页面的自定义动画
            let fromAnimatedFunc: (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void
            fromAnimatedFunc = CustomTransition.getInstance().getNavParam(transitionContext.from.name)
            if (fromAnimatedFunc != undefined) {
              fromAnimatedFunc(operation === NavigationOperation.PUSH, onFinish,false,false)
            }

            // to页面的自定义动画
            let toAnimatedFunc: (isPush: boolean, onFinish: () => void,isexit: boolean, isPop: boolean) => void
            toAnimatedFunc = CustomTransition.getInstance().getNavParam(transitionContext.to.name)
            if (toAnimatedFunc != undefined) {
              toAnimatedFunc(operation === NavigationOperation.PUSH, onFinish,true,false)
            }
          }
        }
        return customAnimation
      })
    }

  }
}


@Component
export struct pageOne {
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State opacity1: number = 1
  @State duration: number = durationOne

  aboutToAppear() {
    CustomTransition.getInstance().registerNavParam('pageOne', (isPush: boolean, onFinish: () => void,isexit:boolean) => {
      if (isexit) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPush) {
        // push 转场
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else {
        // pop 转场
        this.opacity1 = 1
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 0
        })
      }
    })
  }

  aboutToDisappear() {
    CustomTransition.getInstance().unRegisterNavParam('pageOne')
  }

  build() {
    NavDestination() {
      Column() {
      }.width('100%').height('100%')
    }.title('pageOne').opacity(this.opacity1)
    .onBackPressed(() => {
      hilog_log(SR_NO_MAP.NavigationLifeCycle, `testTag pageOne onBackPress`)
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onWillAppear")
    })
    .onAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onAppear")
    })
    .onWillShow(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onWillShow")
    })
    .onShown(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onShown")
    })
    .onWillHide(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onWillHide")
    })
    .onHidden(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onHidden")
    })
    .onWillDisappear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onWillDisappear")
    })
    .onDisAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageOne onDisAppear")
    })
  }
}


@Component
export struct pageTwo {
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State translateX: number = 0
  @State opacity1: number = 1
  @State duration: number = durationTwo

  aboutToAppear() {
    CustomTransition.getInstance().registerNavParam('pageTwo', (isPush: boolean, onFinish: () => void,isexit:boolean) => {
      if (isexit) {
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else if (isPush) {
        // push 转场
        this.opacity1 = 0
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 1
        })
      } else {
        // pop 转场
        this.opacity1 = 1
        animateTo({ duration: durationOne, onFinish: onFinish }, () => {
          this.opacity1 = 0
        })
      }
    })
  }

  aboutToDisappear() {
    CustomTransition.getInstance().unRegisterNavParam('pageTwo')
  }

  build() {
    Scroll() {
      NavDestination() {
        Column() {
        }.width('100%').height('100%')
      }.title('pageTwo').opacity(this.opacity1)
      .onBackPressed(() => {
        hilog_log(SR_NO_MAP.NavigationLifeCycle, `testTag pageTwo onBackPress`)
        this.pageInfos.pop()
        return true
      })
      .onWillAppear(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onWillAppear")
      })
      .onAppear(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onAppear")
      })
      .onWillShow(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onWillShow")
      })
      .onShown(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onShown")
      })
      .onWillHide(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onWillHide")
      })
      .onHidden(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onHidden")
      })
      .onWillDisappear(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onWillDisappear")
      })
      .onDisAppear(()=>{
        hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageTwo onDisAppear")
      })
    }

  }
}