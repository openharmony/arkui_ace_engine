
import { ManyImportComponent80 } from "./manyImportFile80"
import { ManyImportComponent81 } from "./manyImportFile81"


@Component
export struct ManyImportComponent40 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent80()
            ManyImportComponent81()

        }
    }
}
