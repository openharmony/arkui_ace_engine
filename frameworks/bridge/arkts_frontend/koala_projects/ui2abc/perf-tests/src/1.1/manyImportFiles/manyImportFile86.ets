
import { ManyImportComponent172 } from "./manyImportFile172"
import { ManyImportComponent173 } from "./manyImportFile173"


@Component
export struct ManyImportComponent86 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent172()
            ManyImportComponent173()

        }
    }
}
