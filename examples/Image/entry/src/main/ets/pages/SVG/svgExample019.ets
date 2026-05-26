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

interface GradientStop {
  color: ResourceColor
  ratio: number
}

interface PieDataItem {
  label: string
  value: number
  color: ResourceColor
}

interface BarDataItem {
  label: string
  value: number
  color: ResourceColor
}

interface TreeNode {
  name: string
  icon?: Resource
  expanded: boolean
  children: TreeNode[]
}

interface StepItem {
  title: string
  desc: string
  icon: Resource
  completed: boolean
  active: boolean
}

interface MetricCard {
  title: string
  value: string
  unit: string
  trend: number
  icon: Resource
  color: ResourceColor
}

/**
 * SVG Dashboard & UI Components Example (Part 1)
 * Metrics, Gauges, Progress, Charts, Stepper, Timeline,
 * Tree View, Tabs, Sidebar, Notifications, Badges
 */
@Entry
@Component
struct svgExample019 {
  @State gaugeValue: number = 65
  @State gaugeMaxValue: number = 100
  @State gaugeMinValue: number = 0
  @State progressValue: number = 72
  @State ringProgress: number = 85
  @State halfRingProgress: number = 60
  @State currentStep: number = 2
  @State selectedPieIndex: number = -1
  @State selectedBarIndex: number = -1
  @State toggleValue: number = 50
  @State animGaugeValue: number = 0
  @State isGaugeAnimating: boolean = false
  @State speedValue: number = 0
  @State rpmValue: number = 0
  @State fuelValue: number = 80
  @State temperatureValue: number = 45
  @State waveProgress: number = 65
  @State selectedTab: number = 0
  @State collapsedSideBar: boolean = false
  @State notificationCount: number = 3
  @State badgeNumber: number = 5
  @State hoverIndex: number = -1

  @State treeNodes: TreeNode[] = [
    {
      name: 'Root',
      icon: $r('app.media.icon'),
      expanded: true,
      children: [
        {
          name: 'Documents',
          icon: $r('app.media.icon'),
          expanded: false,
          children: [
            { name: 'Report.pdf', expanded: false, children: [] },
            { name: 'Notes.txt', expanded: false, children: [] }
          ]
        },
        {
          name: 'Images',
          icon: $r('app.media.icon'),
          expanded: false,
          children: [
            { name: 'Photo.svg', expanded: false, children: [] },
            { name: 'Logo.svg', expanded: false, children: [] }
          ]
        },
        {
          name: 'Music',
          icon: $r('app.media.icon'),
          expanded: false,
          children: []
        }
      ]
    }
  ]
  @State pieData: PieDataItem[] = [
    { label: 'Product A', value: 35, color: '#FF6B6B' },
    { label: 'Product B', value: 25, color: '#4ECDC4' },
    { label: 'Product C', value: 20, color: '#45B7D1' },
    { label: 'Product D', value: 12, color: '#96CEB4' },
    { label: 'Others', value: 8, color: '#FFEAA7' }
  ]
  @State barData: BarDataItem[] = [
    { label: 'Jan', value: 65, color: '#FF6B6B' },
    { label: 'Feb', value: 78, color: '#4ECDC4' },
    { label: 'Mar', value: 52, color: '#45B7D1' },
    { label: 'Apr', value: 90, color: '#96CEB4' },
    { label: 'May', value: 43, color: '#FFEAA7' },
    { label: 'Jun', value: 71, color: '#DDA0DD' },
    { label: 'Jul', value: 85, color: '#FF8C00' },
    { label: 'Aug', value: 60, color: '#87CEEB' }
  ]
  @State steps: StepItem[] = [
    { title: 'Select', desc: 'Choose your item', icon: $r('app.media.icon'), completed: true, active: false },
    { title: 'Configure', desc: 'Set parameters', icon: $r('app.media.icon'), completed: false, active: true },
    { title: 'Preview', desc: 'Review settings', icon: $r('app.media.icon'), completed: false, active: false },
    { title: 'Confirm', desc: 'Place order', icon: $r('app.media.icon'), completed: false, active: false }
  ]
  @State metrics: MetricCard[] = [
    { title: 'Revenue', value: '128.5', unit: 'K', trend: 12.5, icon: $r('app.media.icon'), color: '#4ECDC4' },
    { title: 'Users', value: '2,847', unit: '', trend: 8.3, icon: $r('app.media.icon'), color: '#FF6B6B' },
    { title: 'Orders', value: '456', unit: '', trend: -3.2, icon: $r('app.media.icon'), color: '#45B7D1' },
    { title: 'Rating', value: '4.8', unit: '/5', trend: 0.5, icon: $r('app.media.icon'), color: '#96CEB4' }
  ]
  @State gradientStops: GradientStop[] = [
    { color: '#FF6B6B', ratio: 0.0 },
    { color: '#4ECDC4', ratio: 0.5 },
    { color: '#45B7D1', ratio: 1.0 }
  ]

