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
struct MenuNestedSubMenu {
  @State message: string = '';
  @State selectColor: Color = Color.Blue;
  scroller: Scroller = new Scroller()
  
  private iconStr: Resource = $r('app.media.app_icon');

  @Builder
  NestedMenuBuilder() {
    Menu() {
      MenuItem({
        content: '文件',
        startIcon: this.iconStr,
        builder: (() => {
          MenuItem({ content: '新建文件' })
          MenuItem({ content: '打开文件' })
          MenuItem({ content: '保存' })
          MenuItem({ content: '另存为' })
        })
      })

      MenuItem({
        content: '编辑',
        startIcon: this.iconStr,
        builder: (() => {
          MenuItem({ content: '撤销' })
          MenuItem({ content: '重做' })
          MenuItem({ content: '剪切' })
          MenuItem({ content: '复制' })
          MenuItem({ content: '粘贴' })
        })
      })

      MenuItem({
        content: '视图',
        startIcon: this.iconStr,
        builder: (() => {
          MenuItem({ content: '全屏' })
          MenuItem({ content: '缩放' })
          MenuItem({ content: '左侧边栏' })
          MenuItem({ content: '右侧边栏' })
          MenuItem({ content: '底部面板' })
        })
      })
    }
  }

  @Builder
  ThreeLevelMenuBuilder() {
    Menu() {
      MenuItem({
        content: '一级菜单1',
        builder: (() => {
            MenuItem({
              content: '二级菜单1-1',
              builder: (() => {
                  MenuItem({ content: '三级菜单1-1-1' })
                  MenuItem({ content: '三级菜单1-1-2' })
              })
            })
            MenuItem({ content: '二级菜单1-2' })
        })
      })
      
      MenuItem({
        content: '一级菜单2',
        builder: (() => {
            MenuItem({ content: '二级菜单2-1' })
            MenuItem({ content: '二级菜单2-2' })
        })
      })
    }
  }

  @Builder
  IconMenuBuilder() {
    Menu() {
      MenuItem({ content: '带图标菜单1', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '带图标菜单2', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '带图标菜单3', startIcon: $r('app.media.app_icon') })
    }
  }

  @Builder
  GroupMenuBuilder() {
    Menu() {
      MenuItemGroup({ header: '分组标题1' }) {
        MenuItem({ content: '分组选项1-1' })
        MenuItem({ content: '分组选项1-2' })
        MenuItem({ content: '分组选项1-3' })
      }
      MenuItemGroup({ header: '分组标题2' }) {
        MenuItem({ content: '分组选项2-1' })
        MenuItem({ content: '分组选项2-2' })
      }
    }
  }
  @Builder
  SideExpandMenu() {
    Menu() {
      MenuItem({
        content: '侧边展开1',
        startIcon: this.iconStr,
        builder: (() => {
            MenuItem({ content: '子项1' })
            MenuItem({ content: '子项2' })
        })
      })
      MenuItem({
        content: '侧边展开2',
        startIcon: this.iconStr,
        builder: (() => {
            MenuItem({ content: '子项3' })
            MenuItem({ content: '子项4' })
        })
      })
    }
    .subMenuExpandingMode(SubMenuExpandingMode.SIDE_EXPAND)
  }

  @Builder
  EmbeddedExpandMenu() {
    Menu() {
      MenuItem({
        content: '嵌入展开1',
        startIcon: this.iconStr,
        builder: (() => {
            MenuItem({ content: '子项A' })
            MenuItem({ content: '子项B' })
        })
      })
      MenuItem({
        content: '嵌入展开2',
        startIcon: this.iconStr,
        builder: (() => {
            MenuItem({ content: '子项C' })
            MenuItem({ content: '子项D' })
        })
      })
    }
    .subMenuExpandingMode(SubMenuExpandingMode.EMBEDDED_EXPAND)
  }


  build() {
    Scroll(this.scroller) {
      Column({ space: 20 }) {
        Text('嵌套子菜单示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 });

        Column({ space: 15 }) {
          Text('1. 基本嵌套菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示嵌套菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e3f2fd')
            .borderRadius(8)
            .bindMenu(this.NestedMenuBuilder, {
              title: '文件菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('2. 三级嵌套菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示三级菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e8f5e9')
            .borderRadius(8)
            .bindMenu(this.ThreeLevelMenuBuilder, {
              title: '多级菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('3. 带图标的菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示图标菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fff3e0')
            .borderRadius(8)
            .bindMenu(this.IconMenuBuilder, {
              title: '图标菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('4. 分组菜单')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示分组菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#fce4ec')
            .borderRadius(8)
            .bindMenu(this.GroupMenuBuilder, {
              title: '分组菜单',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('5. 侧边展开模式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示侧边菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#f3e5f5')
            .borderRadius(8)
            .bindMenu(this.SideExpandMenu, {
              title: '侧边展开',
              placement: Placement.Right
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        Column({ space: 15 }) {
          Text('6. 嵌入式展开模式')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)

          Text('点击显示嵌入菜单')
            .fontSize(18)
            .padding(15)
            .backgroundColor('#e0f7fa')
            .borderRadius(8)
            .bindMenu(this.EmbeddedExpandMenu, {
              title: '嵌入展开',
              placement: Placement.Bottom
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(10)

        if (this.message) {
          Text(`选择: ${this.message}`)
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ top: 10 });
        }
      }
    }
  }
}
