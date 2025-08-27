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

/**
 * This demo demonstrates how to use List component in ArkTS1.2
 * You need create ArkTS1.2 project to run this expample.
 */

import {
  Entry,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  Scroll,
  ListDividerOptions,
  RectResult,
  List,
  ListItem,
  ListItemGroup,
  ForEach,
  ListScroller,
  EdgeEffect,
  GridItem,
  Grid,
  EffectEdge,
  ScrollAlign,
  SwipeActionOptions,
  LengthConstrain,
  ListItemGroupStyle,
  ListItemStyle,
  Color,
  Row,
  ClickEvent,
  SwipeEdgeEffect,
  CustomBuilder,
  Builder,
  SwipeActionItem,
  ScrollState,
  OnScrollCallback,
  OnWillScrollCallback,
  FlexAlign,
  SwipeActionState,
  $$,
  ScrollResult,
  ScrollSource,
  OnScrollVisibleContentChangeCallback,
  VisibleListContentInfo,
  StickyStyle,
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct MyStateSample {
  @State numbers: string[] = new Array<string>();
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);
  @State groupChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);
  private listScroller: ListScroller = new ListScroller();

  aboutToAppear() {
    for (let i = 0; i < 10; i++) {
      this.numbers.push(i.toString());
    }
    this.listChildrenSize.splice(0, 5, [300, 300, 300, 300, 300]);
    this.groupChildrenSize.splice(0, 5, [300, 300, 300, 300, 300]);
    this.listChildrenSize.splice(0, 0, [2000]);
  }

  build() {
    Column() {
      List({ space: 10, initialIndex: 5, scroller: this.listScroller }) {
        ListItemGroup() {
          ForEach(this.numbers, (item: string, index: number) => {
            ListItem() {
              Text(`group: 0, item: ${index}`)
                .height( index < 5 ? 300 : this.listChildrenSize.childDefaultSize)
                .width('90%')
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(Color.Pink)
            }
          }, (item: string) => item)
        }
        .childrenMainSize(this.groupChildrenSize)
        ForEach(this.numbers, (item: string, index: number) => {
          ListItem() {
            Text(`item: ${index + 1}`)
              .height(index < 5 ? 300 : this.listChildrenSize.childDefaultSize)
              .width('90%')
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
          }
        }, (item: string) => item)
      }
      .clip(true)
      .cachedCount(2, false)
      .backgroundColor(Color.Gray)
      .layoutWeight(1)
      .scrollBar(BarState.On)
      .childrenMainSize(this.listChildrenSize)
      .alignListItem(ListItemAlign.Center)
      Button('scrollTo (0, 300)')
        .width('100%')
        .height('20%')
        .onClick((e: ClickEvent) => {
          // 300: 跳转到group item 1顶部与List顶部平齐的位置。
          // 如果不设置childrenMainSize，item高度不一致时scrollTo会不准确。
          this.listScroller.scrollTo({xOffset: 0, yOffset: 300})
        })
    }
  }
}