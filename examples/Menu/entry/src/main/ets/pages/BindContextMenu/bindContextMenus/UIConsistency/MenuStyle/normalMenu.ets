@Entry
@Component
struct MenuStyle_normal {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单选项1' })
      MenuItem({ content: '菜单选项2' })
      MenuItem({ content: '菜单选项3' })
      MenuItem({ content: '菜单选项4' })
      MenuItem({ content: '菜单选项5' })
      MenuItem({ content: '菜单选项6' })
      MenuItem({ content: '菜单选项7' })
      MenuItem({ content: '菜单选项8' })
      MenuItem({ content: '菜单选项9' })
      MenuItem({ content: '菜单选项10' })
      MenuItem({ content: '菜单选项11' })
      MenuItem({ content: '菜单选项12' })
      MenuItem({ content: '菜单选项13' })
      MenuItem({ content: '菜单选项14' })
      MenuItem({ content: '菜单选项15' })
      MenuItem({ content: '菜单选项16' })
      MenuItem({ content: '菜单选项17' })
      MenuItem({ content: '菜单选项18' })
      MenuItem({ content: '菜单选项19' })
      MenuItem({ content: '菜单选项20' })
    }
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
    }
    .bindMenu(this.MyMenu)
  }
}