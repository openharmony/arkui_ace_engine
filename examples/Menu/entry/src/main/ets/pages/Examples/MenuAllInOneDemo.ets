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

@Entry
@Component
struct MenuAllInOneDemo {
  scroller: Scroller = new Scroller()
  @State message: string = ''
  @State isShowMenu1: boolean = false
  @State selectedIndex: number = 0
  @State menuRadius: number = 12
  @State currentTheme: string = '浅色'
  @State currentLanguage: string = '简体中文'
  @State sortType: number = 0
  @State viewMode: number = 0
  @State fontSizeValue: number = 14
  @State opacityValue: number = 1.0
  @State zoomLevel: number = 100

  private iconStr: Resource = $r('app.media.app_icon')

  private basicMenuElements: Array<MenuElement> = [
    { value: '复制', action: () => { this.message = '复制操作已执行'; } },
    { value: '粘贴', action: () => { this.message = '粘贴操作已执行'; } },
    { value: '剪切', action: () => { this.message = '剪切操作已执行'; } },
    { value: '全选', action: () => { this.message = '全选操作已执行'; } }
  ]

  private iconMenuElements: Array<MenuElement> = [
    { value: '分享', icon: this.iconStr, action: () => { this.message = '分享功能已触发'; } },
    { value: '收藏', icon: this.iconStr, action: () => { this.message = '已添加到收藏'; } },
    { value: '下载', icon: this.iconStr, action: () => { this.message = '开始下载'; } },
    { value: '删除', icon: this.iconStr, action: () => { this.message = '删除操作已执行'; } }
  ]

  @Builder
  SimpleMenuBuilder() {
    Menu() {
      MenuItem({ content: '选项一' }).onClick(() => { this.message = '选项一被点击'; })
      MenuItem({ content: '选项二' }).onClick(() => { this.message = '选项二被点击'; })
      MenuItem({ content: '选项三' }).onClick(() => { this.message = '选项三被点击'; })
    }
    .width(160)
  }

