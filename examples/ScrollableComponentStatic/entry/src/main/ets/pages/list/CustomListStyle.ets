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

import { ComponentCard } from '../../common/Card';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';
import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  Text,
  Stack,
  ScrollBar,
  NavDestination,
  Scroller,
  BarState,
  ListItemAlign,
  Alignment,
  Length,
  ResourceColor
} from '@kit.ArkUI';
import { ListOptions, ListDividerOptions } from '@kit.ArkUI';

@Entry
@Component
export struct CustomListStyle {
  @State egDivider: ListDividerOptions = {
    strokeWidth: 1,
    startMargin: 60,
    endMargin: 10,
    color: '#ffe9f0f0'
  } as ListDividerOptions;

  private listScroller: Scroller = new Scroller();

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.CustomListStyle_titleContentSpacing') }) {
          List({ space: 10 }) {
            ListItem() {
              Text('ListItem One')
            }

            ListItem() {
              Text('ListItem Two')
            }
          }
          .backgroundColor('#FFF1F3F5')
          .alignListItem(ListItemAlign.Center)
        }

        ComponentCard({ title: $r('app.string.CustomListStyle_titleDividerLines') }) {
          List(
            { space: 10 } as ListOptions
          ) {
            ListItem() {
              Text('ListItem One')
            }

            ListItem() {
              Text('ListItem Two')
            }
          }
          .divider(this.egDivider)
          .alignListItem(ListItemAlign.Center)
        }

        ComponentCard({ title: $r('app.string.CustomListStyle_titleScrollbars') }) {
          List(
            { space: 10 }
          ) {
            ListItem() {
              Text('ListItem One')
            }.height(30)

            ListItem() {
              Text('ListItem Two')
            }.height(30)

            ListItem() {
              Text('ListItem Three')
            }.height(30)
          }
          .height(60)
          .scrollBar(BarState.Auto)
          .backgroundColor('#FFF1F3F5')
        }

        ComponentCard({ title: $r('app.string.CustomListStyle_titleExternalScrollbars') }) {

          Stack({ alignContent: Alignment.End }){
            // listScroller initializes the scroller parameter of the List component, binding listScroller with the list.
            List({ scroller: this.listScroller }) {
              ListItem() {
                Text('ListItem One')
              }.height(30)

              ListItem() {
                Text('ListItem Two')
              }.height(30)

              ListItem() {
                Text('ListItem Three')
              }.height(30)
            }
            .scrollBar(BarState.Off)
            .backgroundColor('#FFF1F3F5')

            // listScroller initializes the scroller parameter of the ScrollBar component, binding listScroller with the list.
            ScrollBar({ scroller: this.listScroller})

          }.height(60)

        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.CustomListStyle_title'))
  }
}
