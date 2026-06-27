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

import util from '@ohos.util';
import { ComponentCard } from '../../common/Card';
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
  Stack,
  ForEach,
  AlphabetIndexer,
  Scroller,
  NavDestination,
  Alignment,
  FlexAlign,
  Resource,
  StackOptions
} from '@kit.ArkUI';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';

const alphabets = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
  'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];

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

export let contactsGroups: ContactsGroup[] = [
  {
    title: 'A',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_A_one'), $r('sys.media.clone_app_badge_1')),
      new Contact($r('app.string.contacts_A_two'), $r('sys.media.clone_app_badge_2'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'B',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_B_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_B_two'), $r('sys.media.clone_app_badge_4')),
      new Contact($r('app.string.contacts_B_three'), $r('sys.media.clone_app_badge_5'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'D',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_D_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_D_two'), $r('sys.media.clone_app_badge_4')),
      new Contact($r('app.string.contacts_D_three'), $r('sys.media.clone_app_badge_5'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'F',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_F_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_F_two'), $r('sys.media.clone_app_badge_4'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'G',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_G_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_G_two'), $r('sys.media.clone_app_badge_4'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'H',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_H_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_H_two'), $r('sys.media.clone_app_badge_4')),
      new Contact($r('app.string.contacts_H_three'), $r('sys.media.clone_app_badge_5'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup,
  {
    title: 'X',
    contacts: [
      // $r('app.string.xxx') needs to be replaced with the resource file required by the developer
      new Contact($r('app.string.contacts_X_one'), $r('sys.media.clone_app_badge_3')),
      new Contact($r('app.string.contacts_X_two'), $r('sys.media.clone_app_badge_4')),
      new Contact($r('app.string.contacts_X_three'), $r('sys.media.clone_app_badge_5'))
    ],
    key: util.generateRandomUUID(true)
  } as ContactsGroup
];

@Entry
@Component
export struct ResponsiveScrollPositionList {
  @State selectedIndex: int = 0;
  private listScroller: Scroller = new Scroller();
  private currentGroupTitle: string = ''; // Used to track the currently displayed group title

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
        // Please replace $r('app.string.ResponsiveScrollPositionList_titleExample') with the actual
        // resource file. In this example, the value of this resource file is "Responsive Scroll Position Example"
        ComponentCard({ title: $r('app.string.ResponsiveScrollPositionList_titleExample') }) {
          Stack({ alignContent: Alignment.End } as StackOptions) {
            // This is a responsive scroll position example List container
            // listScroller initializes the scroller parameter of the List component, binding listScroller with the list.
            List({ scroller: this.listScroller }) {
              ForEach((contactsGroups as ContactsGroup[]), (itemGroup: ContactsGroup) => {
                ListItemGroup({ header: this.itemHead(itemGroup.title) }) {
                  // Cyclically render ListItem
                  if (itemGroup.contacts) {
                    ForEach((itemGroup.contacts as Contact[]), (item: Contact) => {
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
            .onScrollIndex((firstIndex: int) => {
              // Recalculate the position of the corresponding contact index bar this.selectedIndex based on the
              // index value scrolled to by the list
              let group = contactsGroups[firstIndex] as ContactsGroup;
              this.currentGroupTitle = group.title;
              this.selectedIndex = alphabets.indexOf(this.currentGroupTitle);
            })

            // Alphabet index component
            AlphabetIndexer({ arrayValue: alphabets, selected: 0 })
              .selected(this.selectedIndex)
              .onSelect((index: int) => {
                this.listScroller.scrollToIndex(index);
              })
          }
          .height('90%')
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Please replace $r('app.string.ResponsiveScrollPositionList_title') with the actual resource file.
    // In this example, the value of this resource file is "Responsive Scroll Position"
    .title($r('app.string.ResponsiveScrollPositionList_title'))
  }
}
