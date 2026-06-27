'use static'

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

import { ComponentCard } from '../../common/Card'
import common from '@ohos.app.ability.common';
import {
  Entry,
  Component,
  Builder,
  Column,
  List,
  ListItem,
  Row,
  Text,
  TextInput,
  Button,
  ForEach,
  NavDestination,
  HorizontalAlign,
  TextAlign,
  ListItemAlign,
  ButtonType,
  ResourceStr,
  RowOptions
} from '@kit.ArkUI';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';

// Message type definition
export interface Message {
  id: int
  content: ResourceStr
  sender: ResourceStr
}
@Entry
@Component
export struct ListChatRoom {
  // Custom message component
  @Builder
  MessageItem(message: Message): void {
    Column() {
      Text(`${message.sender}: ${message.content}`)
        .fontSize(16)
        .textAlign(TextAlign.Start)
        .padding(10)
        .backgroundColor(message.sender === 'system' ? '#F0F0F0' : '#E6F3FF')
        .borderRadius(8)
    }
    .width('100%')
    .alignItems(HorizontalAlign.Start)
    .margin({ bottom: 8 })
  }

  // Send message method
  sendMessage(): void {
    if (this.inputText.trim()) {
      this.messages = [...this.messages, {
        id: Date.now().toInt(),
        content: this.inputText,
        sender: 'audience'
      }]
      this.inputText = ''
    }
  }

  // Input box content
  @State inputText: string = ''

  // Message list data
  @State messages: Message[] = [] as Message[];

  aboutToAppear(): void {
    const context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    // The value of app.string.welcome_live_room in resource file is 'Welcome to the live room'
    const welcomeLiveRoom = context.resourceManager.getStringByNameSync('welcome_live_room');
    // The value of app.string.system in resource file is 'System'
    const system = context.resourceManager.getStringByNameSync('system');
    // The value of app.string.hello_everyone in resource file is 'Hello everyone~'
    const helloEveryone = context.resourceManager.getStringByNameSync('hello_everyone');
    // The value of app.string.anchors in resource file is 'Anchor'
    const anchors = context.resourceManager.getStringByNameSync('anchors');
    this.messages = [
      { id: 1, content: welcomeLiveRoom, sender: system },
      { id: 2, content: helloEveryone, sender: anchors }
    ];
  }

  build(): void {
    NavDestination() {
      Column() {
        // Please replace $r('app.string.ListChatRoom_title') with the actual resource file.
        // In this example, the value of this resource file is "Switch Layout Direction"
        ComponentCard({ title: $r('app.string.ListChatRoom_title') }) {
          Column() {
            // Chat message area
            List({ space: 10 }) {
              ForEach(this.messages, (item: Message) => {
                ListItem() {
                  this.MessageItem(item)
                }
              }, (item: Message) => item.id.toString())
            }
            .stackFromEnd(true)
            .layoutWeight(1)  // Occupy remaining space
            .alignListItem(ListItemAlign.Center)

            // Input area
            Row({ space: 10 } as RowOptions) {
              // The value of app.string.say_something in resource file is 'Say something...'
              TextInput({ text: this.inputText, placeholder: $r('app.string.say_something') })
                .layoutWeight(1)
                .onChange((value: string) => {
                  this.inputText = value
                })
                .onSubmit(() => { // Press Enter to send
                  this.sendMessage()
                })

              Button($r('app.string.message'), { type: ButtonType.Capsule })
                .backgroundColor('#007AFF')
                .onClick(() => {
                  this.sendMessage()
                })
            }
            .padding(10)
            .backgroundColor('#F5F5F5')
          }
          .width('100%')
          .height('100%')
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Please replace $r('app.string.ListChatRoom_title') with the actual resource file.
    // In this example, the value of this resource file is "Switch Layout Direction"
    .title($r('app.string.ListChatRoom_title'))
  }
}
