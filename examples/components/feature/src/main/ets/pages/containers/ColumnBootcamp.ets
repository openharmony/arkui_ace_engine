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
export struct ColumnBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableSpace: boolean = false;
  @State space: number = 0;
  @State enableAlignItems: boolean = false;
  @State alignItems: HorizontalAlign = HorizontalAlign.Center;
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
      Column({
        space: useEnabled(this.enableSpace, this.space)
      }) {
        Column().width('100%').height(20).backgroundColor(0xAFEEEE)
        Column().width('100%').height(20).backgroundColor(0x00FFFF)
        Column().width('90%').height(20).backgroundColor(0xAFEEEE)
        Column().width('90%').height(20).backgroundColor(0x00FFFF)
        Column().width('50%').height(20).backgroundColor(0xAFEEEE)
        Column().width('50%').height(20).backgroundColor(0x00FFFF)
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
          title: '纵向布局元素垂直方向间距，单位：vp',
          isEnabled: $enableSpace,
          value: $space,
          min: 0,
          max: 10
        })

        RadioBlock({
          title: '子组件在水平方向上的对齐格式',
          isEnabled: $enableAlignItems,
          value: $alignItems,
          dataSource: [
            { label: '首部对齐', value: HorizontalAlign.Start },
            { label: '居中对齐', value: HorizontalAlign.Center },
            { label: '尾部对齐', value: HorizontalAlign.End }
          ]
        })

        RadioBlock({
          title: '子组件在Column容器主轴上的对齐格式',
          isEnabled: $enableJustifyContent,
          value: $justifyContent,
          dataSource: [
            { label: '首端对齐', value: FlexAlign.Start },
            { label: '居中对齐', value: FlexAlign.Center },
            { label: '尾端对齐', value: FlexAlign.End },
            { label: '均分容器布局，第一个子组件与行首对齐，最后一个子组件与行尾对齐', value: FlexAlign.SpaceBetween },
            {
              label: '均分容器布局，第一个子组件到行首的距离和最后一个子组件到行尾的距离是相邻子组件之间距离的一半',
              value: FlexAlign.SpaceAround
            },
            {
              label: '均分容器布局，子组件之间的距离与第一子组件到行首、最后一个子组件到行尾的距离相等',
              value: FlexAlign.SpaceEvenly
            }
          ]
        })

        RadioBlock({
          title: '子组件在主轴（即竖直方向）上的排列是否反转',
          isEnabled: $enableIsReversed,
          value: $isReversed,
          dataSource: [
            { label: '反转', value: true },
            { label: '不反转', value: false }
          ]
        })

        SliderBlock({
          title: '组件宽度',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: '组件高度',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 50,
          max: 400
        })

        SliderBlock({
          title: '组件内边距',
          isEnabled: $enableCompPadding,
          value: $compPadding,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: '组件外边距',
          isEnabled: $enableCompMargin,
          value: $compMargin,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: '组件背景颜色',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        SliderBlock({
          title: '边框宽度',
          isEnabled: $enableCompBorderWidth,
          value: $compBorderWidth,
          min: 0,
          max: 20
        })

        ColorBlock({
          title: '边框颜色',
          isEnabled: $enableCompBorderColor,
          color: $compBorderColor
        })

        SliderBlock({
          title: '边框圆角',
          isEnabled: $enableCompBorderRadius,
          value: $compBorderRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: '边框线条样式',
          isEnabled: $enableCompBorderStyle,
          value: $compBorderStyle,
          dataSource: [
            { label: '实线', value: BorderStyle.Solid },
            { label: '圆点虚线', value: BorderStyle.Dotted },
            { label: '线段虚线', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: '组件在父容器主轴方向上的基准尺寸',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 10,
          max: 200
        })

        SliderBlock({
          title: '组件的不透明度',
          isEnabled: $enableCompOpacity,
          value: $compOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        RadioBlock({
          title: '组件的显隐',
          isEnabled: $enableCompVisibility,
          value: $compVisibility,
          dataSource: [
            { label: '隐藏不参与占位', value: Visibility.None },
            { label: '隐藏参与占位', value: Visibility.Hidden },
            { label: '正常显示', value: Visibility.Visible }
          ]
        })

        RadioBlock({
          title: '子组件左右排列的方向',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: '从左到右', value: Direction.Ltr },
            { label: '从右到左', value: Direction.Rtl }
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
struct ColumnBootcampPreviewer {
  build() {
    ColumnBootcamp({
      title: '纵向布局/Column'
    })
  }
}