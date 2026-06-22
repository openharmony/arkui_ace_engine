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

import { curves } from '@kit.ArkUI';

/**
 * ========================================
 * 图片扫光效果示例 (对齐官方示例 13)
 * ========================================
 * 功能说明:
 * 本示例通过 linearGradient 和 animateTo 接口实现图片扫光效果。
 * 扫光效果常用于强调图片内容、加载提示、品牌露出等场景。
 *
 * 涉及的 Image API 和技术:
 * 1. Image(src) - 显示图片
 * 2. Stack 布局 - 图片与扫光层叠加
 * 3. linearGradient - 实现渐变扫光层
 * 4. animateTo - 驱动扫光动画
 * 5. curves.cubicBezierCurve - 自定义动画曲线
 * 6. onComplete - 图片加载完成回调
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 加载骨架屏：图片加载过程中显示扫光占位
 * - 品牌强调：营销页面突出产品图片
 * - 动效装饰：为静态图片增加动态视觉
 * - 引导关注：引导用户关注关键内容
 */

@Entry
@Component
struct ImageScanLightEffectExample {
  // 自定义贝塞尔曲线
  private curve: ICurve = curves.cubicBezierCurve(0.33, 0, 0.67, 1);

  @State scanLineWidth: number = 80;
  @State imageWidth: number = 320;
  @State imageHeight: number = 200;
  @State durationTime: number = 1500;
  @State iterationsTimes: number = -1; // -1 表示无限循环
  @State opacityValue: number = 0.6;
  @State linePositionX: number = -80;
  @State isPlaying: boolean = true;
  @State showOriginal: boolean = true;
  @State scanVisible: boolean = true;
  @State imageLoaded: boolean = false;
  @State cycleCount: number = 0;

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('图片扫光效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 13 · linearGradient + animateTo')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 主预览区
        Column({ space: 12 }) {
          Text('扫光效果预览')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Stack() {
            // 背景层（加载前的占位色）
            Column()
              .width(this.imageWidth)
              .height(this.imageHeight)
              .backgroundColor('#E1E4E9')
              .borderRadius(12)

            // 图片层
            if (this.showOriginal) {
              Image($r('app.media.startIcon'))
                .width(this.imageWidth)
                .height(this.imageHeight)
                .objectFit(ImageFit.Cover)
                .borderRadius(12)
                .onComplete(() => {
                  this.imageLoaded = true;
                })
            }

            // 扫光层（渐变条）
            if (this.scanVisible) {
              Row()
                .width(this.scanLineWidth)
                .height(this.imageHeight)
                .position({ x: this.linePositionX, y: 0 })
                .linearGradient({
                  direction: GradientDirection.Right,
                  repeating: false,
                  colors: [
                    [0xE1E4E9, 0],
                    [0xFFFFFF, 0.5],
                    [0xE1E4E9, 1]
                  ]
                })
                .opacity(this.opacityValue)
                .borderRadius(12)
            }
          }
          .width(this.imageWidth)
          .height(this.imageHeight)
          .clip(true)
          .borderRadius(12)
          .border({ width: 2, color: '#E0E0E0' })
          .shadow({ radius: 12, color: '#1A000000', offsetX: 0, offsetY: 4 })

          // 状态指示
          Row({ space: 8 }) {
            Circle({ width: 8, height: 8 })
              .fill(this.isPlaying ? '#32CD32' : '#AAAAAA')
            Text(this.isPlaying ? '运行中' : '已暂停')
              .fontSize(11)
              .fontColor(this.isPlaying ? '#32CD32' : '#AAAAAA')
            Text(`· 已循环 ${this.cycleCount} 次`)
              .fontSize(11)
              .fontColor(Color.Gray)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)
        .alignItems(HorizontalAlign.Center)

        // 控制按钮
        Column({ space: 10 }) {
          Text('动画控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 10 }) {
            Button(this.isPlaying ? '暂停' : '播放')
              .fontSize(13)
              .backgroundColor(this.isPlaying ? '#FF6347' : '#32CD32')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.togglePlay();
              })

            Button('重置位置')
              .fontSize(13)
              .backgroundColor('#888888')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.resetPosition();
              })

            Button('手动扫一次')
              .fontSize(13)
              .backgroundColor('#007DFF')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.scanOnce();
              })
          }
          .width('100%')

          Row({ space: 12 }) {
            Row({ space: 6 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.scanVisible })
                .onChange((on: boolean) => {
                  this.scanVisible = on;
                })
              Text('显示扫光层')
                .fontSize(11)
                .fontColor(Color.Black)
            }

            Row({ space: 6 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.showOriginal })
                .onChange((on: boolean) => {
                  this.showOriginal = on;
                })
              Text('显示原图')
                .fontSize(11)
                .fontColor(Color.Black)
            }
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 参数调节
        Column({ space: 12 }) {
          Text('扫光参数调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.ParamSlider('扫光宽度', this.scanLineWidth, 40, 200, (v: number) => {
            this.scanLineWidth = v;
          })
          this.ParamSlider('动画时长(ms)', this.durationTime, 500, 5000, (v: number) => {
            this.durationTime = v;
          })
          this.ParamSlider('透明度', Math.round(this.opacityValue * 100), 10, 100, (v: number) => {
            this.opacityValue = v / 100;
          })

          Row({ space: 8 }) {
            Text('循环次数')
              .fontSize(11)
              .width(70)
            Row({ space: 6 }) {
              ForEach(
                [
                  { name: '单次', value: 1 },
                  { name: '3次', value: 3 },
                  { name: '无限', value: -1 }
                ],
                (opt: IterOpt) => {
                  Button(opt.name)
                    .fontSize(10)
                    .backgroundColor(this.iterationsTimes === opt.value ? '#007DFF' : '#E0E0E0')
                    .fontColor(this.iterationsTimes === opt.value ? Color.White : Color.Black)
                    .height(28)
                    .onClick(() => {
                      this.iterationsTimes = opt.value;
                      if (this.isPlaying) {
                        this.startAnimation();
                      }
                    })
                },
                (opt: IterOpt) => `${opt.value}`
              )
            }
            .layoutWeight(1)
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 应用场景：卡片
        Column({ space: 10 }) {
          Text('应用场景：营销卡片')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Stack({ alignContent: Alignment.BottomStart }) {
            Image($r('app.media.startIcon'))
              .width('100%')
              .height(120)
              .objectFit(ImageFit.Cover)
              .borderRadius(12)

            // 文字层
            Column({ space: 4 }) {
              Text('限时特惠')
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.White)
              Text('点击查看详情')
                .fontSize(11)
                .fontColor('#EEEEEE')
            }
            .padding(12)
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
          .height(120)
          .borderRadius(12)
          .clip(true)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // 实现原理
        Column({ space: 8 }) {
          Text('实现原理')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem('Stack 布局', '图片层与扫光层叠加，使用 clip(true) 裁剪超出区域')
          this.DocItem('linearGradient', '创建左中右三段渐变实现扫光条')
          this.DocItem('animateTo', '驱动 position.x 从负宽到图片宽，形成扫过效果')
          this.DocItem('cubicBezierCurve', '自定义贝塞尔曲线，让动画更自然')
          this.DocItem('iterations: -1', '设置为 -1 时无限循环播放')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        Text('提示：扫光效果常用于加载占位、品牌露出、营销活动等场景')
          .fontSize(11)
          .fontColor(Color.Gray)
          .margin({ top: 4, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 16, right: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
    .onAppear(() => {
      this.startAnimation();
    })
  }

  /**
   * 启动扫光动画
   */
  private startAnimation(): void {
    if (!this.isPlaying) {
      return;
    }
    this.linePositionX = -this.scanLineWidth;
    this.getUIContext()?.animateTo({
      duration: this.durationTime,
      curve: this.curve,
      tempo: 1,
      iterations: this.iterationsTimes,
      delay: 0
    }, () => {
      this.linePositionX = this.imageWidth;
    });
    this.cycleCount++;
  }

  /**
   * 切换播放/暂停
   */
  private togglePlay(): void {
    this.isPlaying = !this.isPlaying;
    if (this.isPlaying) {
      this.startAnimation();
    } else {
      this.getUIContext()?.animateTo({
        duration: 0,
        curve: curves.linearCurve(),
        iterations: 1,
        delay: 0
      }, () => {
        this.linePositionX = -this.scanLineWidth;
      });
    }
  }

  /**
   * 手动扫一次
   */
  private scanOnce(): void {
    const prevIterations: number = this.iterationsTimes;
    this.iterationsTimes = 1;
    this.startAnimation();
    setTimeout(() => {
      this.iterationsTimes = prevIterations;
    }, this.durationTime + 100);
  }

  /**
   * 重置位置
   */
  private resetPosition(): void {
    this.linePositionX = -this.scanLineWidth;
  }

  @Builder
  ParamSlider(label: string, value: number, min: number, max: number, onChange: (v: number) => void): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .width(90)
      Slider(value: value, min: min, max: max, step: 10)
        .layoutWeight(1)
        .onChange((v: number) => {
          onChange(v);
          if (this.isPlaying) {
            this.startAnimation();
          }
        })
      Text(`${value}`)
        .fontSize(11)
        .width(50)
    }
    .width('100%')
  }

  @Builder
  DocItem(api: string, desc: string): void {
    Row({ space: 8 }) {
      Text(api)
        .fontSize(11)
        .fontColor('#007DFF')
        .fontFamily('monospace')
        .width('35%')
      Text(desc)
        .fontSize(11)
        .fontColor(Color.Gray)
        .layoutWeight(1)
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }
}

interface IterOpt {
  name: string;
  value: number;
}
