import { Detail } from './detail'
import { SearchPage } from './search'

//@Entry
@Component
struct NavigationPage {
    @Provide('pathInfos') pathInfos : NavPathStack = new NavPathStack()

    @Builder
    shoppingRouter(name: string, param: Object) {
        if (name === 'detailPage') {
            Detail()
        } else if (name === 'searchPage') {
            SearchPage()
        }
    }
    build() {
        Navigation(this.pathInfos) {
            Column() {
                Blank().height('10%')
                Button('Detail').width(200).height(100).backgroundColor(Color.Red)
                .onClick((e?: ClickEvent) => {
                    console.log("   ### Button 1005: <DETAIL PAGE> push.") // 1005
                    this.pathInfos.pushPath(new NavPathInfo('detailPage', undefined))
                })
                Button('Search').width(200).height(100).backgroundColor(Color.Blue)
                .onClick((e?: ClickEvent) => {
                    console.log("   ### Button 1006: <SEARCH PAGE> push.") // 1006
                    this.pathInfos.pushPath(new NavPathInfo('searchPage', undefined))
                })
            }
            .backgroundColor(Color.Green).width('100%').height('100%')
        }
        .mode(NavigationMode.Stack)
        .hideTitleBar(true)
        .navDestination(this.shoppingRouter)
    }
}