//@Entry
@Component
struct Case2 {
    @State x:number = 0
    build() {
        TestComponent({ id: 42 }).onChange(() => {
            this.x--
        })
        .log("Case2 - value:" + this.x)
    }
}