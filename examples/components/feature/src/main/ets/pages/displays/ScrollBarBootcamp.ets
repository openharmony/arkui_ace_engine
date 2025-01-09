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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';
import { LengthMetrics } from '@kit.ArkUI';

@Component
export struct ScrollBarBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableScrollBarDirection: boolean = false;
  @State scrollBarDirection: ScrollBarDirection = ScrollBarDirection.Vertical;
  @State enableScrollBarState: boolean = false;
  @State scrollBarState: BarState = BarState.Off;
  @State enableScrollBarBarState: boolean = false;
  @State scrollBarBarState: BarState = BarState.Auto;
  @State enableScrollBarCustomItem: boolean = false;
  @State scrollBarCustomItemType: boolean = false;
  @State enableCompWidth: boolean = false;
  @State compWidth: Length = 'auto';
  @State enableCompHeight: boolean = false;
  @State compHeight: Length = 'auto';
  @State enableCompPadding: boolean = false;
  @State compPadding: number = 0;
  @State enableCompMargin: boolean = false;
  @State compMargin: number = 0;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = '#ff000000';
  @State enableCompBorderWidth: boolean = false;
  @State compBorderWidth: number = 0;
  @State enableCompBorderColor: boolean = false;
  @State compBorderColor: ResourceColor = Color.Black;
  @State enableCompBorderRadius: boolean = false;
  @State compBorderRadius: number = 0;
  @State enableCompBorderStyle: boolean = false;
  @State compBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableCompFlexBasis: boolean = false;
  @State compFlexBasis: number | string = 'auto';
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableCompClip: boolean = false;
  @State compClip: boolean = false;

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
        direction: useEnabled(this.enableScrollBarDirection, this.scrollBarDirection),
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
      .width(useEnabled(this.enableCompWidth, this.compWidth))
      .height(useEnabled(this.enableCompHeight, this.compHeight))
      .padding(useEnabled(this.enableCompPadding, this.compPadding))
      .margin(useEnabled(this.enableCompMargin, this.compMargin))
      .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
      .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
      .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
      .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
      .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
      .flexBasis(useEnabled(this.enableCompFlexBasis, this.compFlexBasis))
      .opacity(useEnabled(this.enableCompOpacity, this.compOpacity))
      .visibility(useEnabled(this.enableCompVisibility, this.compVisibility))
      .direction(useEnabled(this.enableCompDirection, this.compDirection))
      .clip(useEnabled(this.enableCompClip, this.compClip))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'direction',
          isEnabled: $enableScrollBarDirection,
          value: $scrollBarDirection,
          dataSource: [
            { label: 'Vertical', value: ScrollBarDirection.Vertical },
            { label: 'Horizontal', value: ScrollBarDirection.Horizontal }
          ]
        })

        RadioBlock({
          title: 'scrollBarCustomItemType',
          isEnabled: $enableScrollBarCustomItem,
          value: $scrollBarCustomItemType,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'state',
          isEnabled: $enableScrollBarBarState,
          value: $scrollBarBarState,
          dataSource: [
            { label: 'Auto', value: BarState.Auto },
            { label: 'On', value: BarState.On },
            { label: 'Off', value: BarState.Off },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 10,
          max: 300
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 50,
          max: 800
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableCompPadding,
          value: $compPadding,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableCompMargin,
          value: $compMargin,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableCompBorderWidth,
          value: $compBorderWidth,
          min: 0,
          max: 20
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableCompBorderColor,
          color: $compBorderColor
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableCompBorderRadius,
          value: $compBorderRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableCompBorderStyle,
          value: $compBorderStyle,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'flexBasis',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 10,
          max: 200
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableCompOpacity,
          value: $compOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableCompVisibility,
          value: $compVisibility,
          dataSource: [
            { label: 'None', value: Visibility.None },
            { label: 'Hidden', value: Visibility.Hidden },
            { label: 'Visible', value: Visibility.Visible }
          ]
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl }
          ]
        })

        RadioBlock({
          title: 'clip',
          isEnabled: $enableCompClip,
          value: $compClip,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
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