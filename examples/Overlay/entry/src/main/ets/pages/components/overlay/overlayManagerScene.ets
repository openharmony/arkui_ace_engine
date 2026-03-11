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

import { ComponentContent, LevelOrder, OverlayManager, OverlayManagerOptions } from '@kit.ArkUI'
import { ParamOption, SetParam } from '../base/ParamOption'

class BasicOverlayParams {
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public backgroundColor: string = '#FFF0F0F0'
  constructor(message: string, overlayManager: OverlayManager, overlayIdx: number, backgroundColor: string = '#FFF0F0F0') {
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.backgroundColor = backgroundColor
  }
}

class PositionOverlayParams {
  public context: UIContext
  public offsetX: number = 0
  public offsetY: number = 0
  public width: number = 200
  public height: number = 150
  public backgroundColor: string = '#FF5733'
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  constructor(context: UIContext, offsetX: number, offsetY: number, width: number, height: number,
    backgroundColor: string, message: string, overlayManager: OverlayManager, overlayIdx: number) {
    this.context = context
    this.offsetX = offsetX
    this.offsetY = offsetY
    this.width = width
    this.height = height
    this.backgroundColor = backgroundColor
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
  }
}

class AnimationOverlayParams {
  public context: UIContext
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public animationType: string = 'fade'
  public duration: number = 300
  constructor(context: UIContext, message: string, overlayManager: OverlayManager, overlayIdx: number,
    animationType: string, duration: number) {
    this.context = context
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.animationType = animationType
    this.duration = duration
  }
}

class InteractiveOverlayParams {
  public context: UIContext
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public onConfirm: () => void = () => {}
  public onCancel: () => void = () => {}
  constructor(context: UIContext, message: string, overlayManager: OverlayManager, overlayIdx: number,
    onConfirm: () => void, onCancel: () => void) {
    this.context = context
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.onConfirm = onConfirm
    this.onCancel = onCancel
  }
}

class ListOverlayParams {
  public context: UIContext
  public items: string[] = []
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public onItemClick: (index: number) => void = () => {}
  constructor(context: UIContext, items: string[], overlayManager: OverlayManager, overlayIdx: number,
    onItemClick: (index: number) => void) {
    this.context = context
    this.items = items
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.onItemClick = onItemClick
  }
}

class FormOverlayParams {
  public context: UIContext
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public onSubmit: (name: string, email: string) => void = () => {}
  constructor(context: UIContext, overlayManager: OverlayManager, overlayIdx: number,
    onSubmit: (name: string, email: string) => void) {
    this.context = context
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.onSubmit = onSubmit
  }
}

class ProgressOverlayParams {
  public context: UIContext
  public progress: number = 0
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  constructor(context: UIContext, progress: number, message: string, overlayManager: OverlayManager, overlayIdx: number) {
    this.context = context
    this.progress = progress
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
  }
}

class ImageOverlayParams {
  public context: UIContext
  public imageSrc: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  constructor(context: UIContext, imageSrc: string, overlayManager: OverlayManager, overlayIdx: number) {
    this.context = context
    this.imageSrc = imageSrc
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
  }
}

class CustomShapeOverlayParams {
  public context: UIContext
  public shapeType: string = 'circle'
  public color: string = '#FF5733'
  public size: number = 100
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  constructor(context: UIContext, shapeType: string, color: string, size: number,
    overlayManager: OverlayManager, overlayIdx: number) {
    this.context = context
    this.shapeType = shapeType
    this.color = color
    this.size = size
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
  }
}

class DragDropOverlayParams {
  public context: UIContext
  public message: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public onDrop: (x: number, y: number) => void = () => {}
  constructor(context: UIContext, message: string, overlayManager: OverlayManager, overlayIdx: number,
    onDrop: (x: number, y: number) => void) {
    this.context = context
    this.message = message
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.onDrop = onDrop
  }
}

class NotificationOverlayParams {
  public context: UIContext
  public title: string = ''
  public content: string = ''
  public overlayManager: OverlayManager = new OverlayManager()
  public overlayIdx: number = 0
  public autoClose: boolean = true
  public duration: number = 3000
  constructor(context: UIContext, title: string, content: string, overlayManager: OverlayManager,
    overlayIdx: number, autoClose: boolean, duration: number) {
    this.context = context
    this.title = title
    this.content = content
    this.overlayManager = overlayManager
    this.overlayIdx = overlayIdx
    this.autoClose = autoClose
    this.duration = duration
  }
}

let overlayArray: ComponentContent<BasicOverlayParams>[] = []
let positionOverlayArray: ComponentContent<PositionOverlayParams>[] = []
let animationOverlayArray: ComponentContent<AnimationOverlayParams>[] = []
let interactiveOverlayArray: ComponentContent<InteractiveOverlayParams>[] = []
let listOverlayArray: ComponentContent<ListOverlayParams>[] = []
let formOverlayArray: ComponentContent<FormOverlayParams>[] = []
let progressOverlayArray: ComponentContent<ProgressOverlayParams>[] = []
let imageOverlayArray: ComponentContent<ImageOverlayParams>[] = []
let customShapeOverlayArray: ComponentContent<CustomShapeOverlayParams>[] = []
let dragDropOverlayArray: ComponentContent<DragDropOverlayParams>[] = []
let notificationOverlayArray: ComponentContent<NotificationOverlayParams>[] = []

let overlayIndex: number = 0

