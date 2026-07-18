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
 * 业务场景：图片前后对比滑块
 * ========================================
 * 功能说明:
 * 本示例实现一个可拖拽的「前后对比（Before / After）」滑块，
 * 通过 Stack 叠加两层 Image，并用 clip + 宽度约束裁剪上层图片，
 * 拖动分割线即可直观对比同一张图的不同效果，或两张不同图片。
 *
 * 涉及的 Image / 通用 API:
 * 1. Image(src) - 双层图片叠加（下层 After，上层 Before 裁剪显示）
 * 2. objectFit(ImageFit) - 两层图片保持一致填充模式以保证对齐
 * 3. 通用图像效果 - brightness / contrast / grayscale / invert / sepia / saturate
 * 4. clip(boolean) - 裁剪超出容器的内容，配合宽度约束实现分割
 * 5. Stack({ alignContent: Alignment.Start }) - 保证上层图片左对齐
 * 6. TouchEvent (localX) - 拖动 / 点击移动分割线
 * 7. border / borderRadius / shadow - 视觉样式
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 修图应用：对比滤镜/调色前后效果
 * - 医疗影像：对比不同时期影像
 * - 商品展示：对比原图与精修图
 * - 地图/卫星：对比白天与夜景、不同图层
 */

interface CompareEffect {
  name: string;
  desc: string;
  brightness: number;
  contrast: number;
  saturate: number;
  grayscale: number;
  invert: number;
  sepia: number;
}

interface SourcePair {
  before: Resource;
  after: Resource;
  label: string;
}

interface FitOptionItem {
  key: ImageFit;
  name: string;
}

@Entry
@Component
struct ImageCompareSliderExample {
  @State dividerRatio: number = 0.5;
  @State containerWidth: number = 320;
  @State containerHeight: number = 240;
  @State effectIndex: number = 1;
  @State sourcePairIndex: number = 0;
  @State useSameSource: boolean = true;
  @State fitMode: ImageFit = ImageFit.Cover;
  @State dragging: boolean = false;

  private effects: CompareEffect[] = [
    { name: '原图', desc: '无效果', brightness: 1, contrast: 1, saturate: 1, grayscale: 0, invert: 0, sepia: 0 },
    { name: '复古', desc: 'sepia + 降饱和', brightness: 1, contrast: 1.1, saturate: 0.7, grayscale: 0, invert: 0, sepia: 0.7 },
    { name: '黑白', desc: 'grayscale', brightness: 1.05, contrast: 1.2, saturate: 1, grayscale: 1, invert: 0, sepia: 0 },
    { name: '反色', desc: 'invert', brightness: 1, contrast: 1, saturate: 1, grayscale: 0, invert: 1, sepia: 0 },
    { name: '高对比', desc: 'contrast + saturate', brightness: 1.05, contrast: 1.6, saturate: 1.5, grayscale: 0, invert: 0, sepia: 0 },
    { name: '清新', desc: 'brightness + saturate', brightness: 1.2, contrast: 1.05, saturate: 1.5, grayscale: 0, invert: 0, sepia: 0 },
    { name: '暗调', desc: '降亮度', brightness: 0.65, contrast: 1.2, saturate: 0.9, grayscale: 0, invert: 0, sepia: 0 }
  ];

  private sourcePairs: SourcePair[] = [
    { before: $r('app.media.svg'), after: $r('app.media.icon'), label: 'svg / icon' },
    { before: $r('app.media.heart'), after: $r('app.media.star'), label: 'heart / star' },
    { before: $r('app.media.svg'), after: $r('app.media.heart'), label: 'svg / heart' }
  ];

  private fitModes: Array<FitOptionItem> = [
    { key: ImageFit.Cover, name: 'Cover' },
    { key: ImageFit.Contain, name: 'Contain' },
    { key: ImageFit.Fill, name: 'Fill' },
    { key: ImageFit.None, name: 'None' },
    { key: ImageFit.ScaleDown, name: 'ScaleDown' }
  ];

  /**
   * 根据触摸位置更新分割线比例
   */
  private updateRatioByTouch(localX: number): void {
    if (this.containerWidth <= 0) {
      return;
    }
    const ratio = localX / this.containerWidth;
    this.dividerRatio = Math.max(0.02, Math.min(0.98, ratio));
  }

  /**
   * 取当前对比效果
   */
  private currentEffect(): CompareEffect {
    return this.effects[this.effectIndex];
  }

