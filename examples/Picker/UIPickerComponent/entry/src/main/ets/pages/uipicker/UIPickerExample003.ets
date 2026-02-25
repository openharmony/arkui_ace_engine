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

import { LengthMetrics } from '@kit.ArkUI'

/**
 * UIPickerExample003: 响应式布局选择器
 */
@Component
export struct UIPickerExample003 {
  private dataArray: string[] = []
  @State containerWidth: string = '70%'
  @State containerHeight: number = 200

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项' + i)
    }
  }

  build() {
    Column() {
      Text('响应式布局选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width(this.containerWidth)
      .height(this.containerHeight)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Text('宽度: ' + this.containerWidth + ', 高度: ' + this.containerHeight)
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('70%')
          .onClick(() => {
            this.containerWidth = '70%'
            this.containerHeight = 200
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin({ right: 10 })

        Button('80%')
          .onClick(() => {
            this.containerWidth = '80%'
            this.containerHeight = 220
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin({ right: 10 })

        Button('90%')
          .onClick(() => {
            this.containerWidth = '90%'
            this.containerHeight = 250
          })
          .fontSize(12)
          .height(30)
          .width(80)
      }
      .width('70%')
      .margin({ top: 10 })
      .justifyContent(FlexAlign.Center)

      Text('提示: 测试不同容器尺寸')
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
 * UIPickerExample004: 动画效果选择器
 */
@Component
export struct UIPickerExample004 {
  private dataArray: string[] = []
  @State enableHaptic: boolean = true

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项' + i)
    }
  }

  build() {
    Column() {
      Text('动画效果选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .enableHapticFeedback(this.enableHaptic)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Row() {
        Checkbox({ name: 'enableHaptic' })
          .select(this.enableHaptic)
          .onChange((value: boolean) => {
            this.enableHaptic = value
          })
          .margin({ right: 10 })

        Text('触觉反馈')
          .fontSize(14)
      }
      .margin({ top: 20 })

      Text('提示: 启用/禁用触觉反馈')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample005: 数据验证选择器
 */
@Component
export struct UIPickerExample005 {
  @State selectedAge: number = 25
  @State isValidAge: boolean = true
  @State validationMessage: string = ''
  private ages: number[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 120; i++) {
      this.ages.push(i)
    }
  }

  validateAge(age: number): boolean {
    if (age < 18) {
      this.validationMessage = '年龄必须大于等于18岁'
      return false
    } else if (age > 100) {
      this.validationMessage = '请确认年龄是否正确'
      return false
    }
    this.validationMessage = '年龄有效'
    return true
  }

  build() {
    Column() {
      Text('数据验证选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedAge - 1
      }) {
        ForEach(this.ages, (age: number) => {
          Text(age.toString())
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedAge = selectedIndex + 1
        this.isValidAge = this.validateAge(this.selectedAge)
      })

      Text('当前年龄: ' + this.selectedAge + ' 岁')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text(this.validationMessage)
        .fontSize(14)
        .fontColor(this.isValidAge ? '#4CAF50' : '#F44336')
        .margin({ top: 10 })

      Text('提示: 年龄必须18-100岁之间')
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
 * UIPickerExample006: 时间段选择器
 */
@Component
export struct UIPickerExample006 {
  @State selectedStartHour: number = 8
  @State selectedStartMinute: number = 0
  @State selectedEndHour: number = 17
  @State selectedEndMinute: number = 0

  private hours: string[] = []
  private minutes: string[] = []

  aboutToAppear(): void {
    for (let i = 0; i < 24; i++) {
      this.hours.push(i.toString().padStart(2, '0'))
    }
    for (let i = 0; i < 60; i++) {
      this.minutes.push(i.toString().padStart(2, '0'))
    }
  }

  getStartTime(): string {
    return this.hours[this.selectedStartHour] + ':' + this.minutes[this.selectedStartMinute]
  }

  getEndTime(): string {
    return this.hours[this.selectedEndHour] + ':' + this.minutes[this.selectedEndMinute]
  }

  build() {
    Column() {
      Text('时间段选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('开始时间')
        .fontSize(14)
        .margin({ bottom: 5 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedStartHour
        }) {
          ForEach(this.hours, (hour: string) => {
            Text(hour)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedStartHour = selectedIndex
        })

        Text(':')
          .fontSize(24)
          .margin({ left: 5, right: 5 })

        UIPickerComponent({
          selectedIndex: this.selectedStartMinute
        }) {
          ForEach(this.minutes, (minute: string) => {
            Text(minute)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedStartMinute = selectedIndex
        })
      }

      Text('结束时间')
        .fontSize(14)
        .margin({ top: 20, bottom: 5 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedEndHour
        }) {
          ForEach(this.hours, (hour: string) => {
            Text(hour)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedEndHour = selectedIndex
        })

        Text(':')
          .fontSize(24)
          .margin({ left: 5, right: 5 })

        UIPickerComponent({
          selectedIndex: this.selectedEndMinute
        }) {
          ForEach(this.minutes, (minute: string) => {
            Text(minute)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedEndMinute = selectedIndex
        })
      }

      Text(`时间段: ${this.getStartTime()} - ${this.getEndTime()}`)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text('提示: 分别选择开始和结束时间')
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
 * UIPickerExample007: 本地化选择器
 */
@Component
export struct UIPickerExample007 {
  @State selectedLanguage: number = 0
  @State selectedMonth: number = 5

  private languages: string[] = ['简体中文', 'English', '日本語']
  private monthData: Record<string, string[]> = {
    '简体中文': ['一月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '十一月', '十二月'],
    'English': ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'],
    '日本語': ['一月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '十一月', '十二月']
  }

  build() {
    Column() {
      Text('本地化选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('选择语言 / Select Language')
        .fontSize(14)
        .margin({ bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedLanguage
      }) {
        ForEach(this.languages, (language: string) => {
          Text(language)
        })
      }
      .width('70%')
      .height(180)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedLanguage = selectedIndex
        this.selectedMonth = 0
      })

      Text('选择月份 / Select Month')
        .fontSize(14)
        .margin({ top: 20, bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedMonth
      }) {
        ForEach(this.monthData[this.languages[this.selectedLanguage]], (month: string) => {
          Text(month)
        })
      }
      .width('70%')
      .height(180)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Text(`当前语言: ${this.languages[this.selectedLanguage]}`)
        .fontSize(14)
        .margin({ top: 20 })

      Text('提示: 切换语言查看不同语言的月份显示')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample008: 搜索过滤选择器
 */
@Component
export struct UIPickerExample008 {
  @State selectedIndex: number = 0
  @State searchText: string = ''
  @State filteredData: string[] = []

  private allFruits: string[] = [
    '苹果', '香蕉', '橙子', '葡萄', '西瓜', '草莓', '芒果', '樱桃',
    '猕猴桃', '榴莲', '菠萝', '荔枝', '龙眼', '柿子', '柚子', '柠檬',
    '梨', '桃子', '李子', '杏子', '枣', '橄榄', '山楂', '石榴'
  ]

  aboutToAppear(): void {
    this.filteredData = this.allFruits
  }

  performSearch(): void {
    if (this.searchText.trim() === '') {
      this.filteredData = this.allFruits
    } else {
      this.filteredData = this.allFruits.filter(fruit =>
        fruit.includes(this.searchText)
      )
    }
    this.selectedIndex = 0
  }

  build() {
    Column() {
      Text('搜索过滤选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Search({ value: this.searchText, placeholder: '搜索水果...' })
        .width('70%')
        .height(40)
        .backgroundColor('#FFFFFF')
        .borderRadius(20)
        .onChange((value: string) => {
          this.searchText = value
          this.performSearch()
        })

      Text(`找到 ${this.filteredData.length} 个结果`)
        .fontSize(12)
        .fontColor('#666666')
        .margin({ top: 10 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.filteredData, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedIndex = selectedIndex
      })

      Text('当前选择: ' + (this.filteredData[this.selectedIndex] || '无'))
        .fontSize(16)
        .margin({ top: 20 })

      Text('提示: 输入搜索关键字过滤选项')
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
 * UIPickerExample009: 自定义边距选择器
 */
@Component
export struct UIPickerExample009 {
  private dataArray: string[] = []
  @State startMargin: number = 10
  @State endMargin: number = 10

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('自定义边距选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.DIVIDER,
        startMargin: LengthMetrics.px(this.startMargin),
        endMargin: LengthMetrics.px(this.endMargin)
      })

      Text('起始边距: ' + this.startMargin + 'px')
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.startMargin, min: 0, max: 50, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((value: number) => {
          this.startMargin = Math.round(value)
        })

      Text('结束边距: ' + this.endMargin + 'px')
        .fontSize(14)
        .margin({ top: 10 })

      Slider({ value: this.endMargin, min: 0, max: 50, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((value: number) => {
          this.endMargin = Math.round(value)
        })

      Text('提示: 调整分割线的边距')
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
 * UIPickerExample010: 分组标题选择器
 */
@Component
export struct UIPickerExample010 {
  private sections: SectionItem[] = []

  aboutToAppear(): void {
    this.sections = [
      { title: '常用', items: ['推荐1', '推荐2', '推荐3', '推荐4'] },
      { title: '全部', items: ['项目A', '项目B', '项目C', '项目D', '项目E'] },
      { title: '其他', items: ['选项1', '选项2'] }
    ]
  }

  build() {
    Column() {
      Text('分组标题选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.sections, (section: SectionItem) => {
          Column() {
            Text(section.title)
              .fontSize(14)
              .fontColor('#999999')
              .margin({ top: 8, bottom: 4 })
              .width('100%')
              .textAlign(TextAlign.Center)
            ForEach(section.items, (item: string) => {
              Text(item)
                .fontSize(16)
                .fontColor('#333333')
            })
          }
        })
      }
      .width('70%')
      .height(250)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Text('提示: 带有分组标题的选择器')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface SectionItem {
  title: string
  items: string[]
}

/**
 * UIPickerExample011: 渐变色背景指示器
 */
@Component
export struct UIPickerExample011 {
  private dataArray: string[] = []
  @State gradientStart: Color = '#E3F2FD'
  @State gradientEnd: Color = '#2196F3'

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项 ' + i)
    }
  }

  build() {
    Column() {
      Text('渐变色背景指示器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: this.gradientStart,
        borderRadius: LengthMetrics.vp(16)
      })

      Text('提示: 渐变色背景指示器效果')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })

      Row() {
        Button('蓝色')
          .onClick(() => {
            this.gradientStart = '#E3F2FD'
            this.gradientEnd = '#2196F3'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('绿色')
          .onClick(() => {
            this.gradientStart = '#E8F5E9'
            this.gradientEnd = '#4CAF50'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('紫色')
          .onClick(() => {
            this.gradientStart = '#F3E5F5'
            this.gradientEnd = '#9C27B0'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample012: 双向绑定选择器
 */
@Component
export struct UIPickerExample012 {
  @State selectedValue: number = 5
  @State sliderValue: number = 5
  private dataArray: number[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i)
    }
  }

  onPickerChange(index: number): void {
    this.selectedValue = this.dataArray[index]
    this.sliderValue = this.selectedValue
  }

  onSliderChange(value: number): void {
    this.sliderValue = Math.round(value)
    this.selectedValue = this.sliderValue
  }

  build() {
    Column() {
      Text('双向绑定选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedValue - 1
      }) {
        ForEach(this.dataArray, (item: number) => {
          Text(item.toString())
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((index: number) => {
        this.onPickerChange(index)
      })

      Slider({ value: this.sliderValue, min: 1, max: 10, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .margin({ top: 30 })
        .onChange((value: number) => {
          this.onSliderChange(value)
        })

      Text('当前值: ' + this.selectedValue)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text('提示: 选择器和滑块双向绑定')
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
 * UIPickerExample013: 主题配色选择器
 */
@Component
export struct UIPickerExample013 {
  private themes: ThemeItem[] = []

  aboutToAppear(): void {
    this.themes = [
      { name: '蓝色', primary: '#2196F3', background: '#E3F2FD' },
      { name: '绿色', primary: '#4CAF50', background: '#E8F5E9' },
      { name: '紫色', primary: '#9C27B0', background: '#F3E5F5' },
      { name: '橙色', primary: '#FF9800', background: '#FFF3E0' },
      { name: '青色', primary: '#00BCD4', background: '#E0F7FA' }
    ]
  }

  build() {
    Column() {
      Text('主题配色选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.themes, (theme: ThemeItem) => {
          Row() {
            Text(theme.name)
              .fontSize(16)
              .fontColor('#333333')
            Circle()
              .width(20)
              .height(20)
              .fill(theme.primary)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: '#FAFAFA'
      })
      .onChange((index: number) => {
        console.info('Selected theme: ' + this.themes[index].name)
      })

      Text('提示: 选择不同的主题配色')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface ThemeItem {
  name: string
  primary: string
  background: string
}

/**
 * UIPickerExample014: 时间范围选择器
 */
@Component
export struct UIPickerExample014 {
  @State selectedHour: number = 9
  @State selectedMinute: number = 0
  @State selectedDuration: number = 1

  private hours: string[] = []
  private minutes: string[] = []
  private durations: string[] = ['30分钟', '1小时', '1.5小时', '2小时', '3小时', '4小时', '全天']

  aboutToAppear(): void {
    for (let i = 6; i <= 22; i++) {
      this.hours.push(i.toString().padStart(2, '0'))
    }
    for (let i = 0; i < 60; i += 15) {
      this.minutes.push(i.toString().padStart(2, '0'))
    }
  }

  getEndTime(): string {
    let totalMinutes = this.selectedHour * 60 + this.selectedMinute
    let durationMinutes = [30, 60, 90, 120, 180, 240, 480][this.selectedDuration]
    let endMinutes = totalMinutes + durationMinutes
    let endHour = Math.floor(endMinutes / 60) % 24
    let endMin = endMinutes % 60
    return endHour.toString().padStart(2, '0') + ':' + endMin.toString().padStart(2, '0')
  }

  build() {
    Column() {
      Text('时间范围选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('开始时间')
        .fontSize(14)
        .margin({ bottom: 5 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedHour - 6
        }) {
          ForEach(this.hours, (hour: string) => {
            Text(hour)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedHour = index + 6
        })

        Text(':')
          .fontSize(24)
          .margin({ left: 5, right: 5 })

        UIPickerComponent({
          selectedIndex: this.selectedMinute / 15
        }) {
          ForEach(this.minutes, (minute: string) => {
            Text(minute)
          })
        }
        .width('42%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedMinute = index * 15
        })
      }
      .width('70%')

      Text('持续时间')
        .fontSize(14)
        .margin({ top: 20, bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedDuration
      }) {
        ForEach(this.durations, (duration: string) => {
          Text(duration)
        })
      }
      .width('70%')
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((index: number) => {
        this.selectedDuration = index
      })

      Text(`时间段: ${this.hours[this.selectedHour - 6]}:${this.minutes[this.selectedMinute / 15]} - ${this.getEndTime()}`)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text('提示: 选择开始时间和持续时间')
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
 * UIPickerExample015: 带图标的多列选择器
 */
@Component
export struct UIPickerExample015 {
  @State selectedCategory: number = 0
  @State selectedItem: number = 0

  private categories: string[] = ['电子产品', '服装鞋包', '食品饮料', '图书文具']
  private dataMap: Record<string, CategoryItem[]> = {
    '电子产品': [
      { name: '手机', icon: '📱', price: '¥3999' },
      { name: '电脑', icon: '💻', price: '¥5999' },
      { name: '耳机', icon: '🎧', price: '¥299' }
    ],
    '服装鞋包': [
      { name: 'T恤', icon: '👕', price: '¥99' },
      { name: '牛仔裤', icon: '👖', price: '¥199' },
      { name: '运动鞋', icon: '👟', price: '¥399' }
    ],
    '食品饮料': [
      { name: '咖啡', icon: '☕', price: '¥28' },
      { name: '蛋糕', icon: '🍰', price: '¥35' },
      { name: '水果', icon: '🍎', price: '¥15' }
    ],
    '图书文具': [
      { name: '小说', icon: '📚', price: '¥45' },
      { name: '笔记本', icon: '📓', price: '¥12' },
      { name: '笔', icon: '🖊️', price: '¥5' }
    ]
  }

  build() {
    Column() {
      Text('带图标的多列选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedCategory
        }) {
          ForEach(this.categories, (category: string) => {
            Text(category)
              .fontSize(14)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedCategory = index
          this.selectedItem = 0
        })

        UIPickerComponent({
          selectedIndex: this.selectedItem
        }) {
          ForEach(this.dataMap[this.categories[this.selectedCategory]], (item: CategoryItem) => {
            Row() {
              Text(item.icon)
                .fontSize(20)
              Text(item.name)
                .fontSize(14)
                .margin({ left: 5 })
              Text(item.price)
                .fontSize(12)
                .fontColor('#FF6B00')
                .margin({ left: 5 })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedItem = index
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('提示: 先选择分类，再选择具体商品')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface CategoryItem {
  name: string
  icon: string
  price: string
}

/**
 * UIPickerExample016: 货币选择器
 */
@Component
export struct UIPickerExample016 {
  @State selectedCurrency: number = 2
  @State amount: number = 100

  private currencies: CurrencyItem[] = [
    { code: 'CNY', name: '人民币', symbol: '¥', rate: 1 },
    { code: 'USD', name: '美元', symbol: '$', rate: 7.2 },
    { code: 'EUR', name: '欧元', symbol: '€', rate: 7.8 },
    { code: 'JPY', name: '日元', symbol: '¥', rate: 0.05 },
    { code: 'GBP', name: '英镑', symbol: '£', rate: 9.1 },
    { code: 'HKD', name: '港币', symbol: 'HK$', rate: 0.92 },
    { code: 'KRW', name: '韩元', symbol: '₩', rate: 0.0054 },
    { code: 'AUD', name: '澳元', symbol: 'A$', rate: 4.7 }
  ]

  getConvertedAmount(): string {
    const currency = this.currencies[this.selectedCurrency]
    const converted = (this.amount / currency.rate).toFixed(2)
    return currency.symbol + converted
  }

  build() {
    Column() {
      Text('货币选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedCurrency
      }) {
        ForEach(this.currencies, (currency: CurrencyItem) => {
          Row() {
            Text(currency.code)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
            Text(currency.name)
              .fontSize(14)
              .fontColor('#666666')
              .margin({ left: 8 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((index: number) => {
        this.selectedCurrency = index
      })

      Text('金额: ¥' + this.amount)
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('-10')
          .onClick(() => {
            this.amount = Math.max(0, this.amount - 10)
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin({ right: 10 })

        Button('-1')
          .onClick(() => {
            this.amount = Math.max(0, this.amount - 1)
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin({ right: 10 })

        Button('+1')
          .onClick(() => {
            this.amount = this.amount + 1
          })
          .fontSize(12)
          .height(30)
          .width(60)
          .margin({ right: 10 })

        Button('+10')
          .onClick(() => {
            this.amount = this.amount + 10
          })
          .fontSize(12)
          .height(30)
          .width(60)
      }
      .margin({ top: 10 })

      Text('转换后: ' + this.getConvertedAmount())
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor('#007DFF')

      Text(`汇率: 1 ${this.currencies[this.selectedCurrency].code} = ${this.currencies[this.selectedCurrency].rate} CNY`)
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 10 })

      Text('提示: 选择货币并调整金额')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface CurrencyItem {
  code: string
  name: string
  symbol: string
  rate: number
}

/**
 * UIPickerExample017: 温度单位转换器
 */
@Component
export struct UIPickerExample017 {
  @State temperature: number = 25
  @State unit: number = 0

  private units: string[] = ['摄氏度 °C', '华氏度 °F', '开尔文 K']

  getConvertedTemp(): string {
    let temp: number
    if (this.unit === 0) {
      temp = this.temperature
    } else if (this.unit === 1) {
      temp = this.temperature * 9 / 5 + 32
    } else {
      temp = this.temperature + 273.15
    }
    return temp.toFixed(1)
  }

  build() {
    Column() {
      Text('温度单位转换器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.unit
      }) {
        ForEach(this.units, (u: string) => {
          Text(u)
            .fontSize(16)
        })
      }
      .width('70%')
      .height(180)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((index: number) => {
        this.unit = index
      })

      Text('输入温度（摄氏度）: ' + this.temperature)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.temperature, min: -40, max: 100, step: 1 })
        .width('70%')
        .blockColor('#FF5722')
        .trackColor('#E0E0E0')
        .selectedColor('#FF5722')
        .onChange((value: number) => {
          this.temperature = Math.round(value)
        })

      Text('转换结果: ' + this.getConvertedTemp() + ' ' + this.units[this.unit])
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor('#FF5722')

      Text('提示: 调整温度并查看不同单位的转换')
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
 * UIPickerExample018: 自定义项布局选择器
 */
@Component
export struct UIPickerExample018 {
  private userList: UserItem[] = []
  @State selectedIndex: number = 0

  aboutToAppear(): void {
    this.userList = [
      { name: '张三', role: '管理员', status: '在线', avatar: '👤' },
      { name: '李四', role: '普通用户', status: '离线', avatar: '👤' },
      { name: '王五', role: '普通用户', status: '在线', avatar: '👤' },
      { name: '赵六', role: '编辑', status: '忙碌', avatar: '👤' },
      { name: '钱七', role: '普通用户', status: '在线', avatar: '👤' }
    ]
  }

  build() {
    Column() {
      Text('自定义项布局选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.userList, (user: UserItem) => {
          Column() {
            Row() {
              Text(user.avatar)
                .fontSize(32)
              Column() {
                Text(user.name)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#333333')
                Text(user.role)
                  .fontSize(12)
                  .fontColor('#666666')
              }
              .alignItems(VerticalAlign.Center)
              .margin({ left: 10 })
              Blank()
              Text(user.status)
                .fontSize(12)
                .fontColor(
                  user.status === '在线' ? '#4CAF50' :
                  user.status === '忙碌' ? '#FF9800' : '#999999'
                )
                .padding({ left: 8, right: 8, top: 4, bottom: 4 })
                .backgroundColor(
                  user.status === '在线' ? '#E8F5E9' :
                  user.status === '忙碌' ? '#FFF3E0' : '#F5F5F5'
                )
                .borderRadius(12)
            }
            .width('100%')
            .padding(12)
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .margin({ top: 4, bottom: 4 })
          }
        })
      }
      .width('70%')
      .height(280)
      .selectionIndicator({
        type: PickerIndicatorType.NONE
      })

      Text('当前选择: ' + this.userList[this.selectedIndex].name)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text(`角色: ${this.userList[this.selectedIndex].role}`)
        .fontSize(14)
        .fontColor('#666666')
        .margin({ top: 5 })

      Text('提示: 查看用户列表的详细布局')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface UserItem {
  name: string
  role: string
  status: string
  avatar: string
}

/**
 * UIPickerExample019: 带图片的选择器
 */
@Component
export struct UIPickerExample019 {
  private avatars: AvatarItem[] = []
  @State selectedAvatar: number = 0

  aboutToAppear(): void {
    this.avatars = [
      { name: '动物', icons: ['🐶', '🐱', '🐭', '🐹', '🐰', '🦊', '🐻', '🐼'] },
      { name: '水果', icons: ['🍎', '🍊', '🍋', '🍌', '🍉', '🍇', '🍓', '🍒'] },
      { name: '运动', icons: ['⚽', '🏀', '🏈', '🎾', '🏐', '🏊', '🎱', '🏓'] },
      { name: '天气', icons: ['☀', '🌤', '⛅', '🌧', '❄', '🌈', '🌩', '⚡'] }
    ]
  }

  build() {
    Column() {
      Text('带图片的选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('分类')
        .fontSize(14)
        .margin({ bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedAvatar
      }) {
        ForEach(this.avatars, (category: AvatarItem) => {
          Row() {
            ForEach(category.icons.slice(0, 4), (icon: string) => {
              Text(icon)
                .fontSize(28)
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        })
      }
      .width('70%')
      .height(180)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((index: number) => {
        this.selectedAvatar = index
      })

      Text('图标')
        .fontSize(14)
        .margin({ top: 20, bottom: 5 })

      Row() {
        ForEach(this.avatars[this.selectedAvatar].icons, (icon: string) => {
          Text(icon)
            .fontSize(40)
            .padding(8)
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .shadow({ radius: 4, color: '#E0E0E0', offsetX: 0, offsetY: 2 })
        })
      }
      .width('70%')
      .flexWrap(FlexWrap.Wrap)
      .justifyContent(FlexAlign.SpaceBetween)

      Text('提示: 先选择分类，再选择具体图标')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface AvatarItem {
  name: string
  icons: string[]
}

/**
 * UIPickerExample020: 数值范围选择器
 */
@Component
export struct UIPickerExample020 {
  @State minValue: number = 0
  @State maxValue: number = 100
  @State selectedMin: number = 0
  @State selectedMax: number = 100

  private values: number[] = []

  aboutToAppear(): void {
    for (let i = 0; i <= 100; i += 5) {
      this.values.push(i)
    }
  }

  validateRange(): void {
    if (this.selectedMin > this.selectedMax) {
      this.selectedMin = this.selectedMax
      this.minValue = this.selectedMax
    }
  }

  build() {
    Column() {
      Text('数值范围选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('最小值')
        .fontSize(14)
        .margin({ bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedMin / 5
      }) {
        ForEach(this.values, (value: number) => {
          Text(value.toString())
        })
      }
      .width('70%')
      .height(150)
      .selectionIndicator({
        type: PickerIndicatorType.DIVIDER
      })
      .onChange((index: number) => {
        this.minValue = this.values[index]
        this.selectedMin = this.values[index]
        this.validateRange()
      })

      Text('最大值')
        .fontSize(14)
        .margin({ top: 20, bottom: 5 })

      UIPickerComponent({
        selectedIndex: this.selectedMax / 5
      }) {
        ForEach(this.values, (value: number) => {
          Text(value.toString())
        })
      }
      .width('70%')
      .height(150)
      .selectionIndicator({
        type: PickerIndicatorType.DIVIDER
      })
      .onChange((index: number) => {
        this.maxValue = this.values[index]
        this.selectedMax = this.values[index]
        this.validateRange()
      })

      Text(`范围: ${this.minValue} - ${this.maxValue}`)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor('#007DFF')

      Text('跨度: ' + (this.maxValue - this.minValue))
        .fontSize(14)
        .fontColor('#666666')
        .margin({ top: 5 })

      Text('提示: 选择数值范围（最小值 ≤ 最大值）')
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
 * UIPickerExample021: 列表项选择器
 */
@Component
export struct UIPickerExample021 {
  @State selectedIndex: number = 0
  @State checkedItems: boolean[] = []

  private tasks: TaskItem[] = []

  aboutToAppear(): void {
    this.tasks = [
      { title: '完成项目文档', priority: '高', completed: false },
      { title: '修复登录Bug', priority: '紧急', completed: true },
      { title: '代码审查', priority: '中', completed: false },
      { title: '更新测试用例', priority: '低', completed: false },
      { title: '性能优化', priority: '高', completed: false },
      { title: '编写API文档', priority: '中', completed: true }
    ]
    this.checkedItems = this.tasks.map(() => false)
  }

  toggleCheck(index: number): void {
    this.checkedItems[index] = !this.checkedItems[index]
  }

  build() {
    Column() {
      Text('列表项选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.tasks, (task: TaskItem, index: number) => {
          Row() {
            Checkbox({ name: 'task' + index })
              .select(this.checkedItems[index])
              .onChange((value: boolean) => {
                this.toggleCheck(index)
              })
              .margin({ right: 10 })

            Column() {
              Text(task.title)
                .fontSize(16)
                .fontColor('#333333')
              Text(task.priority)
                .fontSize(12)
                .fontColor(
                  task.priority === '紧急' ? '#F44336' :
                  task.priority === '高' ? '#FF9800' :
                  task.priority === '中' ? '#FFC107' : '#4CAF50'
                )
                .padding({ left: 6, right: 6, top: 2, bottom: 2 })
                .backgroundColor(
                  task.priority === '紧急' ? '#FFEBEE' :
                  task.priority === '高' ? '#FFF3E0' :
                  task.priority === '中' ? '#FFF8E1' : '#E8F5E9'
                )
                .borderRadius(4)
                .margin({ top: 4 })
            }
            .alignItems(VerticalAlign.Center)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#FFFFFF')
          .borderRadius(8)
          .margin({ top: 4, bottom: 4 })
        })
      }
      .width('70%')
      .height(300)
      .selectionIndicator({
        type: PickerIndicatorType.NONE
      })

      Text('当前选中: ' + this.tasks[this.selectedIndex].title)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })

      Text('已勾选: ' + this.checkedItems.filter((checked: boolean) => checked).length + ' 项')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ top: 5 })

      Text('提示: 选择并勾选任务项')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface TaskItem {
  title: string
  priority: string
  completed: boolean
}

/**
 * UIPickerExample022: 颜色主题选择器
 */
@Component
export struct UIPickerExample022 {
  @State selectedTheme: number = 0

  private colorThemes: ColorThemeItem[] = []

  aboutToAppear(): void {
    this.colorThemes = [
      { name: '浅色', background: '#FFFFFF', text: '#333333', preview: ['⚪', '⚫', '⚪', '⚫'] },
      { name: '深色', background: '#1A1A1A', text: '#FFFFFF', preview: ['⚫', '⚪', '⚫', '⚪'] },
      { name: '护眼', background: '#E8F5E9', text: '#1B5E20', preview: ['⚪', '⚫', '⚪', '⚫'] },
      { name: '夜间', background: '#0D1117', text: '#64B5F6', preview: ['⚫', '⚪', '⚫', '⚪'] },
      { name: '蓝光', background: '#E3F2FD', text: '#1565C0', preview: ['⚪', '⚫', '⚪', '⚫'] }
    ]
  }

  build() {
    Column() {
      Text('颜色主题选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedTheme
      }) {
        ForEach(this.colorThemes, (theme: ColorThemeItem) => {
          Row() {
            Column() {
              ForEach(theme.preview, (icon: string, index: number) => {
                Text(icon)
                  .fontSize(20)
                  .margin({ top: index > 0 ? -8 : 0 })
              })
            }
            .margin({ right: 12 })
            Text(theme.name)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor(theme.text)
          }
          .width('100%')
          .padding(16)
          .backgroundColor(theme.background)
          .borderRadius(8)
          .justifyContent(FlexAlign.Center)
          .margin({ top: 4, bottom: 4 })
        })
      }
      .width('70%')
      .height(220)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: this.colorThemes[this.selectedTheme].background
      })
      .onChange((index: number) => {
        this.selectedTheme = index
      })

      Text('当前主题: ' + this.colorThemes[this.selectedTheme].name)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor(this.colorThemes[this.selectedTheme].text)

      Text('提示: 选择不同的颜色主题')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface ColorThemeItem {
  name: string
  background: string
  text: string
  preview: string[]
}

/**
 * UIPickerExample023: 星期和时间组合选择器
 */
@Component
export struct UIPickerExample023 {
  @State selectedWeekday: number = 0
  @State selectedHour: number = 9
  @State selectedMinute: number = 0

  private weekdays: string[] = ['周一', '周二', '周三', '周四', '周五', '周六', '周日']
  private hours: string[] = []
  private minutes: string[] = []

  aboutToAppear(): void {
    for (let i = 0; i < 24; i++) {
      this.hours.push(i.toString().padStart(2, '0'))
    }
    for (let i = 0; i < 60; i += 15) {
      this.minutes.push(i.toString().padStart(2, '0'))
    }
  }

  getFormattedTime(): string {
    return `${this.weekdays[this.selectedWeekday]} ${this.hours[this.selectedHour]}:${this.minutes[this.selectedMinute / 15]}`
  }

  build() {
    Column() {
      Text('星期和时间组合选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedWeekday
        }) {
          ForEach(this.weekdays, (day: string) => {
            Text(day)
              .fontSize(14)
          })
        }
        .width('30%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedWeekday = index
        })

        UIPickerComponent({
          selectedIndex: this.selectedHour
        }) {
          ForEach(this.hours, (hour: string) => {
            Text(hour)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
          })
        }
        .width('25%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedHour = index
        })

        Text(':')
          .fontSize(24)
          .margin({ left: 2, right: 2 })

        UIPickerComponent({
          selectedIndex: this.selectedMinute / 15
        }) {
          ForEach(this.minutes, (minute: string) => {
            Text(minute)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
          })
        }
        .width('25%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((index: number) => {
          this.selectedMinute = index * 15
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text(this.getFormattedTime())
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor('#007DFF')

      Text('提示: 选择星期和时间进行提醒设置')
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
 * UIPickerExample024: 自定义指示器样式
 */
@Component
export struct UIPickerExample024 {
  private dataArray: string[] = []
  @State indicatorWidth: number = 80
  @State indicatorHeight: number = 50
  @State indicatorColor: Color = '#E3F2FD'

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('自定义指示器样式')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
            .fontSize(20)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: this.indicatorColor,
        borderRadius: LengthMetrics.vp(12),
        startMargin: LengthMetrics.px((100 - this.indicatorWidth) / 2),
        endMargin: LengthMetrics.px((100 - this.indicatorWidth) / 2)
      })

      Text('指示器宽度: ' + this.indicatorWidth + '%')
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.indicatorWidth, min: 40, max: 100, step: 5 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((value: number) => {
          this.indicatorWidth = Math.round(value)
        })

      Text('指示器颜色')
        .fontSize(14)
        .margin({ top: 15 })

      Row() {
        Button('蓝色')
          .onClick(() => {
            this.indicatorColor = '#E3F2FD'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('绿色')
          .onClick(() => {
            this.indicatorColor = '#4CAF50'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('橙色')
          .onClick(() => {
            this.indicatorColor = '#FF9800'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('紫色')
          .onClick(() => {
            this.indicatorColor = '#9C27B0'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 自定义指示器的宽度、颜色和边距')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
