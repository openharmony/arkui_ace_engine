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
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  Stack,
  StackOptions,
  NavDestination,
  Entry,
  Component,
  Builder,
  Text,
  Image,
  ForEach,
  Button,
  ButtonOptions,
  $r,
  Color,
  ResourceStr,
  FlexAlign,
  TextAlign,
  BarState,
  Scroller,
  ComponentContent,
  UIContext,
  wrapBuilder,
  ButtonType,
  Curve,
  PlayMode,
  LengthMetrics
} from '@kit.ArkUI';
import { ArcList, ArcListItem, ArcListAttribute, ArcListItemAttribute } from '@ohos.arkui.ArcList';
import { util } from '@kit.ArkTS';
import { ComponentCard } from '../../common/Card';
import { common } from '@kit.AbilityKit';
import { State } from '@ohos.arkui.stateManagement';

export class Contact {
  key: string = util.generateRandomUUID(true);
  name: ResourceStr;
  firstChar: string;

  constructor(name: ResourceStr, firstChar: string) {
    this.name = name;
    this.firstChar = firstChar;
  }
}

@Builder
function buildText(): void {
  Column() {
    Text('Contacts ')
      .fontColor('#FFFFFF')
      .fontSize('19fp')

  }
}

@Entry
@Component
export struct ArcListSideSlip {
  private context1: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  @State
  contacts: Contact[] = [
    new Contact('Alice', 'A'),
    new Contact('Bob', 'B'),
    new Contact('Charlie', 'C'),
    new Contact('Diana', 'D'),
    new Contact('Eve', 'E'),
    // Replace $r('app.string.xxx') with actual resource file
    new Contact($r('app.string.name_aha'), 'A'),
    new Contact($r('app.string.name_beibei'), 'B'),
    new Contact($r('app.string.name_caicai'), 'C'),
    new Contact($r('app.string.name_dongdong'), 'D'),
    new Contact($r('app.string.name_enen'), 'E'),
    new Contact($r('app.string.name_fangfang'), 'F'),
    new Contact($r('app.string.name_gege'), 'G'),
    new Contact($r('app.string.name_haha'), 'H'),
    new Contact($r('app.string.name_jiji'), 'J'),
    new Contact($r('app.string.name_keke'), 'K'),
    new Contact($r('app.string.name_lele'), 'L'),
    new Contact($r('app.string.name_meimei'), 'M'),
    new Contact($r('app.string.name_nini'), 'N'),
    new Contact($r('app.string.name_ohuo'), 'O'),
    new Contact($r('app.string.name_pangpang'), 'P'),
    new Contact($r('app.string.name_qiqi'), 'Q'),
    new Contact($r('app.string.name_ranran'), 'R'),
    new Contact($r('app.string.name_shushu'), 'S'),
    new Contact($r('app.string.name_tiantian'), 'T'),
  ];
  private scrollerForList: Scroller = new Scroller();
  @State
  indexerIndex: int = 0;
  context: UIContext = this.getUIContext();
  tabBar1: ComponentContent<Object> = new ComponentContent<Object>(this.context, wrapBuilder(buildText));

  @Builder
  itemEnd(item: Contact): void {
    // Build end swipe-out component
    Button({ type: ButtonType.Circle } as ButtonOptions) {
      Image($r('app.media.ic_public_delete_filled'))
        .width(20)
        .height(20)
    }
    .width(20)
    .height(20)
    .backgroundColor(Color.Black)
    .onClick((): void => {
      this.getUIContext()?.animateTo({
        duration: 1000,
        curve: Curve.Smooth,
        iterations: 1,
        playMode: PlayMode.Normal,
      }, (): void => {
        // this.contacts is the list data source and can be constructed according to
        // actual scenarios. indexOf method can get the index of data to be deleted
        let index: int = this.contacts.indexOf(item);
        // Delete specified data item from data source
        this.contacts.splice(index, 1);
      })
    })
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Replace $r('app.string.ArcListSideSlip_title') with actual resource file.
        // In this example, the resource file's value is "Response to list item side swipe"
        ComponentCard({ title: $r('app.string.ArcListSideSlip_title') }) {
          Stack() {
            ArcList({ initialIndex: 0, header: this.tabBar1, scroller: this.scrollerForList }) {
              ForEach(this.contacts, (item: Contact) => {
                // When building ArcList, use ForEach to render ArcListItem based on
                // data source this.contacts
                ArcListItem() {
                  Row() {
                    Text(item.firstChar)
                      .textAlign(TextAlign.Center)
                      .width(30)
                      .height(30)
                      .margin(10)
                      .backgroundColor('#FF9CC998')
                      .borderRadius(20)
                    Text(item.name).fontSize('38px').fontColor('#FFFFFFFF')
                  }
                  .backgroundColor('#26FFFFFF')
                  .borderRadius('65px')
                  .width('90%')
                  .justifyContent(FlexAlign.Start)
                }
                .swipeAction({
                  end: {
                    // index is the index value of this ArcListItem in ArcList
                    builder: (): void => {
                      this.itemEnd(item);
                    },
                  }
                }) // Set side swipe property
                .borderRadius('65px')
                .width('400px')
                .height('130px')

              }, (item: Contact) => JSON.stringify(item))
            }
            .space(LengthMetrics.px(10))
            .scrollBar(BarState.Auto)
            .width('466px')
            .height('466px')
            .borderRadius('233px')
            .backgroundColor(Color.Black)
            .margin(50)
            .onScrollIndex((firstIndex: int, lastIndex: int, centerIndex: int): void => {
              this.indexerIndex = centerIndex + 1;
            })
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcListSideSlip_title') with actual resource file.
    // In this example, the resource file's value is "Response to list item side swipe"
    .title($r('app.string.ArcListSideSlip_title'))
  }
}
