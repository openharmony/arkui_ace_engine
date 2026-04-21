/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * CalendarPickerExample001: 基础日历选择器示例
 * 演示CalendarPicker的基本用法
 */
@Component
export struct CalendarPickerExample001 {
  private selectedDate: Date = new Date('2024-03-05')

  build() {
    Column() {
      Text('基础日历选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Column() {
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
          .edgeAlign(CalendarAlign.END)
          .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
          .margin(10)
          .onChange((value) => {
            console.info('CalendarPicker onChange:' + JSON.stringify(value))
          })
      }.alignItems(HorizontalAlign.End).width('100%')

      Text('提示: 点击选择日期')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample002: 日期变化事件回调
 */
@Component
export struct CalendarPickerExample002 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State changeDesc: string = ''

  build() {
    Column() {
      Text('日期变化事件回调')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          this.changeDesc = '选中日期: ' + value.year + '-' + value.month + '-' + value.day
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.changeDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('提示: 选择日期查看回调信息')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample003: 设置文本样式
 */
@Component
export struct CalendarPickerExample003 {
  private selectedDate: Date = new Date('2024-03-05')
  @State textColor: string = '#ff182431'
  @State fontSize: number = 20
  @State fontWeight: number = FontWeight.Normal

  build() {
    Column() {
      Text('设置文本样式')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: this.textColor, font: { size: this.fontSize, weight: this.fontWeight } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('文本颜色')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('黑色')
          .onClick(() => {
            this.textColor = '#ff182431'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('红色')
          .onClick(() => {
            this.textColor = '#ff000000'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('蓝色')
          .onClick(() => {
            this.textColor = '#ff0000ff'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换文本颜色')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample004: 设置边缘对齐方式
 */
@Component
export struct CalendarPickerExample004 {
  private selectedDate: Date = new Date('2024-03-05')
  @State align: CalendarAlign = CalendarAlign.END

  build() {
    Column() {
      Text('设置边缘对齐方式')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(this.align)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('对齐方式')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('START')
          .onClick(() => {
            this.align = CalendarAlign.START
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('CENTER')
          .onClick(() => {
            this.align = CalendarAlign.CENTER
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('END')
          .onClick(() => {
            this.align = CalendarAlign.END
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换对齐方式')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample005: 设置日期范围
 */
@Component
export struct CalendarPickerExample005 {
  private selectedDate: Date = new Date('2024-03-05')

  build() {
    Column() {
      Text('设置日期范围')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({
        hintRadius: 10,
        selected: this.selectedDate,
        startYear: 2020,
        startMonth: 1,
        endYear: 2030,
        endMonth: 12
      })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('提示: 日期范围限制在 2020年1月 到 2030年12月')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample006: 设置背景色
 */
@Component
export struct CalendarPickerExample006 {
  private selectedDate: Date = new Date('2024-03-05')
  @State bgColor: string = '#F1F3F5'

  build() {
    Column() {
      Text('设置背景色')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .backgroundColor(this.bgColor)
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('背景色设置')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('灰色')
          .onClick(() => {
            this.bgColor = '#F1F3F5'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('浅蓝')
          .onClick(() => {
            this.bgColor = '#E3F2FD'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('浅绿')
          .onClick(() => {
            this.bgColor = '#E8F5E9'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换背景色')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * CalendarPickerExample007: 设置提示圆角
 */
@Component
export struct CalendarPickerExample007 {
  private selectedDate: Date = new Date('2024-03-05')
  @State hintRadius: number = 10

  build() {
    Column() {
      Text('设置提示圆角')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: this.hintRadius, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('提示圆角: ' + this.hintRadius)
        .fontSize(16)
        .margin({ top: 20 })

      Row() {
        Button('0')
          .onClick(() => {
            this.hintRadius = 0
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('10')
          .onClick(() => {
            this.hintRadius = 10
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('20')
          .onClick(() => {
            this.hintRadius = 20
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换提示圆角')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
