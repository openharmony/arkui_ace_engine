@Entry
@Component
struct FlexTest {
    options1: FlexOptions = { }
    options2: FlexOptions = { direction: FlexDirection.Row, wrap: FlexWrap.NoWrap, justifyContent: FlexAlign.Start,
        alignItems: ItemAlign.Auto, alignContent: FlexAlign.Start }
    options3: FlexOptions = { direction: FlexDirection.Column, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Center,
        alignItems: ItemAlign.Start, alignContent: FlexAlign.Center }
    options4: FlexOptions = { direction: FlexDirection.RowReverse, wrap: FlexWrap.WrapReverse, justifyContent: FlexAlign.End,
        alignItems: ItemAlign.Center, alignContent: FlexAlign.End }
    options5: FlexOptions = { direction: FlexDirection.ColumnReverse, justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.End, alignContent: FlexAlign.SpaceBetween }
    options6: FlexOptions = { justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Baseline, alignContent: FlexAlign.SpaceAround }
    options7: FlexOptions = { justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Stretch, alignContent: FlexAlign.SpaceEvenly }
    options8: FlexOptions = { alignItems: ItemAlign.Auto, alignContent: FlexAlign.Center }
    options9: FlexOptions = { direction: FlexDirection.Row }

    build() {
        Flex()
        Flex(this.options1)
        Flex(this.options2)
        Flex(this.options3)
        Flex(this.options4)
        Flex(this.options5)
        Flex(this.options6)
        Flex(this.options7)
        Flex(this.options8)
        Flex(this.options9)
    }
}
