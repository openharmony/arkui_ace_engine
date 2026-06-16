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

import { ComponentCard } from '../../common/Card';
import util from '@ohos.util';
import { $r } from '@kit.ArkUI';
import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  Row,
  Text,
  Image,
  ForEach,
  NavDestination,
  FlexAlign,
  ResourceStr,
  Resource,
  Length
} from '@kit.ArkUI';

export class Contact {
  public key: string = util.generateRandomUUID(true);
  public name: ResourceStr;
  public icon: Resource;

  constructor(name: ResourceStr, icon: Resource) {
    this.name = name;
    this.icon = icon;
  }
}

@Entry
@Component
export struct ListIteration {
  private contacts: Array<Contact> = [

    // The value of app.string.peopleOne in resource file is 'Xiao Ming', app.media.iconA is a custom resource
    new Contact($r('app.string.peopleOne'), $r('app.media.iconA')),
    // The value of app.string.peopleTwo in resource file is 'Xiao Hong', app.media.iconB is a custom resource
    new Contact($r('app.string.peopleTwo'), $r('app.media.iconB'))
  ];

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.ListIteration_titleExample') }) {
          List() {
            ForEach(this.contacts, (item: Contact) => {
              ListItem() {
                Row() {
                  Image(item.icon)
                    .width(40)
                    .height(40)
                    .margin(10)
                  Text(item.name).fontSize(20)
                }
                .width('100%')
                .justifyContent(FlexAlign.Start)
              }
            }, (item: Contact) => JSON.stringify(item))
          }
          .width('100%')
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.ListIteration_title'))
  }
}
