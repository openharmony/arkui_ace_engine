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

import { SymbolGlyphModifier, LengthMetrics } from '@kit.ArkUI';

interface FileItem {
  id: number
  name: string
  type: 'file' | 'folder' | 'image' | 'document'
  size: string
  modifiedDate: string
  selected: boolean
}

@Entry
@Component
struct MenuBusinessScenarios {
  @State files: FileItem[] = []
  @State selectedFiles: Set<number> = new Set<number>()
  @State currentSortBy: string = 'name'
  @State sortAscending: boolean = true
  @State viewMode: string = 'list'
  @State eventLog: string = ''
  @State searchText: string = ''
  @State clipboardContent: string = ''
  @State undoStack: string[] = []
  @State redoStack: string[] = []
  @State zoomLevel: number = 100
  @State isDarkMode: boolean = false
  @State showHiddenFiles: boolean = false
  @State autoSave: boolean = true
  @State wordWrap: boolean = true
  @State lineNumbers: boolean = true

  private iconResource: Resource = $r('app.media.app_icon')

  aboutToAppear(): void {
    this.initializeFiles()
  }

  initializeFiles(): void {
    this.files = [
      { id: 1, name: '项目文档.docx', type: 'document', size: '2.5MB', modifiedDate: '2026-03-10', selected: false },
      { id: 2, name: '设计稿.png', type: 'image', size: '5.2MB', modifiedDate: '2026-03-09', selected: false },
      { id: 3, name: '源代码', type: 'folder', size: '-', modifiedDate: '2026-03-11', selected: false },
      { id: 4, name: '配置文件.json', type: 'file', size: '1KB', modifiedDate: '2026-03-08', selected: false },
      { id: 5, name: '用户手册.pdf', type: 'document', size: '8.3MB', modifiedDate: '2026-03-07', selected: false },
      { id: 6, name: '截图', type: 'folder', size: '-', modifiedDate: '2026-03-06', selected: false },
      { id: 7, name: 'logo.png', type: 'image', size: '156KB', modifiedDate: '2026-03-05', selected: false },
      { id: 8, name: 'README.md', type: 'file', size: '3KB', modifiedDate: '2026-03-04', selected: false }
    ]
  }