@Builder
function buildBasicOverlay(params: BasicOverlayParams) {
  Column({ space: 10 }) {
    Text(params.message)
      .fontSize(20)
      .fontWeight(FontWeight.Bold)
      .textAlign(TextAlign.Center)
    Divider().color(Color.Gray)
    Button('关闭弹窗')
      .width('80%')
      .onClick(() => {
        let componentContent = overlayArray[params.overlayIdx]
        if (componentContent) {
          params.overlayManager.removeComponentContent(componentContent)
          overlayArray[params.overlayIdx] = null!
        }
      })
  }
  .width(280)
  .height(180)
  .backgroundColor(params.backgroundColor)
  .borderRadius(12)
  .padding(16)
  .shadow({ radius: 20, color: '#66000000', offsetX: 0, offsetY: 4 })
  .justifyContent(FlexAlign.Center)
}

@Builder
function buildPositionOverlay(params: PositionOverlayParams) {
  Column() {
    Stack() {
      Column({ space: 8 }) {
        Text(params.message)
          .fontSize(16)
          .fontColor(Color.White)
        Text(`位置: (${params.offsetX}, ${params.offsetY})`)
          .fontSize(12)
          .fontColor(Color.White)
        Text(`尺寸: ${params.width} x ${params.height}`)
          .fontSize(12)
          .fontColor(Color.White)
      }
      .width(params.width)
      .height(params.height)
      .backgroundColor(params.backgroundColor)
      .borderRadius(8)
      .padding(12)
      .justifyContent(FlexAlign.Center)
    }
    .position({ x: params.offsetX, y: params.offsetY })
  }
  .width('100%')
  .height('100%')
  .hitTestBehavior(HitTestMode.Transparent)
}

@Builder
function buildAnimationOverlay(params: AnimationOverlayParams) {
  Column({ space: 12 }) {
    Text(params.message)
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
    Text(`动画类型: ${params.animationType}`)
      .fontSize(14)
      .fontColor('#666666')
    Text(`持续时间: ${params.duration}ms`)
      .fontSize(14)
      .fontColor('#666666')
    Button('关闭')
      .onClick(() => {
        let componentContent = animationOverlayArray[params.overlayIdx]
        if (componentContent) {
          params.overlayManager.removeComponentContent(componentContent)
          animationOverlayArray[params.overlayIdx] = null!
        }
      })
  }
  .width(260)
  .height(200)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(20)
  .shadow({ radius: 24, color: '#33000000', offsetX: 0, offsetY: 8 })
}

@Builder
function buildInteractiveOverlay(params: InteractiveOverlayParams) {
  Column({ space: 16 }) {
    Text(params.message)
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
      .textAlign(TextAlign.Center)
    Row({ space: 16 }) {
      Button('确认')
        .width(100)
        .backgroundColor('#4CAF50')
        .onClick(() => {
          params.onConfirm()
          let componentContent = interactiveOverlayArray[params.overlayIdx]
          if (componentContent) {
            params.overlayManager.removeComponentContent(componentContent)
            interactiveOverlayArray[params.overlayIdx] = null!
          }
        })
      Button('取消')
        .width(100)
        .backgroundColor('#F44336')
        .onClick(() => {
          params.onCancel()
          let componentContent = interactiveOverlayArray[params.overlayIdx]
          if (componentContent) {
            params.overlayManager.removeComponentContent(componentContent)
            interactiveOverlayArray[params.overlayIdx] = null!
          }
        })
    }
  }
  .width(300)
  .height(180)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(20)
  .justifyContent(FlexAlign.Center)
}

@Builder
function buildListOverlay(params: ListOverlayParams) {
  Column({ space: 8 }) {
    Text('选择项目')
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
      .width('100%')
      .textAlign(TextAlign.Center)
    List({ space: 4 }) {
      ForEach(params.items, (item: string, index: number) => {
        ListItem() {
          Text(item)
            .width('100%')
            .padding(12)
            .backgroundColor(index % 2 === 0 ? '#F5F5F5' : '#FFFFFF')
            .borderRadius(4)
            .onClick(() => {
              params.onItemClick(index)
              let componentContent = listOverlayArray[params.overlayIdx]
              if (componentContent) {
                params.overlayManager.removeComponentContent(componentContent)
                listOverlayArray[params.overlayIdx] = null!
              }
            })
        }
      })
    }
    .width('100%')
    .height(200)
    .divider({ strokeWidth: 1, color: '#EEEEEE' })
  }
  .width(280)
  .height(300)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(16)
}

@Builder
function buildFormOverlay(params: FormOverlayParams) {
  Column({ space: 16 }) {
    Text('表单输入')
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
    TextInput({ placeholder: '请输入姓名' })
      .width('100%')
      .height(40)
      .id('form_name_input')
    TextInput({ placeholder: '请输入邮箱' })
      .width('100%')
      .height(40)
      .id('form_email_input')
    Row({ space: 16 }) {
      Button('提交')
        .width(100)
        .backgroundColor('#4CAF50')
        .onClick(() => {
          params.onSubmit('test_name', 'test@email.com')
          let componentContent = formOverlayArray[params.overlayIdx]
          if (componentContent) {
            params.overlayManager.removeComponentContent(componentContent)
            formOverlayArray[params.overlayIdx] = null!
          }
        })
      Button('取消')
        .width(100)
        .backgroundColor('#9E9E9E')
        .onClick(() => {
          let componentContent = formOverlayArray[params.overlayIdx]
          if (componentContent) {
            params.overlayManager.removeComponentContent(componentContent)
            formOverlayArray[params.overlayIdx] = null!
          }
        })
    }
  }
  .width(300)
  .height(280)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(20)
}

