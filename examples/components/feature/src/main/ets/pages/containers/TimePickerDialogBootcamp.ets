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
import { RadioBlock, ColorBlock, useEnabled } from 'common';

@Component
export struct TimePickerDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  selectedDate: Date = new Date('2010-1-1');
  private selectTime: Date = new Date('2022-07-22T08:00:00');
  @State enableFormat: boolean = false;
  @State enableMilitaryTime: boolean = false;
  @State enableHourFormat: boolean = false;
  @State enableMinuteFormat: boolean = false;
  @State enableSecondFormat: boolean = false;
  @State isMilitaryTime: boolean = false;
  @State hourFormat: string = 'numeric';
  @State minuteFormat: string = '2-digit';
  @State secondFormat: string = '2-digit';
  @State enabledAcceptButtonType: boolean = false;
  @State acceptButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableAcceptButtonStyle: boolean = false;
  @State acceptButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableAcceptButtonRole: boolean = false;
  @State acceptButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableAcceptButtonFontSize: boolean = false;
  @State acceptButtonFontSize: Length = '16fp';
  @State enableAcceptButtonFontColor: boolean = false;
  @State acceptButtonFontColor: ResourceColor = '#ffffff';
  @State enableAcceptButtonFontWeight: boolean = false;
  @State acceptButtonFontWeight: FontWeight = 400;
  @State enableAcceptButtonFontStyle: boolean = false;
  @State acceptButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableAcceptButtonFontFamily: boolean = false;
  @State acceptButtonFontFamily: string = 'sans-serif';
  @State enableAcceptButtonBackGroundColor: boolean = false;
  @State acceptButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableAcceptButtonBorderRadius: boolean = false;
  @State acceptButtonBorderRadius: Length = 10;
  @State enabledCancelButtonType: boolean = false;
  @State cancelButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableCancelButtonStyle: boolean = false;
  @State cancelButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableCancelButtonRole: boolean = false;
  @State cancelButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableCancelButtonFontSize: boolean = false;
  @State cancelButtonFontSize: Length = '16fp';
  @State enableCancelButtonFontColor: boolean = false;
  @State cancelButtonFontColor: ResourceColor = '#ffffff';
  @State enableCancelButtonFontWeight: boolean = false;
  @State cancelButtonFontWeight: FontWeight = 400;
  @State enableCancelButtonFontStyle: boolean = false;
  @State cancelButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableCancelButtonFontFamily: boolean = false;
  @State cancelButtonFontFamily: string = 'sans-serif';
  @State enableCancelButtonBackGroundColor: boolean = false;
  @State cancelButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableCancelButtonBorderRadius: boolean = false;
  @State cancelButtonBorderRadius: Length = 10;

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
    Button('弹出弹窗')
      .margin(20)
      .onClick(() => {
        TimePickerDialog.show({
          selected: this.selectTime,
          useMilitaryTime: false,
          acceptButtonStyle: {
            type: useEnabled(this.enabledAcceptButtonType, this.acceptButtonType),
            style: useEnabled(this.enableAcceptButtonStyle, this.acceptButtonStyle),
            role: useEnabled(this.enableAcceptButtonRole, this.acceptButtonRole),
            fontColor: useEnabled(this.enableAcceptButtonFontColor, this.acceptButtonFontColor),
            fontSize: useEnabled(this.enableAcceptButtonFontSize, this.acceptButtonFontSize),
            fontWeight: useEnabled(this.enableAcceptButtonFontWeight, this.acceptButtonFontWeight),
            fontStyle: useEnabled(this.enableAcceptButtonFontStyle, this.acceptButtonFontStyle),
            fontFamily: useEnabled(this.enableAcceptButtonFontFamily, this.acceptButtonFontFamily),
            backgroundColor: useEnabled(this.enableAcceptButtonBackGroundColor, this.acceptButtonBackGroundColor),
            borderRadius: useEnabled(this.enableAcceptButtonBorderRadius, this.acceptButtonBorderRadius),
          },
          cancelButtonStyle: {
            type: useEnabled(this.enabledCancelButtonType, this.cancelButtonType),
            style: useEnabled(this.enableCancelButtonStyle, this.cancelButtonStyle),
            role: useEnabled(this.enableCancelButtonRole, this.cancelButtonRole),
            fontColor: useEnabled(this.enableCancelButtonFontColor, this.cancelButtonFontColor),
            fontSize: useEnabled(this.enableCancelButtonFontSize, this.cancelButtonFontSize),
            fontWeight: useEnabled(this.enableCancelButtonFontWeight, this.cancelButtonFontWeight),
            fontStyle: useEnabled(this.enableCancelButtonFontStyle, this.cancelButtonFontStyle),
            fontFamily: useEnabled(this.enableCancelButtonFontFamily, this.cancelButtonFontFamily),
            backgroundColor: useEnabled(this.enableCancelButtonBackGroundColor, this.cancelButtonBackGroundColor),
            borderRadius: useEnabled(this.enableCancelButtonBorderRadius, this.cancelButtonBorderRadius),
          },
          onAccept: (value: TimePickerResult) => {
            if (value.hour != undefined && value.minute != undefined) {
              this.selectTime.setHours(value.hour, value.minute)
              console.info('TimePickerDialog:onAccept()' + JSON.stringify(value))
            }
          },
          onCancel: () => {
            console.info('TimePickerDialog:onCancel()')
          },
          onChange: (value: TimePickerResult) => {
            console.info('TimePickerDialog:onChange()' + JSON.stringify(value))
          },
          onDidAppear: () => {
            console.info('TimePickerDialog:onDidAppear()')
          },
          onDidDisappear: () => {
            console.info('TimePickerDialog:onDidDisappear()')
          },
          onWillAppear: () => {
            console.info('TimePickerDialog:onWillAppear()')
          },
          onWillDisappear: () => {
            console.info('TimePickerDialog:onWillDisappear()')
          }
        })
      })
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '确认按钮类型',
          isEnabled: this.enabledAcceptButtonType,
          value: this.acceptButtonType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '取消按钮类型',
          isEnabled: this.enabledCancelButtonType,
          value: this.cancelButtonType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '确认按钮样式',
          isEnabled: this.enableAcceptButtonStyle,
          value: this.acceptButtonStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: '取消按钮样式',
          isEnabled: this.enableCancelButtonStyle,
          value: this.cancelButtonStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: '确认按钮字体颜色',
          isEnabled: this.enableAcceptButtonFontColor,
          color: this.acceptButtonFontColor
        })
        ColorBlock({
          title: '取消按钮字体颜色',
          isEnabled: this.enableCancelButtonFontColor,
          color: this.cancelButtonFontColor
        })

        RadioBlock({
          title: '确认按钮角色',
          isEnabled: this.enableAcceptButtonRole,
          value: this.acceptButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: '取消按钮角色',
          isEnabled: this.enableCancelButtonRole,
          value: this.cancelButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: '确认按钮尺寸',
          isEnabled: this.enableAcceptButtonFontSize,
          value: this.acceptButtonFontSize,
          dataSource: [
            { label: '正常', value: '16fp' },
            { label: '小型', value: '12fp' }
          ]
        })

        RadioBlock({
          title: '取消按钮尺寸',
          isEnabled: this.enableCancelButtonFontSize,
          value: this.cancelButtonFontSize,
          dataSource: [
            { label: '正常', value: '16fp' },
            { label: '小型', value: '12fp' }
          ]
        })

        RadioBlock({
          title: '确认按钮字体粗细',
          isEnabled: this.enableAcceptButtonFontWeight,
          value: this.acceptButtonFontWeight,
          dataSource: [
            { label: '正常', value: 400 },
            { label: '加粗', value: 800 }
          ]
        })

        RadioBlock({
          title: '取消按钮字体粗细',
          isEnabled: this.enableCancelButtonFontWeight,
          value: this.cancelButtonFontWeight,
          dataSource: [
            { label: '正常', value: 400 },
            { label: '加粗', value: 800 }
          ]
        })

        RadioBlock({
          title: '确认按钮字体样式',
          isEnabled: this.enableAcceptButtonFontStyle,
          value: this.acceptButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })

        RadioBlock({
          title: '取消按钮字体样式',
          isEnabled: this.enableCancelButtonFontStyle,
          value: this.cancelButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })

        ColorBlock({
          title: '确认按钮背景颜色',
          isEnabled: this.enableAcceptButtonBackGroundColor,
          color: this.acceptButtonBackGroundColor
        })

        ColorBlock({
          title: '取消按钮背景颜色',
          isEnabled: this.enableCancelButtonBackGroundColor,
          color: this.cancelButtonBackGroundColor
        })

        RadioBlock({
          title: '确认按钮边框圆角半径',
          isEnabled: this.enableAcceptButtonBorderRadius,
          value: this.acceptButtonBorderRadius,
          dataSource: [
            { label: '正常', value: 10 },
            { label: '较大', value: 100 }
          ]
        })

        RadioBlock({
          title: '取消按钮边框圆角半径',
          isEnabled: this.enableCancelButtonBorderRadius,
          value: this.cancelButtonBorderRadius,
          dataSource: [
            { label: '正常', value: 10 },
            { label: '较大', value: 100 }
          ]
        })

        RadioBlock({
          title: '小时是否有前导0',
          isEnabled: this.enableHourFormat,
          value: this.hourFormat,
          dataSource: [
            { label: '有前导0', value: '2-digit' },
            { label: '无前导0', value: 'numeric' }
          ]
        })

        RadioBlock({
          title: '分钟是否有前导0',
          isEnabled: this.enableMinuteFormat,
          value: this.minuteFormat,
          dataSource: [
            { label: '有前导0', value: '2-digit' },
            { label: '无前导0', value: 'numeric' }
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TimePickerDialogBootcampPreviewer {
  build() {
    TimePickerDialogBootcamp({
      title: '时间选择器弹窗'
    })
  }
}