  build(): void {
    Column({ space: 0 }) {
      this.TitleBar()
      Scroll() {
        Column({ space: 14 }) {
          this.CompareCard()
          this.DividerHintCard()
          this.EffectCard()
          this.SourceCard()
          this.FitCard()
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
      Text('图片前后对比滑块')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Black)
        .layoutWeight(1)
      Text(`${Math.round(this.dividerRatio * 100)} : ${Math.round((1 - this.dividerRatio) * 100)}`)
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

  /**
   * 核心对比区：Stack 叠加两层 Image，上层用 clip 裁剪
   */
  @Builder
  CompareCard(): void {
    Column({ space: 10 }) {
      // 对比容器：宽度自适应父容器，通过 onAreaChange 获取数值用于定位计算
      Stack({ alignContent: Alignment.Center }) {
        // 下层（右侧）：After —— 应用效果（或第二张图）
        Image(this.useSameSource ? this.sourcePairs[this.sourcePairIndex].before
          : this.sourcePairs[this.sourcePairIndex].after)
          .width(this.containerWidth)
          .height(this.containerHeight)
          .objectFit(this.fitMode)
          .backgroundColor('#FAFAFA')

        // 上层（左侧）：Before —— 原图，按 dividerRatio 宽度裁剪
        Stack({ alignContent: Alignment.Start }) {
          Image(this.sourcePairs[this.sourcePairIndex].before)
            .width(this.containerWidth)
            .height(this.containerHeight)
            .objectFit(this.fitMode)
            .backgroundColor(this.useSameSource ? '#FAFAFA' : '#00000000')
            .brightness(this.currentEffect().brightness)
            .contrast(this.currentEffect().contrast)
            .saturate(this.currentEffect().saturate)
            .grayscale(this.currentEffect().grayscale)
            .invert(this.currentEffect().invert)
            .sepia(this.currentEffect().sepia)
        }
        .width(this.dividerRatio * this.containerWidth)
        .height(this.containerHeight)
        .clip(true)

        // 分割线
        Column()
          .width(2)
          .height(this.containerHeight)
          .backgroundColor('#FFFFFF')
          .shadow({ radius: 6, color: '#99000000' })
          .position({ x: this.dividerRatio * this.containerWidth - 1, y: 0 })

        // 拖拽手柄
        Row({ space: 4 }) {
          Text('‹')
            .fontSize(16)
            .fontColor('#FFFFFF')
            .fontWeight(FontWeight.Bold)
          Text('›')
            .fontSize(16)
            .fontColor('#FFFFFF')
            .fontWeight(FontWeight.Bold)
        }
        .width(36)
        .height(36)
        .borderRadius(18)
        .backgroundColor('#007DFF')
        .justifyContent(FlexAlign.Center)
        .alignItems(VerticalAlign.Center)
        .shadow({ radius: 8, color: '#66000000' })
        .position({
          x: this.dividerRatio * this.containerWidth - 18,
          y: this.containerHeight / 2 - 18
        })

        // 左右标签
        Text('Before')
          .fontSize(11)
          .fontColor('#FFFFFF')
          .backgroundColor('#80000000')
          .borderRadius(8)
          .padding({ left: 8, right: 8, top: 3, bottom: 3 })
          .position({ x: 8, y: 8 })
        Text('After')
          .fontSize(11)
          .fontColor('#FFFFFF')
          .backgroundColor('#80000000')
          .borderRadius(8)
          .padding({ left: 8, right: 8, top: 3, bottom: 3 })
          .position({ x: this.containerWidth - 56, y: 8 })

        // 触摸层：置于最顶层，覆盖整个容器，用于拖动 / 点击移动分割线
        Column()
          .width('100%')
          .height('100%')
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down || event.type === TouchType.Move) {
              this.dragging = true;
              if (event.touches.length > 0) {
                this.updateRatioByTouch(event.touches[0].localX);
              }
            } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              this.dragging = false;
            }
          })
      }
      .width('100%')
      .height(this.containerHeight)
      .borderRadius(12)
      .clip(true)
      .border({ width: 1, color: '#E0E0E0' })
      .onAreaChange((_old: Area, newArea: Area) => {
        const w = newArea.width;
        if (w > 0 && Math.abs(w - this.containerWidth) > 1) {
          this.containerWidth = w;
        }
      })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  DividerHintCard(): void {
    Row({ space: 8 }) {
      Text('分割位置')
        .fontSize(12)
        .fontColor(Color.Gray)
        .width(60)
      Slider({
        value: this.dividerRatio * 100,
        min: 2,
        max: 98,
        step: 1
      })
        .layoutWeight(1)
        .trackColor('#E0E0E0')
        .selectedColor('#007DFF')
        .onChange((v: number) => {
          this.dividerRatio = v / 100;
        })
      Text(`${Math.round(this.dividerRatio * 100)}%`)
        .fontSize(12)
        .fontColor('#007DFF')
        .width(44)
        .textAlign(TextAlign.End)
    }
    .width('100%')
    .padding({ left: 12, right: 12, top: 6, bottom: 6 })
  }

  @Builder
  EffectCard(): void {
    Column({ space: 10 }) {
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.useSameSource })
          .onChange((on: boolean) => {
            this.useSameSource = on;
          })
        Text('同一图源 + 效果对比（关闭则对比两张不同图片）')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      if (this.useSameSource) {
        Text('Before 层应用的效果')
          .fontSize(13)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
          .width('100%')

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(
            this.effects,
            (effect: CompareEffect, index: number) => {
              Button(effect.name)
                .fontSize(12)
                .height(32)
                .margin({ right: 8, bottom: 8 })
                .backgroundColor(this.effectIndex === index ? '#007DFF' : '#EDEDED')
                .fontColor(this.effectIndex === index ? Color.White : Color.Black)
                .onClick(() => {
                  this.effectIndex = index;
                })
            },
            (effect: CompareEffect) => effect.name
          )
        }
        .width('100%')

        Text(`当前：${this.currentEffect().name} —— ${this.currentEffect().desc}`)
          .fontSize(10)
          .fontColor(Color.Gray)
          .width('100%')
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF8E1')
    .borderRadius(12)
  }

