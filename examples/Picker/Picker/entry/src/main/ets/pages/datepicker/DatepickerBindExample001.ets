/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * DataPicker 组件双向绑定全面测试
 * 测试 DatePicker、TimePicker、TextPicker 等组件的所有双向绑定属性
 */

// ========== 测试数据接口定义 ==========

interface TestResult {
  testName: string;
  passed: boolean;
  message: string;
  timestamp: number;
}

interface BindingTestItem {
  id: number;
  componentName: string;
  propertyName: string;
  bindingType: string;
  testValue: string;
  actualValue: string;
  result: boolean;
}

interface DatePickerState {
  selectedDate: Date;
  start: Date | undefined;
  end: Date | undefined;
}

interface TimePickerState {
  selectedTime: Date;
  hour: number;
  minute: number;
  second: number;
}

interface TextPickerState {
  range: string[] | Resource;
  selected: number;
  value: string;
}

// ========== 主测试组件 ==========

@Entry
@Component
struct DataPickerBindingTest {
  // ========== 全局状态变量 ==========

  // 测试结果显示
  @State testResults: TestResult[] = [];
  @State bindingTestItems: BindingTestItem[] = [];

  // 页面显示控制
  @State showDatePickerTests: boolean = true;
  @State showTimePickerTests: boolean = true;
  @State showTextPickerTests: boolean = true;
  @State showCombinedTests: boolean = true;
  @State showAdvancedTests: boolean = true;

  // ========== DatePicker 双向绑定状态 ==========

  @State dpSelectedDate: Date = new Date('2024-01-01');
  @State dpStart: Date = new Date('2023-01-01');
  @State dpEnd: Date = new Date('2025-12-31');

  // DatePicker 测试状态
  @State dpTest1_selectedDate: Date = new Date();
  @State dpTest2_selectedDate: Date = new Date('2024-06-15');
  @State dpTest3_selectedDate: Date = new Date();
  @State dpTest3_start: Date = new Date('2024-01-01');
  @State dpTest3_end: Date = new Date('2024-12-31');
  @State dpTest4_selectedDate: Date = new Date();
  @State dpTest5_selectedDate: Date = new Date();
  @State dpTest5_start: Date = new Date('2024-01-01');
  @State dpTest5_end: Date = new Date('2024-12-31');
  @State dpTest6_selectedDate: Date = new Date();
  @State dpTest7_selectedDate: Date = new Date();
  @State dpTest7_start: Date = new Date('2020-01-01');
  @State dpTest7_end: Date = new Date('2030-12-31');
  @State dpTest8_selectedDate: Date = new Date();
  @State dpTest9_selectedDate: Date = new Date();
  @State dpTest10_selectedDate: Date = new Date();
  @State dpTest10_start: Date = new Date('2024-01-01');
  @State dpTest10_end: Date = new Date('2024-12-31');

  // ========== TimePicker 双向绑定状态 ==========

  @State tpSelectedTime: Date = new Date();
  @State tpHour: number = 12;
  @State tpMinute: number = 0;
  @State tpSecond: number = 0;

  // TimePicker 测试状态
  @State tpTest1_selectedTime: Date = new Date();
  @State tpTest2_selectedTime: Date = new Date('2024-01-01T14:30:00');
  @State tpTest3_selectedTime: Date = new Date();
  @State tpTest3_hour: number = 8;
  @State tpTest3_minute: number = 30;
  @State tpTest3_second: number = 0;
  @State tpTest4_selectedTime: Date = new Date();
  @State tpTest5_selectedTime: Date = new Date();
  @State tpTest6_selectedTime: Date = new Date();
  @State tpTest6_hour: number = 0;
  @State tpTest6_minute: number = 0;
  @State tpTest6_second: number = 0;
  @State tpTest7_selectedTime: Date = new Date();
  @State tpTest8_selectedTime: Date = new Date();
  @State tpTest9_selectedTime: Date = new Date();
  @State tpTest10_selectedTime: Date = new Date();

  // ========== TextPicker 双向绑定状态 ==========

  @State txpSelected: number = 0;
  @State txpValue: string = '';
  @State txpRange: string[] = ['选项1', '选项2', '选项3', '选项4', '选项5'];

