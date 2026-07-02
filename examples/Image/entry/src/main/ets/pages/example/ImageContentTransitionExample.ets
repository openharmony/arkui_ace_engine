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
 * 图片淡入淡出切换示例 (对齐官方示例 27 · API 21+)
 * ========================================
 * 功能说明:
 * 本示例演示如何通过 contentTransition 属性实现图片切换时的淡入淡出动画效果。
 * 当 Image 的 src 发生变化时，会触发平滑的过渡动画。
 *
 * 涉及的 Image API:
 * 1. contentTransition(ContentTransitionEffect.OPACITY) - 启用淡入淡出过渡
 * 2. Image(src: Resource) - 切换 src 触发过渡
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 图片轮播：图片切换时平滑过渡
 * - 内容切换：图集浏览、产品图切换
 * - 状态切换：默认图、激活图之间的过渡
 * - 用户交互：点击切换、滑动切换
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. 该属性从 API version 21 开始支持
 * 2. 仅在 src 切换时生效，首次加载不触发过渡
 * 3. SVG 图源切换支持过渡效果
 * 4. 配合 onClick / onTouch 等事件触发 src 切换
 */

@Entry
@Component
struct ImageContentTransitionExample {
  @State currentIndex: number = 0;
  @State autoPlay: boolean = false;
  @State intervalSeconds: number = 2;
  @State transitionEnabled: boolean = true;
  @State lastSwitchTime: string = '尚未切换';
  @State switchCount: number = 0;
  private autoPlayTimer: number = -1;

  // 使用资源管理器内的多张图片演示切换效果
  // 实际项目中可以是任意 Resource / PixelMap / DrawableDescriptor
  private imageList: Array<Resource> = [
    $r('app.media.startIcon'),
    $r('app.media.svg'),
    $r('app.media.icon'),
    $r('app.media.star'),
    $r('app.media.heart')
  ];

  private imageNames: Array<string> = [
    'startIcon', 'svg', 'icon', 'star', 'heart'
  ];

  aboutToDisappear(): void {
    this.stopAutoPlay();
  }

  /**
   * 切换到下一张图片
   */
  private switchToNext(): void {
    this.currentIndex = (this.currentIndex + 1) % this.imageList.length;
    this.switchCount++;
    this.lastSwitchTime = this.formatTime(new Date());
  }

  /**
   * 切换到指定索引的图片
   */
  private switchTo(index: number): void {
    if (index === this.currentIndex) {
      return;
    }
    this.currentIndex = index;
    this.switchCount++;
    this.lastSwitchTime = this.formatTime(new Date());
  }

  /**
   * 开启自动轮播
   */
  private startAutoPlay(): void {
    this.stopAutoPlay();
    this.autoPlay = true;
    this.autoPlayTimer = setInterval(
      () => {
        this.switchToNext();
      },
      this.intervalSeconds * 1000
    );
  }

  /**
   * 停止自动轮播
   */
  private stopAutoPlay(): void {
    if (this.autoPlayTimer !== -1) {
      clearInterval(this.autoPlayTimer);
      this.autoPlayTimer = -1;
    }
    this.autoPlay = false;
  }

  /**
   * 切换自动播放状态
   */
  private toggleAutoPlay(): void {
    if (this.autoPlay) {
      this.stopAutoPlay();
    } else {
      this.startAutoPlay();
    }
  }

  /**
   * 格式化时间
   */
  private formatTime(date: Date): string {
    const hours: string = `${date.getHours()}`.padStart(2, '0');
    const minutes: string = `${date.getMinutes()}`.padStart(2, '0');
    const seconds: string = `${date.getSeconds()}`.padStart(2, '0');
    return `${hours}:${minutes}:${seconds}`;
  }

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('图片淡入淡出切换示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 27 · contentTransition (API 21+)')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 主预览区
        Column({ space: 12 }) {
          Text('图片预览')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Stack({ alignContent: Alignment.Center }) {
            // 使用 contentTransition 实现淡入淡出
            Image(this.imageList[this.currentIndex])
              .width(220)
              .height(220)
              .objectFit(ImageFit.Cover)
              .borderRadius(16)
              .border({ width: 2, color: '#E0E0E0' })
              .shadow({ radius: 16, color: '#1A000000', offsetX: 0, offsetY: 4 })
              .contentTransition(
                this.transitionEnabled ? ContentTransitionEffect.OPACITY : ContentTransitionEffect.IDENTITY
              )
              .onClick(() => {
                this.switchToNext();
              })

            // 索引标签
            Text(`${this.currentIndex + 1} / ${this.imageList.length}`)
              .fontSize(12)
              .fontColor(Color.White)
              .backgroundColor('#80000000')
              .borderRadius(12)
              .padding({ left: 8, right: 8, top: 4, bottom: 4 })
              .position({ x: '70%', y: 12 })
          }
          .width('100%')
          .height(240)

          Text(`当前图片: ${this.imageNames[this.currentIndex]}`)
            .fontSize(13)
            .fontColor(Color.Gray)
            .textAlign(TextAlign.Center)
            .width('100%')

          // 操作提示
          Text('点击图片可手动切换 · 或开启自动轮播')
            .fontSize(11)
            .fontColor(Color.Blue)
            .textAlign(TextAlign.Center)
            .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 控制面板
        Column({ space: 12 }) {
          Text('切换控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          // 过渡开关
          Row({ space: 12 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.transitionEnabled })
              .onChange((on: boolean) => {
                this.transitionEnabled = on;
              })
            Text('启用 contentTransition 过渡效果')
              .fontSize(13)
              .fontColor(Color.Black)
              .layoutWeight(1)
          }
          .width('100%')

          // 轮播间隔
          Row({ space: 8 }) {
            Text('轮播间隔')
              .fontSize(12)
              .width(70)
            Slider(value: this.intervalSeconds, min: 1, max: 5, step: 1)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.intervalSeconds = value;
                if (this.autoPlay) {
                  this.startAutoPlay();
                }
              })
            Text(`${this.intervalSeconds}秒`)
              .fontSize(12)
              .width(40)
          }
          .width('100%')