@Builder
function buildProgressOverlay(params: ProgressOverlayParams) {
  Column({ space: 16 }) {
    Text(params.message)
      .fontSize(18)
      .fontWeight(FontWeight.Bold)
    Progress({ value: params.progress, total: 100, type: ProgressType.Linear })
      .width('100%')
      .height(8)
    Text(`${params.progress}%`)
      .fontSize(16)
      .fontColor('#666666')
  }
  .width(280)
  .height(160)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(20)
  .justifyContent(FlexAlign.Center)
}

@Builder
function buildImageOverlay(params: ImageOverlayParams) {
  Column({ space: 12 }) {
    Image(params.imageSrc)
      .width(200)
      .height(200)
      .objectFit(ImageFit.Cover)
      .borderRadius(8)
    Button('关闭')
      .onClick(() => {
        let componentContent = imageOverlayArray[params.overlayIdx]
        if (componentContent) {
          params.overlayManager.removeComponentContent(componentContent)
          imageOverlayArray[params.overlayIdx] = null!
        }
      })
  }
  .width(240)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(16)
}

@Builder
function buildCustomShapeOverlay(params: CustomShapeOverlayParams) {
  Column({ space: 12 }) {
    Text(`形状: ${params.shapeType}`)
      .fontSize(16)
      .fontWeight(FontWeight.Bold)
    if (params.shapeType === 'circle') {
      Circle()
        .width(params.size)
        .height(params.size)
        .fill(params.color)
    } else if (params.shapeType === 'rect') {
      Rect()
        .width(params.size)
        .height(params.size)
        .fill(params.color)
        .radius(8)
    } else if (params.shapeType === 'ellipse') {
      Ellipse()
        .width(params.size * 1.5)
        .height(params.size)
        .fill(params.color)
    }
    Button('关闭')
      .onClick(() => {
        let componentContent = customShapeOverlayArray[params.overlayIdx]
        if (componentContent) {
          params.overlayManager.removeComponentContent(componentContent)
          customShapeOverlayArray[params.overlayIdx] = null!
        }
      })
  }
  .width(200)
  .height(200)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(16)
  .padding(16)
  .justifyContent(FlexAlign.Center)
}

@Builder
function buildDragDropOverlay(params: DragDropOverlayParams) {
  Column({ space: 12 }) {
    Text(params.message)
      .fontSize(16)
      .fontWeight(FontWeight.Bold)
    Text('拖拽此区域')
      .fontSize(14)
      .fontColor('#666666')
  }
  .width(150)
  .height(150)
  .backgroundColor('#4CAF50')
  .borderRadius(12)
  .justifyContent(FlexAlign.Center)
  .gesture(
    PanGesture()
      .onActionEnd((event: GestureEvent) => {
        params.onDrop(event.offsetX, event.offsetY)
      })
  )
}

@Builder
function buildNotificationOverlay(params: NotificationOverlayParams) {
  Column({ space: 8 }) {
    Text(params.title)
      .fontSize(16)
      .fontWeight(FontWeight.Bold)
      .width('100%')
    Text(params.content)
      .fontSize(14)
      .fontColor('#666666')
      .width('100%')
  }
  .width(280)
  .backgroundColor('#FFFFFFFF')
  .borderRadius(12)
  .padding(16)
  .shadow({ radius: 16, color: '#33000000', offsetX: 0, offsetY: 4 })
  .position({ x: 20, y: 50 })
}

@Builder
export function OverlayManagerSceneBuilder(name: string, param: Object) {
  OverlayManagerScene()
}

@Entry
@Component
export struct OverlayManagerScene {
  private ctx: UIContext = this.getUIContext()
  private overlayManager: OverlayManager = this.ctx.getOverlayManager()
  pathStack: NavPathStack = new NavPathStack()

  @State currentTestSection: string = 'basic'
  @State logMessages: string[] = []
  @State overlayCount: number = 0
  @State selectedLevelOrder: number = 0
  @State showHiddenOverlays: boolean = false

  private addLog(message: string) {
    let timestamp = new Date().toLocaleTimeString()
    this.logMessages.unshift(`[${timestamp}] ${message}`)
    if (this.logMessages.length > 20) {
      this.logMessages.pop()
    }
  }

  private clearOverlays() {
    overlayArray = overlayArray.filter(item => item !== null)
    overlayArray.forEach((item, index) => {
      if (item) {
        this.overlayManager.removeComponentContent(item)
      }
    })
    overlayArray = []
    positionOverlayArray = []
    animationOverlayArray = []
    interactiveOverlayArray = []
    listOverlayArray = []
    formOverlayArray = []
    progressOverlayArray = []
    imageOverlayArray = []
    customShapeOverlayArray = []
    dragDropOverlayArray = []
    notificationOverlayArray = []
    overlayIndex = 0
    this.overlayCount = 0
    this.addLog('已清除所有弹窗')
  }

