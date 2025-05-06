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
export struct CalendarPickerDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableAcceptType: boolean = false;
  @State compAcceptType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableAcceptStyle: boolean = false;
  @State compAcceptStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableAcceptRole: boolean = false;
  @State compAcceptRole: ButtonRole = ButtonRole.NORMAL;
  @State enableAcceptFontSize: boolean = false;
  @State compAcceptFontSize: number = 16;
  @State enableAcceptFontColor: boolean = false;
  @State compAcceptFontColor: ResourceColor = '#ffffff';
  @State enableAcceptFontWeight: boolean = false;
  @State compAcceptFontWeight: FontWeight = 400;
  @State enableAcceptFontStyle: boolean = false;
  @State compAcceptFontStyle: FontStyle = FontStyle.Normal;
  @State enableAcceptFontFamily: boolean = false;
  @State compAcceptFontFamily: string = 'HarmonyOS Sans';
  @State enableAcceptBackGroundColor: boolean = false;
  @State compAcceptBackGroundColor: ResourceColor = '#ff182431';
  @State enableAcceptBorderRadius: boolean = false;
  @State compAcceptBorderRadius: number = 10;
  @State enableCancelType: boolean = false;
  @State compCancelType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableCancelStyle: boolean = false;
  @State compCancelStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableCancelRole: boolean = false;
  @State compCancelRole: ButtonRole = ButtonRole.NORMAL;
  @State enableCancelFontSize: boolean = false;
  @State compCancelFontSize: number = 16;
  @State enableCancelFontColor: boolean = false;
  @State compCancelFontColor: ResourceColor = '#ffffff';
  @State enableCancelFontWeight: boolean = false;
  @State compCancelFontWeight: FontWeight = 400;
  @State enableCancelFontStyle: boolean = false;
  @State compCancelFontStyle: FontStyle = FontStyle.Normal;
  @State enableCancelFontFamily: boolean = false;
  @State compCancelFontFamily: string = 'sans-serif';
  @State enableCancelBackGroundColor: boolean = false;
  @State compCancelBackGroundColor: ResourceColor = '#ff182431';
  @State enableCancelBorderRadius: boolean = false;
  @State compCancelBorderRadius: number = 10;
  @State buttonMargin: number = 20;
  @State enableBackgroundBlurStyle: boolean = false;
  @State compBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = Color.Transparent;
  @State enableCompShadowType: boolean = false;
  @State compShadowType: boolean = true;
  @State enableCompShadowStyle: boolean = false;
  @State compShadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;
  @State enableCompShadowOptionsRadius: boolean = false;
  @State compShadowOptionsRadius: number = 0;
  @State enableCompShadowOptionsType: boolean = false;
  @State compShadowOptionsType: ShadowType = ShadowType.COLOR;
  @State enableCompShadowOptionsColor: boolean = false;
  @State compShadowOptionsColor: ResourceColor = '#ff000000';
  @State enableCompShadowOptionsOffsetX: boolean = false;
  @State compShadowOptionsOffsetX: number = 0;
  @State enableCompShadowOptionsOffsetY: boolean = false;
  @State compShadowOptionsOffsetY: number = 0;
  @State enableCompShadowOptionsFill: boolean = false;
  @State compShadowOptionsFill: boolean = false;
  @State enableStartDate: boolean = false;
  @State startDate: Date = new Date('2020-12-10');
  @State enableEndDate: boolean = false;
  @State endDate: Date = new Date('2028-12-30');
  @State enableCompMarkToday: boolean = false;
  @State compMarkToday: boolean = false;
  @State enableCompDisabledDateRange: boolean = false;
  @State compDisabledDateRange: DateRange[] = [{ start: new Date('2020-12-10'), end: new Date('2020-12-11') }];
  scroller: Scroller = new Scroller();

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        generic: () => {
          this.Generic()
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
      Button('弹出弹窗')
        .margin(this.buttonMargin)
        .onClick(() => {
          console.info('CalendarDialog.show')
          CalendarPickerDialog.show({
            acceptButtonStyle: {
              type: useEnabled(this.enableAcceptType, this.compAcceptType),
              style: useEnabled(this.enableAcceptStyle, this.compAcceptStyle),
              role: useEnabled(this.enableAcceptRole, this.compAcceptRole),
              fontColor: useEnabled(this.enableAcceptFontColor, this.compAcceptFontColor),
              fontSize: useEnabled(this.enableAcceptFontSize, this.compAcceptFontSize),
              fontWeight: useEnabled(this.enableAcceptFontWeight, this.compAcceptFontWeight),
              fontStyle: useEnabled(this.enableAcceptFontStyle, this.compAcceptFontStyle),
              fontFamily: useEnabled(this.enableAcceptFontFamily, this.compAcceptFontFamily),
              backgroundColor: useEnabled(this.enableAcceptBackGroundColor, this.compAcceptBackGroundColor),
              borderRadius: useEnabled(this.enableAcceptBorderRadius, this.compAcceptBorderRadius)
            },
            cancelButtonStyle: {
              type: useEnabled(this.enableCancelType, this.compCancelType),
              style: useEnabled(this.enableCancelStyle, this.compCancelStyle),
              role: useEnabled(this.enableCancelRole, this.compCancelRole),
              fontColor: useEnabled(this.enableCancelFontColor, this.compCancelFontColor),
              fontSize: useEnabled(this.enableCancelFontSize, this.compCancelFontSize),
              fontWeight: useEnabled(this.enableCancelFontWeight, this.compCancelFontWeight),
              fontStyle: useEnabled(this.enableCancelFontStyle, this.compCancelFontStyle),
              fontFamily: useEnabled(this.enableCancelFontFamily, this.compCancelFontFamily),
              backgroundColor: useEnabled(this.enableCancelBackGroundColor, this.compCancelBackGroundColor),
              borderRadius: useEnabled(this.enableCancelBorderRadius, this.compCancelBorderRadius)
            },
            backgroundColor: useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor),
            backgroundBlurStyle: useEnabled(this.enableBackgroundBlurStyle,
              this.compBackgroundBlurStyle),
            shadow: useEnabled(this.enableCompShadowType, this.compShadowType) ?
            useEnabled(this.enableCompShadowStyle, this.compShadowStyle) : {
                radius: useEnabled(this.enableCompShadowOptionsRadius,
                  this.compShadowOptionsRadius),
                type: useEnabled(this.enableCompShadowOptionsType, this.compShadowOptionsType),
                color: useEnabled(this.enableCompShadowOptionsColor, this.compShadowOptionsColor),
                offsetX: useEnabled(this.enableCompShadowOptionsOffsetX,
                  this.compShadowOptionsOffsetX),
                offsetY: useEnabled(this.enableCompShadowOptionsOffsetY,
                  this.compShadowOptionsOffsetY),
                fill: useEnabled(this.enableCompShadowOptionsFill, this.compShadowOptionsFill),
              },
            onAccept: (value) => {
              console.info('calendar onAccept:' + JSON.stringify(value))
            },
            onCancel: () => {
              console.info('calendar onCancel')
            },
            onChange: (value) => {
              console.info('calendar onChange:' + JSON.stringify(value))
            },
            onDidAppear: () => {
              console.info('calendar onDidAppear')
            },
            onDidDisappear: () => {
              console.info('calendar onDidDisappear')
            },
            onWillAppear: () => {
              console.info('calendar onWillAppear')
            },
            onWillDisappear: () => {
              console.info('calendar onWillDisappear')
            },
            start: useEnabled(this.enableStartDate, this.startDate),
            end: useEnabled(this.enableEndDate, this.endDate),
            markToday: useEnabled(this.enableCompMarkToday, this.compMarkToday),
            disabledDateRange: useEnabled(this.enableCompDisabledDateRange, this.compDisabledDateRange)
          })
        })
    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.type',
          isEnabled: $enableAcceptType,
          value: $compAcceptType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
            { label: 'ROUNDED_RECTANGLE', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.type',
          isEnabled: $enableCancelType,
          value: $compCancelType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
            { label: 'ROUNDED_RECTANGLE', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.Style.ButtonStyleMode',
          isEnabled: $enableAcceptStyle,
          value: $compAcceptStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.Style.ButtonStyleMode',
          isEnabled: $enableCancelStyle,
          value: $compCancelStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.fontColor',
          isEnabled: $enableAcceptFontColor,
          color: $compAcceptFontColor
        })

        ColorBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.fontColor',
          isEnabled: $enableCancelFontColor,
          color: $compCancelFontColor
        })

        RadioBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.role.ButtonRole',
          isEnabled: $enableAcceptRole,
          value: $compAcceptRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR },
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.role.ButtonRole',
          isEnabled: $enableCancelRole,
          value: $compCancelRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR },
          ]
        })

        SliderBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.fontSize',
          isEnabled: $enableAcceptFontSize,
          value: $compAcceptFontSize,
          min: 12,
          max: 16
        })

        SliderBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.fontSize',
          isEnabled: $enableCancelFontSize,
          value: $compCancelFontSize,
          min: 12,
          max: 16
        })

        SliderBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.fontWeight',
          isEnabled: $enableAcceptFontWeight,
          value: $compAcceptFontWeight,
          min: 400,
          max: 800
        })
        SliderBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.fontWeight',
          isEnabled: $enableCancelFontWeight,
          value: $compCancelFontWeight,
          min: 400,
          max: 800
        })

        RadioBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.fontStyle',
          isEnabled: $enableAcceptFontStyle,
          value: $compAcceptFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.fontStyle',
          isEnabled: $enableCancelFontStyle,
          value: $compCancelFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.backgroundColor',
          isEnabled: $enableAcceptBackGroundColor,
          color: $compAcceptBackGroundColor
        })

        ColorBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.backgroundColor',
          isEnabled: $enableCancelBackGroundColor,
          color: $compCancelBackGroundColor
        })

        SliderBlock({
          title: 'CalendarDialogOptions.acceptButtonStyle.borderRadius',
          isEnabled: $enableAcceptBorderRadius,
          value: $compAcceptBorderRadius,
          min: 10,
          max: 100
        })

        SliderBlock({
          title: 'CalendarDialogOptions.cancelButtonStyle.borderRadius',
          isEnabled: $enableCancelBorderRadius,
          value: $compCancelBorderRadius,
          min: 10,
          max: 100
        })

        RadioBlock({
          title: 'CalendarDialogOptions.backgroundBlurStyle.BlurStyle',
          isEnabled: $enableBackgroundBlurStyle,
          value: $compBackgroundBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })

        ColorBlock({
          title: 'CalendarDialogOptions.backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        RadioBlock({
          title: 'CalendarDialogOptions.shadow',
          isEnabled: $enableCompShadowType,
          value: $compShadowType,
          dataSource: [
            { label: 'shadowStyle', value: true },
            { label: 'shadowOptions', value: false }
          ]
        })

        if (this.compShadowType) {
          RadioBlock({
            title: 'CalendarDialogOptions.shadow.shadowStyle',
            isEnabled: $enableCompShadowStyle,
            value: $compShadowStyle,
            dataSource: [
              { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
              { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
              { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
              { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
              { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
              { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
            ]
          })
        } else {

          SliderBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.radius',
            isEnabled: $enableCompShadowOptionsRadius,
            value: $compShadowOptionsRadius,
            min: 0,
            max: 30,
          })

          RadioBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.type',
            isEnabled: $enableCompShadowOptionsType,
            value: $compShadowOptionsType,
            dataSource: [
              { label: 'COLOR', value: ShadowType.COLOR },
              { label: 'BLUR', value: ShadowType.BLUR },
            ]
          })

          ColorBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.color',
            isEnabled: $enableCompShadowOptionsColor,
            color: $compShadowOptionsColor,
          })

          SliderBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.offsetX',
            isEnabled: $enableCompShadowOptionsOffsetX,
            value: $compShadowOptionsOffsetX,
            min: 0,
            max: 40,
          })

          SliderBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.offsetY',
            isEnabled: $enableCompShadowOptionsOffsetY,
            value: $compShadowOptionsOffsetY,
            min: 0,
            max: 40,
          })

          RadioBlock({
            title: 'CalendarDialogOptions.shadow.shadowOptions.fill',
            isEnabled: $enableCompShadowOptionsFill,
            value: $compShadowOptionsFill,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

        }

        RadioBlock({
          title: 'CalendarDialogOptions.start',
          isEnabled: $enableStartDate,
          value: $startDate,
          dataSource: [
            { label: '2020-12-10', value: new Date('2020-12-10') },
            { label: '2021-12-10', value: new Date('2021-12-10') },
            { label: '2022-12-10', value: new Date('2022-12-10') },
            { label: '2023-12-10', value: new Date('2023-12-10') },
            { label: '2024-12-10', value: new Date('2024-12-10') },
            { label: '2025-12-10', value: new Date('2025-12-10') }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.end',
          isEnabled: $enableEndDate,
          value: $endDate,
          dataSource: [
            { label: '2025-12-10', value: new Date('2025-12-10') },
            { label: '2026-12-10', value: new Date('2026-12-10') },
            { label: '2027-12-10', value: new Date('2027-12-10') },
            { label: '2028-12-10', value: new Date('2028-12-10') },
            { label: '2029-12-10', value: new Date('2029-12-10') },
            { label: '2030-12-10', value: new Date('2030-12-10') }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.markToday',
          isEnabled: $enableCompMarkToday,
          value: $compMarkToday,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'CalendarDialogOptions.disabledDateRange',
          isEnabled: $enableCompDisabledDateRange,
          value: $compDisabledDateRange,
          dataSource: [
            {
              label: '2020-12-10~2020-12-11',
              value: [{ start: new Date('2020-12-10'), end: new Date('2020-12-11') }] as DateRange[]
            },
            {
              label: '2021-12-10~2021-12-11',
              value: [{ start: new Date('2021-12-10'), end: new Date('2021-12-11') }] as DateRange[]
            },
            {
              label: '2022-12-10~2022-12-11',
              value: [{ start: new Date('2022-12-10'), end: new Date('2022-12-11') }] as DateRange[]
            },
            {
              label: '2023-12-10~2023-12-11',
              value: [{ start: new Date('2023-12-10'), end: new Date('2023-12-11') }] as DateRange[]
            },
            {
              label: '2024-12-10~2024-12-11',
              value: [{ start: new Date('2024-12-10'), end: new Date('2024-12-11') }] as DateRange[]
            },
            {
              label: '2025-12-10~2025-12-11',
              value: [{ start: new Date('2025-12-10'), end: new Date('2025-12-11') }] as DateRange[]
            }
          ]
        })

      }.width('100%')
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {

  }
}

@Preview
@Component
struct CalendarPickerDialogBootcampPreviewer {
  build() {
    CalendarPickerDialogBootcamp({
      title: '日历选择器弹窗/CalendarpickerDialog'
    })
  }
}
