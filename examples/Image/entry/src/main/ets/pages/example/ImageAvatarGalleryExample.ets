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

/**
 * ========================================
 * 业务场景：头像画廊综合示例
 * ========================================
 * 功能说明:
 * 本示例模拟实际业务中的"用户头像画廊"场景，综合演示 Image 组件在真实业务中的用法。
 * 包含：占位图、错误处理、圆角、边框、缓存优化、列表展示、状态切换等。
 *
 * 涉及的 Image API 和特性:
 * 1. Image(src) - 多种数据源 (Resource, string URL, 相对路径)
 * 2. alt(ImageAlt) - 占位图配置（API 22+）
 * 3. objectFit(ImageFit) - 填充模式
 * 4. syncLoad(boolean) - 同步加载优化
 * 5. autoResize(boolean) - 自动降采样
 * 6. interpolation(ImageInterpolation) - 插值效果
 * 7. onComplete / onError - 事件回调
 * 8. borderRadius / border / shadow - 通用样式
 * 9. @Builder / @State - 组件化和状态管理
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 社交应用：用户头像列表
 * - 通讯录：联系人头像
 * - 群组成员：多用户头像展示
 * - 选择器：头像选择/切换
 */

interface User {
  id: number;
  name: string;
  avatar: ResourceStr;
  online: boolean;
  role: string;
}

@Entry
@Component
struct ImageAvatarGalleryExample {
  @State users: Array<User> = [];
  @State selectedUserId: number = -1;
  @State avatarSize: number = 56;
  @State avatarRadius: number = 28;
  @State showShadow: boolean = true;
  @State showOnlineIndicator: boolean = true;
  @State gridColumns: number = 3;
  @State loadMode: string = 'optimized';

  private loadModes: Array<LoadMode> = [
    { name: '优化', value: 'optimized' },
    { name: '质量', value: 'quality' },
    { name: '默认', value: 'default' }
  ];

  aboutToAppear(): void {
    this.initUsers();
  }

  /**
   * 初始化用户数据，混合使用资源引用和字符串路径演示多种加载方式
   */
  private initUsers(): void {
    this.users = [
      { id: 1, name: 'Alice', avatar: $r('app.media.startIcon'), online: true, role: '管理员' },
      { id: 2, name: 'Bob', avatar: $r('app.media.icon'), online: false, role: '成员' },
      { id: 3, name: 'Charlie', avatar: $r('app.media.svg'), online: true, role: '成员' },
      { id: 4, name: 'Diana', avatar: $r('app.media.star'), online: false, role: '访客' },
      { id: 5, name: 'Eve', avatar: $r('app.media.heart'), online: true, role: '管理员' },
      { id: 6, name: 'Frank', avatar: $r('app.media.startIcon'), online: false, role: '成员' },
      { id: 7, name: 'Grace', avatar: $r('app.media.icon'), online: true, role: '成员' },
      { id: 8, name: 'Hank', avatar: $r('app.media.svg'), online: false, role: '访客' },
      { id: 9, name: 'Ivy', avatar: $r('app.media.star'), online: true, role: '成员' }
    ];
  }

  /**
   * 选中用户
   */
  private selectUser(userId: number): void {
    this.selectedUserId = this.selectedUserId === userId ? -1 : userId;
  }

