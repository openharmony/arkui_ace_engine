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
export struct RelativeContainerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableGuideLineDirection: boolean = false;
  @State guideLineDirection: Axis = Axis.Vertical;
  @State enableGuideLinePositionStart: boolean = false;
  @State guideLinePositionStart: number = 0;
  @State enableGuideLinePositionEnd: boolean = false;
  @State guideLinePositionEnd: number = 0;
  @State enableBarrierDirection: boolean = false;
  @State barrierDirection: BarrierDirection = BarrierDirection.LEFT;
  @State enableBarrierLocalizedDirection: boolean = false;
  @State barrierLocalizedDirection: LocalizedBarrierDirection = LocalizedBarrierDirection.START;
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
    Row() {
      RelativeContainer() {
        Row().width(40).height(100)
        .backgroundColor('#33FF00')
        .alignRules({
          left: {anchor: 'guideline1', align: HorizontalAlign.End}
        })
        .id('row1')

        Row().width(100).height(40)
        .backgroundColor('#FF3300')
        .alignRules({
          top: {anchor: 'guideline1', align: VerticalAlign.Top}
        })
        .id('row2')

        Row(){Text('row3')}.justifyContent(FlexAlign.Center)
        .width(75).height(75)
        .backgroundColor('#FFCC00')
        .alignRules({
          left: {anchor: 'barrier1-1', align: HorizontalAlign.End}
        })
        .id('row3')

        Row(){Text('row4')}.justifyContent(FlexAlign.Center)
        .width(50).height(50)
        .backgroundColor('#FF9966')
        .alignRules({
          top: {anchor: 'barrier1-1', align: VerticalAlign.Bottom}
        })
        .id('row4')
      }
      .guideLine([{
        id: 'guideline1',
        direction: useEnabled(this.enableGuideLineDirection, this.guideLineDirection),
        position: {
          start: useEnabled(this.enableGuideLinePositionStart, this.guideLinePositionStart),
          end: useEnabled(this.enableGuideLinePositionEnd, this.guideLinePositionEnd)
        }
      }])
      .barrier([
        {
          id: 'barrier1-1',
          direction: useEnabled(this.enableBarrierDirection, this.barrierDirection),
          referencedId: ['row1', 'row2']
        },
        {
          id: 'barrier1-2',
          direction: BarrierDirection.BOTTOM,
          referencedId: ['row1', 'row2']
        }
      ])
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

      RelativeContainer() {
        Row().width(40).height(100)
        .backgroundColor('#33FF00')
        .alignRules({
          left: {anchor: 'guideline1', align: HorizontalAlign.End}
        })
        .id('row5')

        Row().width(100).height(40)
        .backgroundColor('#FF3300')
        .alignRules({
          top: {anchor: 'guideline1', align: VerticalAlign.Top}
        })
        .id('row6')

        Row(){Text('row7')}.justifyContent(FlexAlign.Center)
        .width(75).height(75)
        .backgroundColor('#FFCC00')
        .alignRules({
          start: {anchor: 'barrier2-1', align: HorizontalAlign.End}
        })
        .id('row7')

        Row(){Text('row8')}.justifyContent(FlexAlign.Center)
        .width(50).height(50)
        .backgroundColor('#FF9966')
        .alignRules({
          top: {anchor: 'barrier2-1', align: VerticalAlign.Bottom}
        })
        .id('row8')
      }
      .guideLine([{
        id: 'guideline1',
        direction: useEnabled(this.enableGuideLineDirection, this.guideLineDirection),
        position: {
          start: useEnabled(this.enableGuideLinePositionStart, this.guideLinePositionStart),
          end: useEnabled(this.enableGuideLinePositionEnd, this.guideLinePositionEnd)
        }
      }])
      .barrier([
        {
          id: 'barrier2-1',
          localizedDirection: useEnabled(this.enableBarrierLocalizedDirection, this.barrierLocalizedDirection),
          referencedId: ['row5', 'row6']
        },
        {
          id: 'barrier2-2',
          localizedDirection: LocalizedBarrierDirection.BOTTOM,
          referencedId: ['row5', 'row6']
        }
      ])
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
    }
    .height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'guideLine.direction',
          isEnabled: $enableGuideLineDirection,
          value: $guideLineDirection,
          dataSource: [
            { label: 'Vertical', value: Axis.Vertical },
            { label: 'Horizontal', value: Axis.Horizontal }
          ]
        })

        SliderBlock({
          title: 'guideLine.position.start',
          isEnabled: $enableGuideLinePositionStart,
          value: $guideLinePositionStart,
          min: 0,
          max: 120
        })

        SliderBlock({
          title: 'guideLine.position.end',
          isEnabled: $enableGuideLinePositionEnd,
          value: $guideLinePositionEnd,
          min: 0,
          max: 120
        })

        RadioBlock({
          title: 'barrier.direction',
          isEnabled: $enableBarrierDirection,
          value: $barrierDirection,
          dataSource: [
            { label: 'LEFT', value: BarrierDirection.LEFT },
            { label: 'RIGHT', value: BarrierDirection.RIGHT },
            { label: 'TOP', value: BarrierDirection.TOP },
            { label: 'BOTTOM', value: BarrierDirection.BOTTOM }
          ]
        })

        RadioBlock({
          title: 'barrier.localizedDirection',
          isEnabled: $enableBarrierLocalizedDirection,
          value: $barrierLocalizedDirection,
          dataSource: [
            { label: 'START', value: LocalizedBarrierDirection.START },
            { label: 'END', value: LocalizedBarrierDirection.END },
            { label: 'TOP', value: LocalizedBarrierDirection.TOP },
            { label: 'BOTTOM', value: LocalizedBarrierDirection.BOTTOM }
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
struct RelativeContainerBootcampPreviewer {
  build() {
    RelativeContainerBootcamp({
      title: '相对布局/RelativeContainer'
    })
  }
}