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

import { LengthMetrics } from '@ohos.arkui.node';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, ColorBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct FlexBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFlexDirection: boolean = false;
  @State flexDirection: FlexDirection = FlexDirection.Row;
  @State enableWrap: boolean = false;
  @State wrap: FlexWrap = FlexWrap.NoWrap;
  @State enableJustifyContent: boolean = false;
  @State justifyContent: FlexAlign = FlexAlign.Start;
  @State enableAlignItems: boolean = false;
  @State alignItems: ItemAlign = ItemAlign.Start;
  @State enableAlignContent: boolean = false;
  @State alignContent: FlexAlign = FlexAlign.Start;
  @State enableSpaceMainLengthMetricsPx: boolean = false;
  @State spaceMainLengthMetricsPx: number = 0;
  @State enableSpaceCrossLengthMetricsPx: boolean = false;
  @State spaceCrossLengthMetricsPx: number = 0;
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
  @State enableFlexComp: boolean = false;

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
      Flex({
        direction: useEnabled(this.enableFlexDirection, this.flexDirection),
        wrap: useEnabled(this.enableWrap, this.wrap),
        justifyContent: useEnabled(this.enableJustifyContent, this.justifyContent),
        alignItems: useEnabled(this.enableAlignItems, this.alignItems),
        alignContent: useEnabled(this.enableAlignContent, this.alignContent),
        space: {
          main: useEnabled(this.enableSpaceMainLengthMetricsPx, LengthMetrics.px(this.spaceMainLengthMetricsPx)),
          cross: useEnabled(this.enableSpaceCrossLengthMetricsPx, LengthMetrics.px(this.spaceCrossLengthMetricsPx))
        }
      }) {
        Text('1').width('30%').height(50).backgroundColor(0xF5DEB3)
          .flexBasis(useEnabled(this.enableFlexComp, 50))
          .flexGrow(useEnabled(this.enableFlexComp, 0))
          .flexShrink(useEnabled(this.enableFlexComp, 1))
          .alignSelf(useEnabled(this.enableFlexComp, ItemAlign.Auto))
          .onClick(() => {
            this.enableFlexComp = !this.enableFlexComp
          })
        Text('2').width('30%').height(50).backgroundColor(0xD2B48C)
        Text('3').width('30%').height(50).backgroundColor(0xF5DEB3)
        Text('4').width('30%').height(50).backgroundColor(0xD2B48C)
        Text('5').width('30%').height(50).backgroundColor(0xF5DEB3)
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
    }.width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'direction',
          isEnabled: $enableFlexDirection,
          value: $flexDirection,
          dataSource: [
            { label: 'Row', value: FlexDirection.Row },
            { label: 'RowReverse', value: FlexDirection.RowReverse },
            { label: 'Column', value: FlexDirection.Column },
            { label: 'ColumnReverse', value: FlexDirection.ColumnReverse }
          ]
        })

        RadioBlock({
          title: 'wrap',
          isEnabled: $enableWrap,
          value: $wrap,
          dataSource: [
            { label: 'Wrap', value: FlexWrap.Wrap },
            { label: 'NoWrap', value: FlexWrap.NoWrap },
            { label: 'WrapReverse', value: FlexWrap.WrapReverse }
          ]
        })

        RadioBlock({
          title: 'justifyContent',
          isEnabled: $enableJustifyContent,
          value: $justifyContent,
          dataSource: [
            { label: 'Start', value: FlexAlign.Start },
            { label: 'Center', value: FlexAlign.Center },
            { label: 'End', value: FlexAlign.End },
            { label: 'SpaceBetween', value: FlexAlign.SpaceBetween },
            { label: 'SpaceAround', value: FlexAlign.SpaceAround },
            { label: 'SpaceEvenly', value: FlexAlign.SpaceEvenly }
          ]
        })

        RadioBlock({
          title: 'alignItems',
          isEnabled: $enableAlignItems,
          value: $alignItems,
          dataSource: [
            { label: 'Auto', value: ItemAlign.Auto },
            { label: 'Start', value: ItemAlign.Start },
            { label: 'Center', value: ItemAlign.Center },
            { label: 'End', value: ItemAlign.End },
            { label: 'Stretch', value: ItemAlign.Stretch },
            { label: 'Baseline', value: ItemAlign.Baseline }
          ]
        })

        RadioBlock({
          title: 'alignContent',
          isEnabled: $enableAlignContent,
          value: $alignContent,
          dataSource: [
            { label: 'Start', value: FlexAlign.Start },
            { label: 'Center', value: FlexAlign.Center },
            { label: 'End', value: FlexAlign.End },
            { label: 'SpaceBetween', value: FlexAlign.SpaceBetween },
            { label: 'SpaceAround', value: FlexAlign.SpaceAround },
            { label: 'SpaceEvenly', value: FlexAlign.SpaceEvenly }
          ]
        })

        SliderBlock({
          title: 'space.main.LengthMetrics.px',
          isEnabled: $enableSpaceMainLengthMetricsPx,
          value: $spaceMainLengthMetricsPx,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'space.cross.LengthMetrics.px',
          isEnabled: $enableSpaceCrossLengthMetricsPx,
          value: $spaceCrossLengthMetricsPx,
          min: 0,
          max: 100
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
      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct FlexBootcampPreviewer {
  build() {
    FlexBootcamp({
      title: '弹性布局/Flex'
    })
  }
}