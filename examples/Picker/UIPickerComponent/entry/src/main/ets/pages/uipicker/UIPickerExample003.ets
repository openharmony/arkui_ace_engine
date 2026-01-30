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
