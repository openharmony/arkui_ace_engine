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

/*
 * 测试用例用途:
 * 1、从dump验证通过ets和attributeModifier设置是否生效
 * 2、通过trace观察ets设置为节点剔除true之后是否生效
 */
// 后续： visualEffect
// excludeFromRenderGroup不配合renderGroup使用无影响
// 动画场景
import hiTraceMeter from '@ohos.hiTraceMeter';
import { AttributeUpdater } from '@ohos.arkui.modifier'
@Entry
@Component
struct Page1 {
  @State message: string = 'Hello World';
  @State value1: boolean | undefined = false;
  @State myUpdater: AttributeUpdater<TextAttribute> = new AttributeUpdater<TextAttribute>();

  build() {
    Column() {
      Stack() {
        Image($r('app.media.startIcon'))
          .width(100)
          .height(100)
          .opacity(0.8)
        Text("layer")
          .width(100)
          .height(50)
        Column()
          .width(100)
          .height(100)
          .backgroundColor("#30ffffff") // 带透明的白色
      } // 没有renderGroup和excludeFromRenderGroup，对照组

      Column() {
        Stack() {
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .opacity(0.8)
          Text("layer")
            .width(100)
            .height(50)
            .excludeFromRenderGroup(this.value1)
            .id("A")
          Column()
            .width(100)
            .height(100)
            .backgroundColor("#30ffffff") // 带透明的白色
        }
      }.renderGroup(true)
      .margin({ top: 30 }) // 有renderGroup和excludeFromRenderGroup

      Column() {
        Stack() {
          Image($r('app.media.startIcon'))
            .width(100)
            .height(100)
            .opacity(0.8)
          Text("layer")
            .width(100)
            .height(50)
            .id("B")
            .attributeModifier(this.myUpdater)
          Column()
            .width(100)
            .height(100)
            .backgroundColor("#30ffffff") // 带透明的白色
        }
      }.renderGroup(true)
      .margin({ top: 30 }) // 有renderGroup和excludeFromRenderGroup

      Text("value:" + String(this.value1))
      Button("true")
        .onClick(() => {
          hiTraceMeter.startTrace("true", 0);
          this.value1 = true;
          this.myUpdater.attribute?.excludeFromRenderGroup(this.value1);
          hiTraceMeter.finishTrace("true", 0);
        })
      Button("false")
        .onClick(() => {
          hiTraceMeter.startTrace("false", 0);
          this.value1 = false;
          this.myUpdater.attribute?.excludeFromRenderGroup(this.value1);
          hiTraceMeter.finishTrace("false", 0);
        })
      Button("undefined")
        .onClick(() => {
          hiTraceMeter.startTrace("undefined", 0);
          this.value1 = undefined;
          this.myUpdater.attribute?.excludeFromRenderGroup(this.value1);
          hiTraceMeter.finishTrace("undefined", 0);
        })
    }
    .height('100%')
  }
}