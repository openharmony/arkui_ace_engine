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

import { drawing, common2D } from '@kit.ArkGraphics2D';
import { image } from '@kit.ImageKit';

interface ColorFilterPreset {
  name: string;
  matrix: number[];
  description: string;
}

interface ImageTransform {
  scale: number;
  rotate: number;
;
  translateX: number;
  translateY: number;
  skewX: number;
  skewY: number;
}

@Entry
@Component
struct ImageExample102 {
  @State currentImage: Resource = $r('app.media.example');
  @State selectedColorFilter: ColorFilterPreset | undefined = undefined;
  @State customColorFilter: number[] = [
    1, 0, 0, 0, 0,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0
  ];
  @State imageTransform: ImageTransform = {
    scale: 1,
    rotate: 0,
    translateX: 0,
    translateY: 0,
    skewX: 0,
    skewY: 0
  };
  @State renderMode: ImageRenderMode = ImageRenderMode.Original;
  @State brightness: number = 0;
  @State contrast: number = 1;
  @State saturation: number = 1;
  @State hue: number = 0;
  @State opacity: number = 1;
  @State showGrid: boolean = true;
  @State blendMode: BlendMode = BlendMode.SRC_OVER;
  @State useCustomFilter: boolean = false;
  @State animationEnabled: boolean = false;
  @State animationProgress: number = 0;

  private colorFilterPresets: ColorFilterPreset[] = [
    {
      name: '原图',
      matrix: [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0],
      description: '保持原始颜色'
    },
    {
      name: '灰度',
      matrix: [0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0],
      description: '转换为灰度图像'
    },
    {
      name: '褐色',
      matrix: [0.393, 0.769, 0.189, 0, 0, 0.349, 0.686, 0.168, 0, 0, 0.272, 0.534, 0.131, 0, 0],
      description: '复古褐色效果'
    },
    {
      name: '反色',
      matrix: [-1, 0, 0, 1, 0, 0, -1, 0, 1, 0, 0, 0, -1, 1, 0],
      description: '颜色反转'
    },
    {
      name: '复古',
      matrix: [0.272, 0.534, 0.131, 0, 0, 0.349, 0.686, 0.168, 0, 0, 0.393, 0.769, 0.189, 0, 0],
      description: '怀旧复古效果'
    },
    {
      name: '高对比',
      matrix: [1.5, 0, 0, 0, -0.25, 0, 1.5, 0, 0, -0.25, 0, 0, 1.5, 0, -0.25],
      description: '增强对比度'
    },
    {
      name: '暖色调',
      matrix: [1.2, 0, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0.9, 0, 0],
      description: '温暖色调'
    },
    {
      name: '冷色调',
      matrix: [0.9, 0, 0, 0, 0, 0, 0.9, 0, 0, 0, 0, 0, 1.2, 0, 0],
      description: '冷冽色调'
    }
  ];

  private blendModes: BlendMode[] = [
    BlendMode.SRC_OVER, BlendMode.SRC_IN, BlendMode.SRC_OUT,
    BlendMode.SRC_ATOP, BlendMode.DST_OVER, BlendMode.DST_IN,
    BlendMode.DST_OUT, BlendMode.DST_ATOP, BlendMode.XOR,
    BlendMode.PLUS, BlendMode.MULTIPLY, BlendMode.SCREEN,
    BlendMode.OVERLAY, BlendMode.DARKEN, BlendMode.LIGHTEN
  ];

  aboutToAppear(): void {
    this.selectedColorFilter = this.colorFilterPresets[0];
  }

  applyBrightnessContrast(matrix: number[]): number[] {
    const brightness = this.brightness;
    const contrast = this.contrast;

    const factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    const adjustedMatrix = matrix.map((value, index) => {
      if (index % 5 === 4) {
        return value;
      }
      return factor * (value - 128) + 128 + brightness;
    });

    return adjustedMatrix;
  }

