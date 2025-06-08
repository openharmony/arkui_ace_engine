
@Component
struct ParentStruct {
    build() {
        Column() {
            ChildStruct() {
                Text("xxx")
            }
        }
    }
}

@Component
struct ChildStruct {
    @BuilderParam
    content: () => void

    build() {
        this.content()
    }
}
