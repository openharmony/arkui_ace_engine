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
      Button('Delete')
        .margin('4vp')
      Button('Set')
        .margin('4vp')
        .onClick((e: ClickEvent) => {
          this.listScroller.closeAllSwipeActions();
        })
    }.padding('4vp').justifyContent(FlexAlign.SpaceEvenly)
  }

  build() {
    Column(undefined) {
      Button('scrollToItemInGroup(1, 2, true, ScrollAlign.AUTO)')
        .fontSize(20)
        .onClick((e: ClickEvent) => {
          this.listScroller.scrollToItemInGroup(1, 2, true, ScrollAlign.AUTO)
        })
      Text(`selected: ${this.selectedFlag}`)
        .fontSize(20)
      Text(this.enterEndDeleteAreaString)
        .fontSize(20)
      Text(this.exitEndDeleteAreaString)
        .fontSize(20)
      Button(this.message)
        .backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          this.selectedFlag = this.selectedFlag === true ? false : true
        })
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
              .selectable(true)
              .selected($$(this.selectedFlag))
              .onSelect((isSelected: boolean) => {
                console.info(`listTest group: ${index}, item: ${innerIndex} isSelected: ${this.selectedFlag}`)
              })
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
      .onScrollStart(() => {
        console.info(`listTest onScrollStart`)
      })
      .onScrollStop(() => {
        console.info(`listTest onScrollStop`)
      })
      .onReachStart(() => {
        console.info(`listTest onReachStart`)
      })
      .onReachEnd(() => {
        console.info(`listTest onReachEnd`)
      })
      .onScrollIndex((start: number, end: number, center: number) => {
        console.info(`listTest onScrollIndex start: ${start}, center: ${center}, end: ${end}`)
      })
      .chainAnimation(true)
      .sticky(StickyStyle.Header)
      .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
        console.info(`listTest onDidScroll offset: ${scrollOffset}, state: ${scrollState}`)
      } as OnScrollCallback)
      .onScrollVisibleContentChange((start: VisibleListContentInfo, end: VisibleListContentInfo) => {
        console.info(`listTest onScrollVisibleContentChange start index: ${start.index}, itemGroupArea: ${start.itemGroupArea}, itemIndexInGroup: ${start.itemIndexInGroup}`)
        console.info(`listTest onScrollVisibleContentChange end index: ${end.index}, itemGroupArea: ${end.itemGroupArea}, itemIndexInGroup: ${end.itemIndexInGroup}`)
      } as OnScrollVisibleContentChangeCallback)
      .enableScrollInteraction(true)
      .multiSelectable(true)
      .lanes({ minLength: 150, maxLength: 300 } as LengthConstrain, 100)
      .stackFromEnd(true)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.END | EffectEdge.START })
      .divider({ strokeWidth: 2 } as ListDividerOptions)

      Text('Hello World').fontSize(20)
    }
  }
}