  @Builder
  FileContextMenu(file: FileItem) {
    Menu() {
      MenuItemGroup({ header: '基本操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '打开',
          labelInfo: 'Enter'
        })
          .onClick(() => {
            this.addLog(`打开文件: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '新窗口打开'
        })
          .onClick(() => {
            this.addLog(`新窗口打开: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '快速查看',
          labelInfo: 'Space'
        })
          .onClick(() => {
            this.addLog(`快速查看: ${file.name}`)
          })
      }
      MenuItemGroup({ header: '编辑操作' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '复制',
          labelInfo: 'Ctrl+C'
        })
          .onClick(() => {
            this.clipboardContent = file.name
            this.addLog(`复制: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '剪切',
          labelInfo: 'Ctrl+X'
        })
          .onClick(() => {
            this.clipboardContent = file.name
            this.addLog(`剪切: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '重命名',
          labelInfo: 'F2'
        })
          .onClick(() => {
            this.addLog(`重命名: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '删除',
          labelInfo: 'Delete'
        })
          .onClick(() => {
            this.addLog(`删除: ${file.name}`)
          })
      }
      MenuItemGroup({ header: '分享与导出' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '分享'
        })
          .onClick(() => {
            this.addLog(`分享: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '压缩',
          labelInfo: '右键菜单'
        })
          .onClick(() => {
            this.addLog(`压缩: ${file.name}`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '打印'
        })
          .enabled(file.type === 'document')
          .onClick(() => {
            this.addLog(`打印: ${file.name}`)
          })
      }
      MenuItemGroup({ header: '属性' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '获取信息',
          labelInfo: 'Ctrl+I'
        })
          .onClick(() => {
            this.addLog(`获取信息: ${file.name} (大小: ${file.size}, 修改日期: ${file.modifiedDate})`)
          })
      }
    }
  }

  @Builder
  EditorContextMenu() {
    Menu() {
      MenuItemGroup({ header: '撤销/重做' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '撤销',
          labelInfo: 'Ctrl+Z'
        })
          .enabled(this.undoStack.length > 0)
          .onClick(() => {
            if (this.undoStack.length > 0) {
              const action = this.undoStack.pop()!
              this.redoStack.push(action)
              this.addLog(`撤销: ${action}`)
            }
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '重做',
          labelInfo: 'Ctrl+Y'
        })
          .enabled(this.redoStack.length > 0)
          .onClick(() => {
            if (this.redoStack.length > 0) {
              const action = this.redoStack.pop()!
              this.undoStack.push(action)
              this.addLog(`重做: ${action}`)
            }
          })
      }
      MenuItemGroup({ header: '编辑' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '剪切',
          labelInfo: 'Ctrl+X'
        })
        MenuItem({
          startIcon: this.iconResource,
          content: '复制',
          labelInfo: 'Ctrl+C'
        })
        MenuItem({
          startIcon: this.iconResource,
          content: '粘贴',
          labelInfo: 'Ctrl+V'
        })
          .enabled(this.clipboardContent !== '')
        MenuItem({
          startIcon: this.iconResource,
          content: '全选',
          labelInfo: 'Ctrl+A'
        })
      }
      MenuItemGroup({ header: '格式化' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '格式化代码',
          labelInfo: 'Shift+Alt+F'
        })
          .onClick(() => {
            this.addLog('格式化代码')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '注释/取消注释',
          labelInfo: 'Ctrl+/'
        })
          .onClick(() => {
            this.addLog('切换注释')
          })
      }
    }
  }

  @Builder
  ImageContextMenu() {
    Menu() {
      MenuItemGroup({ header: '查看' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '放大',
          labelInfo: 'Ctrl++'
        })
          .onClick(() => {
            this.zoomLevel = Math.min(200, this.zoomLevel + 10)
            this.addLog(`放大: ${this.zoomLevel}%`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '缩小',
          labelInfo: 'Ctrl+-'
        })
          .onClick(() => {
            this.zoomLevel = Math.max(50, this.zoomLevel - 10)
            this.addLog(`缩小: ${this.zoomLevel}%`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '重置缩放',
          labelInfo: 'Ctrl+0'
        })
          .onClick(() => {
            this.zoomLevel = 100
            this.addLog('重置缩放: 100%')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '全屏查看',
          labelInfo: 'F11'
        })
          .onClick(() => {
            this.addLog('全屏查看')
          })
      }
      MenuItemGroup({ header: '编辑' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '旋转'
        })
          .onClick(() => {
            this.addLog('旋转图片')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '裁剪'
        })
          .onClick(() => {
            this.addLog('裁剪图片')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '滤镜'
        })
          .onClick(() => {
            this.addLog('应用滤镜')
          })
      }
      MenuItemGroup({ header: '导出' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: '保存为PNG'
        })
          .onClick(() => {
            this.addLog('保存为PNG')
          })
        MenuItem({
          startIcon: this.iconResource,
          content: '保存为JPG'
        })
          .onClick(() => {
            this.addLog('保存为JPG')
          })
      }
    }
  }

  @Builder
  SettingsContextMenu() {
    Menu() {
      MenuItemGroup({ header: '显示设置' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: this.isDarkMode ? '切换到亮色模式' : '切换到暗色模式'
        })
          .onClick(() => {
            this.isDarkMode = !this.isDarkMode
            this.addLog(`切换到${this.isDarkMode ? '暗色' : '亮色'}模式`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: this.showHiddenFiles ? '隐藏隐藏文件' : '显示隐藏文件'
        })
          .onClick(() => {
            this.showHiddenFiles = !this.showHiddenFiles
            this.addLog(`${this.showHiddenFiles ? '显示' : '隐藏'}隐藏文件`)
          })
      }
      MenuItemGroup({ header: '编辑器设置' }) {
        MenuItem({
          startIcon: this.iconResource,
          content: this.wordWrap ? '关闭自动换行' : '开启自动换行'
        })
          .onClick(() => {
            this.wordWrap = !this.wordWrap
            this.addLog(`${this.wordWrap ? '开启' : '关闭'}自动换行`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: this.lineNumbers ? '隐藏行号' : '显示行号'
        })
          .onClick(() => {
            this.lineNumbers = !this.lineNumbers
            this.addLog(`${this.lineNumbers ? '显示' : '隐藏'}行号`)
          })
        MenuItem({
          startIcon: this.iconResource,
          content: this.autoSave ? '关闭自动保存' : '开启自动保存'
        })
          .onClick(() => {
            this.autoSave = !this.autoSave
            this.addLog(`${this.autoSave ? '开启' : '关闭'}自动保存`)
          })
      }
    }
  }

  @Builder
  SortMenu() {
    Menu() {
      MenuItemGroup({ header: '排序方式' }) {
        MenuItem({ content: '按名称' })
          .selected(this.currentSortBy === 'name')
          .selectIcon(true)
          .onClick(() => {
            this.currentSortBy = 'name'
            this.sortFiles()
          })
        MenuItem({ content: '按大小' })
          .selected(this.currentSortBy === 'size')
          .selectIcon(true)
          .onClick(() => {
            this.currentSortBy = 'size'
            this.sortFiles()
          })
        MenuItem({ content: '按修改日期' })
          .selected(this.currentSortBy === 'date')
          .selectIcon(true)
          .onClick(() => {
            this.currentSortBy = 'date'
            this.sortFiles()
          })
        MenuItem({ content: '按类型' })
          .selected(this.currentSortBy === 'type')
          .selectIcon(true)
          .onClick(() => {
            this.currentSortBy = 'type'
            this.sortFiles()
          })
      }
      MenuItemGroup({ header: '排序顺序' }) {
        MenuItem({ content: '升序' })
          .selected(this.sortAscending)
          .selectIcon(true)
          .onClick(() => {
            this.sortAscending = true
            this.sortFiles()
          })
        MenuItem({ content: '降序' })
          .selected(!this.sortAscending)
          .selectIcon(true)
          .onClick(() => {
            this.sortAscending = false
            this.sortFiles()
          })
      }
    }
  }

  @Builder
  ViewMenu() {
    Menu() {
      MenuItemGroup({ header: '视图模式' }) {
        MenuItem({ content: '列表视图' })
          .selected(this.viewMode === 'list')
          .selectIcon(true)
          .onClick(() => {
            this.viewMode = 'list'
            this.addLog('切换到列表视图')
          })
        MenuItem({ content: '网格视图' })
          .selected(this.viewMode === 'grid')
          .selectIcon(true)
          .onClick(() => {
            this.viewMode = 'grid'
            this.addLog('切换到网格视图')
          })
        MenuItem({ content: '详情视图' })
          .selected(this.viewMode === 'detail')
          .selectIcon(true)
          .onClick(() => {
            this.viewMode = 'detail'
            this.addLog('切换到详情视图')
          })
      }
    }
  }

  @Builder
  SelectionMenu() {
    Menu() {
      MenuItemGroup({ header: '选择操作' }) {
        MenuItem({ content: '全选', labelInfo: 'Ctrl+A' })
          .onClick(() => {
            this.files.forEach(f => f.selected = true)
            this.selectedFiles = new Set(this.files.map(f => f.id))
            this.addLog('全选所有文件')
          })
        MenuItem({ content: '取消全选', labelInfo: 'Ctrl+D' })
          .onClick(() => {
            this.files.forEach(f => f.selected = false)
            this.selectedFiles.clear()
            this.selectedFiles = new Set()
            this.addLog('取消全选')
          })
        MenuItem({ content: '反选' })
          .onClick(() => {
            this.files.forEach(f => {
              f.selected = !f.selected
              if (f.selected) {
                this.selectedFiles.add(f.id)
              } else {
                this.selectedFiles.delete(f.id)
              }
            })
            this.selectedFiles = new Set(this.selectedFiles)
            this.addLog('反选文件')
          })
        MenuItem({ content: '选择所有文件' })
          .onClick(() => {
            this.files.filter(f => f.type === 'file' || f.type === 'document')
              .forEach(f => {
                f.selected = true
                this.selectedFiles.add(f.id)
              })
            this.selectedFiles = new Set(this.selectedFiles)
            this.addLog('选择所有文件')
          })
        MenuItem({ content: '选择所有文件夹' })
          .onClick(() => {
            this.files.filter(f => f.type === 'folder')
              .forEach(f => {
                f.selected = true
                this.selectedFiles.add(f.id)
              })
            this.selectedFiles = new Set(this.selectedFiles)
            this.addLog('选择所有文件夹')
          })
      }
    }
  }

  sortFiles(): void {
    const sorted = [...this.files]
    switch (this.currentSortBy) {
      case 'name':
        sorted.sort((a, b) => a.name.localeCompare(b.name))
        break
      case 'size':
        sorted.sort((a, b) => {
          if (a.size === '-') return 1
          if (b.size === '-') return -1
          return parseFloat(a.size) - parseFloat(b.size)
        })
        break
      case 'date':
        sorted.sort((a, b) => b.modifiedDate.localeCompare(a.modifiedDate))
        break
      case 'type':
        sorted.sort((a, b) => a.type.localeCompare(b.type))
        break
    }
    if (!this.sortAscending) {
      sorted.reverse()
    }
    this.files = sorted
    this.addLog(`按${this.currentSortBy}${this.sortAscending ? '升序' : '降序'}排序`)
  }

  addLog(message: string): void {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog = `[${timestamp}] ${message}\n${this.eventLog}`
  }

  getFileIcon(type: string): Resource {
    return this.iconResource
  }

  build() {
    Column() {
      Scroll() {
        Column({ space: 20 }) {
          Text('菜单业务场景示例')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Column({ space: 15 }) {
            Text('文件管理器场景')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Button('排序')
                .fontSize(14)
                .width(70)
                .height(35)
                .bindMenu(this.SortMenu)

              Button('视图')
                .fontSize(14)
                .width(70)
                .height(35)
                .bindMenu(this.ViewMenu)

              Button('选择')
                .fontSize(14)
                .width(70)
                .height(35)
                .bindMenu(this.SelectionMenu)

              Button('设置')
                .fontSize(14)
                .width(70)
                .height(35)
                .bindMenu(this.SettingsContextMenu)

              Text(`已选择: ${this.selectedFiles.size} 项`)
                .fontSize(12)
                .fontColor('#666666')
            }
            .width('100%')

            List({ space: 8 }) {
              ForEach(this.files, (file: FileItem) => {
                ListItem() {
                  Row({ space: 10 }) {
                    Image(this.getFileIcon(file.type))
                      .width(32)
                      .height(32)
                    Column({ space: 2 }) {
                      Text(file.name)
                        .fontSize(14)
                        .fontWeight(FontWeight.Medium)
                      Row({ space: 10 }) {
                        Text(file.type)
                          .fontSize(10)
                          .fontColor('#666666')
                        Text(file.size)
                          .fontSize(10)
                          .fontColor('#666666')
                        Text(file.modifiedDate)
                          .fontSize(10)
                          .fontColor('#666666')
                      }
                    }
                    .alignItems(HorizontalAlign.Start)
                    .layoutWeight(1)
                    Checkbox()
                      .select(file.selected)
                      .onChange((isSelected: boolean) => {
                        file.selected = isSelected
                        if (isSelected) {
                          this.selectedFiles.add(file.id)
                        } else {
                          this.selectedFiles.delete(file.id)
                        }
                        this.selectedFiles = new Set(this.selectedFiles)
                      })
                  }
                  .width('100%')
                  .padding(10)
                  .backgroundColor(file.selected ? '#E3F2FD' : '#FFFFFF')
                  .borderRadius(8)
                  .borderWidth(1)
                  .borderColor('#E0E0E0')
                  .bindContextMenu(this.FileContextMenu(file), ResponseType.RightClick)
                }
              })
            }
            .width('100%')
            .height(250)
            .scrollBar(BarState.Auto)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('代码编辑器场景')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text(`自动保存: ${this.autoSave ? '开' : '关'}`)
                .fontSize(12)
                .fontColor('#666666')
              Text(`自动换行: ${this.wordWrap ? '开' : '关'}`)
                .fontSize(12)
                .fontColor('#666666')
              Text(`行号: ${this.lineNumbers ? '显示' : '隐藏'}`)
                .fontSize(12)
                .fontColor('#666666')
            }
            .width('100%')

            Column() {
              if (this.lineNumbers) {
                Row() {
                  Column() {
                    Text('1')
                      .fontSize(12)
                      .fontColor('#999999')
                    Text('2')
                      .fontSize(12)
                      .fontColor('#999999')
                    Text('3')
                      .fontSize(12)
                      .fontColor('#999999')
                    Text('4')
                      .fontSize(12)
                      .fontColor('#999999')
                    Text('5')
                      .fontSize(12)
                      .fontColor('#999999')
                  }
                  .width(30)
                  .padding({ top: 10 })

                  Column() {
                    Text('import { Component } from \'@kit.ArkUI\';')
                      .fontSize(12)
                      .fontColor('#0000FF')
                    Text('')
                      .fontSize(12)
                    Text('@Component')
                      .fontSize(12)
                      .fontColor('#008000')
                    Text('export struct MyComponent {')
                      .fontSize(12)
                      .fontColor('#000000')
                    Text('  build() { }')
                      .fontSize(12)
                      .fontColor('#000000')
                  }
                  .layoutWeight(1)
                  .padding({ top: 10 })
                }
              } else {
                Column() {
                  Text('import { Component } from \'@kit.ArkUI\';')
                    .fontSize(12)
                    .fontColor('#0000FF')
                  Text('')
                    .fontSize(12)
                  Text('@Component')
                    .fontSize(12)
                    .fontColor('#008000')
                  Text('export struct MyComponent {')
                    .fontSize(12)
                    .fontColor('#000000')
                  Text('  build() { }')
                    .fontSize(12)
                    .fontColor('#000000')
                }
                .padding(10)
              }
            }
            .width('100%')
            .height(150)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
            .bindContextMenu(this.EditorContextMenu, ResponseType.RightClick)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('图片查看器场景')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Text(`缩放: ${this.zoomLevel}%`)
                .fontSize(14)
                .fontColor('#666666')
            }
            .width('100%')

            Column() {
              Image($r('app.media.app_icon'))
                .width(100 * this.zoomLevel / 100)
                .height(100 * this.zoomLevel / 100)
                .objectFit(ImageFit.Contain)
            }
            .width('100%')
            .height(150)
            .backgroundColor('#E0E0E0')
            .borderRadius(8)
            .justifyContent(FlexAlign.Center)
            .bindContextMenu(this.ImageContextMenu, ResponseType.RightClick)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('状态信息')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 20 }) {
              Column() {
                Text('剪贴板')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.clipboardContent || '空')
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
              }

              Column() {
                Text('撤销栈')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.undoStack.length}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
              }

              Column() {
                Text('重做栈')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.redoStack.length}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
              }

              Column() {
                Text('主题模式')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.isDarkMode ? '暗色' : '亮色')
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)
            .padding(15)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 15 }) {
            Text('快捷操作')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Row({ space: 10 }) {
              Button('模拟编辑操作')
                .fontSize(12)
                .onClick(() => {
                  this.undoStack.push('编辑操作')
                  this.addLog('执行编辑操作')
                })

              Button('清空撤销栈')
                .fontSize(12)
                .onClick(() => {
                  this.undoStack = []
                  this.addLog('清空撤销栈')
                })

              Button('清空重做栈')
                .fontSize(12)
                .onClick(() => {
                  this.redoStack = []
                  this.addLog('清空重做栈')
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)

            Row({ space: 10 }) {
              Button('重置所有设置')
                .fontSize(12)
                .onClick(() => {
                  this.isDarkMode = false
                  this.showHiddenFiles = false
                  this.autoSave = true
                  this.wordWrap = true
                  this.lineNumbers = true
                  this.zoomLevel = 100
                  this.addLog('重置所有设置')
                })

              Button('重置文件列表')
                .fontSize(12)
                .onClick(() => {
                  this.initializeFiles()
                  this.selectedFiles.clear()
                  this.selectedFiles = new Set()
                  this.addLog('重置文件列表')
                })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)

          Column({ space: 10 }) {
            Text('事件日志')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')

            Column() {
              Text(this.eventLog || '暂无事件')
                .fontSize(12)
                .fontColor('#666666')
                .width('100%')
            }
            .width('100%')
            .height(150)
            .padding(10)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Button('清空日志')
              .fontSize(14)
              .onClick(() => {
                this.eventLog = ''
              })
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)
        }
        .width('100%')
        .padding({ left: 15, right: 15 })
      }
      .width('100%')
      .height('100%')
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F0F0')
  }
}
