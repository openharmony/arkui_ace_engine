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
            }
          })
        })
    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '确认按钮类型',
          isEnabled: this.enableAcceptType,
          value: this.compAcceptType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '取消按钮类型',
          isEnabled: this.enableCancelType,
          value: this.compCancelType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '确认按钮样式',
          isEnabled: this.enableAcceptStyle,
          value: this.compAcceptStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: '取消按钮样式',
          isEnabled: this.enableCancelStyle,
          value: this.compCancelStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: '确认按钮字体颜色',
          isEnabled: this.enableAcceptFontColor,
          color: this.compAcceptFontColor
        })

        ColorBlock({
          title: '取消按钮字体颜色',
          isEnabled: this.enableCancelFontColor,
          color: this.compCancelFontColor
        })

        RadioBlock({
          title: '确认按钮角色',
          isEnabled: this.enableAcceptRole,
          value: this.compAcceptRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR },
          ]
        })

        RadioBlock({
          title: '取消按钮角色',
          isEnabled: this.enableCancelRole,
          value: this.compCancelRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR },
          ]
        })

        SliderBlock({
          title: '确认按钮尺寸',
          isEnabled: this.enableAcceptFontSize,
          value: this.compAcceptFontSize,
          min: 12,
          max: 16
        })

        SliderBlock({
          title: '取消按钮尺寸',
          isEnabled: this.enableCancelFontSize,
          value: this.compCancelFontSize,
          min: 12,
          max: 16
        })

        SliderBlock({
          title: '确认按钮字体粗细',
          isEnabled: this.enableAcceptFontWeight,
          value: this.compAcceptFontWeight,
          min: 400,
          max: 800
        })
        SliderBlock({
          title: '取消按钮字体粗细',
          isEnabled: this.enableCancelFontWeight,
          value: this.compCancelFontWeight,
          min: 400,
          max: 800
        })

        RadioBlock({
          title: '确认按钮字体样式',
          isEnabled: this.enableAcceptFontStyle,
          value: this.compAcceptFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: '取消按钮字体样式',
          isEnabled: this.enableCancelFontStyle,
          value: this.compCancelFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: '确认按钮背景颜色',
          isEnabled: this.enableAcceptBackGroundColor,
          color: this.compAcceptBackGroundColor
        })

        ColorBlock({
          title: '取消按钮背景颜色',
          isEnabled: this.enableCancelBackGroundColor,
          color: this.compCancelBackGroundColor
        })

        SliderBlock({
          title: '确认按钮边框圆角半径',
          isEnabled: this.enableAcceptBorderRadius,
          value: this.compAcceptBorderRadius,
          min: 10,
          max: 100
        })

        SliderBlock({
          title: '取消按钮边框圆角半径',
          isEnabled: this.enableCancelBorderRadius,
          value: this.compCancelBorderRadius,
          min: 10,
          max: 100
        })
      }.width('100%')
    }
    .height('52%')
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
