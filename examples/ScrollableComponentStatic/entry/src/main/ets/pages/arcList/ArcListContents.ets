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
import {
  LengthMetrics,
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  NavDestination,
  Entry,
  Component,
  Text,
  Image,
  ForEach,
  $r,
  Color,
  ResourceStr,
  Resource,
  FlexAlign
} from '@kit.ArkUI';
import { ArcList, ArcListItem, ArcListAttribute, ArcListItemAttribute } from '@ohos.arkui.ArcList';
import { ComponentCard } from '../../common/Card';
import { State } from '@ohos.arkui.stateManagement';
import { util } from '@kit.ArkTS';
import { common } from '@kit.AbilityKit';

export class Contact {
  key: string = util.generateRandomUUID(true);
  name: ResourceStr;
  icon: Resource;

  constructor(name: ResourceStr, icon: Resource) {
    this.name = name;
    this.icon = icon;
  }
}

@Entry
@Component
export struct ArcListContents {
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  @State
  private contacts: Contact[] = [
    // Replace $r('app.string.xxx') with actual resource file
    new Contact($r('app.string.name_xiaohong'), $r('app.media.ic_contact')),
    new Contact($r('app.string.name_xiaolan'), $r('app.media.ic_contact')),
    new Contact($r('app.string.name_xiaowang'), $r('app.media.ic_contact')),
    new Contact($r('app.string.name_xiaoli'), $r('app.media.ic_contact')),
    new Contact($r('app.string.name_xiaoming'), $r('app.media.ic_contact'))
  ];

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Replace $r('app.string.ArcListContents_title') with actual resource file.
        // In this example, the resource file's value is "Iterate arc list contents"
        ComponentCard({ title: $r('app.string.ArcListContents_title') }) {
          ArcList({ initialIndex: 2 }) {
            ForEach(this.contacts, (item: Contact) => {
              ArcListItem() {
                Row() {
                  Image(item.icon)
                    .width(40)
                    .height(40)
                    .margin(10)
                    .backgroundColor('#FF9CC998')
                    .borderRadius(20)
                  Text(item.name).fontSize('38px').fontColor('#FFFFFFFF')
                }
                .width('100%')
                .justifyContent(FlexAlign.Start)
              }
              .borderRadius('65px')
              .width('410px')
              .height('130px')
              .backgroundColor('#26FFFFFF')
            }, (item: Contact) => JSON.stringify(item))
          }
          .space(LengthMetrics.px(10))
          .width('466px')
          .height('466px')
          .borderRadius('233px')
          .backgroundColor(Color.Black)
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcListContents_title') with actual resource file.
    // In this example, the resource file's value is "Iterate arc list contents"
    .title($r('app.string.ArcListContents_title'))
  }
}
