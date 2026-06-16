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
  Stack,
  StackOptions,
  NavDestination,
  Entry,
  Component,
  Builder,
  Text,
  Image,
  $r,
  Color,
  ResourceStr,
  Alignment,
  ForEach,
  TextAlign,
  FlexAlign,
  BarState,
  ComponentContent,
  Scroller,
  UIContext,
  wrapBuilder,
  HitTestMode,
  FontStyle,
  Font
} from '@kit.ArkUI';
import { ArcList, ArcListItem, ArcListAttribute, ArcListItemAttribute } from '@ohos.arkui.ArcList';
import { ComponentCard } from '../../common/Card';
import {
  ArcAlphabetIndexer,
  ArcAlphabetIndexerAttribute,
  ArcAlphabetIndexerInitInfo
} from '@ohos.arkui.ArcAlphabetIndexer';
import { util } from '@kit.ArkTS';
import { ColorMetrics } from '@ohos.arkui.node';
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
    Text($r('app.string.contacts'))
      .fontColor('#FFFFFF')
      .fontSize('19fp')
  }
}
const alphabets: string[] = [
  '#', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
];

@Entry
@Component
export struct ArcListArcIndexerBar {

  private watchSize: string = '600px'; // Default watch width and height: 233*233
  private context1: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;

  @State
  contacts: Contact[] = [
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
  // Selected item index of indexer bar
  @State
  indexerIndex: int = 0;
  // Scroll controller bound to list
  private arcListScroller: Scroller = new Scroller();

  context: UIContext = this.getUIContext();
  tabBar1: ComponentContent<Object> = new ComponentContent<Object>(this.context, wrapBuilder(buildText));

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Replace $r('app.string.ArcListArcIndexerBar_title') with actual resource file.
        // In this example, the resource file's value is "Link with arc indexer bar ArcAlphabetIndexer"
        ComponentCard({ title: $r('app.string.ArcListArcIndexerBar_title') }) {
          Stack({ alignContent: Alignment.End } as StackOptions) {
            ArcList({ initialIndex: 0, header: this.tabBar1, scroller: this.arcListScroller }) {
              ForEach(this.contacts, (item: Contact) => {
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
                  .width('100%')
                  .justifyContent(FlexAlign.Start)
                }
                .borderRadius('65px')
                .width('370px')
                .height('130px')
                .backgroundColor('#26FFFFFF')
              }, (item: Contact) => JSON.stringify(item))
            }
            .space(LengthMetrics.px(10))
            .scrollBar(BarState.Off)
            .width(this.watchSize)
            .height(this.watchSize)
            .borderRadius(this.watchSize)
            .backgroundColor(Color.Black)
            .onScrollIndex((firstIndex: int, lastIndex: int, centerIndex: int): void => {
              // Recalculate the position of corresponding indexer bar this.selectedIndex
              // based on the index value the list has scrolled to
              this.indexerIndex = centerIndex + 1;
            })
            .id('arcIndexTest')
            // Arc indexer bar component
            ArcAlphabetIndexer({ arrayValue: alphabets, selected: this.indexerIndex } as ArcAlphabetIndexerInitInfo)
              .selected(this.indexerIndex!!)
              .onSelect((index: int): void => {
                // After selecting an indexer item, list jumps to corresponding position
                this.indexerIndex = index
                this.arcListScroller.scrollToIndex(this.indexerIndex - 1)
              })
              .autoCollapse(true)
              .width(this.watchSize)
              .height(this.watchSize)
              .usePopup(false)
              .hitTestBehavior(HitTestMode.Transparent)
              .selectedColor(ColorMetrics.resourceColor(0xFFFFFF))
              .selectedBackgroundColor(ColorMetrics.resourceColor(0x1F71FF))
              .color(ColorMetrics.resourceColor(0xFFFFFF))
              .popupColor(ColorMetrics.resourceColor(0xFFFFFF))
              .popupBackground(ColorMetrics.resourceColor('#D8404040'))
              .itemSize(LengthMetrics.px(12))
              .selectedFont({
                size: '11.0fp',
                style: FontStyle.Normal,
                weight: 500,
                family: 'HarmonyOS Sans'
              } as Font)
              .font({
                size: '11.0fp',
                style: FontStyle.Normal,
                weight: 500,
                family: 'HarmonyOS Sans'
              } as Font)
          }
          .width('600px')
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcListArcIndexerBar_title') with actual resource file.
    // In this example, the resource file's value is "Link with arc indexer bar ArcAlphabetIndexer"
    .title($r('app.string.ArcListArcIndexerBar_title'))
  }
}
