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

interface MenuItemData {
  id: number,
  title: string,
  icon: Resource,
  enabled: boolean,
  selected: boolean
}

@Entry
@Component
struct MenuAdvancedDemo {
  scroller: Scroller = new Scroller()
  @State selectedOption: string = '';
  @State menuVisible1: boolean = false;
  @State menuVisible2: boolean = false;
  @State menuVisible3: boolean = false;
  @State menuVisible4: boolean = false;
  @State menuVisible5: boolean = false;
  @State menuVisible6: boolean = false;
  @State menuVisible7: boolean = false;
  @State menuVisible8: boolean = false;
  @State menuVisible9: boolean = false;
  @State menuVisible10: boolean = false;
  @State sortIndex: number = 0;
  @State menuRadius: number = 16;
  @State menuWidth: number = 240;
  @State themeColor: string = '#2ebd82';

  private menuItems: Array<MenuElement> = [
    { value: '新建', action: () => { this.selectedOption = '新建'; } },
    { value: '打开', action: () => { this.selectedOption = '打开'; } },
    { value: '保存', action: () => { this.selectedOption = '保存'; } },
    { value: '另存为', action: () => { this.selectedOption = '另存为'; } }
  ];

  private editMenuItems: Array<MenuElement> = [
    { value: '撤销', icon: $r('sys.media.ohos_user_auth_icon_face'), action: () => { this.selectedOption = '撤销'; } },
    { value: '重做', icon: $r('sys.media.ohos_user_auth_icon_face'), action: () => { this.selectedOption = '重做'; } },
    { value: '剪切', icon: $r('sys.media.ohos_user_auth_icon_face'), action: () => { this.selectedOption = '剪切'; } },
    { value: '复制', icon: $r('sys.media.ohos_user_auth_icon_face'), action: () => { this.selectedOption = '复制'; } },
    { value: '粘贴', icon: $r('sys.media.ohos_user_auth_icon_face'), action: () => { this.selectedOption = '粘贴'; } }
  ];

  @Builder
  BasicMenuBuilder() {
    Menu() {
      MenuItem({ content: '选项A' })
      MenuItem({ content: '选项B' })
      MenuItem({ content: '选项C' })
      MenuItem({ content: '选项D' })
    }
    .width(160)
  }

