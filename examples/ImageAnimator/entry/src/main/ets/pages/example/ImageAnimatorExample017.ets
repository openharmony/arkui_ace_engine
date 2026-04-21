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
 * ImageAnimatorExample017 - Resource 类型和 string 类型尺寸专项示例
 * ========================================
 * 
 * 测试功能说明:
 * 本示例测试 ImageAnimator 组件的两种重要特性:
 * 1. Resource 类型图片 (API 9+)
 * 2. string 类型的 width/height/top/left (带单位)
 * 
 * 涉及的 ImageAnimator API:
 * 1. ImageFrameInfo.src - 支持 Resource 类型 (API 9+)
 * 2. ImageFrameInfo.width/height/top/left - 支持 string 类型 (带单位)
 * 3. fixedSize - 必须为 false 才能使用自定义尺寸
 * 
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "Resource 和 string 尺寸" 页面
 * 2. 观察 Resource 类型图片正常播放
 * 3. 观察 string 类型尺寸 (带单位) 的效果
 * 4. 切换不同单位测试效果
 * 
 * 预期结果:
 * - Resource 类型图片正常加载和播放
 * - string 类型尺寸正确解析 (vp, px, % 等单位)
 * - fixedSize 为 false 时自定义尺寸生效
 * 
 * ========================================
 * ImageAnimator API 知识点
 * ========================================
 * 1. Resource 类型 (API 9+):
 *    - 格式：$r('app.media.xxx')
 *    - 优势：资源管理更规范，支持多语言/多分辨率
 *    - 推荐：优先使用 Resource 类型
 * 
 * 2. string 类型尺寸:
 *    - 支持 number: 100 (默认单位 vp)
 *    - 支持 string: "100vp", "50px", "20%"
 *    - 单位：vp (虚拟像素), px (物理像素), % (百分比)
 * 
 * 3. 使用场景:
 *    - Resource: 所有图片资源加载
 *    - string 尺寸：需要精确控制单位时
 * 
 * 4. 注意事项:
 *    - fixedSize 必须为 false 才能使用自定义尺寸
 *    - string 类型必须包含有效单位
 *    - Resource 类型从 API 9 开始支持
 */

