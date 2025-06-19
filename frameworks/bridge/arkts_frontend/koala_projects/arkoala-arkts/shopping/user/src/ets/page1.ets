@Entry
@Component
struct Page1 {
    @State color1: string = '#ff0000'
    @State color2: string = '#00ff00'
    @State state: number = 1

    build() {
        Column() {
            Button("Hi")
                .backgroundColor(this.color1)
                .width(200).height(100)
                .onClick((e?: ClickEvent) => { this.swap() })
            Button("Bye")
                .backgroundColor(this.color2)
                .width(200).height(100)
                .onClick((e?: ClickEvent) => { this.swap() })
            Button("Click! " + this.state).width(200).height(100)
                .width(50)
                .onClick((e?: ClickEvent) => {
                    this.state++
                    console.log("#### Set Button onClick! #" + this.state)
                })
        }
    }

    swap(): void {
        console.log("#### Swap")
        let tmp = this.color1
        this.color1 = this.color2
        this.color2 = tmp
    }
}