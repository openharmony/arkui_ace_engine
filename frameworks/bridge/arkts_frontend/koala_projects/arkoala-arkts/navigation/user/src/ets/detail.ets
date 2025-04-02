//@Entry
@Component
export struct Detail {
    @Consume('pathInfos') pathInfos: NavPathStack

    build() {
        NavDestination() {
            Column() {
                Blank().height('10%')
                // TODO: return Text after it is ready to work correctly
                Text('DetailPage')
                Button('go back').width(200).height(100).onClick((e?: ClickEvent) => {
                    this.pathInfos.pop(true)
                })
            }
            .backgroundColor(Color.Pink).width('100%').height('100%')
        }.hideTitleBar(true)
    }
}