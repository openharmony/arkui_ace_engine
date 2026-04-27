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

import { AttributeUpdater } from '@kit.ArkUI';

/**
 * reloadKey属性直通场景示例
 * 通过AttributeUpdater<ImageAttribute, ImageInterface>的updateConstructorParams(src, reloadKey)
 * 属性直通更新Image构造参数，绕过状态变量直接触发UI更新
 *
 * 调用链: updateConstructorParams(src, reloadKey) → initialize([src, reloadKey])
 * → ImageSrcModifier + ImageReloadKeyModifier → C++ setReloadKey
 * reloadKey变化时绕过缓存重新加载图片
 */

class ReloadKeyScenarioUpdater extends AttributeUpdater<ImageAttribute, ImageInterface> {
  initializeModifier(instance: ImageAttribute): void {
    instance.width(200)
    instance.height(200)
    instance.objectFit(ImageFit.Cover)
  }
}

@Entry
@Component
struct ImageReloadKeyScenarioExample {
  @State filePath: string = '/data/storage/el2/base/files/test.png'
  @State reloadKey: string = 'key_a'
  @State loadCount: number = 0
  @State lastEvent: string = 'None'
  updater: ReloadKeyScenarioUpdater = new ReloadKeyScenarioUpdater()

  build() {
    Scroll() {
      Column({ space: 12 }) {
        Text('reloadKey属性直通 Scenario Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        // 状态信息
        Column({ space: 4 }) {
          Text('filePath: ' + this.filePath.split('/').pop())
            .fontSize(12)
            .fontColor('#333333')
          Text('reloadKey: ' + this.reloadKey)
            .fontSize(12)
            .fontColor('#333333')
          Text('Load count: ' + this.loadCount)
            .fontSize(12)
            .fontColor('#333333')
          Text('Last event: ' + this.lastEvent)
            .fontSize(12)
            .fontColor('#999999')
        }
        .width('90%')
        .padding(10)
        .border({ width: 1, color: '#dddddd', radius: 8 })
        .alignItems(HorizontalAlign.Start)

        // 通过attributeModifier绑定AttributeUpdater
        // 初始化时initializeModifier设置视觉属性
        Image($r('app.media.startIcon'))
          .attributeModifier(this.updater)
          .border({ width: 1, color: '#cccccc' })
          .onComplete(() => {
            this.loadCount++
            this.lastEvent = 'onComplete (count=' + this.loadCount + ')'
          })
          .onError(() => {
            this.lastEvent = 'onError'
          })

        // 场景1: 修改reloadKey，相同路径 -> 绕过缓存重新加载
        Text('场景1: 相同路径，修改reloadKey -> 绕过缓存')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10 })

        Row({ space: 10 }) {
          Button('reloadKey = key_b')
            .fontSize(12)
            .onClick(() => {
              this.reloadKey = 'key_b'
              this.lastEvent = 'User: changed reloadKey to key_b'
              // 属性直通: 通过updateConstructorParams(src, reloadKey)更新构造参数
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })

          Button('reloadKey = key_c')
            .fontSize(12)
            .onClick(() => {
              this.reloadKey = 'key_c'
              this.lastEvent = 'User: changed reloadKey to key_c'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景2: reloadKey A -> B -> A
        Text('场景2: reloadKey A -> B -> A')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10 })

        Row({ space: 10 }) {
          Button('reloadKey = key_a')
            .fontSize(12)
            .onClick(() => {
              this.reloadKey = 'key_a'
              this.lastEvent = 'User: reverted reloadKey to key_a (A->B->A)'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })

          Button('reloadKey = key_b')
            .fontSize(12)
            .onClick(() => {
              this.reloadKey = 'key_b'
              this.lastEvent = 'User: changed reloadKey to key_b'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景3: 修改路径，保持reloadKey
        Text('场景3: 修改路径，相同reloadKey')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10 })

        Row({ space: 10 }) {
          Button('path = test.png')
            .fontSize(12)
            .onClick(() => {
              this.filePath = '/data/storage/el2/base/files/test.png'
              this.lastEvent = 'User: changed path to test.png'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })

          Button('path = test_v2.png')
            .fontSize(12)
            .onClick(() => {
              this.filePath = '/data/storage/el2/base/files/test_v2.png'
              this.lastEvent = 'User: changed path to test_v2.png'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景4: 同时修改路径和reloadKey
        Text('场景4: 同时修改路径和reloadKey')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10 })

        Button('Change both')
          .fontSize(12)
          .onClick(() => {
            this.filePath = '/data/storage/el2/base/files/test_v3.png'
            this.reloadKey = 'key_' + Date.now().toString()
            this.lastEvent = 'User: changed both path and reloadKey'
            this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
          })

        // 重置
        Button('Reset')
          .fontSize(12)
          .width('80%')
          .backgroundColor('#ff5555')
          .onClick(() => {
            this.reloadKey = 'key_a'
            this.filePath = '/data/storage/el2/base/files/test.png'
            this.loadCount = 0
            this.lastEvent = 'Reset'
            this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
          })
      }
      .width('100%')
      .padding(15)
    }
    .height('100%')
    .width('100%')
  }
}
