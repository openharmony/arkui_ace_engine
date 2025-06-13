//@Entry
@Component
struct Case1 {
    @State x:number = 0
    build() {
        TestComponent({ id: 42 }).onChange(() => {
            this.x++
        })
        .log("Case1 - value:" + this.x)
    }
}