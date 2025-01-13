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
import { RadioBlock, SliderBlock, useEnabled, ColorBlock } from 'common';

@Component
export struct TabsBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableBarPosition: boolean = false;
  @State barPosition: BarPosition = BarPosition.Start;
  @State enableVertical: boolean = false;
  @State vertical: boolean = false;
  @State enableScrollable: boolean = false;
  @State scrollable: boolean = false;
  @State enableBarModeValue: boolean = false;
  @State barModeValue: BarMode = BarMode.Scrollable;
  @State enableBarModeOptionsMargin: boolean = false;
  @State barModeOptionsMargin: Dimension = 0;
  @State enableBarModeOptionsNonScrollableLayoutStyle: boolean = false;
  @State barModeOptionsNonScrollableLayoutStyle: LayoutStyle = LayoutStyle.ALWAYS_CENTER;
  @State enableBarWidth: boolean = false;
  @State barWidth: Length = 56;
  @State enableBarHeight: boolean = false;
  @State barHeight: Length = 56;
  @State enableAnimationDuration: boolean = false;
  @State animationDuration: number = 300;
  @State enableAnimationMode: boolean = false;
  @State animationMode: AnimationMode = AnimationMode.CONTENT_FIRST;
  @State enableDivider: boolean = false;
  @State divider: DividerStyle | null = null;
  @State enableDividerStrokeWidth: boolean = false;
  @State dividerStrokeWidth: Length = 0;
  @State enableDividerColor: boolean = false;
  @State dividerColor: ResourceColor = '#33182431';
  @State enableDividerStartMargin: boolean = false;
  @State dividerStartMargin: Length = 0;
  @State enableDividerEndMargin: boolean = false;
  @State dividerEndMargin: Length = 0;
  @State enableFadingEdge: boolean = false;
  @State fadingEdge: boolean = true;
  @State enableBarOverlap: boolean = false;
  @State barOverlap: boolean = false;
  @State enableBarBackgroundColor: boolean = false;
  @State barBackgroundColor: ResourceColor = Color.Transparent;
  @State enableBarBackgroundBlurStyle: boolean = false;
  @State barBackgroundBlurStyle: BlurStyle = BlurStyle.NONE;
  @State enableBarGridAlign: boolean = false;
  @State barGridAlign: boolean = false;
  @State enableBarGridAlignMargin: boolean = false;
  @State barGridAlignMargin: Dimension = 24;
  @State enableBarGridAlignGutter: boolean = false;
  @State barGridAlignGutter: Dimension = 24;
  @State enableBarGridAlignSm: boolean = false;
  @State barGridAlignSm: number = -1;
  @State enableBarGridAlignMd: boolean = false;
  @State barGridAlignMd: number = -1;
  @State enableBarGridAlignLg: boolean = false;
  @State barGridAlignLg: number = -1;
  @State enableEdgeEffect: boolean = false;
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State fontColor: string = '#182431';
  @State selectedFontColor: string = '#007DFF';
  @State currentIndex: number = 0;
  @State selectedIndex: number = 0;
  private controller: TabsController = new TabsController();

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontColor(this.selectedIndex === index ? this.selectedFontColor : this.fontColor)
        .fontSize(16)
        .fontWeight(this.selectedIndex === index ? 500 : 400)
        .lineHeight(22)
        .margin({ top: 17, bottom: 7 })
      Divider()
        .strokeWidth(2)
        .color('#007DFF')
        .opacity(this.selectedIndex === index ? 1 : 0)
    }.width('100%')
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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Column() {
        Tabs({
          barPosition: useEnabled(this.enableBarPosition, this.barPosition),
          index: $$this.currentIndex,
          controller: this.controller
        }) {
          TabContent() {
            Column()
              .width('100%')
              .height('100%')
              .backgroundColor('#00CB87')
          }
          .tabBar(this.tabBuilder(0, 'green'))

          TabContent() {
            Column()
              .width('100%')
              .height('100%')
              .backgroundColor('#007DFF')
          }
          .tabBar(this.tabBuilder(1, 'blue'))

          TabContent() {
            Column()
              .width('100%')
              .height('100%')
              .backgroundColor('#FFBF00')
          }
          .tabBar(this.tabBuilder(2, 'yellow'))

          TabContent() {
            Column()
              .width('100%')
              .height('100%')
              .backgroundColor('#E67C92')
          }
          .tabBar(this.tabBuilder(3, 'pink'))
        }
        .vertical(useEnabled(this.enableVertical, this.vertical))
        .scrollable(useEnabled(this.enableScrollable, this.scrollable))
        .barMode(useEnabled(this.enableBarModeValue, this.barModeValue), this.barModeValue == BarMode.Scrollable ? {
          margin: useEnabled(this.enableBarModeOptionsMargin, this.barModeOptionsMargin),
          nonScrollableLayoutStyle: useEnabled(this.enableBarModeOptionsNonScrollableLayoutStyle,
            this.barModeOptionsNonScrollableLayoutStyle)
        } : undefined)
        .barWidth(useEnabled(this.enableBarWidth, this.barWidth))
        .barHeight(useEnabled(this.enableBarHeight, this.barHeight))
        .animationDuration(useEnabled(this.enableAnimationDuration, this.animationDuration))
        .animationMode(useEnabled(this.enableAnimationMode, this.animationMode))
        .barPosition(useEnabled(this.enableBarPosition, this.barPosition))
        .divider(this.enableDivider ? {
          strokeWidth: useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth),
          color: useEnabled(this.enableDividerColor, this.dividerColor),
          startMargin: useEnabled(this.enableDividerStartMargin, this.dividerStartMargin),
          endMargin: useEnabled(this.enableDividerEndMargin, this.dividerEndMargin)
        } : null)
        .fadingEdge(useEnabled(this.enableFadingEdge, this.fadingEdge))
        .barOverlap(useEnabled(this.enableBarOverlap, this.barOverlap))
        .barBackgroundColor(useEnabled(this.enableBarBackgroundColor, this.barBackgroundColor))
        .barBackgroundBlurStyle(useEnabled(this.enableBarBackgroundBlurStyle, this.barBackgroundBlurStyle))
        .barGridAlign(useEnabled(this.enableBarGridAlign, this.barGridAlign) ? {
          margin: useEnabled(this.enableBarGridAlignMargin, this.barGridAlignMargin),
          gutter: useEnabled(this.enableBarGridAlignGutter, this.barGridAlignGutter),
          sm: useEnabled(this.enableBarGridAlignSm, this.barGridAlignSm),
          md: useEnabled(this.enableBarGridAlignMd, this.barGridAlignMd),
          lg: useEnabled(this.enableBarGridAlignLg, this.barGridAlignLg)
        } : {})
        .edgeEffect(useEnabled(this.enableEdgeEffect, this.edgeEffect))
        .onChange((index: number) => {
          this.currentIndex = index;
          this.selectedIndex = index;
        })
      }
      .width('100%')
      .height('100%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'barPosition',
          isEnabled: $enableBarPosition,
          value: $barPosition,
          dataSource: [
            { label: 'Start', value: BarPosition.Start },
            { label: 'End', value: BarPosition.End }
          ]
        })

        RadioBlock({
          title: 'vertical',
          isEnabled: $enableVertical,
          value: $vertical,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'scrollable',
          isEnabled: $enableScrollable,
          value: $scrollable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'barMode.value',
          isEnabled: $enableBarModeValue,
          value: $barModeValue,
          dataSource: [
            { label: 'Scrollable', value: BarMode.Scrollable },
            { label: 'Fixed', value: BarMode.Fixed }
          ]
        })

        SliderBlock({
          title: 'barMode.options.margin',
          isEnabled: $enableBarModeOptionsMargin,
          value: $barModeOptionsMargin,
          min: 1,
          max: 12
        })

        RadioBlock({
          title: 'barMode.options.nonScrollableLayoutStyle',
          isEnabled: $enableBarModeOptionsNonScrollableLayoutStyle,
          value: $barModeOptionsNonScrollableLayoutStyle,
          dataSource: [
            { label: 'ALWAYS_CENTER', value: LayoutStyle.ALWAYS_CENTER },
            { label: 'ALWAYS_AVERAGE_SPLIT', value: LayoutStyle.ALWAYS_AVERAGE_SPLIT },
            { label: 'SPACE_BETWEEN_OR_CENTER', value: LayoutStyle.SPACE_BETWEEN_OR_CENTER }
          ]
        })

        SliderBlock({
          title: 'barWidth',
          isEnabled: $enableBarWidth,
          value: $barWidth,
          min: 50,
          max: 100
        })

        SliderBlock({
          title: 'barHeight',
          isEnabled: $enableBarHeight,
          value: $barHeight,
          min: 50,
          max: 100
        })

        SliderBlock({
          title: 'animationDuration',
          isEnabled: $enableAnimationDuration,
          value: $animationDuration,
          min: 300,
          max: 1000
        })

        RadioBlock({
          title: 'animationMode',
          isEnabled: $enableAnimationMode,
          value: $animationMode,
          dataSource: [
            { label: 'CONTENT_FIRST', value: AnimationMode.CONTENT_FIRST },
            { label: 'ACTION_FIRST', value: AnimationMode.ACTION_FIRST },
            { label: 'NO_ANIMATION', value: AnimationMode.NO_ANIMATION }
          ]
        })

        RadioBlock({
          title: 'divider',
          isEnabled: $enableDivider,
          value: $divider
        })

        SliderBlock({
          title: 'divider.strokeWidth',
          isEnabled: $enableDividerStrokeWidth,
          value: $dividerStrokeWidth,
          min: 0,
          max: 10
        })

        ColorBlock({
          title: 'divider.color',
          isEnabled: $enableDividerColor,
          color: $dividerColor
        })

        SliderBlock({
          title: 'divider.startMargin',
          isEnabled: $enableDividerStartMargin,
          value: $dividerStartMargin,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'divider.endMargin',
          isEnabled: $enableDividerEndMargin,
          value: $dividerEndMargin,
          min: 0,
          max: 10
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

        RadioBlock({
          title: 'barOverlap',
          isEnabled: $enableBarOverlap,
          value: $barOverlap,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'barBackgroundColor',
          isEnabled: $enableBarBackgroundColor,
          color: $barBackgroundColor
        })

        RadioBlock({
          title: 'barBackgroundBlurStyle',
          isEnabled: $enableBarBackgroundBlurStyle,
          value: $barBackgroundBlurStyle,
          dataSource: [
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK }
          ]
        })

        RadioBlock({
          title: 'barGridAlign',
          isEnabled: $enableBarGridAlign,
          value: $barGridAlign,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'barGridAlign.margin',
          isEnabled: $enableBarGridAlignMargin,
          value: $barGridAlignMargin,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'barGridAlign.gutter',
          isEnabled: $enableBarGridAlignGutter,
          value: $barGridAlignGutter,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'barGridAlign.sm',
          isEnabled: $enableBarGridAlignSm,
          value: $barGridAlignSm,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'barGridAlign.md',
          isEnabled: $enableBarGridAlignMd,
          value: $barGridAlignMd,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'barGridAlign.lg',
          isEnabled: $enableBarGridAlignLg,
          value: $barGridAlignLg,
          min: 1,
          max: 5
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
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TabsBootcampPreviewer {
  build() {
    TabsBootcamp({ title: '页签容器/Tabs' })
  }
}