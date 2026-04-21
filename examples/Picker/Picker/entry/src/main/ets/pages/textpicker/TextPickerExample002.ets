/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { LengthMetrics } from '@kit.ArkUI'

/**
 * TextPickerExample002: 高级样式定制示例
 * 演示TextPicker的各种高级样式属性
 */
@Component
export struct TextPickerExample002 {
  private select: number = 1
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4']

  build() {
    Column() {
      Text('高级样式定制示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({
        range: this.fruits,
        selected: this.select,
        value: this.fruits[this.select]
      })
        .onChange((value: string | string[], index: number | number[]) => {
          console.info('Picker item changed, value: ' + value + ', index: ' + index)
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          console.info('Picker scroll stopped, value: ' + value + ', index: ' + index)
        })
        .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
        .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
        .selectedTextStyle({ color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } })
        .defaultPickerItemHeight(50)
        .canLoop(false)
        .selectedIndex(2)

      Text('提示: 观察不同选中状态的样式变化')
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
 * TextPickerExample003: 动态样式切换示例
 */
@Component
export struct TextPickerExample003 {
  private fruits: string[] = ['apple', 'orange', 'peach', 'grape', 'banana', 'pear']
  @State selectedColor: Color = Color.Blue
  @State normalColor: Color = Color.Black
  @State disappearColor: Color = Color.Gray
  @State selectedSize: number = 30
  @State normalSize: number = 20
  @State disappearSize: number = 15

