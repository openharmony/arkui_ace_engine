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
  ListItemGroupArea,
  ScrollDirection,
  StickyStyle,
  Scroll,
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct MyStateSample {
  @State smooth: boolean = false;
  @State numbers: Array<string> = new Array<string>();
  private listScroller: ListScroller = new ListScroller();

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
      Scroll() {
        Row() {
          Button('scrollToItemInGroup(1, 2, ScrollAlign.AUTO)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToItemInGroup(1, 2, this.smooth, ScrollAlign.AUTO)
            })
          Button('scrollToItemInGroup(1, 2, ScrollAlign.START)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToItemInGroup(1, 2, this.smooth, ScrollAlign.START)
            })
          Button('scrollToItemInGroup(1, 9, ScrollAlign.CENTER)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToItemInGroup(1, 9, this.smooth, ScrollAlign.CENTER)
            })
          Button('scrollToItemInGroup(1, 9, ScrollAlign.END)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToItemInGroup(1, 9, this.smooth, ScrollAlign.END)
            })
        }
      }
      .scrollable(ScrollDirection.Horizontal)
      Scroll() {
        Row() {
          Button('scrollToIndex(5, ScrollAlign.AUTO)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToIndex(5, this.smooth, ScrollAlign.AUTO)
            })
          Button('scrollToIndex(5, ScrollAlign.START)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToIndex(5, this.smooth, ScrollAlign.START)
            })
          Button('scrollToIndex(5, ScrollAlign.CENTER)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToIndex(5, this.smooth, ScrollAlign.CENTER)
            })
          Button('scrollToIndex(5, ScrollAlign.END)')
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.listScroller.scrollToIndex(5, this.smooth, ScrollAlign.END)
            })
        }
      }
      .scrollable(ScrollDirection.Horizontal)
      Scroll() {
        Row() {
          Button(`smooth: ${this.smooth}`)
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              this.smooth = this.smooth === true ? false : true;
            })
          Button(`getItemRect(1)`)
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              let tmp = this.listScroller.getItemRect(1);
              console.info(`listTest getItemRect x: ${tmp.x}, y: ${tmp.y}, width: ${tmp.width}, height: ${tmp.height}`)
            })
          Button(`getItemRectInGroup(0, 4)`)
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              let tmp = this.listScroller.getItemRectInGroup(0, 4);
              console.info(`listTest getItemRectInGroup` +
                `x: ${tmp.x}, y: ${tmp.y}, width: ${tmp.width}, height: ${tmp.height}`)
            })
          Button(`getVisibleListContentInfo(100, 100)`)
            .fontSize(20)
            .onClick((e: ClickEvent) => {
              let tmp: VisibleListContentInfo = this.listScroller.getVisibleListContentInfo(100, 100);
              console.info(`listTest getItemRectInGroup` +
                `index: ${tmp.index}, itemGroupArea: ${tmp.itemGroupArea}, itemIndexInGroup: ${tmp.itemIndexInGroup}`)
            })
        }
      }
      .scrollable(ScrollDirection.Horizontal)
      List({ space: 10, initialIndex: 11, scroller: this.listScroller }) {
        ForEach(this.numbers, (day: string, index: number) => {
          ListItemGroup({
            style: ListItemGroupStyle.CARD,
            header: () => {
              this.itemHead('Header')
            } as CustomBuilder,
            footer: () => {
              this.itemHead('Footer')
            } as CustomBuilder
          }) {
            ForEach(this.numbers, (innerDay: string, innerIndex: number) => {
              ListItem({ style: ListItemStyle.CARD }) {
                Text(`group: ${index}, item: ${innerIndex}`)
                  .fontSize(20)
                  .backgroundColor("#fff3bef3")
              }
            })
          }
          .divider({
            strokeWidth: 2,
            color: "#ff000000",
            startMargin: 20,
            endMargin: 20
          } as ListDividerOptions)
        })
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
      .sticky(StickyStyle.BOTH)
      .enableScrollInteraction(true)
      .multiSelectable(true)
      .lanes({ minLength: 150, maxLength: 300 } as LengthConstrain, 100)
      .stackFromEnd(true)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.END | EffectEdge.START })
      .divider({ strokeWidth: 2 } as ListDividerOptions)
    }
  }
}