  applySaturation(matrix: number[]): number[] {
    const sat = this.saturation;
    const satMatrix = [
      0.213 + 0.787 * (1 - sat),
      0.715 - 0.715 * (1 - sat),
      0.072 - 0.072 * (1 - sat),
      0,
      0.213 - 0.213 * (1 - sat),
      0.715 + 0.285 * (1 - sat),
      0.072 - 0.072 * (1 - sat),
      0,
      0.213 - 0.213 * (1 - sat),
      0.715 - 0.715 * (1 - sat),
      0.072 + 0.928 * (1 - sat),
      0
    ];

    return this.multiplyMatrices(matrix, satMatrix);
  }

  multiplyMatrices(matrix1: number[], matrix2: number[]): number[] {
    const result: number[] = new Array(20).fill(0);

    for (let i = 0; i < 4; i++) {
      for (let j = 0; j < 4; j++) {
        let sum = 0;
        for (let k = 0; k < 4; k++) {
          sum += matrix1[i * 5 + k] * matrix2[k * 5 + j];
        }
        result[i * 5 + j] = sum;
      }
      result[i * 5 + 4] = matrix1[i * 5 + 4];
    }

    return result;
  }

  getCurrentColorFilter(): ColorFilter {
    let matrix = this.useCustomFilter ? this.customColorFilter : this.selectedColorFilter!.matrix;
    matrix = this.applyBrightnessContrast(matrix);
    matrix = this.applySaturation(matrix);
    return new ColorFilter(matrix);
  }

  resetTransform(): void {
    this.imageTransform = {
      scale: 1,
      rotate: 0,
      translateX: 0,
      translateY: 0,
      skewX: 0,
      skewY: 0
    };
  }

  resetFilters(): void {
    this.brightness = 0;
    this.contrast = 1;
    this.saturation = 1;
    this.hue = 0;
    this.opacity = 1;
  }

  startAnimation(): void {
    if (!this.animationEnabled) {
      return;
    }

    this.animationProgress = 0;
    const animate = () => {
      if (!this.animationEnabled) {
        return;
      }

      this.animationProgress += 0.01;
      if (this.animationProgress > 1) {
        this.animationProgress = 0;
      }

      this.hue = Math.sin(this.animationProgress * Math.PI * 2) * 180;
      this.saturation = 1 + Math.sin(this.animationProgress * Math.PI * 2) * 0.5;

      setTimeout(animate, 16);
    };

    animate();
  }

  build() {
    Column() {
      this.buildHeader();
      this.buildMainContent();
      this.buildControlPanel();
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#1A1A1A');
  }

  @Builder
  buildHeader() {
    Column() {
      Text('图片高级滤镜编辑器')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.White)
        .margin({ bottom: 8 });

      Text('支持颜色滤镜、变换、混合模式等高级效果')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ bottom: 16 });

