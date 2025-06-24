
import { ManyImportComponent22 } from "./manyImportFile22"
import { ManyImportComponent23 } from "./manyImportFile23"


@Component
export struct ManyImportComponent11 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent22()
            ManyImportComponent23()

        }
    }
}
