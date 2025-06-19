// import router from '@ohos.router'

@Component
@Entry
struct Page2 {
    onPageShow() {
        console.log('Page2 onPageShow()')
    }

    onPageHide() {
        console.log('Page2 onPageHide()')
    }

    aboutToAppear() {
        console.log('Page2 aboutToAppear()')
    }

    aboutToDisappear() {
        console.log('Page2 aboutToDisappear()')
    }
    build() {
        console.log(`In Page2 build()`)
        Column() {
            Button("Back")
                .width(200).height(100)
                .backgroundColor('#ff0000')
                .onClick((e?: ClickEvent) => {
                    console.log(`back clicked`)
                    // router.back()
                })
        }
    }
}

