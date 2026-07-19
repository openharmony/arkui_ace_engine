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
 * ========================================
 * 业务场景：图像效果属性游乐场
 * ========================================
 * 功能说明:
 * 本示例系统演示 ArkUI 通用「图像效果」属性（ts-universal-attributes-image-effect），
 * 通过滑块实时调整各项参数，直观对比不同效果对图片的影响，并支持效果组合与预设。
 *
 * 涉及的图像效果属性:
 * 1. brightness - 亮度（0~2，1 为原图）
 * 2. saturate - 饱和度（0~2，1 为原图）
 * 3. contrast - 对比度（0~10，1 为原图）
 * 4. grayscale - 灰度（0~1，0 为原图）
 * 5. invert - 反色（0~1，0 为原图）
 * 6. sepia - 怀旧（0~1，0 为原图）
 * 7. hueRotate - 色相旋转（0~360 度）
 * 8. blur - 内容模糊（0~50 半径）
 * 9. shadow - 阴影（radius/offsetX/offsetY/color）
 * 10. colorFilter - 4x5 颜色矩阵（进阶）
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 图片编辑器：滤镜、调色
 * - 社交应用：头像美化、照片特效
 * - 电商应用：商品图氛围渲染
 * - 设计工具：实时效果预览
 */

interface EffectPreset {
  name: string;
  brightness: number;
  saturate: number;
  contrast: number;
  grayscale: number;
  invert: number;
  sepia: number;
  hueRotate: number;
  blurRadius: number;
}

interface SourceItem {
  res: Resource;
}

@Entry
@Component
struct ImageEffectPlaygroundExample {
  @State brightness: number = 1.0;
  @State saturate: number = 1.0;
  @State contrast: number = 1.0;
  @State grayscale: number = 0;
  @State invert: number = 0;
  @State sepia: number = 0;
  @State hueRotate: number = 0;
  @State blurRadius: number = 0;
  @State shadowOn: boolean = false;
  @State colorFilterOn: boolean = false;
  @State activePreset: string = '原图';
  @State sourceRes: Resource = $r('app.media.svg');

  private sources: SourceItem[] = [
    { res: $r('app.media.svg') },
    { res: $r('app.media.icon') },
    { res: $r('app.media.heart') },
    { res: $r('app.media.star') }
  ];

  private presets: EffectPreset[] = [
    { name: '原图', brightness: 1, saturate: 1, contrast: 1, grayscale: 0, invert: 0, sepia: 0, hueRotate: 0, blurRadius: 0 },
    { name: '清新', brightness: 1.15, saturate: 1.3, contrast: 1.1, grayscale: 0, invert: 0, sepia: 0, hueRotate: 0, blurRadius: 0 },
    { name: '复古', brightness: 0.95, saturate: 0.7, contrast: 1.1, grayscale: 0.2, invert: 0, sepia: 0.6, hueRotate: 0, blurRadius: 0 },
    { name: '黑白', brightness: 1.05, saturate: 0, contrast: 1.2, grayscale: 1, invert: 0, sepia: 0, hueRotate: 0, blurRadius: 0 },
    { name: '冷蓝', brightness: 0.95, saturate: 1.2, contrast: 1.05, grayscale: 0, invert: 0, sepia: 0, hueRotate: 200, blurRadius: 0 },
    { name: '暖橙', brightness: 1.1, saturate: 1.4, contrast: 1.05, grayscale: 0, invert: 0, sepia: 0.3, hueRotate: 20, blurRadius: 0 },
    { name: '梦幻', brightness: 1.2, saturate: 1.5, contrast: 0.9, grayscale: 0, invert: 0, sepia: 0.1, hueRotate: 280, blurRadius: 2 },
    { name: '底片', brightness: 1, saturate: 1, contrast: 1, grayscale: 0, invert: 1, sepia: 0, hueRotate: 0, blurRadius: 0 }
  ];