          // 控制按钮
          Row({ space: 10 }) {
            Button('上一张')
              .fontSize(12)
              .backgroundColor('#007DFF')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.currentIndex =
                  (this.currentIndex - 1 + this.imageList.length) % this.imageList.length;
                this.switchCount++;
                this.lastSwitchTime = this.formatTime(new Date());
              })

            Button(this.autoPlay ? '暂停' : '自动播放')
              .fontSize(12)
              .backgroundColor(this.autoPlay ? '#FF6347' : '#32CD32')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.toggleAutoPlay();
              })

            Button('下一张')
              .fontSize(12)
              .backgroundColor('#007DFF')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(36)
              .onClick(() => {
                this.switchToNext();
              })
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 缩略图列表
        Column({ space: 12 }) {
          Text('图片列表 (点击切换)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Grid() {
            ForEach(
              this.imageList,
              (image: Resource, index: number) => {
                GridItem() {
                  Column({ space: 4 }) {
                    Stack({ alignContent: Alignment.BottomEnd }) {
                      Image(image)
                        .width(60)
                        .height(60)
                        .objectFit(ImageFit.Cover)
                        .borderRadius(8)
                        .border({
                          width: this.currentIndex === index ? 3 : 1,
                          color: this.currentIndex === index ? '#007DFF' : '#E0E0E0'
                        })
                        .contentTransition(ContentTransitionEffect.OPACITY)
                        .onClick(() => {
                          this.switchTo(index);
                        })

                      // 当前索引标记
                      if (this.currentIndex === index) {
                        Text('●')
                          .fontSize(12)
                          .fontColor('#007DFF')
                          .backgroundColor(Color.White)
                          .borderRadius(8)
                          .width(16)
                          .height(16)
                          .textAlign(TextAlign.Center)
                      }
                    }
                    .width(60)
                    .height(60)

                    Text(this.imageNames[index])
                      .fontSize(10)
                      .fontColor(this.currentIndex === index ? '#007DFF' : Color.Gray)
                  }
                  .width('100%')
                  .justifyContent(FlexAlign.Center)
                }
              },
              (image: Resource, index: number) => `${this.imageNames[index]}_${index}`
            )
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .rowsGap(12)
          .columnsGap(8)
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 状态信息
        Column({ space: 8 }) {
          Text('运行状态')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.StatusRow('过渡效果', this.transitionEnabled ? '已启用 (OPACITY)' : '已禁用 (IDENTITY)')
          this.StatusRow('自动轮播', this.autoPlay ? `运行中 · ${this.intervalSeconds}秒/张` : '已停止')
          this.StatusRow('切换次数', `${this.switchCount}`)
          this.StatusRow('上次切换', this.lastSwitchTime)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // API 说明
        Column({ space: 8 }) {
          Text('API 说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem(
            'ContentTransitionEffect.OPACITY',
            '淡入淡出过渡，旧图淡出同时新图淡入'
          )
          this.DocItem(
            'ContentTransitionEffect.IDENTITY',
            '无过渡效果，立即切换'
          )
          this.DocItem(
            '.contentTransition(effect)',
            '绑定过渡效果到 Image 组件'
          )
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        Text('提示：仅 src 变化时触发过渡；首次加载不会触发动画')
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
  }

  @Builder
  StatusRow(label: string, value: string): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(12)
        .fontColor(Color.Gray)
        .width(80)
      Text(value)
        .fontSize(12)
        .fontColor(Color.Black)
        .layoutWeight(1)
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }

  @Builder
  DocItem(api: string, desc: string): void {
    Row({ space: 8 }) {
      Text(api)
        .fontSize(11)
        .fontColor('#007DFF')
        .fontFamily('monospace')
        .width('45%')
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
