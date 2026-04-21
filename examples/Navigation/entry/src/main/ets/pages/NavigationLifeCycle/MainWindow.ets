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
import router from '@ohos.router';
import observer from '@ohos.arkui.observer';
import window from '@ohos.window';
import base from '@ohos.base';
import { hilog_log, SR_NO_MAP, printPathStack } from '../utils/Index';

@Entry
@Component
struct NavigationApi {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack();
  private myWindow: window.Window | null = null;

  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(printPathStack(info, SR_NO_MAP.NavigationLifeCycle))
  }

  observerOn(){
    observer.on('navDestinationUpdate', this.navDesUpdateCallback);
  }

  observerOff(){
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
  }

  onPageShow() {
    console.info('testTag MainWindow-pageA onPageShow');
  }

  onPageHide() {
    console.info('testTag MainWindow-pageA onPageHide');
  }

  onBackPress() {
    console.info('testTag MainWindow-pageA onBackPress');
    return false
  }

  aboutToAppear() {
    console.info('testTag MainWindow-pageA aboutToAppear');
  }

  aboutToDisappear() {
    observer.off('navDestinationUpdate', this.navDesUpdateCallback);
    console.info('testTag MainWindow-pageA aboutToDisappear');
  }

  @Builder
  pageOneTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageOne').backgroundColor(Color.Pink)
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

  @Builder
  pageTwoTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageTwo').backgroundColor(Color.Orange)
    .onBackPressed(() => {
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

  @Builder
  pageThreeTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageThree')
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onWillAppear")
    })
    .onAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onAppear")
    })
    .onWillShow(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onWillShow")
    })
    .onShown(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onShown")
    })
    .onWillHide(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onWillHide")
    })
    .onHidden(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onHidden")
    })
    .onWillDisappear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onWillDisappear")
    })
    .onDisAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageThree onDisAppear")
    })
  }

  @Builder
  pageFourTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageFour')
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      this.pageInfos.pop()
      return true
    })
    .onWillAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onWillAppear")
    })
    .onAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onAppear")
    })
    .onWillShow(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onWillShow")
    })
    .onShown(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onShown")
    })
    .onWillHide(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onWillHide")
    })
    .onHidden(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onHidden")
    })
    .onWillDisappear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onWillDisappear")
    })
    .onDisAppear(()=>{
      hilog_log(SR_NO_MAP.NavigationLifeCycle, "testTag pageFour onDisAppear")
    })
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      this.pageOneTmp()
    } else if (name === 'pageTwo') {
      this.pageTwoTmp()
    } else if (name === 'pageThree') {
      this.pageThreeTmp()
    } else if (name === 'pageFour') {
      this.pageFourTmp()
    }
  }


  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/NavigationLifeCycle/SubWindow', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }


  @State getAllPathName:string = ''
  @State disableAnimation: boolean = false
  @Styles buttonStyles() {
    .height(30)
    .margin(3)
  }

  build() {
    Column({space:5}){
      Text('pageA页面').fontSize(18).fontWeight(FontWeight.Bold)

      Button('全局是否禁用转场动画，disableAnimation: ' + this.disableAnimation)
        .key('disableAnimation')
        .onClick(()=>{
          this.disableAnimation = !this.disableAnimation
          this.pageInfos.disableAnimation(this.disableAnimation)
        })

      Row({space:5}){
        Button('observerOn')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.observerOn()
          })

        Button('observerOff')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.observerOff()
          })
      }
      Row() {
        Button('开启子窗口')
          .fontSize(12)
          .buttonStyles()
          .onClick(() => {
            this.createWindow();
          })

        Button('跳转到pageB页面')
          .fontSize(12)
          .buttonStyles()
          .onClick(()=>{
            router.pushUrl({url:'pages/NavigationLifeCycle/PageB'})
          })
      }

      Flex({ wrap: FlexWrap.Wrap, justifyContent:FlexAlign.Center }) {

          Button('push pageOne')
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageOne' })
            })
            .fontSize(12)
            .buttonStyles()

          Button('push pageTwo')
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageTwo' })
            })
            .fontSize(12)
            .buttonStyles()

          Button('pop')
            .onClick(() => {
              this.pageInfos.pop()
            })
            .fontSize(12)
            .buttonStyles()

          Button('push pageThree')
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageThree' })
            })
            .fontSize(12)
            .buttonStyles()

          Button('push pageFour')
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageFour' })
            })
            .fontSize(12)
            .buttonStyles()

          Button('pop*3')
            .onClick(() => {
              this.pageInfos.pop()
              this.pageInfos.pop()
              this.pageInfos.pop()
            })
            .fontSize(12)
            .buttonStyles()

          Button('replacePath pageTwo')
            .onClick(() => {
              this.pageInfos.replacePath({name: 'pageTwo',  param: null})
            })
            .fontSize(12)
            .buttonStyles()

          Button('replacePath pageThree')
            .onClick(() => {
              this.pageInfos.replacePath({name: 'pageThree',  param: null})
            })
            .fontSize(12)
            .buttonStyles()

          Button('clear')
            .onClick(() => {
              this.pageInfos.clear()
            })
            .fontSize(12)
            .buttonStyles()

          Button('replacePath pageFour')
            .onClick(() => {
              this.pageInfos.replacePath({name: 'pageFour',  param: null})
            })
            .fontSize(12)
            .buttonStyles()

          Button('removeByIndexes [0]')
            .onClick(() => {
              this.pageInfos.removeByIndexes([0])
            })
            .fontSize(12)
            .buttonStyles()

          Button('removeByIndexes [1]')
            .onClick(() => {
              this.pageInfos.removeByIndexes([1])
            })
            .fontSize(12)
            .buttonStyles()

          Button('removeByIndexes [2]')
            .onClick(() => {
              this.pageInfos.removeByIndexes([2])
            })
            .fontSize(12)
            .buttonStyles()

          Button('removeByIndexes [2,4]')
            .onClick(() => {
              this.pageInfos.removeByIndexes([2,4])
            })
            .fontSize(12)
            .buttonStyles()

          Button('moveIndexToTop 0')
            .onClick(() => {
              this.pageInfos.moveIndexToTop(0)
            })
            .fontSize(12)
            .buttonStyles()

          Button('moveIndexToTop 1')
            .onClick(() => {
              this.pageInfos.moveIndexToTop(1)
            })
            .fontSize(12)
            .buttonStyles()

          Button('moveIndexToTop 2')
            .onClick(() => {
              this.pageInfos.moveIndexToTop(2)
            })
            .fontSize(12)
            .buttonStyles()

          Button('popToIndex 0')
            .onClick(() => {
              this.pageInfos.popToIndex(0)
            })
            .fontSize(12)
            .buttonStyles()

          Button('popToName pageThree')
            .onClick(() => {
              this.pageInfos.popToName('pageThree')
            })
            .fontSize(12)
            .buttonStyles()

        Button('popToName pageOne')
          .onClick(() => {
            this.pageInfos.popToName('pageOne')
          })
          .fontSize(12)
          .buttonStyles()

          Button("push*3,pop*2")
            .fontSize(12)
            .buttonStyles()
            .onClick(()=>{
              this.pageInfos.pushPathByName('pageOne', null)
              this.pageInfos.pushPathByName('pageTwo', null)
              this.pageInfos.pushPathByName('pageThree', null)
              this.pageInfos.pop()
              this.pageInfos.pop()
            })

          Button("move*3,pop*2")
            .fontSize(12)
            .buttonStyles()
            .onClick(()=>{
              this.pageInfos.moveToTop('pageOne')
              this.pageInfos.moveToTop('pageTwo')
              this.pageInfos.moveToTop('pageThree')
              this.pageInfos.pop()
              this.pageInfos.pop()
            })

          Button('push 不存在的navDestination')
            .onClick(() => {
              this.pageInfos.pushPathByName('pageFive', null)
            })
            .fontSize(12)
            .buttonStyles()

        }.width('100%').height('48%')

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
