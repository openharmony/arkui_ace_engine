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
export struct ScrollBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = false;
  @State enableFadingEdgeLengthValue: boolean = false;
  @State fadingEdgeLengthValue: number = 32;
  @State enableFadingEdgeLengthUnit: boolean = false;
  @State fadingEdgeLengthUnit: LengthUnit = LengthUnit.VP;
  @State enableScrollable: boolean = false;
  @State scrollable: ScrollDirection = ScrollDirection.Vertical;
  @State enableScrollBar: boolean = false;
  @State scrollBar: BarState = BarState.Auto;
  @State enableScrollBarColor: boolean = false;
  @State scrollBarColor: Color | number | string = '#182431';
  @State enableScrollBarWidth: boolean = false;
  @State scrollBarWidth: number | string = 4;
  @State enableScrollSnapSnapAlign: boolean = false;
  @State scrollSnapSnapAlign: ScrollSnapAlign = ScrollSnapAlign.NONE;
  @State enableScrollSnapSnapPagination: boolean = false;
  @State scrollSnapSnapPagination: Dimension | Array<Dimension> = 500;
  @State enableScrollSnapEnableSnapToStart: boolean = false;
  @State scrollSnapEnableSnapToStart: boolean = true;
  @State enableScrollSnapEnableSnapToEnd: boolean = false;
  @State scrollSnapEnableSnapToEnd: boolean = true;
  @State enableEdgeEffect: boolean = false;
  @State edgeEffect: EdgeEffect = EdgeEffect.None;
  @State enableEdgeEffectOptionsAlwaysEnabled: boolean = false;
  @State edgeEffectOptionsAlwaysEnabled: boolean = true;
  @State enableEnableScrollInteraction: boolean = false;
  @State enableScrollInteraction: boolean = true;
  @State enableNestedScrollScrollForward: boolean = false;
  @State nestedScrollScrollForward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableNestedScrollScrollBackward: boolean = false;
  @State nestedScrollScrollBackward: NestedScrollMode = NestedScrollMode.SELF_ONLY;
  @State enableFriction: boolean = false;
  @State friction: number = 0.75;
  @State enableEnablePaging: boolean = false;
  @State enablePaging: boolean = false;
  @State enableInitialOffsetXOffset: boolean = false;
  @State initialOffsetXOffset: Dimension = 0;
  @State enableInitialOffsetYOffset: boolean = false;
  @State initialOffsetYOffset: Dimension = 0;
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

  scrollerForV: Scroller = new Scroller();
  scrollerForH: Scroller = new Scroller();
  @State totalCount: number = 12;
  @State currentIndex: number = 0
  private controller: TabsController = new TabsController()

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
      Divider()
        .strokeWidth(2)
        .color('#007DFF')
        .opacity(this.currentIndex === index ? 1 : 0)
    }.width('100%')
  }

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
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex, controller: this.controller }) {
        TabContent() {
          Scroll(this.scrollerForV) {
            Column() {
              ForEach(this.getElements(), (item: number) => {
                Row() {
                }
                .width('100%')
                .height(80)
                .backgroundColor('#510A59F7')
                .borderRadius(12)
                .margin({ bottom: 20 })
              }, (item: string) => item)
            }
          }
          .scrollable(useEnabled(this.enableScrollable, this.scrollable))
          .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
          .scrollBarColor(useEnabled(this.enableScrollBarColor, this.scrollBarColor))
          .scrollBarWidth(useEnabled(this.enableScrollBarWidth, this.scrollBarWidth))
          .scrollSnap({
            snapAlign: useEnabled(this.enableScrollSnapSnapAlign, this.scrollSnapSnapAlign),
            snapPagination: useEnabled(this.enableScrollSnapSnapPagination, this.scrollSnapSnapPagination),
            enableSnapToStart: useEnabled(this.enableScrollSnapEnableSnapToStart, this.scrollSnapEnableSnapToStart),
            enableSnapToEnd: useEnabled(this.enableScrollSnapEnableSnapToEnd, this.scrollSnapEnableSnapToEnd)
          })
          .edgeEffect(
            useEnabled(this.enableEdgeEffect, this.edgeEffect),
            {
              alwaysEnabled: useEnabled(
                this.enableEdgeEffectOptionsAlwaysEnabled,
                this.edgeEffectOptionsAlwaysEnabled
              )
            }
          )
          .enableScrollInteraction(useEnabled(this.enableEnableScrollInteraction, this.enableScrollInteraction))
          .nestedScroll({
            scrollForward: useEnabled(this.enableNestedScrollScrollForward, this.nestedScrollScrollForward),
            scrollBackward: useEnabled(this.enableNestedScrollScrollBackward, this.nestedScrollScrollBackward)
          })
          .friction(useEnabled(this.enableFriction, this.friction))
          .enablePaging(useEnabled(this.enableEnablePaging, this.enablePaging))
          .initialOffset({
            xOffset: useEnabled(this.enableInitialOffsetXOffset, this.initialOffsetXOffset),
            yOffset: useEnabled(this.enableInitialOffsetYOffset, this.initialOffsetYOffset)
          })
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
        }.tabBar(this.tabBuilder(0, '竖直布局'))

        TabContent() {
          Scroll(this.scrollerForH) {
            Row() {
              ForEach(this.getElements(), (item: number) => {
                Row() {
                }
                .height(100)
                .width(100)
                .backgroundColor('#510A59F7')
                .borderRadius(12)
                .margin({ right: 20 })
              }, (item: string) => item)
            }
          }
          .scrollable(useEnabled(this.enableScrollable, this.scrollable))
          .scrollBar(useEnabled(this.enableScrollBar, this.scrollBar))
          .scrollBarColor(useEnabled(this.enableScrollBarColor, this.scrollBarColor))
          .scrollBarWidth(useEnabled(this.enableScrollBarWidth, this.scrollBarWidth))
          .scrollSnap({
            snapAlign: useEnabled(this.enableScrollSnapSnapAlign, this.scrollSnapSnapAlign),
            snapPagination: useEnabled(this.enableScrollSnapSnapPagination, this.scrollSnapSnapPagination),
            enableSnapToStart: useEnabled(this.enableScrollSnapEnableSnapToStart, this.scrollSnapEnableSnapToStart),
            enableSnapToEnd: useEnabled(this.enableScrollSnapEnableSnapToEnd, this.scrollSnapEnableSnapToEnd)
          })
          .edgeEffect(
            useEnabled(this.enableEdgeEffect, this.edgeEffect),
            {
              alwaysEnabled: useEnabled(
                this.enableEdgeEffectOptionsAlwaysEnabled,
                this.edgeEffectOptionsAlwaysEnabled
              )
            }
          )
          .enableScrollInteraction(useEnabled(this.enableEnableScrollInteraction, this.enableScrollInteraction))
          .nestedScroll({
            scrollForward: useEnabled(this.enableNestedScrollScrollForward, this.nestedScrollScrollForward),
            scrollBackward: useEnabled(this.enableNestedScrollScrollBackward, this.nestedScrollScrollBackward)
          })
          .friction(useEnabled(this.enableFriction, this.friction))
          .enablePaging(useEnabled(this.enableEnablePaging, this.enablePaging))
          .initialOffset({
            xOffset: useEnabled(this.enableInitialOffsetXOffset, this.initialOffsetXOffset),
            yOffset: useEnabled(this.enableInitialOffsetYOffset, this.initialOffsetYOffset)
          })
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
        }.tabBar(this.tabBuilder(1, '水平布局'))
      }
      .onChange((index: number) => {
        this.currentIndex = index
      })
    }
    .height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'scrollable',
          isEnabled: $enableScrollable,
          value: $scrollable,
          dataSource: [
            { label: 'Vertical', value: ScrollDirection.Vertical },
            { label: 'Horizontal', value: ScrollDirection.Horizontal },
            { label: 'None', value: ScrollDirection.None }
          ]
        })

        RadioBlock({
          title: 'scrollBar',
          isEnabled: $enableScrollBar,
          value: $scrollBar,
          dataSource: [
            { label: 'Off', value: BarState.Off },
            { label: 'On', value: BarState.On },
            { label: 'Auto', value: BarState.Auto }
          ]
        })

        ColorBlock({
          title: 'scrollBarColor',
          isEnabled: $enableScrollBarColor,
          color: $scrollBarColor
        })

        SliderBlock({
          title: 'scrollBarWidth',
          isEnabled: $enableScrollBarWidth,
          value: $scrollBarWidth,
          min: 1,
          max: 8
        })

        RadioBlock({
          title: 'scrollSnap.snapAlign',
          isEnabled: $enableScrollSnapSnapAlign,
          value: $scrollSnapSnapAlign,
          dataSource: [
            { label: 'NONE', value: ScrollSnapAlign.NONE },
            { label: 'START', value: ScrollSnapAlign.START },
            { label: 'CENTER', value: ScrollSnapAlign.CENTER },
            { label: 'END', value: ScrollSnapAlign.END }
          ]
        })

        SliderBlock({
          title: 'scrollSnap.snapPagination',
          isEnabled: $enableScrollSnapSnapPagination,
          value: $scrollSnapSnapPagination,
          min: 100,
          max: 1000
        })

        RadioBlock({
          title: 'scrollSnap.enableSnapToStart',
          isEnabled: $enableScrollSnapEnableSnapToStart,
          value: $scrollSnapEnableSnapToStart,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'scrollSnap.enableSnapToEnd',
          isEnabled: $enableScrollSnapEnableSnapToEnd,
          value: $scrollSnapEnableSnapToEnd,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'edgeEffect',
          isEnabled: $enableEdgeEffect,
          value: $edgeEffect,
          dataSource: [
            { label: 'Spring', value: EdgeEffect.Spring },
            { label: 'Fade', value: EdgeEffect.Fade },
            { label: 'None', value: EdgeEffect.None }
          ]
        })

        RadioBlock({
          title: 'edgeEffect.options.alwaysEnabled',
          isEnabled: $enableEdgeEffectOptionsAlwaysEnabled,
          value: $edgeEffectOptionsAlwaysEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
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

        RadioBlock({
          title: 'enablePaging',
          isEnabled: $enableEnablePaging,
          value: $enablePaging,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'initialOffset.xOffset',
          isEnabled: $enableInitialOffsetXOffset,
          value: $initialOffsetXOffset,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'initialOffset.yOffset',
          isEnabled: $enableInitialOffsetYOffset,
          value: $initialOffsetYOffset,
          min: 0,
          max: 100
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
struct ScrollBootcampPreviewer {
  build() {
    ScrollBootcamp({
      title: '滚动容器/Scroll'
    })
  }
}