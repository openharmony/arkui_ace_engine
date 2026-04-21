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

import { drawing } from '@kit.ArkGraphics2D';

interface ResizableConfig {
  name: string;
  top: number;
  bottom: number;
  left: number;
  right: number;
  description: string;
}

interface LatticeConfig {
  name: string;
  xDivs: number[];
  yDivs: number[];
  description: string;
}

@Entry
@Component
struct ImageExample103 {
  @State currentImage: Resource = $r('app.media.example');
  @State useSlice: boolean = true;
  @State resizableConfig: ResizableConfig = {
    name: '均衡拉伸',
    top: 20,
    bottom: 20,
    left: 20,
    right: 20,
    description: '四边均匀拉伸'
  };
  @State latticeConfig: LatticeConfig = {
    name: '九宫格',
    xDivs: [50, 150, 200],
    yDivs: [50, 150, 200],
    description: '经典九宫格拉伸'
  };
  @State imageWidth: number = 300;
  @State imageHeight: number = 300;
  @State showGrid: boolean = true;
  @State showOriginal: boolean = false;
  @State animationEnabled: boolean = false;
  @State animationPhase: number = 0;
  @State currentLattice: DrawingLattice | undefined = undefined;

  private slicePresets: ResizableConfig[] = [
    {
      name: '仅顶部',
      top: 30,
      bottom: 0,
      left: 0,
      right: 0,
      description: '只拉伸顶部区域'
    },
    {
      name: '仅底部',
      top: 0,
      bottom: 30,
      left: 0,
      right: 0,
      description: '只拉伸底部区域'
    },
    {
      name: '仅左侧',
      top: 0,
      bottom: 0,
      left: 30,
      right: 0,
      description: '只拉伸左侧区域'
    },
    {
      name: '仅右侧',
      top: 0,
      bottom: 0,
      left: 0,
      right: 30,
      description: '只拉伸右侧区域'
    },
    {
      name: '上下拉伸',
      top: 25,
      bottom: 25,
      left: 0,
      right: 0,
      description: '上下边拉伸'
    },
    {
      name: '左右拉伸',
      top: 0,
      bottom: 0,
      left: 25,
      right: 25,
      description: '左右边拉伸'
    },
    {
      name: '四角固定',
      top: 40,
      bottom: 40,
      left: 40,
      right: 40,
      description: '四角固定，边框拉伸'
    },
    {
      name: '均匀拉伸',
      top: 20,
      bottom: 20,
      left: 20,
      right: 20,
      description: '四边均匀拉伸'
    }
  ];

  private latticePresets: LatticeConfig[] = [
    {
      name: '九宫格',
      xDivs: [50, 150, 200],
      yDivs: [50, 150, 200],
      description: '经典九宫格'
    },
    {
      name: '五宫格',
      xDivs: [100, 200],
      yDivs: [50, 150, 200],
      description: '横向五宫格'
    },
    {
      name: '十二宫格',
      xDivs: [50, 100, 150, 200],
      yDivs: [50, 100, 150, 200],
      description: '精细十二宫格'
    },
    {
      name: '十六宫格',
      xDivs: [50, 100, 150, 200],
      yDivs: [50, 100, 150, 200],
      description: '均匀十六宫格'
    },
    {
      name: '顶部三宫格',
      xDivs: [50, 150, 200],
      yDivs: [100, 200],
      description: '顶部固定，底部拉伸'
    },
    {
      name: '底部三宫格',
      xDivs: [50, 150, 200],
      yDivs: [50, 150],
      description: '底部固定，顶部拉伸'
    },
    {
      name: '左侧三宫格',
      xDivs: [100, 200],
      yDivs: [50, 150, 200],
      description: '左侧固定，右侧拉伸'
    },
    {
      name: '右侧三宫格',
      xDivs: [50, 150],
      yDivs: [50, 150, 200],
      description: '右侧固定，左侧拉伸'
    }
  ];

  aboutToAppear(): void {
    this.currentLattice = drawing.Lattice.createImageLattice(
      this.latticeConfig.xDivs,
      this.latticeConfig.yDivs,
      this.latticeConfig.xDivs.length,
      this.latticeConfig.yDivs.length
    );
  }

  selectSlicePreset(preset: ResizableConfig): void {
    this.resizableConfig = preset;
    this.useSlice = true;
  }

