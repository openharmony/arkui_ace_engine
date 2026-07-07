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

import { uiMaterial, ColorMetrics, CustomColors, CustomTheme } from '@kit.ArkUI';

@Builder
export function SliderMaterialOtherScenariosBuilder(name: string, param: Object) {
  SliderMaterialOtherScenarios()
}

export class PageCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class ThemeColors implements CustomColors {
  public sliderTrackSelectedColor = 'rgb(226, 132, 96)'
  public compBackgroundSecondary = '#87CEFA'
  public compBackgroundPrimaryContrary = '#2E8B57'
}

const customTheme: CustomTheme = new PageCustomTheme(new ThemeColors());

@Entry
@Component
struct SliderMaterialOtherScenarios {
  pathStack: NavPathStack = new NavPathStack()

  @State sliderValue: number = 40;
  @State blockType: SliderBlockType = SliderBlockType.DEFAULT;
  @State blockTypeIndex: number = 0;
  @State blockSizeIndex: number = 0;
  @State materialIndex: number = 0;
  @State materialType: uiMaterial.Material | undefined = undefined;
  @State gradientIndex: number = 0;
  @State thicknessIndex: number = 0;
  @State stepColorIndex: number = 0;
  @State selectedColorIndex: number = 0;

  blockTypeArray: Array<SelectOption> = [
    { value: 'DEFAULT' },
    { value: 'IMAGE' },
    { value: 'SHAPE' }
  ]

  materialArray: Array<SelectOption> = [
    { value: 'undefined' },
    { value: 'NONE' },
    { value: 'SEMI_TRANSPARENT' }
  ]

  blockSizeArray: Array<SelectOption> = [
    { value: '默认尺寸' },
    { value: '大尺寸 40x40' },
    { value: '小尺寸 10x10' }
  ]

  gradientArray: Array<SelectOption> = [
    { value: '双色渐变(蓝-紫)' },
    { value: '多色渐变(红-黄-绿)' },
    { value: '深色渐变(青-粉)' },
    { value: '无渐变' }
  ]

  thicknessArray: Array<SelectOption> = [
    { value: '默认厚度' },
    { value: '细厚度 4vp' },
    { value: '中等厚度 8vp' },
    { value: '粗厚度 12vp' }
  ]

  stepColorArray: Array<SelectOption> = [
    { value: '金色 #FFD700' },
    { value: '白色 #FFFFFF' },
    { value: '黑色 #000000' },
    { value: '默认颜色' }
  ]

  selectedColorArray: Array<SelectOption> = [
    { value: '红色 #FF6B6B' },
    { value: '蓝色 #4169E1' },
    { value: '绿色 #6BCB77' },
    { value: '默认颜色' }
  ]