  /**
   * 应用预设
   */
  private applyPreset(preset: EffectPreset): void {
    this.activePreset = preset.name;
    this.brightness = preset.brightness;
    this.saturate = preset.saturate;
    this.contrast = preset.contrast;
    this.grayscale = preset.grayscale;
    this.invert = preset.invert;
    this.sepia = preset.sepia;
    this.hueRotate = preset.hueRotate;
    this.blurRadius = preset.blurRadius;
  }

  /**
   * 重置所有效果
   */
  private resetAll(): void {
    this.applyPreset(this.presets[0]);
    this.shadowOn = false;
    this.colorFilterOn = false;
  }

  /**
   * 随机生成一组参数
   */
  private randomize(): void {
    this.activePreset = '自定义';
    this.brightness = Math.round((0.6 + Math.random() * 1.2) * 100) / 100;
    this.saturate = Math.round((0 + Math.random() * 2) * 100) / 100;
    this.contrast = Math.round((0.6 + Math.random() * 1.2) * 100) / 100;
    this.grayscale = Math.round(Math.random() * 100) / 100;
    this.invert = Math.random() > 0.7 ? 1 : 0;
    this.sepia = Math.round(Math.random() * 80) / 100;
    this.hueRotate = Math.floor(Math.random() * 360);
    this.blurRadius = Math.random() > 0.7 ? Math.floor(Math.random() * 8) : 0;
  }

  /**
   * 构建 4x5 颜色矩阵（基于当前参数合成）
   */
  private buildColorFilter(): number[] {
    const scale = 1 + (this.contrast - 1) * 0.5;
    return [
      scale, 0, 0, 0, 0,
      0, scale, 0, 0, 0,
      0, 0, scale, 0, 0,
      0, 0, 0, 1, 0
    ];
  }

  build(): void {
    Column({ space: 0 }) {
      this.TitleBar()
      Scroll() {
        Column({ space: 14 }) {
          this.PreviewCard()
          this.SourceSelectCard()
          this.PresetCard()
          this.SliderCard()
          this.ExtraEffectCard()
          this.ActionCard()
        }
        .width('100%')
        .padding(12)
      }
      .layoutWeight(1)
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F2F3F5')
  }

  @Builder
  TitleBar(): void {
    Row({ space: 8 }) {
      Text('图像效果属性游乐场')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Black)
        .layoutWeight(1)
      Text(this.activePreset)
        .fontSize(12)
        .fontColor('#007DFF')
        .backgroundColor('#E3F2FD')
        .borderRadius(10)
        .padding({ left: 10, right: 10, top: 4, bottom: 4 })
    }
    .width('100%')
    .height(52)
    .padding({ left: 16, right: 16 })
    .backgroundColor('#FFFFFF')
  }

