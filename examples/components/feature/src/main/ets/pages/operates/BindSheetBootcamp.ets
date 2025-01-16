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
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';

@Component
export struct BindSheetBootcamp {
  @Require @Prop title: ResourceStr
  @State showParameters: boolean = false;
  @State isShowBindSheet: boolean = false;
  @State enablePreferType: boolean = false;
  @State preferType: SheetType = SheetType.BOTTOM;
  @State enableMaskColor: boolean = false;
  @State maskColor: ResourceColor = $r('sys.color.ohos_id_color_sub_background');
  @State enableBackgroundColorColor: boolean = false;
  @State backgroundColorColor: ResourceColor = Color.White;
  @State enableShadowStatus: boolean = false;
  @State shadowStatus: ShadowStyle = ShadowStyle.OUTER_FLOATING_SM;
  @State enableBorderWidth: boolean = false;
  @State borderWidthValue: number = 0;
  @State enableBorderColor: boolean = false;
  @State borderColorValue: ResourceColor = $r('sys.color.ohos_id_color_emphasize');
  @State enableSheetHeight: boolean = false;
  @State sheetHeight: SheetSize | Length = SheetSize.LARGE;
  @State enableSheetDetents: boolean = false;
  @State sheetDetents: SheetSize | Length = SheetSize.LARGE;
  @State enableRadiusLengthValue: boolean = false;
  @State radiusLengthValue: number = 32;
  @State enableRadiusLengthUnit: boolean = false;
  @State radiusLengthUnit: LengthUnit = LengthUnit.VP;

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
      Button('点击唤出半模态界面')
        .onClick(() => {
          this.isShowBindSheet = true;
        })
        .bindSheet($$this.isShowBindSheet, this.SheetBuilder(), {
          title: { title: this.title },
          height: useEnabled(this.enableSheetHeight, this.sheetHeight),
          detents: useEnabled(this.enableSheetDetents, [this.sheetDetents]),
          preferType: useEnabled(this.enablePreferType, this.preferType),
          maskColor: useEnabled(this.enableMaskColor, this.maskColor),
          shadow: useEnabled(this.enableShadowStatus, this.shadowStatus),
          borderWidth: useEnabled(this.enableBorderWidth, this.borderWidthValue),
          borderColor: useEnabled(this.enableBorderColor, this.borderColorValue),
          backgroundColor: useEnabled(this.enableBackgroundColorColor, this.backgroundColorColor),
          radius: new LengthMetrics(useEnabled(this.enableRadiusLengthValue, this.radiusLengthValue),
            useEnabled(this.enableRadiusLengthUnit, this.radiusLengthUnit)),
        })
    }
  }

  @Builder
  SheetBuilder() {
    Scroll() {
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '半模态页面的样式',
          isEnabled: this.enablePreferType,
          value: this.preferType,
          dataSource: [
            { label: 'BOTTOM', value: SheetType.BOTTOM },
            { label: 'CENTER', value: SheetType.CENTER },
            { label: 'POPUP', value: SheetType.POPUP },
          ]
        })

        RadioBlock({
          title: '阴影',
          isEnabled: this.enableShadowStatus,
          value: this.shadowStatus,
          dataSource: [
            { label: '超小阴影', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: '小阴影', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: '中阴影', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: '大阴影', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: '浮动小阴影', value: ShadowStyle.OUTER_FLOATING_SM },
            { label: '浮动中阴影', value: ShadowStyle.OUTER_FLOATING_MD },
          ]
        })

        SliderBlock({
          title: '边框宽度',
          isEnabled: this.enableBorderWidth,
          value: this.borderWidthValue,
          min: 0,
          max: 5
        })

        ColorBlock({
          title: '边框颜色',
          isEnabled: this.enableBorderColor,
          color: this.borderColorValue,
        })

        ColorBlock({
          title: '背景蒙层颜色',
          isEnabled: this.enableMaskColor,
          color: this.maskColor,
        })

        ColorBlock({
          title: '背景色',
          isEnabled: this.enableBackgroundColorColor,
          color: this.backgroundColorColor,
        })

        RadioBlock({
          title: '半模态高度',
          isEnabled: this.enableSheetHeight,
          value: this.sheetHeight,
          dataSource: [
            { label: 'MEDIUM', value: SheetSize.MEDIUM },
            { label: 'LARGE', value: SheetSize.LARGE },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
            { label: '1000vp', value: 1000 },
            { label: '700vp', value: 700 },
            { label: '250vp', value: 250 },
          ]
        })

        RadioBlock({
          title: '切换高度档位的最大值',
          isEnabled: this.enableSheetDetents,
          value: this.sheetDetents,
          dataSource: [
            { label: 'MEDIUM', value: SheetSize.MEDIUM },
            { label: 'LARGE', value: SheetSize.LARGE },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
            { label: '1000vp', value: 1000 },
            { label: '700vp', value: 700 },
            { label: '250vp', value: 250 },
          ]
        })

        SliderBlock({
          title: '圆角半径值',
          isEnabled: this.enableRadiusLengthValue,
          value: this.radiusLengthValue,
          min: -10,
          max: 900,
        })

        RadioBlock({
          title: '圆角半径单位',
          isEnabled: this.enableRadiusLengthUnit,
          value: this.radiusLengthUnit,
          dataSource: [
            { label: 'px', value: LengthUnit.PX },
            { label: 'vp', value: LengthUnit.VP },
            { label: 'fp', value: LengthUnit.FP },
            { label: 'percent', value: LengthUnit.PERCENT },
            { label: 'lpx', value: LengthUnit.LPX },
          ]
        })
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct BindSheetBootcampPreviewer {
  build() {
    BindSheetBootcamp({
      title: '半模态/BindSheet'
    })
  }
}