  @Builder
  IconMenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '首页' })
      MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '发现' })
      MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '消息' })
      MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '我的' })
    }
    .width(180)
  }

  @Builder
  GroupedMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '常用功能' }) {
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '新建项目' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '打开项目' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '保存项目' })
      }
      MenuItemGroup({ header: '高级功能' }) {
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '导出' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '导入' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '发布' })
      }
      MenuItemGroup({ header: '系统' }) {
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '设置' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '帮助' })
        MenuItem({ startIcon: $r('sys.media.ohos_user_auth_icon_face'), content: '退出' })
      }
    }
    .width(240)
  }

  @Builder
  NestedMenuBuilder() {
    Menu() {
      MenuItem({ content: '文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '编辑', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({
        content: '视图',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.ViewSubMenu()
      })
      MenuItem({
        content: '工具',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.ToolsSubMenu()
      })
      MenuItem({ content: '帮助', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  ViewSubMenu() {
    MenuItem({ content: '放大', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    MenuItem({ content: '缩小', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    MenuItem({
      content: '全屏',
      startIcon: $r('sys.media.ohos_user_auth_icon_face'),
      builder: ():void=>this.FullScreenSubMenu()
    })
  }

  @Builder
  FullScreenSubMenu() {
    MenuItem({ content: '横屏模式' })
    MenuItem({ content: '竖屏模式' })
    MenuItem({ content: '自动旋转' })
  }

  @Builder
  ToolsSubMenu() {
    MenuItem({ content: '开发者工具' })
    MenuItem({ content: '性能分析' })
    MenuItem({ content: '调试模式' })
  }

  @Builder
  SelectedMenuBuilder() {
    Menu() {
      MenuItem({ content: '按名称排序' })
        .selected(this.sortIndex === 0)
        .onClick(() => { this.sortIndex = 0; this.selectedOption = '按名称排序'; })
      MenuItem({ content: '按日期排序' })
        .selected(this.sortIndex === 1)
        .onClick(() => { this.sortIndex = 1; this.selectedOption = '按日期排序'; })
      MenuItem({ content: '按大小排序' })
        .selected(this.sortIndex === 2)
        .onClick(() => { this.sortIndex = 2; this.selectedOption = '按大小排序'; })
      MenuItem({ content: '按类型排序' })
        .selected(this.sortIndex === 3)
        .onClick(() => { this.sortIndex = 3; this.selectedOption = '按类型排序'; })
    }
    .width(200)
  }

  @Builder
  DisabledMenuBuilder() {
    Menu() {
      MenuItem({ content: '可用选项1', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '禁用选项2', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        .enabled(false)
      MenuItem({ content: '可用选项3', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '禁用选项4', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        .enabled(false)
      MenuItem({ content: '可用选项5', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  ContextMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '粘贴', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '剪切', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '属性', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '删除', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(180)
  }

  @Builder
  ShortcutMenuBuilder() {
    Menu() {
      MenuItem({ content: '新建文件', labelInfo: 'Ctrl+N', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '打开文件', labelInfo: 'Ctrl+O', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '保存文件', labelInfo: 'Ctrl+S', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '另存为', labelInfo: 'Ctrl+Shift+S', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '退出程序', labelInfo: 'Alt+F4', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(220)
  }

  @Builder
  SystemMenuBuilder() {
    Menu() {
      MenuItem({ content: '系统设置1' })
      MenuItem({ content: '系统设置2' })
      MenuItem({ content: '系统设置3' })
    }
    .width(180)
  }

  @Builder
  CustomMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '用户信息' }) {
        MenuItem() {
          Row() {
            Image($r('sys.media.ohos_user_auth_icon_face'))
              .width(32)
              .height(32)
              .margin({ right: 12 })
            Column() {
              Text('用户名称')
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

        MenuItem({ content: '个人中心', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '我的订单', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '收藏夹', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '历史记录', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '购物车', startIcon: $r('sys.media.ohos_user_auth_icon_face') })

        MenuItem() {
          Row() {
            Text('会员等级')
              .fontSize(14)
            Text('VIP会员')
              .fontSize(12)
              .fontColor('#FFD700')
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
        }

        MenuItem({ content: '升级会员', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      }
    }
    .width(240)
  }

  @Builder
  FullConfigMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '完整配置' }) {
        MenuItem({ content: '带图标选项', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '带快捷键', labelInfo: 'Ctrl+Click' })
        MenuItem({ content: '已选中选项' })
          .selected(true)
        MenuItem({ content: '已禁用选项'})
          .enabled(false)
        MenuItem({})
        MenuItem({ content: '普通选项' })
      }
    }
    .width(220)
    .radius(this.menuRadius)
  }

  @Builder
  buildFileManagerMenu() {
    Menu() {
      MenuItem({ content: '新建文件夹', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '新建文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '打开', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '保存', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '重命名', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '复制', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '移动', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '删除', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '属性', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(220)
  }

  @Builder
  buildEditorMenu() {
    Menu() {
      MenuItem({ content: '撤销', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '重做', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '剪切', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '复制', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '粘贴', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '删除', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '全选', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '查找', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '替换', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildViewControlMenu() {
    Menu() {
      MenuItem({
        content: '缩放',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.ViewSubMenu()
      })
      MenuItem({
        content: '全屏',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.FullScreenSubMenu()
      })
      MenuItem({})
      MenuItem({ content: '显示标尺', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示网格', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示边框', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '上一页', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '下一页', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildSortOptionsMenu() {
    Menu() {
      MenuItem({ content: '按名称', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '按日期', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '按大小', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '按类型', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '升序排列', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '降序排列', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(180)
  }

  @Builder
  buildFilterOptionsMenu() {
    Menu() {
      MenuItem({ content: '全部显示', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '图片文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '视频文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '音频文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '文档文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '压缩文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '隐藏文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        .enabled(false)
      MenuItem({ content: '系统文件', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        .enabled(false)
    }
    .width(180)
  }

  @Builder
  buildUserAccountMenu() {
    Menu() {
      MenuItem() {
        Row() {
          Image($r('sys.media.ohos_user_auth_icon_face'))
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
      MenuItem({ content: '个人资料', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '账户设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '订单管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '收藏内容', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '浏览历史', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '退出登录', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(240)
  }

  @Builder
  buildAppSettingsMenu() {
    Menu() {
      MenuItem({ content: '通用设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '声音设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '通知设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '电池设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '存储设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '安全设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '无障碍功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '关于系统', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  ColorSubMenu() {
    MenuItem({ content: '默认蓝色' })
    MenuItem({ content: '活力橙色' })
    MenuItem({ content: '清新绿色' })
    MenuItem({ content: '浪漫粉色' })
    MenuItem({ content: '神秘紫色' })
  }

  @Builder
  buildThemeSelectionMenu() {
    Menu() {
      MenuItem({ content: '浅色模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '深色模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '跟随系统', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({
        content: '主题颜色',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.ColorSubMenu()
      })
    }
    .width(180)
  }

  @Builder
  buildLanguageSwitchMenu() {
    Menu() {
      MenuItem({ content: '简体中文', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '繁体中文', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'English', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '日本語', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '한국어', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'Français', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'Deutsch', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(180)
  }

  @Builder
  buildHelpCenterMenu() {
    Menu() {
      MenuItem({ content: '使用指南', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '常见问题', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '用户手册', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '视频教程', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '问题反馈', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '联系客服', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '检查更新', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  Level2SubMenu1() {
    MenuItem({
      content: '二级菜单1-1',
      builder: ():void=>this.Level3SubMenu1()
    })
    MenuItem({
      content: '二级菜单1-2',
      builder: ():void=>this.Level3SubMenu2()
    })
  }

  @Builder
  Level3SubMenu1() {
    MenuItem({ content: '三级菜单1-1-1' })
    MenuItem({ content: '三级菜单1-1-2' })
    MenuItem({ content: '三级菜单1-1-3' })
  }

  @Builder
  Level3SubMenu2() {
    MenuItem({ content: '三级菜单1-2-1' })
    MenuItem({ content: '三级菜单1-2-2' })
  }

  @Builder
  Level2SubMenu2() {
    MenuItem({ content: '二级菜单2-1' })
    MenuItem({ content: '二级菜单2-2' })
    MenuItem({ content: '二级菜单2-3' })
  }

  @Builder
  Level2SubMenu3() {
    MenuItem({
      content: '二级菜单3-1',
      builder: ():void=>this.Level3SubMenu3()
    })
    MenuItem({ content: '二级菜单3-2' })
  }

  @Builder
  Level3SubMenu3() {
    MenuItem({ content: '三级菜单3-1-1' })
    MenuItem({ content: '三级菜单3-1-2' })
  }

  @Builder
  buildMultiLevelNestedMenu() {
    Menu() {
      MenuItem({
        content: '一级菜单1',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.Level2SubMenu1()
      })
      MenuItem({
        content: '一级菜单2',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.Level2SubMenu2()
      })
      MenuItem({
        content: '一级菜单3',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.Level2SubMenu3()
      })
    }
    .width(220)
  }

  @Builder
  NotificationTypeSubMenu() {
    MenuItem({ content: '即时通知' })
    MenuItem({ content: '邮件通知' })
    MenuItem({ content: '日程通知' })
    MenuItem({ content: '其他通知' })
  }

  @Builder
  buildNotificationConfigMenu() {
    Menu() {
      MenuItem({ content: '允许通知', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        .enabled(false)
      MenuItem({ content: '锁屏通知', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '横幅通知', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '声音通知', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({
        content: '通知类型',
        startIcon: $r('sys.media.ohos_user_auth_icon_face'),
        builder: ():void=>this.NotificationTypeSubMenu()
      })
      MenuItem({ content: '通知管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildPrivacyProtectionMenu() {
    Menu() {
      MenuItem({ content: '位置信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '相机权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '麦克风权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '存储权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '通讯录权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '电话权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '隐私政策', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '用户协议', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildNetworkConnectionMenu() {
    Menu() {
      MenuItem({ content: '无线网络', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '移动数据', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '蓝牙设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'NFC设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '热点共享', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: 'VPN设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '代理设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'DNS设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildDisplaySettingsMenu() {
    Menu() {
      MenuItem({ content: '屏幕亮度', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '护眼模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '色温调节', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '分辨率', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '刷新率', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '字体大小', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示比例', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '壁纸设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '主题设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildAudioSettingsMenu() {
    Menu() {
      MenuItem({ content: '媒体音量', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '通知音量', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '闹钟音量', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '系统音量', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '静音模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '震动模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '勿扰模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '铃声设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '提示音设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildPowerManagementMenu() {
    Menu() {
      MenuItem({ content: '电量显示', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '省电模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '超级省电', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '性能模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '电池使用', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '耗电排行', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '电池健康', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '充电设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '电池保护', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildStorageManagementMenu() {
    Menu() {
      MenuItem({ content: '存储空间', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '内部存储', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '外部存储', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '云存储', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '清理缓存', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '清理垃圾', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '存储分析', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '文件管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '备份恢复', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildAccountSecurityMenu() {
    Menu() {
      MenuItem({ content: '修改密码', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '设置密保', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '绑定手机', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '绑定邮箱', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '实名认证', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '人脸识别', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '指纹解锁', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '登录设备', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '安全中心', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildSystemSecurityMenu() {
    Menu() {
      MenuItem({ content: '屏幕锁定', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '应用锁', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '文件加密', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '安全扫描', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '病毒查杀', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '骚扰拦截', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '流量监控', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '权限管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '安全日志', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildAccessibilityMenu() {
    Menu() {
      MenuItem({ content: '屏幕阅读器', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '文字转语音', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '语音转文字', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示放大', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '高对比度', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '颜色反转', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '色盲模式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '动作辅助', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '交互控制', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildDeveloperToolsMenu() {
    Menu() {
      MenuItem({ content: '开发者选项', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'USB调试', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'ADB调试', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '网络调试', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '性能分析', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '内存分析', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'CPU分析', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '日志查看', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '布局检查', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildSystemUpdateMenu() {
    Menu() {
      MenuItem({ content: '检查更新', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '系统升级', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '版本信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '更新历史', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '自动更新', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '下载设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '安装设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '恢复出厂', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '系统回滚', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildDataBackupMenu() {
    Menu() {
      MenuItem({ content: '立即备份', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '自动备份', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '备份设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '备份历史', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '数据恢复', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '云备份', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '本地备份', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '同步设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '迁移数据', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildApplicationMenu() {
    Menu() {
      MenuItem({ content: '应用列表', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '正在运行', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '应用安装', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '应用卸载', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '默认应用', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '应用权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '应用存储', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '应用商店', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '特殊权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildPermissionControlMenu() {
    Menu() {
      MenuItem({ content: '权限列表', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '使用记录', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '权限授予', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '权限撤销', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '敏感权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '隐私权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '系统权限', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '权限组', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '权限策略', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildDeviceInfoMenu() {
    Menu() {
      MenuItem({ content: '设备名称', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '设备型号', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '序列号', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: 'IMEI码', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '处理器信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '内存信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '存储信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '屏幕信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '网络信息', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildTimeSettingsMenu() {
    Menu() {
      MenuItem({ content: '自动设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '手动设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '日期设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '时间设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '时区设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '夏令时', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '网络时间', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '日期格式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '时间格式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildFormatOptionsMenu() {
    Menu() {
      MenuItem({ content: '格式化磁盘', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '快速格式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '完全格式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '低级格式', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '文件系统', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '分区表', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '簇大小', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '格式化选项', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '高级选项', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildSystemInfoMenu() {
    Menu() {
      MenuItem({ content: '系统版本', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '内核版本', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '补丁级别', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '构建号', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '运行时间', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '启动时间', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '更新时间', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '系统状态', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '系统日志', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildAdvancedSettingsMenu() {
    Menu() {
      MenuItem({ content: '系统优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '性能调优', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '内存优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '存储优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '网络优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '电池优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '显示优化', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({})
      MenuItem({ content: '实验功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      MenuItem({ content: '隐藏选项', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
    }
    .width(200)
  }

  @Builder
  buildComprehensiveMenu() {
    Menu() {
      MenuItemGroup({ header: '综合功能' }) {
        MenuItem({ content: '基础功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '高级功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '扩展功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '插件功能', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      }
      MenuItemGroup({ header: '系统功能' }) {
        MenuItem({ content: '系统设置', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '系统工具', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '系统监控', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '系统维护', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      }
      MenuItemGroup({ header: '用户功能' }) {
        MenuItem({ content: '用户管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '权限管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '数据管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
        MenuItem({ content: '安全管理', startIcon: $r('sys.media.ohos_user_auth_icon_face') })
      }
    }
    .width(240)
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Menu高级示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0xFFFFFF)
          .textAlign(TextAlign.Center)
          .width('100%')
          .height(50)
          .backgroundColor(this.themeColor)

        Column({ space: 15 }) {
          Text('1. 基础菜单示例')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示基础菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.menuItems, {
              title: '基础菜单',
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
            .bindMenu(this.BasicMenuBuilder, {
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
            .bindMenu(this.editMenuItems, {
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
          Text('4. 菜单位置控制')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('顶部')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '顶部菜单',
                placement: Placement.Top
              })

            Text('底部')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '底部菜单',
                placement: Placement.Bottom
              })

            Text('左侧')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '左侧菜单',
                placement: Placement.Left
              })

            Text('右侧')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#e0e0f0')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '右侧菜单',
                placement: Placement.Right
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
            Text('无圆角')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '圆角菜单',
                borderRadius: 0,
                placement: Placement.Bottom
              })

            Text('小圆角')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
                title: '圆角菜单',
                borderRadius: 12,
                placement: Placement.Bottom
              })

            Text('大圆角')
              .fontSize(14)
              .padding(10)
              .backgroundColor('#fce4ec')
              .borderRadius(5)
              .bindMenu(this.menuItems, {
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
          Text('6. 菜单偏移控制')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带偏移的菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#bbdefb')
            .borderRadius(8)
            .bindMenu(this.menuItems, {
              title: '偏移菜单',
              offset: { x: 25, y: 15 },
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('7. 菜单阴影效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('带阴影的菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d1c4e9')
            .borderRadius(8)
            .bindMenu(this.menuItems, {
              title: '阴影菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('8. 菜单动画效果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击切换显示菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2ebf2')
            .borderRadius(8)
            .bindMenu(this.menuVisible1, this.menuItems, {
              title: '动画菜单',
              placement: Placement.Bottom
            })
            .onClick(() => {
              this.menuVisible1 = !this.menuVisible1;
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('9. 菜单分组显示')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示分组菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff8e1')
            .borderRadius(8)
            .bindMenu(this.GroupedMenuBuilder, {
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
          Text('10. 嵌套子菜单')
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
          Text('11. 菜单选中状态')
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
          Text('12. 菜单禁用状态')
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
          Text('13. 上下文菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('长按显示上下文菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b9f6ca')
            .borderRadius(8)
            .bindContextMenu(this.ContextMenuBuilder, ResponseType.LongPress, {
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('14. 键盘快捷键菜单')
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
          Text('15. 系统材质菜单')
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
          Text('16. 自定义内容菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示自定义菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d4e0e8')
            .borderRadius(8)
            .bindMenu(this.CustomMenuBuilder, {
              title: '自定义菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('17. 完整配置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('调整圆角')
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
              max: 35,
              value: this.menuRadius,
              step: 3
            })
              .onChange((value: number) => {
                this.menuRadius = value;
              })
              .width(120)
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        if (this.selectedOption) {
          Text(`已选择: ${this.selectedOption}`)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 10 })
            .padding(10);
        }

        Column({ space: 15 }) {
          Text('18. 更多示例')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击查看更多Menu示例')
            .fontSize(18)
            .padding(15)
            .backgroundColor(this.themeColor)
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
          Text('19. 文件管理菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('文件管理')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.buildFileManagerMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('20. 编辑工具菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('编辑工具')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.buildEditorMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('21. 视图控制菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('视图控制')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.buildViewControlMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('22. 排序方式菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('排序方式')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindMenu(this.buildSortOptionsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('23. 筛选条件菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('筛选条件')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e0e0e0')
            .borderRadius(8)
            .bindMenu(this.buildFilterOptionsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('24. 用户账户菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('用户账户')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e1bee7')
            .borderRadius(8)
            .bindMenu(this.buildUserAccountMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('25. 应用设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('应用设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#bbdefb')
            .borderRadius(8)
            .bindMenu(this.buildAppSettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('26. 主题选择菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('主题选择')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d1c4e9')
            .borderRadius(8)
            .bindMenu(this.buildThemeSelectionMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('27. 语言切换菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('语言切换')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2ebf2')
            .borderRadius(8)
            .bindMenu(this.buildLanguageSwitchMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('28. 帮助中心菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('帮助中心')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b9f6ca')
            .borderRadius(8)
            .bindMenu(this.buildHelpCenterMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('29. 多级嵌套菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('多级菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffccbc')
            .borderRadius(8)
            .bindMenu(this.buildMultiLevelNestedMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('30. 通知配置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('通知配置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c5cae9')
            .borderRadius(8)
            .bindMenu(this.buildNotificationConfigMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('31. 隐私保护菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('隐私保护')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#d7ccc8')
            .borderRadius(8)
            .bindMenu(this.buildPrivacyProtectionMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('32. 网络连接菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('网络连接')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#b2dfdb')
            .borderRadius(8)
            .bindMenu(this.buildNetworkConnectionMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('33. 显示设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('显示设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c8e6c9')
            .borderRadius(8)
            .bindMenu(this.buildDisplaySettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('34. 音频设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('音频设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff9c4')
            .borderRadius(8)
            .bindMenu(this.buildAudioSettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('35. 电源管理菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('电源管理')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffecb3')
            .borderRadius(8)
            .bindMenu(this.buildPowerManagementMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('36. 存储管理菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('存储管理')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffe0b2')
            .borderRadius(8)
            .bindMenu(this.buildStorageManagementMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('37. 账户安全菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('账户安全')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffcdd2')
            .borderRadius(8)
            .bindMenu(this.buildAccountSecurityMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('38. 系统安全菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('系统安全')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f8bbd9')
            .borderRadius(8)
            .bindMenu(this.buildSystemSecurityMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('39. 无障碍功能菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('无障碍功能')
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
          Text('40. 开发者工具菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('开发者工具')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#80deea')
            .borderRadius(8)
            .bindMenu(this.buildDeveloperToolsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('41. 系统更新菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('系统更新')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#a5d6a7')
            .borderRadius(8)
            .bindMenu(this.buildSystemUpdateMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('42. 数据备份菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('数据备份')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ce93d8')
            .borderRadius(8)
            .bindMenu(this.buildDataBackupMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('43. 应用程序菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('应用程序')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#90caf9')
            .borderRadius(8)
            .bindMenu(this.buildApplicationMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('44. 权限控制菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('权限控制')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ffcc80')
            .borderRadius(8)
            .bindMenu(this.buildPermissionControlMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('45. 设备信息菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('设备信息')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#80cbc4')
            .borderRadius(8)
            .bindMenu(this.buildDeviceInfoMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('46. 时间设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('时间设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#c5e1a5')
            .borderRadius(8)
            .bindMenu(this.buildTimeSettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('47. 格式选项菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('格式选项')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#ef9a9a')
            .borderRadius(8)
            .bindMenu(this.buildFormatOptionsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('48. 系统信息菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('系统信息')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#9fa8da')
            .borderRadius(8)
            .bindMenu(this.buildSystemInfoMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('49. 高级设置菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('高级设置')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#bcaaa4')
            .borderRadius(8)
            .bindMenu(this.buildAdvancedSettingsMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('50. 综合示例菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('综合示例')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#a1887f')
            .borderRadius(8)
            .bindMenu(this.buildComprehensiveMenu())
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)
        .margin({ bottom: 30 })
      }
    }
  }
}