  @Builder
  PreviewCard(): void {
    Column({ space: 10 }) {
      Text('实时预览')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 20 }) {
        Column({ space: 6 }) {
          Image(this.sourceRes)
            .width(130)
            .height(130)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .border({ width: 1, color: '#E0E0E0' })
          Text('原图')
            .fontSize(11)
            .fontColor(Color.Gray)
        }

        Column({ space: 6 }) {
          Image(this.sourceRes)
            .width(130)
            .height(130)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .brightness(this.brightness)
            .saturate(this.saturate)
            .contrast(this.contrast)
            .grayscale(this.grayscale)
            .invert(this.invert)
            .sepia(this.sepia)
            .hueRotate(this.hueRotate)
            .blur(this.blurRadius)
            .colorFilter(this.colorFilterOn ? this.buildColorFilter() : [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0])
            .shadow(this.shadowOn ? { radius: 18, offsetX: 4, offsetY: 6, color: '#66000000' } : { radius: 0, color: '#00000000' })
            .border({ width: 1, color: '#E0E0E0' })
          Text('效果叠加')
            .fontSize(11)
            .fontColor('#007DFF')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  SourceSelectCard(): void {
    Column({ space: 10 }) {
      Text('图片源')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 10 }) {
        ForEach(
          this.sources,
          (item: SourceItem) => {
            Image(item.res)
              .width(52)
              .height(52)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
              .border({
                width: this.sourceRes === item.res ? 2 : 1,
                color: this.sourceRes === item.res ? '#007DFF' : '#E0E0E0'
              })
              .onClick(() => {
                this.sourceRes = item.res;
              })
          },
          (item: SourceItem) => `${item.res}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#F3E5F5')
    .borderRadius(12)
  }

  @Builder
  PresetCard(): void {
    Column({ space: 10 }) {
      Text('效果预设')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(
          this.presets,
          (preset: EffectPreset) => {
            Button(preset.name)
              .fontSize(12)
              .height(32)
              .margin({ right: 8, bottom: 8 })
              .backgroundColor(this.activePreset === preset.name ? '#007DFF' : '#EDEDED')
              .fontColor(this.activePreset === preset.name ? Color.White : Color.Black)
              .onClick(() => {
                this.applyPreset(preset);
              })
          },
          (preset: EffectPreset) => preset.name
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF3E0')
    .borderRadius(12)
  }

  @Builder
  SliderCard(): void {
    Column({ space: 12 }) {
      Text('参数微调')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      this.SliderRow('brightness 亮度', this.brightness, 0, 2, (v: number) => {
        this.brightness = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('saturate 饱和度', this.saturate, 0, 2, (v: number) => {
        this.saturate = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('contrast 对比度', this.contrast, 0, 3, (v: number) => {
        this.contrast = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('grayscale 灰度', this.grayscale, 0, 1, (v: number) => {
        this.grayscale = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('invert 反色', this.invert, 0, 1, (v: number) => {
        this.invert = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('sepia 怀旧', this.sepia, 0, 1, (v: number) => {
        this.sepia = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('hueRotate 色相', this.hueRotate, 0, 360, (v: number) => {
        this.hueRotate = v;
        this.activePreset = '自定义';
      })
      this.SliderRow('blur 模糊半径', this.blurRadius, 0, 30, (v: number) => {
        this.blurRadius = v;
        this.activePreset = '自定义';
      })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  SliderRow(label: string, value: number, min: number, max: number, onChange: (v: number) => void): void {
    Column({ space: 4 }) {
      Row({ space: 8 }) {
        Text(label)
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
        Text(value.toFixed(2))
          .fontSize(12)
          .fontColor('#007DFF')
          .width(50)
          .textAlign(TextAlign.End)
      }
      .width('100%')

      Slider({
        value: value,
        min: min,
        max: max,
        step: max <= 1 ? 0.01 : (max <= 3 ? 0.05 : 1)
      })
        .width('100%')
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((v: number) => {
          onChange(v);
        })
    }
    .width('100%')
  }

  @Builder
  ExtraEffectCard(): void {
    Column({ space: 10 }) {
      Text('附加效果')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.shadowOn })
          .onChange((on: boolean) => {
            this.shadowOn = on;
          })
        Text('shadow 阴影')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.colorFilterOn })
          .onChange((on: boolean) => {
            this.colorFilterOn = on;
          })
        Text('colorFilter 矩阵（基于对比度）')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Text('说明：colorFilter 接收 4×5 颜色矩阵，可实现更精细的色调映射，与上述效果可叠加使用。')
        .fontSize(10)
        .fontColor(Color.Gray)
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E0F7FA')
    .borderRadius(12)
  }

  @Builder
  ActionCard(): void {
    Row({ space: 12 }) {
      Button('重置')
        .fontSize(13)
        .layoutWeight(1)
        .height(40)
        .backgroundColor('#EDEDED')
        .fontColor(Color.Black)
        .onClick(() => {
          this.resetAll();
        })

      Button('随机效果')
        .fontSize(13)
        .layoutWeight(1)
        .height(40)
        .backgroundColor('#007DFF')
        .fontColor(Color.White)
        .onClick(() => {
          this.randomize();
        })
    }
    .width('100%')
  }
}
