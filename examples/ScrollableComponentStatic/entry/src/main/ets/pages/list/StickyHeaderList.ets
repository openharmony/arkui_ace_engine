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
  Builder,
  Column,
  List,
  ListItem,
  ListItemGroup,
  Row,
  Text,
  Image,
  LazyForEach,
  NavDestination,
  StickyStyle,
  FlexAlign,
  Resource,
  IDataSource,
  DataChangeListener
} from '@kit.ArkUI';

export class Contact {
  public key: string = util.generateRandomUUID(true);
  public name: string | Resource;
  public icon: Resource;

  constructor(name: string | Resource, icon: Resource) {
    this.name = name;
    this.icon = icon;
  }
}

export class ContactsGroup {
  public title: string = '';
  public contacts: Array<Contact> | null = null;
  public key: string = '';
}

export class ContactsGroupDataSource implements IDataSource<ContactsGroup> {
  private list: ContactsGroup[] = [];

  constructor(list: ContactsGroup[]) {
    this.list = list;
  }

  totalCount(): int {
    return this.list.length;
  }

  getData(index: int): ContactsGroup {
    return this.list[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
  }
}

export class ContactDataSource implements IDataSource<Contact> {
  private list: Contact[] = [];

  constructor(list: Contact[]) {
    this.list = list;
  }

  totalCount(): int {
    return this.list.length;
  }

  getData(index: int): Contact {
    return this.list[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
  }
}

export let contactsGroups: ContactsGroup[] = [
  {
    title: 'A',
    contacts: [
      // The value of app.string.contacts_A_one in resource file is 'Ai Jia', app.media.iconA is a custom resource
      new Contact($r('app.string.contacts_A_one'), $r('app.media.iconA')),
      // The value of app.string.contacts_A_two in resource file is 'An An', app.media.iconB is a custom resource
      new Contact($r('app.string.contacts_A_two'), $r('app.media.iconB')),
      // app.media.iconC is a custom resource
      new Contact('Angela', $r('app.media.iconC')),
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'B',
    contacts: [
      // The value of app.string.contacts_B_one in resource file is 'Bai Ye', app.media.iconD is a custom resource
      new Contact($r('app.string.contacts_B_one'), $r('app.media.iconD')),
      // The value of app.string.contacts_B_three in resource file is 'Bo Ming', app.media.iconE is a custom resource
      new Contact($r('app.string.contacts_B_three'), $r('app.media.iconE'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup
];
export let contactsGroupsDataSource: ContactsGroupDataSource = new ContactsGroupDataSource(contactsGroups);

@Entry
@Component
export struct StickyHeaderList {
  // Define grouped contact data collection contactsGroups array
  @Builder
  itemHead(text: string): void {
    // Header component of the list group, corresponding to the component at contact groups A, B, etc.
    Text(text)
      .fontSize(20)
      .backgroundColor('#fff1f3f5')
      .width('100%')
      .padding(5)
  }

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.StickyHeaderList_titleExample') }) {
          List() {
            // Lazy load ListItemGroup, contactsGroups is the data collection of multiple grouped
            // contacts and title for contacts
            LazyForEach(contactsGroupsDataSource, (itemGroup: ContactsGroup) => {
              ListItemGroup({ header: this.itemHead(itemGroup.title) }) {
                // Cyclically render ListItem
                if (itemGroup.contacts) {
                  LazyForEach(new ContactDataSource(itemGroup.contacts as Contact[]), (item: Contact) => {
                    ListItem() {
                      Row() {
                        Image(item.icon).width(40).height(40).margin(10)
                        Text(item.name).fontSize(20)
                      }.width('100%').justifyContent(FlexAlign.Start)
                    }
                  }, (item: Contact) => JSON.stringify(item))
                }
              }
            }, (itemGroup: ContactsGroup) => JSON.stringify(itemGroup))
          }
          .sticky(StickyStyle.Header) // Set sticky header to achieve sticky title effect
          .height(130)
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.StickyHeaderList_title'))
  }
}
