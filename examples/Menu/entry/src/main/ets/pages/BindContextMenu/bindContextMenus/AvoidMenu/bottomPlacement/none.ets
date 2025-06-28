@Entry
@Component
struct bottomPlacement_none {
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '二级组件1' })
      MenuItem({ content: '二级组件2' })
      MenuItemGroup({ header: '菜单项目组' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
      }
    }
  }

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ content: '菜单选项1' })
      MenuItem({ content: '菜单选项2' })
      MenuItem({ content: '开启二级菜单', builder: ():void=>this.SubMenu() })
    }.width('100%')
  }

  build() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.End }){
      Column() {
        Text('长按展示菜单')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .bindContextMenu(this.MenuBuilder, ResponseType.LongPress)
    }
  }
}