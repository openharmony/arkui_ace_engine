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
 * ArcSlider样式测试用例 - 展示各种样式配置效果
 * 包括描边粗细、颜色配置、模糊值等样式的动态调整
 * 可用于验证不同样式组合下的渲染效果
 */
import {
  ArcSlider,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

// 样式预设配置
interface StylePreset {
  name: string;
  trackThickness: number;
  activeTrackThickness: number;
  trackColor: string;
  selectedColor: string;
  trackBlur: number;
}

// 颜色预设配置
interface ColorPreset {
  name: string;
  value: string;
}

@Entry
@ComponentV2
struct ArcSliderExample003 {
  // 样式预设列表
  private stylePresets: StylePreset[] = [
    {
      name: '默认样式',
      trackThickness: 5,
      activeTrackThickness: 24,
      trackColor: '#33FFFFFF',
      selectedColor: '#FF5EA1FF',
      trackBlur: 20
    },
    {
      name: '深色主题',
      trackThickness: 6,
      activeTrackThickness: 26,
      trackColor: '#40FFFFFF',
      selectedColor: '#FFFFD700',
      trackBlur: 25
    },
    {
      name: '细线条',
      trackThickness: 5,
      activeTrackThickness: 20,
      trackColor: '#20FFFFFF',
      selectedColor: '#FF00FF00',
      trackBlur: 10
    },
    {
      name: '粗线条',
      trackThickness: 10,
      activeTrackThickness: 30,
      trackColor: '#60FFFFFF',
      selectedColor: '#FFFF0000',
      trackBlur: 30
    },
    {
      name: '高模糊',
      trackThickness: 8,
      activeTrackThickness: 28,
      trackColor: '#33FFFFFF',
      selectedColor: '#FFFF6600',
      trackBlur: 40
    },
    {
      name: '无模糊',
      trackThickness: 7,
      activeTrackThickness: 25,
      trackColor: '#50FFFFFF',
      selectedColor: '#FF0066FF',
      trackBlur: 0
    }
  ];

  @Local currentPresetIndex: number = 0;

  // 自定义样式值
  @Local trackThickness: number = 5;
  @Local activeTrackThickness: number = 24;
  @Local trackColor: string = '#33FFFFFF';
  @Local selectedColor: string = '#FF5EA1FF';
  @Local trackBlur: number = 20;

  // 当前进度值
  @Local progressValue: number = 60;

  // 放大状态
  @Local isEnlarged: boolean = false;

  // ArcSlider配置
  @Local arcSliderOptions: ArcSliderOptions = new ArcSliderOptions({});

  // 颜色预设
  private colorPresets: ColorPreset[] = [
    { name: '白色淡', value: '#33FFFFFF' },
    { name: '白色中', value: '#66FFFFFF' },
    { name: '白色深', value: '#99FFFFFF' },
    { name: '蓝色亮', value: '#FF5EA1FF' },
    { name: '蓝色深', value: '#FF3366FF' },
    { name: '绿色', value: '#FF00FF00' },
    { name: '红色', value: '#FFFF0000' },
    { name: '黄色', value: '#FFFFD700' },
    { name: '橙色', value: '#FFFF6600' },
    { name: '紫色', value: '#FF9932CC' }
  ];

  @Local trackColorIndex: number = 0;
  @Local selectedColorIndex: number = 3;

  aboutToAppear() {
    this.arcSliderOptions = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.progressValue,
        min: 0,
        max: 100
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: this.trackThickness,
        activeTrackThickness: this.activeTrackThickness,
        trackColor: this.trackColor,
        selectedColor: this.selectedColor,
        trackBlur: this.trackBlur
      }),
      onChange: (progress: number) => {
        this.progressValue = progress;
      },
      onEnlarge: (isEnlarged: boolean) => {
        this.isEnlarged = isEnlarged;
      }
    });
  }

  // 应用预设样式
  applyPreset(preset: StylePreset) {
    this.trackThickness = preset.trackThickness;
    this.activeTrackThickness = preset.activeTrackThickness;
    this.trackColor = preset.trackColor;
    this.selectedColor = preset.selectedColor;
    this.trackBlur = preset.trackBlur;

    if (this.arcSliderOptions.styleOptions) {
      this.arcSliderOptions.styleOptions.trackThickness = preset.trackThickness;
      this.arcSliderOptions.styleOptions.activeTrackThickness = preset.activeTrackThickness;
      this.arcSliderOptions.styleOptions.trackColor = preset.trackColor;
      this.arcSliderOptions.styleOptions.selectedColor = preset.selectedColor;
      this.arcSliderOptions.styleOptions.trackBlur = preset.trackBlur;
    }

    // 更新颜色索引
    for (let i = 0; i < this.colorPresets.length; i++) {
      if (this.colorPresets[i].value === preset.trackColor) {
        this.trackColorIndex = i;
        break;
      }
    }
    for (let i = 0; i < this.colorPresets.length; i++) {
      if (this.colorPresets[i].value === preset.selectedColor) {
        this.selectedColorIndex = i;
        break;
      }
    }
  }

  build() {
    Scroll() {
      Column() {
        Text('ArcSlider 样式测试')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15, bottom: 15 })

        // ArcSlider展示区域
        Stack() {
          Circle({ width: 466, height: 466 })
            .strokeWidth(0.1)
            .fill(Color.White)

          ArcSlider({ options: this.arcSliderOptions })
        }
        .width("120%")
        .height(500)
        .margin({ bottom: 20 })

        // 当前值和状态显示
        Row() {
          Text('进度: ')
            .fontSize(14)
          Text(this.progressValue.toFixed(1).toString())
            .fontSize(18)
            .fontColor('#FF5EA1FF')
            .fontWeight(FontWeight.Bold)

          Blank()

          Text('状态: ')
            .fontSize(14)
          Text(this.isEnlarged ? '放大' : '正常')
            .fontSize(14)
            .fontColor(this.isEnlarged ? '#FF5EA1FF' : '#666666')
            .fontWeight(FontWeight.Bold)
        }
        .width('90%')
        .margin({ bottom: 20 })

        // 样式预设选择
        Column() {
          Text('样式预设')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.stylePresets, (preset: StylePreset, index: number) => {
              Text(preset.name)
                .fontSize(12)
                .padding({ left: 10, right: 10, top: 6, bottom: 6 })
                .margin(5)
                .backgroundColor(this.currentPresetIndex === index ? '#FF5EA1FF' : '#E0E0E0')
                .fontColor(this.currentPresetIndex === index ? '#FFFFFF' : '#333333')
                .borderRadius(15)
                .onClick(() => {
                  this.currentPresetIndex = index;
                  this.applyPreset(preset);
                })
            })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 描边粗细配置
        Column() {
          Text('描边粗细 (5-16)')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 8 })

          Slider({
            value: this.trackThickness,
            min: 5,
            max: 16,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('100%')
            .onChange((value: number) => {
              this.trackThickness = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.trackThickness = value;
              }
            })

          Row() {
            Text('当前值: ')
              .fontSize(12)
            Text(this.trackThickness.toString() + ' vp')
              .fontSize(12)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ top: 5 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 15 })

        // 放大粗细配置
        Column() {
          Text('放大粗细 (24-36)')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 8 })

          Slider({
            value: this.activeTrackThickness,
            min: 24,
            max: 36,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('100%')
            .onChange((value: number) => {
              this.activeTrackThickness = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.activeTrackThickness = value;
              }
            })

          Row() {
            Text('当前值: ')
              .fontSize(12)
            Text(this.activeTrackThickness.toString() + ' vp')
              .fontSize(12)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ top: 5 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 15 })

        // 模糊值配置
        Column() {
          Text('模糊值')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 8 })

          Slider({
            value: this.trackBlur,
            min: 0,
            max: 40,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('100%')
            .onChange((value: number) => {
              this.trackBlur = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.trackBlur = value;
              }
            })

          Row() {
            Text('当前值: ')
              .fontSize(12)
            Text(this.trackBlur.toString() + ' vp')
              .fontSize(12)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ top: 5 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 15 })

        // 背景颜色配置
        Column() {
          Text('描边背景色')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 8 })

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.colorPresets, (color: ColorPreset, index: number) => {
              Circle({ width: 30, height: 30 })
                .fill(color.value)
                .margin(6)
                .borderWidth(this.trackColorIndex === index ? 2 : 0)
                .borderColor('#FF5EA1FF')
                .onClick(() => {
                  this.trackColorIndex = index;
                  this.trackColor = color.value;
                  if (this.arcSliderOptions.styleOptions) {
                    this.arcSliderOptions.styleOptions.trackColor = color.value;
                  }
                })
            })
          }
          .width('100%')

          Text('当前: ' + this.colorPresets[this.trackColorIndex].name)
            .fontSize(12)
            .fontColor('#666666')
            .margin({ top: 8 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 15 })

        // 高亮颜色配置
        Column() {
          Text('描边高亮色')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 8 })

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.colorPresets, (color: ColorPreset, index: number) => {
              Circle({ width: 30, height: 30 })
                .fill(color.value)
                .margin(6)
                .borderWidth(this.selectedColorIndex === index ? 2 : 0)
                .borderColor('#FF5EA1FF')
                .onClick(() => {
                  this.selectedColorIndex = index;
                  this.selectedColor = color.value;
                  if (this.arcSliderOptions.styleOptions) {
                    this.arcSliderOptions.styleOptions.selectedColor = color.value;
                  }
                })
            })
          }
          .width('100%')

          Text('当前: ' + this.colorPresets[this.selectedColorIndex].name)
            .fontSize(12)
            .fontColor('#666666')
            .margin({ top: 8 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 30 })
      }
      .width('100%')
      .padding({ left: 15, right: 15 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
  }
}
