@Entry
@Component
struct bottomPlacement_bottomRight {
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '二级组件1' })
      MenuItem({ content: '二级组件2' })
      MenuItemGroup({ header: '菜单项目组' }) {
        MenuItem({ content: '菜单' }).contentFont({ size: 16 })
        MenuItem({ content: '菜单' }).contentFont({ size: 16 })
        MenuItem({ content: '菜单' }).contentFont({ size: 16 })
      }
    }
  }

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ content: '菜单选项1' })
      MenuItem({ content: '菜单选项2' })
      MenuItem({ content: '开启二级菜单', builder: ():void=>this.SubMenu() })
        .id('BP_SubMenu_003')
    }.width('100%')
  }

  build() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.End }){
      Column() {
        Text('长按展示菜单')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
      }
      .id('BP_longPress_003')
      .width('100%')
      .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
        placement: Placement.BottomRight
      })
    }
  }
}