      Row() {
        Button('重置变换')
          .type(ButtonType.Normal)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.resetTransform();
          });

        Button('重置滤镜')
          .type(ButtonType.Normal)
          .backgroundColor('#2196F3')
          .margin({ left: 12 })
          .onClick(() => {
            this.resetFilters();
          });

        Button(this.animationEnabled ? '停止动画' : '开始动画')
          .type(ButtonType.Normal)
          .backgroundColor('#FF9800')
          .margin({ left: 12 })
          .onClick(() => {
            this.animationEnabled = !this.animationEnabled;
            if (this.animationEnabled) {
              this.startAnimation();
            }
          });
      }
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#2D2D2D')
    .borderRadius({ bottomLeft: 16, bottomRight: 16 });
  }

  @Builder
  buildMainContent() {
    Column() {
      if (this.showGrid) {
        this.buildImageGrid();
      } else {
        this.buildSingleImage();
      }
    }
    .width('100%')
    .layoutWeight(1)
    .padding(16);
  }

  @Builder
  buildImageGrid() {
    Grid() {
      GridItem() {
        this.buildImagePreview(false);
      }
      .columnStart(0)
      .rowStart(0);

      GridItem() {
        this.buildImagePreview(true);
      }
      .columnStart(1)
      .rowStart(0);
    }
    .columnsTemplate('1fr 1fr')
    .rowsTemplate('1fr')
    .width('100%')
    .height('100%');
  }

  @Builder
  buildSingleImage() {
    this.buildImagePreview(false);
  }

  @Builder
  buildImagePreview(withFilter: boolean) {
    Column() {
      Stack() {
        Image(this.currentImage)
          .width('100%')
          .height('100%')
          .objectFit(ImageFit.Contain)
          .renderMode(this.renderMode)
          .opacity(this.opacity)
          .border(withFilter ? 4 : 0)
          .borderColor(withFilter ? '#4CAF50' : Color.Transparent)
          .colorFilter(withFilter ? this.getCurrentColorFilter() : undefined)
          .borderRadius(8);

        if (withFilter) {
          Text('应用滤镜')
            .fontSize(12)
            .fontColor(Color.White)
            .backgroundColor('#4CAF5040')
            .padding({ left: 8, right: 8, top: 4, bottom: 4 })
            .borderRadius(4)
            .position({ x: 8, y: 8 });
        }
      }
      .width('100%')
      .height('100%');

      this.buildImageInfo();
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#3D3D3D')
    .borderRadius(12);
  }

  @Builder
  buildImageInfo() {
    Column() {
      Row() {
        Text('缩放: ')
          .fontSize(12)
          .fontColor('#999999');
        Text(`${this.imageTransform.scale.toFixed(2)}x`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });

        Text('旋转: ')
          .fontSize(12)
          .fontColor('#999999')
          .margin({ left: 16 });
        Text(`${this.imageTransform.rotate.toFixed(1)}°`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });
      }
      .margin({ bottom: 8 });

      Row() {
        Text('亮度: ')
          .fontSize(12)
          .fontColor('#999999');
        Text(`${this.brightness}`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });

        Text('对比度: ')
          .fontSize(12)
          .fontColor('#999999')
          .margin({ left: 16 });
        Text(`${this.contrast.toFixed(2)}`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });
      }
      .margin({ bottom: 8 });

      Row() {
        Text('饱和度: ')
          .fontSize(12)
          .fontColor('#999999');
        Text(`${this.saturation.toFixed(2)}`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });

        Text('透明度: ')
          .fontSize(12)
          .fontColor('#999999')
          .margin({ left: 16 });
        Text(`${this.opacity.toFixed(2)}`)
          .fontSize(12)
          .fontColor(Color.White)
          .margin({ left: 8 });
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#2D2D2D')
    .borderRadius(8);
  }

  @Builder
  buildControlPanel() {
    Column() {
      this.buildFilterPresets();
      this.buildTransformControls();
      this.buildColorAdjustments();
      this.buildAdvancedControls();
    }
    .width('100%')
    .padding(16)
    .backgroundColor('#2D2D2D')
    .borderRadius({ topLeft: 16, topRight: 16 });
  }

  @Builder
  buildFilterPresets() {
    Column() {
      Row() {
        Text('滤镜预设')
    .fontSize(16)
    .fontWeight(FontWeight.Medium)
    .fontColor(Color.White)
    .margin({ bottom: 12 });

        Toggle({ type: ToggleType.Switch, isOn: this.useCustomFilter })
          .onChange((isOn: boolean) => {
            this.useCustomFilter = isOn;
          });
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween);

      if (!this.useCustomFilter) {
        Grid() {
          ForEach(this.colorFilterPresets, (preset: ColorFilterPreset, index: number) => {
            GridItem() {
              Column() {
                Text(preset.name)
                  .fontSize(12)
                  .fontColor(Color.White)
                  .margin({ bottom: 4 });
                Text(preset.description)
                  .fontSize(10)
                  .fontColor('#999999')
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis });
              }
              .width('100%')
              .padding(12)
              .backgroundColor(
                this.selectedColorFilter?.name === preset.name ? '#4CAF50' : '#3D3D3D'
              )
              .borderRadius(8)
              .onClick(() => {
                this.selectedColorFilter = preset;
              });
            }
          }, (preset: ColorFilterPreset) => preset.name);
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(8)
        .columnsGap(8)
        .width('100%');
      }
    }
    .width('100%')
    .margin({ bottom: 16 });
  }

  @Builder
  buildTransformControls() {
    Column() {
      Text('变换控制')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.White)
        .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('缩放')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.imageTransform.scale, min: 0.1, max: 3, step: 0.1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageTransform.scale = value;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('旋转')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.imageTransform.rotate, min: -180, max: 180, step: 1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageTransform.rotate = value;
            });
        }
        .layoutWeight(1);
      }
      .width('100%')
      .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('X轴平移')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.imageTransform.translateX, min: -100, max: 100, step: 1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageTransform.translateX = value;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('Y轴平移')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.imageTransform.translateY, min: -100, max: 100, step: 1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageTransform.translateY = value;
            });
        }
        .layoutWeight(1);
      }
      .width('100%');
    }
    .width('100%')
    .margin({ bottom: 16 });
  }

  @Builder
  buildColorAdjustments() {
    Column() {
      Text('色彩调整')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.White)
        .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('亮度')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.brightness, min: -100, max: 100, step: 1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#2196F3')
            .onChange((value: number) => {
              this.brightness = value;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('对比度')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.contrast, min: 0, max: 2, step: 0.1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#2196F3')
            .onChange((value: number) => {
              this.contrast = value;
            });
        }
        .layoutWeight(1);
      }
      .width('100%')
      .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('饱和度')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.saturation, min: 0, max: 2, step: 0.1 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#2196F3')
            .onChange((value: number) => {
              this.saturation = value;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('透明度')
            .fontSize(12)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Slider({ value: this.opacity, min: 0, max: 1, step: 0.05 })
            .width('100%')
            .trackColor('#3D3D3D')
            .selectedColor('#2196F3')
            .onChange((value: number) => {
              this.opacity = value;
            });
        }
        .layoutWeight(1);
      }
      .width('100%');
    }
    .width('100%')
    .margin({ bottom: 16 });
  }

  @Builder
  buildAdvancedControls() {
    Column() {
      Row() {
        Column() {
          Text('渲染模式')
            .fontSize(14)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Select([ImageRenderMode.Original, ImageRenderMode.Template])
            .selected(this.renderMode)
            .value('ImageRenderMode')
            .font({ size: 12 })
            .selectedOptionBg('#4CAF50')
            .optionFont({ size: 12 })
            .onSelect((index: number) => {
              this.renderMode = index === 0 ? ImageRenderMode.Original : ImageRenderMode.Template;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('混合模式')
            .fontSize(14)
            .fontColor('#999999')
            .margin({ bottom: 8 });
          Select(this.blendModes.map(mode => this.getBlendModeName(mode)))
            .selected(this.getBlendModeName(this.blendMode))
            .value('string')
            .font({ size: 12 })
            .selectedOptionBg('#FF9800')
            .optionFont({ size: 12 })
            .onSelect((index: number) => {
              this.blendMode = this.blendModes[index];
            });
        }
        .layoutWeight(1);
      }
      .width('100%')
      .margin({ bottom: 12 });

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: this.showGrid })
          .onChange((isOn: boolean) => {
            this.showGrid = isOn;
          });
        Text('显示对比网格')
          .fontSize(14)
          .fontColor(Color.White)
          .margin({ left: 8 });
      }
    }
    .width('100%');
  }

  getBlendModeName(mode: BlendMode): string {
    const modeNames: Record<number, string> = {
      [BlendMode.SRC_OVER]: 'SRC_OVER',
      [BlendMode.SRC_IN]: 'SRC_IN',
      [BlendMode.SRC_OUT]: 'SRC_OUT',
      [BlendMode.SRC_ATOP]: 'SRC_ATOP',
      [BlendMode.DST_OVER]: 'DST_OVER',
      [BlendMode.DST_IN]: 'DST_IN',
      [BlendMode.DST_OUT]: 'DST_OUT',
      [BlendMode.DST_ATOP]: 'DST_ATOP',
      [BlendMode.XOR]: 'XOR',
      [BlendMode.PLUS]: 'PLUS',
      [BlendMode.MULTIPLY]: 'MULTIPLY',
      [BlendMode.SCREEN]: 'SCREEN',
      [BlendMode.OVERLAY]: 'OVERLAY',
      [BlendMode.DARKEN]: 'DARKEN',
      [BlendMode.LIGHTEN]: 'LIGHTEN'
    };
    return modeNames[mode] || 'UNKNOWN';
  }
}
