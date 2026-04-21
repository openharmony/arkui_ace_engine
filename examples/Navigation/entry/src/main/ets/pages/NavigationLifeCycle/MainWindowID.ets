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
import observer from '@ohos.arkui.observer';
import { hilog_log, printPathStack, SR_NO_MAP } from '../utils/Index';

@Entry
@Component
struct NavigationApiID {
  @State pageInfos: NavPathStack = new NavPathStack();
  @State pageInfos2: NavPathStack = new NavPathStack();

  navDesUpdateCallback(info: NavDestinationInfo) {
    console.log(printPathStack(info, SR_NO_MAP.NavigationLifeCycle))
  }

  observerOn(){
    observer.on('navDestinationUpdate', {navigationId:'nav1'}, this.navDesUpdateCallback);
  }

  observerOff(){
    observer.off('navDestinationUpdate',{navigationId:'nav1'}, this.navDesUpdateCallback);
  }

  onPageShow() {
    console.info('testTag pageAID onPageShow');
  }

  onPageHide() {
    console.info('testTag pageAID onPageHide');
  }

  onBackPress() {
    console.info('testTag pageAID onBackPress');
    return false
  }

  aboutToAppear() {
    console.info('testTag pageAID aboutToAppear');
  }

  aboutToDisappear() {
    observer.off('navDestinationUpdate',{navigationId:'nav1'}, this.navDesUpdateCallback);
    console.info('testTag pageAID aboutToDisappear');
  }

  @Builder
  pageOneTmp() {
    NavDestination() {
      Column({ space: 10 }) {
      }
    }.title('pageOne').backgroundColor(Color.Pink)
    .onBackPressed(() => {
      hilog_log(SR_NO_MAP.NavigationLifeCycle, `testTag pageOne onBackPress`)
      return false
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
      console.log(`testTag pageTwo onBackPress`)
      return false
    })
    .onWillAppear(()=>{
      console.log("testTag pageTwo onWillAppear")
    })
    .onAppear(()=>{
      console.log("testTag pageTwo onAppear")
    })
    .onWillShow(()=>{
      console.log("testTag pageTwo onWillShow")
    })
    .onShown(()=>{
      console.log("testTag pageTwo onShown")
    })
    .onWillHide(()=>{
      console.log("testTag pageTwo onWillHide")
    })
    .onHidden(()=>{
      console.log("testTag pageTwo onHidden")
    })
    .onWillDisappear(()=>{
      console.log("testTag pageTwo onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("testTag pageTwo onDisAppear")
    })
  }


  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      this.pageOneTmp()
    } else if (name === 'pageTwo') {
      this.pageTwoTmp()
    }
  }

  @Builder
  PageMap2(name: string) {
    if (name === 'pageOne') {
      this.pageOneTmp()
    } else if (name === 'pageTwo') {
      this.pageTwoTmp()
    }
  }


  build() {
    Column({space:5}){
      Text('指定id监听').fontSize(18).fontWeight(FontWeight.Bold)

      Row({space:5}){
        Button('observerOn')
          .onClick(() => {
            this.observerOn()
          })

        Button('observerOff')
          .onClick(() => {
            this.observerOff()
          })
      }

      Navigation(this.pageInfos) {
        Column({space:10}) {
          Button('push pageOne')
            .key('firstPushPageOne')
            .onClick(() => {
              this.pageInfos.pushPath({ name: 'pageOne' })
            }).margin(5)
        }
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation1')
      .id('nav1')
      .navDestination(this.PageMap)

      Navigation(this.pageInfos2) {
        Column({space:10}) {
          Button('push pageOne')
            .key('secondPushPageOne')
            .onClick(() => {
              this.pageInfos2.pushPath({ name: 'pageOne' })
            }).margin(5)
        }
      }
      .borderWidth(1)
      .height('30%')
      .title('Navigation2')
      .navDestination(this.PageMap2)
    }

  }
}
