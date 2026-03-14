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
import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
import { hilog_log, SR_NO_MAP } from '../utils/Index';

@Entry
@Component
struct NavigationApiSub {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack();
  private curWindow: window.Window | null = null;

  onPageShow() {
    console.info('testTag SubWindow-PageA onPageShow');
  }

  onPageHide() {
    console.info('testTag SubWindow-PageA onPageHide');
  }

  onBackPress() {
    console.info('testTag SubWindow-PageA onBackPress');
    return false
  }

  aboutToAppear() {
    console.info('testTag SubWindow-PageA aboutToAppear');
  }

  aboutToDisappear() {
    console.info('testTag SubWindow-PageA aboutToDisappear');
  }

  @Styles buttonStyles() {
    .height(30)
    .margin(3)
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

  @Builder
  pageThreeTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageThree')
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      hilog_log(SR_NO_MAP.NavigationLifeCycle, `testTag pageThree onBackPress`)
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
      hilog_log(SR_NO_MAP.NavigationLifeCycle, `testTag pageFour onBackPress`)
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


  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindow');
      if (!this.curWindow) {
        console.log(`testTag failed to findWindow`);
        return;
      }

      this.curWindow.destroyWindow().then(() => {
        console.log(`testTag success to destroy curWindow`);
      }).catch((err: BusinessError) => {
        console.log(`failed to destroy curWindow`)
      })
    } catch (e) {
      console.log(`testTag catch exception when find Window: ${JSON.stringify(e)}`)
    }
  }


  @State getAllPathName:string = ''


  build() {
    Column({space:5}){
      Flex({ wrap: FlexWrap.Wrap, justifyContent:FlexAlign.Center }) {
        Button('关闭子窗口')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.closeWindow();
          })
        Button('push pageOne')
          .key('subWindowPageOne')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' })
          })

        Button('push pageTwo')
          .key('subWindowPageTwo')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageTwo' })
          })

        Button('push pageThree')
          .key('subWindowPageThree')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageThree' })
          })

        Button('push pageFour')
          .key('subWindowPageFour')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageFour' })
          })

        Button('pop')
          .key('subWindowPop')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pop()
          })

        Button('replacePath pageTwo')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.replacePath({name: 'pageTwo',  param: null})
          })

        Button('replacePath pageThree')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.replacePath({name: 'pageThree',  param: null})
          })

        Button('replacePath pageFour')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.replacePath({name: 'pageFour',  param: null})
          })

        Button('removeByIndexes [2]')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.removeByIndexes([2])
          })

        Button('clear')
          .key('subWindowClear')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.clear()
          })

        Button('removeByIndexes [1]')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.removeByIndexes([1])
          })

        Button('pop*3')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.pop()
            this.pageInfos.pop()
            this.pageInfos.pop()
          })

        Button('moveIndexToTop 0')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.moveIndexToTop(0)
          })

        Button('moveIndexToTop 1')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.moveIndexToTop(1)
          })

        Button('moveIndexToTop 2')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.moveIndexToTop(2)
          })

        Button('popToIndex 0')
          .buttonStyles()
          .fontSize(12)
          .onClick(() => {
            this.pageInfos.popToIndex(0)
          })
        }
        .width('100%').height('50%').borderWidth(1).borderColor('#ffe20ea6')

      Navigation(this.pageInfos) {
        Column({space:10}) {
        }
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation')
      .navDestination(this.PageMap)
    }.backgroundColor(Color.Pink)
  }
}