@Entry
@Component
struct ImageAnimatorExample017 {
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentIterations: number = 1;
  @State showStringSize: boolean = true;
  @State sizeUnit: string = 'vp';
  @State currentStatus: string = 'Initial';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Resource 类型和 string 尺寸示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildResourceDemo()
        this.buildStringSizeDemo()
        this.buildComparisonDemo()
        this.buildControlPanel()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildDescription() {
    Column({ space: 10 }) {
      Text('API 特性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('Resource 类型 (API 9+)')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('格式：$r("app.media.xxx")')
            .fontSize(12)
            .fontColor(0x999999)
          Text('优势：资源管理更规范')
            .fontSize(12)
            .fontColor(0x999999)
        }
        .padding(15)
        .backgroundColor(0xE3F2FD)
        .borderRadius(10)
        .layoutWeight(1)

        Column({ space: 5 }) {
          Text('string 类型尺寸')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('支持："100vp", "50px", "20%"')
            .fontSize(12)
            .fontColor(0x999999)
          Text('fixedSize: false 时生效')
            .fontSize(12)
            .fontColor(0x999999)
        }
        .padding(15)
        .backgroundColor(0xFFF3E0)
        .borderRadius(10)
        .layoutWeight(1)
      }
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildResourceDemo() {
    Column({ space: 15 }) {
      Text('示例 1: Resource 类型图片')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      ImageAnimator()
        .images([
          {
            // Resource 类型 (API 9+)
            src: $r('app.media.img1')
          },
          {
            src: $r('app.media.img2')
          },
          {
            src: $r('app.media.img3')
          },
          {
            src: $r('app.media.img4')
          }
        ])
        .duration(2000)
        .state(this.animationState)
        .iterations(this.currentIterations)
        .width(300)
        .height(200)
        .onStart(() => {
          this.currentStatus = 'Running';
        })
        .onPause(() => {
          this.currentStatus = 'Paused';
        })
        .onFinish(() => {
          this.currentStatus = 'Finished';
          this.animationState = AnimationStatus.Stopped;
        })

      Text('状态：' + this.currentStatus)
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildStringSizeDemo() {
    Column({ space: 15 }) {
      Text('示例 2: string 类型尺寸 (带单位)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Toggle({ type: ToggleType.Switch, isOn: this.showStringSize })
        .onChange((isOn: boolean) => {
          this.showStringSize = isOn;
        })
        .padding({ bottom: 10 })

      // 使用 string 类型尺寸
      ImageAnimator()
        .images([
          {
            src: $r('app.media.img1'),
            // string 类型，带单位
            width: this.getSizeValue('100vp'),
            height: this.getSizeValue('75vp'),
            top: this.getSizeValue('10vp'),
            left: this.getSizeValue('20vp')
          },
          {
            src: $r('app.media.img2'),
            width: this.getSizeValue('120vp'),
            height: this.getSizeValue('90vp'),
            top: this.getSizeValue('5vp'),
            left: this.getSizeValue('15vp')
          },
          {
            src: $r('app.media.img3'),
            width: this.getSizeValue('140vp'),
            height: this.getSizeValue('105vp'),
            top: this.getSizeValue('0vp'),
            left: this.getSizeValue('10vp')
          },
          {
            src: $r('app.media.img4'),
            width: this.getSizeValue('160vp'),
            height: this.getSizeValue('120vp'),
            top: this.getSizeValue('-5vp'),
            left: this.getSizeValue('5vp')
          }
        ])
        // 重要：fixedSize 必须为 false 才能使用自定义尺寸
        .fixedSize(false)
        .duration(3000)
        .iterations(-1)
        // 组件总尺寸
        .width(340)
        .height(240)
        .backgroundColor(0xF0F0F0)

      Text('提示：fixedSize 必须为 false 才能使用自定义尺寸')
        .fontSize(12)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildComparisonDemo() {
    Column({ space: 15 }) {
      Text('示例 3: 不同单位对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 15 }) {
        // vp 单位
        Column({ space: 10 }) {
          Text('vp 单位')
            .fontSize(14)
            .fontColor(Color.Gray)
          ImageAnimator()
            .images([
              { src: $r('app.media.img1'), width: "80vp", height: "60vp" }
            ])
            .fixedSize(false)
            .duration(1000)
            .width(100)
            .height(80)
            .backgroundColor(0xE3F2FD)
        }
        .padding(10)
        .backgroundColor(0xF5F5F5)
        .borderRadius(10)
        .layoutWeight(1)

        // px 单位
        Column({ space: 10 }) {
          Text('px 单位')
            .fontSize(14)
            .fontColor(Color.Gray)
          ImageAnimator()
            .images([
              { src: $r('app.media.img1'), width: "80px", height: "60px" }
            ])
            .fixedSize(false)
            .duration(1000)
            .width(100)
            .height(80)
            .backgroundColor(0xFFF3E0)
        }
        .padding(10)
        .backgroundColor(0xF5F5F5)
        .borderRadius(10)
        .layoutWeight(1)
      }
      .width('100%')

      Text('vp: 虚拟像素 (推荐) | px: 物理像素')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('开始')
          .fontSize(14)
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.animationState = AnimationStatus.Running;
            this.currentStatus = 'Running';
          })

        Button('暂停')
          .fontSize(14)
          .backgroundColor(Color.Orange)
          .onClick(() => {
            this.animationState = AnimationStatus.Paused;
            this.currentStatus = 'Paused';
          })

        Button('停止')
          .fontSize(14)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.animationState = AnimationStatus.Stopped;
            this.currentStatus = 'Stopped';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Button('1 次')
          .fontSize(14)
          .backgroundColor(this.currentIterations === 1 ? Color.Blue : Color.Gray)
          .onClick(() => {
            this.currentIterations = 1;
          })

        Button('3 次')
          .fontSize(14)
          .backgroundColor(this.currentIterations === 3 ? Color.Blue : Color.Gray)
          .onClick(() => {
            this.currentIterations = 3;
          })

        Button('无限')
          .fontSize(14)
          .backgroundColor(this.currentIterations === -1 ? Color.Blue : Color.Gray)
          .onClick(() => {
            this.currentIterations = -1;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xE8F5E9)
    .borderRadius(15)
  }

  getSizeValue(baseValue: string): string {
    if (!this.showStringSize) {
      return baseValue;
    }
    return baseValue;
  }
}
