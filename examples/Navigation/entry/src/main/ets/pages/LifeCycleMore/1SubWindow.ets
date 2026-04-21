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
import { pageOne, pageTwo, pageThree, navId1 } from './common';

@Entry
@Component
struct SubWindow {
  @State stackA: NavPathStack = new NavPathStack();
  @State stackB: NavPathStack = new NavPathStack();
  private curWindow: window.Window | null = null;

  @Builder
  PageMapA(name: string) {
    if (name === 'pageOne') {
      pageOne({str:'SubA'})
    } else if (name === 'pageTwo'){
      pageTwo({str:'SubA'})
    } else if (name === 'pageThree'){
      pageThree({str:'SubA'})
    }
  }

  @Builder
  PageMapB(name: string) {
    if (name === 'pageOne') {
      pageOne({str:'SubB'})
    } else if (name === 'pageTwo'){
      pageTwo({str:'SubB'})
    } else if (name === 'pageThree'){
      pageThree({str:'SubB'})
    }
  }

  @Builder Title1() {
    Column() {
      Text('SubA Navigation').fontSize(18)
    }.alignItems(HorizontalAlign.Start)
  }

  @Builder Title2() {
    Column() {
      Text('SubB Navigation').fontSize(18)
    }.alignItems(HorizontalAlign.Start)
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

  build() {
    Column({space:10}) {
      Text('SubWindow').fontSize(20)
      Button('close Window')
        .onClick(() => {
          this.closeWindow();
        })


      Navigation(this.stackA) {
        Column({space:10}){
          Button('SubA push pageOne')
            .onClick(() => {
              this.stackA.pushPath({name: 'pageOne', param: 1})
            })

          NavRouter({name: "pageOne", param: 1}) {
            Stack({alignContent: Alignment.Center}) {
              Text('SubA navRouter pageOne')
                .padding(5)
                .fontSize(20)
            }
          }.borderWidth(1)
        }

      }
      .navDestination(this.PageMapA)
      .title({builder:this.Title1,height:'40vp'})
      .backgroundColor(Color.Pink)
      .width('100%')
      .height('280vp')


      Navigation(this.stackB) {
        Column({space:10}){
          Button('SubB push pageOne')
            .onClick(() => {
              this.stackB.pushPath({name: 'pageOne', param: 1})
            })

          NavRouter({name: "pageOne", param: 1}) {
            Stack({alignContent: Alignment.Center}) {
              Text('SubB navRouter pageOne')
                .padding(5)
                .fontSize(20)
            }
          }.borderWidth(1)
        }

      }
      .id(navId1)
      .navDestination(this.PageMapB)
      .title({builder:this.Title2,height:'40vp'})
      .backgroundColor('#ffc7f5c7')
      .width('100%')
      .height('280vp')
    }
    .backgroundColor(Color.Green)
    .width('100%')
    .height('100%')
    .borderWidth(1)
  }
}