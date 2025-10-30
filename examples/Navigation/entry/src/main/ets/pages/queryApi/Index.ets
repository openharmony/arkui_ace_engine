/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { BusinessError } from '@ohos.base';

import('library/Index');
import('./Page');
import('sharedLibrary/src/main/ets/pages/Index');

class BackParam {
  info: String = 'params from Index'
}
@Entry({routeName:'pages/Index'})
@Component
struct Index {
  @State message: string = 'Hello Index';
  @State pageInfo:string = '';
  @State Index:number = 1;
  @State Text:string = '';
  @State Text1:string = '';
  @State Text2:string = '';
  @State Text3:string = '';
  @State Text4:string = '';
  @State Text5:string = '';
  @State url:string = '';
  @State url1:string = '';
  @State url2:string = '';
  @State Index1:number = 1;
  @State Index2:number = 1;
  @State Index3:number = 1;
  @State pageInfo5:string = '';
  @State params:string = '';

  onPageShow() {
    const params: object = router.getParams();
    this.params = 'cxx' + JSON.stringify(params);
  }

  build() {
    Row() {
      Column() {
        Text(this.message)
        Text(this.params)
        Text(`Index: ${this.Text}`).width('95%')
        Flex() {
          TextInput({ placeholder: 'input index', text: this.Text })
            .key('getStateByIndex')
              .showError('result：')
            .borderRadius(0)
            .fontSize(12)
            .onChange((value: string) => {
              this.Text = value
              this.Index = parseInt(value)
            })
          Button('getStateByIndex')
            .padding(2)
            .type(ButtonType.Normal)
            .backgroundColor(0x317aff)
            .fontSize(12)
            .width(150)
            .onClick(() => {
              this.pageInfo = 'message：' + JSON.stringify(router.getStateByIndex(this.Index));
            })
        }

        TextArea({ text: this.pageInfo }).width(400)

        Text(`url：${this.Text1}`)
          .width('95%')
          .margin({top: 10})
        Flex() {
          TextInput({ placeholder: 'input url', text: this.Text1 })
            .key('getStateByUrl')
            .borderRadius(0)
            .fontSize(12)
            .showError('result：')
            .onChange((value1: string) => {
              this.Text1 = value1
              this.url = value1
            })
          Button('getStateByUrl')
            .padding(2)
            .type(ButtonType.Normal)
            .backgroundColor(0x317aff)
            .fontSize(12)
            .width(150)
            .onClick(() => {
              this.pageInfo5 = 'message：' + JSON.stringify(router.getStateByUrl(this.url));
            })
        }

        TextArea({ text: this.pageInfo5 }).width(400)

        Text(`return index：${this.Text2}`)
          .width('95%')
          .margin({top: 10})
        Flex() {
          TextInput({ placeholder: 'input index', text: this.Text2 })
            .borderRadius(0)
            .fontSize(12)
            .onChange((value2: string) => {
              this.Text2 = value2
              this.Index1 = parseInt(value2)
            })

          Button('return index')
            .backgroundColor(0x317aff)
            .fontSize(12)
            .type(ButtonType.Normal)
            .width(200)
            .padding(2)
            .margin({left: 2, right: 2})
            .onClick(() => {
              let params: object = new BackParam()
              router.back(this.Index1, params)
            })

          Button('return index without params')
            .backgroundColor(0x317aff)
            .fontSize(12)
            .type(ButtonType.Normal)
            .width(310)
            .padding(2)
            .onClick(() => {
              router.back(this.Index1)
            })
        }

        Text(`return index, open dialog：${this.Text3}`)
          .width('95%')
          .margin({top: 10})
        Flex() {
          TextInput({ placeholder: 'input index', text: this.Text3 })
            .key('backIndex')
            .borderRadius(0)
            .fontSize(12)
            .onChange((value3: string) => {
              this.Text3 = value3
              this.Index2 = parseInt(value3)
            })

          Button('backIndex')
            .backgroundColor(0x317aff)
            .fontSize(12)
            .type(ButtonType.Normal)
            .width(120)
            .padding(2)
            .margin({left: 2, right: 2})
            .onClick(() => {
              let params: object = new BackParam()
              try {
                router.showAlertBeforeBackPage({
                  message: 'Message Info index'
                });
              } catch (err) {
                console.error(`showAlertBeforeBackPage failed, code is ${(err as BusinessError).code}, message is ${(err as BusinessError).message}`);
              }
              router.back(this.Index2, params)
            })

          Button('backIndex without params')
            .backgroundColor(0x317aff)
            .fontSize(12)
            .type(ButtonType.Normal)
            .width(230)
            .padding(2)
            .onClick(() => {
              try {
                router.showAlertBeforeBackPage({
                  message: 'Message Info index'
                });
              } catch (err) {
                console.error(`showAlertBeforeBackPage failed, code is ${(err as BusinessError).code}, message is ${(err as BusinessError).message}`);
              }
              router.back(this.Index2)
            })
        }

        Text(`use pushurl jump page：${this.Text4}`)
          .width('95%')
          .margin({top: 10})

        Flex() {
          TextInput({ placeholder: 'input url', text: this.Text4 })
            .key('pushUrlTextInput')
            .borderRadius(0)
            .fontSize(12)
            .onChange((value4: string) => {
              this.Text4 = value4
              this.url1 = value4
            })

          Button('go to ' + this.url1)
            .key('pushUrlButton')
            .backgroundColor(0x317aff)
            .fontSize(12)
            .type(ButtonType.Normal)
            .width(80)
            .padding(2)
            .onClick(() => {
              router.pushUrl({
                url: this.url1,
                params: new BackParam()
              })
            })
        }

        Text(`use pushnamedroute jump page：${this.Text5}`)
          .width('95%')
          .margin({top: 10})

        Flex() {
          TextInput({ placeholder: 'input url', text: this.Text5 })
            .key('pushNamedRouteTextInput')
            .borderRadius(0)
            .fontSize(12)
            .onChange((value5: string) => {
              this.Text5 = value5
              this.url2 = value5
            })

          Button('go to ' + this.url1)
            .key('pushNamedRouteButton')
            .fontSize(12)
            .backgroundColor(0x317aff)
            .type(ButtonType.Normal)
            .padding(2)
            .width(80)
            .onClick(() => {
              router.pushNamedRoute({
                name: this.url2,
                params: new BackParam()
              })
            })
        }
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
    .alignItems(VerticalAlign.Top)
  }
}