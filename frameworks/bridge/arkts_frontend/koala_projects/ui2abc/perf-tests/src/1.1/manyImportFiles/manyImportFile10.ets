
import { ManyImportComponent20 } from "./manyImportFile20"
import { ManyImportComponent21 } from "./manyImportFile21"


@Component
export struct ManyImportComponent10 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent20()
            ManyImportComponent21()

        }
    }
}
