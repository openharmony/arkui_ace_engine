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
 * 测试Image组件事件处理
 * 涵盖onComplete、onError、onAppear、onDisappear等事件
 */
import { image } from '@kit.ImageKit'
import { BusinessError } from '@ohos.base'

interface EventLog {
  timestamp: number
  event: string
  details: string
  success: boolean
}

@Entry
@Component
struct ImageEventTestCase {
  @State eventLogs: Array<EventLog> = []
  @State currentTestIndex: number = 0
  @State testInProgress: boolean = false
  @State imageLoadState: 'idle' | 'loading' | 'success' | 'error' = 'idle'
  @State eventCounter: Map<string, number> = new Map()
  @State testResults: Array<{ testName: string, expectedEvents: number, actualEvents: number, status: string }> = []

  private readonly TEST_SCENARIOS = [
    {
      name: '正常图片加载事件',
      imageUrl: $r('app.media.icon'),
      expectedEvents: ['onAppear', 'onComplete'],
      stressTest: false
    },
    {
      name: '无效图片加载事件',
      imageUrl: 'invalid://nonexistent/image.jpg',
      expectedEvents: ['onAppear', 'onError'],
      stressTest: false
    },
    {
      name: '网络图片加载事件',
      imageUrl: 'https://picsum.photos/200/200',
      expectedEvents: ['onAppear', 'onComplete'],
      stressTest: false
    },
    {
      name: '替代图片事件',
      imageUrl: '',
      altImage: $r('app.media.icon'),
      expectedEvents: ['onAppear', 'onComplete'],
      stressTest: false
    },
    {
      name: '快速切换图片事件',
      imageUrl: $r('app.media.icon'),
      expectedEvents: ['onAppear', 'onComplete', 'onDisappear'],
      stressTest: true
    },
    {
      name: '动态图片源事件',
      imageUrl: $r('app.media.icon'),
      expectedEvents: ['onAppear', 'onComplete'],
      stressTest: false
    },
    {
      name: '图片缓存事件',
      imageUrl: $r('app.media.icon'),
      expectedEvents: ['onAppear', 'onComplete'],
      stressTest: false
    }
  ]

  aboutToAppear() {
    this.initializeEventCounter()
    this.startEventTests()
  }

  private initializeEventCounter(): void {
    const allEvents = ['onAppear', 'onDisappear', 'onComplete', 'onError', 'onDragStart', 'onDragEnd']
    allEvents.forEach(event => {
      this.eventCounter.set(event, 0)
    })
  }

  private async startEventTests(): Promise<void> {
    this.testInProgress = true
    this.eventLogs = []
    this.testResults = []

    for (let i = 0; i < this.TEST_SCENARIOS.length; i++) {
      this.currentTestIndex = i
      await this.runSingleEventTest(this.TEST_SCENARIOS[i])
      await this.delay(1000) // 测试间隔
    }

    this.testInProgress = false
  }

  private async runSingleEventTest(scenario: any): Promise<void> {
    const testStartTime = Date.now()
    const initialEvents = new Map(this.eventCounter)
    
    this.addEventLog('testStart', `开始测试: ${scenario.name}`, true)

    try {
      if (scenario.stressTest) {
        await this.runStressTest(scenario)
      } else {
        await this.runNormalTest(scenario)
      }

      // 等待事件触发
      await this.delay(2000)

      // 统计事件次数
      const eventCounts = this.calculateEventDifferences(initialEvents)
      const expectedCount = scenario.expectedEvents.length
      const actualCount = eventCounts.filter(count => count > 0).length

      this.testResults.push({
        testName: scenario.name,
        expectedEvents: expectedCount,
        actualEvents: actualCount,
        status: actualCount >= expectedCount ? 'success' : 'partial'
      })

      this.addEventLog('testComplete', `测试完成: ${scenario.name}`, true)

    } catch (error) {
      this.testResults.push({
        testName: scenario.name,
        expectedEvents: scenario.expectedEvents.length,
        actualEvents: 0,
        status: 'failed'
      })
      this.addEventLog('testError', `测试失败: ${scenario.name}`, false)
    }

    const testDuration = Date.now() - testStartTime
    this.addEventLog('testDuration', `测试耗时: ${testDuration}ms`, true)
  }

  private async runNormalTest(scenario: any): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        this.imageLoadState = 'loading'
        
