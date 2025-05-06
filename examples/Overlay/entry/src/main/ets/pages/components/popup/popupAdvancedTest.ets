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

import { Popup, PopupTextOptions, PopupButtonOptions, PopupIconOptions } from '@kit.ArkUI';

@Builder
export function PopupAdvancedBuilder(name: string, param: Object) {
  PopupExample04()
}

@Entry
@Component
struct PopupExample04 {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup1: boolean = false

  @Builder
  PopupBuilder() {
    Row() {
      // popup 自定义高级组件
      Popup({
        // PopupIconOptions类型设置图标内容
        icon: {
          image: $r('app.media.app_icon'),
          width:32,
          height:32,
          fillColor:Color.White,
          borderRadius: 16
        } as PopupIconOptions,
        // PopupTextOptions类型设置文字内容
        title: {
          text: 'This is a popup with PopupOptions',
          fontSize: 20,
          fontColor: Color.Black,
          fontWeight: FontWeight.Normal
        } as PopupTextOptions,
        // PopupTextOptions类型设置文字内容
        message: {
          text: 'This is the message',
          fontSize: 15,
          fontColor: Color.Black
        } as PopupTextOptions,
        showClose: false,
        onClose: () => {
          console.info('close Button click')
        },
        // PopupButtonOptions类型设置按钮内容
        buttons: [{
          text: 'confirm',
          action: () => {
            console.info('confirm button click')
          },
          fontSize: 15,
          fontColor: Color.Black,
        },
        {
          text: 'cancel',
          action: () => {
            console.info('cancel button click')
          },
          fontSize: 15,
          fontColor: Color.Black
        }] as [PopupButtonOptions?, PopupButtonOptions?]
      })
    }
    .width(300)
    .height(200)
    .justifyContent(FlexAlign.Center)
  }
  build() {
    NavDestination() {
      Column({ space: 100 }) {
        Button('bindPopup内嵌Popup高级组件')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1
          })
          .bindPopup(this.handlePopup1!!, {
            builder: this.PopupBuilder(),
            autoCancel: false,
            focusable: true,
            mask: false,
            shadow: ShadowStyle.OUTER_DEFAULT_LG
          })
        Column() {
          Popup({
            // PopupIconOptions类型设置图标内容
            icon: {
              image: $r('app.media.app_icon'),
              width:32,
              height:32,
              fillColor:Color.White,
              borderRadius: 16
            } as PopupIconOptions,
            // PopupTextOptions类型设置文字内容
            title: {
              text: 'This is a popup with PopupOptions',
              fontSize: 20,
              fontColor: Color.Black,
              fontWeight: FontWeight.Normal
            } as PopupTextOptions,
            // PopupTextOptions类型设置文字内容
            message: {
              text: 'This is the message',
              fontSize: 15,
              fontColor: Color.Black
            } as PopupTextOptions,
            showClose: false,
            onClose: () => {
              console.info('close Button click')
            },
            // PopupButtonOptions类型设置按钮内容
            buttons: [{
              text: 'confirm',
              action: () => {
                console.info('confirm button click')
              },
              fontSize: 15,
              fontColor: Color.Black,
            },
            {
              text: 'cancel',
              action: () => {
                console.info('cancel button click')
              },
              fontSize: 15,
              fontColor: Color.Black
            }] as [PopupButtonOptions?, PopupButtonOptions?]
          })
        }
        .border({ color: Color.Black, width: 2 })
        .width('80%')
      }
      .width('100%')
    }
    .title('PopupAdvancedTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
