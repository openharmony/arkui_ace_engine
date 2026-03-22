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

import router from '@ohos.router';

interface ListCategories {
  title: string,
  url: string
}

@Entry
@Component
struct MenuComprehensiveDemo {
  scroller: Scroller = new Scroller()
  @State message: string = '';
  @State isShowMenu1: boolean = false;
  @State isShowMenu2: boolean = false;
  @State isShowMenu3: boolean = false;
  @State isShowMenu4: boolean = false;
  @State isShowMenu5: boolean = false;
  @State isShowMenu6: boolean = false;
  @State isShowMenu7: boolean = false;
  @State isShowMenu8: boolean = false;
  @State isShowMenu9: boolean = false;
  @State isShowMenu10: boolean = false;
  @State isShowMenu11: boolean = false;
  @State isShowMenu12: boolean = false;
  @State isShowMenu13: boolean = false;
  @State isShowMenu14: boolean = false;
  @State isShowMenu15: boolean = false;
  @State isShowMenu16: boolean = false;
  @State isShowMenu17: boolean = false;
  @State isShowMenu18: boolean = false;
  @State isShowMenu19: boolean = false;
  @State isShowMenu20: boolean = false;
  @State selectedIndex: number = 0;
  @State menuRadius: number = 12;
  @State menuWidth: number = 200;
  @State menuOffsetX: number = 0;
  @State menuOffsetY: number = 0;

  private items: ListCategories[] = [
    { title: '示例1: 基本菜单使用', url: 'pages/Examples/MenuComprehensiveBasic' },
    { title: '示例2: 自定义构建器菜单', url: 'pages/Examples/MenuComprehensiveBuilder' },
    { title: '示例3: 带图标菜单', url: 'pages/Examples/MenuComprehensiveIcons' },
    { title: '示例4: 菜单位置放置', url: 'pages/Examples/MenuComprehensivePlacement' },
    { title: '示例5: 菜单圆角样式', url: 'pages/Examples/MenuComprehensiveRadius' },
    { title: '示例6: 菜单宽度设置', url: 'pages/Examples/MenuComprehensiveWidth' },
    { title: '示例7: 菜单偏移设置', url: 'pages/Examples/MenuComprehensiveOffset' },
    { title: '示例8: 菜单阴影效果', url: 'pages/Examples/MenuComprehensiveShadow' },
    { title: '示例9: 菜单遮罩效果', url: 'pages/Examples/MenuComprehensiveMask' },
    { title: '示例10: 菜单动画效果', url: 'pages/Examples/MenuComprehensiveAnimation' },
    { title: '示例11: 菜单分组显示', url: 'pages/Examples/MenuComprehensiveGroup' },
    { title: '示例12: 嵌套子菜单', url: 'pages/Examples/MenuComprehensiveNested' },
    { title: '示例13: 菜单选中状态', url: 'pages/Examples/MenuComprehensiveSelected' },
    { title: '示例14: 菜单禁用状态', url: 'pages/Examples/MenuComprehensiveDisabled' },
    { title: '示例15: 上下文菜单', url: 'pages/Examples/MenuComprehensiveContext' },
    { title: '示例16: 预览图菜单', url: 'pages/Examples/MenuComprehensivePreview' },
    { title: '示例17: 键盘快捷键菜单', url: 'pages/Examples/MenuComprehensiveShortcut' },
    { title: '示例18: 系统材质菜单', url: 'pages/Examples/MenuComprehensiveSystem' },
    { title: '示例19: 混合菜单', url: 'pages/Examples/MenuComprehensiveMixed' },
    { title: '示例20: 完整配置菜单', url: 'pages/Examples/MenuComprehensiveFull' },
  ]

  private basicMenuElements: Array<MenuElement> = [
    { value: '复制', action: () => { this.message = '复制 clicked'; } },
    { value: '粘贴', action: () => { this.message = '粘贴 clicked'; } },
    { value: '剪切', action: () => { this.message = '剪切 clicked'; } },
    { value: '全选', action: () => { this.message = '全选 clicked'; } }
  ];

  private iconMenuElements: Array<MenuElement> = [
    { value: '分享', icon: $r('app.media.app_icon'), action: () => { this.message = '分享 clicked'; } },
    { value: '复制链接', icon: $r('app.media.app_icon'), action: () => { this.message = '复制链接 clicked'; } },
    { value: '移动', icon: $r('app.media.app_icon'), action: () => { this.message = '移动 clicked'; } },
    { value: '重命名', icon: $r('app.media.app_icon'), action: () => { this.message = '重命名 clicked'; } },
    { value: '删除', icon: $r('app.media.app_icon'), action: () => { this.message = '删除 clicked'; } }
  ];

  @Builder
  SimpleMenuBuilder() {
    Menu() {
      MenuItem({ content: '选项1' })
      MenuItem({ content: '选项2' })
      MenuItem({ content: '选项3' })
    }
    .width(150)
  }

