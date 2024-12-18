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
import { RadioBlock, ColorBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct GridColBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableSpanXs: boolean = false;
  @State spanXs: number = 1;
  @State enableSpanSm: boolean = false;
  @State spanSm: number = 1;
  @State enableSpanMd: boolean = false;
  @State spanMd: number = 1;
  @State enableSpanLg: boolean = false;
  @State spanLg: number = 1;
  @State enableSpanXl: boolean = false;
  @State spanXl: number = 1;
  @State enableSpanXxl: boolean = false;
  @State spanXxl: number = 1;
  @State enableOffsetXs: boolean = false;
  @State offsetXs: number = 0;
  @State enableOffsetSm: boolean = false;
  @State offsetSm: number = 0;
  @State enableOffsetMd: boolean = false;
  @State offsetMd: number = 0;
  @State enableOffsetLg: boolean = false;
  @State offsetLg: number = 0;
  @State enableOffsetXl: boolean = false;
  @State offsetXl: number = 0;
  @State enableOffsetXxl: boolean = false;
  @State offsetXxl: number = 0;
  @State enableOrderXs: boolean = false;
  @State orderXs: number = 0;
  @State enableOrderSm: boolean = false;
  @State orderSm: number = 0;
  @State enableOrderMd: boolean = false;
  @State orderMd: number = 0;
  @State enableOrderLg: boolean = false;
  @State orderLg: number = 0;
  @State enableOrderXl: boolean = false;
  @State orderXl: number = 0;
  @State enableOrderXxl: boolean = false;
  @State orderXxl: number = 0;
  @State enableGridColOffset: boolean = false;
  @State gridColOffset: number = 0;
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

  @State bgColors: Color[] = [
    Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink, Color.Grey, Color.Blue, Color.Brown
  ]

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
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column({ space: 5 }) {
      GridRow({
        columns: 5,
        gutter: { x: 5, y: 10 },
        breakpoints: {
          value: ['400vp', '600vp', '800vp'],
          reference: BreakpointsReference.WindowSize
        },
        direction: GridRowDirection.Row
      }) {
        GridCol({
          span: { xs: 1, sm: 1, md: 3, lg: 4, xl: 5, xxl: 6 },
          offset: 0,
          order: 1
        }) {
          Row().width('100%').height('30vp')
        }
        .gridColOffset(useEnabled(this.enableGridColOffset, this.gridColOffset))
        .backgroundColor(Color.Green)
        .borderColor(Color.Red)
        .borderWidth(5)
        .borderRadius(10)

        ForEach(this.bgColors, (color: Color) => {
          GridCol({
            span: { xs: 1, sm: 1, md: 3, lg: 4 },
            offset: 0,
            order: 3
          }) {
            Row().width('100%').height('20vp')
          }
          .borderColor(color)
          .borderWidth(2)
        })

        GridCol({
          span: {
            xs: useEnabled(this.enableSpanXs, this.spanXs),
            sm: useEnabled(this.enableSpanSm, this.spanSm),
            md: useEnabled(this.enableSpanMd, this.spanMd),
            lg: useEnabled(this.enableSpanLg, this.spanLg),
            xl: useEnabled(this.enableSpanXl, this.spanXl),
            xxl: useEnabled(this.enableSpanXxl, this.spanXxl)
          },
          offset: {
            xs: useEnabled(this.enableOffsetXs, this.offsetXs),
            sm: useEnabled(this.enableOffsetSm, this.offsetSm),
            md: useEnabled(this.enableOffsetMd, this.offsetMd),
            lg: useEnabled(this.enableOffsetLg, this.offsetLg),
            xl: useEnabled(this.enableOffsetXl, this.offsetXl),
            xxl: useEnabled(this.enableOffsetXxl, this.offsetXxl)
          },
          order: {
            xs: useEnabled(this.enableOrderXs, this.orderXs),
            sm: useEnabled(this.enableOrderSm, this.orderSm),
            md: useEnabled(this.enableOrderMd, this.orderMd),
            lg: useEnabled(this.enableOrderLg, this.orderLg),
            xl: useEnabled(this.enableOrderXl, this.orderXl),
            xxl: useEnabled(this.enableOrderXxl, this.orderXxl)
          },
        }) {
          Row().width('100%').height('20vp')
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
      }.backgroundColor(Color.White)
    }.width('100%').padding({ top: 5 })
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'span.xs',
          isEnabled: $enableSpanXs,
          value: $spanXs,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'span.sm',
          isEnabled: $enableSpanSm,
          value: $spanSm,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'span.md',
          isEnabled: $enableSpanMd,
          value: $spanMd,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'span.lg',
          isEnabled: $enableSpanLg,
          value: $spanLg,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'span.xl',
          isEnabled: $enableSpanXl,
          value: $spanXl,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'span.xxl',
          isEnabled: $enableSpanXxl,
          value: $spanXxl,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'offset.xs',
          isEnabled: $enableOffsetXs,
          value: $offsetXs,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'offset.sm',
          isEnabled: $enableOffsetSm,
          value: $offsetSm,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'offset.md',
          isEnabled: $enableOffsetMd,
          value: $offsetMd,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'offset.lg',
          isEnabled: $enableOffsetLg,
          value: $offsetLg,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'offset.xl',
          isEnabled: $enableOffsetXl,
          value: $offsetXl,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'offset.xxl',
          isEnabled: $enableOffsetXxl,
          value: $offsetXxl,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'order.xs',
          isEnabled: $enableOrderXs,
          value: $orderXs,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'order.sm',
          isEnabled: $enableOrderSm,
          value: $orderSm,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'order.md',
          isEnabled: $enableOrderMd,
          value: $orderMd,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'order.lg',
          isEnabled: $enableOrderLg,
          value: $orderLg,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'order.xl',
          isEnabled: $enableOrderXl,
          value: $orderXl,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'order.xxl',
          isEnabled: $enableOrderXxl,
          value: $orderXxl,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'gridColOffset',
          isEnabled: $enableGridColOffset,
          value: $gridColOffset,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 50,
          max: 400
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
struct GridColBootcampPreviewer {
  build() {
    GridColBootcamp({
      title: '栅格列/GridCol'
    })
  }
}