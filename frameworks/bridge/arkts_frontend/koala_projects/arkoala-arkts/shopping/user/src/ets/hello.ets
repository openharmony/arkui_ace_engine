@Component
struct Hello {
    @State state: number = 1
    build() {
        Column() {
            Button("One").width(200).height(100)
            Button("Two").width(200).height(100)
            Button("Click! " + this.state).width(200).height(100)
                .width(50)
                .onClick((e?: ClickEvent) => {
                    this.state++
                    console.log(">>> Set Button onClick! #" + this.state)
                })
            ProvideExample()
            console.log("Yay! #" + this.state)
        }
    }
}

@Component
struct ProvideExample {
    @Provide("name") x: string = "provided text"

    build() {
        ConsumeExample()
    }
}


@Component
struct ConsumeExample {
    @Consume("name") x: string

    build() {
        Button(this.x).width(200).height(100)
    }
}
