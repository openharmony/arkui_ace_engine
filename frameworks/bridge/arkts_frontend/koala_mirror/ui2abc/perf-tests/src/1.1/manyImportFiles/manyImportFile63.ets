
import { ManyImportComponent126 } from "./manyImportFile126"
import { ManyImportComponent127 } from "./manyImportFile127"


@Component
export struct ManyImportComponent63 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent126()
            ManyImportComponent127()

        }
    }
}