  @Builder
  IconMenuBuilder() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '新建文件' })
      MenuItem({ startIcon: this.iconStr, content: '打开文件' })
      MenuItem({ startIcon: this.iconStr, content: '保存文件' })
      MenuItem({ startIcon: this.iconStr, content: '另存为' })
      MenuItem({})
      MenuItem({ startIcon: this.iconStr, content: '打印' })
    }
    .width(200)
  }

  @Builder
  GroupMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '文件操作' }) {
        MenuItem({ startIcon: this.iconStr, content: '新建' })
        MenuItem({ startIcon: this.iconStr, content: '打开' })
        MenuItem({ startIcon: this.iconStr, content: '保存' })
      }
      MenuItemGroup({ header: '编辑操作' }) {
        MenuItem({ startIcon: this.iconStr, content: '撤销' })
        MenuItem({ startIcon: this.iconStr, content: '重做' })
      }
      MenuItemGroup({ header: '其他' }) {
        MenuItem({ startIcon: this.iconStr, content: '设置' })
        MenuItem({ startIcon: this.iconStr, content: '帮助' })
      }
    }
    .width(200)
  }

  @Builder
  NestedMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件', startIcon: this.iconStr, builder: (): void => this.FileSubMenu() })
      MenuItem({ content: '编辑', startIcon: this.iconStr, builder: (): void => this.EditSubMenu() })
      MenuItem({ content: '视图', startIcon: this.iconStr, builder: (): void => this.ViewSubMenu() })
      MenuItem({ content: '帮助', startIcon: this.iconStr })
    }
    .width(180)
  }

  @Builder
  FileSubMenu() {
    MenuItem({ content: '新建', startIcon: this.iconStr })
    MenuItem({ content: '打开', startIcon: this.iconStr })
    MenuItem({ content: '保存', startIcon: this.iconStr })
    MenuItem({})
    MenuItem({ content: '退出', startIcon: this.iconStr })
  }

  @Builder
  EditSubMenu() {
    MenuItem({ content: '撤销', startIcon: this.iconStr })
    MenuItem({ content: '重做', startIcon: this.iconStr })
    MenuItem({})
    MenuItem({ content: '剪切', startIcon: this.iconStr })
    MenuItem({ content: '复制', startIcon: this.iconStr })
    MenuItem({ content: '粘贴', startIcon: this.iconStr })
  }

  @Builder
  ViewSubMenu() {
    MenuItem({ content: '放大', startIcon: this.iconStr })
    MenuItem({ content: '缩小', startIcon: this.iconStr })
    MenuItem({ content: '适应窗口', startIcon: this.iconStr })
    MenuItem({})
    MenuItem({ content: '全屏模式', startIcon: this.iconStr })
  }

  @Builder
  SelectedMenuBuilder() {
    Menu() {
      MenuItem({ content: '按名称排序' }).selected(this.sortType === 0)
        .onClick(() => { this.sortType = 0; this.message = '当前排序: 名称'; })
      MenuItem({ content: '按日期排序' }).selected(this.sortType === 1)
        .onClick(() => { this.sortType = 1; this.message = '当前排序: 日期'; })
      MenuItem({ content: '按大小排序' }).selected(this.sortType === 2)
        .onClick(() => { this.sortType = 2; this.message = '当前排序: 大小'; })
      MenuItem({ content: '按类型排序' }).selected(this.sortType === 3)
        .onClick(() => { this.sortType = 3; this.message = '当前排序: 类型'; })
    }
    .width(180)
  }

  @Builder
  DisabledMenuBuilder() {
    Menu() {
      MenuItem({ content: '启用选项1', startIcon: this.iconStr })
      MenuItem({ content: '禁用选项2', startIcon: this.iconStr }).enabled(false)
      MenuItem({ content: '启用选项3', startIcon: this.iconStr })
      MenuItem({ content: '禁用选项4', startIcon: this.iconStr }).enabled(false)
      MenuItem({ content: '启用选项5', startIcon: this.iconStr })
    }
    .width(200)
  }

  @Builder
  ContextMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', startIcon: this.iconStr })
      MenuItem({ content: '粘贴', startIcon: this.iconStr })
      MenuItem({ content: '剪切', startIcon: this.iconStr })
      MenuItem({})
      MenuItem({ content: '重命名', startIcon: this.iconStr })
      MenuItem({ content: '删除', startIcon: this.iconStr })
      MenuItem({})
      MenuItem({ content: '属性', startIcon: this.iconStr })
    }
    .width(180)
  }

  @Builder
  ShortcutMenuBuilder() {
    Menu() {
      MenuItem({ content: '新建', labelInfo: 'Ctrl+N', startIcon: this.iconStr })
      MenuItem({ content: '打开', labelInfo: 'Ctrl+O', startIcon: this.iconStr })
      MenuItem({ content: '保存', labelInfo: 'Ctrl+S', startIcon: this.iconStr })
      MenuItem({})
      MenuItem({ content: '撤销', labelInfo: 'Ctrl+Z', startIcon: this.iconStr })
      MenuItem({ content: '退出', labelInfo: 'Alt+F4', startIcon: this.iconStr })
    }
    .width(220)
  }

  @Builder
  ThemeMenuBuilder() {
    Menu() {
      MenuItem({ content: '浅色模式' }).selected(this.currentTheme === '浅色')
        .onClick(() => { this.currentTheme = '浅色'; this.message = '主题已切换为浅色'; })
      MenuItem({ content: '深色模式' }).selected(this.currentTheme === '深色')
        .onClick(() => { this.currentTheme = '深色'; this.message = '主题已切换为深色'; })
      MenuItem({ content: '跟随系统' }).selected(this.currentTheme === '系统')
        .onClick(() => { this.currentTheme = '系统'; this.message = '主题已切换为跟随系统'; })
    }
    .width(180)
  }

  @Builder
  LanguageMenuBuilder() {
    Menu() {
      MenuItem({ content: '简体中文' }).selected(this.currentLanguage === '简体中文')
        .onClick(() => { this.currentLanguage = '简体中文'; this.message = '语言已切换'; })
      MenuItem({ content: '繁体中文' }).selected(this.currentLanguage === '繁体中文')
        .onClick(() => { this.currentLanguage = '繁体中文'; })
      MenuItem({ content: 'English' }).selected(this.currentLanguage === 'English')
        .onClick(() => { this.currentLanguage = 'English'; })
      MenuItem({ content: '日本語' }).selected(this.currentLanguage === '日本語')
        .onClick(() => { this.currentLanguage = '日本語'; })
    }
    .width(160)
  }

  @Builder
  ViewModeMenuBuilder() {
    Menu() {
      MenuItem({ content: '列表视图', startIcon: this.iconStr }).selected(this.viewMode === 0)
        .onClick(() => { this.viewMode = 0; this.message = '视图模式: 列表'; })
      MenuItem({ content: '网格视图', startIcon: this.iconStr }).selected(this.viewMode === 1)
        .onClick(() => { this.viewMode = 1; this.message = '视图模式: 网格'; })
      MenuItem({ content: '缩略图视图', startIcon: this.iconStr }).selected(this.viewMode === 2)
        .onClick(() => { this.viewMode = 2; this.message = '视图模式: 缩略图'; })
    }
    .width(180)
  }

  @Builder
  DividerMenuBuilder() {
    Menu() {
      MenuItem({ content: '选项A' })
      MenuItem({})
      MenuItem({ content: '选项B' })
      MenuItem({ content: '选项C' })
      MenuItem({})
      MenuItem({ content: '选项D' })
    }
    .width(160)
  }

  @Builder
  ThreeLevelMenuBuilder() {
    Menu() {
      MenuItem({ content: '一级菜单1', startIcon: this.iconStr, builder: (): void => this.Level2Menu1() })
      MenuItem({ content: '一级菜单2', startIcon: this.iconStr, builder: (): void => this.Level2Menu2() })
      MenuItem({ content: '一级菜单3', startIcon: this.iconStr })
    }
    .width(180)
  }

  @Builder
  Level2Menu1() {
    MenuItem({ content: '二级菜单1-1', builder: (): void => this.Level3Menu1() })
    MenuItem({ content: '二级菜单1-2' })
  }

  @Builder
  Level2Menu2() {
    MenuItem({ content: '二级菜单2-1' })
    MenuItem({ content: '二级菜单2-2' })
  }

  @Builder
  Level3Menu1() {
    MenuItem({ content: '三级菜单1-1-1' })
    MenuItem({ content: '三级菜单1-1-2' })
  }

  @Builder
  SideExpandMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件', startIcon: this.iconStr, builder: (): void => this.FileSubMenu() })
      MenuItem({ content: '编辑', startIcon: this.iconStr, builder: (): void => this.EditSubMenu() })
    }
    .width(180)
    .subMenuExpandingMode(SubMenuExpandingMode.SIDE_EXPAND)
  }

  @Builder
  EmbeddedExpandMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件', startIcon: this.iconStr, builder: (): void => this.FileSubMenu() })
      MenuItem({ content: '编辑', startIcon: this.iconStr, builder: (): void => this.EditSubMenu() })
    }
    .width(180)
    .subMenuExpandingMode(SubMenuExpandingMode.EMBEDDED_EXPAND)
  }

  @Builder
  CustomContentMenuBuilder() {
    Menu() {
      MenuItem() {
        Row() {
          Image(this.iconStr).width(40).height(40).borderRadius(20).margin({ right: 12 })
          Column() {
            Text('张三').fontSize(16).fontWeight(FontWeight.Medium)
            Text('zhangsan@example.com').fontSize(12).fontColor('#888888')
          }.alignItems(HorizontalAlign.Start)
        }.width('100%').padding(8)
      }
      MenuItem({})
      MenuItem({ content: '个人资料', startIcon: this.iconStr })
      MenuItem({ content: '账户设置', startIcon: this.iconStr })
      MenuItem({})
      MenuItem({ content: '退出登录', startIcon: this.iconStr })
    }
    .width(260)
  }

  @Builder
  PreviewMenuBuilder() {
    Menu() {
      MenuItem({ content: '分享', startIcon: this.iconStr })
      MenuItem({ content: '复制链接', startIcon: this.iconStr })
      MenuItem({})
      MenuItem({ content: '保存图片', startIcon: this.iconStr })
      MenuItem({ content: '下载', startIcon: this.iconStr })
    }
    .width(180)
  }

  @Builder
  PreviewBuilder() {
    Column() {
      Image(this.iconStr).width(100).height(100).objectFit(ImageFit.Cover).borderRadius(12)
      Text('预览内容').fontSize(14).margin({ top: 8 })
    }
    .backgroundColor('#f5f5f5')
    .borderRadius(16)
    .padding(12)
  }

  @Builder
  DynamicMenuBuilder() {
    Menu() {
      MenuItem({ content: `当前圆角: ${this.menuRadius}` }).enabled(false)
      MenuItem({})
      MenuItem({ content: '选项1', startIcon: this.iconStr })
      MenuItem({ content: '选项2', startIcon: this.iconStr })
    }
    .width(200)
    .radius(this.menuRadius)
  }

  @Builder
  AnimatedMenuBuilder() {
    Menu() {
      MenuItem({ content: '淡入效果', startIcon: this.iconStr })
        .onClick(() => { this.message = '淡入效果已选择'; })
      MenuItem({ content: '缩放效果', startIcon: this.iconStr })
        .onClick(() => { this.message = '缩放效果已选择'; })
      MenuItem({ content: '滑动效果', startIcon: this.iconStr })
        .onClick(() => { this.message = '滑动效果已选择'; })
      MenuItem({})
      MenuItem({ content: '组合动画', startIcon: this.iconStr })
        .onClick(() => { this.message = '组合动画已选择'; })
    }
    .width(180)
  }

  @Builder
  BorderMenuBuilder() {
    Menu() {
      MenuItem({ content: '无边框', startIcon: this.iconStr })
        .onClick(() => { this.message = '无边框样式'; })
      MenuItem({ content: '细边框', startIcon: this.iconStr })
        .onClick(() => { this.message = '细边框样式'; })
      MenuItem({ content: '粗边框', startIcon: this.iconStr })
        .onClick(() => { this.message = '粗边框样式'; })
      MenuItem({ content: '虚线边框', startIcon: this.iconStr })
        .onClick(() => { this.message = '虚线边框样式'; })
    }
    .width(180)
  }

  @Builder
  FontStyleMenuBuilder() {
    Menu() {
      MenuItem({ content: '字号12', startIcon: this.iconStr })
        .onClick(() => { this.fontSizeValue = 12; this.message = '字号设置为12'; })
      MenuItem({ content: '字号14', startIcon: this.iconStr })
        .onClick(() => { this.fontSizeValue = 14; this.message = '字号设置为14'; })
      MenuItem({ content: '字号16', startIcon: this.iconStr })
        .onClick(() => { this.fontSizeValue = 16; this.message = '字号设置为16'; })
      MenuItem({ content: '字号18', startIcon: this.iconStr })
        .onClick(() => { this.fontSizeValue = 18; this.message = '字号设置为18'; })
      MenuItem({})
      MenuItem({ content: '加粗', startIcon: this.iconStr })
        .onClick(() => { this.message = '字体加粗'; })
      MenuItem({ content: '斜体', startIcon: this.iconStr })
        .onClick(() => { this.message = '字体斜体'; })
    }
    .width(180)
  }

  @Builder
  BackgroundColorMenuBuilder() {
    Menu() {
      MenuItem({ content: '白色背景', startIcon: this.iconStr })
        .onClick(() => { this.message = '背景色: 白色'; })
      MenuItem({ content: '浅灰背景', startIcon: this.iconStr })
        .onClick(() => { this.message = '背景色: 浅灰'; })
      MenuItem({ content: '浅蓝背景', startIcon: this.iconStr })
        .onClick(() => { this.message = '背景色: 浅蓝'; })
      MenuItem({ content: '浅绿背景', startIcon: this.iconStr })
        .onClick(() => { this.message = '背景色: 浅绿'; })
    }
    .width(180)
  }

  @Builder
  ZoomMenuBuilder() {
    Menu() {
      MenuItem({ content: '50%', startIcon: this.iconStr }).selected(this.zoomLevel === 50)
        .onClick(() => { this.zoomLevel = 50; this.message = '缩放: 50%'; })
      MenuItem({ content: '75%', startIcon: this.iconStr }).selected(this.zoomLevel === 75)
        .onClick(() => { this.zoomLevel = 75; this.message = '缩放: 75%'; })
      MenuItem({ content: '100%', startIcon: this.iconStr }).selected(this.zoomLevel === 100)
        .onClick(() => { this.zoomLevel = 100; this.message = '缩放: 100%'; })
      MenuItem({ content: '125%', startIcon: this.iconStr }).selected(this.zoomLevel === 125)
        .onClick(() => { this.zoomLevel = 125; this.message = '缩放: 125%'; })
      MenuItem({ content: '150%', startIcon: this.iconStr }).selected(this.zoomLevel === 150)
        .onClick(() => { this.zoomLevel = 150; this.message = '缩放: 150%'; })
      MenuItem({ content: '200%', startIcon: this.iconStr }).selected(this.zoomLevel === 200)
        .onClick(() => { this.zoomLevel = 200; this.message = '缩放: 200%'; })
    }
    .width(180)
  }

  @Builder
  OpacityMenuBuilder() {
    Menu() {
      MenuItem({ content: '不透明', startIcon: this.iconStr }).selected(this.opacityValue === 1.0)
        .onClick(() => { this.opacityValue = 1.0; this.message = '不透明度: 100%'; })
      MenuItem({ content: '75%透明度', startIcon: this.iconStr }).selected(this.opacityValue === 0.75)
        .onClick(() => { this.opacityValue = 0.75; this.message = '不透明度: 75%'; })
      MenuItem({ content: '50%透明度', startIcon: this.iconStr }).selected(this.opacityValue === 0.5)
        .onClick(() => { this.opacityValue = 0.5; this.message = '不透明度: 50%'; })
      MenuItem({ content: '25%透明度', startIcon: this.iconStr }).selected(this.opacityValue === 0.25)
        .onClick(() => { this.opacityValue = 0.25; this.message = '不透明度: 25%'; })
    }
    .width(180)
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Menu组件全功能示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .fontColor(0xFFFFFF)
          .textAlign(TextAlign.Center)
          .width('100%')
          .height(60)
          .backgroundColor('#1976D2')

        if (this.message) {
          Text(`状态: ${this.message}`)
            .fontSize(14)
            .fontColor('#1976D2')
            .backgroundColor('#E3F2FD')
            .padding(10)
            .borderRadius(8)
            .margin({ top: 10, bottom: 10 })
        }

        Column({ space: 12 }) {
          Text('1. 基本菜单使用')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示基本菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#E3F2FD')
            .borderRadius(8)
            .bindMenu(this.basicMenuElements, { title: '编辑操作', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .margin({ top: 15 })

        Column({ space: 12 }) {
          Text('2. 自定义Builder菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示自定义菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#E8F5E9')
            .borderRadius(8)
            .bindMenu(this.SimpleMenuBuilder, { title: '自定义菜单', borderRadius: 20 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('3. 带图标菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示带图标菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#FFF3E0')
            .borderRadius(8)
            .bindMenu(this.IconMenuBuilder, { title: '文件操作', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('4. 菜单位置放置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('Top').fontSize(14).padding(10).backgroundColor('#FCE4EC').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '上方', placement: Placement.Top })
            Text('Bottom').fontSize(14).padding(10).backgroundColor('#F3E5F5').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '下方', placement: Placement.Bottom })
            Text('Left').fontSize(14).padding(10).backgroundColor('#E0F7FA').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '左侧', placement: Placement.Left })
            Text('Right').fontSize(14).padding(10).backgroundColor('#E8EAF6').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '右侧', placement: Placement.Right })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('5. 更多位置选项')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 8 }) {
            Text('TopLeft').fontSize(12).padding(8).backgroundColor('#FFFDE7').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '左上', placement: Placement.TopLeft })
            Text('TopRight').fontSize(12).padding(8).backgroundColor('#EFEBE9').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '右上', placement: Placement.TopRight })
            Text('BottomLeft').fontSize(12).padding(8).backgroundColor('#E1F5FE').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '左下', placement: Placement.BottomLeft })
            Text('BottomRight').fontSize(12).padding(8).backgroundColor('#E0F2F1').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '右下', placement: Placement.BottomRight })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('6. 菜单圆角样式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('圆角0').fontSize(14).padding(10).backgroundColor('#C8E6C9').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '无圆角', borderRadius: 0 })
            Text('圆角12').fontSize(14).padding(10).backgroundColor('#DCEDC8').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '中等圆角', borderRadius: 12 })
            Text('圆角24').fontSize(14).padding(10).backgroundColor('#F0F4C3').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '大圆角', borderRadius: 24 })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('7. 菜单偏移设置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('偏移(0,0)').fontSize(14).padding(10).backgroundColor('#FFF9C4').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '无偏移', offset: { x: 0, y: 0 } })
            Text('偏移(20,10)').fontSize(14).padding(10).backgroundColor('#FFECB3').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '右下偏移', offset: { x: 20, y: 10 } })
            Text('偏移(-20,0)').fontSize(14).padding(10).backgroundColor('#FFE0B2').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '左偏移', offset: { x: -20, y: 0 } })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('8. 菜单遮罩效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('无遮罩').fontSize(14).padding(10).backgroundColor('#FFCCBC').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '无遮罩', mask: false })
            Text('有遮罩').fontSize(14).padding(10).backgroundColor('#D7CCC8').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '有遮罩', mask: true })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('9. 箭头显示设置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('显示箭头').fontSize(14).padding(10).backgroundColor('#CFD8DC').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '有箭头', enableArrow: true })
            Text('隐藏箭头').fontSize(14).padding(10).backgroundColor('#B0BEC5').borderRadius(6)
              .bindMenu(this.basicMenuElements, { title: '无箭头', enableArrow: false })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('10. 菜单分组显示')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示分组菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#BBDEFB')
            .borderRadius(8)
            .bindMenu(this.GroupMenuBuilder, { title: '分组菜单', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('11. 嵌套子菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示嵌套菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#90CAF9')
            .borderRadius(8)
            .bindMenu(this.NestedMenuBuilder, { title: '嵌套菜单', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('12. 三级嵌套菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示三级菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#64B5F6')
            .borderRadius(8)
            .bindMenu(this.ThreeLevelMenuBuilder, { title: '三级菜单', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('13. 侧边展开模式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示侧边展开菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#42A5F5')
            .borderRadius(8)
            .bindMenu(this.SideExpandMenuBuilder, { title: '侧边展开', placement: Placement.Right })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('14. 嵌入式展开模式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示嵌入式菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#2196F3')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.EmbeddedExpandMenuBuilder, { title: '嵌入式展开' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('15. 菜单选中状态')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text(`当前排序: ${['名称', '日期', '大小', '类型'][this.sortType]}`)
            .fontSize(18)
            .padding(15)
            .backgroundColor('#1E88E5')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.SelectedMenuBuilder, { title: '排序方式' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('16. 菜单禁用状态')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示禁用状态菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#1976D2')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.DisabledMenuBuilder, { title: '禁用状态' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('17. 上下文菜单 (长按)')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('长按显示上下文菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#1565C0')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindContextMenu(this.ContextMenuBuilder, ResponseType.LongPress, { placement: Placement.Bottom })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('18. 右键上下文菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('右键显示上下文菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#0D47A1')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindContextMenu(this.ContextMenuBuilder, ResponseType.RightClick, { placement: Placement.Bottom })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('19. 键盘快捷键菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示快捷键菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#0277BD')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.ShortcutMenuBuilder, { title: '快捷键' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('20. 主题选择菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text(`当前主题: ${this.currentTheme}`)
            .fontSize(18)
            .padding(15)
            .backgroundColor('#01579B')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.ThemeMenuBuilder, { title: '主题设置' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('21. 语言选择菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text(`当前语言: ${this.currentLanguage}`)
            .fontSize(18)
            .padding(15)
            .backgroundColor('#00838F')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.LanguageMenuBuilder, { title: '语言设置' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('22. 视图模式菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text(`当前视图: ${['列表', '网格', '缩略图'][this.viewMode]}`)
            .fontSize(18)
            .padding(15)
            .backgroundColor('#00695C')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.ViewModeMenuBuilder, { title: '视图模式' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('23. 分割线样式菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示分割线菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#004D40')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.DividerMenuBuilder, { title: '分割线样式' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('24. 自定义内容菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示自定义内容菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#1B5E20')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.CustomContentMenuBuilder, { title: '用户菜单' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('25. 预览图上下文菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('长按显示预览菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#33691E')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindContextMenu(this.PreviewMenuBuilder, ResponseType.LongPress, {
              preview: this.PreviewBuilder(),
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('26. 动态圆角菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('动态菜单')
              .fontSize(18)
              .padding(15)
              .backgroundColor('#F57F17')
              .borderRadius(8)
              .fontColor(Color.White)
              .bindMenu(this.DynamicMenuBuilder, { title: '动态圆角', borderRadius: this.menuRadius })
            Column() {
              Text(`圆角值: ${this.menuRadius}`).fontSize(12)
              Slider({ min: 0, max: 30, value: this.menuRadius, step: 2 })
                .onChange((value: number) => { this.menuRadius = value })
                .width(120)
            }
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('27. 状态控制菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击切换菜单显示')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#E65100')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.isShowMenu1, this.basicMenuElements, { title: '状态控制' })
            .onClick(() => { this.isShowMenu1 = !this.isShowMenu1 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('28. 图标菜单元素')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示图标元素菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#BF360C')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu(this.iconMenuElements, { title: '图标菜单', enableArrow: true })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('29. 组合功能菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Row({ space: 10 }) {
            Text('带箭头+遮罩').fontSize(12).padding(10).backgroundColor('#4E342E').borderRadius(6).fontColor(Color.White)
              .bindMenu(this.basicMenuElements, { title: '组合1', enableArrow: true, mask: true })
            Text('圆角+偏移').fontSize(12).padding(10).backgroundColor('#3E2723').borderRadius(6).fontColor(Color.White)
              .bindMenu(this.basicMenuElements, { title: '组合2', borderRadius: 16, offset: { x: 10, y: 5 } })
            Text('全部属性').fontSize(12).padding(10).backgroundColor('#212121').borderRadius(6).fontColor(Color.White)
              .bindMenu(this.basicMenuElements, { title: '组合3', enableArrow: true, mask: true, borderRadius: 12 })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('30. 大量选项菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示大量选项菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#546E7A')
            .borderRadius(8)
            .fontColor(Color.White)
            .bindMenu([
              { value: '选项1', action: () => { this.message = '选择了选项1' } },
              { value: '选项2', action: () => { this.message = '选择了选项2' } },
              { value: '选项3', action: () => { this.message = '选择了选项3' } },
              { value: '选项4', action: () => { this.message = '选择了选项4' } },
              { value: '选项5', action: () => { this.message = '选择了选项5' } },
              { value: '选项6', action: () => { this.message = '选择了选项6' } },
              { value: '选项7', action: () => { this.message = '选择了选项7' } },
              { value: '选项8', action: () => { this.message = '选择了选项8' } }
            ], { title: '大量选项' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .margin({ bottom: 30 })

        Column({ space: 12 }) {
          Text('31. 动画效果菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示动画菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#FF9800')
            .borderRadius(8)
            .bindMenu(this.AnimatedMenuBuilder, { title: '动画效果' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('32. 边框样式菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示边框菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#FFA726')
            .borderRadius(8)
            .bindMenu(this.BorderMenuBuilder, { title: '边框样式' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('33. 字体样式菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示字体菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#CE93D8')
            .borderRadius(8)
            .bindMenu(this.FontStyleMenuBuilder, { title: '字体样式' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 12 }) {
          Text('34. 背景颜色菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
          Text('点击显示背景菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#B39DDB')
            .borderRadius(8)
            .bindMenu(this.BackgroundColorMenuBuilder, { title: '背景颜色' })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .margin({ bottom: 30 })
      }
    }
    .backgroundColor('#F5F5F5')
  }
}
