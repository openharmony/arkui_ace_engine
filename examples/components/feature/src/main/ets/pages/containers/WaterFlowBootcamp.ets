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

import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import { Drawer, RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';


@Component
export struct WaterFlowBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = false;
  @State enableFadingEdgeLengthValue: boolean = false;
  @State fadingEdgeLengthValue: number = 32;
  @State enableFadingEdgeLengthUnit: boolean = false;
  @State fadingEdgeLengthUnit: LengthUnit = LengthUnit.VP;
  @State enableLayoutDirection: boolean = false;
  @State layoutDirection: FlexDirection = FlexDirection.Column;
  @State enableLayoutMode: boolean = false;
  @State layoutMode: WaterFlowLayoutMode = WaterFlowLayoutMode.ALWAYS_TOP_DOWN;
  @State enableColumnsTemplate: boolean = false;
  @State columnsTemplate: string = '1fr';
  @State enableRowsTemplate: boolean = false;
  @State rowsTemplate: string = '1fr';
  @State enableItemConstraintSizeMinWidth: boolean = false;
  @State itemConstraintSizeMinWidth: Length = 0;
  @State enableItemConstraintSizeMaxWidth: boolean = false;
  @State itemConstraintSizeMaxWidth: Length = '100%';
  @State enableItemConstraintSizeMinHeight: boolean = false;
  @State itemConstraintSizeMinHeight: Length = 0;
  @State enableItemConstraintSizeMaxHeight: boolean = false;
  @State itemConstraintSizeMaxHeight: Length = '100%';
  @State enableColumnsGap: boolean = false;
  @State columnsGap: Length = 0;
  @State enableRowsGap: boolean = false;
  @State rowsGap: Length = 0;
  @State enableEnableScrollInteraction: boolean = false;
  @State enableScrollInteraction: boolean = true;
  @State enableNestedScrollScrollForward: boolean = false;
  @State nestedScrollScrollForward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableNestedScrollScrollBackward: boolean = false;
  @State nestedScrollScrollBackward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableFriction: boolean = false;
  @State friction: number = 0.75;
  @State enableCachedCount: boolean = false;
  @State cachedCount: number = 1;
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

  @State totalCount: number = 30;
  scroller: Scroller = new Scroller();
  private listScroller: ListScroller = new ListScroller()

  getElements() {
    return Array.from({ length: this.totalCount }, (_: ESObject, index: number) => `${index}`);
  }

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
    List({scroller: this.listScroller}) {
      ListItem() {
        Text('1').width('90%').textAlign(TextAlign.Center)
      }
      .height(200).backgroundColor(Color.Green).margin(10)

      ListItem() {
        Text('2').width('90%').textAlign(TextAlign.Center)
      }
      .height(200).backgroundColor(Color.Green).margin(10)

      ListItem() {
        WaterFlow({
          scroller: this.scroller,
          layoutMode: useEnabled(this.enableLayoutMode, this.layoutMode)
        }) {
          ForEach(this.getElements(), (item: number) => {
            FlowItem() {
            }
            .width(
              (FlexDirection.Row === this.layoutDirection || FlexDirection.RowReverse === this.layoutDirection)
                ? (item % 2 ? '50%' : '30%') : '100%'
            )
            .height(
              (FlexDirection.Column === this.layoutDirection || FlexDirection.ColumnReverse === this.layoutDirection)
                ? (item % 2 ? 80 : 50) : 80
            )
            .margin({ bottom: 20 })
            .backgroundColor('#510A59F7')
            .borderRadius(12)
          }, (item: string) => item)
        }
        .layoutDirection(useEnabled(this.enableLayoutDirection, this.layoutDirection))
        .columnsTemplate(useEnabled(this.enableColumnsTemplate, this.columnsTemplate))
        .rowsTemplate(useEnabled(this.enableRowsTemplate, this.rowsTemplate))
        .itemConstraintSize(
          {
            minWidth: useEnabled(this.enableItemConstraintSizeMinWidth, this.itemConstraintSizeMinWidth),
            maxWidth: useEnabled(this.enableItemConstraintSizeMaxWidth, this.itemConstraintSizeMaxWidth),
            minHeight: useEnabled(this.enableItemConstraintSizeMinHeight, this.itemConstraintSizeMinHeight),
            maxHeight: useEnabled(this.enableItemConstraintSizeMaxHeight, this.itemConstraintSizeMaxHeight),
          }
        )
        .columnsGap(useEnabled(this.enableColumnsGap, this.columnsGap))
        .rowsGap(useEnabled(this.enableRowsGap, this.rowsGap))
        .enableScrollInteraction(useEnabled(this.enableEnableScrollInteraction, this.enableScrollInteraction))
        .nestedScroll({
          scrollForward: useEnabled(this.enableNestedScrollScrollForward, this.nestedScrollScrollForward),
          scrollBackward: useEnabled(this.enableNestedScrollScrollBackward, this.nestedScrollScrollBackward)
        })
        .friction(useEnabled(this.enableFriction, this.friction))
        .cachedCount(useEnabled(this.enableCachedCount, this.cachedCount))
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
        .fadingEdge(
          useEnabled(this.enableFadingEdge, this.fadingEdge),
          useEnabled<FadingEdgeOptions>(this.fadingEdge, {
            fadingEdgeLength: new LengthMetrics(this.fadingEdgeLengthValue, this.fadingEdgeLengthUnit)
          })
        )
      }
      .height(400)

      ListItem() {
        Text('4').width('90%').textAlign(TextAlign.Center)
      }
      .height(200).backgroundColor(Color.Green).margin(10)

      ListItem() {
        Text('5').width('90%').textAlign(TextAlign.Center)
      }
      .height(200).backgroundColor(Color.Green).margin(10)
    }
    .height('80%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'layoutMode',
          isEnabled: $enableLayoutMode,
          value: $layoutMode,
          dataSource: [
            { label: 'ALWAYS_TOP_DOWN', value: WaterFlowLayoutMode.ALWAYS_TOP_DOWN },
            { label: 'SLIDING_WINDOW', value: WaterFlowLayoutMode.SLIDING_WINDOW }
          ]
        })

        RadioBlock({
          title: 'layoutDirection',
          isEnabled: $enableLayoutDirection,
          value: $layoutDirection,
          dataSource: [
            { label: 'Column', value: FlexDirection.Column },
            { label: 'ColumnReverse', value: FlexDirection.ColumnReverse },
            { label: 'Row', value: FlexDirection.Row },
            { label: 'RowReverse', value: FlexDirection.RowReverse }
          ]
        })

        if (FlexDirection.Column === this.layoutDirection || FlexDirection.ColumnReverse === this.layoutDirection) {
          RadioBlock({
            title: 'columnsTemplate',
            isEnabled: $enableColumnsTemplate,
            value: $columnsTemplate,
            dataSource: [
              { label: '1fr', value: '1fr' },
              { label: '1fr 1fr', value: '1fr 1fr' },
              { label: '1fr 1fr 1fr', value: '1fr 1fr 1fr' },
              { label: '1fr 1fr 2fr', value: '1fr 1fr 2fr' },
              { label: '1fr 1fr 1fr 1fr', value: '1fr 1fr 1fr 1fr' },
              { label: '1fr 1fr 1fr 1fr 1fr', value: '1fr 1fr 1fr 1fr 1fr' }
            ]
          })
        } else if (FlexDirection.Row === this.layoutDirection || FlexDirection.RowReverse === this.layoutDirection) {
          RadioBlock({
            title: 'rowsTemplate',
            isEnabled: $enableRowsTemplate,
            value: $rowsTemplate,
            dataSource: [
              { label: '1fr', value: '1fr' },
              { label: '1fr 1fr', value: '1fr 1fr' },
              { label: '1fr 1fr 1fr', value: '1fr 1fr 1fr' },
              { label: '1fr 1fr 2fr', value: '1fr 1fr 2fr' },
              { label: '1fr 1fr 1fr 1fr', value: '1fr 1fr 1fr 1fr' },
              { label: '1fr 1fr 1fr 1fr 1fr', value: '1fr 1fr 1fr 1fr 1fr' }
            ]
          })
        }

        SliderBlock({
          title: 'itemConstraintSize.minWidth',
          isEnabled: $enableItemConstraintSizeMinWidth,
          value: $itemConstraintSizeMinWidth,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'itemConstraintSize.maxWidth',
          isEnabled: $enableItemConstraintSizeMaxWidth,
          value: $itemConstraintSizeMaxWidth,
          min: 0,
          max: 600
        })

        SliderBlock({
          title: 'itemConstraintSize.minHeight',
          isEnabled: $enableItemConstraintSizeMinHeight,
          value: $itemConstraintSizeMinHeight,
          min: 0,
          max: 500
        })

        SliderBlock({
          title: 'itemConstraintSize.maxHeight',
          isEnabled: $enableItemConstraintSizeMaxHeight,
          value: $itemConstraintSizeMaxHeight,
          min: 0,
          max: 600
        })

        SliderBlock({
          title: 'columnsGap',
          isEnabled: $enableColumnsGap,
          value: $columnsGap,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: 'rowsGap',
          isEnabled: $enableRowsGap,
          value: $rowsGap,
          min: 0,
          max: 20
        })

        RadioBlock({
          title: 'enableScrollInteraction',
          isEnabled: $enableEnableScrollInteraction,
          value: $enableScrollInteraction,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'nestedScroll.scrollForward',
          isEnabled: $enableNestedScrollScrollForward,
          value: $nestedScrollScrollForward,
          dataSource: [
            { label: 'SELF_ONLY', value: NestedScrollMode.SELF_ONLY },
            { label: 'SELF_FIRST', value: NestedScrollMode.SELF_FIRST },
            { label: 'PARENT_FIRST', value: NestedScrollMode.PARENT_FIRST },
            { label: 'PARALLEL', value: NestedScrollMode.PARALLEL }
          ]
        })

        RadioBlock({
          title: 'nestedScroll.scrollBackward',
          isEnabled: $enableNestedScrollScrollBackward,
          value: $nestedScrollScrollBackward,
          dataSource: [
            { label: 'SELF_ONLY', value: NestedScrollMode.SELF_ONLY },
            { label: 'SELF_FIRST', value: NestedScrollMode.SELF_FIRST },
            { label: 'PARENT_FIRST', value: NestedScrollMode.PARENT_FIRST },
            { label: 'PARALLEL', value: NestedScrollMode.PARALLEL }
          ]
        })

        SliderBlock({
          title: 'friction',
          isEnabled: $enableFriction,
          value: $friction,
          min: 0,
          max: 1,
          step: 0.05
        })

        SliderBlock({
          title: 'cachedCount',
          isEnabled: $enableCachedCount,
          value: $cachedCount,
          min: 0,
          max: 30
        })

        RadioBlock({
          title: 'fadingEdge',
          isEnabled: $enableFadingEdge,
          value: $fadingEdge,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        if (this.fadingEdge) {
          SliderBlock({
            title: 'fadingEdge.length',
            isEnabled: $enableFadingEdgeLengthValue,
            value: $fadingEdgeLengthValue,
            min: 0,
            max: 500
          })
          RadioBlock({
            title: 'fadingEdge.length.unit',
            isEnabled: $enableFadingEdgeLengthUnit,
            value: $fadingEdgeLengthUnit,
            dataSource: [
              { label: 'px', value: LengthUnit.PX },
              { label: 'vp', value: LengthUnit.VP },
              { label: 'fp', value: LengthUnit.FP },
              { label: 'percent', value: LengthUnit.PERCENT },
              { label: 'lpx', value: LengthUnit.LPX }
            ]
          })
        }

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
struct WaterFlowBootcampPreviewer {
  build() {
    WaterFlowBootcamp({
      title: '瀑布流容器/WaterFlow'
    })
  }
}