  @Builder
  SourceCard(): void {
    Column({ space: 10 }) {
      Text('图片源对')
        .fontSize(13)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        ForEach(
          this.sourcePairs,
          (pair: SourcePair, index: number) => {
            Column({ space: 4 }) {
              Row({ space: 4 }) {
                Image(pair.before)
                  .width(36)
                  .height(36)
                  .objectFit(ImageFit.Cover)
                  .borderRadius(6)
                Image(pair.after)
                  .width(36)
                  .height(36)
                  .objectFit(ImageFit.Cover)
                  .borderRadius(6)
              }
              Text(pair.label)
                .fontSize(9)
                .fontColor(Color.Gray)
            }
            .padding(6)
            .borderRadius(8)
            .border({
              width: this.sourcePairIndex === index ? 2 : 1,
              color: this.sourcePairIndex === index ? '#007DFF' : '#E0E0E0'
            })
            .onClick(() => {
              this.sourcePairIndex = index;
            })
          },
          (pair: SourcePair) => pair.label
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
  FitCard(): void {
    Column({ space: 10 }) {
      Text('objectFit 填充模式（两层保持一致以保证对齐）')
        .fontSize(13)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 6 }) {
        ForEach(
          this.fitModes,
          (item: FitOptionItem) => {
            Button(item.name)
              .fontSize(10)
              .height(28)
              .layoutWeight(1)
              .backgroundColor(this.fitMode === item.key ? '#007DFF' : '#EDEDED')
              .fontColor(this.fitMode === item.key ? Color.White : Color.Black)
              .onClick(() => {
                this.fitMode = item.key;
              })
          },
          (item: FitOptionItem) => `${item.key}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E3F2FD')
    .borderRadius(12)
  }

  @Builder
  ActionCard(): void {
    Row({ space: 12 }) {
      Button('居中')
        .fontSize(13)
        .layoutWeight(1)
        .height(38)
        .backgroundColor('#EDEDED')
        .fontColor(Color.Black)
        .onClick(() => {
          this.dividerRatio = 0.5;
        })

      Button('随机效果')
        .fontSize(13)
        .layoutWeight(1)
        .height(38)
        .backgroundColor('#007DFF')
        .fontColor(Color.White)
        .onClick(() => {
          this.useSameSource = true;
          let next = Math.floor(Math.random() * this.effects.length);
          if (next === this.effectIndex) {
            next = (next + 1) % this.effects.length;
          }
          this.effectIndex = next;
        })
    }
    .width('100%')
  }
}
