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

/**
 * ========================================
 * 测试功能说明
 * ========================================
 * 本示例测试 Image 组件的圆角属性设置
 *
 * 涉及的Image API:
 * 1. borderRadius属性 - 设置圆角半径
 * 2. 通用属性 - border/borderRadius - 边框和圆角
 * 3. 通用属性 - shadow - 阴影效果
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "圆角 ImageRoundedCorners" 页面
 * 2. 调整"圆角大小"滑块，观察图片圆角变化
 *   - 值为0时为直角，值越大圆角越明显
 * 3. 点击"应用圆形"按钮，查看圆形效果
 * 4. 观察阴影效果如何增强圆角立体感
 *
 * 预期结果:
 * - 圆角随滑块值实时变化
 * - 圆形按钮图片变为正圆形
 * - 阴影增强了图片的层次感
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. borderRadius属性:
 *    - 接收 number 或 BorderRadiuses
 *    - borderRadius: number - 四个圆角统一设置
 *    - borderRadius: {topLeft, topRight, bottomLeft, bottomRight} - 分别设置
 *
 * 2. 圆角值的建议:
 *    - 小圆角: 5-10px - 柔和风格
 *    - 中圆角: 15-20px - 常见应用风格
 *    - 大圆角: 25-35px - 明显圆润效果
 *    - 完全圆角: 50% (正圆)
 *
 * 3. border vs borderRadius:
 *    - border 描述边框样式
 *    - borderRadius 控制圆角
 *    - 两者可以组合使用
 */
@Entry
@Component
struct ImageRoundedCornersExample {
  @State borderRadius: number = 20;
  @State showShadow: boolean = true;
  @State presetApplied: boolean = false;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('圆角效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 圆角预览
        Column({ space: 15 }) {
          Text('圆角预览 - 半径: ' + this.borderRadius + 'px')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            Image($r('app.media.app_icon'))
              .width(250)
              .height(250)
              .objectFit(ImageFit.Cover)
              .borderRadius(this.borderRadius)
              .shadow(this.showShadow ? {
                radius: 15,
                color: '#40000000',
                offsetX: 0,
                offsetY: 8
              } : {})
          }
          .width(270)
          .height(270)
          .backgroundColor('#F8F8FF')
          .borderRadius(20)
          .shadow({ radius: 10, color: '#20000000' })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F0F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 圆角大小控制
        Column({ space: 10 }) {
          Text('圆角大小: ' + this.borderRadius + 'px')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.borderRadius,
            min: 0,
            max: 125,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadius = value;
              this.presetApplied = false;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 预设按钮
        Column({ space: 15 }) {
          Text('圆角预设:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            Button('直角')
              .onClick(() => {
                this.borderRadius = 0;
                this.presetApplied = false;
              })

            Button('小圆角')
              .onClick(() => {
                this.borderRadius = 10;
                this.presetApplied = false;
              })

            Button('中圆角')
              .onClick(() => {
                this.borderRadius = 20;
                this.presetApplied = false;
              })

            Button('大圆角')
              .onClick(() => {
                this.borderRadius = 35;
                this.presetApplied = false;
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)

          Button('应用圆形')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.borderRadius = 125;
              this.presetApplied = true;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFF8DC')
        .borderRadius(10)

        // 阴影控制
        Row({ space: 20 }) {
          Text('显示阴影:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Toggle({ type: ToggleType.Switch, isOn: this.showShadow })
            .onChange((value: boolean) => {
              this.showShadow = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // API说明
        Column({ space: 10 }) {
          Text('测试的Image API:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. borderRadius - 设置圆角半径')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('2. shadow - 添加阴影增强立体感')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('3. 圆角半径建议:')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('   - 0-10px: 直角/微圆角')
            .fontSize(12)
            .fontColor(Color.Gray)

          Text('   - 15-25px: 常见应用风格')
            .fontSize(12)
            .fontColor(Color.Gray)

          Text('   - 50%: 完全圆形')
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }
}