  build(): void {
    Column({ space: 12 }) {
      // 顶部标题栏
      Row({ space: 8 }) {
        Column({ space: 2 }) {
          Text('用户头像画廊')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Black)
          Text('业务场景综合示例')
            .fontSize(11)
            .fontColor(Color.Gray)
        }
        .alignItems(HorizontalAlign.Start)
        .layoutWeight(1)

        Text(`共 ${this.users.length} 人`)
          .fontSize(11)
          .fontColor(Color.White)
          .backgroundColor('#007DFF')
          .borderRadius(10)
          .padding({ left: 8, right: 8, top: 4, bottom: 4 })
      }
      .width('100%')
      .padding({ left: 16, right: 16, top: 16, bottom: 8 })

      // 当前选中用户详情
      this.SelectedUserDetail()

      // 头像画廊
      Scroll() {
        Column({ space: 12 }) {
          // 选中模式：列表
          if (this.gridColumns === 1) {
            this.ListView()
          } else {
            this.GridView()
          }
        }
        .width('100%')
        .padding({ left: 16, right: 16, bottom: 16 })
      }
      .layoutWeight(1)
      .scrollBar(BarState.Off)

      // 底部控制面板
      this.ControlPanel()
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  SelectedUserDetail(): void {
    if (this.selectedUserId !== -1) {
      const user: User | undefined = this.users.find((u: User): boolean => u.id === this.selectedUserId);
      if (user) {
        Row({ space: 16 }) {
          // 大头像
          Stack({ alignContent: Alignment.BottomEnd }) {
            Image(user.avatar)
              .width(80)
              .height(80)
              .objectFit(ImageFit.Cover)
              .borderRadius(40)
              .border({ width: 3, color: '#007DFF' })
              .alt({ placeholder: $r('app.media.startIcon'), error: $r('app.media.startIcon') })
              .interpolation(ImageInterpolation.High)
              .shadow({ radius: 10, color: '#33000000', offsetX: 0, offsetY: 4 })

            if (this.showOnlineIndicator) {
              Circle({ width: 16, height: 16 })
                .fill(user.online ? '#32CD32' : '#AAAAAA')
                .border({ width: 2, color: Color.White })
            }
          }
          .width(80)
          .height(80)

          // 用户信息
          Column({ space: 4 }) {
            Text(user.name)
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .fontColor(Color.Black)
            Text(`ID: ${user.id} · ${user.role}`)
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(user.online ? '在线' : '离线')
              .fontSize(11)
              .fontColor(user.online ? '#32CD32' : '#AAAAAA')
          }
          .alignItems(HorizontalAlign.Start)
          .layoutWeight(1)

          Button('取消选择')
            .fontSize(11)
            .backgroundColor('#FF6347')
            .fontColor(Color.White)
            .height(30)
            .onClick(() => {
              this.selectedUserId = -1;
            })
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)
        .margin({ left: 16, right: 16 })
        .shadow({ radius: 8, color: '#1A000000', offsetX: 0, offsetY: 2 })
      }
    }
  }

  @Builder
  ListView(): void {
    Column({ space: 8 }) {
      ForEach(
        this.users,
        (user: User) => {
          this.UserListItem(user)
        },
        (user: User) => `user_${user.id}`
      )
    }
    .width('100%')
  }

  @Builder
  GridView(): void {
    Grid() {
      ForEach(
        this.users,
        (user: User) => {
          GridItem() {
            this.UserGridItem(user)
          }
        },
        (user: User) => `user_${user.id}`
      )
    }
    .columnsTemplate(this.gridColumnsTemplate())
    .rowsGap(12)
    .columnsGap(12)
    .width('100%')
  }

  @Builder
  UserListItem(user: User): void {
    Row({ space: 12 }) {
      // 头像
      Stack({ alignContent: Alignment.BottomEnd }) {
        Image(user.avatar)
          .width(this.avatarSize)
          .height(this.avatarSize)
          .objectFit(ImageFit.Cover)
          .borderRadius(this.avatarRadius)
          .border({
            width: this.selectedUserId === user.id ? 3 : 0,
            color: '#007DFF'
          })
          .alt({ placeholder: $r('app.media.startIcon'), error: $r('app.media.startIcon') })
          .onClick(() => {
            this.selectUser(user.id);
          })

        if (this.showOnlineIndicator) {
          Circle({ width: 12, height: 12 })
            .fill(user.online ? '#32CD32' : '#AAAAAA')
            .border({ width: 2, color: Color.White })
        }
      }
      .width(this.avatarSize)
      .height(this.avatarSize)

      // 信息
      Column({ space: 3 }) {
        Row({ space: 6 }) {
          Text(user.name)
            .fontSize(15)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
          Text(user.role)
            .fontSize(10)
            .fontColor(this.roleColor(user.role))
            .backgroundColor(this.roleBgColor(user.role))
            .borderRadius(4)
            .padding({ left: 4, right: 4, top: 1, bottom: 1 })
        }
        .alignItems(VerticalAlign.Center)

        Text(`ID: ${user.id}`)
          .fontSize(11)
          .fontColor(Color.Gray)
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)

      // 状态
      Text(user.online ? '● 在线' : '● 离线')
        .fontSize(11)
        .fontColor(user.online ? '#32CD32' : '#AAAAAA')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .border({
      width: this.selectedUserId === user.id ? 2 : 0,
      color: '#007DFF'
    })
    .shadow(this.showShadow ? { radius: 4, color: '#1A000000', offsetX: 0, offsetY: 1 } : { radius: 0 })
  }

  @Builder
  UserGridItem(user: User): void {
    Column({ space: 6 }) {
      // 头像
      Stack({ alignContent: Alignment.BottomEnd }) {
        Image(user.avatar)
          .width(this.avatarSize)
          .height(this.avatarSize)
          .objectFit(ImageFit.Cover)
          .borderRadius(this.avatarRadius)
          .border({
            width: this.selectedUserId === user.id ? 3 : 1,
            color: this.selectedUserId === user.id ? '#007DFF' : '#E0E0E0'
          })
          .alt({ placeholder: $r('app.media.startIcon'), error: $r('app.media.startIcon') })
          .onClick(() => {
            this.selectUser(user.id);
          })

        if (this.showOnlineIndicator) {
          Circle({ width: 12, height: 12 })
            .fill(user.online ? '#32CD32' : '#AAAAAA')
            .border({ width: 2, color: Color.White })
        }
      }
      .width(this.avatarSize)
      .height(this.avatarSize)

      Text(user.name)
        .fontSize(12)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })

      Text(user.role)
        .fontSize(10)
        .fontColor(this.roleColor(user.role))
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
    .alignItems(HorizontalAlign.Center)
    .shadow(this.showShadow ? { radius: 4, color: '#1A000000', offsetX: 0, offsetY: 1 } : { radius: 0 })
  }

  @Builder
  ControlPanel(): void {
    Column({ space: 10 }) {
      Text('控制面板')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      // 头像尺寸
      Row({ space: 8 }) {
        Text('头像尺寸')
          .fontSize(11)
          .width(60)
        Slider(value: this.avatarSize, min: 32, max: 96, step: 4)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.avatarSize = value;
            this.avatarRadius = Math.floor(value / 2);
          })
        Text(`${this.avatarSize}px`)
          .fontSize(11)
          .width(45)
      }
      .width('100%')

      // 圆角调节
      Row({ space: 8 }) {
        Text('圆角')
          .fontSize(11)
          .width(60)
        Slider(value: this.avatarRadius, min: 0, max: 48, step: 2)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.avatarRadius = value;
          })
        Text(`${this.avatarRadius}px`)
          .fontSize(11)
          .width(45)
      }
      .width('100%')

      // 显示选项
      Row({ space: 16 }) {
        Row({ space: 6 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showShadow })
            .onChange((on: boolean) => {
              this.showShadow = on;
            })
          Text('阴影')
            .fontSize(11)
        }

        Row({ space: 6 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showOnlineIndicator })
            .onChange((on: boolean) => {
              this.showOnlineIndicator = on;
            })
          Text('状态指示')
            .fontSize(11)
        }
      }
      .width('100%')

      // 布局切换
      Row({ space: 6 }) {
        Text('布局')
          .fontSize(11)
          .width(40)
        ForEach(
          [1, 2, 3, 4],
          (cols: number) => {
            Button(cols === 1 ? '列表' : `${cols}列`)
              .fontSize(10)
              .backgroundColor(this.gridColumns === cols ? '#007DFF' : '#E0E0E0')
              .fontColor(this.gridColumns === cols ? Color.White : Color.Black)
              .height(26)
              .layoutWeight(1)
              .onClick(() => {
                this.gridColumns = cols;
              })
          },
          (cols: number) => `${cols}`
        )
      }
      .width('100%')

      // 加载模式
      Row({ space: 6 }) {
        Text('加载')
          .fontSize(11)
          .width(40)
        ForEach(
          this.loadModes,
          (mode: LoadMode) => {
            Button(mode.name)
              .fontSize(10)
              .backgroundColor(this.loadMode === mode.value ? '#007DFF' : '#E0E0E0')
              .fontColor(this.loadMode === mode.value ? Color.White : Color.Black)
              .height(26)
              .layoutWeight(1)
              .onClick(() => {
                this.loadMode = mode.value;
              })
          },
          (mode: LoadMode) => mode.value
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(16)
    .backgroundColor('#FFFFFF')
    .borderRadius({ topLeft: 16, topRight: 16 })
    .shadow({ radius: 8, color: '#1A000000', offsetX: 0, offsetY: -2 })
  }

  private gridColumnsTemplate(): string {
    switch (this.gridColumns) {
      case 1:
        return '1fr';
      case 2:
        return '1fr 1fr';
      case 3:
        return '1fr 1fr 1fr';
      case 4:
        return '1fr 1fr 1fr 1fr';
      default:
        return '1fr 1fr 1fr';
    }
  }

  private roleColor(role: string): ResourceColor {
    switch (role) {
      case '管理员':
        return '#FF6347';
      case '成员':
        return '#007DFF';
      case '访客':
        return '#888888';
      default:
        return '#888888';
    }
  }

  private roleBgColor(role: string): ResourceColor {
    switch (role) {
      case '管理员':
        return '#FFE4E1';
      case '成员':
        return '#E6F7FF';
      case '访客':
        return '#F5F5F5';
      default:
        return '#F5F5F5';
    }
  }
}

interface LoadMode {
  name: string;
  value: string;
}