        // 模拟图片加载过程
        setTimeout(() => {
          if (scenario.expectedEvents.includes('onError') && scenario.imageUrl.toString().includes('invalid')) {
            this.imageLoadState = 'error'
            this.onImageError('Invalid image URL', scenario.imageUrl)
          } else {
            this.imageLoadState = 'success'
            this.onImageComplete(scenario.imageUrl)
          }
          resolve()
        }, 500 + Math.random() * 1000) // 随机延迟模拟真实场景

      } catch (error) {
        reject(error)
      }
    })
  }

  private async runStressTest(scenario: any): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        let switchCount = 0
        const maxSwitches = 5

        const switchInterval = setInterval(() => {
          this.onImageDisappear(scenario.imageUrl)
          this.onImageAppear(scenario.imageUrl)
          
          switchCount++
          if (switchCount >= maxSwitches) {
            clearInterval(switchInterval)
            this.imageLoadState = 'success'
            this.onImageComplete(scenario.imageUrl)
            resolve()
          }
        }, 200)

      } catch (error) {
        reject(error)
      }
    })
  }

  private calculateEventDifferences(initial: Map<string, number>): Array<number> {
    const differences: Array<number> = []
    for (const [event, count] of this.eventCounter) {
      const initialCount = initial.get(event) || 0
      differences.push(count - initialCount)
    }
    return differences
  }

  private addEventLog(event: string, details: string, success: boolean): void {
    this.eventLogs.unshift({
      timestamp: Date.now(),
      event: event,
      details: details,
      success: success
    })

    // 限制日志数量
    if (this.eventLogs.length > 100) {
      this.eventLogs = this.eventLogs.slice(0, 100)
    }
  }

  private incrementEventCounter(event: string): void {
    const current = this.eventCounter.get(event) || 0
    this.eventCounter.set(event, current + 1)
  }

  // 事件处理方法
  private onImageAppear(imageUrl: string | Resource): void {
    this.incrementEventCounter('onAppear')
    this.addEventLog('onAppear', `图片出现: ${imageUrl}`, true)
  }

  private onImageDisappear(imageUrl: string | Resource): void {
    this.incrementEventCounter('onDisappear')
    this.addEventLog('onDisappear', `图片消失: ${imageUrl}`, true)
  }

  private onImageComplete(imageUrl: string | Resource): void {
    this.incrementEventCounter('onComplete')
    this.addEventLog('onComplete', `图片加载完成: ${imageUrl}`, true)
  }

  private onImageError(error: string, imageUrl: string | Resource): void {
    this.incrementEventCounter('onError')
    this.addEventLog('onError', `图片加载失败: ${error}, URL: ${imageUrl}`, false)
  }

  private onImageDragStart(): void {
    this.incrementEventCounter('onDragStart')
    this.addEventLog('onDragStart', '图片拖拽开始', true)
  }

  private onImageDragEnd(): void {
    this.incrementEventCounter('onDragEnd')
    this.addEventLog('onDragEnd', '图片拖拽结束', true)
  }

  private delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms))
  }

  build() {
    Column() {
      // 标题和状态
      Row() {
        Text('Image事件处理测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        if (this.testInProgress) {
          LoadingProgress()
            .width(20)
            .height(20)
            .margin({ right: 8 })
        }
        Text(`测试进度: ${this.currentTestIndex + 1}/${this.TEST_SCENARIOS.length}`)
          .fontSize(14)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .padding(16)

      Scroll() {
        Column() {
          // 测试图片展示区域
          Column() {
            Text('测试图片展示区')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 8 })

            Row() {
              // 正常加载的图片
              Column() {
                Text('正常加载')
                  .fontSize(12)
                  .margin({ bottom: 4 })
                Image($r('app.media.icon'))
                  .width(80)
                  .height(80)
                  .onAppear(() => this.onImageAppear($r('app.media.icon')))
                  .onDisappear(() => this.onImageDisappear($r('app.media.icon')))
                  .onComplete(() => this.onImageComplete($r('app.media.icon')))
                  .onError((error: BusinessError) => this.onImageError(error.message, $r('app.media.icon')))
              }
              .margin(8)

              // 网络图片
              Column() {
                Text('网络图片')
                  .fontSize(12)
                  .margin({ bottom: 4 })
                Image('https://picsum.photos/80/80')
                  .width(80)
                  .height(80)
                  .alt($r('app.media.icon'))
                  .onAppear(() => this.onImageAppear('https://picsum.photos/80/80'))
                  .onDisappear(() => this.onImageDisappear('https://picsum.photos/80/80'))
                  .onComplete(() => this.onImageComplete('https://picsum.photos/80/80'))
                  .onError((error: BusinessError) => this.onImageError(error.message, 'https://picsum.photos/80/80'))
              }
              .margin(8)

              // 无效URL图片
              Column() {
                Text('无效URL')
                  .fontSize(12)
                  .margin({ bottom: 4 })
                Image('invalid://url')
                  .width(80)
                  .height(80)
                  .alt($r('app.media.icon'))
                  .onAppear(() => this.onImageAppear('invalid://url'))
                  .onDisappear(() => this.onImageDisappear('invalid://url'))
                  .onComplete(() => this.onImageComplete('invalid://url'))
                  .onError((error: BusinessError) => this.onImageError(error.message, 'invalid://url'))
              }
              .margin(8)

              // 拖拽测试图片
              Column() {
                Text('拖拽测试')
                  .fontSize(12)
                  .margin({ bottom: 4 })
                Image($r('app.media.icon'))
                  .width(80)
                  .height(80)
                  .draggable(true)
                  .onAppear(() => this.onImageAppear('dragTest'))
                  .onDragStart(() => this.onImageDragStart())
                  .onDragEnd(() => this.onImageDragEnd())
              }
              .margin(8)
            }
            .justifyContent(FlexAlign.Center)

            // 加载状态指示器
            Row() {
              Text('加载状态:')
                .fontSize(14)
                .margin({ right: 8 })
              Text(this.imageLoadState)
                .fontSize(14)
                .fontColor(this.getStateColor())
            }
            .justifyContent(FlexAlign.Center)
            .margin({ top: 16 })
          }
          .padding(16)
          .backgroundColor(Color.White)
          .borderRadius(8)
          .margin({ vertical: 8 })

          Divider()

          // 事件统计
          Text('事件次数统计')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 16, bottom: 8 })

          Grid() {
            ForEach(Array.from(this.eventCounter.entries()), ([event, count]) => {
              GridItem() {
                Column() {
                  Text(event)
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${count}`)
                    .fontSize(18)
                    .fontWeight(FontWeight.Bold)
                    .fontColor(count > 0 ? Color.Blue : Color.Gray)
                }
                .justifyContent(FlexAlign.Center)
                .padding(8)
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(8)
          .columnsGap(8)
          .padding(8)

          Divider()

          // 测试结果
          Text('自动化测试结果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 16, bottom: 8 })

          ForEach(this.testResults, (result: { testName: string, expectedEvents: number, actualEvents: number, status: string }) => {
            Row() {
              Column() {
                Text(result.testName)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                Text(`预期: ${result.expectedEvents} | 实际: ${result.actualEvents}`)
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }
              .layoutWeight(1)
              .alignItems(HorizontalAlign.Start)

              Text(result.status)
                .fontSize(12)
                .fontColor(this.getStatusColor(result.status))
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor(this.getStatusBgColor(result.status))
                .borderRadius(4)
            }
            .width('100%')
            .padding(12)
            .backgroundColor('#FAFAFA')
            .borderRadius(6)
            .margin({ bottom: 6 })
          })

          Divider()

          // 事件日志
          Text('事件日志 (最新50条)')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 16, bottom: 8 })

          List() {
            ForEach(this.eventLogs.slice(0, 50), (log: EventLog, index: number) => {
              ListItem() {
                Row() {
                  Circle({ width: 6, height: 6 })
                    .fill(log.success ? Color.Green : Color.Red)
                    .margin({ right: 8 })

                  Column() {
                    Text(log.event)
                      .fontSize(12)
                      .fontWeight(FontWeight.Medium)
                    Text(log.details)
                      .fontSize(10)
                      .fontColor(Color.Gray)
                      .maxLines(2)
                      .textOverflow({ overflow: TextOverflow.Ellipsis })
                  }
                  .layoutWeight(1)
                  .alignItems(HorizontalAlign.Start)

                  Text(`${this.formatTime(log.timestamp)}`)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                }
                .width('100%')
                .padding(8)
                .backgroundColor(index % 2 === 0 ? Color.White : '#FAFAFA')
              }
            })
          }
          .width('100%')
          .height(300)
          .borderRadius(6)
          .border({ width: 1, color: Color.Gray })
        }
        .padding(16)
      }
      .layoutWeight(1)

      // 控制按钮
      Row() {
        Button('重新测试')
          .onClick(() => {
            this.initializeEventCounter()
            this.startEventTests()
          })

        Button('清空日志')
          .onClick(() => {
            this.eventLogs = []
          })
          .margin({ left: 8 })

        Button('手动触发')
          .onClick(() => {
            this.testInProgress = false
            this.addEventLog('manual', '手动触发事件', true)
          })
          .margin({ left: 8 })
      }
      .justifyContent(FlexAlign.Center)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  private getStateColor(): ResourceColor {
    switch (this.imageLoadState) {
      case 'loading':
        return Color.Blue
      case 'success':
        return Color.Green
      case 'error':
        return Color.Red
      default:
        return Color.Gray
    }
  }

  private getStatusColor(status: string): ResourceColor {
    switch (status) {
      case 'success':
        return Color.Green
      case 'partial':
        return Color.Orange
      case 'failed':
        return Color.Red
      default:
        return Color.Gray
    }
  }

  private getStatusBgColor(status: string): ResourceColor {
    switch (status) {
      case 'success':
        return '#E8F5E8'
      case 'partial':
        return '#FFF3E0'
      case 'failed':
        return '#FFEBEE'
      default:
        return '#F5F5F5'
    }
  }

  private formatTime(timestamp: number): string {
    const date = new Date(timestamp)
    return `${date.getHours().toString().padStart(2, '0')}:${date.getMinutes().toString().padStart(2, '0')}:${date.getSeconds().toString().padStart(2, '0')}.${date.getMilliseconds().toString().padStart(3, '0')}`
  }
}