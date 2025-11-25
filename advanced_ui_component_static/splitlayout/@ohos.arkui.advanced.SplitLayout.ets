/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
  Component, ResourceStr, Column, GridRow, BreakpointsReference, GridRowDirection, Row, GridCol, Stack, Alignment,
  Image, Scroll, Text, FontWeight, TextAlign, HorizontalAlign, BarState, NestedScrollMode, Flex, FlexAlign, Area,
  ItemAlign, FlexDirection, $r, Padding, LocalizedMargin, Margin, BreakPoints, GridColColumnOption, BuilderParam,
  Builder
} from '@ohos.arkui.component';
import { State, PropRef } from '@ohos.arkui.stateManagement';
import { LengthMetrics } from '@ohos.arkui.node';
import hilog from '@ohos.hilog';

const TEXT_MARGIN_TOP_4: number = 4;
const TEXT_MARGIN_BOTTOM_8: number = 8;
const TEXT_MARGIN_BOTTOM_24: number = 24;
const TEXT_MARGIN_LEFT_48: number = 48;
const TEXT_MARGIN_RIGHT_48: number = 48;

@Component
export struct SplitLayout {
  @BuilderParam container: () => void =this.doBuilder;
  @Builder doBuilder(){}
  @State sizeValue: string = '';
  @State areaWidth: number = 0;
  @State imageBackgroundColor: string = '#19000000';
  @State mainImage: ResourceStr = '';
  @PropRef primaryText: ResourceStr = '';
  @PropRef secondaryText?: ResourceStr = '';
  @PropRef tertiaryText?: ResourceStr = '';

