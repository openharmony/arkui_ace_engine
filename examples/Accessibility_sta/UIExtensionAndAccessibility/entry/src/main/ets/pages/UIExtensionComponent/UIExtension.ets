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

import { Entry, Component, Column, UIExtensionComponent, UIExtensionProxy,
  Text, Button,
  NavDestination, Color, Visibility, $r, ClickEvent } from '@ohos.arkui.component';
import { State } from '@ohos.arkui.stateManagement';
import Want from '@ohos.app.ability.Want';
import { RecordData, BusinessError } from '@ohos.base';

@Entry
@Component
export struct UIExtension {
  @State message1: string = 'Hello World 1'
  @State message2: string = 'Hello World 2'
  @State message3: string = 'Hello World 3'
  @State visible: Visibility = Visibility.Hidden
  @State wid: number = 300
  @State hei: number = 300
  private proxy: UIExtensionProxy | null = null;

  build(): void {
    NavDestination() {
      Column() {
        Column() {
          Text(this.message1).fontSize(25)
          Text(this.message2).fontSize(25)
          Text(this.message3).fontSize(25)

          UIExtensionComponent(this.createWant())
            .width(this.wid)
            .height(this.hei)
            .border({ width: 5, color: Color.Blue })
            .onReceive((data: Record<string, RecordData>) => {
              console.info('Lee onReceive, for test')
              this.message3 = JSON.stringify(data['data'])
            })
            .onTerminated((info) => {
              console.info('onTerminated: code =' + info.code + ', want = ' + JSON.stringify(info.want));
            })
            .onError((error) => {
              console.info('TestUEC onError, code: ' + error.code.toString() + ', message: ' + error.message);
            })
            .onRemoteReady((proxy: UIExtensionProxy) => {
              console.info('onRemoteReady, for test')
              this.proxy = proxy;
              proxy.onAsyncReceiverRegister(syncRegisterCallback1);
              proxy.onAsyncReceiverRegister((proxy1: UIExtensionProxy) => {
                console.info('on invoke for test, type is asyncReceiverRegister')
              });
            })
          Button($r('app.string.UIExtensionComponent_button3')).onClick((_event: ClickEvent) => {
            const proxy = this.proxy;
            if (proxy != null) {
              proxy.send({ 'data': 'hello1' } as Record<string, RecordData>)
              try {
                let re: Record<string, RecordData> =
                  proxy.sendSync({ 'data': 'hello2' } as Record<string, RecordData>);
                console.info('for test, re = ' + JSON.stringify(re));
              } catch (err) {
                console.error(`sendSync failed for test. errCode = ${(err as BusinessError).code}, message = ${(err as BusinessError).message}`);
              }
            }
          })
        }
      }
      .height('100%')
      .width('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.UI_Extension_Component_title'))
  }

  private createWant(): Want {
    let want: Want = new Want();
    want.bundleName = 'com.samples.uiextensionandaccessibility';
    want.abilityName = 'UIExtensionProvider';
    want.parameters = { 'ability.want.params.uiExtensionType': 'sys/commonUI' } as Record<string, RecordData>;
    return want;
  }
}

function syncRegisterCallback1(proxy: UIExtensionProxy): void {
  console.info('on invoke for test, syncRegisterCallback1, type is syncReceiverRegister')
}

function syncRegisterCallback2(proxy: UIExtensionProxy): void {
  console.info('on invoke for test, syncRegisterCallback2, type is syncReceiverRegister')
}