  build() {
    Column() {
      Text('动态样式切换示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .disappearTextStyle({ color: this.disappearColor, font: { size: this.disappearSize } })
        .textStyle({ color: this.normalColor, font: { size: this.normalSize } })
        .selectedTextStyle({ color: this.selectedColor, font: { size: this.selectedSize } })

      Text('选中项颜色')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('蓝色')
          .onClick(() => {
            this.selectedColor = Color.Blue
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('绿色')
          .onClick(() => {
            this.selectedColor = Color.Green
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('红色')
          .onClick(() => {
            this.selectedColor = Color.Red
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('选中项大小: ' + this.selectedSize)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.selectedSize, min: 20, max: 40, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.selectedSize = Math.round(value)
        })

      Text('提示: 调整按钮和滑块来改变样式')
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
 * TextPickerExample004: 日期时间选择器示例
 */
@Component
export struct TextPickerExample004 {
  private years: string[] = []
  private months: string[] = []
  private days: string[] = []
  private hours: string[] = []
  private minutes: string[] = []
  private seconds: string[] = []
  @State yearIndex: number = 0
  @State monthIndex: number = 0
  @State dayIndex: number = 0
  @State hourIndex: number = 0
  @State minuteIndex: number = 0
  @State secondIndex: number = 0

  aboutToAppear(): void {
    const currentYear = new Date().getFullYear()
    for (let i = currentYear - 50; i <= currentYear + 50; i++) {
      this.years.push(i.toString() + '年')
    }
    for (let i = 1; i <= 12; i++) {
      this.months.push(i.toString() + '月')
    }
    for (let i = 1; i <= 31; i++) {
      this.days.push(i.toString() + '日')
    }
    for (let i = 0; i <= 23; i++) {
      this.hours.push(i.toString().padStart(2, '0') + '时')
    }
    for (let i = 0; i <= 59; i++) {
      this.minutes.push(i.toString().padStart(2, '0') + '分')
    }
    for (let i = 0; i <= 59; i++) {
      this.seconds.push(i.toString().padStart(2, '0') + '秒')
    }
    this.yearIndex = 50
  }

  build() {
    Column() {
      Text('日期时间选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        Column() {
          Text('日期')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: [this.years, this.months, this.days],
            selected: [this.yearIndex, this.monthIndex, this.dayIndex]
          })
            .onChange((value: string | string[], index: number | number[]) => {
              const idx = index as number[]
              this.yearIndex = idx[0]
              this.monthIndex = idx[1]
              this.dayIndex = idx[2]
            })
        }
        .width('48%')

        Column() {
          Text('时间')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: [this.hours, this.minutes, this.seconds],
            selected: [this.hourIndex, this.minuteIndex, this.secondIndex]
          })
            .onChange((value: string | string[], index: number | number[]) => {
              const idx = index as number[]
              this.hourIndex = idx[0]
              this.minuteIndex = idx[1]
              this.secondIndex = idx[2]
            })
        }
        .width('48%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('提示: 选择完整的日期和时间')
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
 * TextPickerExample005: 复杂地区选择器（四级联动）
 */
@Component
export struct TextPickerExample005 {
  type RegionDict = Record<string, Record<string, Record<string, string[]>>>

  @State provinceIndex: number = 0
  @State cityIndex: number = 0
  @State districtIndex: number = 0
  @State streetIndex: number = 0
  @State provinces: string[] = []
  @State cities: string[] = []
  @State districts: string[] = []
  @State streets: string[] = []

  private regionData: RegionDict = {
    '北京市': {
      '北京市': {
        '东城区': ['王府井大街', '长安街', '东华门大街'],
        '西城区': ['西单大街', '复兴门大街', '西华门大街']
      }
    },
    '上海市': {
      '上海市': {
        '黄浦区': ['南京东路', '淮海中路', '西藏中路'],
        '静安区': ['南京西路', '华山路', '常德路']
      }
    },
    '广东省': {
      '广州市': {
        '天河区': ['天河路', '体育西路', '珠江新城'],
        '越秀区': ['中山路', '北京路', '东风路']
      },
      '深圳市': {
        '南山区': ['科技园路', '深南大道', '南海大道'],
        '福田区': ['华强北', '中心区', '岗厦']
      }
    }
  }

  aboutToAppear(): void {
    this.provinces = Object.keys(this.regionData)
    this.flushCityColumn()
  }

  flushCityColumn() {
    let currentProvince = this.provinces[this.provinceIndex]
    this.cities = Object.keys(this.regionData[currentProvince])
    this.cityIndex = 0
    this.flushDistrictColumn()
  }

  flushDistrictColumn() {
    let currentProvince = this.provinces[this.provinceIndex]
    let currentCity = this.cities[this.cityIndex]
    this.districts = Object.keys(this.regionData[currentProvince][currentCity])
    this.districtIndex = 0
    this.flushStreetColumn()
  }

  flushStreetColumn() {
    let currentProvince = this.provinces[this.provinceIndex]
    let currentCity = this.cities[this.cityIndex]
    let currentDistrict = this.districts[this.districtIndex]
    this.streets = this.regionData[currentProvince][currentCity][currentDistrict]
    this.streetIndex = 0
  }

  build() {
    Column() {
      Text('四级地区选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        TextPicker({
          range: this.provinces,
          selected: this.provinceIndex
        })
          .onChange((value: string | string[], index: number | number[]) => {
            this.provinceIndex = index as number
            this.flushCityColumn()
          })
          .width('23%')

        TextPicker({
          range: this.cities,
          selected: this.cityIndex
        })
          .onChange((value: string | string[], index: number | number[]) => {
            this.cityIndex = index as number
            this.flushDistrictColumn()
          })
          .width('23%')

        TextPicker({
          range: this.districts,
          selected: this.districtIndex
        })
          .onChange((value: string | string[], index: number | number[]) => {
            this.districtIndex = index as number
            this.flushStreetColumn()
          })
          .width('23%')

        TextPicker({
          range: this.streets,
          selected: this.streetIndex
        })
          .onChange((value: string | string[], index: number | number[]) => {
            this.streetIndex = index as number
          })
          .width('23%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('提示: 省市区街道四级联动选择')
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
 * TextPickerExample006: 大数据量性能测试
 */
@Component
export struct TextPickerExample006 {
  private largeData: string[] = []
  @State dataSize: number = 100
  @State selectedIndex: number = 0

  aboutToAppear(): void {
    this.generateData()
  }

  generateData() {
    this.largeData = []
    for (let i = 1; i <= this.dataSize; i++) {
      this.largeData.push('数据项 ' + i)
    }
  }

  build() {
    Column() {
      Text('大数据量性能测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.largeData, selected: this.selectedIndex })
        .onChange((value: string | string[], index: number | number[]) => {
          this.selectedIndex = index as number
        })
        .canLoop(true)

      Text('数据量: ' + this.dataSize)
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('100项')
          .onClick(() => {
            this.dataSize = 100
            this.selectedIndex = 0
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('500项')
          .onClick(() => {
            this.dataSize = 500
            this.selectedIndex = 0
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('1000项')
          .onClick(() => {
            this.dataSize = 1000
            this.selectedIndex = 0
            this.generateData()
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('当前选中: ' + this.largeData[this.selectedIndex])
        .fontSize(16)
        .margin({ top: 20 })

      Text('提示: 测试大数据量下的滚动性能')
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
 * TextPickerExample007: 自定义主题示例
 */
@Component
export struct TextPickerExample007 {
  private fruits: string[] = ['apple', 'orange', 'peach', 'grape', 'banana']
  @State theme: string = 'default'

  build() {
    Column() {
      Text('自定义主题示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.theme === 'default') {
        TextPicker({ range: this.fruits })
          .disappearTextStyle({ color: Color.Gray, font: { size: 15 } })
          .textStyle({ color: Color.Black, font: { size: 20 } })
          .selectedTextStyle({ color: Color.Blue, font: { size: 30 } })
      } else if (this.theme === 'dark') {
        TextPicker({ range: this.fruits })
          .disappearTextStyle({ color: '#444444', font: { size: 15 } })
          .textStyle({ color: '#CCCCCC', font: { size: 20 } })
          .selectedTextStyle({ color: '#00D4FF', font: { size: 30 } })
      } else if (this.theme === 'warm') {
        TextPicker({ range: this.fruits })
          .disappearTextStyle({ color: '#FFCCBC', font: { size: 15 } })
          .textStyle({ color: '#FF9800', font: { size: 20 } })
          .selectedTextStyle({ color: '#FF5722', font: { size: 30 } })
      } else if (this.theme === 'cool') {
        TextPicker({ range: this.fruits })
          .disappearTextStyle({ color: '#BBDEFB', font: { size: 15 } })
          .textStyle({ color: '#2196F3', font: { size: 20 } })
          .selectedTextStyle({ color: '#0D47A1', font: { size: 30 } })
      }

      Text('选择主题')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('默认')
          .onClick(() => {
            this.theme = 'default'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('暗色')
          .onClick(() => {
            this.theme = 'dark'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('暖色')
          .onClick(() => {
            this.theme = 'warm'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('冷色')
          .onClick(() => {
            this.theme = 'cool'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 切换不同的主题风格')
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
 * TextPickerExample008: 动态数据更新示例
 */
@Component
export struct TextPickerExample008 {
  @State currentData: string[] = ['apple', 'orange', 'peach']
  @State dataType: string = 'fruits'
  @State selectedIndex: number = 0

  private fruits: string[] = ['apple', 'orange', 'peach', 'grape', 'banana']
  private vegetables: string[] = ['tomato', 'potato', 'carrot', 'cabbage', 'broccoli']
  private drinks: string[] = ['water', 'juice', 'milk', 'coffee', 'tea']

  updateData(type: string) {
    this.dataType = type
    this.selectedIndex = 0
    if (type === 'fruits') {
      this.currentData = this.fruits
    } else if (type === 'vegetables') {
      this.currentData = this.vegetables
    } else if (type === 'drinks') {
      this.currentData = this.drinks
    }
  }

  build() {
    Column() {
      Text('动态数据更新示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.currentData, selected: this.selectedIndex })
        .onChange((value: string | string[], index: number | number[]) => {
          this.selectedIndex = index as number
        })

      Text('当前数据类型: ' + this.dataType)
        .fontSize(14)
        .margin({ top: 20 })

      Text('当前选中: ' + this.currentData[this.selectedIndex])
        .fontSize(16)
        .margin({ top: 10 })

      Text('选择数据类型')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('水果')
          .onClick(() => {
            this.updateData('fruits')
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('蔬菜')
          .onClick(() => {
            this.updateData('vegetables')
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('饮料')
          .onClick(() => {
            this.updateData('drinks')
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 切换数据类型会动态更新选择器内容')
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
 * TextPickerExample009: 自定义高度和间距示例
 */
@Component
export struct TextPickerExample009 {
  private fruits: string[] = []
  @State itemHeight: number = 50
  @State canLoop: boolean = true

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.fruits.push('选项 ' + i)
    }
  }

  build() {
    Column() {
      Text('自定义高度和间距示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .defaultPickerItemHeight(this.itemHeight)
        .canLoop(this.canLoop)

      Text('项目高度: ' + this.itemHeight)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.itemHeight, min: 30, max: 80, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.itemHeight = Math.round(value)
        })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.canLoop = isOn
          })
        Text('循环滚动').fontSize(16)
      }
      .width('70%')
      .margin({ top: 20 })

      Text('提示: 调整滑块改变项目高度，切换开关控制循环')
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
 * TextPickerExample010: 事件日志示例
 */
@Component
export struct TextPickerExample010 {
  private fruits: string[] = ['apple', 'orange', 'peach', 'grape', 'banana']
  @State eventLogs: string[] = []

  addLog(eventName: string, value: string | string[], index: number | number[]) {
    const timestamp = new Date().toLocaleTimeString()
    const log = `${timestamp}: ${eventName} - value: ${JSON.stringify(value)}, index: ${JSON.stringify(index)}`
    this.eventLogs.unshift(log)
    if (this.eventLogs.length > 10) {
      this.eventLogs.pop.pop()
    }
  }

  build() {
    Column() {
      Text('事件日志示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .onChange((value: string | string[], index: number | number[]) => {
          this.addLog('onChange', value, index)
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          this.addLog('onScrollStop', value, index)
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          this.addLog('onEnterSelectedArea', value, index)
        })

      Text('事件日志')
        .fontSize(14)
        .margin({ top: 20 })

      List({ space: 8 }) {
        ForEach(this.eventLogs, (log: string) => {
          ListItem() {
            Text(log)
              .fontSize(12)
              .fontColor('#666666')
          }
        })
      }
      .width('100%')
      .height(200)
      .backgroundColor('#FFFFFF')
      .borderRadius(8)
      .padding(10)

      Text('提示: 滚动选择器查看事件触发顺序')
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
 * TextPickerExample011: 多列复杂联动示例
 */
@Component
export struct TextPickerExample011 {
  @State colorIndex: number = 0
  @State sizeIndex: number = 0
  @State styleIndex: number = 0
  @State result: string = ''

  private colors: string[] = ['红色', '绿色', '蓝色', '黄色', '紫色']
  private sizes: string[] = ['S', 'M', 'L', 'XL', 'XXL']
  private styles: string[] = ['休闲', '正式', '运动', '复古', '时尚']

  updateResult() {
    this.result = `${this.colors[this.colorIndex]} - ${this.sizes[this.sizeIndex]} - ${this.styles[this.styleIndex]}`
  }

  aboutToAppear(): void {
    this.updateResult()
  }

  build() {
    Column() {
      Text('多列复杂联动示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        Column() {
          Text('颜色')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: this.colors,
            selected: this.colorIndex
          })
            .onChange((value: string | string[], index: number | number[]) => {
              this.colorIndex = index as number
              this.updateResult()
            })
        }
        .width('30%')

        Column() {
          Text('尺码')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: this.sizes,
            selected: this.sizeIndex
          })
            .onChange((value: string | string[], index: number | number[]) => {
              this.sizeIndex = index as number
              this.updateResult()
            })
        }
        .width('30%')

        Column() {
          Text('风格')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: this.styles,
            selected: this.styleIndex
          })
            .onChange((value: string | string[], index: number | number[]) => {
              this.styleIndex = index as number
              this.updateResult()
            })
        }
        .width('30%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('选择结果: ' + this.result)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 20 })

      Text('提示: 多列选择器可以组合出多种结果')
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
 * TextPickerExample012: 边界条件测试示例
 */
@Component
export struct TextPickerExample012 {
  @State emptyData: string[] = []
  @State singleData: string[] = ['唯一选项']
  @State twoData: string[] = ['选项1', '选项2']
  @State testData: string = 'empty'

  build() {
    Column() {
      Text('边界条件测试示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.testData === 'empty') {
        Text('空数据测试')
          .fontSize(14)
          .margin({ bottom: 10 })

        TextPicker({ range: this.emptyData })
      } else if (this.testData === 'single') {
        Text('单数据测试')
          .fontSize(14)
          .margin({ bottom: 10 })

        TextPicker({ range: this.singleData })
      } else if (this.testData === 'two') {
        Text('双数据测试')
          .fontSize(14)
          .margin({ bottom: 10 })

        TextPicker({ range: this.twoData })
      }

      Text('选择测试场景')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('空数据')
          .onClick(() => {
            this.testData = 'empty'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('单数据')
          .onClick(() => {
            this.testData = 'single'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('双数据')
          .onClick(() => {
            this.testData = 'two'
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 测试各种边界条件下的选择器行为')
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
 * TextPickerExample013: 自定义列宽百分比示例
 */
@Component
export struct TextPickerExample013 {
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private pefruits: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.apfruits, this.orfruits, this.pefruits]

  private columnWidths1: LengthMetrics[] = [
    LengthMetrics.percent(33),
    LengthMetrics.percent(33),
    LengthMetrics.percent(34)
  ]

  private columnWidths2: LengthMetrics[] = [
    LengthMetrics.percent(20),
    LengthMetrics.percent(50),
    LengthMetrics.percent(30)
  ]

  private columnWidths3: LengthMetrics[] = [
    LengthMetrics.percent(50),
    LengthMetrics.percent(25),
    LengthMetrics.percent(25)
  ]

  @State currentWidths: LengthMetrics[] = this.columnWidths1

  build() {
    Column() {
      Text('自定义列宽百分比示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.multi, columnWidths: this.currentWidths })

      Text('选择列宽比例')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('33:33:34')
          .onClick(() => {
            this.currentWidths = this.columnWidths1
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('20:50:30')
          .onClick(() => {
            this.currentWidths = this.columnWidths2
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('50:25:25')
          .onClick(() => {
            this.currentWidths = this.columnWidths3
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 使用百分比设置列宽，总和应为100%')
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
 * TextPickerExample014: 级联选择器深度测试
 */
@Component
export struct TextPickerExample014 {
  @State level1Index: number = 0
  @State level2Index: number = 0
  @State level3Index: number = 0
  @State level4Index: number = 0
  @State level5Index: number = 0
  @State level1Data: string[] = []
  @State level2Data: string[] = []
  @State level3Data: string[] = []
  @State level4Data: string[] = []
  @State level5Data: string[] = []

  private deepData: Record<string, Record<string, Record<string, Record<string, string[]>>>> = {
    '一级1': {
      '二级1': {
        '三级1': {
          '四级1': ['五级1', '五级2', '五级3'],
          '四级2': ['五级4', '五级5', '五级6']
        },
        '三级2': {
          '四级3': ['五级7', '五级8', '五级9'],
          '四级4': ['五级10', '五级11', '五级12']
        }
      },
      '二级2': {
        '三级3': {
          '四级5': ['五级13', '五级14', '五级15'],
          '四级6': ['五级16', '五级17', '五级18']
        }
      }
    },
    '一级2': {
      '二级3': {
        '三级3': {
          '四级7': ['五级19', '五级20', '五级21']
        }
      }
    }
  }

  aboutToAppear(): void {
    this.level1Data = Object.keys(this.deepData)
    this.flushLevel2()
  }

  flushLevel2() {
    const l1 = this.level1Data[this.level1Index]
    this.level2Data = Object.keys(this.deepData[l1])
    this.level2Index = 0
    this.flushLevel3()
  }

  flushLevel3() {
    const l1 = this.level1Data[this.level1Index]
    const l2 = this.level2Data[this.level2Index]
    this.level3Data = Object.keys(this.deepData[l1][l2])
    this.level3Index = 0
    this.flushLevel4()
  }

  flushLevel4() {
    const l1 = this.level1Data[this.level1Index]
    const l2 = this.level2Data[this.level2Index]
    const l3 = this.level3Data[this.level3Index]
    this.level4Data = Object.keys(this.deepData[l1][l2][l3])
    this.level4Index = 0
    this.flushLevel5()
  }

  flushLevel5() {
    const l1 = this.level1Data[this.level1Index]
    const l2 = this.level2Data[this.level2Index]
    const l3 = this.level3Data[this.level3Index]
    const l4 = this.level4Data[this.level4Index]
    this.level5Data = this.deepData[l1][l2][l3][l4]
    this.level5Index = 0
  }

  build() {
    Column() {
      Text('五级级联选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Scroll() {
        Column({ space: 10 }) {
          Row() {
            TextPicker({
              range: this.level1Data,
              selected: this.level1Index
            })
              .onChange((value: string | string[], index: number | number[]) => {
                this.level1Index = index as number
                this.flushLevel2()
              })
              .width('19%')

            TextPicker({
              range: this.level2Data,
              selected: this.level2Index
            })
              .onChange((value: string | string[], index: number | number[]) => {
                this.level2Index = index as number
                this.flushLevel3()
              })
              .width('19%')

            TextPicker({
              range: this.level3Data,
              selected: this.level3Index
            })
              .onChange((value: string | string[], index: number | number[]) => {
                this.level3Index = index as number
                this.flushLevel4()
              })
              .width('19%')

            TextPicker({
              range: this.level4Data,
              selected: this.level4Index
            })
              .onChange((value: string | string[], index: number | number[]) => {
                this.level4Index = index as number
                this.flushLevel5()
              })
              .width('19%')

            TextPicker({
              range: this.level5Data,
              selected: this.level5Index
            })
              .onChange((value: string | string[], index: number | number[]) => {
                this.level5Index = index as number
              })
              .width('19%')
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }
      }

      Text('提示: 五级深度级联选择器测试')
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
 * TextPickerExample015: 字体样式组合示例
 */
@Component
export struct TextPickerExample015 {
  private fruits: string[] = ['apple', 'orange', 'peach', 'grape', 'banana']
  @State selectedWeight: number = 700
  @State normalWeight: number = 400
  @State disappearWeight: number = 300

  build() {
    Column() {
      Text('字体样式组合示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .disappearTextStyle({
          color: Color.Gray,
          font: {
            size: 15,
            weight: this.disappearWeight,
            style: FontStyle.Italic
          }
        })
        .textStyle({
          color: Color.Black,
          font: {
            size: 20,
            weight: this.normalWeight,
            style: FontStyle.Normal
          }
        })
        .selectedTextStyle({
          color: Color.Blue,
          font: {
            size: 30,
            weight: this.selectedWeight,
            style: FontStyle.Normal
          }
        })

      Text('选中项字重: ' + this.selectedWeight)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.selectedWeight, min: 100, max: 900, step: 100 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.selectedWeight = Math.round(value)
        })

      Text('提示: 调整字重来改变字体粗细')
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
 * TextPickerExample016: 实际应用-身高体重选择器
 */
@Component
export struct TextPickerExample016 {
  private heights: string[] = []
  private weights: string[] = []
  @State heightIndex: number = 0
  @State weightIndex: number = 0
  @State bmi: number = 0

  aboutToAppear(): void {
    for (let i = 100; i <= 220; i++) {
      this.heights.push(i.toString() + 'cm')
    }
    for (let i = 30; i <= 150; i++) {
      this.weights.push(i.toString() + 'kg')
    }
    this.heightIndex = 70
    this.weightIndex = 50
    this.calculateBMI()
  }

  calculateBMI() {
    const height = (this.heightIndex + 100) / 100
    const weight = this.weightIndex + 30
    this.bmi = weight / (height * height)
  }

  build() {
    Column() {
      Text('身高体重选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        Column() {
          Text('身高')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: this.heights,
            selected: this.heightIndex
          })
            .onChange((value: string | string[], index: number | number[]) => {
              this.heightIndex = index as number
              this.calculateBMI()
            })
        }
        .width('48%')

        Column() {
          Text('体重')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: this.weights,
            selected: this.weightIndex
          })
            .onChange((value: string | string[], index: number | number[]) => {
              this.weightIndex = index as number
              this.calculateBMI()
            })
        }
        .width('48%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('BMI指数: ' + this.bmi.toFixed(2))
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 20 })

      Text(this.getBMIDescription())
        .fontSize(14)
        .fontColor('#666666')
        .margin({ top: 10 })

      Text('提示: 选择身高和体重自动计算BMI')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }

  getBMIDescription(): string {
    if (this.bmi < 18.5) return '偏瘦'
    if (this.bmi < 24) return '正常'
    if (this.bmi < 28) return '偏胖'
    return '肥胖'
  }
}

/**
 * TextPickerExample017: 实际应用-时间范围选择器
 */
@Component
export struct TextPickerExample017 {
  private hours: string[] = []
  private minutes: string[] = []
  @State startHourIndex: number = 0
  @State startMinuteIndex: number = 0
  @State endHourIndex: number = 0
  @State endMinuteIndex: number = 0
  @State timeRange: string = ''

  aboutToAppear(): void {
    for (let i = 0; i <= 23; i++) {
      this.hours.push(i.toString().padStart(2, '0'))
    }
    for (let i = 0; i <= 59; i++) {
      this.minutes.push(i.toString().padStart(2, '0'))
    }
    this.startHourIndex = 9
    this.endHourIndex = 18
    this.updateTimeRange()
  }

  updateTimeRange()() {
    const startHour = this.hours[this.startHourIndex]
    const startMinute = this.minutes[this.startMinuteIndex]
    const endHour = this.hours[this.endHourIndex]
    const endMinute = this.minutes[this.endMinuteIndex]
    this.timeRange = `${startHour}:${startMinute} - ${endHour}:${endMinute}`
  }

  build() {
    Column() {
      Text('时间范围选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        Column() {
          Text('开始时间')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: [this.hours, this.minutes],
            selected: [this.startHourIndex, this.startMinuteIndex]
          })
            .onChange((value: string | string[], index: number | number[]) => {
              const idx = index as number[]
              this.startHourIndex = idx[0]
              this.startMinuteIndex = idx[1]
              this.updateTimeRange()
            })
        }
        .width('48%')

        Column() {
          Text('结束时间')
            .fontSize(14)
            .margin({ bottom: 10 })

          TextPicker({
            range: [this.hours, this.minutes],
            selected: [this.endHourIndex, this.endMinuteIndex]
          })
            .onChange((value: string | string[], index: number | number[]) => {
              const idx = index as number[]
              this.endHourIndex = idx[0]
              this.endMinuteIndex = idx[1]
              this.updateTimeRange()
            })
        }
        .width('48%')
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Text('时间范围: ' + this.timeRange)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 20 })

      Text('提示: 选择开始和结束时间')
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
 * TextPickerExample018: 性能对比示例
 */
@Component
export struct TextPickerExample018 {
  private smallData: string[] = []
  private mediumData: string[] = []
  private largeData: string[] = []
  @State selectedData: string[] = []
  @State selectedIndex: number = 0

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.smallData.push('数据 ' + i)
    }
    for (let i = 1; i <= 100; i++) {
      this.mediumData.push('数据 ' + i)
    }
    for (let i = 1; i <= 500; i++) {
      this.largeData.push('数据 ' + i)
    }
    this.selectedData = this.smallData
  }

  build() {
    Column() {
      Text('性能对比示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.selectedData, selected: this.selectedIndex })
        .canLoop(true)
        .onChange((value: string | string[], index: number | number[]) => {
          this.selectedIndex = index as number
        })

      Text('当前数据量: ' + this.selectedData.length)
        .fontSize(14)
        .margin({ top: 20 })

      Text('当前选中: ' + this.selectedData[this.selectedIndex])
        .fontSize(16)
        .margin({ top: 10 })

      Text('选择数据量')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('10项')
          .onClick(() => {
            this.selectedData = this.smallData
            this.selectedIndex = 0
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('100项')
          .onClick(() => {
            this.selectedData = this.mediumData
            this.selectedIndex = 0
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('500项')
          .onClick(() => {
            this.selectedData = this.largeData
            this.selectedIndex = 0
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
     .width('70%')
      .margin({ top: 10 })

      Text('提示: 对比不同数据量下的滚动性能')
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
 * TextPickerExample019: 样式组合测试示例
 */
@Component
export struct TextPickerExample019 {
  private fruits: string[] = []
  @State selectedSize: number = 30
  @State selectedColor: Color = Color.Blue
  @State itemHeight: number = 50
  @State canLoop: boolean = true

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.fruits.push('选项 ' + i)
    }
  }

  build() {
    Column() {
      Text('样式组合测试示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .disappearTextStyle({
          color: Color.Gray,
          font: { size: 15, weight: FontWeight.Lighter }
        })
        .textStyle({
          color: Color.Black,
          font: { size: 20, weight: FontWeight.Normal }
        })
        .selectedTextStyle({
          color: this.selectedColor,
          font: { size: this.selectedSize, weight: FontWeight.Bolder }
        })
        .defaultPickerItemHeight(this.itemHeight)
        .canLoop(this.canLoop)

      Text('选中项大小: ' + this.selectedSize)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.selectedSize, min: 20, max: 40, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.selectedSize = Math.round(value)
        })

      Text('项目高度: ' + this.itemHeight)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.itemHeight, min: 30, max: 80, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.itemHeight = Math.round(value)
        })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.canLoop = isOn
          })
        Text('循环滚动').fontSize(16)
      }
      .width('70%')
      .margin({ top: 20 })

      Text('提示: 组合多种样式属性')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
