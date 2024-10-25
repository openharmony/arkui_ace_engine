/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled } from 'common';
import { LengthMetrics } from '@kit.ArkUI';

@Component
export struct ScrollBarBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableScrollBarState: boolean = true;
  @State scrollBarState: BarState = BarState.Off;
  @State enableScrollBarBarState: boolean = true;
  @State scrollBarBarState: BarState = BarState.Auto;
  @State enableScrollBarCustomItem: boolean = false;
  @State scrollBarCustomItemType: boolean = false;
  private scroller: Scroller = new Scroller();
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Scroll(this.scroller) {
        Flex({
          direction: FlexDirection.Column,
          space: { main: LengthMetrics.vp(5) }
        }) {
          ForEach(this.arr, (item: number) => {
            Row() {
              Text(item.toString())
                .backgroundColor(Color.White)
                .borderRadius(10)
                .width('95%')
                .height(60)
            }
          }, (item:number) => item.toString())
        }
      }
      .width('95%')
      .scrollBar(BarState.Off)
      .scrollable(ScrollDirection.Vertical)
      ScrollBar({
        scroller: this.scroller,
        direction: ScrollBarDirection.Vertical,
        state: useEnabled(this.enableScrollBarBarState, this.scrollBarBarState)
      }) {
        if (this.enableScrollBarCustomItem) {
          if (this.scrollBarCustomItemType) {
            Text('---')
              .width(10)
              .height(80)
              .borderRadius(10)
              .backgroundColor('#ff42c2ff')
          } else {
            Image($r('app.media.background'))
              .width(10)
              .height(80)
              .borderRadius(10)
              .draggable(false)
          }
        }
      }
      .width('5%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '是否使用自定义item',
          isEnabled: this.enableScrollBarCustomItem,
          value: this.scrollBarCustomItemType,
          dataSource: [
            { label: '文本', value: true },
            { label: '图片', value: false },
          ]
        })
        RadioBlock({
          title: '滚动条状态',
          isEnabled: this.enableScrollBarBarState,
          value: this.scrollBarBarState,
          dataSource: [
            { label: '按需显示(触摸时显示，2s后消失)', value: BarState.Auto },
            { label: '常驻显示', value: BarState.On },
            { label: '不显示', value: BarState.Off },
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct ScrollBarBootcampPreviewer {
  build() {
    ScrollBarBootcamp({
      title: '滚动条/scrollbar'
    })
  }
}