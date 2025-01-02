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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct BadgeBootcamp{

  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableNumberOrString: boolean = false;
  @State numberOrString: string = 'number'
  @State enableBadgeParamWithNumberCount: boolean = false
  @State badgeParamWithNumberCount: number = 1
  @State enableBadgeParamWithNumberMaxCount: boolean = false
  @State badgeParamWithNumberMaxCount: number = 99
  @State enableBadgeParamWithStringValue: boolean = false
  @State badgeParamWithStringValue: string = 'new'
  @State enableBadgeStyleColor: boolean = false
  @State badgeStyleColor: ResourceColor = Color.White
  @State enableBadgeStyleFontSize: boolean = false
  @State badgeStyleFontSize: number = 10
  @State enableBadgeStyleBadgeSize: boolean = false
  @State badgeStyleBadgeSize: number = 16
  @State enableBadgeStyleBadgeColor: boolean = false
  @State badgeStyleBadgeColor: ResourceColor = Color.Red
  @State enableBadgeStyleFontWeight: boolean = false
  @State badgeStyleFontWeight: FontWeight = FontWeight.Normal
  @State enableBadgeStyleBorderColor: boolean = false
  @State badgeStyleBorderColor: ResourceColor = Color.Red
  @State enableBadgeStyleBorderWidth: boolean = false
  @State badgeStyleBorderWidth: number = 1
  @State enableBadgePosition: boolean = false
  @State badgePosition: BadgePosition = BadgePosition.RightTop

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
  badgeParamWithNumber(){
    Badge({
      count: useEnabled(this.enableBadgeParamWithNumberCount, this.badgeParamWithNumberCount) as number,
      maxCount: useEnabled(this.enableBadgeParamWithNumberMaxCount, this.badgeParamWithNumberMaxCount),
      style: {
        color: useEnabled(this.enableBadgeStyleColor, this.badgeStyleColor),
        fontSize: useEnabled(this.enableBadgeStyleFontSize, this.badgeStyleFontSize),
        badgeSize: useEnabled(this.enableBadgeStyleBadgeSize, this.badgeStyleBadgeSize),
        badgeColor: useEnabled(this.enableBadgeStyleBadgeColor, this.badgeStyleBadgeColor),
        fontWeight: useEnabled(this.enableBadgeStyleFontWeight, this.badgeStyleFontWeight),
        borderColor: useEnabled(this.enableBadgeStyleBorderColor, this.badgeStyleBorderColor),
        borderWidth: useEnabled(this.enableBadgeStyleBorderWidth, this.badgeStyleBorderWidth)
      },
      position: useEnabled(this.enableBadgePosition, this.badgePosition),
    }){
      Image($r('app.media.app_icon'))
        .width(50)
        .height(50)
    }
    .width(55)
  }
  @Builder
  badgeParamWithString(){
    Badge({
      value: this.badgeParamWithStringValue,
      style: {
        color: useEnabled(this.enableBadgeStyleColor, this.badgeStyleColor),
        fontSize: useEnabled(this.enableBadgeStyleFontSize, this.badgeStyleFontSize),
        badgeSize: useEnabled(this.enableBadgeStyleBadgeSize, this.badgeStyleBadgeSize),
        badgeColor: useEnabled(this.enableBadgeStyleBadgeColor, this.badgeStyleBadgeColor),
        fontWeight: useEnabled(this.enableBadgeStyleFontWeight, this.badgeStyleFontWeight),
        borderColor: useEnabled(this.enableBadgeStyleBorderColor, this.badgeStyleBorderColor),
        borderWidth: useEnabled(this.enableBadgeStyleBorderWidth, this.badgeStyleBorderWidth)
      },
      position: useEnabled(this.enableBadgePosition, this.badgePosition),
    }){
      Image($r('app.media.app_icon'))
        .width(50)
        .height(50)
    }
    .width(55)
  }


  @Builder
  Content() {
    Column() {
      if (this.numberOrString === 'number'){
        this.badgeParamWithNumber()
      } else {
        this.badgeParamWithString()
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'badgeType',
          isEnabled: $enableNumberOrString,
          value: $numberOrString,
          dataSource: [
            { label: 'number', value: 'number' },
            { label: 'string', value: 'string' },
          ]
        })
        SliderBlock({
          title: 'BadgeParamWithNumber.count',
          isEnabled: $enableBadgeParamWithNumberCount,
          value: $badgeParamWithNumberCount,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'BadgeParamWithNumber.maxCount',
          isEnabled: $enableBadgeParamWithNumberMaxCount,
          value: $badgeParamWithNumberMaxCount,
          min: 0,
          max: 1000
        })
        RadioBlock({
          title: 'BadgeParamWithString.value',
          isEnabled: $enableBadgeParamWithStringValue,
          value: $badgeParamWithStringValue,
          dataSource: [
            { label: 'new', value: 'new' },
            { label: 'text', value: 'text' },
            { label: 'number', value: 'number' },
            { label: 'string', value: 'string' },
          ]
        })
        ColorBlock({
          title: 'BadgeStyle.color',
          isEnabled: $enableBadgeStyleColor,
          color: $badgeStyleColor
        })
        SliderBlock({
          title: 'BadgeStyle.fontSize',
          isEnabled: $enableBadgeStyleFontSize,
          value: $badgeStyleFontSize,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'BadgeStyle.badgeSize',
          isEnabled: $enableBadgeStyleBadgeSize,
          value: $badgeStyleBadgeSize,
          min: 0,
          max: 32
        })
        ColorBlock({
          title: 'BadgeStyle.badgeColor',
          isEnabled: $enableBadgeStyleBadgeColor,
          color: $badgeStyleBadgeColor
        })
        RadioBlock({
          title: 'BadgeStyle.fontWeight',
          isEnabled: $enableBadgeStyleFontWeight,
          value: $badgeStyleFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        ColorBlock({
          title: 'BadgeStyle.borderColor',
          isEnabled: $enableBadgeStyleBorderColor,
          color: $badgeStyleBorderColor
        })
        SliderBlock({
          title: 'BadgeStyle.borderWidth',
          isEnabled: $enableBadgeStyleBorderWidth,
          value: $badgeStyleBorderWidth,
          min: 0,
          max: 10
        })
        RadioBlock({
          title: 'BadgePosition',
          isEnabled: $enableBadgePosition,
          value: $badgePosition,
          dataSource: [
            { label: 'RightTop', value: BadgePosition.RightTop },
            { label: 'Right', value: BadgePosition.Right },
            { label: 'Left', value: BadgePosition.Left },
          ]
        })
      }
    }
    .height('52%')
  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    BadgeBootcamp({
      title: '信息标记/Badge'
    })
  }
}