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
 * 验证Image reloadKey属性直通功能
 * 通过AttributeUpdater<ImageAttribute, ImageInterface>的updateConstructorParams(src, reloadKey)
 * 属性直通更新Image构造参数
 *
 * 调用链: updateConstructorParams(src, reloadKey) → initialize([src, reloadKey])
 * → ImageSrcModifier + ImageReloadKeyModifier → C++ setReloadKey
 * 当reloadKey变化时绕过缓存重新加载图片
 */

class ReloadKeyTestCaseUpdater extends AttributeUpdater<ImageAttribute, ImageInterface> {
  initializeModifier(instance: ImageAttribute): void {
    instance.width(180)
    instance.height(180)
    instance.objectFit(ImageFit.Cover)
  }
}

@Entry
@Component
struct ImageReloadKeyTestCase {
  @State reloadKey: string = 'v1'
  @State filePath: string = '/data/storage/el2/base/files/test.png'
  @State loadCount: number = 0
  @State lastEvent: string = 'None'
  @State reloadKeyHistory: string[] = ['v1']
  updater: ReloadKeyTestCaseUpdater = new ReloadKeyTestCaseUpdater()

  build() {
    Scroll() {
      Column({ space: 10 }) {
        Text('reloadKey属性直通 TestCase')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15 })

        // 状态信息
        Column({ space: 4 }) {
          Text('filePath: ' + this.filePath.split('/').pop())
            .fontSize(12)
            .fontColor('#333333')
          Text('reloadKey: ' + this.reloadKey)
            .fontSize(12)
            .fontColor('#333333')
          Text('loadCount: ' + this.loadCount)
            .fontSize(12)
            .fontColor('#333333')
          Text('lastEvent: ' + this.lastEvent)
            .fontSize(12)
            .fontColor('#999999')
          Text('history: [' + this.reloadKeyHistory.join(' -> ') + ']')
            .fontSize(11)
            .fontColor('#999999')
        }
        .width('90%')
        .padding(8)
        .border({ width: 1, color: '#dddddd', radius: 6 })
        .alignItems(HorizontalAlign.Start)

        // 通过attributeModifier绑定AttributeUpdater
        // 初始化时initializeModifier设置视觉属性
        Image($r('app.media.startIcon'))
          .attributeModifier(this.updater)
          .border({ width: 1, color: '#cccccc' })
          .id('reloadKeyImage')
          .onComplete(() => {
            this.loadCount++
            this.lastEvent = 'onComplete (count=' + this.loadCount + ')'
          })
          .onError((err) => {
            this.lastEvent = 'onError: ' + (err?.message ?? 'unknown')
          })

        // 场景1: 修改reloadKey，相同路径 -> 绕过缓存重新加载
        Text('场景1: 相同路径，修改reloadKey -> 绕过缓存')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 8 })

        Row({ space: 8 }) {
          Button('reloadKey=v2')
            .fontSize(11)
            .onClick(() => {
              this.reloadKey = 'v2'
              this.reloadKeyHistory.push('v2')
              this.lastEvent = 'User: reloadKey -> v2'
              // 属性直通: 通过updateConstructorParams(src, reloadKey)更新构造参数
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
          Button('reloadKey=v3')
            .fontSize(11)
            .onClick(() => {
              this.reloadKey = 'v3'
              this.reloadKeyHistory.push('v3')
              this.lastEvent = 'User: reloadKey -> v3'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
          Button('random key')
            .fontSize(11)
            .onClick(() => {
              let key = 'key_' + Date.now()
              this.reloadKey = key
              this.reloadKeyHistory.push(key)
              this.lastEvent = 'User: reloadKey -> ' + key
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景2: reloadKey A->B->A
        Text('场景2: reloadKey A->B->A -> 仍然绕过缓存')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 8 })

        Row({ space: 8 }) {
          Button('reloadKey=v1')
            .fontSize(11)
            .onClick(() => {
              this.reloadKey = 'v1'
              this.reloadKeyHistory.push('v1')
              this.lastEvent = 'User: A->B->A scenario, reloadKey -> v1'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
          Button('reloadKey=v2')
            .fontSize(11)
            .onClick(() => {
              this.reloadKey = 'v2'
              this.reloadKeyHistory.push('v2')
              this.lastEvent = 'User: reloadKey -> v2'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景3: 修改路径，保持reloadKey
        Text('场景3: 修改路径，相同reloadKey -> 走缓存')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 8 })

        Row({ space: 8 }) {
          Button('path=test.png')
            .fontSize(11)
            .onClick(() => {
              this.filePath = '/data/storage/el2/base/files/test.png'
              this.lastEvent = 'User: path -> test.png'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
          Button('path=test_v2.png')
            .fontSize(11)
            .onClick(() => {
              this.filePath = '/data/storage/el2/base/files/test_v2.png'
              this.lastEvent = 'User: path -> test_v2.png'
              this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
            })
        }

        // 场景4: 同时修改路径和reloadKey
        Text('场景4: 同时修改路径和reloadKey')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 8 })

        Button('Change both')
          .fontSize(11)
          .onClick(() => {
            this.filePath = '/data/storage/el2/base/files/test_v3.png'
            this.reloadKey = 'key_' + Date.now()
            this.reloadKeyHistory.push(this.reloadKey)
            this.lastEvent = 'User: changed both'
            this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
          })

        // 重置
        Button('Reset')
          .fontSize(11)
          .width('80%')
          .backgroundColor('#ff6666')
          .onClick(() => {
            this.reloadKey = 'v1'
            this.filePath = '/data/storage/el2/base/files/test.png'
            this.loadCount = 0
            this.lastEvent = 'Reset'
            this.reloadKeyHistory = ['v1']
            this.updater.updateConstructorParams('file://' + this.filePath, this.reloadKey)
          })
      }
      .width('100%')
      .padding(12)
    }
    .height('100%')
    .width('100%')
  }
}
