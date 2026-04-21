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

import { promptAction } from '@kit.ArkUI'

@Builder
export function ToastLifecycleBuilder(name: string, param: Object) {
  ToastLifecycleExample()
}

@Entry
@Component
struct ToastLifecycleExample {
  pathStack: NavPathStack = new NavPathStack()
  @State activeToastIds: number[] = []
  @State toastCreatedCount: number = 0
  @State toastDestroyedCount: number = 0
  @State managedToastId: number = -1
  @State lastToastId: number = -1

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('Toast 生命周期测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Row({ space: 8 }) {
          Text(`创建: ${this.toastCreatedCount}`)
            .fontSize(12)
            .fontColor('#4CAF50')
          Text(` | `)
            .fontSize(12)
          Text(`关闭: ${this.toastDestroyedCount}`)
            .fontSize(12)
            .fontColor('#F44336')
          Text(` | `)
            .fontSize(12)
          Text(`活跃: ${this.activeToastIds.length}`)
            .fontSize(12)
            .fontColor('#2196F3')
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        Text('创建生命周期')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('showToast 创建')
          .width('100%')
          .onClick(() => {
            promptAction.showToast({
              message: '自动管理生命周期',
              duration: 2000
            })
            this.toastCreatedCount++
          })

        Button('openToast 创建')
          .width('100%')
          .onClick(() => {
            promptAction.openToast({
              message: '手动管理生命周期',
              duration: 10000
            }).then((toastId: number) => {
              this.activeToastIds.push(toastId)
              this.toastCreatedCount++
            })
          })

        Divider()

        Text('销毁生命周期')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('创建并记录 ID')
          .width('100%')
          .onClick(() => {
            promptAction.openToast({
              message: '可手动关闭',
              duration: 60000
            }).then((toastId: number) => {
              this.activeToastIds.push(toastId)
              this.toastCreatedCount++
              this.lastToastId = toastId
            })
          })

        Text(`最后创建的 Toast ID: ${this.lastToastId}`)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Button('关闭最后创建的 Toast')
          .width('100%')
          .enabled(this.lastToastId !== -1)
          .onClick(() => {
            if (this.lastToastId !== -1) {
              promptAction.closeToast(this.lastToastId)
              this.activeToastIds = this.activeToastIds.filter(id => id !== this.lastToastId)
              this.toastDestroyedCount++
              this.lastToastId = -1
            }
          })

        Divider()

        Text('自动销毁测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('1秒后自动销毁')
          .width('100%')
          .onClick(() => {
            promptAction.showToast({
              message: '1秒',
              duration: 1000
            })
            this.toastCreatedCount++
          })

        Button('2秒后自动销毁')
          .width('100%')
          .onClick(() => {
            promptAction.showToast({
              message: '2秒',
              duration: 2000
            })
            this.toastCreatedCount++
          })

        Button('5秒后自动销毁')
          .width('100%')
          .onClick(() => {
            promptAction.showToast({
              message: '5秒',
              duration: 5000
            })
            this.toastCreatedCount++
          })

        Divider()

        Text('手动销毁测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')


        Button() {
          if (this.managedToastId === -1) {
            Text('创建长时 Toast')
          } else {
            Text('Toast 已创建')
          }
        }
        .width('100%')
        .enabled(this.managedToastId === -1)
        .onClick(() => {
          promptAction.openToast({
            message: '长时 Toast (60秒)',
            duration: 60000
          }).then((toastId: number) => {
            this.activeToastIds.push(toastId)
            this.toastCreatedCount++
            this.managedToastId = toastId
          })
        })

        Button('手动销毁')
          .width('100%')
          .enabled(this.managedToastId !== -1)
          .onClick(() => {
            if (this.managedToastId !== -1) {
              promptAction.closeToast(this.managedToastId)
              this.activeToastIds = this.activeToastIds.filter(id => id !== this.managedToastId)
              this.toastDestroyedCount++
              this.managedToastId = -1
            }
          })

        Divider()

        Text('批量生命周期管理')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button() {
          Text('批量创建 5 个')
        }
        .width('100%')
        .onClick(async () => {
          for (let i = 0; i < 5; i++) {
            promptAction.openToast({
              message: `批量 ${i + 1}`,
              duration: 60000
            }).then((toastId: number) => {
              this.activeToastIds.push(toastId)
              this.toastCreatedCount++
            })
          }
        })

        Button() {
          Text('批量创建 10 个')
        }
        .width('100%')
        .onClick(async () => {
          for (let i = 0; i < 10; i++) {
            promptAction.openToast({
              message: `批量 ${i + 1}`,
              duration: 60000
            }).then((toastId: number) => {
              this.activeToastIds.push(toastId)
              this.toastCreatedCount++
            })
          }
        })

        Button('关闭所有活跃 Toast')
          .width('100%')
          .backgroundColor('#F44336')
          .enabled(this.activeToastIds.length > 0)
          .onClick(() => {
            let ids = [...this.activeToastIds]
            ids.forEach(id => {
              promptAction.closeToast(id)
            })
            this.activeToastIds = []
            this.toastDestroyedCount += ids.length
          })

        Divider()

        Text('活跃 Toast 列表')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        if (this.activeToastIds.length > 0) {
          List({ space: 4 }) {
            ForEach(this.activeToastIds.slice(0, 10), (id: number) => {
              ListItem() {
                Row({ space: 8 }) {
                  Text(`ID: ${id}`)
                    .fontSize(12)
                    .layoutWeight(1)
                  Button('关闭')
                    .fontSize(10)
                    .height(28)
                    .onClick(() => {
                      promptAction.closeToast(id)
                      this.activeToastIds = this.activeToastIds.filter(i => i !== id)
                      this.toastDestroyedCount++
                    })
                }
                .width('100%')
              }
            })
          }
          .layoutWeight(1)
          .width('100%')

          if (this.activeToastIds.length > 10) {
            Text(`... 还有 ${this.activeToastIds.length - 10} 个 Toast`)
              .fontSize(11)
              .fontColor('#999999')
              .width('100%')
          }
        } else {
          Text('当前没有活跃的 Toast')
            .fontSize(12)
            .fontColor('#999999')
            .width('100%')
        }

        Divider()

        Text('生命周期事件')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('测试自动销毁事件')
          .width('100%')
          .onClick(() => {
            promptAction.showToast({
              message: '测试自动销毁',
              duration: 3000
            })
            this.toastCreatedCount++
          })

        Button('测试手动销毁事件')
          .width('100%')
          .onClick(() => {
            promptAction.openToast({
              message: '测试手动销毁',
              duration: 60000
            }).then((toastId: number) => {
              this.activeToastIds.push(toastId)
              this.toastCreatedCount++
              setTimeout(() => {
                promptAction.closeToast(toastId)
                this.activeToastIds = this.activeToastIds.filter(id => id !== toastId)
                this.toastDestroyedCount++
              }, 2000)
            })
          })

        Divider()

        Text('生命周期统计')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Text(`总创建数: ${this.toastCreatedCount}`)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Text(`总销毁数: ${this.toastDestroyedCount}`)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Text(`当前活跃数: ${this.activeToastIds.length}`)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Text(`理论活跃数: ${this.toastCreatedCount - this.toastDestroyedCount}`)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Button('重置统计')
          .width('100%')
          .onClick(() => {
            this.toastCreatedCount = 0
            this.toastDestroyedCount = 0
          })
      }
      .width('100%')
      .height('100%')
      .padding(12)
    }
    .title('Lifecycle Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
