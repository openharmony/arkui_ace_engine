/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { curves } from '@kit.ArkUI';

@Entry
@ComponentV2
struct IndexTest {
  uiContext: UIContext | undefined = undefined;
  @Local angle: number = 0;
  @Local move_x0: number = 0;

  // 组件即将显示时触发：获取ComponentV2的UI上下文
  aboutToAppear(): void {
    this.uiContext = this.getUIContext();
    if (!this.uiContext) {
      console.warn("no uiContext");
      return;
    }
  }

  build() {
    List() {
      // 列表项1：显示cat01图片，添加颜色滤镜（调整透明度相关）
      ListItem() {
        Image($r('app.media.cat01'))
          .size({ width: 100, height: 100 })
          .colorFilter([0, 0, 0, 0, 255,
            0, 0, 0, 0, 255,
            0, 0, 0, 0, 255,
            0, 0, 0, 0.9, 0]) // RGBA颜色矩阵滤镜
      }

      // 列表项2：显示startIcon图片，应用与项1相同的颜色滤镜
      ListItem() {
        Image($r('app.media.startIcon'))
          .size({ width: 100, height: 100 })
          .colorFilter([0, 0, 0, 0, 255,
            0, 0, 0, 0, 255,
            0, 0, 0, 0, 255,
            0, 0, 0, 0.9, 0])
      }
    }
    .backgroundColor('#ff00ff00')
    .height('100%')
    .rotate({
      y: 1,
      angle: this.angle,
      centerY: '50%', 
      perspective: 50
    })
    .onTouch((event: TouchEvent) => { // 触摸事件：控制旋转与回弹
      if (event.type === TouchType.Down) {
        // 触摸按下：记录初始触摸X坐标
        this.move_x0 = event.touches[0].x
      } else if (event.type === TouchType.Move) {
        // 触摸滑动：执行弹簧曲线动画，计算旋转角度（限制在-35~35度）
        this.uiContext?.animateTo({ curve: curves.springMotion(0.5, 0.85) }, () => {
          this.angle = Math.min(Math.max((event.touches[0].x - this.move_x0) / 5, -35), 35)
        })
      } else {
        // 触摸结束（松手）：动画回弹到初始角度（0度）
        this.uiContext?.animateTo({ curve: curves.springMotion(0.5, 0.85) }, () => {
          this.angle = 0
        })
        let isSub: number = 0
        if (event.touches[0].x - this.move_x0 < -80) { // 向左滑动超80px
        } else if (event.touches[0].x - this.move_x0 > 80) { // 向右滑动超80px
          isSub = 1
        } else { // 滑动距离不足80px
          isSub = 2
        }
      }
    })
  }
}