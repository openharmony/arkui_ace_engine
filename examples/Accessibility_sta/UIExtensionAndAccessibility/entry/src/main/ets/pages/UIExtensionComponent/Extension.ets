'use static';

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

import UIExtensionContentSession from '@ohos.app.ability.UIExtensionContentSession';
import { Entry, Component, NavPathStack, Navigation, Builder, Row, Column, Text, FontWeight, Button, NavigationMode, NavDestination, NavDestinationContext, ClickEvent, NavPathInfo, $r } from '@ohos.arkui.component';
import { AppStorage, LocalStorage, StorageLink } from '@ohos.arkui.stateManagement';
import { RecordData } from '@ohos.base';

AppStorage.setOrCreate('message', 'UIExtensionAbility')

@Entry()
@Component
struct Extension {
  @StorageLink('message') storageLink: string = '';
  private storage: LocalStorage | undefined = this.getUIContext().getSharedLocalStorage();
  private session: UIExtensionContentSession | undefined = this.storage?.get<UIExtensionContentSession>('session');
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string, param: Object | null | undefined) {
    if (name === 'hello') {
      pageOneTmp()
    }
  }

  onPageShow(): void {
    const session = this.session;
    if (session != undefined) {
      session.setReceiveDataCallback((data: Record<string, RecordData>): void => {
        this.storageLink = JSON.stringify(data)
        console.info('invoke for test, handle callback set by setReceiveDataCallback successfully');
      })
      session.setReceiveDataForResultCallback(func1)
    }
  }

  build(): void {
    Navigation(this.pathStack) {
      Row() {
        Column() {
          Text(this.storageLink)
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
          Button($r('app.string.UIExtensionComponent_button1')).onClick((event: ClickEvent)=> {
            const session = this.session;
            if (session != undefined) {
              session.sendData({ 'data': 543321 } as Record<string, RecordData>)
              console.info('send 543321, for test')
            }
          })
          Button('terminate').onClick((event: ClickEvent)=> {
            if (this.session != undefined) {
              this.session?.terminateSelf();
            }
            this.storage?.clear()
          })
          Button('terminate with result').onClick((event: ClickEvent)=>{
            if (this.session != undefined) {
              this.session?.terminateSelfWithResult({
                resultCode: 0,
                want: {
                  bundleName: 'myBundleName',
                  parameters: { 'result': 123456 }
                }
              })
            }
            this.storage?.clear()
          })

          Button($r('app.string.UIExtensionComponent_button2')).onClick((event: ClickEvent)=> {
            this.pathStack.pushPath(new NavPathInfo('hello', null))
          })
        }
      }
      .height('100%')
    }.navDestination(this.PageMap)
    .mode(NavigationMode.Stack)
  }
}

function func1(data: Record<string, RecordData>): Record<string, RecordData> {
  AppStorage.setOrCreate('message', JSON.stringify(data))
  console.info('invoke for test, handle callback set by setReceiveDataForResultCallback successfully');
  return data;
}

@Component
export struct pageOneTmp {
  pathStack: NavPathStack = new NavPathStack()

  build(): void {
    NavDestination() {
      Column() {
        Text('Hello World')
      }.width('100%').height('100%')
    }.title('pageOne')
    .onBackPressed(() => {
      const popDestinationInfo = this.pathStack.pop()
      console.log('pop' + $r('app.string.UIExtensionComponent_return') + JSON.stringify(popDestinationInfo))
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
