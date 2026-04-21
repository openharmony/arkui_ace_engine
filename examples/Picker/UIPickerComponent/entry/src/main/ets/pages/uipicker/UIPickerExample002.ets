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
 * UIPickerExample013: 自定义文本样式选择器
 */
@Component
export struct UIPickerExample013 {
  private dataArray: string[] = []
  @State fontSize: number = 20
  @State fontColor: Color = Color.Black
  @State fontWeight: number = FontWeight.Normal

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项' + i)
    }
  }

  build() {
    Column() {
      Text('自定义文本样式选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
            .fontSize(this.fontSize)
            .fontColor(this.fontColor)
            .fontWeight(this.fontWeight)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Text('字体大小: ' + this.fontSize)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.fontSize, min: 12, max: 32, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((value: number) => {
          this.fontSize = Math.round(value)
        })

      Text('字体颜色')
        .fontSize(14)
        .margin({ top: 10 })

      Row() {
        Button('黑色')
          .onClick(() => {
            this.fontColor = Color.Black
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('蓝色')
          .onClick(() => {
            this.fontColor = Color.Blue
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('红色')
          .onClick(() => {
            this.fontColor = Color.Red
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 调整文本样式')
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
 * UIPickerExample014: 无数据状态选择器
 */
@Component
export struct UIPickerExample014 {
  @State hasData: boolean = true
  private dataArray: string[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项' + i)
    }
  }

  build() {
    Column() {
      Text('无数据状态选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.hasData) {
        UIPickerComponent() {
          ForEach(this.dataArray, (item: string) => {
            Text(item)
          })
        }
        .width('70%')
        .height(200)
        .selectionIndicator({
          type: PickerIndicatorType.BACKGROUND
        })
      } else {
        Text('暂无数据')
          .fontSize(16)
          .fontColor('#999999')
          .width('70%')
          .height(200)
          .textAlign(TextAlign.Center)
      }

      Row() {
        Button('有数据')
          .onClick(() => {
            this.hasData = true
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .backgroundColor(this.hasData ? '#007DFF' : '#E0E0E0')
          .margin({ right: 10 })

        Button('无数据')
          .onClick(() => {
            this.hasData = false
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .backgroundColor(!this.hasData ? '#007DFF' : '#E0E0E0')
      }
      .width('70%')
      .margin({ top: 20 })

      Text('提示: 切换数据状态')
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
 * UIPickerExample015: 禁用状态选择器
 */
@Component
export struct UIPickerExample015 {
  private dataArray: string[] = []
  @State isEnabled: boolean = true

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push('选项' + i)
    }
  }

  build() {
    Column() {
      Text('禁用状态选择器')
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
      .enabled(this.isEnabled)
      .opacity(this.isEnabled ? 1.0 : 0.4)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Row() {
        Button('启用')
          .onClick(() => {
            this.isEnabled = true
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .backgroundColor(this.isEnabled ? '#4CAF50' : '#E0E0E0')
          .margin({ right: 10 })

        Button('禁用')
          .onClick(() => {
            this.isEnabled = false
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .backgroundColor(!this.isEnabled ? '#F44336' : '#E0E0E0')
      }
      .width('70%')
      .margin({ top: 20 })

      Text(`当前状态: ${this.isEnabled ? '启用' : '禁用'}`)
        .fontSize(14)
        .fontColor(this.isEnabled ? '#4CAF50' : '#F44336')
        .margin({ top: 10 })

      Text('提示: 切换启用/禁用状态')
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
 * UIPickerExample016: 动态数据更新选择器
 */
@Component
export struct UIPickerExample016 {
  @State selectedIndex: number = 0
  @State currentData: string[] = []
  @State categoryIndex: number = 0

  private categories: string[] = ['水果', '蔬菜', '饮料']
  private dataMap: Record<string, string[]> = {
    '水果': ['苹果', '香蕉', '橙子', '葡萄', '西瓜', '草莓', '芒果', '樱桃'],
    '蔬菜': ['白菜', '萝卜', '西红柿', '黄瓜', '茄子', '菠菜', '芹菜', '西兰花'],
    '饮料': ['可乐', '雪碧', '芬达', '美年达', '红牛', '脉动', '冰红茶', '绿茶']
  }

  aboutToAppear(): void {
    this.currentData = this.dataMap[this.categories[0]] || []
  }

  changeCategory(index: number) {
    this.categoryIndex = index
    this.currentData = this.dataMap[this.categories[index]] || []
    this.selectedIndex = 0
  }

  build() {
    Column() {
      Text('动态数据更新选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('选择分类:')
        .fontSize(14)
        .width('70%')

      Row() {
        ForEach(this.categories, (category: string, index: number) => {
          Button(category)
            .width(60)
            .height(35)
            .fontSize(12)
            .backgroundColor(this.categoryIndex === index ? '#007DFF' : '#E0E0E0')
            .fontColor(this.categoryIndex === index ? '#FFFFFF' : '#000000')
            .onClick(() => {
              this.changeCategory(index)
            })
            .margin({ right: 5 })
        })
      }
      .width('70%')
      .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.currentData, (item: string) => {
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

      Text('当前选择: ' + (this.currentData[this.selectedIndex] || ''))
        .fontSize(16)
        .margin({ top: 20 })

      Text('提示: 点击分类按钮切换数据源')
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
 * UIPickerExample017: 多列并行选择器
 */
@Component
export struct UIPickerExample017 {
  @State selectedProvince: number = 0
  @State selectedCity: number = 0
  @State selectedYear: number = 0
  @State selectedMonth: number = 0

  private provinces: string[] = ['北京市', '上海市', '广东省', '浙江省', '江苏省']
  private cities: string[] = ['东城区', '黄浦区', '广州市', '杭州市', '南京市']
  private years: string[] = []
  private months: string[] = []

  aboutToAppear(): void {
    for (let i = 2020; i <= 2030; i++) {
      this.years.push(i + '年')
    }
    for (let i = 1; i <= 12; i++) {
      this.months.push(i + '月')
    }
  }

  build() {
    Column() {
      Text('多列并行选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('地区选择')
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedProvince
        }) {
          ForEach(this.provinces, (province: string) => {
            Text(province)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedProvince = selectedIndex
        })

        UIPickerComponent({
          selectedIndex: this.selectedCity
        }) {
          ForEach(this.cities, (city: string) => {
            Text(city)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedCity = selectedIndex
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('日期选择')
        .fontSize(14)
        .margin({ top: 20, bottom: 10 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.selectedYear
        }) {
          ForEach(this.years, (year: string) => {
            Text(year)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedYear = selectedIndex
        })

        UIPickerComponent({
          selectedIndex: this.selectedMonth
        }) {
          ForEach(this.months, (month: string) => {
            Text(month)
          })
        }
        .width('45%')
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .onChange((selectedIndex: number) => {
          this.selectedMonth = selectedIndex
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('提示: 两个独立的多列选择器')
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
 * UIPickerExample018: 自定义圆角选择器
 */
@Component
export struct UIPickerExample018 {
  private dataArray: string[] = []
  @State borderRadius: number = 12

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('自定义圆角选择器')
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
        borderRadius: LengthMetrics.vp(this.borderRadius)
      })

      Text('圆角半径: ' + this.borderRadius + 'vp')
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.borderRadius, min: 0, max: 20, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((value: number) => {
          this.borderRadius = Math.round(value)
        })

      Text('提示: 滑动调整圆角半径')
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
 * UIPickerExample019: 性能测试选择器（大量数据）
 */
@Component
export struct UIPickerExample019 {
  @State selectedIndex: number = 500
  @State itemCount: number = 1000
  @State largeData: string[] = []

  aboutToAppear(): void {
    this.generateData()
  }

  generateData() {
    this.largeData = []
    for (let i = 0; i < this.itemCount; i++) {
      this.largeData.push(`项目 ${i + 1}`)
    }
  }

  build() {
    Column() {
      Text('性能测试选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text(`数据量: ${this.itemCount} 项`)
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 10 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.largeData, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .canLoop(true)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedIndex = selectedIndex
      })

      Row() {
        Button('500项')
          .onClick(() => {
            this.itemCount = 500
            this.selectedIndex = 250
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin({ right: 10 })

        Button('1000项')
          .onClick(() => {
            this.itemCount = 1000
            this.selectedIndex = 500
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(80)
          .margin({ right: 10 })

        Button('2000项')
          .onClick(() => {
            this.itemCount = 2000
            this.selectedIndex = 1000
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(80)
      }
      .width('70%')
      .margin({ top: 20 })
      .justifyContent(FlexAlign.Center)

      Text('提示: 测试不同数据量下的性能')
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
 * UIPickerExample010: 图标文本混合选择器
 */
@Component
export struct UIPickerExample010 {
  private items: IconTextItem[] = []

  aboutToAppear(): void {
    const icons: string[] = ['😀', '😎', '🥳', '🎉', '⭐', '🌟', '✨', '💫', '🔥', '💎']
    const labels: string[] = ['开心', '酷炫', '庆祝', '派对', '星星', '闪亮', '光芒', '彗星', '火焰', '钻石']
    for (let i = 0; i < 10; i++) {
      this.items.push({ icon: icons[i], label: labels[i] })
    }
  }

  build() {
    Column() {
      Text('图标文本混合选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.items, (item: IconTextItem) => {
          Row() {
            Text(item.icon)
              .fontSize(24)
            Text(item.label)
              .fontSize(16)
              .margin({ left: 8 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: '#FFF9C4'
      })

      Text('提示: 图标和文本混合显示')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

interface IconTextItem {
  icon: string
  label: string
}

/**
 * UIPickerExample011: 单列短数据选择器
 */
@Component
export struct UIPickerExample011 {
  private priorityLevels: string[] = ['低优先级', '中优先级', '高优先级', '紧急']
  @State selectedPriority: number = 1

  build() {
    Column() {
      Text('单列短数据选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedPriority
      }) {
        ForEach(this.priorityLevels, (level: string) => {
          Text(level)
            .fontSize(16)
            .fontColor('#333333')
        })
      }
      .width('70%')
      .height(180)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedPriority = selectedIndex
      })

      Text('当前优先级: ' + this.priorityLevels[this.selectedPriority])
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .fontColor(this.selectedPriority === 3 ? '#F44336' : this.selectedPriority === 2 ? '#FF9800' : this.selectedPriority === 1 ? '#FFC107' : '#4CAF50')

      Text('提示: 少量选项的快速选择')
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
 * UIPickerExample012: 数字密码选择器
 */
@Component
export struct UIPickerExample012 {
  @State digit1: number = 0
  @State digit2: number = 0
  @State digit3: number = 0
  @State digit4: number = 0

  private digits: string[] = []

  aboutToAppear(): void {
    for (let i = 0; i <= 9; i++) {
      this.digits.push(i.toString())
    }
  }

  getPinCode(): string {
    return this.digits[this.digit1] + this.digits[this.digit2] + this.digits[this.digit3] + this.digits[this.digit4]
  }

  build() {
    Column() {
      Text('数字密码选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        ForEach([this.digit1, this.digit2, this.digit3, this.digit4], (digitIndex: number, index: number) => {
          UIPickerComponent({
            selectedIndex: digitIndex
          }) {
            ForEach(this.digits, (digit: string) => {
              Text(digit)
                .fontSize(32)
                .fontWeight(FontWeight.Bold)
                .fontColor('#333333')
            })
          }
          .width('20%')
          .height(150)
          .selectionIndicator({
            type: PickerIndicatorType.DIVIDER
          })
          .onChange((selectedIndex: number) => {
            if (index === 0) this.digit1 = selectedIndex
            else if (index === 1) this.digit2 = selectedIndex
            else if (index === 2) this.digit3 = selectedIndex
            else if (index === 3) this.digit4 = selectedIndex
          })
        })
      }
      .width('80%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('PIN码: ' + this.getPinCode())
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 30 })
        .letterSpacing(8)

      Text('提示: 四位数字密码组合选择')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