  getMaterialType(index: number): uiMaterial.Material | undefined {
    switch (index) {
      case 0:
        return undefined;
      case 1:
        return new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE });
      case 2:
        return new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });
      default:
        return undefined;
    }
  }

  getBlockSize(index: number): Size {
    switch (index) {
      case 0:
        return { width: 20, height: 20 };
      case 1:
        return { width: 40, height: 40 };
      case 2:
        return { width: 10, height: 10 };
      default:
        return { width: 20, height: 20 };
    }
  }

  getGradient(index: number): ColorMetricsLinearGradient | undefined {
    switch (index) {
      case 0:
        return new ColorMetricsLinearGradient([
          { color: ColorMetrics.numeric(0x0000FF), offset: 0 },
          { color: ColorMetrics.numeric(0x800080), offset: 1 }
        ]);
      case 1:
        return new ColorMetricsLinearGradient([
          { color: ColorMetrics.numeric(0xFF6B6B), offset: 0 },
          { color: ColorMetrics.numeric(0xFFD93D), offset: 0.5 },
          { color: ColorMetrics.numeric(0x6BCB77), offset: 1 }
        ]);
      case 2:
        return new ColorMetricsLinearGradient([
          { color: ColorMetrics.numeric(0x20B2AA), offset: 0 },
          { color: ColorMetrics.numeric(0xFF1493), offset: 1 }
        ]);
      case 3:
        return undefined;
      default:
        return undefined;
    }
  }

  getThickness(index: number): number {
    switch (index) {
      case 0:
        return 0;
      case 1:
        return 4;
      case 2:
        return 8;
      case 3:
        return 12;
      default:
        return 0;
    }
  }

  getStepColor(index: number): ResourceColor | undefined {
    switch (index) {
      case 0:
        return '#FFD700';
      case 1:
        return '#FFFFFF';
      case 2:
        return '#000000';
      case 3:
        return undefined;
      default:
        return undefined;
    }
  }

  getSelectedColor(index: number): ResourceColor | undefined {
    switch (index) {
      case 0:
        return '#FF6B6B';
      case 1:
        return '#4169E1';
      case 2:
        return '#6BCB77';
      case 3:
        return undefined;
      default:
        return undefined;
    }
  }

  build() {
    NavDestination() {
      Column() {
        Scroll() {
          Column({ space: 12 }) {
            Text('配置面板')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 10 })

            Row() {
              Text('systemMaterial:')
                .fontSize(14)
                .width('40%')
              Select(this.materialArray)
                .value(this.materialArray[this.materialIndex].value)
                .selected(this.materialIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.materialIndex = index;
                  this.materialType = this.getMaterialType(index);
                })
            }
            .width('100%')

            Row() {
              Text('blockType:')
                .fontSize(14)
                .width('40%')
              Select(this.blockTypeArray)
                .value(this.blockTypeArray[this.blockTypeIndex].value)
                .selected(this.blockTypeIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.blockTypeIndex = index;
                  this.blockType = index === 0 ? SliderBlockType.DEFAULT :
                    index === 1 ? SliderBlockType.IMAGE : SliderBlockType.SHAPE;
                })
            }
            .width('100%')

            Row() {
              Text('blockSize:')
                .fontSize(14)
                .width('40%')
              Select(this.blockSizeArray)
                .value(this.blockSizeArray[this.blockSizeIndex].value)
                .selected(this.blockSizeIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.blockSizeIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('trackColorMetrics:')
                .fontSize(14)
                .width('40%')
              Select(this.gradientArray)
                .value(this.gradientArray[this.gradientIndex].value)
                .selected(this.gradientIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.gradientIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('trackThickness:')
                .fontSize(14)
                .width('40%')
              Select(this.thicknessArray)
                .value(this.thicknessArray[this.thicknessIndex].value)
                .selected(this.thicknessIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.thicknessIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('stepColor:')
                .fontSize(14)
                .width('40%')
              Select(this.stepColorArray)
                .value(this.stepColorArray[this.stepColorIndex].value)
                .selected(this.stepColorIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.stepColorIndex = index;
                })
            }
            .width('100%')

            Row() {
              Text('selectedColor:')
                .fontSize(14)
                .width('40%')
              Select(this.selectedColorArray)
                .value(this.selectedColorArray[this.selectedColorIndex].value)
                .selected(this.selectedColorIndex)
                .width('60%')
                .onSelect((index: number) => {
                  this.selectedColorIndex = index;
                })
            }
            .width('100%')

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('Value值控制')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 10, bottom: 10 })

            Row() {
              Text('当前值: ' + this.sliderValue.toFixed(0))
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Blue)
            }
            .width('100%')

            Text('正常值测试 (min=0, max=100)')
              .fontSize(12)
              .fontColor(0x666666)
              .margin({ top: 8 })

            Row({ space: 10 }) {
              Button('设为 0')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 0;
                })
              Button('设为 50')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 50;
                })
              Button('设为 100')
                .fontSize(12)
                .width(80)
                .onClick(() => {
                  this.sliderValue = 100;
                })
            }
            .width('100%')

            Text('异常值测试')
              .fontSize(12)
              .fontColor(0x666666)
              .margin({ top: 8 })

            Row({ space: 10 }) {
              Button('设为 -10')
                .fontSize(12)
                .width(80)
                .backgroundColor(Color.Red)
                .onClick(() => {
                  this.sliderValue = -10;
                })
              Button('设为 150')
                .fontSize(12)
                .width(80)
                .backgroundColor(Color.Red)
                .onClick(() => {
                  this.sliderValue = 150;
                })
            }
            .width('100%')

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('Slider展示区域')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Column({ space: 20 }) {
              Text('OutSet Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.OutSet,
                step: 10
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .trackColorMetrics(this.getGradient(this.gradientIndex))
                .trackThickness(this.getThickness(this.thicknessIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                .stepColor(this.getStepColor(this.stepColorIndex))
                .showSteps(true)
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })

              Text('InSet Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.InSet,
                step: 10
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .trackColorMetrics(this.getGradient(this.gradientIndex))
                .trackThickness(this.getThickness(this.thicknessIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                .stepColor(this.getStepColor(this.stepColorIndex))
                .showSteps(true)
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })

              Text('NONE Slider')
                .fontSize(12)
                .fontColor(0x666666)
              Slider({
                value: this.sliderValue,
                style: SliderStyle.NONE,
                step: 10
              })
                .blockSize(this.getBlockSize(this.blockSizeIndex))
                .blockStyle({
                  type: this.blockType,
                  image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                  shape: this.blockType === SliderBlockType.SHAPE ?
                    new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                })
                .trackColorMetrics(this.getGradient(this.gradientIndex))
                .trackThickness(this.getThickness(this.thicknessIndex))
                .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                .stepColor(this.getStepColor(this.stepColorIndex))
                .showSteps(true)
                .systemMaterial(this.materialType)
                .onChange((value: number) => {
                  this.sliderValue = value;
                })
            }
            .width('100%')
            .padding({ left: 20, right: 20, bottom: 20 })
            .backgroundColor(Color.Gray)
            .borderRadius(8)

            Divider()
              .margin({ top: 10, bottom: 10 })

            Text('WithTheme测试区域')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)

            Text('以下Slider在WithTheme组件下测试主题适配')
              .fontSize(12)
              .fontColor(0x666666)

            WithTheme({ theme: customTheme }) {
              Column({ space: 20 }) {
                Text('OutSet Slider (WithTheme)')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.OutSet,
                  step: 10
                })
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .trackColorMetrics(this.getGradient(this.gradientIndex))
                  .trackThickness(this.getThickness(this.thicknessIndex))
                  .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                  .stepColor(this.getStepColor(this.stepColorIndex))
                  .showSteps(true)
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })

                Text('InSet Slider (WithTheme)')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.InSet,
                  step: 10
                })
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .trackColorMetrics(this.getGradient(this.gradientIndex))
                  .trackThickness(this.getThickness(this.thicknessIndex))
                  .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                  .stepColor(this.getStepColor(this.stepColorIndex))
                  .showSteps(true)
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })

                Text('NONE Slider (WithTheme)')
                  .fontSize(12)
                  .fontColor(0x666666)
                Slider({
                  value: this.sliderValue,
                  style: SliderStyle.NONE,
                  step: 10
                })
                  .blockSize(this.getBlockSize(this.blockSizeIndex))
                  .blockStyle({
                    type: this.blockType,
                    image: this.blockType === SliderBlockType.IMAGE ? $r('sys.media.ohos_app_icon') : undefined,
                    shape: this.blockType === SliderBlockType.SHAPE ?
                      new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) : undefined
                  })
                  .trackColorMetrics(this.getGradient(this.gradientIndex))
                  .trackThickness(this.getThickness(this.thicknessIndex))
                  .selectedColor(this.getSelectedColor(this.selectedColorIndex))
                  .stepColor(this.getStepColor(this.stepColorIndex))
                  .showSteps(true)
                  .systemMaterial(this.materialType)
                  .onChange((value: number) => {
                    this.sliderValue = value;
                  })
              }
              .width('100%')
              .padding({ left: 20, right: 20, bottom: 20 })
              .backgroundColor('#E8F4F8')
              .borderRadius(8)
            }
          }
          .width('100%')
          .padding(16)
        }
        .width('100%')
        .height('100%')
      }
      .width('100%')
      .height('100%')
    }
    .title('Slider其他场景测试')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}