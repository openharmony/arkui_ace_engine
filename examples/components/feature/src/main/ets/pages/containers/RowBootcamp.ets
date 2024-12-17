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
export struct RowBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableSpace: boolean = false;
  @State space: number = 0;
  @State enableAlignItems: boolean = false;
  @State alignItems: VerticalAlign = VerticalAlign.Center;
  @State enableJustifyContent: boolean = false;
  @State justifyContent: FlexAlign = FlexAlign.Start;
  @State enableIsReversed: boolean = false;
  @State isReversed: boolean = true;
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
      Row({
        space: useEnabled(this.enableSpace, this.space)
      }) {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('20%').height(50).backgroundColor(0x00FFFF)
        Row().width('10%').height(50).backgroundColor(0xAFEEEE)
        Row().width('20%').height(50).backgroundColor(0x00FFFF)
      }
      .alignItems(useEnabled(this.enableAlignItems, this.alignItems))
      .justifyContent(useEnabled(this.enableJustifyContent, this.justifyContent))
      .reverse(useEnabled(this.enableIsReversed, this.isReversed))
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
    }.width('100%').padding({ top: 5 })
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'space',
          isEnabled: $enableSpace,
          value: $space,
          min: 0,
          max: 10
        })

        RadioBlock({
          title: 'alignItems',
          isEnabled: $enableAlignItems,
          value: $alignItems,
          dataSource: [
            { label: 'Top', value: VerticalAlign.Top },
            { label: 'Center', value: VerticalAlign.Center },
            { label: 'Bottom', value: VerticalAlign.Bottom }
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
          title: 'isReversed',
          isEnabled: $enableIsReversed,
          value: $isReversed,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
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
      }
      .width('100%')
    }
    .align(Alignment.Top)
    .height('50%')
  }
}

@Preview
@Component
struct RowBootcampPreviewer {
  build() {
    RowBootcamp({
      title: '横向布局/Row'
    })
  }
}