  build() {
    Column() {
      if (this.areaWidth < 600) {
        GridRow({
          columns: 4,
          breakpoints: {
            reference: BreakpointsReference.WindowSize
          } as BreakPoints,
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 4, sm: 4, md: 4, lg: 4 } as GridColColumnOption }) {
            Column() {
              Stack({ alignContent: Alignment.Bottom }) {
                Image(this.mainImage)
                  .height('100%')
                  .width('100%')
                Scroll() {
                  Column() {
                    Text(this.primaryText)
                      .fontWeight(FontWeight.Medium)
                      .textAlign(TextAlign.Center)
                      .fontSize($r('sys.float.Title_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    Text(this.secondaryText)
                      .textAlign(TextAlign.Center)
                      .fontSize($r('sys.float.Body_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_primary'))
                      .margin({ top: TEXT_MARGIN_TOP_4, bottom: TEXT_MARGIN_BOTTOM_8 } as Margin)
                    Text(this.tertiaryText)
                      .textAlign(TextAlign.Center)
                      .fontSize($r('sys.float.Caption_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                      .margin({ bottom: TEXT_MARGIN_BOTTOM_24 } as Margin)
                  }
                  .alignItems(HorizontalAlign.Center)
                  .margin({
                    left: $r('sys.float.ohos_id_max_padding_start'),
                    right: $r('sys.float.ohos_id_max_padding_end')
                  } as Margin)
                }.scrollBar(BarState.On)
                .nestedScroll({
                  scrollForward: NestedScrollMode.SELF_FIRST,
                  scrollBackward: NestedScrollMode.SELF_FIRST,
                })
              }
              .height('34%')
              .width('100%')

              Column() {
                this.container()
              }
              .height('66%')
              .width('100%')
            }
          }
        }
      } else if (600 < this.areaWidth && this.areaWidth < 840) {
        GridRow({
          columns: 8,
          breakpoints: {
            reference: BreakpointsReference.WindowSize
          } as BreakPoints,
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 8, sm: 8, md: 8, lg: 8 } as GridColColumnOption }) {
            Column() {
              Row() {
                Image(this.mainImage)
                  .margin({ start: LengthMetrics.vp(96), end: LengthMetrics.vp(36) } as LocalizedMargin)
                  .height('60%')
                  .width('20%')
                Scroll() {
                  Column() {
                    Text(this.primaryText)
                      .fontWeight(FontWeight.Medium)
                      .fontSize($r('sys.float.Title_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    Text(this.secondaryText)
                      .fontSize($r('sys.float.Body_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_primary'))
                      .margin({ top: TEXT_MARGIN_TOP_4, bottom: TEXT_MARGIN_BOTTOM_8 } as Padding)
                    Text(this.tertiaryText)
                      .fontSize($r('sys.float.Caption_M'))
                      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                      .margin({ bottom: TEXT_MARGIN_BOTTOM_24 } as Padding)
                  }
                  .width('42%')
                  .alignItems(HorizontalAlign.Start)
                  .margin({ end: LengthMetrics.vp(96) } as LocalizedMargin)
                }.scrollBar(BarState.On)
                .nestedScroll({
                  scrollForward: NestedScrollMode.SELF_FIRST,
                  scrollBackward: NestedScrollMode.SELF_FIRST,
                })
              }
              .backgroundColor(this.imageBackgroundColor)
              .height('34%')
              .width('100%')

              Column() {
                this.container()
              }
              .width('100%')
              .height('66%')
            }
          }
        }
      } else if (this.areaWidth > 840) {
        GridRow({
          columns: 12,
          breakpoints: {
            reference: BreakpointsReference.WindowSize
          } as BreakPoints,
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 4, sm: 4, md: 4, lg: 4 } as GridColColumnOption }) {
            Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center, direction: FlexDirection.Column }) {
              Image(this.mainImage)
                .height('17%')
                .width('34%')
                .margin({ bottom: 36 } as Margin)
              Scroll() {
                Column() {
                  Text(this.primaryText)
                    .textAlign(TextAlign.Center)
                    .fontWeight(FontWeight.Medium)
                    .fontSize($r('sys.float.Title_M'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    .margin({ left: TEXT_MARGIN_LEFT_48, right: TEXT_MARGIN_RIGHT_48 } as Margin)
                  Text(this.secondaryText)
                    .textAlign(TextAlign.Center)
                    .fontSize($r('sys.float.Body_M'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    .margin({
                      top: TEXT_MARGIN_TOP_4,
                      bottom: TEXT_MARGIN_BOTTOM_8,
                      left: TEXT_MARGIN_LEFT_48,
                      right: TEXT_MARGIN_RIGHT_48
                    } as Margin)
                  Text(this.tertiaryText)
                    .textAlign(TextAlign.Center)
                    .fontSize($r('sys.float.Caption_M'))
                    .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                    .margin({
                      left: TEXT_MARGIN_LEFT_48,
                      right: TEXT_MARGIN_RIGHT_48,
                      bottom: TEXT_MARGIN_BOTTOM_24
                    } as Margin)
                }.alignItems(HorizontalAlign.Center)
                .margin({
                  left: $r('sys.float.ohos_id_max_padding_start'),
                  right: $r('sys.float.ohos_id_max_padding_end')
                } as Margin)
              }.scrollBar(BarState.On)
              .nestedScroll({
                scrollForward: NestedScrollMode.SELF_FIRST,
                scrollBackward: NestedScrollMode.SELF_FIRST,
              })
            }
            .width('100%')
            .height('100%')
            .backgroundColor(this.imageBackgroundColor)
          }
          .height('100%')

          GridCol({ span: { xs: 8, sm: 8, md: 8, lg: 8 } as GridColColumnOption }) {
            this.container()
          }
        }.width('100%')
      }
    }
    .onAreaChange((oldValue: Area, newValue: Area) => {
      console.info(`Ace: on area change, oldValue is ${JSON.stringify(oldValue)} value is ${JSON.stringify(newValue)}`);
      this.sizeValue = JSON.stringify(newValue);
      this.areaWidth = parseInt(newValue.width.toString(), 0);
      console.info(`pingAce: newWidth: ${this.areaWidth}, newHeight: ${parseInt(newValue.height.toString(), 0)}`);
    })
  }
}