//import router from '@ohos.router'

//@Entry

@Component
struct TestConsume {
    @State color: Color = Color.Blue
    @State colorFlag: boolean = false
    @Consume('BigYearNumber') @Watch('changeBackgroundColor') state: number
    @State @Watch('changeBackgroundColor') @Watch('inc') anotherState: number = 10000

    build() {
        Button(`Consume: ` + this.state)
            .width(200).height(100)
            .backgroundColor(this.color)
            .onClick((e?: ClickEvent) => { this.inc() })
    }

    inc(stateName?: string) {
        this.state += 1
    }

    changeBackgroundColor(stateName: string) {
        if (this.colorFlag == false) { // enum comparation doesn't compile by es2panda now
            this.colorFlag = true
            this.color = Color.Green
        } else {
            this.colorFlag = false
            this.color = Color.Blue
        }
    }
}

@Component
struct TestProvide {
    @Provide('BigYearNumber') state1: number = 2024

    build() {
        Column() {
            Button('Provide: ' + this.state1)
                .width(200).height(100)
                .backgroundColor('#b420a0')
                .onClick((e?: ClickEvent) => { this.inc() })
            TestConsume()
            TestConsume()
        }
    }

    inc() {
        this.state1 += 100
    }
}

@Component
struct TestStructBuilder {
    build() {
        Column() {
            Button("struct builder test")
        }
        .backgroundColor(Color.Yellow)
        .width('50%')
    }
}

function makeArray(items: number): Array<string> {
    const result = new Array<string>(items)
    for (let i = 0; i < items; i++) result[i] = `elem${i}`
    return result
}

@Component
struct TestBuilderParam {
    @Builder builder() {
        Button("TestBuilder")
    }
    @BuilderParam builderParam: () => void = this.builder
    @BuilderParam anotherParam: () => void = this.builder
    build() {
        Column() {
            this.builderParam()
            this.anotherParam()
        }
    }
}

@Builder
function globalBuilder() {
    Text("AnotherBuilder")
}

@Entry
@Component
struct Page1 {
    @State color1: string = '#ff0000'
    @State color2: string = '#00ff00'
    @State state: number = 1
    @State visible: boolean = false

    data: Array<string> = makeArray(10)

    build() {
        console.log(`In Page1 build()`)

        Column() {
        if (this.visible) {
            console.log("With blinker")
            Button("Blinker")
                .width(200).height(100)
                .backgroundColor('#ff0000')
            Child1()
        }

        ForEach(this.data, (item: string, index: number) => {
        Column() {
            Button("Hi")
                .backgroundColor(this.color1)
                .width(200).height(100)
                .onClick((e?: ClickEvent) => {
                    console.log("Hi button")
                    console.log(`navigate to page2`)
                    this.swap()
                    // router.push({ url: "page2" })
                })
            Button("Bye")
                .backgroundColor(this.color2)
                .width(200).height(100)
                .onClick((e?: ClickEvent) => {
                    console.log("Bye button")
                    this.swap()
                })
            Text($r('app.string.my_text')).height(50)
            Button("Click! " + this.state)
                .width(200).height(100)
                .backgroundColor($r('app.color.my_color'))
                .onClick((e?: ClickEvent) => {
                    this.state++
                    console.log("Click button")
                    console.log("#### Set Button onClick! #" + this.state)
                })
            Image($r('app.media.startIcon')).width(60).height(60)
            Image($rawfile('koala.png')).width(400)
            Text("Set Button onClick! #" + this.state)
                .width(200).height(100)
            TestProvide()
            TestStructBuilder().width('100%')
            TestBuilderParam({anotherParam: globalBuilder})
        }
        .width('100%').height('100%')
        .backgroundColor(Color.Gray)
        .justifyContent(FlexAlign.Center)
        }, (item:string, index: number) => item)
        }
    }

    swap(): void {
        console.log("#### Swap")
        let tmp = this.color1
        this.color1 = this.color2
        this.color2 = tmp
        this.visible = !this.visible
    }
}

@Component
struct Child1 {
    onPageShow() {
        console.log('Child1 onPageShow()')
    }

    onPageHide() {
        console.log('Child1 onPageHide()')
    }

    aboutToAppear() {
        console.log('Child1 aboutToAppear()')
    }

    aboutToDisappear() {
        console.log('Child1 aboutToDisappear()')
    }


    build() {
        console.log('Child1 build()')
    }
}