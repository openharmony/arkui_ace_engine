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

interface ListItemGroupData {
  header: string;
  items: string[];
}

interface WaterFlowItem {
  id: number;
  height: number;
  color: string;
}

interface SwipeItem {
  id: number;
  title: string;
}

interface DragItem {
  id: number;
  value: number;
}

interface LazyItem {
  id: number;
}

class LazyDataSource implements IDataSource {
  private data: LazyItem[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(count: number) {
    for (let i = 0; i < count; i++) {
      this.data.push({ id: i });
    }
  }

  totalCount(): number {
    return this.data.length;
  }

  getData(index: number): LazyItem {
    return this.data[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }
}

@Component
struct RectDemo {
  @State rectWidth: number = 150
  @State rectHeight: number = 100
  @State rectColor: string = '#45B7D1'
  @State rectRadius: number = 0

  build() {
    Column() {
      Text('Rect Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Rect({ width: this.rectWidth, height: this.rectHeight })
        .fill(this.rectColor)
        .radius(this.rectRadius)
        .margin({ bottom: 15 })

      Text('Size: ' + this.rectWidth + ' x ' + this.rectHeight + ', Radius: ' + this.rectRadius)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.rectWidth = Math.min(this.rectWidth + 10, 250)
          })

        Button('Width -')
          .onClick(() => {
            this.rectWidth = Math.max(this.rectWidth - 10, 50)
          })
        Button('Height +')
          .onClick(() => {
            this.rectHeight = Math.min(this.rectHeight + 10, 200)
          })
        Button('Height -')
          .onClick(() => {
            this.rectHeight = Math.max(this.rectHeight - 10, 30)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Radius +')
          .onClick(() => {
            this.rectRadius = Math.min(this.rectRadius + 5, 50)
          })
        Button('Radius -')
          .onClick(() => {
            this.rectRadius = Math.max(this.rectRadius - 5, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PathDemo {
  @State pathScale: number = 1.0

  build() {
    Column() {
      Text('Path Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Path()
        .width(200)
        .height(200)
        .commands('M 50 50 L 150 50 L 150 150 L 50 150 Z')
        .fill('#96CEB4')
        .stroke('#FF6B6B')
        .strokeWidth(2)
        .scale({ x: this.pathScale, y: this.pathScale })
        .margin({ bottom: 15 })
      Text('Scale: ' + this.pathScale.toFixed(2))
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Scale +')
          .onClick(() => {
            this.pathScale = Math.min(this.pathScale + 0.1, 2.0)
          })
        Button('Scale -')
          .onClick(() => {
            this.pathScale = Math.max(this.pathScale - 0.1, 0.5)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PolygonDemo {
  @State polygonSides: number = 6
  @State polygonRadius: number = 80
  @State polygonColor: string = '#FFEAA7'

  build() {
    Column() {
      Text('Polygon Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Polygon({ points: this.getPolygonPoints(this.polygonSides, this.polygonRadius) })
        .fill(this.polygonColor)
        .stroke('#DDA0DD')
        .strokeWidth(2)
        .margin({ bottom: 15 })

      Text('Sides: ' + this.polygonSides + ', Radius: ' + this.polygonRadius)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Sides +')
          .onClick(() => {
            this.polygonSides = Math.min(this.polygonSides + 1, 12)
          })
        Button('Sides -')
          .onClick(() => {
            this.polygonSides = Math.max(this.polygonSides - 1, 3)
          })
        Button('Radius +')
          .onClick(() => {
            this.polygonRadius = Math.min(this.polygonRadius + 10, 100)
          })
        Button('Radius -')
          .onClick(() => {
            this.polygonRadius = Math.max(this.polygonRadius - 10, 30)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  private getPolygonPoints(sides: number, radius: number): string {
    let points = ''
    const centerX = 100
    const centerY = 100

    for (let i = 0; i < sides; i++) {
      const angle = (i * 2 * Math.PI) / sides - Math.PI / 2
      const x = centerX + radius * Math.cos(angle)
      const y = centerY + radius * Math.sin(angle)
      points += x + ',' + y + ' '
    }
    return points.trim()
  }
}

@Component
struct PolylineDemo {
  @State linePoints: string = '50,50 150,50 150,150 50,150'
  @State strokeWidth: number = 2
  @State strokeColor: string = '#FF6B6B'

  build() {
    Column() {
      Text('Polyline Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Polyline({ points: this.linePoints })
        .width(200)
        .height(200)
        .stroke(this.strokeColor)
        .strokeWidth(this.strokeWidth)
        .margin({ bottom: 15 })
      Text('Stroke Width: ' + this.strokeWidth)
        .fontSize(14)
        .margin({ bottom: 10 })
      Row() {
        Button('Width +')
          .onClick(() => {
            this.strokeWidth = Math.min(this.strokeWidth + 1, 10)
          })
        Button('Width -')
          .onClick(() => {
            this.strokeWidth = Math.max(this.strokeWidth - 1, 1)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ImageAnimatorDemo {
  @State isPlaying: boolean = false
  @State currentFrame: number = 0

  build() {
    Column() {
      Text('Image Animator Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      ImageAnimator()
        .images([$r('app.media.icon')])
        .state(this.isPlaying ? AnimationStatus.Running : AnimationStatus.Paused)
        .duration(1000)
        .iterations(-1)
        .width(200)
        .height(200)
        .margin({ bottom: 15 })

      Text('Current Frame: ' + this.currentFrame)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button(this.isPlaying ? 'Pause' : 'Play')
          .onClick(() => {
            this.isPlaying = !this.isPlaying
          })

        Button('Stop')
          .onClick(() => {
            this.isPlaying = false
            this.currentFrame = 0
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct VideoDemo {
  @State isPlaying: boolean = false
  @State currentTime: number = 0
  @State duration: number = 100
  private videoController: VideoController = new VideoController()

  build() {
    Column() {
      Text('Video Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Video({
        src: $r('app.media.icon'),
        controller: this.videoController
      })
      .width('100%')
      .height(200)
      .autoPlay(false)
      .controls(true)
      .loop(false)
      .margin({ bottom: 15 })

      Text('Time: ' + this.currentTime + ' / ' + this.duration)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button(this.isPlaying ? 'Pause' : 'Play')
          .onClick(() => {
            this.isPlaying = !this.isPlaying
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct WebDemo {
  @State currentUrl: string = 'https://www.example.com'
  @State canGoBack: boolean = false
  @State canGoForward: boolean = false
  private webController: WebController = new WebController()

  build() {
    Column() {
      Text('Web Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Web({ src: this.currentUrl, controller: this.webController })
        .width('100%')
        .height(200)
        .margin({ bottom: 15 })

      TextInput({ placeholder: 'Enter URL...' })
        .onChange((value: string) => {
          this.currentUrl = value
        })
        .margin({ bottom: 10 })

      Row() {
        Button('Back')
          .enabled(this.canGoBack)
          .onClick(() => {
            this.canGoBack = false
          })

        Button('Forward')
          .enabled(this.canGoForward)
          .onClick(() => {
            this.canGoForward = false
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct CanvasDemo {
  @State canvasWidth: number = 300
  @State canvasHeight: number = 200
  private settings: RenderingContextSettings = new RenderingContextSettings(true)

  build() {
    Column() {
      Text('Canvas Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Canvas(this.settings)
        .width(this.canvasWidth)
        .height(this.canvasHeight)
        .backgroundColor('#FFFFFF')
        .onReady(() => {
          this.drawCanvas()
        })
        .margin({ bottom: 15 })

      Text('Size: ' + this.canvasWidth + ' x ' + this.canvasHeight)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.canvasWidth = Math.min(this.canvasWidth + 20, 400)
          })

        Button('Width -')
          .onClick(() => {
            this.canvasWidth = Math.max(this.canvasWidth - 20, 100)
          })

        Button('Height +')
          .onClick(() => {
            this.canvasHeight = Math.min(this.canvasHeight + 20, 300)
          })

        Button('Height -')
          .onClick(() => {
            this.canvasHeight = Math.max(this.canvasHeight - 20, 100)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  private drawCanvas(): void {
    console.log('Canvas ready for drawing')
  }
}

@Component
struct XComponentDemo {
  @State componentType: string = 'Surface'

  build() {
    Column() {
      Text('XComponent Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      XComponent({ id: 'xcomponent', type: this.componentType === 'Surface' ? XComponentType.SURFACE : XComponentType.TEXTURE })
        .width('100%')
        .height(200)
        .onLoad(() => {
          console.log('XComponent loaded')
        })
        .margin({ bottom: 15 })

      Text('Type: ' + this.componentType)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('Surface')
          .onClick(() => {
            this.componentType = 'Surface'
          })

        Button('Texture')
          .onClick(() => {
            this.componentType = 'Texture'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct AlphabetIndexerDemo {
  @State selectedValue: string = 'A'
  @State selectedIndex: number = 0
  private arrayValue: string[] = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

  build() {
    Column() {
      Text('Alphabet Indexer Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Stack({ alignContent: Alignment.End }) {
        List() {
          ForEach(this.arrayValue, (item: string) => {
            ListItem() {
              Text('Item ' + item)
                .fontSize(16)
                .padding(10)
                .width('100%')
            }
          })
        }
        .width('100%')
        .height(300)

        AlphabetIndexer({ arrayValue: this.arrayValue, selected: this.selectedIndex })
          .onSelected((index: number) => {
            this.selectedIndex = index
            this.selectedValue = this.arrayValue[index]
          })
      }
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })

      Text('Selected: ' + this.selectedValue)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ListItemGroupDemo {
  private groups: ListItemGroupData[] = [
    {
      header: 'Group A',
      items: ['Item A1', 'Item A2', 'Item A3']
    },
    {
      header: 'Group B',
      items: ['Item B1', 'Item B2']
    },
    {
      header: 'Group C',
      items: ['Item C1', 'Item C2', 'Item C3', 'Item C4']
    }
  ]

  build() {
    Column() {
      Text('List Item Group Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      List() {
        ForEach(this.groups, (group: ListItemGroupData) => {
          ListItemGroup({ header: this.groupHeader(group.header) }) {
            ForEach(group.items, (item: string) => {
              ListItem() {
                Text(item)
                  .fontSize(16)
                  .padding(10)
                  .width('100%')
              }
            })
          }
        })
      }
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })

      Text('Total Groups: ' + this.groups.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  @Builder
  groupHeader(title: string) {
    Text(title)
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
      .padding(10)
      .width('100%')
      .backgroundColor('#E5E5E5')
  }
}

@Component
struct WaterFlowDemo {
  private items: WaterFlowItem[] = Array.from({ length: 20 }, (_, i) => ({
    id: i,
    height: 100 + (i % 4) * 50,
    color: ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4'][i % 4]
  }))

  build() {
    Column() {
      Text('Water Flow Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      WaterFlow() {
        ForEach(this.items, (item: WaterFlowItem) => {
          FlowItem() {
            Text('Item ' + item.id)
              .fontSize(16)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
              .backgroundColor(item.color)
          }
          .height(item.height)
        })
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(10)
      .columnsGap(10)
      .width('100%')
      .height(400)
      .margin({ bottom: 15 })

      Text('Total Items: ' + this.items.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GridColDemo {
  @State columns: string = '1fr 1fr 1fr'

  build() {
    Column() {
      Text('Grid Col Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          GridItem() {
            Text('' + item)
              .fontSize(24)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
              .backgroundColor('#FF6B6B')
          }
        })
      }
      .columnsTemplate(this.columns)
      .rowsTemplate('1fr 1fr')
      .width('100%')
      .height(200)
      .margin({ bottom: 15 })

      Text('Columns: ' + this.columns)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('2 Columns')
          .onClick(() => {
            this.columns = '1fr 1fr'
          })

        Button('3 Columns')
          .onClick(() => {
            this.columns = '1fr 1fr 1fr'
          })

        Button('4 Columns')
          .onClick(() => {
            this.columns = '1fr 1fr 1fr 1fr'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GridRowDemo {
  @State rows: string = '1fr 1fr'

  build() {
    Column() {
      Text('Grid Row Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          GridItem() {
            Text('' + item)
              .fontSize(24)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
              .backgroundColor('#4ECDC4')
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate(this.rows)
      .width('100%')
      .height(200)
      .margin({ bottom: 15 })

      Text('Rows: ' + this.rows)
        .fontSize(14)
        .margin({ bottom: 10 })

      Row() {
        Button('2 Rows')
          .onClick(() => {
            this.rows = '1fr 1fr'
          })

        Button('3 Rows')
          .onClick(() => {
            this.rows = '1fr 1fr 1fr'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct RelativeContainerDemo {
  @State containerWidth: number = 300
  @State containerHeight: number = 200

  build() {
    Column() {
      Text('Relative Container Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      RelativeContainer() {
        Text('Top Left')
          .fontSize(14)
          .width(80)
          .height(40)
          .backgroundColor('#FF6B6B')
          .id('item1')
          .alignRules({
            top: { anchor: '__container__', align: VerticalAlign.Top },
            left: { anchor: '__container__', align: HorizontalAlign.Start }
          })

        Text('Bottom Right')
          .fontSize(14)
          .width(80)
          .height(40)
          .backgroundColor('#4ECDC4')
          .id('item2')
          .alignRules({
            bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
            right: { anchor: '__container__', align: HorizontalAlign.End }
          })
      }
      .width(this.containerWidth)
      .height(this.containerHeight)
      .backgroundColor('#F0F0F0')
      .margin({ bottom: 15 })

      Text('Size: ' + this.containerWidth + ' x ' + this.containerHeight)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SideBarContainerDemo {
  @State showSideBar: boolean = false

  build() {
    Column() {
      Text('Side Bar Container Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Button('Toggle Side Bar')
        .onClick(() => {
          this.showSideBar = !this.showSideBar
        })
        .margin({ bottom: 15 })

      SideBarContainer(SideBarContainerType.Embed) {
        Column() {
          Text('Main Content')
            .fontSize(16)
        }
        .width('100%')
        .height('100%')
        .backgroundColor('#FFFFFF')
      }
      .sideBarWidth(200)
      .showSideBar(this.showSideBar)
      .height(200)
      .width('100%')
      .controlButton({
        sideBar: '',
        showSideBar: '',
        hideSideBar: ''
      })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct NavigationStackDemo {
  @State stackDepth: number = 1

  build() {
    Column() {
      Text('Navigation Stack Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Stack Depth: ' + this.stackDepth)
        .fontSize(14)
        .margin({ bottom: 15 })

      Row() {
        Button('Push')
          .onClick(() => {
            this.stackDepth++
          })

        Button('Pop')
          .onClick(() => {
            this.stackDepth = Math.max(this.stackDepth - 1, 1)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct StepperDemo {
  @State currentStep: number = 0
  private totalSteps: number = 3

  build() {
    Column() {
      Text('Stepper Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Stepper() {
        StepperItem() {
          Text('Step 1 Content')
            .fontSize(16)
        }
        .nextLabel('Next')
        StepperItem() {
          Text('Step 2 Content')
            .fontSize(16)
        }
        .nextLabel('Next')
        .prevLabel('Previous')
        StepperItem() {
          Text('Step 3 Content')
            .fontSize(16)
        }
        .prevLabel('Previous')
      }
      .index(this.currentStep)
      .onChange((index: number) => {
        this.currentStep = index
      })
      .margin({ bottom: 15 })
      Text('Current Step: ' + (this.currentStep + 1) + ' / ' + this.totalSteps)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct TabsDemo {
  @State currentTab: number = 0
  private tabTitles: string[] = ['Tab 1', 'Tab 2', 'Tab 3', 'Tab 4']

  build() {
    Column() {
      Text('Tabs Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Tabs({ index: this.currentTab }) {
        ForEach(this.tabTitles, (title: string, index: number) => {
TabContent() {
            Text(title + ' Content')
              .fontSize(16)
          }
          .tabBar(title)
        })
      }
      .width('100%')
      .height(200)
      .onChange((index: number) => {
        this.currentTab = index
      })
      .margin({ bottom: 15 })
      Text('Current Tab: ' + this.tabTitles[this.currentTab])
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct SwiperDemo {
  @State currentIndex: number = 0
  private items: string[] = ['Slide 1', 'Slide 2', 'Slide 3', 'Slide 4', 'Slide 5']

  build() {
    Column() {
      Text('Swiper Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Swiper() {
        ForEach(this.items, (item: string, index: number) => {
          SwiperItem() {
            Text(item)
              .fontSize(24)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
              .backgroundColor(['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FFEAA7'][index])
          }
        })
      }
      .width('100%')
      .height(200)
      .index(this.currentIndex)
      .onChange((index: number) => {
        this.currentIndex = index
      })
      .margin({ bottom: 15 })
      Text('Current Slide: ' + (this.currentIndex + 1) + ' / ' + this.items.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ScrollbarDemo {
  @State scrollPosition: number = 0

  build() {
    Column() {
      Text('Scrollbar Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Scroll() {
        Column() {
          ForEach(Array.from({ length: 30 }, (_, i) => i), (index: number) => {
            Text('Item ' + (index + 1))
              .fontSize(16)
              .padding(10)
              .width('100%')
          })
        }
        .width('100%')
      }
      .width('100%')
      .height(200)
      .scrollBar(BarState.Auto)
      .onScroll((xOffset: number, yOffset: number) => {
        this.scrollPosition = yOffset
      })
      .margin({ bottom: 15 })
      Text('Scroll Position: ' + this.scrollPosition.toFixed(0))
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct RefreshDemo {
  @State isRefreshing: boolean = false
  @State itemCount: number = 10

  build() {
    Column() {
      Text('Refresh Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Refresh({ refreshing: this.isRefreshing, offset: 60, friction: 100 }) {
        List() {
          ForEach(Array.from({ length: this.itemCount }, (_, i) => i), (index: number) => {
            ListItem() {
              Text('Item ' + (index + 1))
                .fontSize(16)
                .padding(10)
                .width('100%')
            }
          })
        }
        .width('100%')
        .height(300)
      }
      .onStateChange((refreshing: boolean) => {
        this.isRefreshing = refreshing
        if (refreshing) {
          this.refreshData()
        }
      })
      .margin({ bottom: 15 })
      Text('Item Count: ' + this.itemCount)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  private refreshData(): void {
    setTimeout(() => {
      this.itemCount = 10
      this.isRefreshing = false
    }, 1000)
  }
}

@Component
struct ListItemSwipeDemo {
  private items: SwipeItem[] = Array.from({ length: 5 }, (_, i) => ({
    id: i,
    title: 'Item ' + (i + 1)
  }))

  build() {
    Column() {
      Text('List Item Swipe Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      List() {
        ForEach(this.items, (item: SwipeItem) => {
          ListItem() {
            Text(item.title)
              .fontSize(16)
              .padding(10)
              .width('100%')
          }
          .swipeAction({ edge: SwipeEdge.End }) {
            Button('Delete')
              .backgroundColor('#FF6B6B')
          }
        })
      }
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })
      Text('Total Items: ' + this.items.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GridItemDragDemo {
  private items: DragItem[] = Array.from({ length: 9 }, (_, i) => ({
    id: i,
    value: i + 1
  }))

  build() {
    Column() {
      Text('Grid Item Drag Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Grid() {
        ForEach(this.items, (item: DragItem) => {
          GridItem() {
            Text('' + item.value)
              .fontSize(24)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
              .backgroundColor('#FF6B6B')
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr')
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })
      Text('Total Items: ' + this.items.length)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ForEachDemo {
  @State itemCount: number = 5

  build() {
    Column() {
      Text('ForEach Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Column() {
        ForEach(Array.from({ length: this.itemCount }, (_, i) => i), (index: number) => {
          Text('Item ' + (index + 1))
            .fontSize(16)
            .padding(10)
            .width('100%')
            .backgroundColor(['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FFEAA7'][index % 5])
        })
      }
      .width('100%')
      .margin({ bottom: 15 })
      Text('Item Count: ' + this.itemCount)
        .fontSize(14)
        .margin({ bottom: 10 })
      Row() {
        Button('Add Item')
          .onClick(() => {
            this.itemCount = Math.min(this.itemCount + 1, 10)
          })
        Button('Remove Item')
          .onClick(() => {
            this.itemCount = Math.max(this.itemCount - 1, 1)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct LazyForEachDemo {
  @State itemCount: number = 20

  build() {
    Column() {
      Text('LazyForEach Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      List() {
        LazyForEach(new LazyDataSource(this.itemCount), (item: LazyItem, index: number) => {
          ListItem() {
            Text('Item ' + item.id)
              .fontSize(16)
              .padding(10)
              .width('100%')
          }
        })
      }
      .width('100%')
      .height(300)
      .margin({ bottom: 15 })
      Text('Item Count: ' + this.itemCount)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct IfElseDemo {
  @State showContent: boolean = true
  @State contentType: string = 'Text'

  build() {
    Column() {
      Text('If-Else Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      if (this.showContent) {
        if (this.contentType === 'Text') {
          Text('Text Content')
            .fontSize(16)
            .padding(10)
            .width('100%')
            .backgroundColor('#FF6B6B')
        } else if (this.contentType === 'Button') {
          Button('Button Content')
            .width('100%')
        } else {
          Image($r('app.media.icon'))
            .width(100)
            .height(100)
        }
      } else {
        Text('No Content')
          .fontSize(16)
          .padding(10)
          .width('100%')
          .backgroundColor('#E5E5E5')
      }
      .margin({ bottom: 15 })
      Row() {
        Button('Toggle Content')
          .onClick(() => {
            this.showContent = !this.showContent
          })
        Button('Change Type')
          .onClick(() => {
            if (this.contentType === 'Text') {
              this.contentType = 'Button'
            } else if (this.contentType === 'Button') {
              this.contentType = 'Image'
            } else {
              this.contentType = 'Text'
            }
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct BuilderDemo {
  @State builderType: string = 'Header'

  build() {
    Column() {
      Text('Builder Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Column() {
        if (this.builderType === 'Header') {
          this.buildHeader()
        } else if (this.builderType === 'Content') {
          this.buildContent()
        } else {
          this.buildFooter()
        }
      }
      .margin({ bottom: 15 })
      Row() {
        Button('Header')
          .onClick(() => {
            this.builderType = 'Header'
          })
        Button('Content')
          .onClick(() => {
            this.builderType = 'Content'
          })
        Button('Footer')
          .onClick(() => {
            this.builderType = 'Footer'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }

  @Builder
  buildHeader() {
    Text('Header Content')
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
      .padding(15)
      .width('100%')
      .backgroundColor('#FF6B6B')
  }

  @Builder
  buildContent() {
    Text('Main Content')
      .fontSize(16)
      .padding(15)
      .width('100%')
      .backgroundColor('#4ECDC4')
  }

  @Builder
  buildFooter() {
    Text('Footer Content')
      .fontSize(14)
      .padding(15)
      .width('100%')
      .backgroundColor('#45B7D1')
  }
}

@Component
struct CustomDialogDemo {
  @State showDialog: boolean = false

  build() {
    Column() {
      Text('Custom Dialog Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Button('Show Dialog')
        .onClick(() => {
          this.showDialog = true
        })
        .margin({ bottom: 15 })
      if (this.showDialog) {
        Column() {
          Text('Dialog Content')
            .fontSize(16)
            .margin({ bottom: 15 })
          Row() {
            Button('Cancel')
              .onClick(() => {
                this.showDialog = false
              })
            Button('Confirm')
              .onClick(() => {
                this.showDialog = false
              })
          }
          .justifyContent(FlexAlign.SpaceAround)
          .width('100%')
        }
        .width('80%')
        .padding(20)
        .backgroundColor('#FFFFFF')
        .borderRadius(10)
        .shadow({ radius: 10, color: '#000000', offsetX: 0, offsetY: 5 })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct StateManagementDemo {
  @State counter: number = 0
  @State message: string = 'Hello'
  @State isActive: boolean = true

  build() {
    Column() {
      Text('State Management Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Counter: ' + this.counter)
        .fontSize(16)
        .margin({ bottom: 10 })
      Text('Message: ' + this.message)
        .fontSize(16)
        .margin({ bottom: 10 })
      Text('Active: ' + (this.isActive ? 'Yes' : 'No'))
        .fontSize(16)
        .margin({ bottom: 15 })
      Row() {
        Button('Counter +')
          .onClick(() => {
            this.counter++
          })
        Button('Counter -')
          .onClick(() => {
            this.counter--
          })
        Button('Toggle')
          .onClick(() => {
            this.isActive = !this.isActive
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct LifecycleDemo {
  @State appearCount: number = 0
  @State disappearCount: number = 0
  @State showComponent: boolean = true

  build() {
    Column() {
      Text('Lifecycle Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      if (this.showComponent) {
        Text('Lifecycle Component')
          .fontSize(16)
          .padding(15)
          .width('100%')
          .backgroundColor('#FF6B6B')
          .onAppear(() => {
            this.appearCount++
          })
          .onDisappear(() => {
            this.disappearCount++
          })
      }
      Text('Appear Count: ' + this.appearCount)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Disappear Count: ' + this.disappearCount)
        .fontSize(14)
        .margin({ bottom: 15 })
      Button('Toggle Component')
        .onClick(() => {
          this.showComponent = !this.showComponent
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct EventHandlingDemo {
  @State clickCount: number = 0
  @State hoverState: string = 'None'
  @State focusState: string = 'Blurred'

  build() {
    Column() {
      Text('Event Handling Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Click Me')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#FF6B6B')
        .onClick(() => {
          this.clickCount++
        })
        .onHover((isHover: boolean) => {
          this.hoverState = isHover ? 'Hovering' : 'None'
        })
        .margin({ bottom: 15 })
      Text('Click Count: ' + this.clickCount)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Hover State: ' + this.hoverState)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Focus State: ' + this.focusState)
        .fontSize(14)
        .margin({ bottom: 15 })
      TextInput({ placeholder: 'Focus me...' })
        .onFocus(() => {
          this.focusState = 'Focused'
        })
        .onBlur(() => {
          this.focusState = 'Blurred'
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct AnimationDemo {
  @State scale: number = 1.0
  @State opacity: number = 1.0
  @State rotation: number = 0
  @State translateX: number = 0

  build() {
    Column() {
      Text('Animation Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Animated Element')
        .fontSize(16)
        .padding(15)
        .width(200)
        .height(100)
        .textAlign(TextAlign.Center)
        .backgroundColor('#FF6B6B')
        .scale({ x: this.scale, y: this.scale })
        .opacity(this.opacity)
        .rotate({ angle: this.rotation })
        .translate({ x: this.translateX, y: 0 })
        .margin({ bottom: 15 })
      Row() {
        Button('Scale')
          .onClick(() => {
            this.scale = this.scale === 1.0 ? 1.5 : 1.0
          })
        Button('Opacity')
          .onClick(() => {
            this.opacity = this.opacity === 1.0 ? 0.5 : 1.0
          })
        Button('Rotate')
          .onClick(() => {
            this.rotation = this.rotation === 0 ? 45 : 0
          })

        Button('Translate')
          .onClick(() => {
            this.translateX = this.translateX === 0 ? 50 : 0
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct TransitionDemo {
  @State showElement: boolean = true

  build() {
    Column() {
      Text('Transition Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      if (this.showElement) {
        Text('Transition Element')
          .fontSize(16)
          .padding(15)
          .width('100%')
          .backgroundColor('#4ECDC4')
          .transition({ type: TransitionType.All, opacity: 0.5, duration: 300 })
      }
      Button('Toggle Element')
        .onClick(() => {
          this.showElement = !this.showElement
        })
        .margin({ top: 15 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct GestureDemo {
  @State tapCount: number = 0
  @State longPressCount: number = 0
  @State panOffset: string = '(0, 0)'
  @State pinchScale: number = 1.0

  build() {
    Column() {
      Text('Gesture Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })

      Text('Tap Me')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#FF6B6B')
        .gesture(
          TapGesture()
            .onAction(() => {
              this.tapCount++
            })
        )
        .margin({ bottom: 10 })

      Text('Long Press Me')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#4ECDC4')
        .gesture(
          LongPressGesture({ repeat: false })
            .onAction(() => {
              this.longPressCount++
            })
        )
        .margin({ bottom: 10 })

      Text('Pan Me')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#45B7D1')
        .gesture(
          PanGesture({ direction: PanDirection.All })
            .onActionUpdate((event: GestureEvent) => {
              this.panOffset = '(' + event.offsetX.toFixed(0) + ', ' + event.offsetY.toFixed(0) + ')'
            })
        )
        .margin({ bottom: 10 })
      Text('Pinch Me')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#96CEB4')
        .gesture(
          PinchGesture({ fingers: 2 })
            .onActionUpdate((event: GestureEvent) => {
              this.pinchScale = event.scale
            })
        )
        .margin({ bottom: 15 })
      Text('Tap Count: ' + this.tapCount)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Long Press Count: ' + this.longPressCount)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Pan Offset: ' + this.panOffset)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Pinch Scale: ' + this.pinchScale.toFixed(2))
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct AccessibilityDemo {
  @State accessibilityText: string = 'Accessible Element'
  @State accessibilityDescription: string = 'This is an accessible element for screen readers'

  build() {
    Column() {
      Text('Accessibility Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text(this.accessibilityText)
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#FF6B6B')
        .accessibilityText(this.accessibilityText)
        .accessibilityDescription(this.accessibilityDescription)
        .accessibilityLevel(AccessibilityLevel.Level1)
        .margin({ bottom: 15 })
      Text('Accessibility Text: ' + this.accessibilityText)
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Description: ' + this.accessibilityDescription)
        .fontSize(14)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct PerformanceDemo {
  @State renderTime: number = 0
  @State frameRate: number = 60
  @State memoryUsage: number = 0

  build() {
    Column() {
      Text('Performance Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Performance Metrics')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#FF6B6B')
        .margin({ bottom: 15 })
      Text('Render Time: ' + this.renderTime + 'ms')
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Frame Rate: ' + this.frameRate + ' FPS')
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Memory Usage: ' + this.memoryUsage + ' MB')
        .fontSize(14)
        .margin({ bottom: 15 })
      Button('Update Metrics')
        .onClick(() => {
          this.renderTime = Math.floor(Math.random() * 50) + 10
          this.frameRate = Math.floor(Math.random() * 10) + 55
          this.memoryUsage = Math.floor(Math.random() * 100) + 50
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ResponsiveDemo {
  @State screenWidth: number = 0
  @State screenHeight: number = 0
  @State orientation: string = 'Portrait'

  build() {
    Column() {
      Text('Responsive Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Screen Info')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor('#FF6B6B')
        .margin({ bottom: 15 })
      Text('Screen Width: ' + this.screenWidth)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Screen Height: ' + this.screenHeight)
        .fontSize(14)
        .margin({ bottom: 5 })
      Text('Orientation: ' + this.orientation)
        .fontSize(14)
        .margin({ bottom: 15 })
      Button('Update Screen Info')
        .onClick(() => {
          this.screenWidth = 375
          this.screenHeight = 667
          this.orientation = 'Portrait'
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}

@Component
struct ThemeDemo {
  @State isDarkMode: boolean = false
  @State primaryColor: string = '#007DFF'
  @State backgroundColor: string = '#FFFFFF'

  build() {
    Column() {
      Text('Theme Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      Text('Theme Preview')
        .fontSize(16)
        .padding(15)
        .width('100%')
        .backgroundColor(this.primaryColor)
        .fontColor('#FFFFFF')
        .margin({ bottom: 15 })

      Text('Dark Mode: ' + (this.isDarkMode ? 'On' : 'Off'))
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Primary Color: ' + this.primaryColor)
        .fontSize(14)
        .margin({ bottom: 5 })

      Text('Background Color: ' + this.backgroundColor)
        .fontSize(14)
        .margin({ bottom: 15 })

      Row() {
        Button('Toggle Dark Mode')
          .onClick(() => {
            this.isDarkMode = !this.isDarkMode
            this.backgroundColor = this.isDarkMode ? '#000000' : '#FFFFFF'
          })
        Button('Change Color')
          .onClick(() => {
            this.primaryColor = this.primaryColor === '#007DFF' ? '#FF6B6B' : '#007DFF'
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}