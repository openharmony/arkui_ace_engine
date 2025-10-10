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
'use static'

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
  @State selectedFlag: boolean = false;
  @State numbers: Array<string> = new Array<string>();
  private listScroller: ListScroller = new ListScroller();
  private message: string = 'changeSelected';

  aboutToAppear()
  {
    for (let i = 0; i < 10; i++) {
      this.numbers.push(i.toString())
    }
  }

  build() {
    Column(undefined) {
      Text(`selected: ${this.selectedFlag}`)
        .fontSize(20)
      Button(this.message)
        .backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          this.selectedFlag = this.selectedFlag === true ? false : true
        })
      List({ space: 10, initialIndex: 11, scroller: this.listScroller }) {
        ForEach(this.numbers, (day: string, index: number) => {
          ListItem() {
            Text(day)
              .fontSize(20)
              .backgroundColor("#fff3bef3")
              .height(100)
              .width('100%')
              .borderRadius(20)
          }
          .selectable(true)
          .selected($$(this.selectedFlag))
          .onSelect((isSelected: boolean) => {
            console.info(`listTest item: ${index} isSelected: ${this.selectedFlag}`)
          })
        })
      }
      .height(600)
      .width(400)
      .backgroundColor(Color.Gray)
      .multiSelectable(true)
    }
  }
}