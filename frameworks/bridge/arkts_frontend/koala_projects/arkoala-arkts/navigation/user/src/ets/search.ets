export interface  BaseRouteParam {
  num: number
  ratio: number
}
export interface SearchParam extends BaseRouteParam {
  message: string
}

//@Entry
@Component
export struct SearchPage {
    @Consume('pathInfos') pathInfos: NavPathStack

    build() {
        NavDestination() {
            Column() {
                Blank().height('10%')
                // TODO: return Text after it is ready to work correctly
                Text('SearchPage')
                Button('go back').width(200).height(100).onClick((e?: ClickEvent) => {
                    this.pathInfos.pop(true)
                })
            }
            .backgroundColor(Color.Orange).width('100%').height('100%')
        }.hideTitleBar(true)
    }
}