  private pieTotal: number = 0

  aboutToAppear(): void {
    this.pieTotal = this.pieData.reduce((sum, item) => sum + item.value, 0)
  }

  private showToast(msg: string): void {
    // Toast helper - delegates to component state
  }

  private toggleTreeNode(node: TreeNode): void {
    node.expanded = !node.expanded
    this.treeNodes = [...this.treeNodes]
  }

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('SVG Dashboard & UI Components (Part 1)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 5 })

        Text('Metrics, Gauges, Progress, Charts & Navigation')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 10 })

        this.MetricCardsSection()
        this.GaugeSection()
        this.SpeedometerSection()
        this.ProgressSection()
        this.RingProgressSection()
        this.WaveProgressSection()
        this.PieChartSection()
        this.BarChartSection()
        this.StepperSection()
        this.TimelineSection()
        this.TreeViewSection()
        this.TabSection()
        this.SidebarSection()
        this.NotificationSection()
        this.BadgeSection()
      }
      .width('100%')
      .padding(15)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F2F5')
  }

  // ============================================================
  // 1. Metric Cards Section
  // ============================================================
  @Builder
  MetricCardsSection() {
    Column({ space: 12 }) {
      Text('Dashboard Metrics')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween }) {
        ForEach(this.metrics, (metric: MetricCard, index: number) => {
          Column({ space: 8 }) {
            Row({ space: 8 }) {
              Image(metric.icon)
                .width(32)
                .height(32)
                .fillColor(metric.color)

              Text(metric.title)
                .fontSize(12)
                .fontColor('#888888')
            }

            Row({ space: 4 }) {
              Text(metric.value)
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
                .fontColor('#333333')

              Text(metric.unit)
                .fontSize(14)
                .fontColor('#888888')
                .margin({ top: 8 })
            }

            Row({ space: 4 }) {
              Image($r('app.media.icon'))
                .width(14)
                .height(14)
                .fillColor(metric.trend >= 0 ? '#4CAF50' : '#F44336')
                .rotate({ angle: metric.trend >= 0 ? 0 : 180 })

              Text((metric.trend >= 0 ? '+' : '') + metric.trend.toFixed(1) + '%')
                .fontSize(12)
                .fontColor(metric.trend >= 0 ? '#4CAF50' : '#F44336')
            }
          }
          .width('48%')
          .padding(12)
          .backgroundColor(Color.White)
          .borderRadius(12)
          .shadow({
            radius: 4,
            color: '#22000000',
            offsetX: 0,
            offsetY: 2
          })
          .margin({ bottom: 8 })
        })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 2. Gauge Section
  // ============================================================
  @Builder
  GaugeSection() {
    Column({ space: 12 }) {
      Text('Gauge Component')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Stack() {
            Gauge({ value: this.gaugeValue, min: this.gaugeMinValue, max: this.gaugeMaxValue })
              .width(120)
              .height(120)
              .colors([[Color.Red, 0.25], [Color.Orange, 0.5], [Color.Yellow, 0.75], [Color.Green, 1.0]])
              .strokeWidth(12)

            Text(this.gaugeValue.toFixed(0) + '%')
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(120)
          .height(120)

          Text('Performance')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Stack() {
            Gauge({ value: this.gaugeValue * 0.8, min: 0, max: 100 })
              .width(120)
              .height(120)
              .colors([[Color.Blue, 1.0]])
              .strokeWidth(10)
              .trackShadow({ radius: 8 })

            Text((this.gaugeValue * 0.8).toFixed(0))
              .fontSize(20)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(120)
          .height(120)

          Text('Efficiency')
            .fontSize(12)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Slider({
        value: this.gaugeValue,
        min: 0,
        max: 100,
        step: 1
      })
        .width('90%')
        .onChange((value: number) => {
          this.gaugeValue = value
        })

      Text('Gauge Value: ' + this.gaugeValue.toFixed(0))
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 3. Speedometer Section
  // ============================================================
  @Builder
  SpeedometerSection() {
    Column({ space: 12 }) {
      Text('Speedometer')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Stack() {
        // Background arc
        Image($r('app.media.icon'))
          .width(200)
          .height(200)
          .fillColor('#E8E8E8')
          .opacity(0.3)

        // Speed indicator SVG
        Image($r('app.media.testSvg'))
          .width(180)
          .height(180)
          .fillColor('#4ECDC4')
          .rotate({ angle: -135 + (this.speedValue / 240) * 270 })
          .clip(new Path({ width: 180, height: 180, commands: 'M90 10 A80 80 0 1 1 10 90' }))

        Column({ space: 2 }) {
          Text(this.speedValue.toFixed(0))
            .fontSize(36)
            .fontWeight(FontWeight.Bold)
            .fontColor('#333333')

          Text('km/h')
            .fontSize(14)
            .fontColor('#888888')
        }
      }
      .width(200)
      .height(200)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.svg'))
              .width(70)
              .height(70)
              .fillColor('#FF6B6B')
              .opacity(0.3)

            Text(this.rpmValue.toFixed(0))
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(70)
          .height(70)

          Text('RPM x1000')
            .fontSize(10)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.icon'))
              .width(70)
              .height(70)
              .fillColor('#45B7D1')
              .opacity(0.3)

            Text(this.fuelValue.toFixed(0) + '%')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(70)
          .height(70)

          Text('Fuel')
            .fontSize(10)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.star'))
              .width(70)
              .height(70)
              .fillColor('#FF8C00')
              .opacity(0.3)

            Text(this.temperatureValue.toFixed(0) + '°')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(70)
          .height(70)

          Text('Temp °C')
            .fontSize(10)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Text('Speed:')
          .fontSize(12)
          .width(50)
        Slider({
          value: this.speedValue,
          min: 0,
          max: 240,
          step: 1
        })
          .width('60%')
          .onChange((value: number) => {
            this.speedValue = value
            this.rpmValue = value * 30 / 240
            this.temperatureValue = 45 + value * 0.2
          })
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('Fuel:')
          .fontSize(12)
          .width(50)
        Slider({
          value: this.fuelValue,
          min: 0,
          max: 100,
          step: 1
        })
          .width('60%')
          .onChange((value: number) => {
            this.fuelValue = value
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 4. Progress Section
  // ============================================================
  @Builder
  ProgressSection() {
    Column({ space: 12 }) {
      Text('Progress Indicators')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Progress({ value: this.progressValue, total: 100, type: ProgressType.Linear })
            .width(120)
            .height(8)
            .color('#4ECDC4')
            .style({ strokeWidth: 8 })

          Text('Linear')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Progress({ value: this.progressValue, total: 100, type: ProgressType.Linear })
            .width(120)
            .height(8)
            .color('#FF6B6B')
            .style({ strokeWidth: 8, enableSmoothEffect: true })

          Text('Smooth')
            .fontSize(12)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Stack() {
            Progress({ value: this.progressValue, total: 100, type: ProgressType.Ring })
              .width(70)
              .height(70)
              .color('#45B7D1')
              .style({ strokeWidth: 6 })

            Text(this.progressValue.toFixed(0) + '%')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(70)
          .height(70)

          Text('Ring')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Stack() {
            Progress({ value: this.progressValue, total: 100, type: ProgressType.Ring })
              .width(70)
              .height(70)
              .color('#96CEB4')
              .style({ strokeWidth: 4, enableSmoothEffect: true })

            Text(this.progressValue.toFixed(0))
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(70)
          .height(70)

          Text('Thin Ring')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Progress({ value: this.progressValue, total: 100, type: ProgressType.ScaleRing })
            .width(70)
            .height(70)
            .color('#DDA0DD')
            .style({ strokeWidth: 6, scaleCount: 20, scaleWidth: 2 })

          Text('Scale Ring')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Progress({ value: this.progressValue, total: 100, type: ProgressType.Capsule })
            .width(70)
            .height(30)
            .color('#FF8C00')
            .style({ strokeWidth: 20 })

          Text('Capsule')
            .fontSize(12)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Slider({
        value: this.progressValue,
        min: 0,
        max: 100,
        step: 1
      })
        .width('90%')
        .onChange((value: number) => {
          this.progressValue = value
        })

      Text('Progress: ' + this.progressValue.toFixed(0) + '%')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 5. Ring Progress Section
  // ============================================================
  @Builder
  RingProgressSection() {
    Column({ space: 12 }) {
      Text('Custom Ring Progress')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(100)
              .fillColor('#E8E8E8')

            Image($r('app.media.testSvg'))
              .width(100)
              .height(100)
              .fillColor('#4ECDC4')
              .clip(new Circle({ width: 100, height: 100 }))

            Text(this.ringProgress.toFixed(0) + '%')
              .fontSize(22)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(100)
          .height(100)

          Text('Full Ring')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .fillColor('#E8E8E8')

            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .fillColor('#FF6B6B')
              .clip(new Ellipse({ width: 100, height: this.halfRingProgress }))

            Text(this.halfRingProgress.toFixed(0) + '%')
              .fontSize(22)
              .fontWeight(FontWeight.Bold)
              .fontColor('#333333')
          }
          .width(100)
          .height(100)

          Text('Vertical Fill')
            .fontSize(12)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Text('Full:')
          .fontSize(12)
          .width(50)
        Slider({
          value: this.ringProgress,
          min: 0,
          max: 100,
          step: 1
        })
          .width('60%')
          .onChange((value: number) => {
            this.ringProgress = value
          })
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('Half:')
          .fontSize(12)
          .width(50)
        Slider({
          value: this.halfRingProgress,
          min: 0,
          max: 100,
          step: 1
        })
          .width('60%')
          .onChange((value: number) => {
            this.halfRingProgress = value
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 6. Wave Progress Section
  // ============================================================
  @Builder
  WaveProgressSection() {
    Column({ space: 12 }) {
      Text('Wave Progress')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Stack() {
          Image($r('app.media.testSvg'))
            .width(130)
            .height(130)
            .fillColor('#87CEEB')
            .opacity(0.2)
            .borderRadius(65)
            .clip(true)

          Stack() {
            Image($r('app.media.icon'))
              .width(200)
              .height(200)
              .fillColor('#4ECDC4')
              .opacity(0.5)
          }
          .width(130)
          .height(130)
          .clip(new Circle({ width: 130, height: 130 }))
          .alignContent(Alignment.Bottom)

          Text(this.waveProgress.toFixed(0) + '%')
            .fontSize(28)
            .fontWeight(FontWeight.Bold)
            .fontColor('#FFFFFF')
            .shadow({ radius: 2, color: '#333333', offsetX: 0, offsetY: 1 })
        }
        .width(130)
        .height(130)
        .borderRadius(65)
        .border({ width: 3, color: '#4ECDC4' })

        Stack() {
          Image($r('app.media.svg'))
            .width(130)
            .height(130)
            .fillColor('#FF6B6B')
            .opacity(0.2)
            .borderRadius(10)
            .clip(true)

          Stack() {
            Image($r('app.media.star'))
              .width(200)
              .height(200)
              .fillColor('#FF6B6B')
              .opacity(0.5)
          }
          .width(130)
          .height(130)
          .clip(new Rect({ width: 130, height: 130 }))
          .alignContent(Alignment.Bottom)

          Text(this.waveProgress.toFixed(0) + '%')
            .fontSize(28)
            .fontWeight(FontWeight.Bold)
            .fontColor('#FFFFFF')
            .shadow({ radius: 2, color: '#333333', offsetX: 0, offsetY: 1 })
        }
        .width(130)
        .height(130)
        .borderRadius(10)
        .border({ width: 3, color: '#FF6B6B' })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Slider({
        value: this.waveProgress,
        min: 0,
        max: 100,
        step: 1
      })
        .width('90%')
        .onChange((value: number) => {
          this.waveProgress = value
        })

      Text('Wave Level: ' + this.waveProgress.toFixed(0) + '%')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 7. Pie Chart Section
  // ============================================================
  @Builder
  PieChartSection() {
    Column({ space: 12 }) {
      Text('Pie Chart')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Stack() {
        ForEach(this.pieData, (item: PieDataItem, index: number) => {
          Image($r('app.media.icon'))
            .width(this.selectedPieIndex === index ? 160 : 140)
            .height(this.selectedPieIndex === index ? 160 : 140)
            .fillColor(item.color)
            .opacity(this.selectedPieIndex === -1 || this.selectedPieIndex === index ? 1.0 : 0.4)
            .animation({ duration: 300, curve: Curve.EaseInOut })
        })
      }
      .width(160)
      .height(160)
      .clip(new Circle({ width: 160, height: 160 }))

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center }) {
        ForEach(this.pieData, (item: PieDataItem, index: number) => {
          Row({ space: 6 }) {
            Image($r('app.media.icon'))
              .width(12)
              .height(12)
              .fillColor(item.color)

            Text(item.label + ' (' + item.value + '%)')
              .fontSize(12)
              .fontColor(this.selectedPieIndex === index ? '#333333' : '#888888')
              .fontWeight(this.selectedPieIndex === index ? FontWeight.Bold : FontWeight.Normal)
          }
          .padding(6)
          .borderRadius(8)
          .backgroundColor(this.selectedPieIndex === index ? '#F0F0F0' : Color.Transparent)
          .onClick(() => {
            this.selectedPieIndex = this.selectedPieIndex === index ? -1 : index
          })
        })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 8. Bar Chart Section
  // ============================================================
  @Builder
  BarChartSection() {
    Column({ space: 12 }) {
      Text('Bar Chart')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      // Bar chart using SVG icons as bars
      Row({ space: 6 }) {
        ForEach(this.barData, (item: BarDataItem, index: number) => {
          Column({ space: 4 }) {
            Stack() {
              Image($r('app.media.icon'))
                .width(24)
                .height(120)
                .fillColor('#E8E8E8')

              Image($r('app.media.icon'))
                .width(24)
                .height(item.value * 1.2)
                .fillColor(item.color)
                .opacity(this.selectedBarIndex === -1 || this.selectedBarIndex === index ? 1.0 : 0.4)
            }
            .width(24)
            .height(120)
            .alignContent(Alignment.Bottom)
            .onClick(() => {
              this.selectedBarIndex = this.selectedBarIndex === index ? -1 : index
            })

            Text(item.label)
              .fontSize(10)
              .fontColor('#888888')

            Text(item.value.toString())
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
              .fontColor(item.color)
          }
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .height(160)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 9. Stepper Section
  // ============================================================
  @Builder
  StepperSection() {
    Column({ space: 12 }) {
      Text('Custom Stepper')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 0 }) {
        ForEach(this.steps, (step: StepItem, index: number) => {
          Row({ space: 0 }) {
            // Connector line before step (except first)
            if (index > 0) {
              Row()
                .width(30)
                .height(3)
                .backgroundColor(index <= this.currentStep ? '#4ECDC4' : '#E0E0E0')
            }

            Column({ space: 4 }) {
              Stack() {
                Image(step.icon)
                  .width(36)
                  .height(36)
                  .fillColor(
                    step.completed ? '#4ECDC4' :
                    step.active ? '#FF6B6B' :
                    '#CCCCCC'
                  )

                if (step.completed) {
                  Image($r('app.media.icon'))
                    .width(14)
                    .height(14)
                    .fillColor(Color.White)
                }
              }
              .width(36)
              .height(36)
              .borderRadius(18)
              .border({
                width: step.active ? 2 : 0,
                color: '#FF6B6B'
              })

              Text(step.title)
                .fontSize(10)
                .fontColor(
                  step.completed ? '#4ECDC4' :
                  step.active ? '#FF6B6B' :
                  '#CCCCCC'
                )
                .fontWeight(step.active ? FontWeight.Bold : FontWeight.Normal)
            }
            .alignItems(HorizontalAlign.Center)
          }
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 4 }) {
        Text('Current: ')
          .fontSize(12)
          .fontColor('#888888')
        Text(this.steps[this.currentStep].title + ' - ' + this.steps[this.currentStep].desc)
          .fontSize(12)
          .fontColor('#333333')
          .fontWeight(FontWeight.Medium)
      }

      Row({ space: 10 }) {
        Button('Previous')
          .fontSize(12)
          .enabled(this.currentStep > 0)
          .onClick(() => {
            if (this.currentStep > 0) {
              this.steps[this.currentStep].active = false
              this.currentStep--
              this.steps[this.currentStep].active = true
              this.steps[this.currentStep].completed = false
            }
          })

        Button('Next')
          .fontSize(12)
          .enabled(this.currentStep < this.steps.length - 1)
          .onClick(() => {
            if (this.currentStep < this.steps.length - 1) {
              this.steps[this.currentStep].completed = true
              this.steps[this.currentStep].active = false
              this.currentStep++
              this.steps[this.currentStep].active = true
            }
          })

        Button('Reset')
          .fontSize(12)
          .onClick(() => {
            this.currentStep = 0
            this.steps.forEach((step, i) => {
              step.completed = i === 0 ? false : false
              step.active = i === 0
            })
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 10. Timeline Section
  // ============================================================
  @Builder
  TimelineSection() {
    Column({ space: 12 }) {
      Text('Timeline')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Column({ space: 0 }) {
        // Timeline item 1
        Row({ space: 12 }) {
          Column() {
            Image($r('app.media.icon'))
              .width(24)
              .height(24)
              .fillColor('#4ECDC4')

            Row()
              .width(2)
              .height(40)
              .backgroundColor('#4ECDC4')
          }
          .alignItems(HorizontalAlign.Center)

          Column({ space: 2 }) {
            Text('Order Placed')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')
            Text('Your order has been confirmed')
              .fontSize(12)
              .fontColor('#888888')
            Text('10:30 AM')
              .fontSize(10)
              .fontColor('#BBBBBB')
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')

        // Timeline item 2
        Row({ space: 12 }) {
          Column() {
            Image($r('app.media.icon'))
              .width(24)
              .height(24)
              .fillColor('#FF6B6B')

            Row()
              .width(2)
              .height(40)
              .backgroundColor('#FF6B6B')
          }
          .alignItems(HorizontalAlign.Center)

          Column({ space: 2 }) {
            Text('Processing')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')
            Text('Your order is being prepared')
              .fontSize(12)
              .fontColor('#888888')
            Text('11:15 AM')
              .fontSize(10)
              .fontColor('#BBBBBB')
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')

        // Timeline item 3
        Row({ space: 12 }) {
          Column() {
            Image($r('app.media.icon'))
              .width(24)
              .height(24)
              .fillColor('#45B7D1')

            Row()
              .width(2)
              .height(40)
              .backgroundColor('#E0E0E0')
          }
          .alignItems(HorizontalAlign.Center)

          Column({ space: 2 }) {
            Text('Shipped')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')
            Text('Package is on the way')
              .fontSize(12)
              .fontColor('#888888')
            Text('2:45 PM')
              .fontSize(10)
              .fontColor('#BBBBBB')
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')

        // Timeline item 4
        Row({ space: 12 }) {
          Column() {
            Image($r('app.media.icon'))
              .width(24)
              .height(24)
              .fillColor('#E0E0E0')
          }
          .alignItems(HorizontalAlign.Center)

          Column({ space: 2 }) {
            Text('Delivered')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#CCCCCC')
            Text('Pending delivery')
              .fontSize(12)
              .fontColor('#CCCCCC')
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 11. Tree View Section
  // ============================================================
  @Builder
  TreeViewSection() {
    Column({ space: 12 }) {
      Text('Tree View')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Column({ space: 4 }) {
        this.TreeNodeBuilder(this.treeNodes[0], 0)
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#FAFAFA')
      .borderRadius(8)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  @Builder
  TreeNodeBuilder(node: TreeNode, depth: number) {
    Column({ space: 2 }) {
      Row({ space: 8 }) {
        Row()
          .width(depth * 20)

        if (node.children.length > 0) {
          Image($r('app.media.icon'))
            .width(16)
            .height(16)
            .fillColor('#888888')
            .rotate({ angle: node.expanded ? 90 : 0 })
            .animation({ duration: 200, curve: Curve.EaseInOut })
        } else {
          Row()
            .width(16)
            .height(16)
        }

        if (node.icon) {
          Image(node.icon)
            .width(20)
            .height(20)
            .fillColor(node.children.length > 0 ? '#FF8C00' : '#4ECDC4')
        }

        Text(node.name)
          .fontSize(14)
          .fontColor('#333333')
      }
      .width('100%')
      .height(36)
      .padding({ left: 8, right: 8 })
      .borderRadius(6)
      .backgroundColor(this.hoverIndex === depth * 100 + node.name.length ? '#F0F0F0' : Color.Transparent)
      .onClick(() => {
        if (node.children.length > 0) {
          this.toggleTreeNode(node)
        }
      })

      if (node.expanded && node.children.length > 0) {
        Column({ space: 2 }) {
          ForEach(node.children, (child: TreeNode) => {
            this.TreeNodeBuilder(child, depth + 1)
          })
        }
        .width('100%')
        .margin({ left: 12 })
      }
    }
    .width('100%')
  }

  // ============================================================
  // 12. Tab Section
  // ============================================================
  @Builder
  TabSection() {
    Column({ space: 12 }) {
      Text('Tab Navigation')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 0 }) {
        ForEach(['Overview', 'Analytics', 'Settings'], (tab: string, index: number) => {
          Column({ space: 4 }) {
            Text(tab)
              .fontSize(14)
              .fontColor(this.selectedTab === index ? '#4ECDC4' : '#888888')
              .fontWeight(this.selectedTab === index ? FontWeight.Bold : FontWeight.Normal)

            Row()
              .width(40)
              .height(3)
              .borderRadius(2)
              .backgroundColor(this.selectedTab === index ? '#4ECDC4' : Color.Transparent)
          }
          .padding({ left: 12, right: 12, top: 8, bottom: 8 })
          .onClick(() => {
            this.selectedTab = index
          })
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      if (this.selectedTab === 0) {
        this.OverviewTabContent()
      } else if (this.selectedTab === 1) {
        this.AnalyticsTabContent()
      } else {
        this.SettingsTabContent()
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  @Builder
  OverviewTabContent() {
    Column({ space: 8 }) {
      Row({ space: 10 }) {
        Image($r('app.media.testSvg'))
          .width(40)
          .height(40)
          .fillColor('#4ECDC4')

        Column({ space: 2 }) {
          Text('System Status')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('All services operational')
            .fontSize(12)
            .fontColor('#4CAF50')
        }
        .alignItems(HorizontalAlign.Start)
      }

      Row({ space: 10 }) {
        Image($r('app.media.icon'))
          .width(40)
          .height(40)
          .fillColor('#45B7D1')

        Column({ space: 2 }) {
          Text('Active Users')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('1,234 users online')
            .fontSize(12)
            .fontColor('#888888')
        }
        .alignItems(HorizontalAlign.Start)
      }
    }
    .width('100%')
    .padding(10)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  AnalyticsTabContent() {
    Column({ space: 8 }) {
      Row({ space: 10 }) {
        Image($r('app.media.svg'))
          .width(40)
          .height(40)
          .fillColor('#FF6B6B')

        Column({ space: 2 }) {
          Text('Page Views')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('45,678 views today')
            .fontSize(12)
            .fontColor('#888888')
        }
        .alignItems(HorizontalAlign.Start)
      }

      Row({ space: 10 }) {
        Image($r('app.media.star'))
          .width(40)
          .height(40)
          .fillColor('#96CEB4')

        Column({ space: 2 }) {
          Text('Conversion Rate')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('3.2% (+0.5%)')
            .fontSize(12)
            .fontColor('#4CAF50')
        }
        .alignItems(HorizontalAlign.Start)
      }
    }
    .width('100%')
    .padding(10)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  SettingsTabContent() {
    Column({ space: 8 }) {
      Row({ space: 10 }) {
        Image($r('app.media.icon'))
          .width(40)
          .height(40)
          .fillColor('#888888')

        Column({ space: 2 }) {
          Text('Notifications')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('Push & Email enabled')
            .fontSize(12)
            .fontColor('#888888')
        }
        .alignItems(HorizontalAlign.Start)
      }

      Row({ space: 10 }) {
        Image($r('app.media.icon'))
          .width(40)
          .height(40)
          .fillColor('#888888')

        Column({ space: 2 }) {
          Text('Theme')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('Light mode')
            .fontSize(12)
            .fontColor('#888888')
        }
        .alignItems(HorizontalAlign.Start)
      }
    }
    .width('100%')
    .padding(10)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  // ============================================================
  // 13. Sidebar Section
  // ============================================================
  @Builder
  SidebarSection() {
    Column({ space: 12 }) {
      Text('Sidebar Navigation')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row() {
        // Sidebar
        Column({ space: 8 }) {
          Image($r('app.media.icon'))
            .width(this.collapsedSideBar ? 24 : 32)
            .height(this.collapsedSideBar ? 24 : 32)
            .fillColor('#4ECDC4')

          Divider()
            .color('#E0E0E0')

          ForEach(['Home', 'Dashboard', 'Profile', 'Settings'], (item: string) => {
            Row({ space: 8 }) {
              Image($r('app.media.icon'))
                .width(20)
                .height(20)
                .fillColor('#888888')

              if (!this.collapsedSideBar) {
                Text(item)
                  .fontSize(12)
                  .fontColor('#333333')
              }
            }
            .width('100%')
            .padding(8)
            .borderRadius(6)
          })
        }
        .width(this.collapsedSideBar ? 50 : 120)
        .height(200)
        .padding(8)
        .backgroundColor('#FAFAFA')
        .borderRadius({ topLeft: 8, bottomLeft: 8 })
        .justifyContent(FlexAlign.Start)
        .animation({ duration: 300, curve: Curve.EaseInOut })

        // Main content area
        Column({ space: 8 }) {
          Image($r('app.media.testSvg'))
            .width(60)
            .height(60)
            .fillColor('#45B7D1')

          Text('Content Area')
            .fontSize(14)
            .fontColor('#888888')
        }
        .layoutWeight(1)
        .height(200)
        .padding(12)
        .backgroundColor(Color.White)
        .borderRadius({ topRight: 8, bottomRight: 8 })
        .justifyContent(FlexAlign.Center)
        .alignItems(HorizontalAlign.Center)
      }
      .width('100%')
      .border({ width: 1, color: '#E0E0E0', radius: 8 })

      Button(this.collapsedSideBar ? 'Expand' : 'Collapse')
        .fontSize(12)
        .onClick(() => {
          this.collapsedSideBar = !this.collapsedSideBar
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 14. Notification Section
  // ============================================================
  @Builder
  NotificationSection() {
    Column({ space: 12 }) {
      Text('Notification Icons')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Stack() {
          Image($r('app.media.icon'))
            .width(36)
            .height(36)
            .fillColor('#888888')

          if (this.notificationCount > 0) {
            Text(this.notificationCount > 9 ? '9+' : this.notificationCount.toString())
              .fontSize(8)
              .fontColor(Color.White)
              .fontWeight(FontWeight.Bold)
              .textAlign(TextAlign.Center)
              .width(16)
              .height(16)
              .borderRadius(8)
              .backgroundColor('#FF6B6B')
              .position({ x: 24, y: -4 })
          }
        }
        .width(36)
        .height(36)

        Stack() {
          Image($r('app.media.testSvg'))
            .width(36)
            .height(36)
            .fillColor('#888888')

          if (this.notificationCount > 3) {
            Row()
              .width(8)
              .height(8)
              .borderRadius(4)
              .backgroundColor('#FF6B6B')
              .position({ x: 28, y: 0 })
          }
        }
        .width(36)
        .height(36)

        Stack() {
          Image($r('app.media.icon'))
            .width(36)
            .height(36)
            .fillColor('#888888')

          Image($r('app.media.icon'))
            .width(16)
            .height(16)
            .fillColor('#FF6B6B')
            .position({ x: 22, y: -4 })
        }
        .width(36)
        .height(36)
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Button('Add')
          .fontSize(12)
          .onClick(() => {
            this.notificationCount = Math.min(this.notificationCount + 1, 15)
          })

        Button('Clear')
          .fontSize(12)
          .onClick(() => {
            this.notificationCount = 0
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('Notifications: ' + this.notificationCount)
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
  }

  // ============================================================
  // 15. Badge Section
  // ============================================================
  @Builder
  BadgeSection() {
    Column({ space: 12 }) {
      Text('Badge Component')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Badge({ count: this.badgeNumber, maxCount: 99, style: { badgeSize: 16, badgeColor: '#FF6B6B' } }) {
            Image($r('app.media.icon'))
              .width(48)
              .height(48)
              .fillColor('#4ECDC4')
          }

          Text('Messages')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Badge({ count: 1, maxCount: 99, style: { badgeSize: 12, badgeColor: '#FF8C00' } }) {
            Image($r('app.media.testSvg'))
              .width(48)
              .height(48)
              .fillColor('#45B7D1')
          }

          Text('Alerts')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Badge({ count: 99, maxCount: 99, style: { badgeSize: 20, badgeColor: '#F44336' } }) {
            Image($r('app.media.svg'))
              .width(48)
              .height(48)
              .fillColor('#96CEB4')
          }

          Text('Updates')
            .fontSize(12)
            .fontColor('#888888')
        }

        Column({ space: 5 }) {
          Badge({ value: 'NEW', style: { badgeSize: 16, badgeColor: '#DDA0DD' } }) {
            Image($r('app.media.star'))
              .width(48)
              .height(48)
              .fillColor('#DDA0DD')
          }

          Text('New')
            .fontSize(12)
            .fontColor('#888888')
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('+')
          .fontSize(12)
          .width(40)
          .onClick(() => {
            this.badgeNumber = Math.min(this.badgeNumber + 1, 99)
          })

        Button('-')
          .fontSize(12)
          .width(40)
          .onClick(() => {
            this.badgeNumber = Math.max(this.badgeNumber - 1, 0)
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12)
    .margin({ bottom: 20 })
  }
}