  selectLatticePreset(preset: LatticeConfig): void {
    this.latticeConfig = preset;
    this.currentLattice = drawing.Lattice.createImageLattice(
      preset.xDivs,
      preset.yDivs,
      preset.xDivs.length,
      preset.yDivs.length
    );
    this.useSlice = false;
  }

  resizeImage(width: number, height: number): void {
    this.imageWidth = width;
    this.imageHeight = height;
  }

  startAnimation(): void {
    if (!this.animationEnabled) {
      return;
    }

    this.animationPhase = 0;
    const animate = () => {
      if (!this.animationEnabled) {
        return;
      }

      this.animationPhase += 0.02;
      if (this.animationPhase > 1) {
        this.animationPhase = 0;
      }

      const phase = Math.sin(this.animationPhase * Math.PI * 2);
      const baseSize = 200;
      const size = baseSize + phase * 100;

      this.imageWidth = size;
      this.imageHeight = size;

      setTimeout(animate, 16);
    };

    animate();
  }

  resetToDefault(): void {
    this.imageWidth = 300;
    this.imageHeight = 300;
    this.resizableConfig = this.slicePresets[7];
    this.latticeConfig = this.latticePresets[0];
    this.currentLattice = drawing.Lattice.createImageLattice(
      this.latticeConfig.xDivs,
      this.latticeConfig.yDivs,
      this.latticeConfig.xDivs.length,
      this.latticeConfig.yDivs.length
    );
    this.useSlice = true;
    this.showGrid = true;
    this.showOriginal = false;
  }

  build() {
    Column() {
      this.buildHeader();
      this.buildMainContent();
      this.buildControlPanel();
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F4F8');
  }

  @Builder
  buildHeader() {
    Column() {
      Text('图片可拉伸区域编辑器')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.White)
        .margin({ bottom: 8 });

      Text('支持Slice边框拉伸和Lattice网格拉伸')
        .fontSize(14)
        .fontColor('#E0E0E0')
        .margin({ bottom: 16 });

      Row() {
        Button('重置默认')
          .type(ButtonType.Normal)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.resetToDefault();
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

        Toggle({ type: ToggleType.Switch, isOn: this.showOriginal })
          .onChange((isOn: boolean) => {
            this.showOriginal = isOn;
          });
        Text('显示原图')
          .fontSize(14)
          .fontColor(Color.White)
          .margin({ left: 8 });
      }
      .margin({ bottom: 16 });
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#1976D2');
  }

  @Builder
  buildMainContent() {
    Column() {
      if (this.showOriginal) {
        this.buildOriginalImage();
      } else {
        this.buildResizableImage();
      }
    }
    .width('100%')
    .layoutWeight(1)
    .padding(16);
  }

  @Builder
  buildOriginalImage() {
    Column() {
      Text('原图')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      Image(this.currentImage)
        .width(this.imageWidth)
        .height(this.imageHeight)
        .objectFit(ImageFit.Contain)
        .borderRadius(8)
        .shadow({
          radius: 8,
          color: '#00000033',
          offsetX: 0,
          offsetY: 4
        });

      this.buildImageInfo();
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center);
  }

  @Builder
  buildResizableImage() {
    Column() {
      Text(this.useSlice ? 'Slice边框拉伸' : 'Lattice网格拉伸')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      if (this.showGrid) {
        this.buildImageWithGrid();
      } else {
        this.buildImageOnly();
      }

      this.buildImageInfo();
    }
    .width('100%')
    .height('100%');
  }

  @Builder
  buildImageWithGrid() {
    Row() {
      Column() {
        Text('效果图')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 8 });

        Image(this.currentImage)
          .width(this.imageWidth)
          .height(this.imageHeight)
          .objectFit(ImageFit.Contain)
          .resizable(this.useSlice ? {
            slice: {
              top: `${this.resizableConfig.top}px`,
              bottom: `${this.resizableConfig.bottom}px`,
              left: `${this.resizableConfig.left}px`,
              right: `${this.resizableConfig.right}px`
            }
          } : {
            lattice: this.currentLattice
          })
          .borderRadius(8)
          .shadow({
            radius: 8,
            color: '#00000033',
            offsetX: 0,
            offsetY: 4
          });
      }
      .layoutWeight(1);

      Column() {
        Text('网格示意')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 8 });

