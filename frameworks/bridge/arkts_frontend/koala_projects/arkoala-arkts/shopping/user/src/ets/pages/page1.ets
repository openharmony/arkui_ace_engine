import { AttributeUpdater, ColumnModifier } from '@ohos.arkui.modifier'

class MyColumnModifier extends AttributeUpdater<ColumnAttribute> {
  initializeModifier(instance: ColumnAttribute): void {
    instance.alignItems(HorizontalAlign.Start)

  }
}

@Entry
@Component
struct Index {
  updater: MyColumnModifier = new MyColumnModifier()

  modifier: ColumnModifier = new ColumnModifier().width(20)


  build() {
    Column() {
      Column() {

        Column() {
          // Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
          Text('Text111')
          Text('Text222222')
          //  }
          // .height('8%')
        }
        .width('100%')
          .attributeModifier(this.updater)
      }
      .width(`100%`)
        .backgroundColor('#FFF000')
        .attributeModifier(this.modifier)
    }
  }


}