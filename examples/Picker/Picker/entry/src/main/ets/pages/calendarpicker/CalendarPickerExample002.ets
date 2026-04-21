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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * CalendarPickerExample001: 动态切换日期范围
 * 演示如何动态修改日历选择器的日期范围
 */
@Component
export struct CalendarPickerExample001 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State startYear: number = 2020
  @State startMonth: number = 1
  @State endYear: number = 2030
  @State endMonth: number = 12
  @State rangeDesc: string = '当前范围: 2020年1月 - 2030年12月'

  build() {
    Column() {
      Text('动态切换日期范围')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({
        hintRadius: 10,
        selected: this.selectedDate,
        startYear: this.startYear,
        startMonth: this.startMonth,
        endYear: this.endYear,
        endMonth: this.endMonth
      })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.rangeDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('预设范围')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('近十年')
          .onClick(() => {
            let currentYear = new Date().getFullYear()
            this.startYear = currentYear - 10
            this.startMonth = 1
            this.endYear = currentYear
            this.endMonth = 12
            this.rangeDesc = '当前范围: ' + this.startYear + '年1月 - ' + this.endYear + '年12月'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('近五年')
          .onClick(() => {
            let currentYear = new Date().getFullYear()
            this.startYear = currentYear - 5
            this.startMonth = 1
            this.endYear = currentYear
            this.endMonth = 12
            this.rangeDesc = '当前范围: ' + this.startYear + '年1月 - ' + this.endYear + '年12月'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('今年')
          .onClick(() => {
            let currentYear = new Date().getFullYear()
            this.startYear = currentYear
            this.startMonth = 1
            this.endYear = currentYear
            this.endMonth = 12
            this.rangeDesc = '当前范围: ' + this.startYear + '年1月 - ' + this.endYear + '年12月'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换日期范围')
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
 * CalendarPickerExample002: 动态切换样式
 * 演示如何动态修改日历选择器的文本样式
 */
@Component
export struct CalendarPickerExample002 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State textColor: string = '#ff182431'
  @State fontSize: number = 20
  @State fontWeight: number = FontWeight.Normal
  @State styleDesc: string = '当前样式: 默认'

  build() {
    Column() {
      Text('动态切换样式')
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

      Text(this.styleDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('文本颜色')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('黑色')
          .onClick(() => {
            this.textColor = '#ff182431'
            this.styleDesc = '当前样式: 黑色'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('红色')
          .onClick(() => {
            this.textColor = '#ff000000'
            this.styleDesc = '当前样式: 红色'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('蓝色')
          .onClick(() => {
            this.textColor = '#ff0000ff'
            this.styleDesc = '当前样式: 蓝色'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('字体大小')
        .fontSize(14)
        .margin({ top: 10 })

      Row() {
        Button('16')
          .onClick(() => {
            this.fontSize = 16
            this.styleDesc = '当前样式: 字体大小16'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('20')
          .onClick(() => {
            this.fontSize = 20
            this.styleDesc = '当前样式: 字体大小20'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('24')
          .onClick(() => {
            this.fontSize = 24
            this.styleDesc = '当前样式: 字体大小24'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('字体粗细')
        .fontSize(14)
        .margin({ top: 10 })

      Row() {
        Button('正常')
          .onClick(() => {
            this.fontWeight = FontWeight.Normal
            this.styleDesc = '当前样式: 正常粗细'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('加粗')
          .onClick(() => {
            this.fontWeight = FontWeight.Bold
            this.styleDesc = '当前样式: 加粗'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('更粗')
          .onClick(() => {
            this.fontWeight = FontWeight.Bolder
            this.styleDesc = '当前样式: 更粗'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换样式')
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
 * CalendarPickerExample003: 动态切换对齐方式
 * 演示如何动态修改日历选择器的对齐方式
 */
@Component
export struct CalendarPickerExample003 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State align: CalendarAlign = CalendarAlign.END
  @State alignDesc: string = '当前对齐: END'

  build() {
    Column() {
      Text('动态切换对齐方式')
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

      Text(this.alignDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('对齐方式')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('START')
          .onClick(() => {
            this.align = CalendarAlign.START
            this.alignDesc = '当前对齐: START'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('CENTER')
          .onClick(() => {
            this.align = CalendarAlign.CENTER
            this.alignDesc = '当前对齐: CENTER'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('END')
          .onClick(() => {
            this.align = CalendarAlign.END
            this.alignDesc = '当前对齐: END'
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
 * CalendarPickerExample004: 多个日历选择器联动
 * 演示两个日历选择器的联动效果
 */
@Component
export struct CalendarPickerExample004 {
  @State startDate: Date = new Date('2024-03-01')
  @State endDate: Date = new Date('2024-03-31')
  @State dateRange: string = '日期范围: 2024-03-01 至 2024-03-31'

  build() {
    Column() {
      Text('多个日历选择器联动')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('开始日期')
        .fontSize(16)
        .margin({ top: 10 })

      CalendarPicker({ hintRadius: 10, selected: this.startDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          this.startDate = new Date(value.year, value.month - 1, value.day)
          this.updateDateRange()
          console.info('Start date onChange:' + JSON.stringify(value))
        })

      Text('结束日期')
        .fontSize(16)
        .margin({ top: 10 })

      CalendarPicker({ hintRadius: 10, selected: this.endDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          this.endDate = new Date(value.year, value.month - 1, value.day)
          this.updateDateRange()
          console.info('End date onChange:' + JSON.stringify(value))
        })

      Text(this.dateRange)
        .fontSize(16)
        .margin({ top: 20 })

      Button('重置日期')
        .onClick(() => {
          this.startDate = new Date('2024-03-01')
          this.endDate = new Date('2024-03-31')
          this.updateDateRange()
        })
        .fontSize(14)
        .height(35)
        .width(150)
        .margin({ top: 10 })

      Text('提示: 选择开始日期和结束日期')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  updateDateRange() {
    let startStr = this.startDate.getFullYear() + '-' +
      (this.startDate.getMonth() + 1).toString().padStart(2, '0') + '-' +
      this.startDate.getDate().toString().padStart(2, '0')
    let endStr = this.endDate.getFullYear() + '-' +
      (this.endDate.getMonth() + 1).toString().padStart(2, '0') + '-' +
      this.endDate.getDate().toString().padStart(2, '0')
    this.dateRange = '日期范围: ' + startStr + ' 至 ' + endStr
  }
}

/**
 * CalendarPickerExample005: 动态切换主题
 * 演示如何动态切换日历选择器的主题样式
 */
@Component
export struct CalendarPickerExample005 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State theme: string = 'default'
  @State bgColor: string = '#F1F3F5'
  @State textColor: string = '#ff182431'
  @State fontSize: number = 20
  @State themeDesc: string = '当前主题: 默认'

  build() {
    Column() {
      Text('动态切换主题')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: this.textColor, font: { size: this.fontSize, weight: FontWeight.Normal } })
        .backgroundColor(this.bgColor)
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.themeDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('主题切换')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('默认')
          .onClick(() => {
            this.theme = 'default'
            this.bgColor = '#F1F3F5'
            this.textColor = '#ff182431'
            this.fontSize = 20
            this.themeDesc = '当前主题: 默认'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('浅蓝')
          .onClick(() => {
            this.theme = 'lightBlue'
            this.bgColor = '#E3F2FD'
            this.textColor = '#ff1565C0'
            this.fontSize = 22
            this.themeDesc = '当前主题: 浅蓝'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('浅绿')
          .onClick(() => {
            this.theme = 'lightGreen'
            this.bgColor = '#E8F5E9'
            this.textColor = '#ff2E7D32'
            this.fontSize = 22
            this.themeDesc = '当前主题: 浅绿'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('浅紫')
          .onClick(() => {
            this.theme = 'lightPurple'
            this.bgColor = '#F3E5F5'
            this.textColor = '#ff7B1FA2'
            this.fontSize = 22
            this.themeDesc = '当前主题: 浅紫'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('浅橙')
          .onClick(() => {
            this.theme = 'lightOrange'
            this.bgColor = '#FFF3E0'
            this.textColor = '#ffE65100'
            this.fontSize = 22
            this.themeDesc = '当前主题: 浅橙'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('深色')
          .onClick(() => {
            this.theme = 'dark'
            this.bgColor = '#424242'
            this.textColor = '#ffFFFFFF'
            this.fontSize = 24
            this.themeDesc = '当前主题: 深色'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换主题')
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
 * CalendarPickerExample006: 复杂的表单场景
 * 演示在表单中使用日历选择器的场景
 */
@Component
export struct CalendarPickerExample006 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State name: string = ''
  @State email: string = ''
  @State phone: string = ''
  @State desc: string = ''
  @State submitInfo: string = ''

  build() {
    Column() {
      Text('复杂的表单场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('姓名')
        .fontSize(16)
        .margin({ top: 10 })

      TextInput({ placeholder: '请输入姓名', text: this.name })
        .width('100%')
        .height(40)
        .onChange((value: string) => {
          this.name = value
        })

      Text('邮箱')
        .fontSize(16)
        .margin({ top: 10 })

      TextInput({ placeholder: '请输入邮箱', text: this.email })
        .width('100%')
        .height(40)
        .onChange((value: string) => {
          this.email = value
        })

      Text('电话')
        .fontSize(16)
        .margin({ top: 10 })

      TextInput({ placeholder: '请输入电话', text: this.phone })
        .width('100%')
        .height(40)
        .onChange((value: string) => {
          this.phone = value
        })

      Text('预约日期')
        .fontSize(16)
        .margin({ top: 10 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('描述')
        .fontSize(16)
        .margin({ top: 10 })

      TextInput({ placeholder: '请输入描述', text: this.desc })
        .width('100%')
        .height(80)
        .type(InputType.TextArea)
        .onChange((value: string) => {
          this.desc = value
        })

      Button('提交')
        .onClick(() => {
          let dateStr = this.selectedDate.getFullYear() + '-' +
            (this.selectedDate.getMonth() + 1).toString().padStart(2, '0') + '-' +
            this.selectedDate.getDate().toString().padStart(2, '0')
          this.submitInfo = '姓名: ' + this.name + '\n邮箱: ' + this.email +
            '\n电话: ' + this.phone + '\n日期: ' + dateStr + '\n描述: ' + this.desc
        })
        .fontSize(16)
        .height(40)
        .width(150)
        .margin({ top: 20 })

      if (this.submitInfo !== '') {
        Text(this.submitInfo)
          .fontSize(14)
          .margin({ top: 20 })
      }

      Text('提示: 填写表单并提交')
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
 * CalendarPickerExample007: 预设日期选择
 * 演示快速选择预设日期的功能
 */
@Component
export struct CalendarPickerExample007 {
  @State selectedDate: Date = new Date()
  @State presetDesc: string = '当前日期: 今天'

  build() {
    Column() {
      Text('预设日期选择')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.presetDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('快速选择')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('今天')
          .onClick(() => {
            this.selectedDate = new Date()
            this.presetDesc = '当前日期: 今天'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('明天')
          .onClick(() => {
            let tomorrow = new Date()
            tomorrow.setDate(tomorrow.getDate() + 1)
            this.selectedDate = tomorrow
            this.presetDesc = '当前日期: 明天'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('后天')
          .onClick(() => {
            let dayAfterTomorrow = new Date()
            dayAfterTomorrow.setDate(dayAfterTomorrow.getDate() + 2)
            this.selectedDate = dayAfterTomorrow
            this.presetDesc = '当前日期: 后天'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('下周一')
          .onClick(() => {
            let date = new Date()
            let day = date.getDay()
            let diff = day === 0 ? 1 : 8 - day
            date.setDate(date.getDate() + diff)
            this.selectedDate = date
            this.presetDesc = '当前日期: 下周一'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('下周三')
          .onClick(() => {
            let date = new Date()
            let day = date.getDay()
            let diff = day === 0 ? 3 : 10 - day
            date.setDate(date.getDate() + diff)
            this.selectedDate = date
            this.presetDesc = '当前日期: 下周三'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('下周五')
          .onClick(() => {
            let date = new Date()
            let day = date.getDay()
            let diff = day === 0 ? 5 : 12 - day
            date.setDate(date.getDate() + diff)
            this.selectedDate = date
            this.presetDesc = '当前日期: 下周五'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('下月1号')
          .onClick(() => {
            let date = new Date()
            date.setMonth(date.getMonth() + 1)
            date.setDate(1)
            this.selectedDate = date
            this.presetDesc = '当前日期: 下月1号'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('明年1月')
          .onClick(() => {
            let date = new Date()
            date.setFullYear(date.getFullYear() + 1)
            date.setMonth(0)
            date.setDate(1)
            this.selectedDate = date
            this.presetDesc = '当前日期: 明年1月'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('今年生日')
          .onClick(() => {
            let date = new Date()
            date.setMonth(11)
            date.setDate(25)
            this.selectedDate = date
            this.presetDesc = '当前日期: 今年生日'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮快速选择日期')
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
 * CalendarPickerExample008: 动态切换提示圆角
 * 演示如何动态修改日历选择器的提示圆角
 */
@Component
export struct CalendarPickerExample008 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State hintRadius: number = 10
  @State radiusDesc: string = '当前圆角: 10'

  build() {
    Column() {
      Text('动态切换提示圆角')
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

      Text(this.radiusDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('圆角大小')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('0')
          .onClick(() => {
            this.hintRadius = 0
            this.radiusDesc = '当前圆角: 0'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('5')
          .onClick(() => {
            this.hintRadius = 5
            this.radiusDesc = '当前圆角: 5'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('10')
          .onClick(() => {
            this.hintRadius = 10
            this.radiusDesc = '当前圆角: 10'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('15')
          .onClick(() => {
            this.hintRadius = 15
            this.radiusDesc = '当前圆角: 15'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('20')
          .onClick(() => {
            this.hintRadius = 20
            this.radiusDesc = '当前圆角: 20'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('25')
          .onClick(() => {
            this.hintRadius = 25
            this.radiusDesc = '当前圆角: 25'
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

/**
 * CalendarPickerExample009: 多状态管理
 * 演示如何管理日历选择器的多个状态
 */
@Component
export struct CalendarPickerExample009 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State isEditing: boolean = false
  @State isSaved: boolean = false
  @State saveHistory: string[] = []
  @State currentStatus: string = '状态: 浏览中'

  build() {
    Column() {
      Text('多状态管理')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text(this.currentStatus)
        .fontSize(16)
        .margin({ top: 10 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          if (!this.isEditing) {
            this.isEditing = true
            this.currentStatus = '状态: 编辑中'
          }
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Row() {
        Button('保存')
          .onClick(() => {
            if (this.isEditing) {
              let dateStr = this.selectedDate.getFullYear() + '-' +
                (this.selectedDate.getMonth() + 1).toString().padStart(2, '0') + '-' +
                this.selectedDate.getDate().toString().padStart(2, '0')
              this.saveHistory.push(dateStr)
              this.isEditing = false
              this.isSaved = true
              this.currentStatus = '状态: 已保存'
            }
          })
          .fontSize(14)
          .height(35)
          .width(100)
          .margin(5)

        Button('取消')
          .onClick(() => {
            this.isEditing = false
            this.currentStatus = '状态: 浏览中'
          })
          .fontSize(14)
          .height(35)
          .width(100)
          .margin(5)

        Button('清空历史')
          .onClick(() => {
            this.saveHistory = []
            this.isSaved = false
            this.currentStatus = '状态: 浏览中'
          })
          .fontSize(14)
          .height(35)
          .width(100)
          .margin(5)
      }
      .width('100%')
      .margin({ top: 20 })

      if (this.saveHistory.length > 0) {
        Text('保存历史')
          .fontSize(16)
          .margin({ top: 20 })

        ForEach(this.saveHistory, (item: string, index: number) => {
          Text((index + 1) + '. ' + item)
            .fontSize(14)
            .margin({ top: 5 })
        })
      }

      Text('提示: 选择日期后保存到历史记录')
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
 * CalendarPickerExample010: 复杂的布局场景
 * 演示在复杂布局中使用日历选择器
 */
@Component
export struct CalendarPickerExample010 {
  @State selectedDate1: Date = new Date('2024-03-05')
  @State selectedDate2: Date = new Date('2024-03-15')
  @State selectedDate3: Date = new Date('2024-03-25')
  @State layoutMode: string = 'vertical'

  build() {
    Column() {
      Text('复杂的布局场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin(20)

      Row() {
        Button('垂直布局')
          .onClick(() => {
            this.layoutMode = 'vertical'
          })
          .fontSize(12)
          .height(30)
          .width(100)
          .margin(5)

        Button('水平布局')
          .onClick(() => {
            this.layoutMode = 'horizontal'
          })
          .fontSize(12)
          .height(30)
          .width(100)
          .margin(5)
      }
      .width('100%')
      .margin({ bottom: 20 })

      if (this.layoutMode === 'vertical') {
        Column() {
          Text('日历选择器 1')
            .fontSize(16)
            .margin({ top: 10 })

          CalendarPicker({ hintRadius: 10, selected: this.selectedDate1 })
            .edgeAlign(CalendarAlign.END)
            .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
            .margin(10)
            .onChange((value) => {
              console.info('CalendarPicker 1 onChange:' + JSON.stringify(value))
            })

          Text('日历选择器 2')
            .fontSize(16)
            .margin({ top: 10 })

          CalendarPicker({ hintRadius: 10, selected: this.selectedDate2 })
            .edgeAlign(CalendarAlign.END)
            .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
            .margin(10)
            .onChange((value) => {
              console.info('CalendarPicker 2 onChange:' + JSON.stringify(value))
            })

          Text('日历选择器 3')
            .fontSize(16)
            .margin({ top: 10 })

          CalendarPicker({ hintRadius: 10, selected: this.selectedDate3 })
            .edgeAlign(CalendarAlign.END)
            .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
            .margin(10)
            .onChange((value) => {
              console.info('CalendarPicker 3 onChange:' + JSON.stringify(value))
            })
        }
        .width('100%')
      } else {
        Row() {
          Column() {
            Text('日历选择器 1')
              .fontSize(16)
              .margin({ top: 10 })

            CalendarPicker({ hintRadius: 10, selected: this.selectedDate1 })
              .edgeAlign(CalendarAlign.END)
              .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
              .margin(10)
              .onChange((value) => {
                console.info('CalendarPicker 1 onChange:' + JSON.stringify(value))
              })
          }
          .width('33%')

          Column() {
            Text('日历选择器 2')
              .fontSize(16)
              .margin({ top: 10 })

            CalendarPicker({ hintRadius: 10, selected: this.selectedDate2 })
              .edgeAlign(CalendarAlign.END)
              .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
              .margin(10)
              .onChange((value) => {
                console.info('CalendarPicker 2 onChange:' + JSON.stringify(value))
              })
          }
          .width('33%')

          Column() {
            Text('日历选择器 3')
              .fontSize(16)
              .margin({ top: 10 })

            CalendarPicker({ hintRadius: 10, selected: this.selectedDate3 })
              .edgeAlign(CalendarAlign.END)
              .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
              .margin(10)
              .onChange((value) => {
                console.info('CalendarPicker 3 onChange:' + JSON.stringify(value))
              })
          }
          .width('33%')
        }
        .width('100%')
      }

      Text('提示: 切换布局模式查看不同效果')
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
 * CalendarPickerExample011: 日期验证场景
 * 演示日期选择时的验证逻辑
 */
@Component
export struct CalendarPickerExample011 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State minDate: Date = new Date('2024-03-01')
  @State maxDate: Date = new Date('2024-03-31')
  @State validationMsg: string = '日期有效'
  @State isValid: boolean = true

  build() {
    Column() {
      Text('日期验证场景')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .textStyle({ color: '#ff182431', font: { size: 20, weight: FontWeight.Normal } })
        .margin(10)
        .onChange((value) => {
          this.selectedDate = new Date(value.year, value.month - 1, value.day)
          this.validateDate()
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.validationMsg)
        .fontSize(16)
        .fontColor(this.isValid ? '#2E7D32' : '#C62828')
        .margin({ top: 20 })

      Text('设置验证范围')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('本月')
          .onClick(() => {
            let date = new Date()
            this.minDate = new Date(date.getFullYear(), date.getMonth(), 1)
            this.maxDate = new Date(date.getFullYear(), date.getMonth() + 1, 0)
            this.validateDate()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('本周')
          .onClick(() => {
            let date = new Date()
            let day = date.getDay()
            let diff = date.getDate() - day + (day === 0 ? -6 : 1)
            this.minDate = new Date(date.getFullYear(), date.getMonth(), diff)
            this.maxDate = new Date(date.getFullYear(), date.getMonth(), diff + 6)
            this.validateDate()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('近30天')
          .onClick(() => {
            let date = new Date()
            this.minDate = new Date(date.getFullYear(), date.getMonth(), date.getDate() - 30)
            this.maxDate = new Date(date.getFullYear(), date.getMonth(), date.getDate())
            this.validateDate()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 设置验证范围后选择日期')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  validateDate() {
    if (this.selectedDate < this.minDate || this.selectedDate > this.maxDate) {
      this.validationMsg = '日期超出范围'
      this.isValid = false
    } else {
      this.validationMsg = '日期有效'
      this.isValid = true
    }
  }
}

/**
 * CalendarPickerExample012: 动态切换所有属性
 * 演示同时动态切换日历选择器的所有属性
 */
@Component
export struct CalendarPickerExample012 {
  @State selectedDate: Date = new Date('2024-03-05')
  @State startYear: number = 2020
  @State startMonth: number = 1
  @State endYear: number = 2030
  @State endMonth: number = 12
  @State align: CalendarAlign = CalendarAlign.END
  @State textColor: string = '#ff182431'
  @State fontSize: number = 20
  @State fontWeight: number = FontWeight.Normal
  @State bgColor: string = '#F1F3F5'
  @State hintRadius: number = 10
  @State configDesc: string = '配置: 默认'

  build() {
    Column() {
      Text('动态切换所有属性')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({
        hintRadius: this.hintRadius,
        selected: this.selectedDate,
        startYear: this.startYear,
        startMonth: this.startMonth,
        endYear: this.endYear,
        endMonth: this.endMonth
      })
        .edgeAlign(this.align)
        .textStyle({ color: this.textColor, font: { size: this.fontSize, weight: this.fontWeight } })
        .backgroundColor(this.bgColor)
        .margin(10)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text(this.configDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text('预设配置')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('默认')
          .onClick(() => {
            this.startYear = 2020
            this.startMonth = 1
            this.endYear = 2030
            this.endMonth = 12
            this.align = CalendarAlign.END
            this.textColor = '#ff182431'
            this.fontSize = 20
            this.fontWeight = FontWeight.Normal
            this.bgColor = '#F1F3F5'
            this.hintRadius = 10
            this.configDesc = '配置: 默认'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('紧凑')
          .onClick(() => {
            this.startYear = 2024
            this.startMonth = 1
            this.endYear = 2024
            this.endMonth = 12
            this.align = CalendarAlign.CENTER
            this.textColor = '#ff182431'
            this.fontSize = 16
            this.fontWeight = FontWeight.Normal
            this.bgColor = '#F1F3F5'
            this.hintRadius = 5
            this.configDesc = '配置: 紧凑'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('大字体')
          .onClick(() => {
            this.startYear = 2020
            this.startMonth = 1
            this.endYear = 2030
            this.endMonth = 12
            this.align = CalendarAlign.START
            this.textColor = '#ff182431'
            this.fontSize = 24
            this.fontWeight = FontWeight.Bold
            this.bgColor = '#F1F3F5'
            this.hintRadius = 10
            this.configDesc = '配置: 大字体'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('蓝色主题')
          .onClick(() => {
            this.startYear = 2020
            this.startMonth = 1
            this.endYear = 2030
            this.endMonth = 12
            this.align = CalendarAlign.END
            this.textColor = '#ff1565C0'
            this.fontSize = 20
            this.fontWeight = FontWeight.Normal
            this.bgColor = '#E3F2FD'
            this.hintRadius = 10
            this.configDesc = '配置: 蓝色主题'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('绿色主题')
          .onClick(() => {
            this.startYear = 2020
            this.startMonth = 1
            this.endYear = 2030
            this.endMonth = 12
            this.align = CalendarAlign.END
            this.textColor = '#ff2E7D32'
            this.fontSize = 20
            this.fontWeight = FontWeight.Normal
            this.bgColor = '#E8F5E9'
            this.hintRadius = 10
            this.configDesc = '配置: 绿色主题'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('紫色主题')
          .onClick(() => {
            this.startYear = 2020
            this.startMonth = 1
            this.endYear = 2030
            this.endMonth = 12
            this.align = CalendarAlign.END
            this.textColor = '#ff7B1FA2'
            this.fontSize = 20
            this.fontWeight = FontWeight.Normal
            this.bgColor = '#F3E5F5'
            this.hintRadius = 10
            this.configDesc = '配置: 紫色主题'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换预设配置')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
