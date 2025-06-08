
import { ManyImportComponent112 } from "./manyImportFile112"
import { ManyImportComponent113 } from "./manyImportFile113"


@Component
export struct ManyImportComponent56 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent112()
            ManyImportComponent113()

        }
    }
}
