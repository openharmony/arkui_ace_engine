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
struct SwipeActionTest {
  @State selectedFlag: boolean = false;
  @State numbers: Array<string> = new Array<string>();
  @State enterEndDeleteAreaString: string = 'not enterEndDeleteArea';
  @State exitEndDeleteAreaString: string = 'not exitEndDeleteArea';
  private listScroller: ListScroller = new ListScroller();
  private message: string = 'changeSelected';

  aboutToAppear()
  {
    for (let i = 0; i < 10; i++) {
      this.numbers.push(i.toString())
    }
  }

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(10)
  }

  @Builder
  itemSwipeNode(text: string) {
    Row() {
      Button('Close')
        .margin('4vp')
        .onClick((e: ClickEvent) => {
          this.listScroller.closeAllSwipeActions({
            onFinish: () => {
              console.info(`listTest closeAllSwipeActions onFinish triggered`)
            }
          });
        })
      Button('CloseWithPrint')
        .margin('4vp')
        .onClick((e: ClickEvent) => {
          this.listScroller.closeAllSwipeActions();
        })
    }.padding('4vp').justifyContent(FlexAlign.SpaceEvenly)
  }

  build() {
    Column(undefined) {
      Text(this.enterEndDeleteAreaString)
        .fontSize(20)
      Text(this.exitEndDeleteAreaString)
        .fontSize(20)
      List({ space: 10, initialIndex: 0, scroller: this.listScroller }) {
        ForEach(this.numbers, (day: string, index: number) => {
          ListItem() {
            Text(day)
              .fontSize(20)
              .backgroundColor("#fff3bef3")
              .height(100)
              .width('100%')
              .borderRadius(20)
          }
          .swipeAction({
            start: () => {
              this.itemSwipeNode(`item: ${index} SwipeNode`)
            } as CustomBuilder,
            end: {
              builder: () => {
                this.itemSwipeNode(`item: ${index} SwipeNode`)
              } as CustomBuilder,
              onAction: () => {
                console.info(`listTest onAction triggered`)
              },
              actionAreaDistance: 56,
              onEnterActionArea: () => {
                this.enterEndDeleteAreaString = 'enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
              },
              onExitActionArea: () => {
                this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'exitEndDeleteArea';
              },
              onStateChange: (state: SwipeActionState) => {
                console.info(`listTest onStateChange state: ${state}`)
              }
            } as SwipeActionItem,
            edgeEffect: SwipeEdgeEffect.None,
            onOffsetChange: (offset: number) => {
              console.info(`listTest onOffsetChange offset: ${offset}`)
            }
          } as SwipeActionOptions)
        })
      }
      .height(600)
      .width(400)
      .backgroundColor(Color.Gray)
      .chainAnimation(true)
      .enableScrollInteraction(true)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.END | EffectEdge.START })
    }
  }
}