  private testSections: SetParam[] = [
    { title: '基础功能', func: () => { this.currentTestSection = 'basic' } },
    { title: '层级顺序', func: () => { this.currentTestSection = 'levelOrder' } },
    { title: '位置控制', func: () => { this.currentTestSection = 'position' } },
    { title: '显示隐藏', func: () => { this.currentTestSection = 'visibility' } },
    { title: '动画效果', func: () => { this.currentTestSection = 'animation' } },
    { title: '交互弹窗', func: () => { this.currentTestSection = 'interactive' } },
    { title: '列表选择', func: () => { this.currentTestSection = 'list' } },
    { title: '表单输入', func: () => { this.currentTestSection = 'form' } },
    { title: '进度显示', func: () => { this.currentTestSection = 'progress' } },
    { title: '图片展示', func: () => { this.currentTestSection = 'image' } },
    { title: '自定义形状', func: () => { this.currentTestSection = 'shape' } },
    { title: '拖拽功能', func: () => { this.currentTestSection = 'drag' } },
    { title: '通知消息', func: () => { this.currentTestSection = 'notification' } },
    { title: '批量操作', func: () => { this.currentTestSection = 'batch' } },
    { title: '选项设置', func: () => { this.currentTestSection = 'options' } },
  ]

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Text('OverlayManager 综合测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Row({ space: 4 }) {
          Text(`当前弹窗数: ${this.overlayCount}`)
            .fontSize(12)
          Text(` | `)
            .fontSize(12)
          Text(`当前模块: ${this.currentTestSection}`)
            .fontSize(12)
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Scroll() {
          Row({ space: 4 }) {
            ForEach(this.testSections, (item: SetParam) => {
              ParamOption({ title: item.title!, func: item.func! })
            }, (item: SetParam) => item.title)
          }
        }
        .scrollable(ScrollDirection.Horizontal)
        .width('100%')
        .height(40)
        .scrollBar(BarState.Off)

        Scroll() {
          Column({ space: 12 }) {
            if (this.currentTestSection === 'basic') {
              this.BasicTestSection()
            } else if (this.currentTestSection === 'levelOrder') {
              this.LevelOrderTestSection()
            } else if (this.currentTestSection === 'position') {
              this.PositionTestSection()
            } else if (this.currentTestSection === 'visibility') {
              this.VisibilityTestSection()
            } else if (this.currentTestSection === 'animation') {
              this.AnimationTestSection()
            } else if (this.currentTestSection === 'interactive') {
              this.InteractiveTestSection()
            } else if (this.currentTestSection === 'list') {
              this.ListTestSection()
            } else if (this.currentTestSection === 'form') {
              this.FormTestSection()
            } else if (this.currentTestSection === 'progress') {
              this.ProgressTestSection()
            } else if (this.currentTestSection === 'image') {
              this.ImageTestSection()
            } else if (this.currentTestSection === 'shape') {
              this.ShapeTestSection()
            } else if (this.currentTestSection === 'drag') {
              this.DragTestSection()
            } else if (this.currentTestSection === 'notification') {
              this.NotificationTestSection()
            } else if (this.currentTestSection === 'batch') {
              this.BatchTestSection()
            } else if (this.currentTestSection === 'options') {
              this.OptionsTestSection()
            }
          }
          .width('100%')
          .padding(8)
        }
        .layoutWeight(1)
        .width('100%')

        this.LogSection()
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F5F5F5')
    }
    .title('OverlayManager Demo')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }

  @Builder
  BasicTestSection() {
    Column({ space: 12 }) {
      Text('基础功能测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('addComponentContent - 添加组件内容到Overlay层')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('添加基础弹窗')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`基础弹窗 #${idx}`, this.overlayManager, idx))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加基础弹窗 #${idx}`)
          })

        Button('添加彩色弹窗')
          .fontSize(12)
          .onClick(() => {
            let colors = ['#FFE4E1', '#E6E6FA', '#F0FFF0', '#FFF0F5', '#F0F8FF']
            let color = colors[overlayIndex % colors.length]
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`彩色弹窗 #${idx}`, this.overlayManager, idx, color))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加彩色弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('添加指定索引')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`索引弹窗 #${idx}`, this.overlayManager, idx))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 2)
            this.overlayCount++
            this.addLog(`添加弹窗到索引2: #${idx}`)
          })

        Button('添加到最前')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`最前弹窗 #${idx}`, this.overlayManager, idx))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加弹窗到最前: #${idx}`)
          })
      }
      .width('100%')

      Button('清除所有弹窗')
        .width('100%')
        .backgroundColor('#F44336')
        .onClick(() => {
          this.clearOverlays()
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  LevelOrderTestSection() {
    Column({ space: 12 }) {
      Text('层级顺序测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('addComponentContentWithOrder - 带层级顺序添加组件')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 4 }) {
        Text('选择层级:')
          .fontSize(12)
        ForEach([
          { title: '-100', value: -100 },
          { title: '-50', value: -50 },
          { title: '0', value: 0 },
          { title: '50', value: 50 },
          { title: '100', value: 100 },
        ], (item: { title: string, value: number }) => {
          Button(item.title)
            .fontSize(10)
            .height(28)
            .backgroundColor(this.selectedLevelOrder === item.value ? '#4CAF50' : '#2196F3')
            .onClick(() => {
              this.selectedLevelOrder = item.value
            })
        })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('添加层级弹窗')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let levelOrder = LevelOrder.clamp(this.selectedLevelOrder)
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`层级${this.selectedLevelOrder}弹窗 #${idx}`, this.overlayManager, idx))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContentWithOrder(componentContent, levelOrder)
            this.overlayCount++
            this.addLog(`添加层级${this.selectedLevelOrder}弹窗 #${idx}`)
          })

        Button('添加多个层级')
          .fontSize(12)
          .onClick(() => {
            let orders = [-100, -50, 0, 50, 100]
            orders.forEach((order, i) => {
              let idx = overlayIndex++
              let levelOrder = LevelOrder.clamp(order)
              let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
                new BasicOverlayParams(`层级${order}弹窗 #${idx}`, this.overlayManager, idx))
              overlayArray[idx] = componentContent
              this.overlayManager.addComponentContentWithOrder(componentContent, levelOrder)
              this.overlayCount++
            })
            this.addLog('添加多个层级弹窗')
          })
      }
      .width('100%')

      Text('层级说明: 数值越大层级越高，会覆盖在数值小的弹窗之上')
        .fontSize(10)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  PositionTestSection() {
    Column({ space: 12 }) {
      Text('位置控制测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('通过参数控制弹窗显示位置')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('左上角')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[PositionOverlayParams]>(buildPositionOverlay),
              new PositionOverlayParams(this.ctx, 10, 50, 150, 100, '#FF5733', '左上角', this.overlayManager, idx))
            positionOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加左上角弹窗 #${idx}`)
          })

        Button('右上角')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[PositionOverlayParams]>(buildPositionOverlay),
              new PositionOverlayParams(this.ctx, 200, 50, 150, 100, '#33FF57', '右上角', this.overlayManager, idx))
            positionOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加右上角弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('左下角')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[PositionOverlayParams]>(buildPositionOverlay),
              new PositionOverlayParams(this.ctx, 10, 500, 150, 100, '#3357FF', '左下角', this.overlayManager, idx))
            positionOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加左下角弹窗 #${idx}`)
          })

        Button('右下角')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[PositionOverlayParams]>(buildPositionOverlay),
              new PositionOverlayParams(this.ctx, 200, 500, 150, 100, '#FF33A1', '右下角', this.overlayManager, idx))
            positionOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加右下角弹窗 #${idx}`)
          })
      }
      .width('100%')

      Button('居中弹窗')
        .fontSize(12)
        .width('100%')
        .onClick(() => {
          let idx = overlayIndex++
          let componentContent = new ComponentContent(this.ctx, wrapBuilder<[PositionOverlayParams]>(buildPositionOverlay),
            new PositionOverlayParams(this.ctx, 100, 250, 200, 150, '#A133FF', '居中弹窗', this.overlayManager, idx))
          positionOverlayArray[idx] = componentContent
          this.overlayManager.addComponentContent(componentContent, 0)
          this.overlayCount++
          this.addLog(`添加居中弹窗 #${idx}`)
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  VisibilityTestSection() {
    Column({ space: 12 }) {
      Text('显示隐藏测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('showComponentContent / hideComponentContent')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('showAllComponentContents / hideAllComponentContents')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('添加可隐藏弹窗')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
              new BasicOverlayParams(`可隐藏弹窗 #${idx}`, this.overlayManager, idx))
            overlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加可隐藏弹窗 #${idx}`)
          })

        Button('隐藏最后一个')
          .fontSize(12)
          .onClick(() => {
            for (let i = overlayArray.length - 1; i >= 0; i--) {
              if (overlayArray[i]) {
                this.overlayManager.hideComponentContent(overlayArray[i])
                this.addLog(`隐藏弹窗 #${i}`)
                break
              }
            }
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('显示最后一个')
          .fontSize(12)
          .onClick(() => {
            for (let i = overlayArray.length - 1; i >= 0; i--) {
              if (overlayArray[i]) {
                this.overlayManager.showComponentContent(overlayArray[i])
                this.addLog(`显示弹窗 #${i}`)
                break
              }
            }
          })

        Button('隐藏所有')
          .fontSize(12)
          .onClick(() => {
            this.overlayManager.hideAllComponentContents()
            this.showHiddenOverlays = true
            this.addLog('隐藏所有弹窗')
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('显示所有')
          .fontSize(12)
          .onClick(() => {
            this.overlayManager.showAllComponentContents()
            this.showHiddenOverlays = false
            this.addLog('显示所有弹窗')
          })

        Button('移除隐藏的')
          .fontSize(12)
          .onClick(() => {
            overlayArray.forEach((item, index) => {
              if (item) {
                this.overlayManager.removeComponentContent(item)
              }
            })
            overlayArray = []
            this.overlayCount = 0
            this.addLog('移除所有弹窗')
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  AnimationTestSection() {
    Column({ space: 12 }) {
      Text('动画效果测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('不同动画类型的弹窗展示')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('淡入动画')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '淡入动画弹窗', this.overlayManager, idx, 'fade', 300))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加淡入动画弹窗 #${idx}`)
          })

        Button('缩放动画')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '缩放动画弹窗', this.overlayManager, idx, 'scale', 400))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加缩放动画弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('滑动动画')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '滑动动画弹窗', this.overlayManager, idx, 'slide', 350))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加滑动动画弹窗 #${idx}`)
          })

        Button('弹性动画')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '弹性动画弹窗', this.overlayManager, idx, 'bounce', 500))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加弹性动画弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('快速动画(100ms)')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '快速动画弹窗', this.overlayManager, idx, 'fade', 100))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加快速动画弹窗 #${idx}`)
          })

        Button('慢速动画(1000ms)')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[AnimationOverlayParams]>(buildAnimationOverlay),
              new AnimationOverlayParams(this.ctx, '慢速动画弹窗', this.overlayManager, idx, 'fade', 1000))
            animationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加慢速动画弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  InteractiveTestSection() {
    Column({ space: 12 }) {
      Text('交互弹窗测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('带确认/取消按钮的交互式弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('确认对话框')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[InteractiveOverlayParams]>(buildInteractiveOverlay),
              new InteractiveOverlayParams(this.ctx, '确定要执行此操作吗?', this.overlayManager, idx,
                () => { this.addLog('用户点击了确认') },
                () => { this.addLog('用户点击了取消') }))
            interactiveOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加确认对话框 #${idx}`)
          })

        Button('删除确认')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[InteractiveOverlayParams]>(buildInteractiveOverlay),
              new InteractiveOverlayParams(this.ctx, '确定要删除这条记录吗？此操作不可撤销。', this.overlayManager, idx,
                () => { this.addLog('删除确认') },
                () => { this.addLog('取消删除') }))
            interactiveOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加删除确认弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('保存确认')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[InteractiveOverlayParams]>(buildInteractiveOverlay),
              new InteractiveOverlayParams(this.ctx, '是否保存当前修改?', this.overlayManager, idx,
                () => { this.addLog('保存确认') },
                () => { this.addLog('放弃保存') }))
            interactiveOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加保存确认弹窗 #${idx}`)
          })

        Button('退出确认')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[InteractiveOverlayParams]>(buildInteractiveOverlay),
              new InteractiveOverlayParams(this.ctx, '确定要退出应用吗?', this.overlayManager, idx,
                () => { this.addLog('退出确认') },
                () => { this.addLog('继续使用') }))
            interactiveOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加退出确认弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  ListTestSection() {
    Column({ space: 12 }) {
      Text('列表选择测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('列表选择弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('颜色选择')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ListOverlayParams]>(buildListOverlay),
              new ListOverlayParams(this.ctx, ['红色', '绿色', '蓝色', '黄色', '紫色'], this.overlayManager, idx,
                (index: number) => { this.addLog(`选择了颜色: ${index}`) }))
            listOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加颜色选择弹窗 #${idx}`)
          })

        Button('字体大小')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ListOverlayParams]>(buildListOverlay),
              new ListOverlayParams(this.ctx, ['12px', '14px', '16px', '18px', '20px', '24px'], this.overlayManager, idx,
                (index: number) => { this.addLog(`选择了字体大小: ${index}`) }))
            listOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加字体大小选择弹窗 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('城市选择')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ListOverlayParams]>(buildListOverlay),
              new ListOverlayParams(this.ctx, ['北京', '上海', '广州', '深圳', '杭州', '成都'], this.overlayManager, idx,
                (index: number) => { this.addLog(`选择了城市: ${index}`) }))
            listOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加城市选择弹窗 #${idx}`)
          })

        Button('排序方式')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ListOverlayParams]>(buildListOverlay),
              new ListOverlayParams(this.ctx, ['按时间升序', '按时间降序', '按名称升序', '按名称降序', '按大小'], this.overlayManager, idx,
                (index: number) => { this.addLog(`选择了排序方式: ${index}`) }))
            listOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加排序方式选择弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  FormTestSection() {
    Column({ space: 12 }) {
      Text('表单输入测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('表单输入弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('用户信息表单')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[FormOverlayParams]>(buildFormOverlay),
              new FormOverlayParams(this.ctx, this.overlayManager, idx,
                (name: string, email: string) => { this.addLog(`提交: name=${name}, email=${email}`) }))
            formOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加用户信息表单 #${idx}`)
          })

        Button('反馈表单')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[FormOverlayParams]>(buildFormOverlay),
              new FormOverlayParams(this.ctx, this.overlayManager, idx,
                (name: string, email: string) => { this.addLog(`反馈提交: ${name}`) }))
            formOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加反馈表单 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  ProgressTestSection() {
    Column({ space: 12 }) {
      Text('进度显示测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('进度条弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('0%进度')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ProgressOverlayParams]>(buildProgressOverlay),
              new ProgressOverlayParams(this.ctx, 0, '加载中...', this.overlayManager, idx))
            progressOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加0%进度弹窗 #${idx}`)
          })

        Button('50%进度')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ProgressOverlayParams]>(buildProgressOverlay),
              new ProgressOverlayParams(this.ctx, 50, '正在处理...', this.overlayManager, idx))
            progressOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加50%进度弹窗 #${idx}`)
          })

        Button('100%进度')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ProgressOverlayParams]>(buildProgressOverlay),
              new ProgressOverlayParams(this.ctx, 100, '已完成!', this.overlayManager, idx))
            progressOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加100%进度弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  ImageTestSection() {
    Column({ space: 12 }) {
      Text('图片展示测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('图片预览弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('本地图片')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ImageOverlayParams]>(buildImageOverlay),
              new ImageOverlayParams(this.ctx, 'app.media.startIcon', this.overlayManager, idx))
            imageOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加本地图片弹窗 #${idx}`)
          })

        Button('网络图片')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[ImageOverlayParams]>(buildImageOverlay),
              new ImageOverlayParams(this.ctx, 'https://example.com/image.png', this.overlayManager, idx))
            imageOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加网络图片弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  ShapeTestSection() {
    Column({ space: 12 }) {
      Text('自定义形状测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('不同形状的弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('圆形')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[CustomShapeOverlayParams]>(buildCustomShapeOverlay),
              new CustomShapeOverlayParams(this.ctx, 'circle', '#FF5733', 80, this.overlayManager, idx))
            customShapeOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加圆形弹窗 #${idx}`)
          })

        Button('矩形')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[CustomShapeOverlayParams]>(buildCustomShapeOverlay),
              new CustomShapeOverlayParams(this.ctx, 'rect', '#33FF57', 80, this.overlayManager, idx))
            customShapeOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加矩形弹窗 #${idx}`)
          })

        Button('椭圆')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[CustomShapeOverlayParams]>(buildCustomShapeOverlay),
              new CustomShapeOverlayParams(this.ctx, 'ellipse', '#3357FF', 80, this.overlayManager, idx))
            customShapeOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加椭圆弹窗 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  DragTestSection() {
    Column({ space: 12 }) {
      Text('拖拽功能测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('可拖拽的弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('添加可拖拽弹窗')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[DragDropOverlayParams]>(buildDragDropOverlay),
              new DragDropOverlayParams(this.ctx, '拖拽我', this.overlayManager, idx,
                (x: number, y: number) => { this.addLog(`拖拽结束: (${x}, ${y})`) }))
            dragDropOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加可拖拽弹窗 #${idx}`)
          })

        Button('添加多个')
          .fontSize(12)
          .onClick(() => {
            for (let i = 0; i < 3; i++) {
              let idx = overlayIndex++
              let componentContent = new ComponentContent(this.ctx, wrapBuilder<[DragDropOverlayParams]>(buildDragDropOverlay),
                new DragDropOverlayParams(this.ctx, `拖拽项${i + 1}`, this.overlayManager, idx,
                  (x: number, y: number) => { this.addLog(`拖拽项${i + 1}结束: (${x}, ${y})`) }))
              dragDropOverlayArray[idx] = componentContent
              this.overlayManager.addComponentContent(componentContent, 0)
              this.overlayCount++
            }
            this.addLog('添加3个可拖拽弹窗')
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  NotificationTestSection() {
    Column({ space: 12 }) {
      Text('通知消息测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('通知消息弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('普通通知')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[NotificationOverlayParams]>(buildNotificationOverlay),
              new NotificationOverlayParams(this.ctx, '通知', '这是一条普通通知消息', this.overlayManager, idx, true, 3000))
            notificationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加普通通知 #${idx}`)
          })

        Button('成功通知')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[NotificationOverlayParams]>(buildNotificationOverlay),
              new NotificationOverlayParams(this.ctx, '成功', '操作已成功完成!', this.overlayManager, idx, true, 2000))
            notificationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加成功通知 #${idx}`)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('警告通知')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[NotificationOverlayParams]>(buildNotificationOverlay),
              new NotificationOverlayParams(this.ctx, '警告', '请注意，这是一个警告消息', this.overlayManager, idx, true, 4000))
            notificationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加警告通知 #${idx}`)
          })

        Button('持久通知')
          .fontSize(12)
          .onClick(() => {
            let idx = overlayIndex++
            let componentContent = new ComponentContent(this.ctx, wrapBuilder<[NotificationOverlayParams]>(buildNotificationOverlay),
              new NotificationOverlayParams(this.ctx, '提示', '这条消息不会自动关闭', this.overlayManager, idx, false, 0))
            notificationOverlayArray[idx] = componentContent
            this.overlayManager.addComponentContent(componentContent, 0)
            this.overlayCount++
            this.addLog(`添加持久通知 #${idx}`)
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  BatchTestSection() {
    Column({ space: 12 }) {
      Text('批量操作测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('批量添加和移除弹窗')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('批量添加5个')
          .fontSize(12)
          .onClick(() => {
            for (let i = 0; i < 5; i++) {
              let idx = overlayIndex++
              let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
                new BasicOverlayParams(`批量弹窗 #${idx}`, this.overlayManager, idx))
              overlayArray[idx] = componentContent
              this.overlayManager.addComponentContent(componentContent, 0)
              this.overlayCount++
            }
            this.addLog('批量添加5个弹窗')
          })

        Button('批量添加10个')
          .fontSize(12)
          .onClick(() => {
            for (let i = 0; i < 10; i++) {
              let idx = overlayIndex++
              let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
                new BasicOverlayParams(`批量弹窗 #${idx}`, this.overlayManager, idx))
              overlayArray[idx] = componentContent
              this.overlayManager.addComponentContent(componentContent, 0)
              this.overlayCount++
            }
            this.addLog('批量添加10个弹窗')
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('批量隐藏所有')
          .fontSize(12)
          .onClick(() => {
            this.overlayManager.hideAllComponentContents()
            this.addLog('批量隐藏所有弹窗')
          })

        Button('批量显示所有')
          .fontSize(12)
          .onClick(() => {
            this.overlayManager.showAllComponentContents()
            this.addLog('批量显示所有弹窗')
          })
      }
      .width('100%')

      Button('批量移除所有')
        .width('100%')
        .backgroundColor('#F44336')
        .onClick(() => {
          this.clearOverlays()
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  OptionsTestSection() {
    Column({ space: 12 }) {
      Text('选项设置测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('OverlayManagerOptions 配置')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('获取当前选项')
          .fontSize(12)
          .onClick(() => {
            let options = this.overlayManager.getOverlayManagerOptions()
            this.addLog(`获取选项: ${JSON.stringify(options)}`)
          })

        Button('设置默认选项')
          .fontSize(12)
          .onClick(() => {
            let options: OverlayManagerOptions = {}
            let result = this.overlayManager.setOverlayManagerOptions(options)
            this.addLog(`设置默认选项: ${result}`)
          })
      }
      .width('100%')

      Text('setOverlayManagerOptions / getOverlayManagerOptions 用于配置OverlayManager的全局行为')
        .fontSize(10)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  LogSection() {
    Column({ space: 4 }) {
      Row({ space: 8 }) {
        Text('操作日志')
          .fontSize(14)
          .fontWeight(FontWeight.Bold)
        Blank()
        Button('清除日志')
          .fontSize(10)
          .height(24)
          .onClick(() => {
            this.logMessages = []
          })
      }
      .width('100%')
      .padding({ left: 8, right: 8 })

      List({ space: 2 }) {
        ForEach(this.logMessages, (log: string, index: number) => {
          ListItem() {
            Text(log)
              .fontSize(10)
              .fontColor('#666666')
              .width('100%')
              .padding(4)
              .backgroundColor(index % 2 === 0 ? '#F9F9F9' : '#FFFFFF')
          }
        })
      }
      .width('100%')
      .height(120)
      .backgroundColor('#FAFAFA')
      .borderRadius(4)
      .padding(4)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }
}

@Builder
export function OverlayManagerBasicApiBuilder(name: string, param: Object) {
  OverlayManagerBasicApi()
}

@Entry
@Component
export struct OverlayManagerBasicApi {
  private ctx: UIContext = this.getUIContext()
  private overlayManager: OverlayManager = this.ctx.getOverlayManager()
  pathStack: NavPathStack = new NavPathStack()

  @State apiTestResult: string = ''
  @State testIndex: number = 0

  private testAddComponentContent() {
    this.apiTestResult = '测试 addComponentContent...'
    let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
      new BasicOverlayParams('addComponentContent 测试', this.overlayManager, 0))
    this.overlayManager.addComponentContent(componentContent, 0)
    this.apiTestResult = 'addComponentContent 成功'
  }

  private testAddComponentContentWithOrder() {
    this.apiTestResult = '测试 addComponentContentWithOrder...'
    let levelOrder = LevelOrder.clamp(100)
    let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
      new BasicOverlayParams('addComponentContentWithOrder 测试', this.overlayManager, 0))
    this.overlayManager.addComponentContentWithOrder(componentContent, levelOrder)
    this.apiTestResult = 'addComponentContentWithOrder 成功，层级: 100'
  }

  private testRemoveComponentContent() {
    this.apiTestResult = '测试 removeComponentContent...'
    let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
      new BasicOverlayParams('将被移除的弹窗', this.overlayManager, 0))
    this.overlayManager.addComponentContent(componentContent, 0)
    setTimeout(() => {
      this.overlayManager.removeComponentContent(componentContent)
      this.apiTestResult = 'removeComponentContent 成功'
    }, 1000)
    this.apiTestResult = '弹窗将在1秒后移除...'
  }

  private testShowHideComponentContent() {
    this.apiTestResult = '测试 showComponentContent / hideComponentContent...'
    let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
      new BasicOverlayParams('显示隐藏测试', this.overlayManager, 0))
    this.overlayManager.addComponentContent(componentContent, 0)
    setTimeout(() => {
      this.overlayManager.hideComponentContent(componentContent)
      this.apiTestResult = '已隐藏弹窗'
      setTimeout(() => {
        this.overlayManager.showComponentContent(componentContent)
        this.apiTestResult = '已显示弹窗'
      }, 1000)
    }, 1000)
    this.apiTestResult = '弹窗将在1秒后隐藏...'
  }

  private testShowHideAllComponentContents() {
    this.apiTestResult = '测试 showAllComponentContents / hideAllComponentContents...'
    for (let i = 0; i < 3; i++) {
      let componentContent = new ComponentContent(this.ctx, wrapBuilder<[BasicOverlayParams]>(buildBasicOverlay),
        new BasicOverlayParams(`批量测试 #${i}`, this.overlayManager, 0))
      this.overlayManager.addComponentContent(componentContent, 0)
    }
    setTimeout(() => {
      this.overlayManager.hideAllComponentContents()
      this.apiTestResult = '已隐藏所有弹窗'
      setTimeout(() => {
        this.overlayManager.showAllComponentContents()
        this.apiTestResult = '已显示所有弹窗'
      }, 1000)
    }, 1000)
    this.apiTestResult = '已添加3个弹窗，1秒后隐藏...'
  }

  private testGetSetOverlayManagerOptions() {
    this.apiTestResult = '测试 getOverlayManagerOptions / setOverlayManagerOptions...'
    let options = this.overlayManager.getOverlayManagerOptions()
    this.apiTestResult = `获取选项成功: ${JSON.stringify(options)}`
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('OverlayManager API 测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Text('测试结果:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Text(this.apiTestResult)
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')
          .padding(12)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .minHeight(60)

        Scroll() {
          Column({ space: 8 }) {
            Button('1. addComponentContent')
              .width('100%')
              .onClick(() => this.testAddComponentContent())

            Button('2. addComponentContentWithOrder')
              .width('100%')
              .onClick(() => this.testAddComponentContentWithOrder())

            Button('3. removeComponentContent')
              .width('100%')
              .onClick(() => this.testRemoveComponentContent())

            Button('4. showComponentContent / hideComponentContent')
              .width('100%')
              .onClick(() => this.testShowHideComponentContent())

            Button('5. showAllComponentContents / hideAllComponentContents')
              .width('100%')
              .onClick(() => this.testShowHideAllComponentContents())

            Button('6. getOverlayManagerOptions / setOverlayManagerOptions')
              .width('100%')
              .onClick(() => this.testGetSetOverlayManagerOptions())
          }
          .width('100%')
        }
        .layoutWeight(1)
        .width('100%')
      }
      .width('100%')
      .height('100%')
      .padding(16)
      .backgroundColor('#FFFFFF')
    }
    .title('API 测试')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