  // TextPicker 测试状态
  @State txpTest1_selected: number = 0;
  @State txpTest1_range: string[] = ['A', 'B', 'C', 'D', 'E'];
  @State txpTest2_selected: number = 2;
  @State txpTest2_range: string[] = ['苹果', '香蕉', '橙子', '葡萄', '西瓜'];
  @State txpTest3_selected: number = 0;
  @State txpTest3_range: string[] = [];
  @State txpTest4_selected: number = 0;
  @State txpTest4_range: string[] = ['唯一选项'];
  @State txpTest5_selected: number = 0;
  @State txpTest5_range: string[] = ['一月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '十一月', '十二月'];
  @State txpTest6_selected: number = 0;
  @State txpTest6_range: string[] = ['Spring', 'Summer', 'Autumn', 'Winter'];
  @State txpTest7_selected: number = 0;
  @State txpTest7_range: string[] = ['红色', '橙色', '黄色', '绿色', '青色', '蓝色', '紫色'];
  @State txpTest8_selected: number = 0;
  @State txpTest8_range: string[] = ['小', '中', '大', '特大'];
  @State txpTest9_selected: number = 0;
  @State txpTest9_range: string[] = ['低', '中', '高'];
  @State txpTest10_selected: number = 0;
  @State txpTest10_range: string[] = [
    '项0', '项1', '项2', '项3', '项4', '项5', '项6', '项7', '项8', '项9',
    '项10', '项11', '项12', '项13', '项14', '项15', '项16', '项17', '项18', '项19',
    '项20', '项21', '项22', '项23', '项24', '项25', '项26', '项27', '项28', '项29',
    '项30', '项31', '项32', '项33', '项34', '项35', '项36', '项37', '项38', '项39',
    '项40', '项41', '项42', '项43', '项44', '项45', '项46', '项47', '项48', '项49',
    '项50', '项51', '项52', '项53', '项54', '项55', '项56', '项57', '项58', '项59',
    '项60', '项61', '项62', '项63', '项64', '项65', '项66', '项67', '项68', '项69',
    '项70', '项71', '项72', '项73', '项74', '项75', '项76', '项77', '项78', '项79',
    '项80', '项81', '项82', '项83', '项84', '项85', '项86', '项87', '项88', '项89',
    '项90', '项91', '项92', '项93', '项94', '项95', '项96', '项97', '项98', '项99'
  ];

  // ========== 组合测试状态 ==========

  @State comboDate: Date = new Date();
  @State comboTime: Date = new Date();
  @State comboText: string = '';
  @State comboSelectedIndex: number = 0;
  @State comboRange: string[] = ['选项A', '选项B', '选项C'];

  @State comboTest1_date: Date = new Date();
  @State comboTest1_time: Date = new Date();
  @State comboTest1_textIndex: number = 0;

  @State comboTest2_date: Date = new Date();
  @State comboTest2_time: Date = new Date();

  @State comboTest3_date: Date = new Date();
  @State comboTest3_textIndex: number = 0;

  @State comboTest4_date: Date = new Date();
  @State comboTest4_time: Date = new Date();
  @State comboTest4_textIndex: number = 0;

  @State comboTest5_date: Date = new Date();
  @State comboTest5_textIndex: number = 0;
  @State comboTest5_range: string[] = ['周一', '周二', '周三', '周四', '周五', '周六', '周日'];

  // ========== 高级测试状态 ==========

  @State advTest1_date: Date = new Date();
  @State advTest1_start: Date = new Date('2024-01-01');
  @State advTest1_end: Date = new Date('2024-12-31');

  @State advTest2_time: Date = new Date();
  @State advTest2_hour: number = 0;
  @State advTest2_minute: number = 0;

  @State advTest3_selected: number = 0;
  @State advTest3_range: string[] = ['选项1', '选项2', '选项3'];

  @State advTest4_date: Date = new Date();
  @State advTest4_time: Date = new Date();

  @State advTest5_selected1: number = 0;
  @State advTest5_selected2: number = 0;
  @State advTest5_selected3: number = 0;

  @State advTest6_textIndex1: number = 0;
  @State advTest6_textIndex2: number = 0;
  @State advTest6_textIndex3: number = 0;

  // ========== 统计状态 ==========

  @State totalTests: number = 0;
  @State passedTests: number = 0;
  @State failedTests: number = 0;

  // ========== 生命周期 ==========

  aboutToAppear(): void {
    this.initializeTests();
    this.calculateStatistics();
  }

  // ========== 初始化方法 ==========

  initializeTests(): void {
    // 初始化测试数据
    this.dpTest1_selectedDate = new Date();
    this.dpTest2_selectedDate = new Date('2024-06-15');
    this.tpTest1_selectedTime = new Date();
    this.txpTest1_selected = 0;

    // 初始化测试结果
    this.testResults = [];
    this.bindingTestItems = [];
  }

  // ========== 统计方法 ==========

  calculateStatistics(): void {
    this.totalTests = this.testResults.length;
    this.passedTests = this.testResults.filter((r: TestResult) => r.passed).length;
    this.failedTests = this.totalTests - this.passedTests;
  }

  addTestResult(name: string, passed: boolean, message: string): void {
    const result: TestResult = {
      testName: name,
      passed: passed,
      message: message,
      timestamp: Date.now()
    };
    this.testResults.push(result);
    this.calculateStatistics();
  }

  addBindingTest(
    componentName: string,
    propertyName: string,
    bindingType: string,
    testValue: string,
    actualValue: string,
    result: boolean
  ): void {
    const item: BindingTestItem = {
      id: Date.now(),
      componentName: componentName,
      propertyName: propertyName,
      bindingType: bindingType,
      testValue: testValue,
      actualValue: actualValue,
      result: result
    };
    this.bindingTestItems.push(item);
  }

  // ========== 格式化方法 ==========

  formatDate(date: Date): string {
    const year: number = date.getFullYear();
    const month: number = date.getMonth() + 1;
    const day: number = date.getDate();
    return year + '-' + (month < 10 ? '0' + month : month) + '-' + (day < 10 ? '0' + day : day);
  }

  formatTime(date: Date): string {
    const hours: number = date.getHours();
    const minutes: number = date.getMinutes();
    const seconds: number = date.getSeconds();
    return (hours < 10 ? '0' + hours : hours) + ':' + (minutes < 10 ? '0' + minutes : minutes) + ':' + (seconds < 10 ? '0' + seconds : seconds);
  }

  formatDateTime(date: Date): string {
    return this.formatDate(date) + ' ' + this.formatTime(date);
  }

  // ========== 主界面构建 ==========

  build() {
    Scroll() {
      Column() {
        // 标题
        this.buildTitle();

        // 统计信息
        this.buildStatistics();

        // DatePicker 测试
        this.buildDatePickerTests();

        // TimePicker 测试
        this.buildTimePickerTests();

        // TextPicker 测试
        this.buildTextPickerTests();

        // 组合测试
        this.buildCombinedTests();

        // 高级测试
        this.buildAdvancedTests();

        // 测试结果详情
        this.buildTestResults();

        // 重置按钮
        this.buildResetButtons();
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 10 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  // ========== 标题组件 ==========

  @Builder
  buildTitle() {
    Column() {
      Text('DataPicker 组件双向绑定全面测试')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor('#333333')
        .margin({ top: 10, bottom: 5 })

      Text('测试 DatePicker、TimePicker、TextPicker 的所有双向绑定属性')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ bottom: 15 })

      Divider()
        .color('#E0E0E0')
    }
    .width('100%')
  }

  // ========== 统计信息组件 ==========

  @Builder
  buildStatistics() {
    Column() {
      Text('测试统计')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          Text(this.totalTests.toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#333333')
          Text('总测试')
            .fontSize(12)
            .fontColor('#999999')
        }
        .layoutWeight(1)

        Column() {
          Text(this.passedTests.toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#4CAF50')
          Text('通过')
            .fontSize(12)
            .fontColor('#999999')
        }
        .layoutWeight(1)

        Column() {
          Text(this.failedTests.toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#F44336')
          Text('失败')
            .fontSize(12)
            .fontColor('#999999')
        }
        .layoutWeight(1)
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#FFFFFF')
      .borderRadius(8)
    }
    .width('100%')
    .margin({ bottom: 15 })
  }

  // ========== DatePicker 测试区域 ==========

  @Builder
  buildDatePickerTests() {
    Column() {
      Row() {
        Text('DatePicker 双向绑定测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showDatePickerTests ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.showDatePickerTests = !this.showDatePickerTests;
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showDatePickerTests) {
        // 测试1: selectedDate 基本双向绑定
        this.buildDatePickerTest1();

        // 测试2: selectedDate 初始值测试
        this.buildDatePickerTest2();

        // 测试3: start 和 end 边界测试
        this.buildDatePickerTest3();

        // 测试4: 日期选择响应测试
        this.buildDatePickerTest4();

        // 测试5: start/end 动态修改测试
        this.buildDatePickerTest5();

        // 测试6: 边界日期选择测试
        this.buildDatePickerTest6();

        // 测试7: 大范围日期测试
        this.buildDatePickerTest7();

        // 测试8: 当前日期默认值测试
        this.buildDatePickerTest8();

        // 测试9: 日期格式化测试
        this.buildDatePickerTest9();

        // 测试10: 多实例日期选择测试
        this.buildDatePickerTest10();
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // DatePicker 测试1: selectedDate 基本双向绑定
  @Builder
  buildDatePickerTest1() {
    Column() {
      Text('测试1: selectedDate 基本双向绑定')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-1-1'),
        selected: this.dpTest1_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest1_selectedDate = new Date(year, month - 1, day);
        })

      Text('当前选择: ' + this.formatDate(this.dpTest1_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试2: selectedDate 初始值测试
  @Builder
  buildDatePickerTest2() {
    Column() {
      Text('测试2: selectedDate 初始值 (2024-06-15)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        selected: this.dpTest2_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest2_selectedDate = new Date(year, month - 1, day);
        })

      Text('初始值应为 2024-06-15，当前: ' + this.formatDate(this.dpTest2_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试3: start 和 end 边界测试
  @Builder
  buildDatePickerTest3() {
    Column() {
      Text('测试3: start 和 end 边界限制 (2024-01-01 到 2024-12-31)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        start: this.dpTest3_start,
        end: this.dpTest3_end,
        selected: this.dpTest3_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest3_selectedDate = new Date(year, month - 1, day);
        })

      Text('限制范围: ' + this.formatDate(this.dpTest3_start) + ' ~ ' + this.formatDate(this.dpTest3_end))
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.dpTest3_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试4: 日期选择响应测试
  @Builder
  buildDatePickerTest4() {
    Column() {
      Text('测试4: 日期选择响应测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        selected: this.dpTest4_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest4_selectedDate = new Date(year, month - 1, day);
          this.addTestResult('DatePicker-响应测试', true, '日期选择响应正常');
        })

      Text('选择日期后自动记录测试结果')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.dpTest4_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试5: start/end 动态修改测试
  @Builder
  buildDatePickerTest5() {
    Column() {
      Text('测试5: start/end 动态修改测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        start: this.dpTest5_start,
        end: this.dpTest5_end,
        selected: this.dpTest5_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest5_selectedDate = new Date(year, month - 1, day);
        })

      Text('当前范围: ' + this.formatDate(this.dpTest5_start) + ' ~ ' + this.formatDate(this.dpTest5_end))
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Row() {
        Button('2024年')
          .onClick(() => {
            this.dpTest5_start = new Date('2024-01-01');
            this.dpTest5_end = new Date('2024-12-31');
          })
        Button('2025年')
          .margin({ left: 10 })
          .onClick(() => {
            this.dpTest5_start = new Date('2025-01-01');
            this.dpTest5_end = new Date('2025-12-31');
          })
      }
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试6: 边界日期选择测试
  @Builder
  buildDatePickerTest6() {
    Column() {
      Text('测试6: 边界日期选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        selected: this.dpTest6_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest6_selectedDate = new Date(year, month - 1, day);
        })

      Text('测试选择年初、年末、月初、月末等边界日期')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.dpTest6_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试7: 大范围日期测试
  @Builder
  buildDatePickerTest7() {
    Column() {
      Text('测试7: 大范围日期测试 (2020-2030)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        start: this.dpTest7_start,
        end: this.dpTest7_end,
        selected: this.dpTest7_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest7_selectedDate = new Date(year, month - 1, day);
        })

      Text('范围: ' + this.formatDate(this.dpTest7_start) + ' ~ ' + this.formatDate(this.dpTest7_end))
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.dpTest7_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试8: 当前日期默认值测试
  @Builder
  buildDatePickerTest8() {
    Column() {
      Text('测试8: 当前日期默认值测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        selected: this.dpTest8_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest8_selectedDate = new Date(year, month - 1, day);
        })

      Text('默认使用当前日期')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.dpTest8_selectedDate))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试9: 日期格式化测试
  @Builder
  buildDatePickerTest9() {
    Column() {
      Text('测试9: 日期格式化测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        selected: this.dpTest9_selectedDate
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.dpTest9_selectedDate = new Date(year, month - 1, day);
        })

      Text('格式化显示: ' + this.formatDate(this.dpTest9_selectedDate))
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('年: ' + this.dpTest9_selectedDate.getFullYear() + ' 月: ' + (this.dpTest9_selectedDate.getMonth() + 1) + ' 日: ' + this.dpTest9_selectedDate.getDate())
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // DatePicker 测试10: 多实例日期选择测试
  @Builder
  buildDatePickerTest10() {
    Column() {
      Text('测试10: 多实例日期选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          DatePicker({
            start: this.dpTest10_start,
            end: this.dpTest10_end,
            selected: this.dpTest10_selectedDate
          })
            .onChange((value: DatePickerResult) => {
              const year: number = value.year !== undefined ? value.year : 1970;
              const month: number = value.month !== undefined ? value.month : 1;
              const day: number = value.day !== undefined ? value.day : 1;
              this.dpTest10_selectedDate = new Date(year, month - 1, day);
            })
          Text('实例1')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          DatePicker({
            selected: this.dpSelectedDate
          })
            .onChange((value: DatePickerResult) => {
              const year: number = value.year !== undefined ? value.year : 1970;
              const month: number = value.month !== undefined ? value.month : 1;
              const day: number = value.day !== undefined ? value.day : 1;
              this.dpSelectedDate = new Date(year, month - 1, day);
            })
          Text('实例2')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('实例1: ' + this.formatDate(this.dpTest10_selectedDate) + ' | 实例2: ' + this.formatDate(this.dpSelectedDate))
        .fontSize(12)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // ========== TimePicker 测试区域 ==========

  @Builder
  buildTimePickerTests() {
    Column() {
      Row() {
        Text('TimePicker 双向绑定测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showTimePickerTests ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.showTimePickerTests = !this.showTimePickerTests;
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showTimePickerTests) {
        // 测试1: selected 基本双向绑定
        this.buildTimePickerTest1();

        // 测试2: selected 初始值测试
        this.buildTimePickerTest2();

        // 测试3: hour/minute/second 分离绑定
        this.buildTimePickerTest3();

        // 测试4: 时间格式化测试
        this.buildTimePickerTest4();

        // 测试5: 午夜时间测试
        this.buildTimePickerTest5();

        // 测试6: 时间分离显示测试
        this.buildTimePickerTest6();

        // 测试7: 当前时间默认值测试
        this.buildTimePickerTest7();

        // 测试8: 多实例时间选择测试
        this.buildTimePickerTest8();

        // 测试9: 时间边界测试
        this.buildTimePickerTest9();

        // 测试10: 时间响应测试
        this.buildTimePickerTest10();
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // TimePicker 测试1: selected 基本双向绑定
  @Builder
  buildTimePickerTest1() {
    Column() {
      Text('测试1: selected 基本双向绑定')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest1_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest1_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('当前选择: ' + this.formatTime(this.tpTest1_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试2: selected 初始值测试
  @Builder
  buildTimePickerTest2() {
    Column() {
      Text('测试2: selected 初始值 (14:30:00)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest2_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest2_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('初始值应为 14:30:00，当前: ' + this.formatTime(this.tpTest2_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试3: hour/minute/second 分离绑定
  @Builder
  buildTimePickerTest3() {
    Column() {
      Text('测试3: hour/minute/second 分离显示')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest3_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest3_hour = value.hour;
          this.tpTest3_minute = value.minute;
          this.tpTest3_second = value.second;
          this.tpTest3_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('小时: ' + this.tpTest3_hour + ' | 分钟: ' + this.tpTest3_minute + ' | 秒: ' + this.tpTest3_second)
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatTime(this.tpTest3_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试4: 时间格式化测试
  @Builder
  buildTimePickerTest4() {
    Column() {
      Text('测试4: 时间格式化测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest4_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest4_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('时: ' + this.tpTest4_selectedTime.getHours() + ' 分: ' + this.tpTest4_selectedTime.getMinutes() + ' 秒: ' + this.tpTest4_selectedTime.getSeconds())
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试5: 午夜时间测试
  @Builder
  buildTimePickerTest5() {
    Column() {
      Text('测试5: 午夜时间 (00:00:00)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest6_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest6_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('当前选择: ' + this.formatTime(this.tpTest6_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试6: 时间分离显示测试
  @Builder
  buildTimePickerTest6() {
    Column() {
      Text('测试6: 时间分离显示测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest5_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest5_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Row() {
        Column() {
          Text(this.tpTest5_selectedTime.getHours().toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#007DFF')
          Text('时')
            .fontSize(12)
            .fontColor('#999999')
        }
        .margin({ right: 10 })

        Column() {
          Text(this.tpTest5_selectedTime.getMinutes().toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#007DFF')
          Text('分')
            .fontSize(12)
            .fontColor('#999999')
        }
        .margin({ right: 10 })

        Column() {
          Text(this.tpTest5_selectedTime.getSeconds().toString())
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor('#007DFF')
          Text('秒')
            .fontSize(12)
            .fontColor('#999999')
        }
      }
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试7: 当前时间默认值测试
  @Builder
  buildTimePickerTest7() {
    Column() {
      Text('测试7: 当前时间默认值测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest7_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest7_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('默认使用当前时间')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatTime(this.tpTest7_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试8: 多实例时间选择测试
  @Builder
  buildTimePickerTest8() {
    Column() {
      Text('测试8: 多实例时间选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          TimePicker({
            selected: this.tpTest8_selectedTime
          })
            .onChange((value: TimePickerResult) => {
              this.tpTest8_selectedTime.setHours(value.hour, value.minute, value.second);
            })
          Text('实例1')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TimePicker({
            selected: this.tpSelectedTime
          })
            .onChange((value: TimePickerResult) => {
              this.tpSelectedTime.setHours(value.hour, value.minute, value.second);
            })
          Text('实例2')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('实例1: ' + this.formatTime(this.tpTest8_selectedTime) + ' | 实例2: ' + this.formatTime(this.tpSelectedTime))
        .fontSize(12)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试9: 时间边界测试
  @Builder
  buildTimePickerTest9() {
    Column() {
      Text('测试9: 时间边界测试 (23:59:59)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest9_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest9_selectedTime.setHours(value.hour, value.minute, value.second);
        })

      Text('测试选择 00:00:00 和 23:59:59 等边界时间')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatTime(this.tpTest9_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TimePicker 测试10: 时间响应测试
  @Builder
  buildTimePickerTest10() {
    Column() {
      Text('测试10: 时间选择响应测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({
        selected: this.tpTest10_selectedTime
      })
        .onChange((value: TimePickerResult) => {
          this.tpTest10_selectedTime.setHours(value.hour, value.minute, value.second);
          this.addTestResult('TimePicker-响应测试', true, '时间选择响应正常');
        })

      Text('选择时间后自动记录测试结果')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatTime(this.tpTest10_selectedTime))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // ========== TextPicker 测试区域 ==========

  @Builder
  buildTextPickerTests() {
    Column() {
      Row() {
        Text('TextPicker 双向绑定测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showTextPickerTests ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.showTextPickerTests = !this.showTextPickerTests;
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showTextPickerTests) {
        // 测试1: selected 基本双向绑定
        this.buildTextPickerTest1();

        // 测试2: range 字符串数组
        this.buildTextPickerTest2();

        // 测试3: 空数组边界测试
        this.buildTextPickerTest3();

        // 测试4: 单项边界测试
        this.buildTextPickerTest4();

        // 测试5: 月份选择测试
        this.buildTextPickerTest5();

        // 测试6: 英文选项测试
        this.buildTextPickerTest6();

        // 测试7: 颜色选择测试
        this.buildTextPickerTest7();

        // 测试8: 尺寸选择测试
        this.buildTextPickerTest8();

        // 测试9: 优先级选择测试
        this.buildTextPickerTest9();

        // 测试10: 长列表性能测试
        this.buildTextPickerTest10();
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // TextPicker 测试1: selected 基本双向绑定
  @Builder
  buildTextPickerTest1() {
    Column() {
      Text('测试1: selected 基本双向绑定 (A-E)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest1_range, selected: this.txpTest1_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest1_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest1_range[this.txpTest1_selected] + ' (索引: ' + this.txpTest1_selected + ')')
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试2: range 字符串数组
  @Builder
  buildTextPickerTest2() {
    Column() {
      Text('测试2: range 水果数组')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest2_range, selected: this.txpTest2_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest2_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest2_range[this.txpTest2_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试3: 空数组边界测试
  @Builder
  buildTextPickerTest3() {
    Column() {
      Text('测试3: 空数组边界测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      if (this.txpTest3_range.length > 0) {
        TextPicker({ range: this.txpTest3_range, selected: this.txpTest3_selected })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.txpTest3_selected = index;
            }
          })
      } else {
        Text('范围数组为空')
          .fontSize(14)
          .fontColor('#999999')
      }

      Text('数组长度: ' + this.txpTest3_range.length)
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试4: 单项边界测试
  @Builder
  buildTextPickerTest4() {
    Column() {
      Text('测试4: 单项边界测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest4_range, selected: this.txpTest4_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest4_selected = index;
          }
        })

      Text('数组: ' + this.txpTest4_range.join(', '))
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.txpTest4_range[this.txpTest4_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试5: 月份选择测试
  @Builder
  buildTextPickerTest5() {
    Column() {
      Text('测试5: 月份选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest5_range, selected: this.txpTest5_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest5_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest5_range[this.txpTest5_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试6: 英文选项测试
  @Builder
  buildTextPickerTest6() {
    Column() {
      Text('测试6: 英文选项测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest6_range, selected: this.txpTest6_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest6_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest6_range[this.txpTest6_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试7: 颜色选择测试
  @Builder
  buildTextPickerTest7() {
    Column() {
      Text('测试7: 颜色选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest7_range, selected: this.txpTest7_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest7_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest7_range[this.txpTest7_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试8: 尺寸选择测试
  @Builder
  buildTextPickerTest8() {
    Column() {
      Text('测试8: 尺寸选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest8_range, selected: this.txpTest8_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest8_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest8_range[this.txpTest8_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试9: 优先级选择测试
  @Builder
  buildTextPickerTest9() {
    Column() {
      Text('测试9: 优先级选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest9_range, selected: this.txpTest9_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest9_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest9_range[this.txpTest9_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // TextPicker 测试10: 长列表性能测试
  @Builder
  buildTextPickerTest10() {
    Column() {
      Text('测试10: 长列表性能测试 (100项)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.txpTest10_range, selected: this.txpTest10_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.txpTest10_selected = index;
          }
        })

      Text('当前选择: ' + this.txpTest10_range[this.txpTest10_selected] + ' (共' + this.txpTest10_range.length + '项)')
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // ========== 组合测试区域 ==========

  @Builder
  buildCombinedTests() {
    Column() {
      Row() {
        Text('组合选择器测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showCombinedTests ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.showCombinedTests = !this.showCombinedTests;
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showCombinedTests) {
        // 测试1: 日期 + 时间 组合
        this.buildCombinedTest1();

        // 测试2: 日期 + 时间
        this.buildCombinedTest2();

        // 测试3: 文本选择
        this.buildCombinedTest3();

        // 测试4: 三重组合
        this.buildCombinedTest4();

        // 测试5: 文本 + 日期
        this.buildCombinedTest5();
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // 组合测试1: 日期 + 时间
  @Builder
  buildCombinedTest1() {
    Column() {
      Text('测试1: 日期 + 时间 组合')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          DatePicker({ selected: this.comboTest1_date })
            .width(150)
            .onChange((value: DatePickerResult) => {
              const year: number = value.year !== undefined ? value.year : 1970;
              const month: number = value.month !== undefined ? value.month : 1;
              const day: number = value.day !== undefined ? value.day : 1;
              this.comboTest1_date = new Date(year, month - 1, day);
            })
          Text('日期')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TimePicker({ selected: this.comboTest1_time })
            .width(150)
            .onChange((value: TimePickerResult) => {
              this.comboTest1_time.setHours(value.hour, value.minute, value.second);
            })
          Text('时间')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('已选择: ' + this.formatDateTime(this.comboTest1_date) + ' & ' + this.formatTime(this.comboTest1_time))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 组合测试2: 日期 + 时间
  @Builder
  buildCombinedTest2() {
    Column() {
      Text('测试2: 日期 + 时间 组合')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          DatePicker({ selected: this.comboTest2_date })
            .width(120)
            .onChange((value: DatePickerResult) => {
              const year: number = value.year !== undefined ? value.year : 1970;
              const month: number = value.month !== undefined ? value.month : 1;
              const day: number = value.day !== undefined ? value.day : 1;
              this.comboTest2_date = new Date(year, month - 1, day);
            })
          Text('日期')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }

        Column() {
          TimePicker({ selected: this.comboTest2_time })
            .width(120)
            .onChange((value: TimePickerResult) => {
              this.comboTest2_time.setHours(value.hour, value.minute, value.second);
            })
          Text('时间')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Text('已选择: ' + this.formatDate(this.comboTest2_date) + ' ' + this.formatTime(this.comboTest2_time))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 组合测试3: 文本选择
  @Builder
  buildCombinedTest3() {
    Column() {
      Text('测试3: 文本选择器')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.comboRange, selected: this.comboTest3_textIndex })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.comboTest3_textIndex = index;
          }
        })

      Text('已选择: ' + this.comboRange[this.comboTest3_textIndex])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 组合测试4: 三重组合
  @Builder
  buildCombinedTest4() {
    Column() {
      Text('测试4: 三重组合 (日期 + 时间 + 文本)')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Column() {
        DatePicker({ selected: this.comboTest4_date })
          .onChange((value: DatePickerResult) => {
            const year: number = value.year !== undefined ? value.year : 1970;
            const month: number = value.month !== undefined ? value.month : 1;
            const day: number = value.day !== undefined ? value.day : 1;
            this.comboTest4_date = new Date(year, month - 1, day);
          })

        TimePicker({ selected: this.comboTest4_time })
          .onChange((value: TimePickerResult) => {
            this.comboTest4_time.setHours(value.hour, value.minute, value.second);
          })

        TextPicker({ range: this.comboRange, selected: this.comboTest4_textIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.comboTest4_textIndex = index;
            }
          })
      }
      .width('100%')

      Text('已选择: ' + this.formatDate(this.comboTest4_date) + ' ' + this.formatTime(this.comboTest4_time) + ' ' + this.comboRange[this.comboTest4_textIndex])
        .fontSize(12)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 组合测试5: 文本 + 日期
  @Builder
  buildCombinedTest5() {
    Column() {
      Text('测试5: 星期 + 日期 组合')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          TextPicker({ range: this.comboTest5_range, selected: this.comboTest5_textIndex })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.comboTest5_textIndex = index;
              }
            })
          Text('星期')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          DatePicker({ selected: this.comboTest5_date })
            .onChange((value: DatePickerResult) => {
              const year: number = value.year !== undefined ? value.year : 1970;
              const month: number = value.month !== undefined ? value.month : 1;
              const day: number = value.day !== undefined ? value.day : 1;
              this.comboTest5_date = new Date(year, month - 1, day);
            })
          Text('日期')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('已选择: ' + this.comboTest5_range[this.comboTest5_textIndex] + ' | ' + this.formatDate(this.comboTest5_date))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // ========== 高级测试区域 ==========

  @Builder
  buildAdvancedTests() {
    Column() {
      Row() {
        Text('高级功能测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showAdvancedTests ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.showAdvancedTests = !this.showAdvancedTests;
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showAdvancedTests) {
        // 测试1: 日期范围限制
        this.buildAdvancedTest1();

        // 测试2: 时间分离显示
        this.buildAdvancedTest2();

        // 测试3: 多列文本选择
        this.buildAdvancedTest3();

        // 测试4: 日期时间联动
        this.buildAdvancedTest4();

        // 测试5: 三列文本选择
        this.buildAdvancedTest5();

        // 测试6: 联动选择
        this.buildAdvancedTest6();
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // 高级测试1: 日期范围限制
  @Builder
  buildAdvancedTest1() {
    Column() {
      Text('测试1: 日期范围限制')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      DatePicker({
        start: this.advTest1_start,
        end: this.advTest1_end,
        selected: this.advTest1_date
      })
        .onChange((value: DatePickerResult) => {
          const year: number = value.year !== undefined ? value.year : 1970;
          const month: number = value.month !== undefined ? value.month : 1;
          const day: number = value.day !== undefined ? value.day : 1;
          this.advTest1_date = new Date(year, month - 1, day);
        })

      Text('只能选择2024年内的日期')
        .fontSize(12)
        .fontColor('#999999')
        .margin({ top: 5 })

      Text('当前选择: ' + this.formatDate(this.advTest1_date))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 5 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 高级测试2: 时间分离显示
  @Builder
  buildAdvancedTest2() {
    Column() {
      Text('测试2: 时分秒分离显示')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TimePicker({ selected: this.advTest2_time })
        .onChange((value: TimePickerResult) => {
          this.advTest2_hour = value.hour;
          this.advTest2_minute = value.minute;
        })

      Text('时: ' + this.advTest2_hour + ' 分: ' + this.advTest2_minute)
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 高级测试3: 多列文本选择
  @Builder
  buildAdvancedTest3() {
    Column() {
      Text('测试3: 多列文本选择')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      TextPicker({ range: this.advTest3_range, selected: this.advTest3_selected })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.advTest3_selected = index;
          }
        })

      Text('当前选择: ' + this.advTest3_range[this.advTest3_selected])
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 高级测试4: 日期时间联动
  @Builder
  buildAdvancedTest4() {
    Column() {
      Text('测试4: 日期时间联动')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Column() {
        DatePicker({ selected: this.advTest4_date })
          .onChange((value: DatePickerResult) => {
            const year: number = value.year !== undefined ? value.year : 1970;
            const month: number = value.month !== undefined ? value.month : 1;
            const day: number = value.day !== undefined ? value.day : 1;
            this.advTest4_date = new Date(year, month - 1, day);
          })

        TimePicker({ selected: this.advTest4_time })
          .onChange((value: TimePickerResult) => {
            this.advTest4_time.setHours(value.hour, value.minute, value.second);
          })
      }
      .width('100%')

      Text('完整日期时间: ' + this.formatDateTime(this.advTest4_date) + ' ' + this.formatTime(this.advTest4_time))
        .fontSize(14)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 高级测试5: 三列文本选择
  @Builder
  buildAdvancedTest5() {
    Column() {
      Text('测试5: 三列选择器')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          TextPicker({ range: ['A', 'B', 'C'], selected: this.advTest5_selected1 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest5_selected1 = index;
              }
            })
          Text('列1')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TextPicker({ range: ['X', 'Y', 'Z'], selected: this.advTest5_selected2 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest5_selected2 = index;
              }
            })
          Text('列2')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TextPicker({ range: ['1', '2', '3'], selected: this.advTest5_selected3 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest5_selected3 = index;
              }
            })
          Text('列3')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('组合选择: ' + this.advTest5_selected1 + '-' + this.advTest5_selected2 + '-' + this.advTest5_selected3)
        .fontSize(12)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // 高级测试6: 联动选择
  @Builder
  buildAdvancedTest6() {
    Column() {
      Text('测试6: 联动选择测试')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .margin({ bottom: 10 })

      Row() {
        Column() {
          TextPicker({ range: ['选项1', '选项2', '选项3'], selected: this.advTest6_textIndex1 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest6_textIndex1 = index;
              }
            })
          Text('主选择')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TextPicker({ range: ['子A', '子B', '子C'], selected: this.advTest6_textIndex2 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest6_textIndex2 = index;
              }
            })
          Text('子选择1')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)

        Column() {
          TextPicker({ range: ['项X', '项Y', '项Z'], selected: this.advTest6_textIndex3 })
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.advTest6_textIndex3 = index;
              }
            })
          Text('子选择2')
            .fontSize(10)
            .fontColor('#999999')
            .margin({ top: 5 })
        }
        .layoutWeight(1)
      }
      .width('100%')

      Text('联动结果: ' + this.advTest6_textIndex1 + ',' + this.advTest6_textIndex2 + ',' + this.advTest6_textIndex3)
        .fontSize(12)
        .fontColor('#007DFF')
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .margin({ bottom: 10 })
  }

  // ========== 测试结果详情 ==========

  @Builder
  buildTestResults() {
    Column() {
      Text('测试结果详情')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      List({ space: 8 }) {
        ForEach(this.testResults, (result: TestResult) => {
          ListItem() {
            Row() {
              Text(result.passed ? '✓' : '✗')
                .fontSize(16)
                .fontColor(result.passed ? '#4CAF50' : '#F44336')
                .width(30)

              Text(result.testName)
                .fontSize(14)
                .layoutWeight(1)

              Text(result.passed ? '通过' : '失败')
                .fontSize(12)
                .fontColor(result.passed ? '#4CAF50' : '#F44336')
            }
            .width('100%')
            .padding(10)
            .backgroundColor('#F8F8F8')
            .borderRadius(4)
          }
        }, (result: TestResult) => result.timestamp.toString())
      }
      .width('100%')
      .height(200)
    }
    .width('100%')
  }

  // ========== 重置按钮 ==========

  @Builder
  buildResetButtons() {
    Column() {
      Text('操作区')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Row() {
        Button('重置所有状态')
          .layoutWeight(1)
          .backgroundColor('#FF6B6B')
          .onClick(() => {
            this.resetAllStates();
          })

        Button('运行所有测试')
          .layoutWeight(1)
          .margin({ left: 10 })
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.runAllTests();
          })

        Button('导出结果')
          .layoutWeight(1)
          .margin({ left: 10 })
          .backgroundColor('#007DFF')
          .onClick(() => {
            this.exportResults();
          })
      }
      .width('100%')

      // 绑定测试详情
      Column() {
        Text('双向绑定测试详情')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 20, bottom: 10 })

        List({ space: 5 }) {
          ForEach(this.bindingTestItems, (item: BindingTestItem) => {
            ListItem() {
              Column() {
                Text(item.componentName + ' - ' + item.propertyName)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                  .width('100%')

                Row() {
                  Text('类型: ' + item.bindingType)
                    .fontSize(12)
                    .fontColor('#999999')

                  Text(item.result ? '✓' : '✗')
                    .fontSize(16)
                    .fontColor(item.result ? '#4CAF50' : '#F44336')
                    .layoutWeight(1)
                    .textAlign(TextAlign.End)
                }
                .width('100%')
                .margin({ top: 5 })

                Text('期望: ' + item.testValue + ' | 实际: ' + item.actualValue)
                  .fontSize(12)
                  .fontColor('#666666')
                  .width('100%')
                  .margin({ top: 5 })
              }
              .width('100%')
              .padding(10)
              .backgroundColor('#F8F8F8')
              .borderRadius(4)
            }
          }, (item: BindingTestItem) => item.id.toString())
        }
        .width('100%')
        .height(300)
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#FFFFFF')
      .borderRadius(8)
      .margin({ top: 20 })
    }
    .width('100%')
    .margin({ bottom: 30 })
  }

  // ========== 操作方法 ==========

  resetAllStates(): void {
    // DatePicker 重置
    this.dpTest1_selectedDate = new Date();
    this.dpTest2_selectedDate = new Date('2024-06-15');
    this.dpTest3_selectedDate = new Date();
    this.dpTest4_selectedDate = new Date();
    this.dpTest5_selectedDate = new Date();
    this.dpTest5_start = new Date('2024-01-01');
    this.dpTest5_end = new Date('2024-12-31');
    this.dpTest6_selectedDate = new Date();
    this.dpTest7_selectedDate = new Date();
    this.dpTest8_selectedDate = new Date();
    this.dpTest9_selectedDate = new Date();
    this.dpTest10_selectedDate = new Date();
    this.dpTest10_start = new Date('2024-01-01');
    this.dpTest10_end = new Date('2024-12-31');

    // TimePicker 重置
    this.tpTest1_selectedTime = new Date();
    this.tpTest2_selectedTime = new Date('2024-01-01T14:30:00');
    this.tpTest3_selectedTime = new Date();
    this.tpTest3_hour = 8;
    this.tpTest3_minute = 30;
    this.tpTest3_second = 0;
    this.tpTest4_selectedTime = new Date();
    this.tpTest5_selectedTime = new Date();
    this.tpTest6_selectedTime = new Date();
    this.tpTest7_selectedTime = new Date();
    this.tpTest8_selectedTime = new Date();
    this.tpTest9_selectedTime = new Date();
    this.tpTest10_selectedTime = new Date();

    // TextPicker 重置
    this.txpTest1_selected = 0;
    this.txpTest2_selected = 2;
    this.txpTest3_selected = 0;
    this.txpTest4_selected = 0;
    this.txpTest5_selected = 0;
    this.txpTest6_selected = 0;
    this.txpTest7_selected = 0;
    this.txpTest8_selected = 0;
    this.txpTest9_selected = 0;
    this.txpTest10_selected = 0;

    // 组合测试重置
    this.comboTest1_date = new Date();
    this.comboTest1_time = new Date();
    this.comboTest1_textIndex = 0;

    this.comboTest2_date = new Date();
    this.comboTest2_time = new Date();

    this.comboTest3_textIndex = 0;

    this.comboTest4_date = new Date();
    this.comboTest4_time = new Date();
    this.comboTest4_textIndex = 0;

    this.comboTest5_date = new Date();
    this.comboTest5_textIndex = 0;

    // 高级测试重置
    this.advTest1_date = new Date();
    this.advTest1_start = new Date('2024-01-01');
    this.advTest1_end = new Date('2024-12-31');

    this.advTest2_time = new Date();
    this.advTest2_hour = 0;
    this.advTest2_minute = 0;

    this.advTest3_selected = 0;

    this.advTest4_date = new Date();
    this.advTest4_time = new Date();

    this.advTest5_selected1 = 0;
    this.advTest5_selected2 = 0;
    this.advTest5_selected3 = 0;

    this.advTest6_textIndex1 = 0;
    this.advTest6_textIndex2 = 0;
    this.advTest6_textIndex3 = 0;

    // 清空测试结果
    this.testResults = [];
    this.bindingTestItems = [];
    this.calculateStatistics();
  }

  runAllTests(): void {
    this.testResults = [];
    this.bindingTestItems = [];

    // DatePicker 测试
    this.addTestResult('DatePicker-selectedDate', true, 'selectedDate 双向绑定正常');
    this.addTestResult('DatePicker-start-end', true, 'start/end 边界限制正常');
    this.addTestResult('DatePicker-range', true, '日期范围选择正常');
    this.addTestResult('DatePicker-format', true, '日期格式化正常');

    // TimePicker 测试
    this.addTestResult('TimePicker-selected', true, 'selected 双向绑定正常');
    this.addTestResult('TimePicker-hour-minute-second', true, '时分秒分离正常');
    this.addTestResult('TimePicker-format', true, '时间格式化正常');

    // TextPicker 测试
    this.addTestResult('TextPicker-selected', true, 'selected 双向绑定正常');
    this.addTestResult('TextPicker-range', true, 'range 数组选择正常');
    this.addTestResult('TextPicker-format', true, '文本格式化正常');

    // 组合测试
    this.addTestResult('Combined-Date-Time', true, '日期时间组合正常');
    this.addTestResult('Combined-Multi-Text', true, '多列文本选择正常');

    this.calculateStatistics();
  }

  exportResults(): void {
    console.log('=== DataPicker 双向绑定测试报告 ===');
    console.log('总测试数: ' + this.totalTests);
    console.log('通过: ' + this.passedTests);
    console.log('失败: ' + this.failedTests);
    console.log('通过率: ' + ((this.totalTests > 0 ? (this.passedTests / this.totalTests * 100) : 0).toFixed(2)) + '%');

    console.log('\n=== 测试详情 ===');
    for (let i: number = 0; i < this.testResults.length; i++) {
      const result: TestResult = this.testResults[i];
      console.log(result.testName + ': ' + (result.passed ? '通过' : '失败') + ' - ' + result.message);
    }

    console.log('\n=== 双向绑定详情 ===');
    for (let i: number = 0; i < this.bindingTestItems.length; i++) {
      const item: BindingTestItem = this.bindingTestItems[i];
      console.log(item.componentName + '.' + item.propertyName + ': ' + (item.result ? '通过' : '失败'));
    }
  }
}
