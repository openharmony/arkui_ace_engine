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
 * CalendarPickerExample001: 禁用日期范围
 * 演示如何设置禁用的日期范围
 */
@Component
export struct CalendarPickerExample001 {
  private disabledDateRange: DateRange[] = [
    { start: new Date('2025-01-01'), end: new Date('2025-01-02') },
    { start: new Date('2025-01-09'), end: new Date('2025-01-10') },
    { start: new Date('2025-01-15'), end: new Date('2025-01-16') },
    { start: new Date('2025-01-19'), end: new Date('2025-01-19') },
    { start: new Date('2025-01-22'), end: new Date('2025-01-25') }
  ]

  build() {
    Column() {
      Text('禁用日期范围')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .margin(10)
        .markToday(true)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('提示: 灰色日期为禁用日期')
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
 * CalendarPickerExample002: 标记今天
 * 演示如何标记今天的日期
 */
@Component
export struct CalendarPickerExample002 {
  private selectedDate: Date = Date.now()

  build() {
    Column() {
      Text('标记今天')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ hintRadius: 6, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.END)
        .margin(10)
        .onChange((value) => {
          console.info(`CalendarPicker onChange: ${value.toString()}`)
        })
        .responseRegion({ x: 0, y: 0, width: '100%', height: '100%' })
        .markToday(true)
        .align(Alignment.TopStart)

      Text('提示: 今天的日期会被高亮标记')
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
 * CalendarPickerExample003: 动态切换禁用日期
 * 演示如何动态修改禁用的日期范围
 */
@Component
export struct CalendarPickerExample003 {
  @State disabledDateRange: DateRange[] = []
  @State mode: string = '工作日'

  build() {
    Column() {
      Text('动态切换禁用日期')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .margin(10)
        .markToday(true)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('当前模式: ' + this.mode)
        .fontSize(16)
        .margin({ top: 20 })

      Text('禁用模式')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('工作日')
          .onClick(() => {
            this.mode = '工作日'
            this.disabledDateRange = this.getWeekdayDisabled()
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('周末')
          .onClick(() => {
            this.mode = '周末'
            this.disabledDateRange = this.getWeekendDisabled()
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('全部')
          .onClick(() => {
            this.mode = '全部'
            this.disabledDateRange = []
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换禁用模式')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  getWeekdayDisabled(): DateRange[] {
    let ranges: DateRange[] = []
    let date = new Date()
    let year = date.getFullYear()
    let month = date.getMonth()
    let daysInMonth = new Date(year, month + 1, 0).getDate()

    for (let day = 1; day <= daysInMonth; day++) {
      let currentDate = new Date(year, month, day)
      let dayOfWeek = currentDate.getDay()
      if (dayOfWeek === 0 || dayOfWeek === 6) {
        ranges.push({ start: new Date(year, month, day), end: new Date(year, month, day) })
      }
    }
    return ranges
  }

  getWeekendDisabled(): DateRange[] {
    let ranges: DateRange[] = []
    let date = new Date()
    let year = date.getFullYear()
    let month = date.getMonth()
    let daysInMonth = new Date(year, month + 1, 0).getDate()

    for (let day = 1; day <= daysInMonth; day++) {
      let currentDate = new Date(year, month, day)
      let dayOfWeek = currentDate.getDay()
      if (dayOfWeek !== 0 && dayOfWeek !== 6) {
        ranges.push({ start: new Date(year, month, day), end: new Date(year, month, day) })
      }
    }
    return ranges
  }
}

/**
 * CalendarPickerExample004: 设置响应区域
 * 演示如何设置日历选择器的响应区域
 */
@Component
export struct CalendarPickerExample004 {
  private selectedDate: Date = new Date('2024-08-05')
  @State responseRegionEnabled: boolean = true

  build() {
    Column() {
      Text('设置响应区域')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.responseRegionEnabled) {
        CalendarPicker({ hintRadius: 6, selected: this.selectedDate })
          .edgeAlign(CalendarAlign.END)
          .margin(10)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
          .responseRegion({ x: 0, y: 0, width: '100%', height: '100%' })
          .markToday(true)
          .align(Alignment.TopStart)
      } else {
        CalendarPicker({ hintRadius: 6, selected: this.selectedDate })
          .edgeAlign(CalendarAlign.END)
          .margin(10)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
          .markToday(true)
          .align(Alignment.TopStart)
      }

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.responseRegionEnabled = isOn
          })
        Text('responseRegion').fontSize(16)
      }
      .width('100%')
      .margin({ top: 20 })

      Text('提示: 切换开关来启用/禁用响应区域')
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
 * CalendarPickerExample005: 组合使用禁用日期和标记今天
 * 演示同时使用禁用日期和标记今天功能
 */
@Component
export struct CalendarPickerExample005 {
  @State disabledDateRange: DateRange[] = []
  @State markToday: boolean = true

  build() {
    Column() {
      Text('组合使用禁用日期和标记今天')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .margin(10)
        .markToday(this.markToday)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.markToday = isOn
          })
        Text('markToday').fontSize(16)
      }
      .width('100%')
      .margin({ top: 20 })

      Text('禁用本月前三天')
        .fontSize(14)
        .margin({ top: 20 })

      Button('设置禁用日期')
        .onClick(() => {
          let date = new Date()
          let year = date.getFullYear()
          let month = date.getMonth()
          this.disabledDateRange = [
            { start: new Date(year, month, 1), end: new Date(year, month, 3) }
          ]
        })
        .fontSize(14)
        .height(35)
        .width(150)
        .margin({ top: 10 })

      Button('清除禁用日期')
        .onClick(() => {
          this.disabledDateRange = []
        })
        .fontSize(14)
        .height(35)
        .width(150)
        .margin({ top: 10 })

      Text('提示: 切换开关和按钮来测试功能')
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
 * CalendarPickerExample006: 自定义禁用日期范围
 * 演示如何自定义禁用日期范围
 */
@Component
export struct CalendarPickerExample006 {
  @State disabledDateRange: DateRange[] = []
  @State rangeDesc: string = '当前禁用范围: 无'

  build() {
    Column() {
      Text('自定义禁用日期范围')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .margin(10)
        .markToday(true)
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
        Button('前5天')
          .onClick(() => {
            let date = new Date()
            let year = date.getFullYear()
            let month = date.getMonth()
            this.disabledDateRange = [
              { start: new Date(year, month, 1), end: new Date(year, month, 5) }
            ]
            this.rangeDesc = '当前禁用范围: 本月前5天'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('后5天')
          .onClick(() => {
            let date = new Date()
            let year = date.getFullYear()
            let month = date.getMonth()
            let daysInMonth = new Date(year, month + 1, 0).getDate()
            this.disabledDateRange = [
              { start: new Date(year, month, daysInMonth - 4), end: new Date(year, month, daysInMonth) }
            ]
            this.rangeDesc = '当前禁用范围: 本月后5天'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('每周三')
          .onClick(() => {
            this.disabledDateRange = this.getEveryWednesday()
            this.rangeDesc = '当前禁用范围: 每周三'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Button('清除')
        .onClick(() => {
          this.disabledDateRange = []
          this.rangeDesc = '当前禁用范围: 无'
        })
        .fontSize(12)
        .height(30)
        .width(80)
        .margin({ top: 10 })

      Text('提示: 点击按钮设置不同的禁用范围')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  getEveryWednesday(): DateRange[] {
    let ranges: DateRange[] = []
    let date = new Date()
    let year = date.getFullYear()
    let month = date.getMonth()
    let daysInMonth = new Date(year, month + 1, 0).getDate()

    for (let day = 1; day <= daysInMonth; day++) {
      let currentDate = new Date(year, month, day)
      let dayOfWeek = currentDate.getDay()
      if (dayOfWeek === 3) {
        ranges.push({ start: new Date(year, month, day), end: new Date(year, month, day) })
      }
    }
    return ranges
  }
}

/**
 * CalendarPickerExample007: 多个禁用日期范围
 * 演示如何设置多个不连续的禁用日期范围
 */
@Component
export struct CalendarPickerExample007 {
  @State disabledDateRange: DateRange[] = []
  @State rangeCount: number = 0

  build() {
    Column() {
      Text('多个禁用日期范围')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .margin(10)
        .markToday(true)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('当前禁用范围数量: ' + this.rangeCount)
        .fontSize(16)
        .margin({ top: 20 })

      Text('添加禁用范围')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('添加1天')
          .onClick(() => {
            this.addDisabledRange(1)
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('添加3天')
          .onClick(() => {
            this.addDisabledRange(3)
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('添加5天')
          .onClick(() => {
            this.addDisabledRange(5)
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Button('清除所有')
        .onClick(() => {
          this.disabledDateRange = []
          this.rangeCount = 0
        })
        .fontSize(12)
        .height(30)
        .width(80)
        .margin({ top: 10 })

      Text('提示: 点击按钮添加多个禁用范围')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  addDisabledRange(days: number) {
    let date = new Date()
    let year = date.getFullYear()
    let month = date.getMonth()
    let randomDay = Math.floor(Math.random() * 28) + 1
    let endDay = Math.min(randomDay + days - 1, 28)
    this.disabledDateRange.push({
      start: new Date(year, month, randomDay),
      end: new Date(year, month, endDay)
    })
    this.rangeCount = this.disabledDateRange.length
  }
}

/**
 * CalendarPickerExample008: 禁用日期与样式组合
 * 演示禁用日期与各种样式属性的组合使用
 */
@Component
export struct CalendarPickerExample008 {
  @State disabledDateRange: DateRange[] = []
  @State textColor: string = '#ff182431'
  @State bgColor: string = '#F1F3F5'
  @State align: CalendarAlign = CalendarAlign.END

  build() {
    Column() {
      Text('禁用日期与样式组合')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      CalendarPicker({ disabledDateRange: this.disabledDateRange })
        .edgeAlign(this.align)
        .textStyle({ color: this.textColor, font: { size: 20, weight: FontWeight.Normal } })
        .backgroundColor(this.bgColor)
        .margin(10)
        .markToday(true)
        .onChange((value) => {
          console.info('CalendarPicker onChange:' + JSON.stringify(value))
        })

      Text('样式设置')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('蓝色主题')
          .onClick(() => {
            this.textColor = '#ff1565C0'
            this.bgColor = '#E3F2FD'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('绿色主题')
          .onClick(() => {
            this.textColor = '#ff2E7D32'
            this.bgColor = '#E8F5E9'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('默认主题')
          .onClick(() => {
            this.textColor = '#ff182431'
            this.bgColor = '#F1F3F5'
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('START')
          .onClick(() => {
            this.align = CalendarAlign.START
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('CENTER')
          .onClick(() => {
            this.align = CalendarAlign.CENTER
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)

        Button('END')
          .onClick(() => {
            this.align = CalendarAlign.END
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Button('设置禁用日期')
        .onClick(() => {
          let date = new Date()
          let year = date.getFullYear()
          let month = date.getMonth()
          this.disabledDateRange = [
            { start: new Date(year, month, 10), end: new Date(year, month, 15) }
          ]
        })
        .fontSize(12)
        .height(30)
        .width(150)
        .margin({ top: 10 })

      Text('提示: 组合使用禁用日期和样式属性')
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
 * CalendarPickerExample009: 响应区域与禁用日期
 * 演示响应区域与禁用日期的组合使用
 */
@Component
export struct CalendarPickerExample009 {
  private selectedDate: Date = new Date('2024-08-05')
  @State disabledDateRange: DateRange[] = []
  @State responseRegionEnabled: boolean = true
  @State markToday: boolean = true

  build() {
    Column() {
      Text('响应区域与禁用日期')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.responseRegionEnabled) {
        CalendarPicker({ hintRadius: 6, selected: this.selectedDate, disabledDateRange: this.disabledDateRange })
          .edgeAlign(CalendarAlign.END)
          .margin(10)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
          .responseRegion({ x: 0, y: 0, width: '100%', height: '100%' })
          .markToday(this.markToday)
          .align(Alignment.TopStart)
      } else {
        CalendarPicker({ hintRadius: 6, selected: this.selectedDate, disabledDateRange: this.disabledDateRange })
          .edgeAlign(CalendarAlign.END)
          .margin(10)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
          .markToday(this.markToday)
          .align(Alignment.TopStart)
      }

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.responseRegionEnabled = isOn
          })
        Text('responseRegion').fontSize(16)
      }
      .width('100%')
      .margin({ top: 20 })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.markToday = isOn
          })
        Text('markToday').fontSize(16)
      }
      .width('100%')
      .margin({ top: 10 })

      Button('设置禁用日期')
        .onClick(() => {
          let date = new Date()
          let year = date.getFullYear()
          let month = date.getMonth()
          this.disabledDateRange = [
            { start: new Date(year, month, 5), end: new Date(year, month, 10) }
          ]
        })
        .fontSize(12)
        .height(30)
        .width(150)
        .margin({ top: 10 })

      Text('提示: 测试响应区域、标记今天和禁用日期的组合')
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
 * CalendarPickerExample010: 完整功能演示
 * 演示CalendarPicker的所有功能组合
 */
@Component
export struct CalendarPickerExample010 {
  @State selectedDate: Date = new Date('2024-08-05')
  @State disabledDateRange: DateRange[] = []
  @State markToday: boolean = true
  @State responseRegionEnabled: boolean = true
  @State textColor: string = '#ff182431'
  @State fontSize: number = 20
  @State align: CalendarAlign = CalendarAlign.END
  @State bgColor: string = '#F1F3F5'
  @State hintRadius: number = 6

  build() {
    Column() {
      Text('完整功能演示')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.responseRegionEnabled) {
        CalendarPicker({
          hintRadius: this.hintRadius,
          selected: this.selectedDate,
          disabledDateRange: this.disabledDateRange
        })
          .edgeAlign(this.align)
          .textStyle({ color: this.textColor, font: { size: this.fontSize, weight: FontWeight.Normal } })
          .backgroundColor(this.bgColor)
          .margin(10)
          .responseRegion({ x: 0, y: 0, width: '100%', height: '100%' })
          .markToday(this.markToday)
          .align(Alignment.TopStart)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
      } else {
        CalendarPicker({
          hintRadius: this.hintRadius,
          selected: this.selectedDate,
          disabledDateRange: this.disabledDateRange
        })
          .edgeAlign(this.align)
          .textStyle({ color: this.textColor, font: { size: this.fontSize, weight: FontWeight.Normal } })
          .backgroundColor(this.bgColor)
          .margin(10)
          .markToday(this.markToday)
          .align(Alignment.TopStart)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`)
          })
      }

      Text('功能开关')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.responseRegionEnabled = isOn
          })
        Text('responseRegion').fontSize(14)
      }
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.markToday = isOn
          })
        Text('markToday').fontSize(14)
      }
      .width('100%')
      .margin({ top: 10 })

      Text('样式设置')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('默认')
          .onClick(() => {
            this.textColor = '#ff182431'
            this.fontSize = 20
            this.bgColor = '#F1F3F5'
            this.align = CalendarAlign.END
            this.hintRadius = 6
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin(2)

        Button('蓝色')
          .onClick(() => {
            this.textColor = '#ff1565C0'
            this.fontSize = 22
            this.bgColor = '#E3F2FD'
            this.align = CalendarAlign.CENTER
            this.hintRadius = 8
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin(2)

        Button('绿色')
          .onClick(() => {
            this.textColor = '#ff2E7D32'
            this.fontSize = 22
            this.bgColor = '#E8F5E9'
            this.align = CalendarAlign.START
            this.hintRadius = 8
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin(2)
      }
      .width('100%')
      .margin({ top: 10 })

      Button('设置禁用日期')
        .onClick(() => {
          let date = new Date()
          let year = date.getFullYear()
          let month = date.getMonth()
          this.disabledDateRange = [
            { start: new Date(year, month, 8), end: new Date(year, month, 12) },
            { start: new Date(year, month, 18), end: new Date(year, month, 22) }
          ]
        })
        .fontSize(12)
        .height(30)
        .width(150)
        .margin({ top: 10 })

      Button('清除禁用日期')
        .onClick(() => {
          this.disabledDateRange = []
        })
        .fontSize(12)
        .height(30)
        .width(150)
        .margin({ top: 10 })

      Text('提示: 演示所有功能的组合使用')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
