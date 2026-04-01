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
 * TextPicker组件全面测试页面
 * 用于测试TextPicker组件的各种属性和用法
 */

// ========== 数据定义部分 ==========

// 测试用基础数据数组
const TEST_DATA_NUMBERS: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'];
const TEST_DATA_LETTERS: string[] = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'];
const TEST_DATA_MONTHS: string[] = ['一月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '十一月', '十二月'];
const TEST_DATA_WEEKDAYS: string[] = ['星期一', '星期二', '星期三', '星期四', '星期五', '星期六', '星期日'];
const TEST_DATA_YEARS: string[] = [];
const TEST_DATA_CITIES: string[] = ['北京', '上海', '广州', '深圳', '杭州', '成都', '西安', '南京', '武汉', '重庆'];
const TEST_DATA_COLORS: string[] = ['红色', '橙色', '黄色', '绿色', '青色', '蓝色', '紫色'];
const TEST_DATA_SIZES: string[] = ['XS', 'S', 'M', 'L', 'XL', 'XXL', 'XXXL'];
const TEST_DATA_PRIORITIES: string[] = ['低', '中', '高', '紧急'];
const TEST_DATA_STATUS: string[] = ['待处理', '处理中', '已完成', '已关闭'];
const TEST_DATA_TYPES: string[] = ['类型A', '类型B', '类型C', '类型D', '类型E'];

// 生成年份数据
for (let i: number = 2000; i <= 2050; i++) {
  TEST_DATA_YEARS.push(i.toString() + '年');
}

// ========== 主题颜色定义 ==========

const THEME_COLORS: string[] = [
  '#FF0000', '#FF6600', '#FFCC00', '#00FF00',
  '#00CCFF', '#0066FF', '#9900FF', '#FF00FF',
  '#FF0066', '#00FF99', '#FF9900', '#6600FF'
];

const BG_COLORS: string[] = [
  '#F5F5F5', '#EEEEEE', '#E0E0E0', '#D5D5D5',
  '#CCCCCC', '#C0C0C0', '#B5B5B5', '#AAAAAA'
];

// ========== 字体大小数组 ==========

const FONT_SIZES: number[] = [10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 36, 40];

// ========== 主测试组件 ==========

@Entry
@Component
struct TextPickerTestPage {
  // ========== 状态变量定义 ==========

  // 基础选择状态
  @State selectedBasicIndex: number = 0;
  @State selectedNumberIndex: number = 5;
  @State selectedMonthIndex: number = 0;
  @State selectedWeekdayIndex: number = 0;
  @State selectedYearIndex: number = 24;
  @State selectedCityIndex: number = 0;
  @State selectedColorIndex: number = 0;
  @State selectedSizeIndex: number = 2;
  @State selectedPriorityIndex: number = 1;
  @State selectedStatusIndex: number = 0;
  @State selectedTypeIndex: number = 0;

  // 样式测试状态
  @State testBgColor: string = '#F5F5F5';
  @State testFontColor: string = '#333333';
  @State testFontSize: number = 16;
  @State testFontWeight: number = FontWeight.Normal;
  @State testOpacity: number = 1.0;
  @State testBorderRadius: number = 8;
  @State testBorderWidth: number = 1;
  @State testBorderColor: string = '#E0E0E0';
  @State testPadding: number = 10;

  // 事件测试状态
  @State onChangeCount: number = 0;
  @State onChangeValue: string = '';
  @State onChangeIndex: number = 0;
  @State onAcceptCount: number = 0;
  @State onCancelCount: number = 0;

  // 显示控制状态
  @State showBasicTest: boolean = true;
  @State showStyleTest: boolean = true;
  @State showEventTest: boolean = true;
  @State showComboTest: boolean = true;
  @State showCustomTest: boolean = true;
  @State showLayoutTest: boolean = true;
  @State showAnimationTest: boolean = true;

  // 动画测试状态
  @State animationScale: number = 1.0;
  @State animationRotation: number = 0;
  @State animationTranslate: number = 0;
  @State animationOpacity: number = 1.0;

  // 布局测试状态
  @State layoutWidth: string = '100%';
  @State layoutHeight: number = 200;
  @State layoutMargin: number = 10;
  @State layoutPadding: number = 10;

  // 自定义对象数组测试
  @State customSelectedIndex: number = 0;

  // 长列表测试状态
  @State longListSelectedIndex: number = 50;

  // 联动测试状态
  @State linkedProvinceIndex: number = 0;
  @State linkedCityIndex: number = 0;
  @State linkedDistrictIndex: number = 0;

  // 省市区联动数据
  private provinces: string[] = ['北京市', '上海市', '广东省', '浙江省', '江苏省'];
  private cities: Record<string, string[]> = {
    '北京市': ['东城区', '西城区', '朝阳区', '海淀区', '丰台区'],
    '上海市': ['黄浦区', '徐汇区', '静安区', '浦东新区', '闵行区'],
    '广东省': ['广州市', '深圳市', '珠海市', '佛山市', '东莞市'],
    '浙江省': ['杭州市', '宁波市', '温州市', '嘉兴市', '湖州市'],
    '江苏省': ['南京市', '苏州市', '无锡市', '常州市', '徐州市']
  };
  private districts: Record<string, string[]> = {
    '东城区': ['东华门街道', '景山街道', '交道口街道'],
    '西城区': ['西长安街道', '新街口街道', '月坛街道'],
    '朝阳区': ['建外街道', '朝外街道', '呼家楼街道'],
    '海淀区': ['万寿路街道', '永定路街道', '羊坊店街道']
  };

  // 多列选择测试状态
  @State multiCol1Index: number = 0;
  @State multiCol2Index: number = 0;
  @State multiCol3Index: number = 0;

  // 禁用状态测试
  @State disabledPickerIndex: number = 2;

  // 默认值测试
  @State defaultPickerIndex: number = 5;

  // 极值测试状态
  @State minSelectedIndex: number = 0;
  @State maxSelectedIndex: number = 0;

  // ========== 生命周期方法 ==========

  aboutToAppear(): void {
    console.log('[TextPickerTest] aboutToAppear called');
    this.initTestData();
  }

  aboutToDisappear(): void {
    console.log('[TextPickerTest] aboutToDisappear called');
  }

  // ========== 初始化方法 ==========

  initTestData(): void {
    console.log('[TextPickerTest] initTestData called');
    // 初始化测试数据
    this.selectedBasicIndex = 0;
    this.selectedNumberIndex = 5;
    this.selectedMonthIndex = new Date().getMonth();
    this.selectedYearIndex = 24;
  }

  // ========== 事件处理方法 ==========

  handleBasicChange(value: string, index: number): void {
    this.onChangeCount++;
    this.onChangeValue = value;
    this.onChangeIndex = index;
    console.log('[TextPickerTest] Basic onChange - value: ' + value + ', index: ' + index);
  }

  handleNumberChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedNumberIndex = index;
      console.log('[TextPickerTest] Number onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleMonthChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedMonthIndex = index;
      console.log('[TextPickerTest] Month onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleWeekdayChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedWeekdayIndex = index;
      console.log('[TextPickerTest] Weekday onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleYearChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedYearIndex = index;
      console.log('[TextPickerTest] Year onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleCityChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedCityIndex = index;
      console.log('[TextPickerTest] City onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleColorChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedColorIndex = index;
      console.log('[TextPickerTest] Color onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleSizeChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedSizeIndex = index;
      console.log('[TextPickerTest] Size onChange - value: ' + value + ', index: ' + index);
    }
  }

  handlePriorityChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedPriorityIndex = index;
      console.log('[TextPickerTest] Priority onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleStatusChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedStatusIndex = index;
      console.log('[TextPickerTest] Status onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleTypeChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.selectedTypeIndex = index;
      console.log('[TextPickerTest] Type onChange - value: ' + value + ', index: ' + index);
    }
  }

  handleAccept(): void {
    this.onAcceptCount++;
    console.log('[TextPickerTest] onAccept called, count: ' + this.onAcceptCount);
  }

  handleCancel(): void {
    this.onCancelCount++;
    console.log('[TextPickerTest] onCancel called, count: ' + this.onCancelCount);
  }

  handleLinkedProvinceChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.linkedProvinceIndex = index;
      this.linkedCityIndex = 0;
      console.log('[TextPickerTest] Province changed to: ' + value);
    }
  }

  handleLinkedCityChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.linkedCityIndex = index;
      this.linkedDistrictIndex = 0;
      console.log('[TextPickerTest] City changed to: ' + value);
    }
  }

  handleLinkedDistrictChange(value: string | string[], index: number | number[]): void {
    if (typeof value === 'string' && typeof index === 'number') {
      this.linkedDistrictIndex = index;
      console.log('[TextPickerTest] District changed to: ' + value);
    }
  }

  // ========== 辅助方法 ==========

  getCurrentCityList(): string[] {
    const province: string = this.provinces[this.linkedProvinceIndex];
    return this.cities[province] || [];
  }

  getCurrentDistrictList(): string[] {
    const province: string = this.provinces[this.linkedProvinceIndex];
    const cities: string[] = this.cities[province] || [];
    const city: string = cities[this.linkedCityIndex];
    return this.districts[city] || [];
  }

  getSelectedText(): string {
    return TEST_DATA_LETTERS[this.selectedBasicIndex];
  }

  getSelectedNumberText(): string {
    return TEST_DATA_NUMBERS[this.selectedNumberIndex];
  }

  getSelectedMonthText(): string {
    return TEST_DATA_MONTHS[this.selectedMonthIndex];
  }

  getSelectedWeekdayText(): string {
    return TEST_DATA_WEEKDAYS[this.selectedWeekdayIndex];
  }

  getSelectedYearText(): string {
    return TEST_DATA_YEARS[this.selectedYearIndex];
  }

  getSelectedCityText(): string {
    return TEST_DATA_CITIES[this.selectedCityIndex];
  }

  getSelectedColorText(): string {
    return TEST_DATA_COLORS[this.selectedColorIndex];
  }

  getSelectedSizeText(): string {
    return TEST_DATA_SIZES[this.selectedSizeIndex];
  }

  getSelectedPriorityText(): string {
    return TEST_DATA_PRIORITIES[this.selectedPriorityIndex];
  }

  getSelectedStatusText(): string {
    return TEST_DATA_STATUS[this.selectedStatusIndex];
  }

  getSelectedTypeText(): string {
    return TEST_DATA_TYPES[this.selectedTypeIndex];
  }

  // ========== 样式修改方法 ==========

  changeBgColor(): void {
    const currentIndex: number = BG_COLORS.indexOf(this.testBgColor);
    const nextIndex: number = (currentIndex + 1) % BG_COLORS.length;
    this.testBgColor = BG_COLORS[nextIndex];
  }

  changeFontColor(): void {
    const currentIndex: number = THEME_COLORS.indexOf(this.testFontColor);
    const nextIndex: number = (currentIndex + 1) % THEME_COLORS.length;
    this.testFontColor = THEME_COLORS[nextIndex];
  }

  changeFontSize(): void {
    const currentIndex: number = FONT_SIZES.indexOf(this.testFontSize);
    const nextIndex: number = (currentIndex + 1) % FONT_SIZES.length;
    this.testFontSize = FONT_SIZES[nextIndex];
  }

  changeFontWeight(): void {
    const weights: number[] = [
      FontWeight.Lighter,
      FontWeight.Normal,
      FontWeight.Regular,
      FontWeight.Medium,
      FontWeight.Bold,
      FontWeight.Bolder
    ];
    const currentIndex: number = weights.indexOf(this.testFontWeight);
    const nextIndex: number = (currentIndex + 1) % weights.length;
    this.testFontWeight = weights[nextIndex];
  }

  changeOpacity(): void {
    this.testOpacity = this.testOpacity >= 1.0 ? 0.3 : this.testOpacity + 0.1;
    this.testOpacity = Math.round(this.testOpacity * 10) / 10;
  }

  changeBorderRadius(): void {
    this.testBorderRadius = this.testBorderRadius >= 20 ? 0 : this.testBorderRadius + 2;
  }

  changeBorderWidth(): void {
    this.testBorderWidth = this.testBorderWidth >= 5 ? 0 : this.testBorderWidth + 1;
  }

  changeBorderColor(): void {
    const currentIndex: number = THEME_COLORS.indexOf(this.testBorderColor);
    const nextIndex: number = (currentIndex + 1) % THEME_COLORS.length;
    this.testBorderColor = THEME_COLORS[nextIndex];
  }

  changePadding(): void {
    this.testPadding = this.testPadding >= 30 ? 5 : this.testPadding + 5;
  }

  // ========== 动画控制方法 ==========

  startScaleAnimation(): void {
    this.animationScale = this.animationScale === 1.0 ? 1.1 : 1.0;
  }

  startRotationAnimation(): void {
    this.animationRotation = this.animationRotation === 0 ? 360 : 0;
  }

  startTranslateAnimation(): void {
    this.animationTranslate = this.animationTranslate === 0 ? 10 : 0;
  }

  startOpacityAnimation(): void {
    this.animationOpacity = this.animationOpacity === 1.0 ? 0.5 : 1.0;
  }

  resetAnimations(): void {
    this.animationScale = 1.0;
    this.animationRotation = 0;
    this.animationTranslate = 0;
    this.animationOpacity = 1.0;
  }

  // ========== 显示控制方法 ==========

  toggleBasicTest(): void {
    this.showBasicTest = !this.showBasicTest;
  }

  toggleStyleTest(): void {
    this.showStyleTest = !this.showStyleTest;
  }

  toggleEventTest(): void {
    this.showEventTest = !this.showEventTest;
  }

  toggleComboTest(): void {
    this.showComboTest = !this.showComboTest;
  }

  toggleCustomTest(): void {
    this.showCustomTest = !this.showCustomTest;
  }

  toggleLayoutTest(): void {
    this.showLayoutTest = !this.showLayoutTest;
  }

  toggleAnimationTest(): void {
    this.showAnimationTest = !this.showAnimationTest;
  }

  // ========== 重置方法 ==========

  resetAllStates(): void {
    this.selectedBasicIndex = 0;
    this.selectedNumberIndex = 5;
    this.selectedMonthIndex = 0;
    this.selectedWeekdayIndex = 0;
    this.selectedYearIndex = 24;
    this.selectedCityIndex = 0;
    this.selectedColorIndex = 0;
    this.selectedSizeIndex = 2;
    this.selectedPriorityIndex = 1;
    this.selectedStatusIndex = 0;
    this.selectedTypeIndex = 0;

    this.testBgColor = '#F5F5F5';
    this.testFontColor = '#333333';
    this.testFontSize = 16;
    this.testFontWeight = FontWeight.Normal;
    this.testOpacity = 1.0;
    this.testBorderRadius = 8;
    this.testBorderWidth = 1;
    this.testBorderColor = '#E0E0E0';
    this.testPadding = 10;

    this.onChangeCount = 0;
    this.onChangeValue = '';
    this.onChangeIndex = 0;
    this.onAcceptCount = 0;
    this.onCancelCount = 0;

    this.resetAnimations();
  }

  // ========== 主界面构建方法 ==========

  build() {
    Scroll() {
      Column() {
        // 页面标题
        this.buildTitle();

        // 基础功能测试区
        this.buildBasicTestSection();

        // 样式属性测试区
        this.buildStyleTestSection();

        // 事件回调测试区
        this.buildEventTestSection();

        // 组合选择测试区
        this.buildComboTestSection();

        // 联动选择测试区
        this.buildLinkedTestSection();

        // 自定义对象测试区
        this.buildCustomObjectTestSection();

        // 长列表测试区
        this.buildLongListTestSection();

        // 布局属性测试区
        this.buildLayoutTestSection();

        // 动画效果测试区
        this.buildAnimationTestSection();

        // 禁用状态测试区
        this.buildDisabledTestSection();

        // 默认值测试区
        this.buildDefaultTestSection();

        // 极值测试区
        this.buildExtremeTestSection();

        // 边界条件测试区
        this.buildBoundaryTestSection();

        // 性能测试区
        this.buildPerformanceTestSection();

        // 多实例测试区
        this.buildMultiInstanceTestSection();

        // 嵌套容器测试区
        this.buildNestedTestSection();

        // 状态保存测试区
        this.buildStateSaveTestSection();

        // 重置按钮区
        this.buildResetSection();
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 10 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }

  // ========== 标题组件 ==========

  @Builder
  buildTitle() {
    Column() {
      Text('TextPicker组件全面测试')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor('#333333')
        .margin({ top: 10, bottom: 5 })

      Text('测试TextPicker组件的各种属性和用法')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ bottom: 15 })

      Divider()
        .color('#E0E0E0')
    }
    .width('100%')
  }

  // ========== 基础功能测试区 ==========

  @Builder
  buildBasicTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('基础功能测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showBasicTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleBasicTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showBasicTest) {
        // 字母选择器
        this.buildPickerRow('字母选择', TEST_DATA_LETTERS, this.selectedBasicIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedBasicIndex = index;
            }
          }, this.getSelectedText())

        // 数字选择器
        this.buildPickerRow('数字选择', TEST_DATA_NUMBERS, this.selectedNumberIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedNumberIndex = index;
            }
          }, this.getSelectedNumberText())

        // 月份选择器
        this.buildPickerRow('月份选择', TEST_DATA_MONTHS, this.selectedMonthIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedMonthIndex = index;
            }
          }, this.getSelectedMonthText())

        // 星期选择器
        this.buildPickerRow('星期选择', TEST_DATA_WEEKDAYS, this.selectedWeekdayIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedWeekdayIndex = index;
            }
          }, this.getSelectedWeekdayText())

        // 年份选择器
        this.buildPickerRow('年份选择', TEST_DATA_YEARS, this.selectedYearIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedYearIndex = index;
            }
          }, this.getSelectedYearText())

        // 城市选择器
        this.buildPickerRow('城市选择', TEST_DATA_CITIES, this.selectedCityIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedCityIndex = index;
            }
          }, this.getSelectedCityText())

        // 颜色选择器
        this.buildPickerRow('颜色选择', TEST_DATA_COLORS, this.selectedColorIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedColorIndex = index;
            }
          }, this.getSelectedColorText())

        // 尺寸选择器
        this.buildPickerRow('尺寸选择', TEST_DATA_SIZES, this.selectedSizeIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedSizeIndex = index;
            }
          }, this.getSelectedSizeText())

        // 优先级选择器
        this.buildPickerRow('优先级选择', TEST_DATA_PRIORITIES, this.selectedPriorityIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedPriorityIndex = index;
            }
          }, this.getSelectedPriorityText())

        // 状态选择器
        this.buildPickerRow('状态选择', TEST_DATA_STATUS, this.selectedStatusIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedStatusIndex = index;
            }
          }, this.getSelectedStatusText())

        // 类型选择器
        this.buildPickerRow('类型选择', TEST_DATA_TYPES, this.selectedTypeIndex,
          (value: string | string[], index: number | number[]) => {
            if (typeof value === 'string' && typeof index === 'number') {
              this.selectedTypeIndex = index;
            }
          }, this.getSelectedTypeText())
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 通用选择器行构建器 ==========

  @Builder
  buildPickerRow(
    label: string,
    data: string[],
    selectedIndex: number,
    onChangeCallback: (value: string | string[], index: number | number[]) => void,
    selectedText: string
  ) {
    Row() {
      Text(label)
        .width(100)
        .fontSize(14)
        .fontColor('#666666')

      TextPicker({ range: data, selected: selectedIndex })
        .layoutWeight(1)
        .onChange(onChangeCallback)

      Text('已选: ' + selectedText)
        .width(120)
        .fontSize(12)
        .fontColor('#007DFF')
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .height(50)
    .margin({ bottom: 8 })
    .padding({ left: 10, right: 10 })
    .backgroundColor('#F8F8F8')
    .borderRadius(8)
  }

  // ========== 样式属性测试区 ==========

  @Builder
  buildStyleTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('样式属性测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showStyleTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleStyleTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showStyleTest) {
        // 背景颜色测试
        Row() {
          Text('背景色')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_COLORS, selected: this.selectedColorIndex })
            .layoutWeight(1)
            .backgroundColor(this.testBgColor)
          Button('切换')
            .onClick(() => {
              this.changeBgColor();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 字体颜色测试（TextPicker不支持fontColor，使用样式替代）
        Row() {
          Text('字体色')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_COLORS, selected: this.selectedColorIndex })
            .layoutWeight(1)
          Button('切换')
            .onClick(() => {
              this.changeFontColor();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 字体大小测试（TextPicker不支持font属性，显示当前值）
        Row() {
          Text('字体大小')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_SIZES, selected: this.selectedSizeIndex })
            .layoutWeight(1)
          Text(this.testFontSize.toString())
            .width(40)
            .textAlign(TextAlign.Center)
          Button('切换')
            .onClick(() => {
              this.changeFontSize();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 字体粗细测试（TextPicker不支持font属性）
        Row() {
          Text('字体粗细')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_PRIORITIES, selected: this.selectedPriorityIndex })
            .layoutWeight(1)
          Button('切换')
            .onClick(() => {
              this.changeFontWeight();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 透明度测试
        Row() {
          Text('透明度')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_NUMBERS, selected: this.selectedNumberIndex })
            .layoutWeight(1)
            .opacity(this.testOpacity)
          Text(this.testOpacity.toFixed(1))
            .width(40)
            .textAlign(TextAlign.Center)
          Button('切换')
            .onClick(() => {
              this.changeOpacity();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 圆角测试
        Row() {
          Text('圆角')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_SIZES, selected: this.selectedSizeIndex })
            .layoutWeight(1)
            .borderRadius(this.testBorderRadius)
          Text(this.testBorderRadius.toString())
            .width(40)
            .textAlign(TextAlign.Center)
          Button('切换')
            .onClick(() => {
              this.changeBorderRadius();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 边框宽度测试
        Row() {
          Text('边框宽')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_NUMBERS, selected: this.selectedNumberIndex })
            .layoutWeight(1)
            .border({ width: this.testBorderWidth })
          Text(this.testBorderWidth.toString())
            .width(40)
            .textAlign(TextAlign.Center)
          Button('切换')
            .onClick(() => {
              this.changeBorderWidth();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 边框颜色测试
        Row() {
          Text('边框色')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_COLORS, selected: this.selectedColorIndex })
            .layoutWeight(1)
            .border({ color: this.testBorderColor })
          Button('切换')
            .onClick(() => {
              this.changeBorderColor();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 内边距测试
        Row() {
          Text('内边距')
            .width(80)
            .fontSize(14)
          TextPicker({ range: TEST_DATA_SIZES, selected: this.selectedSizeIndex })
            .layoutWeight(1)
            .padding(this.testPadding)
          Text(this.testPadding.toString())
            .width(40)
            .textAlign(TextAlign.Center)
          Button('切换')
            .onClick(() => {
              this.changePadding();
            })
        }
        .width('100%')
        .height(50)
        .margin({ bottom: 8 })
        .alignItems(VerticalAlign.Center)

        // 组合样式测试（TextPicker不支持fontColor和font属性）
        Column() {
          Text('组合样式测试')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 5 })
          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .backgroundColor(this.testBgColor)
            .opacity(this.testOpacity)
            .borderRadius(this.testBorderRadius)
            .border({ width: this.testBorderWidth, color: this.testBorderColor })
            .padding(this.testPadding)
        }
        .width('100%')
        .margin({ top: 5, bottom: 5 })
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 事件回调测试区 ==========

  @Builder
  buildEventTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('事件回调测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showEventTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleEventTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showEventTest) {
        // onChange事件测试
        Column() {
          Text('onChange事件测试')
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          TextPicker({ range: TEST_DATA_MONTHS, selected: this.selectedMonthIndex })
            .width('100%')
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof value === 'string' && typeof index === 'number') {
                this.handleMonthChange(value, index);
              }
            })

          Row() {
            Text('触发次数: ' + this.onChangeCount.toString())
              .fontSize(12)
            Text('当前值: ' + this.onChangeValue)
              .fontSize(12)
              .margin({ left: 10 })
            Text('当前索引: ' + this.onChangeIndex.toString())
              .fontSize(12)
              .margin({ left: 10 })
          }
          .width('100%')
          .margin({ top: 5 })
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // onAccept事件测试
        Column() {
          Text('onAccept事件测试')
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          TextPicker({ range: TEST_DATA_WEEKDAYS, selected: this.selectedWeekdayIndex })
            .width('100%')
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof value === 'string' && typeof index === 'number') {
                this.handleWeekdayChange(value, index);
              }
            })
            .onAccept(() => {
              this.handleAccept();
            })

          Text('确认触发次数: ' + this.onAcceptCount.toString())
            .fontSize(12)
            .margin({ top: 5 })
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // onCancel事件测试
        Column() {
          Text('onCancel事件测试')
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width('100%')
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof value === 'string' && typeof index === 'number') {
                this.handleCityChange(value, index);
              }
            })
            .onCancel(() => {
              this.handleCancel();
            })

          Text('取消触发次数: ' + this.onCancelCount.toString())
            .fontSize(12)
            .margin({ top: 5 })
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 所有事件组合测试
        Column() {
          Text('所有事件组合测试')
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          TextPicker({ range: TEST_DATA_YEARS, selected: this.selectedYearIndex })
            .width('100%')
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof value === 'string' && typeof index === 'number') {
                this.handleYearChange(value, index);
              }
            })
            .onAccept(() => {
              this.handleAccept();
            })
            .onCancel(() => {
              this.handleCancel();
            })

          Row() {
            Text('onChange: ' + this.onChangeCount.toString())
              .fontSize(12)
            Text('onAccept: ' + this.onAcceptCount.toString())
              .fontSize(12)
              .margin({ left: 10 })
            Text('onCancel: ' + this.onCancelCount.toString())
              .fontSize(12)
              .margin({ left: 10 })
          }
          .width('100%')
          .margin({ top: 5 })
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 组合选择测试区 ==========

  @Builder
  buildComboTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('组合选择测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showComboTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleComboTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showComboTest) {
        // 日期组合（年月日）
        Column() {
          Text('日期组合选择（年月日）')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('年')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_YEARS, selected: this.selectedYearIndex })
                .width(120)
                .height(150)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleYearChange(value, index);
                  }
                })
            }

            Column() {
              Text('月')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_MONTHS, selected: this.selectedMonthIndex })
                .width(100)
                .height(150)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleMonthChange(value, index);
                  }
                })
            }

            Column() {
              Text('日')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_NUMBERS.slice(0, 31), selected: this.selectedNumberIndex })
                .width(80)
                .height(150)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleNumberChange(value, index);
                  }
                })
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)

          Text('已选择: ' + this.getSelectedYearText() + this.getSelectedMonthText() +
          (this.selectedNumberIndex + 1).toString() + '日')
            .fontSize(14)
            .fontColor('#007DFF')
            .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 时间组合（时分秒）
        Column() {
          Text('时间组合选择（时分秒）')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('时')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_NUMBERS.slice(0, 24), selected: this.selectedNumberIndex })
                .width(80)
                .height(150)
            }

            Column() {
              Text('分')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_NUMBERS.slice(0, 60), selected: this.selectedNumberIndex })
                .width(80)
                .height(150)
            }

            Column() {
              Text('秒')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_NUMBERS.slice(0, 60), selected: this.selectedNumberIndex })
                .width(80)
                .height(150)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)

          Text('已选择时间')
            .fontSize(14)
            .fontColor('#007DFF')
            .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 商品属性组合
        Column() {
          Text('商品属性选择')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('颜色')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_COLORS, selected: this.selectedColorIndex })
                .width(100)
                .height(120)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleColorChange(value, index);
                  }
                })
            }

            Column() {
              Text('尺寸')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_SIZES, selected: this.selectedSizeIndex })
                .width(100)
                .height(120)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleSizeChange(value, index);
                  }
                })
            }

            Column() {
              Text('数量')
                .fontSize(12)
                .margin({ bottom: 5 })
              TextPicker({ range: TEST_DATA_NUMBERS.slice(0, 10), selected: this.selectedNumberIndex })
                .width(80)
                .height(120)
                .onChange((value: string | string[], index: number | number[]) => {
                  if (typeof value === 'string' && typeof index === 'number') {
                    this.handleNumberChange(value, index);
                  }
                })
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)

          Text('已选择: ' + this.getSelectedColorText() + ' / ' + this.getSelectedSizeText())
            .fontSize(14)
            .fontColor('#007DFF')
            .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 联动选择测试区 ==========

  @Builder
  buildLinkedTestSection() {
    Column() {
      Text('联动选择测试（省市区）')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Column() {
        Row() {
          Column() {
            Text('省份')
              .fontSize(12)
              .margin({ bottom: 5 })
            TextPicker({ range: this.provinces, selected: this.linkedProvinceIndex })
              .width(100)
              .height(150)
              .onChange((value: string | string[], index: number | number[]) => {
                this.handleLinkedProvinceChange(value, index);
              })
          }

          Column() {
            Text('城市')
              .fontSize(12)
              .margin({ bottom: 5 })
            TextPicker({ range: this.getCurrentCityList(), selected: this.linkedCityIndex })
              .width(100)
              .height(150)
              .onChange((value: string | string[], index: number | number[]) => {
                this.handleLinkedCityChange(value, index);
              })
          }

          Column() {
            Text('区县')
              .fontSize(12)
              .margin({ bottom: 5 })
            TextPicker({ range: this.getCurrentDistrictList(), selected: this.linkedDistrictIndex })
              .width(100)
              .height(150)
              .onChange((value: string | string[], index: number | number[]) => {
                this.handleLinkedDistrictChange(value, index);
              })
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceAround)

        Text('已选择: ' + this.provinces[this.linkedProvinceIndex] + ' ' +
          (this.getCurrentCityList()[this.linkedCityIndex] || '') + ' ' +
          (this.getCurrentDistrictList()[this.linkedDistrictIndex] || ''))
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 自定义对象测试区 ==========

  @Builder
  buildCustomObjectTestSection() {
    Column() {
      Text('字符串数组测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      // 字符串数组（TextPicker的range必须是字符串数组）
      Column() {
        TextPicker({ range: ['选项A', '选项B', '选项C', '选项D', '选项E'], selected: this.customSelectedIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.customSelectedIndex = index;
            }
          })

        Text('当前选中索引: ' + this.customSelectedIndex.toString())
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 长列表测试区 ==========

  @Builder
  buildLongListTestSection() {
    Column() {
      Text('长列表测试（100项）')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      // 使用预先生成的长列表数据
      Column() {
        TextPicker({
          range: [
            '项目 1', '项目 2', '项目 3', '项目 4', '项目 5', '项目 6', '项目 7', '项目 8', '项目 9', '项目 10',
            '项目 11', '项目 12', '项目 13', '项目 14', '项目 15', '项目 16', '项目 17', '项目 18', '项目 19', '项目 20',
            '项目 21', '项目 22', '项目 23', '项目 24', '项目 25', '项目 26', '项目 27', '项目 28', '项目 29', '项目 30',
            '项目 31', '项目 32', '项目 33', '项目 34', '项目 35', '项目 36', '项目 37', '项目 38', '项目 39', '项目 40',
            '项目 41', '项目 42', '项目 43', '项目 44', '项目 45', '项目 46', '项目 47', '项目 48', '项目 49', '项目 50',
            '项目 51', '项目 52', '项目 53', '项目 54', '项目 55', '项目 56', '项目 57', '项目 58', '项目 59', '项目 60',
            '项目 61', '项目 62', '项目 63', '项目 64', '项目 65', '项目 66', '项目 67', '项目 68', '项目 69', '项目 70',
            '项目 71', '项目 72', '项目 73', '项目 74', '项目 75', '项目 76', '项目 77', '项目 78', '项目 79', '项目 80',
            '项目 81', '项目 82', '项目 83', '项目 84', '项目 85', '项目 86', '项目 87', '项目 88', '项目 89', '项目 90',
            '项目 91', '项目 92', '项目 93', '项目 94', '项目 95', '项目 96', '项目 97', '项目 98', '项目 99', '项目 100'
          ],
          selected: this.longListSelectedIndex
        })
          .height(200)
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.longListSelectedIndex = index;
            }
          })

        Text('当前选中: 项目 ' + (this.longListSelectedIndex + 1).toString())
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 布局属性测试区 ==========

  @Builder
  buildLayoutTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('布局属性测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showLayoutTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleLayoutTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showLayoutTest) {
        // 宽度测试
        Column() {
          Text('宽度测试')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width('50%')
            .backgroundColor('#FFE0E0')

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width('80%')
            .backgroundColor('#FFE8E8')

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width('100%')
            .backgroundColor('#FFF0F0')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 高度测试
        Column() {
          Text('高度测试')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('高度150')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
                .height(150)
                .backgroundColor('#E0E0FF')
            }
            .layoutWeight(1)

            Column() {
              Text('高度200')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
                .height(200)
                .backgroundColor('#E8E8FF')
            }
            .layoutWeight(1)

            Column() {
              Text('高度250')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
                .height(250)
                .backgroundColor('#F0F0FF')
            }
            .layoutWeight(1)
          }
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 边距测试
        Column() {
          Text('边距测试')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .margin({ top: 10, bottom: 10, left: 10, right: 10 })
            .backgroundColor('#E0FFE0')

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .margin(20)
            .backgroundColor('#E8FFE8')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 对齐测试
        Column() {
          Text('对齐测试')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('居左')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES.slice(0, 3), selected: this.selectedCityIndex })
                .align(Alignment.TopStart)
                .backgroundColor('#FFFFE0')
            }
            .layoutWeight(1)

            Column() {
              Text('居中')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES.slice(0, 3), selected: this.selectedCityIndex })
                .align(Alignment.Top)
                .backgroundColor('#FFFFE8')
            }
            .layoutWeight(1)

            Column() {
              Text('居右')
                .fontSize(12)
              TextPicker({ range: TEST_DATA_CITIES.slice(0, 3), selected: this.selectedCityIndex })
                .align(Alignment.TopEnd)
                .backgroundColor('#FFFFF0')
            }
            .layoutWeight(1)
          }
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 动画效果测试区 ==========

  @Builder
  buildAnimationTestSection() {
    Column() {
      // 区域标题
      Row() {
        Text('动画效果测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1)

        Button(this.showAnimationTest ? '收起' : '展开')
          .fontSize(14)
          .onClick(() => {
            this.toggleAnimationTest();
          })
      }
      .width('100%')
      .margin({ top: 15, bottom: 10 })

      if (this.showAnimationTest) {
        // 缩放动画
        Column() {
          Text('缩放动画')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .scale({ x: this.animationScale, y: this.animationScale })
            .animation({
              duration: 300,
              curve: Curve.EaseInOut
            })

          Button('切换缩放')
            .onClick(() => {
              this.startScaleAnimation();
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 旋转动画
        Column() {
          Text('旋转动画')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .rotate({ angle: this.animationRotation })
            .animation({
              duration: 500,
              curve: Curve.EaseInOut
            })

          Button('切换旋转')
            .onClick(() => {
              this.startRotationAnimation();
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 平移动画
        Column() {
          Text('平移动画')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .translate({ x: this.animationTranslate, y: 0 })
            .animation({
              duration: 300,
              curve: Curve.EaseInOut
            })

          Button('切换平移')
            .onClick(() => {
              this.startTranslateAnimation();
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 透明度动画
        Column() {
          Text('透明度动画')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .opacity(this.animationOpacity)
            .animation({
              duration: 300,
              curve: Curve.EaseInOut
            })

          Button('切换透明度')
            .onClick(() => {
              this.startOpacityAnimation();
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })

        // 组合动画
        Column() {
          Text('组合动画')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 })

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .scale({ x: this.animationScale, y: this.animationScale })
            .opacity(this.animationOpacity)
            .animation({
              duration: 300,
              curve: Curve.EaseInOut
            })

          Row() {
            Button('切换缩放')
              .onClick(() => {
                this.startScaleAnimation();
              })
            Button('切换透明度')
              .margin({ left: 10 })
              .onClick(() => {
                this.startOpacityAnimation();
              })
            Button('重置')
              .margin({ left: 10 })
              .onClick(() => {
                this.resetAnimations();
              })
          }
          .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8F8')
        .borderRadius(8)
        .margin({ bottom: 10 })
      }

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 禁用状态测试区 ==========

  @Builder
  buildDisabledTestSection() {
    Column() {
      Text('禁用状态测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Row() {
        Column() {
          Text('正常状态')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 5 })
          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width(150)
            .height(120)
        }
        .layoutWeight(1)

        Column() {
          Text('禁用状态')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 5 })
          TextPicker({ range: TEST_DATA_CITIES, selected: this.disabledPickerIndex })
            .width(150)
            .height(120)
            .enabled(false)
        }
        .layoutWeight(1)
      }
      .width('100%')

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 默认值测试区 ==========

  @Builder
  buildDefaultTestSection() {
    Column() {
      Text('默认值测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Column() {
        Text('默认选择第6项（索引5）')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: TEST_DATA_NUMBERS, selected: 5 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 极值测试区 ==========

  @Builder
  buildExtremeTestSection() {
    Column() {
      Text('极值测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      // 最小列表（1项）
      Column() {
        Text('最小列表（1项）')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: ['唯一选项'], selected: 0 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 10 })

      // 两项列表
      Column() {
        Text('两项列表')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: ['选项A', '选项B'], selected: 0 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 10 })

      // 最大索引测试
      Column() {
        Text('选择最后一项')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: TEST_DATA_MONTHS, selected: 11 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 边界条件测试区 ==========

  @Builder
  buildBoundaryTestSection() {
    Column() {
      Text('边界条件测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      // 空字符串测试
      Column() {
        Text('包含空字符串')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: ['', '选项A', '', '选项B', ''], selected: 1 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 10 })

      // 特殊字符测试
      Column() {
        Text('特殊字符')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: ['@#$%', '中文*&%', '混合123abc', '   ', '很长很长的文本内容用来测试显示效果'], selected: 0 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 10 })

      // 字符串类型range测试（数字需转为字符串）
      Column() {
        Text('字符串类型range（数字字符串）')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10'], selected: 4 })
          .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 性能测试区 ==========

  @Builder
  buildPerformanceTestSection() {
    Column() {
      Text('性能测试（多实例）')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Column() {
        Text('同时渲染多个TextPicker')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        // 渲染10个TextPicker
        ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], (item: number) => {
          Column() {
            Text('选择器 ' + (item + 1).toString())
              .fontSize(12)
            TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
              .height(100)
          }
          .margin({ bottom: 5 })
        }, (item: number) => item.toString())
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 多实例测试区 ==========

  @Builder
  buildMultiInstanceTestSection() {
    Column() {
      Text('多实例联动测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Column() {
        Text('主选择器')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 5 })
        TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.selectedCityIndex = index;
            }
          })

        Text('从选择器（同步主选择器的索引）')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ top: 10, bottom: 5 })
        TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.selectedCityIndex = index;
            }
          })

        Text('当前选中: ' + this.getSelectedCityText())
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 嵌套容器测试区 ==========

  @Builder
  buildNestedTestSection() {
    Column() {
      Text('嵌套容器测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      // Stack中的TextPicker
      Column() {
        Text('Stack容器中')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        Stack() {
          Text('背景文字')
            .fontSize(20)
            .fontColor('#CCCCCC')

          TextPicker({ range: TEST_DATA_CITIES, selected: this.selectedCityIndex })
            .width('80%')
        }
        .width('100%')
        .height(150)
        .backgroundColor('#F0F0F0')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 10 })

      // Grid中的TextPicker
      Column() {
        Text('Grid容器中')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        Grid() {
          ForEach([0, 1, 2, 3], (item: number) => {
            GridItem() {
              Column() {
                Text('项目 ' + (item + 1).toString())
                  .fontSize(12)
                TextPicker({ range: TEST_DATA_CITIES.slice(0, 3), selected: this.selectedCityIndex })
                  .height(100)
              }
            }
          }, (item: number) => item.toString())
        }
        .columnsTemplate('1fr 1fr')
        .rowsTemplate('1fr 1fr')
        .height(200)
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 状态保存测试区 ==========

  @Builder
  buildStateSaveTestSection() {
    Column() {
      Text('状态保存测试')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')
        .margin({ top: 15, bottom: 10 })

      Column() {
        Text('选择后切换页面，再返回时应保持选择状态')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 10 })

        TextPicker({ range: TEST_DATA_YEARS, selected: this.selectedYearIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            if (typeof index === 'number') {
              this.handleYearChange(value, index);
            }
          })

        Text('当前选择: ' + this.getSelectedYearText())
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })

        Row() {
          Text('其他选择器:')
            .fontSize(14)
            .fontColor('#666666')
          TextPicker({ range: TEST_DATA_MONTHS, selected: this.selectedMonthIndex })
            .layoutWeight(1)
            .onChange((value: string | string[], index: number | number[]) => {
              if (typeof index === 'number') {
                this.handleMonthChange(value, index);
              }
            })
        }
        .width('100%')
        .margin({ top: 10 })

        Text('当前选择: ' + this.getSelectedMonthText())
          .fontSize(14)
          .fontColor('#007DFF')
          .margin({ top: 10 })
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      Divider()
        .color('#E0E0E0')
        .margin({ top: 10, bottom: 10 })
    }
    .width('100%')
  }

  // ========== 重置按钮区 ==========

  @Builder
  buildResetSection() {
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

        Button('收起所有区域')
          .layoutWeight(1)
          .margin({ left: 10 })
          .onClick(() => {
            this.showBasicTest = false;
            this.showStyleTest = false;
            this.showEventTest = false;
            this.showComboTest = false;
            this.showCustomTest = false;
            this.showLayoutTest = false;
            this.showAnimationTest = false;
          })

        Button('展开所有区域')
          .layoutWeight(1)
          .margin({ left: 10 })
          .onClick(() => {
            this.showBasicTest = true;
            this.showStyleTest = true;
            this.showEventTest = true;
            this.showComboTest = true;
            this.showCustomTest = true;
            this.showLayoutTest = true;
            this.showAnimationTest = true;
          })
      }
      .width('100%')

      // 统计信息
      Column() {
        Text('测试-统计')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 20, bottom: 10 })

        Row() {
          Text('onChange触发次数: ' + this.onChangeCount.toString())
            .fontSize(14)
            .layoutWeight(1)
        }
        .width('100%')
        .margin({ bottom: 5 })

        Row() {
          Text('onAccept触发次数: ' + this.onAcceptCount.toString())
            .fontSize(14)
            .layoutWeight(1)
          Text('onCancel触发次数: ' + this.onCancelCount.toString())
            .fontSize(14)
            .layoutWeight(1)
        }
        .width('100%')
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F0F8FF')
      .borderRadius(8)
      .margin({ top: 20 })
    }
    .width('100%')
    .margin({ bottom: 30 })
  }
}
