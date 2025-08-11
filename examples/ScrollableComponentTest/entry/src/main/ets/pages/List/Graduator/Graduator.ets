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

import { display, PathShape } from '@kit.ArkUI'

// 定义时间点的数据结构
export interface TimePoint {
  timestamp: number // 自2000年1月1日00:00的小时数
  hasColorBar: boolean // 是否有颜色条
  moonRiseMinutes: number // 该小时内月亮升起的起始分钟
  moonSetMinutes: number // 该小时内月亮落下的结束分钟
}

// 定义 hasColorBar 方法返回对象的接口
export interface MoonTimeResult {
  hasColorBar: boolean
  moonRiseMinutes: number
  moonSetMinutes: number
}

export class TimePointDataSource implements IDataSource {
  private listeners: DataChangeListener[] = []
  // 使用 Map 替代索引签名对象
  private cachedData: Map<number, TimePoint> = new Map()
  public startDate = new Date(2000, 0, 1, 0, 0)
  private endDate = new Date(2101, 0, 1, 0, 0)
  private totalHours = (this.endDate.getTime() - this.startDate.getTime()) / (1000 * 60 * 60)
  private lat = 30.0
  private lon = 120.0

  totalCount(): number {
    return this.totalHours
  }

  getData(index: number): TimePoint {
    if (!this.cachedData.has(index)) {
      const result = this.hasColorBar(index)
      const hasColorBar = result.hasColorBar
      const moonRiseMinutes = result.moonRiseMinutes
      const moonSetMinutes = result.moonSetMinutes
      this.cachedData.set(index, {
        timestamp: index,
        hasColorBar,
        moonRiseMinutes,
        moonSetMinutes
      })
    }
    return this.cachedData.get(index)!
  }

  constructor(lat: number | null | undefined, lon: number | null | undefined) {
    if (lat && lon) {
      this.lat = lat
      this.lon = lon
    }
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener)
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener)
    if (index !== -1) {
      this.listeners.splice(index, 1)
    }
  }

  private hasColorBar(index: number): MoonTimeResult {
    let moonRiseMinutes = 0
    let moonSetMinutes = 60
    let hasColorBar = false
    return { hasColorBar, moonRiseMinutes, moonSetMinutes }
  }
}

@Entry
@Component
struct RollBar {
  private dataSource: TimePointDataSource = new TimePointDataSource(30, 120) //2000 - 2100年数据源
  @State curTime: Date = new Date(2025,11,31) //指示条时间
  @State isInit: boolean = true
  private baseOffset: number = 0 //基本偏移量，以其为标准进行比较加时间还是间时间
  private intervalTime: number = 12
  private listScroller: ListScroller = new ListScroller()
  private cursorWidth: number = 12
  private cursorHeight: number = 10
  private centerWidth: number = 0
  private count: number = 0
  private lastOffsetDiff: number = 0 //滚动都因为小数而舍去的差值
  private centerIndex: number = 0;

  aboutToAppear(): void {
    const displayInfo = display.getDefaultDisplaySync()
    this.centerWidth = px2vp(displayInfo.width) / 2
  }

  // 计算黄色条宽度的方法
  private calculateBarWidth(item: TimePoint): number {
    return (item.moonSetMinutes - item.moonRiseMinutes) / 60 * this.intervalTime
  }

  // 计算黄色条左边距的方法
  private calculateBarMarginLeft(item: TimePoint): number {
    return Math.ceil(item.moonRiseMinutes / 60 * this.intervalTime)
  }

  //指示浮标
  onGetCursor() {
    const centerX = vp2px(this.cursorWidth / 2)
    const endX = vp2px(this.cursorWidth)
    const centerY = vp2px(this.cursorHeight)
    return `M0 0 L${centerX} ${centerY} L${endX} 0 Z`
  }

  formatDate(date: Date) {
    // 获取年、月、日、小时、分钟
    const year = date.getFullYear()
    const month = String(date.getMonth() + 1).padStart(2, '0') // 月份从 0 开始，需要加 1
    const day = String(date.getDate()).padStart(2, '0')
    const hours = String(date.getHours()).padStart(2, '0')
    const minutes = String(date.getMinutes()).padStart(2, '0')
    // 获取星期几
    const weekdays = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六']
    const weekday = weekdays[date.getDay()]
    // 拼接成目标格式
    return `${year}/${month}/${day} ${hours}:${minutes} ${weekday}`
  }

  //回到当前时间
  onBackCurTime() {
    this.onTimeSync(new Date())
  }

  onTimeSync(time: Date) {
    const now = time
    const index = Math.floor((now.getTime() - this.dataSource.startDate.getTime()) / (1000 * 60 * 60)) + 1
    const offsetMin = now.getMinutes() * 0.2
    this.listScroller.scrollToIndex(index)
    this.listScroller.scrollBy(-this.centerWidth + offsetMin, 0)
    this.count = 0
  }

  getCurrentOffset(offset: number): number {
    let rect = this.listScroller.getItemRect(this.centerIndex);
    let totalOffset = this.centerWidth + this.intervalTime * (this.centerIndex - 1) - rect.x + offset;
    totalOffset = Math.min(10624320, totalOffset)
    totalOffset = Math.max(0, totalOffset)
    return totalOffset
  }