  @Builder
  IconMenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '图片' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '视频' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '文档' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '音频' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '压缩包' })
    }
    .width(180)
  }

  @Builder
  GroupMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '主要操作' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '保存' })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '另存为' })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '导出' })
      }
      MenuItemGroup({ header: '次要操作' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '打印' })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '分享' })
      }
      MenuItemGroup({ header: '系统' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '设置' })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '帮助' })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '关于' })
      }
    }
    .width(220)
  }

  @Builder
  NestedMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '编辑', startIcon: $r('app.media.app_icon') })
      MenuItem({
        content: '视图',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '放大', startIcon: $r('app.media.app_icon') }),
          MenuItem({ content: '缩小', startIcon: $r('app.media.app_icon') }),
          MenuItem({
            content: '全屏',
            startIcon: $r('app.media.app_icon'),
            children: [
              MenuItem({ content: '横屏' }),
              MenuItem({ content: '竖屏' }),
              MenuItem({ content: '自动旋转' })
            ]
          })
        ]
      })
      MenuItem({
        content: '工具',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '开发者选项' }),
          MenuItem({ content: '性能监视器' }),
          MenuItem({ content: '调试模式' })
        ]
      })
      MenuItem({ content: '帮助', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  SelectedMenuBuilder() {
    Menu() {
      MenuItem({ content: '名称' })
        .selected(this.selectedIndex === 0)
        .onClick(() => { this.selectedIndex = 0; this.message = '按名称排序'; })
      MenuItem({ content: '修改日期' })
        .selected(this.selectedIndex === 1)
        .onClick(() => { this.selectedIndex = 1; this.message = '按日期排序'; })
      MenuItem({ content: '大小' })
        .selected(this.selectedIndex === 2)
        .onClick(() => { this.selectedIndex = 2; this.message = '按大小排序'; })
      MenuItem({ content: '类型' })
        .selected(this.selectedIndex === 3)
        .onClick(() => { this.selectedIndex = 3; this.message = '按类型排序'; })
    }
    .width(180)
  }

  @Builder
  DisabledMenuBuilder() {
    Menu() {
      MenuItem({ content: '启用选项1', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '禁用选项2', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '启用选项3', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '禁用选项4', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '启用选项5', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  ContextMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '粘贴', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '剪切', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '属性', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
    }
    .width(180)
  }

  @Builder
  ShortcutMenuBuilder() {
    Menu() {
      MenuItem({ content: '新建', description: 'Ctrl+N', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '打开', description: 'Ctrl+O', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '保存', description: 'Ctrl+S', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '另存为', description: 'Ctrl+Shift+S', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '退出', description: 'Alt+F4', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  SystemMenuBuilder() {
    Menu() {
      MenuItem({ content: '系统选项1' })
      MenuItem({ content: '系统选项2' })
      MenuItem({ content: '系统选项3' })
    }
    .width(180)
  }

  @Builder
  MixedMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '自定义内容' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(24)
              .height(24)
              .margin({ right: 10 })
            Column() {
              Text('用户头像')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('user@example.com')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }

        MenuItem({ content: '我的文件', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '共享文件', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '最近文件', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '收藏夹', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '回收站', startIcon: $r('app.media.app_icon') })

        MenuItem() {
          Row() {
            Text('存储空间')
              .fontSize(14)
            Text('75% 已使用')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }

        MenuItem({ content: '升级存储空间', startIcon: $r('app.media.app_icon') })
      }
    }
    .width(240)
  }

  @Builder
  FullConfigMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '完整配置菜单' }) {
        MenuItem({ content: '带图标的选项', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '带描述的选项', description: 'Ctrl+Click' })
        MenuItem({ content: '选中的选项' })
          .selected(true)
        MenuItem({ content: '禁用的选项', enabled: false })
        MenuItem({})
        MenuItem({ content: '普通选项' })
      }
    }
    .width(220)
    .radius(this.menuRadius)
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Menu综合示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0xFFFFFF)
          .textAlign(TextAlign.Center)
          .width('100%')
          .height(50)
          .backgroundColor('#2ebd82')

        Column({ space: 15 }) {
          Text('1. 基本菜单使用')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.basicMenuElements, {
              title: '编辑选项',
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)
        .margin({ top: 10 })

        Column({ space: 15 }) {
          Text('2. 自定义构建器菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示自定义菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.SimpleMenuBuilder, {
              title: '自定义菜单',
              enableArrow: true,
              borderRadius: 20
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 带图标菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示带图标菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.iconMenuElements, {
              title: '带图标',
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 菜单位置放置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('Top')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '上方菜单',
                placement: Placement.Top
              })

            Text('Bottom')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '下方菜单',
                placement: Placement.Bottom
              })

            Text('Left')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '左侧菜单',
                placement: Placement.Start
              })

            Text('Right')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '右侧菜单',
                placement: Placement.End
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 菜单圆角样式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('圆角0')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '圆角菜单',
                borderRadius: 0,
                placement: Placement.Bottom
              })

            Text('圆角12')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '圆角菜单',
                borderRadius: 12,
                placement: Placement.Bottom
              })

            Text('圆角24')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '圆角菜单',
                borderRadius: 24,
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 菜单宽度设置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('宽度100')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#c8e6c9')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '窄菜单',
                menuWidth: 100,
                placement: Placement.Bottom
              })

            Text('宽度200')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#c8e6c9')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '中菜单',
                menuWidth: 200,
                placement: Placement.Bottom
              })

            Text('宽度300')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#c8e6c9')
              .borderRadius(5)
              .bindMenu(this.basicMenuElements, {
                title: '宽菜单',
                menuWidth: 300,
                placement: Placement.Bottom
              })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('7. 菜单偏移设置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带偏移的菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#bbdefb')
            .borderRadius(8)
            .bindMenu(this.basicMenuElements, {
              title: '偏移菜单',
              offset: { x: 20, y: 10 },
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('8. 菜单阴影效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带阴影的菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d1c4e9')
            .borderRadius(8)
            .bindMenu(this.basicMenuElements, {
              title: '阴影菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('9. 菜单遮罩效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('右键显示带遮罩菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#cfd8dc')
            .borderRadius(8)
            .bindContextMenu(this.basicMenuElements, ResponseType.RightClick, {
              title: '遮罩菜单',
              maskColor: '#80000000',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('10. 菜单动画效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击切换显示菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2ebf2')
            .borderRadius(8)
            .bindMenu(this.isShowMenu10, this.basicMenuElements, {
              title: '动画菜单',
              placement: Placement.Bottom
            })
            .onClick(() => {
              this.isShowMenu10 = !this.isShowMenu10;
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('11. 菜单分组显示')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示分组菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff8e1')
            .borderRadius(8)
            .bindMenu(this.GroupMenuBuilder, {
              title: '分组菜单',
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('12. 嵌套子菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示嵌套菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffecb3')
            .borderRadius(8)
            .bindMenu(this.NestedMenuBuilder, {
              title: '嵌套菜单',
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('13. 菜单选中状态')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示选中菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e1bee7')
            .borderRadius(8)
            .bindMenu(this.SelectedMenuBuilder, {
              title: '排序方式',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('14. 菜单禁用状态')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示禁用菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffcdd2')
            .borderRadius(8)
            .bindMenu(this.DisabledMenuBuilder, {
              title: '禁用状态',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('15. 上下文菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示上下文菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b9f6ca')
            .borderRadius(8)
            .bindContextMenu(this.ContextMenuBuilder, ResponseType.LongPress, {
              title: '上下文菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('16. 键盘快捷键菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示快捷键菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffccbc')
            .borderRadius(8)
            .bindMenu(this.ShortcutMenuBuilder, {
              title: '快捷键',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('17. 系统材质菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示系统菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#cad2c5')
            .borderRadius(8)
            .bindMenu(this.SystemMenuBuilder, {
              title: '系统菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('18. 混合菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示混合菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d4e0e8')
            .borderRadius(8)
            .bindMenu(this.MixedMenuBuilder, {
              title: '混合菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('19. 完整配置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('圆角调整')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e8eaf6')
              .borderRadius(5)
              .bindMenu(this.FullConfigMenuBuilder, {
                title: '完整配置',
                borderRadius: this.menuRadius,
                placement: Placement.Bottom
              })

            Slider({
              min: 0,
              max: 30,
              value: this.menuRadius,
              step: 2
            })
              .onChange((value: number) => {
                this.menuRadius = value;
              })
              .width(100)
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        if (this.message) {
          Text(`选择: ${this.message}`)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 10 })
            .padding(10);
        }

        Column({ space: 15 }) {
          Text('20. 更多示例')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击跳转到更多Menu示例')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#2ebd82')
            .borderRadius(8)
            .fontColor(Color.White)
            .onClick(() => {
              router.pushUrl({ url: 'pages/Examples/Index' });
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)
        .margin({ bottom: 20 })

        Column({ space: 15 }) {
          Text('21. 文件操作菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('文件操作')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.buildFileOperationMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('22. 编辑操作菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('编辑操作')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.buildEditMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('23. 视图操作菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('视图操作')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.buildViewMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('24. 排序选项菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('排序选项')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindMenu(this.buildSortMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('25. 筛选选项菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('筛选选项')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e0e0e0')
            .borderRadius(8)
            .bindMenu(this.buildFilterMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('26. 用户信息菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('用户信息')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e1bee7')
            .borderRadius(8)
            .bindMenu(this.buildUserMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('27. 设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('应用设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#bbdefb')
            .borderRadius(8)
            .bindMenu(this.buildSettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('28. 主题菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('选择主题')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d1c4e9')
            .borderRadius(8)
            .bindMenu(this.buildThemeMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('29. 语言菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('选择语言')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2ebf2')
            .borderRadius(8)
            .bindMenu(this.buildLanguageMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('30. 帮助菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('帮助与反馈')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b9f6ca')
            .borderRadius(8)
            .bindMenu(this.buildHelpMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('31. 多级嵌套菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('多级菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffccbc')
            .borderRadius(8)
            .bindMenu(this.buildMultiLevelMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('32. 通知设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('通知设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c5cae9')
            .borderRadius(8)
            .bindMenu(this.buildNotificationMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('33. 隐私设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('隐私设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d7ccc8')
            .borderRadius(8)
            .bindMenu(this.buildPrivacyMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('34. 网络设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('网络设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2dfdb')
            .borderRadius(8)
            .bindMenu(this.buildNetworkMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('35. 显示设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('显示设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c8e6c9')
            .borderRadius(8)
            .bindMenu(this.buildDisplayMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('36. 声音设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('声音设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff9c4')
            .borderRadius(8)
            .bindMenu(this.buildSoundMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('37. 电池设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('电池设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffecb3')
            .borderRadius(8)
            .bindMenu(this.buildBatteryMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('38. 存储设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('存储设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffe0b2')
            .borderRadius(8)
            .bindMenu(this.buildStorageMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('39. 账户设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('账户设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffcdd2')
            .borderRadius(8)
            .bindMenu(this.buildAccountMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('40. 安全设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('安全设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f8bbd9')
            .borderRadius(8)
            .bindMenu(this.buildSecurityMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('41. 辅助功能菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('辅助功能')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e6ee9c')
            .borderRadius(8)
            .bindMenu(this.buildAccessibilityMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('42. 开发者选项菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('开发者选项')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#80deea')
            .borderRadius(8)
            .bindMenu(this.buildDeveloperMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('43. 系统更新菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('系统更新')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#a5d6a7')
            .borderRadius(8)
            .bindMenu(this.buildUpdateMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('44. 备份与恢复菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('备份与恢复')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ce93d8')
            .borderRadius(8)
            .bindMenu(this.buildBackupMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('45. 应用管理菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('应用管理')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#90caf9')
            .borderRadius(8)
            .bindMenu(this.buildAppManagerMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('46. 权限管理菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('权限管理')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffcc80')
            .borderRadius(8)
            .bindMenu(this.buildPermissionMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('47. 设备信息菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('设备信息')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#80cbc4')
            .borderRadius(8)
            .bindMenu(this.buildDeviceMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('48. 日期时间菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('日期时间')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c5e1a5')
            .borderRadius(8)
            .bindMenu(this.buildDateTimeMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('49. 格式化菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('格式化选项')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ef9a9a')
            .borderRadius(8)
            .bindMenu(this.buildFormatMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('50. 关于手机菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('关于手机')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#9fa8da')
            .borderRadius(8)
            .bindMenu(this.buildAboutMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)
        .margin({ bottom: 30 })
      }
    }
  }

  @Builder
  buildFileOperationMenu() {
    Menu() {
      MenuItem({ content: '新建文件', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '打开文件', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '保存', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '另存为', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '导入', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '导出', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '打印', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '打印预览', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildEditMenu() {
    Menu() {
      MenuItem({ content: '撤销', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '重做', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '剪切', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '粘贴', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '全选', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '查找', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '替换', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildViewMenu() {
    Menu() {
      MenuItem({
        content: '缩放',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '放大' }),
          MenuItem({ content: '缩小' }),
          MenuItem({ content: '适应窗口' }),
          MenuItem({ content: '实际大小' })
        ]
      })
      MenuItem({
        content: '全屏',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '横屏' }),
          MenuItem({ content: '竖屏' }),
          MenuItem({ content: '自动旋转' })
        ]
      })
      MenuItem({})
      MenuItem({ content: '显示标尺', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '显示网格', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '显示边框', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '前一项', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '后一项', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildSortMenu() {
    Menu() {
      MenuItem({ content: '名称', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '修改日期', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '大小', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '类型', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '升序', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '降序', startIcon: $r('app.media.app_icon') })
    }
    .width(180)
  }

  @Builder
  buildFilterMenu() {
    Menu() {
      MenuItem({ content: '所有文件', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '图片', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '视频', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '音频', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '文档', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '压缩包', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '隐藏文件', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '系统文件', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(180)
  }

  @Builder
  buildUserMenu() {
    Menu() {
      MenuItem() {
        Row() {
          Image($r('app.media.app_icon'))
            .width(40)
            .height(40)
            .margin({ right: 10 })
          Column() {
            Text('用户名')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
            Text('user@example.com')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .alignItems(HorizontalAlign.Start)
        }
        .width('100%')
      }
      MenuItem({})
      MenuItem({ content: '个人资料', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '账户设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '我的订单', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '我的收藏', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '我的足迹', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '退出登录', startIcon: $r('app.media.app_icon') })
    }
    .width(240)
  }

  @Builder
  buildSettingsMenu() {
    Menu() {
      MenuItem({ content: '通用设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '显示设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '声音设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通知设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电池设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '存储设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '安全设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '辅助功能', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '关于手机', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildThemeMenu() {
    Menu() {
      MenuItem({ content: '浅色模式', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '深色模式', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '跟随系统', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({
        content: '主题颜色',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '默认蓝' }),
          MenuItem({ content: '活力橙' }),
          MenuItem({ content: '清新绿' }),
          MenuItem({ content: '浪漫粉' }),
          MenuItem({ content: '神秘紫' })
        ]
      })
    }
    .width(180)
  }

  @Builder
  buildLanguageMenu() {
    Menu() {
      MenuItem({ content: '简体中文', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '繁体中文', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'English', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '日本語', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '한국어', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'Français', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'Deutsch', startIcon: $r('app.media.app_icon') })
    }
    .width(180)
  }

  @Builder
  buildHelpMenu() {
    Menu() {
      MenuItem({ content: '使用帮助', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '常见问题', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '用户指南', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '视频教程', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '反馈问题', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '联系客服', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '检查更新', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildMultiLevelMenu() {
    Menu() {
      MenuItem({
        content: '第一级1',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({
            content: '第二级1-1',
            children: [
              MenuItem({ content: '第三级1-1-1' }),
              MenuItem({ content: '第三级1-1-2' }),
              MenuItem({ content: '第三级1-1-3' })
            ]
          }),
          MenuItem({
            content: '第二级1-2',
            children: [
              MenuItem({ content: '第三级1-2-1' }),
              MenuItem({ content: '第三级1-2-2' })
            ]
          })
        ]
      })
      MenuItem({
        content: '第一级2',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '第二级2-1' }),
          MenuItem({ content: '第二级2-2' }),
          MenuItem({ content: '第二级2-3' })
        ]
      })
      MenuItem({
        content: '第一级3',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({
            content: '第二级3-1',
            children: [
              MenuItem({ content: '第三级3-1-1' }),
              MenuItem({ content: '第三级3-1-2' })
            ]
          }),
          MenuItem({ content: '第二级3-2' })
        ]
      })
    }
    .width(220)
  }

  @Builder
  buildNotificationMenu() {
    Menu() {
      MenuItem({ content: '允许通知', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '锁屏通知', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '横幅通知', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '铃声通知', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({
        content: '通知类型',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '即时消息' }),
          MenuItem({ content: '邮件' }),
          MenuItem({ content: '日历' }),
          MenuItem({ content: '其他' })
        ]
      })
      MenuItem({ content: '通知管理', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildPrivacyMenu() {
    Menu() {
      MenuItem({ content: '位置信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '相机权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '麦克风权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '存储权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通讯录权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电话权限', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '隐私政策', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '用户协议', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildNetworkMenu() {
    Menu() {
      MenuItem({ content: 'WLAN', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '移动网络', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '蓝牙', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'NFC', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '热点与共享', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: 'VPN', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '代理设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'DNS设置', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildDisplayMenu() {
    Menu() {
      MenuItem({ content: '亮度', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '护眼模式', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '色温调节', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '屏幕分辨率', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '屏幕刷新率', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '字体大小', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '显示比例', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '壁纸设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '主题设置', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildSoundMenu() {
    Menu() {
      MenuItem({ content: '媒体音量', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通知音量', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '闹钟音量', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通话音量', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '铃声设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通知铃声', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '闹钟铃声', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '振动反馈', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '触摸音效', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildBatteryMenu() {
    Menu() {
      MenuItem({ content: '省电模式', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '超级省电', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电池优化', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '耗电排行', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电池使用详情', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '后台耗电管理', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '充电设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电池健康', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildStorageMenu() {
    Menu() {
      MenuItem() {
        Row() {
          Text('存储空间')
            .fontSize(14)
          Text('已使用 75%')
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
      }
      MenuItem({})
      MenuItem({ content: '内部存储', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '外部存储', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '云存储', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '清理存储空间', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '应用管理', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '大文件管理', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildAccountMenu() {
    Menu() {
      MenuItem({ content: '添加账户', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '华为账号', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'Google账号', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '企业账号', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '同步设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '自动同步数据', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '同步频率', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '移除账户', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(200)
  }

  @Builder
  buildSecurityMenu() {
    Menu() {
      MenuItem({ content: '指纹解锁', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '面部识别', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '密码解锁', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '图案解锁', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '应用锁', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '文件保险箱', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '安全验证', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '查找设备', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '隐私空间', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildAccessibilityMenu() {
    Menu() {
      MenuItem({ content: 'TalkBack', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '放大字体', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '高对比度文字', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '色彩校正', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '移除动画', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '快捷方式', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '语音控制', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '手势导航', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildDeveloperMenu() {
    Menu() {
      MenuItem({ content: 'USB调试', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '无线调试', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '开发者选项', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: 'GPU渲染', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '硬件加速', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '内存监控', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '日志级别', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '性能监视器', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildUpdateMenu() {
    Menu() {
      MenuItem({ content: '检查更新', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '自动下载', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '夜间更新', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '版本信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '更新日志', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '内测版本', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '恢复出厂设置', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(200)
  }

  @Builder
  buildBackupMenu() {
    Menu() {
      MenuItem({ content: '本地备份', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '云端备份', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'SD卡备份', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '本地恢复', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '云端恢复', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'SD卡恢复', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '备份应用数据', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '备份短信', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '备份联系人', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildAppManagerMenu() {
    Menu() {
      MenuItem({ content: '已安装应用', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '系统应用', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '用户应用', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '应用权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '应用通知', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '应用内存', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '默认应用', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '应用兼容性', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildPermissionMenu() {
    Menu() {
      MenuItem({ content: '位置权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '相机权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '麦克风权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '存储权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '电话权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '短信权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '通讯录权限', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '日历权限', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '特殊权限', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildDeviceMenu() {
    Menu() {
      MenuItem({ content: '设备名称', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '设备型号', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '硬件序列号', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'MAC地址', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'IP地址', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '处理器信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '内存信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '存储信息', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '设备状态', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'IMEI信息', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(200)
  }

  @Builder
  buildDateTimeMenu() {
    Menu() {
      MenuItem({ content: '自动设置时间', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '自动设置时区', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '设置时间', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '设置日期', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '设置时区', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '24小时制', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '选择时区', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '闹钟设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '倒计时', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildFormatMenu() {
    Menu() {
      MenuItem({ content: '格式化内部存储', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '格式化外部存储', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '格式化SD卡', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({})
      MenuItem({ content: '快速格式化', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({ content: '完全格式化', startIcon: $r('app.media.app_icon'), enabled: false })
      MenuItem({})
      MenuItem({ content: '格式化前注意', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(220)
  }

  @Builder
  buildAboutMenu() {
    Menu() {
      MenuItem({ content: '设备名称', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '设备型号', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: 'HarmonyOS版本', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '内核版本', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '安全补丁', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '状态信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '法律信息', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '认证信息', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '电子保卡', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildProfileMenu() {
    Menu() {
      MenuItemGroup({ header: '个人资料' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(50)
              .height(50)
              .borderRadius(25)
              .margin({ right: 15 })
            Column() {
              Text('用户昵称')
                .fontSize(18)
                .fontWeight(FontWeight.Bold)
              Text('个人简介：这是一个测试用户')
                .fontSize(12)
                .fontColor(Color.Gray)
                .maxLines(2)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '账号信息' }) {
        MenuItem({ content: '修改头像', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '修改昵称', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '修改签名', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '修改性别', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '修改生日', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '联系方式' }) {
        MenuItem({ content: '手机号', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '邮箱', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '社交账号', startIcon: $r('app.media.app_icon') })
      }
    }
    .width(280)
  }

  @Builder
  buildShoppingCartMenu() {
    Menu() {
      MenuItemGroup({ header: '购物车 (3)' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(40)
              .height(40)
              .margin({ right: 10 })
            Column() {
              Text('商品名称1')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('¥99.00 x 1')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(40)
              .height(40)
              .margin({ right: 10 })
            Column() {
              Text('商品名称2')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('¥199.00 x 2')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(40)
              .height(40)
              .margin({ right: 10 })
            Column() {
              Text('商品名称3')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('¥299.00 x 1')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItem() {
        Row() {
          Text('合计: ')
            .fontSize(14)
          Text('¥795.00')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Red)
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
      }
      MenuItem({})
      MenuItem({ content: '结算', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '清空购物车', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(300)
  }

  @Builder
  buildMusicPlayerMenu() {
    Menu() {
      MenuItemGroup({ header: '正在播放' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(50)
              .height(50)
              .borderRadius(8)
              .margin({ right: 15 })
            Column() {
              Text('歌曲名称')
                .fontSize(16)
                .fontWeight(FontWeight.Medium)
              Text('艺术家 - 专辑')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '播放控制' }) {
        MenuItem({ content: '上一首', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '播放/暂停', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '下一首', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '播放列表' }) {
        MenuItem({ content: '循环播放', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '随机播放', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '添加到歌单', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '查看歌词', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '查看专辑', startIcon: $r('app.media.app_icon') })
    }
    .width(280)
  }

  @Builder
  buildFileFolderMenu() {
    Menu() {
      MenuItem({ content: '打开', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '重命名', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '移动', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({
        content: '发送到',
        startIcon: $r('app.media.app_icon'),
        children: [
          MenuItem({ content: '好友' }),
          MenuItem({ content: '云端' }),
          MenuItem({ content: '邮箱' }),
          MenuItem({ content: '蓝牙' })
        ]
      })
      MenuItem({ content: '压缩', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '解压', startIcon: $r('app.media.app_icon') })
      MenuItem({})
      MenuItem({ content: '属性', startIcon: $r('app.media.app_icon') })
    }
    .width(200)
  }

  @Builder
  buildImageViewerMenu() {
    Menu() {
      MenuItemGroup({ header: '图片操作' }) {
        MenuItem({ content: '收藏', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '分享', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '保存到相册', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '设为壁纸', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '编辑' }) {
        MenuItem({ content: '裁剪', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '旋转', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '滤镜', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '调整大小', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '信息' }) {
        MenuItem({ content: '详细信息', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '位置信息', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '删除', startIcon: $r('app.media.app_icon'), enabled: false })
    }
    .width(220)
  }

  @Builder
  buildVideoPlayerMenu() {
    Menu() {
      MenuItemGroup({ header: '播放控制' }) {
        MenuItem({ content: '播放/暂停', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '上一集', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '下一集', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '快进/快退', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '画面' }) {
        MenuItem({ content: '全屏', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '画面比例', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '亮度', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '对比度', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '音频' }) {
        MenuItem({ content: '音量', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '声道', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '字幕', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '分享', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '投屏', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildTextEditorMenu() {
    Menu() {
      MenuItemGroup({ header: '文字编辑' }) {
        MenuItem({ content: '撤销', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '重做', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '剪切', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '粘贴', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '全选', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '文字格式' }) {
        MenuItem({ content: '加粗', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '斜体', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '下划线', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除线', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '段落格式' }) {
        MenuItem({ content: '左对齐', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '居中对齐', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '右对齐', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '两端对齐', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '插入图片', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '插入表格', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildEmailMenu() {
    Menu() {
      MenuItemGroup({ header: '发件人' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(30)
              .height(30)
              .borderRadius(15)
              .margin({ right: 10 })
            Column() {
              Text('发件人名称')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('sender@example.com')
                .fontSize(10)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '回复', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '回复全部', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '转发', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '更多' }) {
        MenuItem({ content: '标记为已读', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '标记为重要', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '移动到文件夹', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '创建过滤器', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '查看附件', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '打印', startIcon: $r('app.media.app_icon') })
    }
    .width(280)
  }

  @Builder
  buildCalendarMenu() {
    Menu() {
      MenuItemGroup({ header: '今天' }) {
        MenuItem() {
          Row() {
            Text('2024年1月15日')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)
            Text('星期一')
              .fontSize(12)
              .fontColor(Color.Gray)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '新建事件', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '新建日程', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '新建提醒', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '视图' }) {
        MenuItem({ content: '日视图', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '周视图', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '月视图', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '年视图', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '导出日历', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '导入日历', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildContactMenu() {
    Menu() {
      MenuItemGroup({ header: '联系人信息' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(50)
              .height(50)
              .borderRadius(25)
              .margin({ right: 15 })
            Column() {
              Text('联系人姓名')
                .fontSize(18)
                .fontWeight(FontWeight.Bold)
              Text('138****8888')
                .fontSize(14)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '拨打电话', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '发送短信', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '发送邮件', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '视频通话', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '编辑' }) {
        MenuItem({ content: '编辑联系人', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除联系人', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '标记收藏', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '加入黑名单', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '分享联系人', startIcon: $r('app.media.app_icon') })
    }
    .width(260)
  }

  @Builder
  buildNoteMenu() {
    Menu() {
      MenuItemGroup({ header: '笔记内容' }) {
        MenuItem() {
          Column() {
            Text('笔记标题')
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
            Text('笔记内容预览部分...')
              .fontSize(12)
              .fontColor(Color.Gray)
              .maxLines(2)
            Text('2024-01-15 10:30')
              .fontSize(10)
              .fontColor(Color.Gray)
              .margin({ top: 5 })
          }
          .width('100%')
          .alignItems(HorizontalAlign.Start)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '编辑', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '移动', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '更多' }) {
        MenuItem({ content: '置顶', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '标记星标', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '锁定', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '分享', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '创建备份', startIcon: $r('app.media.app_icon') })
    }
    .width(260)
  }

  @Builder
  buildWeatherMenu() {
    Menu() {
      MenuItemGroup({ header: '当前天气' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(40)
              .height(40)
              .margin({ right: 15 })
            Column() {
              Text('25°C')
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
              Text('晴转多云')
                .fontSize(14)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '详细信息' }) {
        MenuItem({ content: '湿度: 65%', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '风速: 3级', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '空气质量: 良', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '能见度: 10km', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '预报' }) {
        MenuItem({ content: '逐小时预报', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '7天预报', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '15天预报', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '天气设置', startIcon: $r('app.media.app_icon') })
    }
    .width(240)
  }

  @Builder
  buildBrowserMenu() {
    Menu() {
      MenuItemGroup({ header: '当前页面' }) {
        MenuItem({ content: '刷新', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '停止加载', startIcon: $r('app.media.app_icon'), enabled: false })
        MenuItem({ content: '主页', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '导航' }) {
        MenuItem({ content: '后退', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '前进', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '历史记录', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '书签', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '工具' }) {
        MenuItem({ content: '保存页面', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '分享', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '查找', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '开发者工具', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '设置', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '新建标签页', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildChatMenu() {
    Menu() {
      MenuItemGroup({ header: '消息内容' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(40)
              .height(40)
              .borderRadius(20)
              .margin({ right: 10 })
            Column() {
              Text('对方昵称')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('消息内容预览...')
                .fontSize(12)
                .fontColor(Color.Gray)
                .maxLines(1)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '回复', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '复制', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '转发', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '更多' }) {
        MenuItem({ content: '引用', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '收藏', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '提醒', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '设为未读', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '查看详情', startIcon: $r('app.media.app_icon') })
    }
    .width(260)
  }

  @Builder
  buildMapMenu() {
    Menu() {
      MenuItemGroup({ header: '当前位置' }) {
        MenuItem() {
          Column() {
            Text('北京市朝阳区')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
            Text('详细地址信息')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .width('100%')
          .alignItems(HorizontalAlign.Start)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '导航' }) {
        MenuItem({ content: '到这里', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '从这里出发', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '公交线路', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '步行线路', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '更多' }) {
        MenuItem({ content: '分享位置', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '收藏地点', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '添加标签', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '纠错', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '查看周围', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildClockMenu() {
    Menu() {
      MenuItemGroup({ header: '当前时间' }) {
        MenuItem() {
          Text('10:30:25')
            .fontSize(32)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .textAlign(TextAlign.Center)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '闹钟' }) {
        MenuItem({ content: '添加闹钟', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '编辑闹钟', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '删除闹钟', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '计时器' }) {
        MenuItem({ content: '开始计时', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '暂停计时', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '重置计时', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '秒表' }) {
        MenuItem({ content: '开始秒表', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '计次', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '停止秒表', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '世界时钟', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildCalculatorMenu() {
    Menu() {
      MenuItemGroup({ header: '计算结果' }) {
        MenuItem() {
          Text('123456789')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .textAlign(TextAlign.End)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '复制结果', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '粘贴', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '清除', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '高级计算' }) {
        MenuItem({ content: '科学计算器', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '程序员计算器', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '单位转换', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '货币转换', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '历史记录', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }

  @Builder
  buildSettingsSliderMenu() {
    Menu() {
      MenuItemGroup({ header: '亮度调节' }) {
        MenuItem() {
          Row() {
            Text('亮度')
              .fontSize(14)
            Slider({
              min: 0,
              max: 100,
              value: 50,
              step: 1
            })
              .width(150)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '音量调节' }) {
        MenuItem() {
          Row() {
            Text('媒体音量')
              .fontSize(14)
            Slider({
              min: 0,
              max: 100,
              value: 70,
              step: 1
            })
              .width(150)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }
        MenuItem() {
          Row() {
            Text('通知音量')
              .fontSize(14)
            Slider({
              min: 0,
              max: 100,
              value: 80,
              step: 1
            })
              .width(150)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '其他设置' }) {
        MenuItem({ content: '自动调节亮度', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '自动调节音量', startIcon: $r('app.media.app_icon') })
      }
    }
    .width(280)
  }

  @Builder
  buildLocationMenu() {
    Menu() {
      MenuItemGroup({ header: '位置信息' }) {
        MenuItem() {
          Column() {
            Text('当前定位')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
            Text('北京市朝阳区xxx街道')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .width('100%')
          .alignItems(HorizontalAlign.Start)
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '定位模式' }) {
        MenuItem({ content: '高精度模式', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '低功耗模式', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '仅设备定位', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '应用权限' }) {
        MenuItem({ content: '地图应用', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '天气应用', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '社交应用', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '运动应用', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '位置历史记录', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '位置服务设置', startIcon: $r('app.media.app_icon') })
    }
    .width(240)
  }

  @Builder
  buildBluetoothMenu() {
    Menu() {
      MenuItemGroup({ header: '蓝牙状态' }) {
        MenuItem({ content: '已开启', startIcon: $r('app.media.app_icon'), enabled: false })
      }
      MenuItem({})
      MenuItemGroup({ header: '已配对设备' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(30)
              .height(30)
              .margin({ right: 10 })
            Column() {
              Text('设备名称')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('已连接')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(30)
              .height(30)
              .margin({ right: 10 })
            Column() {
              Text('耳机名称')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('未连接')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '搜索设备', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '关闭蓝牙', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '文件传输', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '蓝牙设置', startIcon: $r('app.media.app_icon') })
    }
    .width(240)
  }

  @Builder
  buildWIFIMenu() {
    Menu() {
      MenuItemGroup({ header: '当前网络' }) {
        MenuItem() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(30)
              .height(30)
              .margin({ right: 10 })
            Column() {
              Text('WIFI名称')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('已连接')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
        }
      }
      MenuItem({})
      MenuItemGroup({ header: '可用网络' }) {
        MenuItem({ content: '网络1', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '网络2', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '网络3', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: '更多网络...', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItemGroup({ header: '操作' }) {
        MenuItem({ content: '刷新', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: 'WIFI设置', startIcon: $r('app.media.app_icon') })
        MenuItem({ content: 'WIFI热点', startIcon: $r('app.media.app_icon') })
      }
      MenuItem({})
      MenuItem({ content: '已保存网络', startIcon: $r('app.media.app_icon') })
    }
    .width(220)
  }
}