        this.buildGridPreview();
      }
      .layoutWeight(1);
    }
    .width('100%')
    .height('100%');
  }

  @Builder
  buildImageOnly() {
    Image(this.currentImage)
      .width(this.imageWidth)
      .height(this.imageHeight)
      .objectFit(ImageFit.Contain)
      .resizable(this.useSlice ? {
        slice: {
          top: `${this.resizableConfig.top}px`,
          bottom: `${this.resizableConfig.bottom}px`,
          left: `${this.resizableConfig.left}px`,
          right: `${this.resizableConfig.right}px`
        }
      } : {
        lattice: this.currentLattice
      })
      .borderRadius(8)
      .shadow({
        radius: 8,
        color: '#00000033',
        offsetX: 0,
        offsetY: 4
      });
  }

  @Builder
  buildGridPreview() {
    Stack() {
      Image(this.currentImage)
        .width(this.imageWidth)
        .height(this.imageHeight)
        .objectFit(ImageFit.Contain)
        .opacity(0.3);

      this.buildGridLines();
    }
    .width(this.imageWidth)
    .height(this.imageHeight)
    .borderRadius(8)
    .border({ width: 1, color: '#4CAF50' });
  }

  @Builder
  buildGridLines() {
    if (this.useSlice) {
      this.buildSliceGridLines();
    } else {
      this.buildLatticeGridLines();
    }
  }

  @Builder
  buildSliceGridLines() {
    Column() {
      if (this.resizableConfig.top > 0) {
        Divider()
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ top: this.resizableConfig.top });
      }

      if (this.resizableConfig.bottom > 0) {
        Divider()
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ bottom: this.resizableConfig.bottom });
      }
    }
    .width('100%')
    .height('100%')
    .position({ x: 0, y: 0 });

    Row() {
      if (this.resizableConfig.left > 0) {
        Divider()
          .vertical(true)
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ left: this.resizableConfig.left });
      }

      if (this.resizableConfig.right > 0) {
        Divider()
          .vertical(true)
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ right: this.resizableConfig.right });
      }
    }
    .width('100%')
    .height('100%')
    .position({ x: 0, y: 0 });
  }

  @Builder
  buildLatticeGridLines() {
    const xDivs = this.latticeConfig.xDivs;
    const yDivs = this.latticeConfig.yDivs;

    Column() {
      ForEach(yDivs, (y: number, index: number) => {
        Divider()
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ top: index === 0 ? y : y - yDivs[index - 1] });
      }, (y: number) => y.toString());
    }
    .width('100%')
    .height('100%')
    .position({ x: 0, y: 0 });

    Row() {
      ForEach(xDivs, (x: number, index: number) => {
        Divider()
          .vertical(true)
          .strokeWidth(2)
          .color('#FF5722')
          .margin({ left: index === 0 ? x : x - xDivs[index - 1] });
      }, (x: number) => x.toString());
    }
    .width('100%')
    .height('100%')
    .position({ x: 0, y: 0 });
  }

  @Builder
  buildImageInfo() {
    Column() {
      Row() {
        Text('尺寸: ')
          .fontSize(14)
          .fontColor('#666666');
        Text(`${this.imageWidth.toFixed(0)} x ${this.imageHeight.toFixed(0)}`)
          .fontSize(14)
          .fontWeight(FontWeight.Medium);
      }
      .margin({ bottom: 8 });

      Row() {
        Text('模式: ')
          .fontSize(14)
          .fontColor('#666666');
        Text(this.useSlice ? this.resizableConfig.name : this.latticeConfig.name)
          .fontSize(14)
          .fontWeight(FontWeight.Medium);
      }
      .margin({ bottom: 8 });

      if (this.useSlice) {
        Text(this.resizableConfig.description)
          .fontSize(12)
          .fontColor('#999999');
      } else {
        Text(this.latticeConfig.description)
          .fontSize(12)
          .fontColor('#999999');
      }
    }
    .width('100%')
    .padding(12)
    .margin({ top: 12 })
    .backgroundColor('#F5FFFA')
    .borderRadius(8);
  }

  @Builder
  buildControlPanel() {
    Column() {
      this.buildModeToggle();
      this.buildSizeControls();
      this.buildPresetSelector();
      this.buildGridToggle();
    }
    .width('100%')
    .padding(16)
    .backgroundColor(Color.White)
    .borderRadius({ topLeft: 16, topRight: 16 });
  }

  @Builder
  buildModeToggle() {
    Row() {
      Column() {
        Text('Slice模式')
          .fontSize(14)
          .margin({ bottom: 8 });
        Button('使用Slice')
          .type(ButtonType.Normal)
          .backgroundColor(this.useSlice ? '#4CAF50' : '#E0E0E0')
          .onClick(() => {
            this.useSlice = true;
          });
      }
      .layoutWeight(1);

      Column() {
        Text('Lattice模式')
          .fontSize(14)
          .margin({ bottom: 8 });
        Button('使用Lattice')
          .type(ButtonType.Normal)
          .backgroundColor(!this.useSlice ? '#4CAF50' : '#E0E0E0')
          .onClick(() => {
            this.useSlice = false;
          });
      }
      .layoutWeight(1);
    }
    .width('100%')
    .margin({ bottom: 16 });
  }

  @Builder
  buildSizeControls() {
    Column() {
      Text('图片尺寸')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('宽度')
            .fontSize(14)
            .margin({ bottom: 8 });
          Slider({ value: this.imageWidth, min: 100, max: 600, step: 10 })
            .width('100%')
            .trackColor('#E0E0E0')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageWidth = value;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('高度')
            .fontSize(14)
            .margin({ bottom: 8 });
          Slider({ value: this.imageHeight, min: 100, max: 600, step: 10 })
            .width('100%')
            .trackColor('#E0E0E0')
            .selectedColor('#4CAF50')
            .onChange((value: number) => {
              this.imageHeight = value;
            });
        }
        .layoutWeight(1);
      }
      .width('100%');

      Row() {
        Button('200x200')
          .type(ButtonType.Normal)
          .onClick(() => {
            this.resizeImage(200, 200);
          });

        Button('300x300')
          .type(ButtonType.Normal)
          .margin({ left: 8 })
          .onClick(() => {
            this.resizeImage(300, 300);
          });

        Button('400x400')
          .type(ButtonType.Normal)
          .margin({ left: 8 })
          .onClick(() => {
            this.resizeImage(400, 400);
          });

        Button('500x500')
          .type(ButtonType.Normal)
          .margin({ left: 8 })
          .onClick(() => {
            this.resizeImage(500, 500);
          });
      }
      .width('100%')
      .margin({ top: 12 });
    }
    .width('100%')
    .margin({ bottom: 16 });
  }

  @Builder
  buildPresetSelector() {
    Column() {
      Text(this.useSlice ? 'Slice预设' : 'Lattice预设')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      if (this.useSlice) {
        Grid() {
          ForEach(this.slicePresets, (preset: ResizableConfig) => {
            GridItem() {
              Column() {
                Text(preset.name)
                  .fontSize(12)
                  .margin({ bottom: 4 });
                Text(preset.description)
                  .fontSize(10)
                  .fontColor('#999999')
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis });
              }
              .width('100%')
              .padding(10)
              .backgroundColor(
                this.resizableConfig.name === preset.name ? '#4CAF50' : '#F5F5F5'
              )
              .borderRadius(6)
              .onClick(() => {
                this.selectSlicePreset(preset);
              });
            }
          }, (preset: ResizableConfig) => preset.name);
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(8)
        .columnsGap(8)
        .width('100%');
      } else {
        Grid() {
          ForEach(this.latticePresets, (preset: LatticeConfig) => {
            GridItem() {
              Column() {
                Text(preset.name)
                  .fontSize(12)
                  .margin({ bottom: 4 });
                Text(preset.description)
                  .fontSize(10)
                  .fontColor('#999999')
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis });
              }
              .width('100%')
              .padding(10)
              .backgroundColor(
                this.latticeConfig.name === preset.name ? '#4CAF50' : '#F5F5F5'
              )
              .borderRadius(6)
              .onClick(() => {
                this.selectLatticePreset(preset);
              });
            }
          }, (preset: LatticeConfig) => preset.name);
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
  buildGridToggle() {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.showGrid })
        .onChange((isOn: boolean) => {
          this.showGrid = isOn;
        });
      Text('显示网格')
        .fontSize(14)
        .margin({ left: 8 });
    }
    .width('100%');
  }
}