  onSyncTime(offset: number) {
    if (!this.isInit) {
      if (this.count) {
      }
      this.count++
      const curOffset = this.getCurrentOffset(offset)
      const offsetDiff = curOffset - this.baseOffset
      console.log('当前偏移值--------', curOffset, '上一次偏移值', this.baseOffset, '当前偏移差值--------', offsetDiff,
        '上一次偏移值------', this.lastOffsetDiff)
      if (Math.abs(offsetDiff) >= 0.2) {
        const specificOffset: number = (Math.sign(offsetDiff) * Math.abs(offsetDiff) + this.lastOffsetDiff)
        const deltaMinutes = Math.trunc(specificOffset / 0.2)
        this.lastOffsetDiff = specificOffset - deltaMinutes * 0.2
        const tempTime = this.curTime
        tempTime.setMinutes(tempTime.getMinutes() + deltaMinutes)
        this.curTime = new Date(tempTime)
        this.baseOffset = curOffset
      }
    }
  }

  private isSpecialTime(timestamp: number): boolean {
    const hour = timestamp % 24
    return hour === 0 || hour === 12 // 判断是否是0时或12时
  }

  formatTime(timestamp: number): string {
    const date = new Date(timestamp * 60 * 60 * 1000 + new Date(2000, 0, 1, 0, 0).getTime())
    return `${date.getFullYear()}/${date.getMonth() + 1}/${date.getDate()} ${date.getHours()}:${date.getMinutes()}`
  }

  build() {
    Column() {
      Row() {
        Text(this.formatDate(this.curTime)).fontSize(18).fontColor(Color.White).height(26).lineHeight(26)
      }
      .padding({ left: 15, right: 15 })
      .width('100%')
      Stack() {
        //浮标
        Row()
          .zIndex(20)
          .height(this.cursorWidth)
          .width(this.cursorHeight + 2)
          .offset({ x: -0.5, y: -22 })
          .maskShape(
            new PathShape({
              commands: this.onGetCursor()
            }).fill(Color.White)
          )
          .backgroundColor(Color.Red)
        RelativeContainer() {
          List({ scroller: this.listScroller }) {
            ListItem() {
              Column().width(this.centerWidth).height(20)
            }
            LazyForEach(
              this.dataSource,
              (item: TimePoint) => {
                ListItem() {
                  RelativeContainer() {
                    Row().width(1).height(this.isSpecialTime(item.timestamp) ? 24 : 12).backgroundColor(Color.White)
                      .alignRules({
                        center: { anchor: '__container__', align: VerticalAlign.Center },
                        middle: { anchor: '__container__', align: HorizontalAlign.Start }
                      })
                  }
                  .width(this.intervalTime)
                  .height(60)
                }
              },
              (item: TimePoint) => item.timestamp.toString()
            )
            ListItem() {
              RelativeContainer() {
                Row().width(1).height(20).backgroundColor(Color.White).alignRules({
                  center: { anchor: '__container__', align: VerticalAlign.Center },
                  middle: { anchor: '__container__', align: HorizontalAlign.Start }
                })
                Text('0时')
                  .fontSize(14)
                  .textAlign(TextAlign.Center)
                  .margin({ top: 5 })// 调整上下间距
                  .fontColor(Color.White)
                  .width(30)
                  .alignRules({
                    center: { anchor: '__container__', align: VerticalAlign.Bottom },
                    left: { anchor: '__container__', align: HorizontalAlign.Start }
                  })
                  .offset({ x: -14, y: 0 })
              }
              .width(1)
              .height(60)
            }
            ListItem() {
              Column().width(this.centerWidth -1).height(20)
            }
          }
          .width('100%')
          .height(70)
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center },
            middle: { anchor: '__container__', align: HorizontalAlign.Center }
          })
          .edgeEffect(EdgeEffect.None)
          .listDirection(Axis.Horizontal)
          .scrollBar(BarState.Off)
          .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
            console.log('滚动条滚动的距离------',scrollOffset)
            this.onSyncTime(scrollOffset)
            return undefined
          })
          .onScrollIndex((start: number, end: number, center: number)=>{
            this.centerIndex = center;
          })
          .onScrollStop(() => {
            console.log('list滚动完全停止')
          })
          .onVisibleAreaChange([0.0, 1.0], (isExpanding: boolean, currentRatio: number) => {
            console.info('Test Text isExpanding: ' + isExpanding + ', currentRatio:' + currentRatio)
            if (isExpanding && currentRatio >= 1.0) {
              this.onTimeSync(this.curTime)
              setTimeout(() => {
                this.baseOffset = this.getCurrentOffset(0)
                this.isInit = false
              }, 100)
            }
            if (!isExpanding && currentRatio <= 0.0) {
              console.info('Test Text is completely invisible.')
              this.isInit = true
              this.count = 0
            }
          })
          Row()
            .hitTestBehavior(HitTestMode.None)
            .width('100%')
            .linearGradient({
              direction: GradientDirection.Left, // 渐变方向
              repeating: false, // 渐变颜色是否重复
              colors: [['#9917273a', 0.0], ['#0017273a', 0.4], ['#0017273a', 0.6], ['#9917273a', 1.0]] // 数组末尾元素占比小于1时满足重复着色效果
            })
            .height(70)
        }
        .width('100%')
      }
      .width('100%')
      .height(70)
    }
    .height(160)
    .padding({ top: 15 })
    .backgroundColor('#FF17273A')
  }
}
