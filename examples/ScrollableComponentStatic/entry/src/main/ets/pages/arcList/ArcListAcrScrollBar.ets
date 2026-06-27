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
  ComponentContent,
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  NavDestination,
  Entry,
  Component,
  Text,
  Image,
  $r,
  Color,
  ResourceStr,
  Resource,
  Alignment,
  UIContext,
  wrapBuilder,
  Scroller
} from '@kit.ArkUI';
import { ArcList, ArcListItem } from '@ohos.arkui.ArcList';
import { ArcScrollBar } from '@ohos.arkui.ArcScrollBar';
import { ComponentCard } from '../../common/Card';

@Builder
function customHeader(): void {
  Column() {
    Text($r('app.string.ArcListCrown_set'))
      .fontColor('#FFFFFFFF')
      .fontSize('19fp')
  }
}

@Entry
@Component
export struct ArcListAcrScrollBar {
  private arcListScroller: Scroller = new Scroller();


  context: UIContext = this.getUIContext();
  arcListHeader: ComponentContent<Object> = new ComponentContent<Object>(this.context, wrapBuilder(customHeader));

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Replace $r('app.string.ArcListAcrScrollBar_title') with actual resource file.
        // In this example, the resource file's value is "Add external scrollbar ArcScrollBar"
        ComponentCard({ title: $r('app.string.ArcListAcrScrollBar_title') }) {
          // Use arcListScroller to initialize scroller parameter of ArcList component,
          // completing the binding between arcListScroller and arc list.
          ArcList({ scroller: this.arcListScroller, header: this.arcListHeader }) {
            ArcListItem() {
              Row() {
                Image($r('app.media.wlan')).width('99px').height('99px')
                  .borderRadius('50px').margin({ left: 7 })
                Column() {
                  Text($r('app.string.ArcListStyles_wlan')).fontSize('38px').fontColor('#FFFFFFFF')
                  Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                }.width('190px')

                Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                  .borderRadius('50px')
              }
            }
            .borderRadius('65px')
            .width('414px')
            .height('129px')
            .backgroundColor('#26FFFFFF')

            ArcListItem() {
              Row() {
                Image($r('app.media.blueTooth')).width('99px').height('99px')
                  .borderRadius('50px').margin({ left: 7 })
                Column() {
                  Text($r('app.string.ArcListStyles_blue')).fontSize('38px').fontColor('#FFFFFFFF')
                  Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                }.width('190px')

                Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                  .borderRadius('50px')
              }
            }
            .borderRadius('65px')
            .width('414px')
            .height('129px')
            .backgroundColor('#26FFFFFF')

            ArcListItem() {
              Row() {
                Image($r('app.media.mobileData')).width('99px').height('99px')
                  .borderRadius('50px').margin({ left: 7 })
                Column() {
                  Text($r('app.string.ArcListStyles_net')).fontSize('38px').fontColor('#FFFFFFFF')
                }.width('190px')

                Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                  .borderRadius('50px')
              }
            }
            .borderRadius('65px')
            .width('414px')
            .height('129px')
            .backgroundColor('#26FFFFFF')

            ArcListItem() {
              Row() {
                Image($r('app.media.ic_settings_more_connections')).width('99px').height('99px')
                  .borderRadius('50px').margin({ left: 7 })
                Column() {
                  Text($r('app.string.ArcListStyles_connect')).fontSize('38px').fontColor('#FFFFFFFF')
                }.width('190px')

                Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                  .borderRadius('50px')
              }
            }
            .borderRadius('65px')
            .width('414px')
            .height('129px')
            .backgroundColor('#26FFFFFF')

            ArcListItem() {
              Row() {
                Image($r('app.media.displayAndBrightness')).width('99px').height('99px')
                  .borderRadius('50px').margin({ left: 7 })
                Column() {
                  Text($r('app.string.ArcListStyles_light')).fontSize('38px').fontColor('#FFFFFFFF')
                }.width('190px')

                Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                  .borderRadius('50px')
              }
            }
            .borderRadius('65px')
            .width('414px')
            .height('129px')
            .backgroundColor('#26FFFFFF')

          }
          .width('466px')
          .height('466px')
          .space(LengthMetrics.px(10))
          .borderRadius('233px')
          .backgroundColor(Color.Black)

          // Use arcListScroller to initialize scroller parameter of ArcScrollBar component,
          // completing the binding between arcListScroller and scrollbar.
          ArcScrollBar({ scroller: this.arcListScroller })
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcListAcrScrollBar_title') with actual resource file.
    // In this example, the resource file's value is "Add external scrollbar ArcScrollBar"
    .title($r('app.string.ArcListAcrScrollBar_title'))
  }
}
